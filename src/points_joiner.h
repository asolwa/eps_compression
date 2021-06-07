/**
 * \file points_joiner.h
 * \brief Klasa sluzaca do laczenie punktow w wieksze punkty
 */
/** 
 * @file points_joiner.h
 * @class PointsJoiner
 * @brief Klasa sluzaca do laczenie punktow w wieksze punkty
 * @details Klasa sluzaca do laczenie punktow w wieksze punkty
 *          Na podstawie parametrow takich jak maksymalny promien polaczenia
 *          oraz stopen kwantyzacji przestrzeni, przetwarza otrzymany wektor punktow,
 *          laczac odpowiedni puntkty w wieksze linie, na podstaiw wczesniej podanych parametrow
 * 
 * @author Adam Solawa
 * @date 07.06.2021
 */
#ifndef POINTS_JOINER
#define POINTS_JOINER

#include <tuple>
#include <vector>
#include "shape_factory.h"

using Point = std::tuple<float, float, float, float>;
using Points = std::vector<Point>;
using Coordinate = std::pair<float, float>;
using Coordinates = std::vector<Coordinate>;

class PointsJoiner {
    private:
        /** Zmienna sluzaca do oznaczania danych w wektorze do usuniecia */
        static const int TO_DELETE = -1;
        /** Liczba okreslajaca odleglosc dla ktorej dane 2 pkt sa laczone */
        float thr_;
        /** Liczba okreslajaca stopien skantyzowania przestrzeni */
        int grid_factor_;

        /**
         * Funkcja ktora zamienia wektor punktow na wektor tupli
         * 
         * @param shapes Wektor punktow, danych do konwersji
         */
        Points convert(const std::vector<ShapePtr> &shapes);
        /**
         * Funkcja ktora sortuje punkty ze wzgledu na 1 a nastepnie 2 skladowa
         * 
         * @param shapes Wektor punktow do posortowania, ten argument jest modyfikowany
         */
        void sort(Points &points_cloud);
        /**
         * Funkcja ktora laczy punkty w linie
         * 
         * @param shapes Wektor punktow do polaczenia, ten argument jest modyfikowany
         */
        void doJoin(Points &points_cloud); 

    public:
        PointsJoiner() = delete;
        /** 
         * Konstruktor kompresora.
         * Przyjmuje kompresor ktory przyjmuje wartosc thr.
         * 
         * @param thr Liczba okreslajaca co ktory element jaka jest maksymalna odleglosc
         * miedzy dwoma punktamy ktore algorymt laczy
         * @param grid_factor_ Liczba orkeslajaca stopnien skfanyzowania przstrzestrzeni, uzytej do szeregowania elementow
         */
        PointsJoiner(int grid_factor_,  float thr=1.0);
        /**
         * Funkcja ktora laczy punkty, przyjmuje wektor punktow, zwraca wektor tupli, gotowych do wypisanaia
         * 
         * @param shapes Wektor punktow, danych to laczenia
         */
        Points join(const std::vector<ShapePtr> &shapes);  
};

#endif /* POINTS_JOINER */
