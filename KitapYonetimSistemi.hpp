#ifndef KITAP_YONETIM_SISTEMI_HPP
#define KITAP_YONETIM_SISTEMI_HPP

#include "Kitap.hpp"
#include <vector>

class KitapYonetimSistemi {
private:
    std::vector<Kitap> kitaplar;
    std::string dosyaAdi = "kitaplar.txt";
    std::string kullaniciAdi;

public:
    void kullaniciArayuzu();

private:
    void kitapEkle();
    void kitapListele() const;
    void kitapAra() const;
    void kitapDuzenle();
    void kitapSil();
    void kitaplariDosyayaKaydet() const;
    void kitaplariDosyadanYukle();
    void kullaniciGiris();
    void kullaniciCikis();
    void hataMesaji() const;
    void temizle() const;
};

#endif // KITAP_YONETIM_SISTEMI_HPP
