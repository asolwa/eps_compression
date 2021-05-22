/**
 * \file compressor.h
 * \brief Klasa bedaca interfejsem do kompresji plikow
 */
#ifndef COMPRESSOR
#define COMPRESSOR

#include <vector>
#include <utility>

using PointData = std::vector<std::pair<float, float>>;

/** 
 * @file compressor.h
 * @class Compressor
 * @brief Klasa bedaca interfejsem do konkretnych metod kompresji
 * @details Makieta obiektu kompresora, ktory wywoluje konkretne
 *          implementacje kompressji znajdujace sie w dekoratorach
 * 
 * @author Adam Solawa
 * @date 15.05.2021
 */
class Compressor {
public:
    /** 
     * Funkcja delegujaca kompresje wektora punktow do konkretnych kompresorow dekoratorow
     * 
     * @param data Wektor punktow do kompresji
     */
    virtual PointData compress(const PointData &data);
    virtual ~Compressor();
};

#endif /* COMPRESSOR */
