#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "BANKA.h"
int main() {
    int para; // Kullanıcının hesabındaki para miktarı
    srand(time(NULL));
    para = rand() % 500 + 500; // Rastgele bir para değeri belirleme (500-999 arası)
    int sifre; // Kullanıcının girdiği şifre
    int sayac = 0; // Şifre deneme sayacı
    while (sayac < 3) { // Kullanıcının 3 kere şifre deneme hakkı var
        printf("\tSIFRE GIRINIZ\n");
        if (scanf("%d", &sifre) == 1) {
            if (sifre == 1234) { // Doğru şifre girilirse döngüden çık
                break;
            }
        } else {
            printf("\tHATA\n");
            scanf("%*s"); // Hatalı giriş olduğunda tekrar denemek için
        }
        sayac++;
        if (sayac == 3) { // 3 kere hatalı şifre girildiğinde hesabı bloke et
            printf("\tBLOK\n");
            return 1;
        }
    }
    // Menü fonksiyonuna yönlendirme
    menu(&para);
    return 0;
}

void menu(int *para) {
    printf("\t--------------------\n\n");
    printf("\tKULLANILABILIR BAKIYE %dTL\n", *para); // Mevcut bakiye gösterimi
    int a; // Kullanıcının menü seçimi
    printf("\t1-PARA CEKME\n \t2-PARA YATIRMA\n \t3-FATURA ODEME\n \t4-IBAN'A HAVALE\n\t5=CIKIS\n");

    while (1) {
        if (scanf("%d", &a) != 1) { // Geçersiz giriş kontrolü
            printf("\tYANLIS GIRIS\n");
            scanf("%*s"); // Hatalı girdiyi temizleme
        } else {
            switch (a) {
                case 1:
                    printf("\t--------------------\n\n");
                    cek(para); // Para çekme fonksiyonunu çağırma
                    printf("\t--------------------\n\n");
                    break;
                case 2:
                    printf("\t--------------------\n\n");
                    yatir(para); // Para yatırma fonksiyonunu çağırma
                    printf("\t--------------------\n\n");
                    break;
                case 3:
                    printf("\t--------------------\n\n");
                    ode(para); // Fatura ödeme fonksiyonunu çağırma
                    printf("\t--------------------\n\n");
                    sleep(2); // İşlem sonrası kısa bir bekleme
                    break;
                case 4:
                    printf("\t--------------------\n\n");
                    gonder(para); // Para gönderme fonksiyonunu çağırma
                    printf("\t--------------------\n\n");
                    break;
                case 5:
                    printf("\t--------------------\n\n");
                    printf("\tKARTINIZI ALINIZ\n"); // Çıkış mesajı
                    printf("\t--------------------\n\n");
                    exit(EXIT_SUCCESS);
                default:
                    printf("YANLIS GIRDI"); // Geçersiz menü seçeneği
                    scanf("%*s");
            }
        }
        printf("\t1-PARA CEKME\n \t2-PARA YATIRMA\n \t3-FATURA ODEME\n \t4-IBAN'A HAVALE\n\t5=CIKIS\n"); // Menü seçeneklerini tekrar göster
    }
}

void yatir(int *para) {
    int paraekle; // Kullanıcının yatırmak istediği para miktarı
    printf("\tYATIRMAK ISTEDIGINIZ TUTARI GIRINIZ: \n");
    scanf("%d", &paraekle);
    *para += paraekle; // Mevcut bakiyeye ekleme yap
    printf("\tISLEM BASARIYLA GERCEKLESTIRILDI\n");
    printf("\tHESABINIZDAKI BAKIYE: %d\n", *para); // Yeni bakiyeyi göster
}

void cek(int *sayi) {
    int miktar; // Kullanıcının çekmek istediği para miktarı
    printf("\tKULLANILABILIR BAKIYE %dTL\n", *sayi);
    printf("\tCEKMEK ISTEDIGINIZ TUTARI GIRINIZ\n");
    scanf("%d", &miktar);
    if (miktar <= 0 || miktar > *sayi) {
        printf("\tEKSIK VEYA HATALI GIRIS MENU'YE YONLENDIRME YAPILIYOR\n"); // Hatalı giriş durumunda
    } else {
        *sayi -= miktar; // Bakiyeden çekilen miktarı düş
        printf("\tISLEMINIZ BASARILI...\n");
    }
}

