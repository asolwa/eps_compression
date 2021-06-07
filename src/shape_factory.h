/**
     * @file shape_factory.h
     * @brief Plik nagłówkowy dla klasy ShapeFactory
     * @author Piotr Lewandowski
 */

#ifndef EPS_SHAPE_FACTORY_H
#define EPS_SHAPE_FACTORY_H

#include <utility>
#include <unordered_map>
#include <string>
#include <stack>
#include <unordered_map>

#include "eps_objects.h"
#include "shape.h"
#include "graphics_state.h"

using EpsDataPtr = std::shared_ptr<EpsData>;
using EpsDatas = std::vector<EpsDataPtr>;
using ShapePtr = std::shared_ptr<Shape>;

/**
     * @class ShapeFactory
     * @brief Klasa tworząca obiekty Shape
     * @details Klasa, która przetwarza otrzymane aliasy, headery oraz instrukcje i tworzy obiekty typu Shape.
     * @author Piotr Lewandowski
 */

class ShapeFactory {

public:
    /**
     * Metoda, która z otrzymanego wektora obiektów typu EpsData tworzy obiekty Shape, będace łatwiejsze do kompresji.
     * @param epsData Wektor wskaźników na obiekt typu EpsData.
    */
    std::vector<ShapePtr> create(EpsDatas epsData);

    std::vector<std::string> getHeader();

    std::unordered_map<std::string, std::vector<std::string>> getAlias();

private:
    /**
     * Metoda, która dodaje aliasy do declaredAliases_.
     * @param dataPtr Wskaźnik na obiekt typu EpsData
    */
    void convertAlias(EpsDataPtr &dataPtr);

    /**
     * Metoda, która łaczy wektor tokenów w string i dodaje go do wektora header_.
     * @param dataPtr Wskaźnik na obiekt typu EpsData
    */
    void convertHeader(EpsDataPtr &dataPtr);

    /**
     * Metoda, która w zależności od wartości otrzymanej instrukcji aktualizuje graphics_
     * lub tworzy obiekty typu Shape.
     * @param dataPtr Wskaźnik na obiekt typu EpsData
    */
    void convertInstruction(EpsDataPtr &dataPtr);

    /**
     * Metoda, która sprawdza czy podana nazwa znajduje się w mapie aliasów declaredAliases_,
     * jeśli tak to dodaje instrukcje, które oznaczał dany alias do stosu instrukcji oczekujacych
     * na przetworzenie i zwraca wartość true, w przeciwnym wypadku zwraca wartość false.
     * @param dataPtr Wskaźnik na obiekt typu EpsData
    */
    bool replaceAlias(std::string &name, std::stack<std::string> &pendingInstructions);

    std::stack<std::string> pendingInstructions_;
    std::vector<std::string> header_;
    std::unordered_map<std::string, std::vector<std::string>> declaredAliases_;
    std::pair<float, float> currentPoint_;
    std::vector<ShapePtr> shapes_;
    GraphicsState graphics_;
    std::stack<GraphicsState> graphicsStack_;
};


#endif //EPS_SHAPE_FACTORY_H
