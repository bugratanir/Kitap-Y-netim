#include "KitapYonetimSistemi.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>

void KitapYonetimSistemi::kullaniciArayuzu() {
    kullaniciGiris();

    int secim;
    do {
        std::cout << "\n----- Kitap Yönetim Sistemi -----\n";
        std::cout << "1. Kitap Ekle\n";
        std::cout << "2. Kitap Listele\n";
        std::cout << "3. Kitap Ara\n";
        std::cout << "4. Kitap Düzenle\n";
        std::cout << "5. Kitap Sil\n";
        std::cout << "6. Kitapları Dosyaya Kaydet\n";
        std::cout << "7. Çıkış\n";
        std::cout << "Seçiminizi yapın: ";
        std::cin >> secim;

        switch (secim) {
            case 1:
                temizle();
                kitapEkle();
                break;
            case 2:
                temizle();
                kitapListele();
                break;
            case 3:
                temizle();
                kitapAra();
                break;
            case 4:
                temizle();
                kitapDuzenle();
                break;
            case 5:
                temizle();
                kitapSil();
                break;
            case 6:
                temizle();
                kitaplariDosyayaKaydet();
                break;
            case 7:
                temizle();
                kullaniciCikis();
                break;
            default:
                temizle();
                hataMesaji();
        }
    } while (secim != 7);
}

void KitapYonetimSistemi::kitapEkle() {
    Kitap yeniKitap;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Önceki girişi temizle

    std::cout << "Kitap Adı: ";
    std::getline(std::cin, yeniKitap.ad);

    std::cout << "Yazar: ";
    std::getline(std::cin, yeniKitap.yazar);

    std::cout << "Yıl: ";
    std::cin >> yeniKitap.yil;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Buffer temizle

    std::cout << "Kategori: ";
    std::getline(std::cin, yeniKitap.kategori);

    kitaplar.push_back(yeniKitap);
    std::cout << "Kitap eklendi: " << yeniKitap.ad << std::endl;
}

void KitapYonetimSistemi::kitapListele() const {
    std::cout << "----- Kitap Listesi -----\n";
    for (const auto& kitap : kitaplar) {
        std::cout << "Ad: " << kitap.ad << ", Yazar: " << kitap.yazar << ", Yıl: " << kitap.yil << ", Kategori: " << kitap.kategori << std::endl;
    }
}

void KitapYonetimSistemi::kitapAra() const {
    std::string arananKelime;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Önceki girişi temizle

    std::cout << "Aranacak Kelime: ";
    std::getline(std::cin, arananKelime);

    std::cout << "----- Sonuçlar -----\n";
    for (const auto& kitap : kitaplar) {
        if (kitap.ad.find(arananKelime) != std::string::npos ||
            kitap.yazar.find(arananKelime) != std::string::npos ||
            kitap.kategori.find(arananKelime) != std::string::npos) {
            std::cout << "Ad: " << kitap.ad << ", Yazar: " << kitap.yazar << ", Yıl: " << kitap.yil << ", Kategori: " << kitap.kategori << std::endl;
        }
    }
}

void KitapYonetimSistemi::kitapDuzenle() {
    std::string duzenlenecekAd;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Önceki girişi temizle

    std::cout << "Düzenlenecek Kitap Adı: ";
    std::getline(std::cin, duzenlenecekAd);

    auto it = std::find_if(kitaplar.begin(), kitaplar.end(), [duzenlenecekAd](const Kitap& kitap) {
        return kitap.ad == duzenlenecekAd;
    });

    if (it != kitaplar.end()) {
        std::cout << "Yeni Kitap Adı: ";
        std::getline(std::cin, it->ad);

        std::cout << "Yeni Yazar: ";
        std::getline(std::cin, it->yazar);

        std::cout << "Yeni Yıl: ";
        std::cin >> it->yil;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Buffer temizle

        std::cout << "Yeni Kategori: ";
        std::getline(std::cin, it->kategori);

        std::cout << "Kitap düzenlendi: " << it->ad << std::endl;
    } else {
        std::cout << "Kitap bulunamadı.\n";
    }
}

void KitapYonetimSistemi::kitapSil() {
    std::string silinecekAd;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Önceki girişi temizle

    std::cout << "Silinecek Kitap Adı: ";
    std::getline(std::cin, silinecekAd);

    auto it = std::remove_if(kitaplar.begin(), kitaplar.end(), [silinecekAd](const Kitap& kitap) {
        return kitap.ad == silinecekAd;
    });

    if (it != kitaplar.end()) {
        kitaplar.erase(it, kitaplar.end());
        std::cout << "Kitap silindi: " << silinecekAd << std::endl;
    } else {
        std::cout << "Kitap bulunamadı.\n";
    }
}

void KitapYonetimSistemi::kitaplariDosyayaKaydet() const {
    std::ofstream dosya(dosyaAdi);

    if (!dosya.is_open()) {
        std::cerr << "Dosya açılamadı: " << dosyaAdi << std::endl;
        return;
    }

    for (const auto& kitap : kitaplar) {
        dosya << kitap.ad << ',' << kitap.yazar << ',' << kitap.yil << ',' << kitap.kategori << '\n';
    }

    std::cout << "Kitaplar dosyaya kaydedildi.\n";
}

void KitapYonetimSistemi::kitaplariDosyadanYukle() {
    std::ifstream dosya(dosyaAdi);

    if (!dosya.is_open()) {
        std::cerr << "Dosya açılamadı: " << dosyaAdi << std::endl;
        return;
    }

    kitaplar.clear();

    std::string satir;
    while (std::getline(dosya, satir)) {
        std::istringstream ss(satir);
        std::string ad, yazar, kategori;
        int yil;

        std::getline(ss, ad, ',');
        std::getline(ss, yazar, ',');
        ss >> yil;
        ss.ignore(); // ',' karakterini atla
        std::getline(ss, kategori);

        kitaplar.push_back({ad, yazar, yil, kategori});
    }

    std::cout << "Kitaplar dosyadan yüklendi.\n";
}

void KitapYonetimSistemi::kullaniciGiris() {
    std::cout << "Kullanıcı Adı: ";
    std::cin >> kullaniciAdi;
    std::cout << "Merhaba, " << kullaniciAdi << "!\n";
}

void KitapYonetimSistemi::kullaniciCikis() {
    std::cout << "Hoşça kal, " << kullaniciAdi << "!\n";
}

void KitapYonetimSistemi::hataMesaji() const {
    std::cerr << "Geçersiz seçim. Lütfen tekrar deneyin.\n";
}

void KitapYonetimSistemi::temizle() const {
    // Ekranı temizleme işlemi
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

int main() {
    KitapYonetimSistemi kitapYonetim;
    kitapYonetim.kullaniciArayuzu();
    return 0;
}