void ode(int *sayi) {
    int sec, kod, ucret, secim; // Fatura ödeme işlemi için değişkenler
    srand(time(NULL));
    ucret = rand() % 100 + 50; // Rastgele bir fatura ücreti belirleme (50-149 arası)
    printf("\tKULLANILABILIR BAKIYE %dTL\n", *sayi);
    printf("\t1-DOGALGAZ 2-ELEKTRIK 3-SU\n");

    if (scanf("%d", &sec) != 1) { // Geçersiz giriş kontrolü
        printf("\tHATALI GIRIS\n");
        scanf("%*s");
    } else {
        printf("\tFATURA KODUNU GIRINIZ\n");
        switch (sec) {
            case 1:
                scanf("%d", &kod);
                if (kod == 1234 && *sayi >= ucret) {
                    printf("FATURA UCRETINIZ %d TL ", ucret);
                    printf("ONAYLAMAK ICIN 1 E BASINIZ ");
                    scanf("%d", &secim);
                    if (secim == 1) {
                        *sayi -= ucret; // Bakiyeden fatura ücretini düş
                        printf("\tISLEMINIZ GERCEKLESTIRILIYOR\n");
                    }
                    else {
                        printf("\tISLEM IPTAL EDILDI\n");
                    }
                } else {
                    printf("YANLIS KOD GIRDINIZ MENUYE YONLENDIRILIYORSUNUZ...");
                }
                break;
            case 2:
                scanf("%d", &kod);
                if (kod == 5678 && *sayi >= ucret) {
                    printf("FATURA UCRETINIZ %d TL ", ucret);
                    *sayi -= ucret;
                    printf("ONAYLAMAK ICIN 1 E BASINIZ ");
                    scanf("%d", &secim);
                    if (secim == 1) {
                        *sayi -= ucret;
                        printf("\tISLEMINIZ GERCEKLESTIRILIYOR\n");
                    }
                    else {
                        printf("\tISLEM IPTAL EDILDI\n");
                    }
                } else {
                    printf("YANLIS KOD GIRDINIZ MENUYE YONLENDIRILIYORSUNUZ...");
                }
                break;
            case 3:
                scanf("%d", &kod);
                if (kod == 1357 && *sayi >= ucret) {
                    printf("FATURA UCRETINIZ %d TL ", ucret);
                    *sayi -= ucret;
                    printf("ONAYLAMAK ICIN 1 E BASINIZ ");
                    scanf("%d", &secim);
                    if (secim == 1) {
                        *sayi -= ucret;
                        printf("\tISLEMINIZ GERCEKLESTIRILIYOR\n");
                    }
                    else {
                        printf("\tISLEM IPTAL EDILDI\n");
                    }
                } else {
                    printf("YANLIS KOD GIRDINIZ MENUYE YONLENDIRILIYORSUNUZ...");
                }
                break;
            default:
                printf("YANLIS KOD GIRDINIZ MENUYE YONLENDIRILIYORSUNUZ...");
                break;
        }
    }
}

void gonder(int *para) {
    int user_iban; // Kullanıcının gireceği IBAN numarası
    int gonder_para; // Gönderilmek istenen para miktarı
    printf("\tIBAN GIRINIZ: \n");
    scanf("%d", &user_iban);

    if (user_iban == 12345) {
        printf("\tGONDERILMEK ISTENILEN TUTARI GIRINIZ: \n");
        scanf("%d", &gonder_para);
        if (gonder_para > *para) {
            printf("\tBAKIYENIZI KONTROL EDINIZ\n"); // Yetersiz bakiye durumu
        } else {
            *para -= gonder_para; // Bakiyeden gönderilen miktarı düş
            printf("\tISLEM BASARILI\n");
            printf("\tMEVCUT BAKIYE: %d\n", *para);
        }
    } else {
        printf("\tYANLIS IBAN BILGISI\n"); // Geçersiz IBAN durumu
    }
}
