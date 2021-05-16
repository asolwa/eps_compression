/**
 * \file compressor_decorator.h
 * \brief Plik zawierajacy dekorator bazowy klas kompresji
 */
#ifndef BASE_COMPRESSOR_DECORATOR
#define BASE_COMPRESSOR_DECORATOR

#include <memory>
#include "compressor.h"

/** 
 * @file compressor_decorator.h
 * @class BaseCompressorDecorator
 * @brief Klasa bedaca dekoratorem bazowym klas kompresji
 * @details Klasa bedaca dekoratorem bazowym klas kompresji
 *          Wykonuje kompresje korzystajac z kompresora konretnego
 *          przekazanego w konstruktorze
 * 
 * @author Adam Solawa
 * @date 15.05.2021
 */
class BaseCompressorDecorator : public Compressor {
private:
    /** Kompresor konkretny, ktory wykonuje kompresje */
    std::shared_ptr<Compressor> compressor_;
public:
    /** 
     * Konstruktor ktory przyjmuje kompresor dekorowany
     * 
     * @param compressor Kompresor konktertny do dekracji
     */
    BaseCompressorDecorator(std::shared_ptr<Compressor> compressor);
    /**
     * Funkcja wirtualna ktora deleguje kompresje do kompresora konkretnego
     * 
     * @param data Wektor danych do kompresji
     */
    virtual PointData compress(PointData data);
};

#endif /* BASE_COMPRESSOR_DECORATOR */
