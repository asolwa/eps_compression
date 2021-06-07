/**
 * \file points_joiner.cpp
 * \brief Plik zawierajacy implementacje joinera punktow 
 */
#include <algorithm>
#include <cmath>
#include "points_joiner.h"


Points PointsJoiner::join(const std::vector<ShapePtr> &shapes) {
    Points result = convert(shapes);
    sort(result);
    doJoin(result);
    return result;
}

Points PointsJoiner::convert(const std::vector<ShapePtr> &shapes) {
    Points result;
    for(auto &shape : shapes) {
        float x=0;
        float y=0;
        float rx=0;
        float ry=0;
        Coordinates points_ = shape->getPoints();

        x = trunc( points_[0].first*grid_factor_ ) / grid_factor_;
        y = trunc( points_[0].second*grid_factor_ ) / grid_factor_;
        rx = trunc(( points_[1].second - points_[0].second ) * grid_factor_ ) / grid_factor_;
        ry = trunc(( points_[2].first - points_[1].first ) * grid_factor_ ) / grid_factor_;
        result.push_back({x, y, rx, ry});
    }
    return result;
}

void PointsJoiner::sort(Points &points_cloud) {
    std::sort(points_cloud.begin(), points_cloud.end(), [](const Point &a, const Point &b) {
        return (std::get<0>(a) < std::get<0>(b));
    });

    for(auto element = points_cloud.begin(); element != points_cloud.end(); ++element) {
        float current_x = std::get<0>(*element);
        auto upper = std::upper_bound(points_cloud.begin(), points_cloud.end(),
                                      current_x, [](float current_x, Point &a) {
            return current_x < std::get<0>(a);
        });

        if(upper != points_cloud.end() && (upper-1) != element ) {
            std::sort(element, upper, [](const Point &a, const Point &b) {
                return std::get<1>(a) < std::get<1>(b);
            });
        }
    }
}

void PointsJoiner::doJoin(Points &points_cloud) {
    for(auto first = points_cloud.begin(); first != points_cloud.end()-1; ++first) {
        if(std::get<0>(*first) != PointsJoiner::TO_DELETE) {
            for(auto sec = first + 1; sec != points_cloud.end() &&
                ( std::get<0>(*first) == std::get<0>(*sec) || std::get<0>(*sec) == PointsJoiner::TO_DELETE); ++sec) {
                if(std::get<0>(*sec) != PointsJoiner::TO_DELETE) {
                    if (abs(std::get<1>(*first) - std::get<1>(*sec)) < thr_) {
                        std::get<0>(*sec) = PointsJoiner::TO_DELETE;
                    } else if (abs(std::get<1>(*first) - std::get<1>(*sec)) < thr_ + std::get<2>(*first)) {
                        std::get<3>(*first) += std::get<3>(*sec);
                        std::get<3>(*first) -= (std::get<1>(*sec) - std::get<1>(*first));
                        std::get<0>(*sec) = PointsJoiner::TO_DELETE;
                    } else
                        break;
                }
            }
        }
    }
}

PointsJoiner::PointsJoiner(int grid_factor, float thr) : thr_(thr), grid_factor_(grid_factor) {}
