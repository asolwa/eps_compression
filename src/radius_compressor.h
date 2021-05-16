/**
 * \file radius_compressor.h
 * \brief Plik zawierajacy implementacje kompresora opartego o promien
 */
#ifndef RADIUS_COMPRESSOR
#define RADIUS_COMPRESSOR

#include "compressor_decorator.h"

using Point = std::pair<float, float>;

/** 
 * @file radius_compressor.h
 * @class RadiusCompressor
 * @brief Klasa bedaca kompresorem konkretnym
 * @details Klasa bedaca kompresorem konkretnym,
 *          dziedziczy po dekoratorze bazowym.
 *          Kompresja polega na pomijaniu kolejnych elementow
 *          jezeli znajduja sie blizej niz dlugos promienia r
 * 
 * @author Adam Solawa
 * @date 15.05.2021
 */
class RadiusCompressor : public BaseCompressorDecorator {
private:
    /** Wartosc graniczna odlaglosci dla ktorej odrzucane sa pkt */
    int thr_;
    /** 
     * Funckja sprawdzajaca czy dane 2 pkt sa w odleglosci mniejszej niz thr_
     * 
     * @param a Pierwszy punkt, zawierajacy wspolzedne x i y
     * @param b Drugi punkt, zawierajacy wspolzedne x i y
     * @return Zwraca wartosc logina okreslajaca czy punkty sa oddalone o mniej niz thr_
     */
    bool closer_than_radius(const Point &a, const Point &b);
public: 
    /** 
     * Konstruktor kompresora.
     * Przyjmuje kompresor ktory zostanie udekorowany,
     * oraz liczbe okreslajacy promien
     * 
     * @param dec Kompresor ktory zostanie udekorowany
     * @param radius Liczba okreslajaca promien w ktorym punkty sa odrzucane
     */
    RadiusCompressor(std::shared_ptr<Compressor> dec, int radius=1);
    /**
     * Funkcja ktora wywoluje kompresje a rzecz kompresora bazowego,
     * a nastepnie wlasna kompresje, ktora polega na odrzucanu kolejnych punktow
     * jezeli znajduja sie blizej niz wartosc promia
     * 
     * @param data Wektor danych do kompresji
     */
    virtual PointData compress(PointData data);
};

#endif /* RADIUS_COMPRESSOR */
