/**
 * \file skip_n_compressor.h
 * \brief Plik zawierajacy interfejs kompresora pomijajacego co n-ty element 
 */
#ifndef SKIP_N_COMPRESSOR
#define SKIP_N_COMPRESSOR

#include "compressor_decorator.h"

/** 
 * @file skip_n_compressor.h
 * @class SkipNCompressor
 * @brief Klasa bedaca kompresorem konkretnym
 * @details Klasa bedaca kompresorem konkretnym,
 *          dziedziczy po dekoratorze bazowym.
 *          Kompresja polega na zachowaniu co n-tego elementu
 *          danych, reszta zostaje porzucona.
 * 
 * @author Adam Solawa
 * @date 15.05.2021
 */
class SkipNCompressor: public BaseCompressorDecorator {
private:
    /** Liczba okreslajaca co ktory element jest zachowywany */
    int skip_n_;
public:
    SkipNCompressor() = delete;
    /** 
     * Konstruktor kompresora.
     * Przyjmuje kompresor ktory zostanie udekorowany,
     * oraz liczbe okreslajacy co ktory element jest zachowywany
     * 
     * @param dec Kompresor ktory zostanie udekorowany
     * @param skip_n Liczba okreslajaca co ktory element jest zachowywany, domyslna wartosc to 2
     */
    SkipNCompressor(std::shared_ptr<Compressor> dec, int skip_n=2);
    /**
     * Funkcja ktora wywoluje kompresje a rzecz kompresora bazowego,
     * a nastepnie wlasna kompresje, ktora polega na zostawieniu co n-tego elementu
     * z wynikowej porcji danych
     * 
     * @param data Wektor danych do kompresji
     */
    virtual PointData compress(PointData data);
};

#endif /* SKIP_N_COMPRESSOR */
