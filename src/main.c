#include <stdio.h>
#include <stdlib.h> // srand ve rand fonksiyonları için
#include <time.h>   // rastgele sayı üretimi için

// --- Durum Değişkenleri ---
int saglik = 100;   // 0-100 aralığında
int enerji = 100;   // 0-100 aralığında
int yemek_sayisi = 5;
int siginak_bulundu = 0; // 0:Hayır , 1:Evet

// Fonksiyon prototipleri (SWITCH-CASE içinde çağırılacak komutlar)
void avlan();
void siginak_ara();
void envanter_goster();
void dinlen();
void tehlike_serisi();
void sifreli_ilerleme();
void durumu_goster();   // Yardımcı fonksiyon

int main() {
    //Rastgele sayı üretecinin başlangıcını (seed) ayarla
    srand(time(NULL));

    char komut;

    // Ana komut dinlenme döngüsü (do-while zorunluluğu)
    do{
        durumu_goster(); // Mevcut durumu ekrana yazdır
        printf("\n>> komut girin (A, S, E, R, F, P, X: ");
        scanf(" %c", &komut); // Boşluk, önceki new-line karakterini yutmak için önemli

        //Büyük/küçük harf duyarlılığını kaldırmak için komutu büyük harfe çevirelim
        if (komut >= 'a' && komut <= 'z') {
            komut -= 32;
        }
        // --- Komut İşleme: SWITCH-CASE Zorunlu ---
        switch (komut) {
            case 'A':
                avlan();
                break;
            case 'S':
                siginak_ara();
                break;
            case 'E':
                envanter_goster();
                break;
            case 'R':
                dinlen();
                break;
            case 'F':
                tehlike_serisi();
                break;
            case 'P':
                sifreli_ilerleme();
                break;
            case 'X':
                printf("\nSimülasyondan çıkılıyor.Hayatta kaldığınız günler kaydedildi!\n");
                break;
            default:
                printf("\nGEÇERSİZ KOMUT! Lütfen A, S, E, R, F, P veya X girin.\n");
                break;

        }

        //Öldü mü kontrolü (Sağlık veya Enerji 0'ın altına düşerse)
        if (saglik <= 0 || enerji <= 0){
            printf("\n!!! SIMULASYON SONA ERDI !!!\n");
            printf("Sağlığınız (%d) veya Enerjiniz (%d) sıfırn altına düştü.\n", saglik, enerji);
            komut = 'X'; //Döngüden çıkmak için komutu 'X' yap
        }

    } while (komut != 'X');
    return 0;
}
// Yardımcı Fonksiyon: Durumu Ekrana Yazdırır
void durumu_goster() {
    printf("\n--- Mevcut Durum ---\n");
    printf("Sağlık: %d/100\n", saglik);
    printf("Enerji: %d/100\n", enerji);
    printf("Yemek Sayısı: %d\n", yemek_sayisi);
    printf("Sığınak: %s\n", siginak_bulundu ? "BULUNDU (Koruma altında)" : "YOK (Açık alan)");
    printf("--------------------\n");
}

// Avlan Komutu: Enerji harca, yemek kazanmaya çalış
void avlan() {
    printf("\n>>> AVLANIYORSUNUZ...\n");

    // 1. Enerji Kaybı (Aritmetik Operatörler)
    int harcanan_enerji = 10;
    enerji = enerji - harcanan_enerji; // Veya enerji -= 10;
    printf("- %d Enerji harcandı. (Kalan Enerji: %d)\n", harcanan_enerji, enerji);

    if (enerji < 0) enerji = 0; // Enerji negatif olmasın

    // 2. Yemek Kazanma İhtimali (IF ile değerlendirilir)
    int sans = rand() % 100; // 0-99 arası rastgele sayı

    // Enerji yüksekse başarılı olma şansı artsın
    if (sans < 60 || enerji > 50) { // Basit IF ve birleştirilmiş koşul örneği
        int kazanilan_yemek = rand() % 3 + 1; // 1-3 arası yemek
        yemek_sayisi += kazanilan_yemek;
        printf("BAŞARILI! %d adet yemek buldunuz. (Toplam: %d)\n", kazanilan_yemek, yemek_sayisi);

        // Yemek yersek enerjimiz artsın
        if (yemek_sayisi > 0) {
            yemek_sayisi--;
            int geri_kazanilan_enerji = 5;
            enerji += geri_kazanilan_enerji;
            if (enerji > 100) enerji = 100;
            printf("Bir yemek yediniz ve %d Enerji geri kazandınız.\n", geri_kazanilan_enerji);
        }

    } else {
        printf("Başarısız oldunuz. Hiç yemek bulamadınız.\n");
    }
}
// Sığınak Ara Komutu: Sığınak bulma ihtimali mantıksal operatörlerle değerlendirilir

void siginak_ara() {
    printf("\n>>> SIĞINAK ARIYORSUNUZ...\n");

    // Enerji Kaybı
    enerji -= 5;
    if (enerji < 0) enerji = 0;

    if (siginak_bulundu) {
        printf("Zaten bir sığınağınız var. Boşuna aramayınız!\n");
        return;
    }

    // Koşullar: Yemek varsa VE Enerji yüksekse VEYA çok şanslıysak
    int sans = rand() % 100;

    // Mantıksal Operatörler (&amp;&amp; ve || zorunluluğu)
    if ((yemek_sayisi >= 2 && enerji >= 40) || (sans > 85)) {
        // IF-ELSE yapısıyla değerlendirilir
        siginak_bulundu = 1;
        printf("Büyük bir şans eseri, mükemmel bir Sığınak buldunuz! Artık daha güvendesiniz.\n");
    } else {
        printf("Aramanız sonuçsuz kaldı. Etrafınızdaki bölge güvensiz görünüyor.\n");

        // Başarısızlık durumunda küçük bir risk alalım
        if (sans < 10) {
            saglik -= 5;
            printf("Arama sırasında küçük bir yaralanma yaşadınız! -5 Sağlık.\n");
            if (saglik < 0) saglik = 0;
        }
    }
}
// Dinlen Komutu: Enerji ve Sağlık Artışı

void dinlen() {
    printf("\n>>> DİNLENİYORSUNUZ...\n");

    // Aritmetik İşlemlerle Sağlık ve Enerji Artışı

    int kazanilan_enerji = 25;
    int kazanilan_saglik = 10;

    // Yetersiz yemek uyarısı

    if (yemek_sayisi < 1) {
        kazanilan_enerji -= 10;
        printf("Yeterli yemeğiniz yok! Dinlenme verimi düştü.\n");
    } else {
        yemek_sayisi--; // Bir adet yemek tüket
        printf("Bir yemek yediniz ve iyice dinlenmeye başladınız.\n");
    }

    enerji += kazanilan_enerji;
    saglik += kazanilan_saglik;

    // Sınır Kontrolü (IF-ELSE Yapıları)

    if (enerji > 100) {
        enerji = 100;
    }

    if (saglik > 100) {
        saglik = 100;
    }

    printf("Enerji: +%d (Yeni: %d/100)\n", kazanilan_enerji, enerji);
    printf("Sağlık: +%d (Yeni: %d/100)\n", kazanilan_saglik, saglik);
}

// Envanter Görüntüleme Komutu

void envanter_goster() {
    printf("\n--- ENVANTER ---\n");
    printf("Yemek Sayısı: %d\n", yemek_sayisi);
    printf("------------------\n");
}

// Komut F: Tehlike Serisi (FOR Döngüsü Zorunluluğu)

void tehlike_serisi() {
    printf("\n>>> BÖLGEDE KISA BİR TEHLİKE DALGASI BAŞLADI!\n");
    int i;
    int tehlike_sayisi = rand() % 3 + 3; // 3 ila 5 arası tehlike simüle et

    // FOR Döngüsü Zorunluluğu
    for (i = 1; i <= tehlike_sayisi; i++) {
        printf("\n--- Tehlike %d ---\n", i);
        enerji -= 3; // Enerji her turda düşer (Aritmetik İşlem)
        if (enerji < 0) enerji = 0;

        int risk = rand() % 100;

        // Sığınağın varlığı ve enerji seviyesi hasarı etkilesin (IF-ELSE)
        if (siginak_bulundu) {
            printf("Sığınak koruması sayesinde küçük bir risk atlattınız.\n");
        } else if (enerji < 20) {
            // Düşük enerji + sığınak yoksa büyük hasar riski
            if (risk > 70) {
                int hasar = rand() % 15 + 10;
                saglik -= hasar;
                printf("ÇOK YÜKSEK RİSK! Ciddi hasar aldınız: -%d Sağlık.\n", hasar);
            } else {
                printf("Zorlukla atlattınız. Neyse ki büyük yara almadınız.\n");
            }
        } else {
            // Normal risk
            if (risk > 50) {
                int hasar = rand() % 8 + 3;
                saglik -= hasar;
                printf("Yaralandınız: -%d Sağlık.\n", hasar);
            }
        }
    }

    printf("\nTehlike serisi sona erdi. Kalan Sağlık: %d, Kalan Enerji: %d\n", saglik, enerji);
    if (saglik < 0) saglik = 0;
}

// Komut P: Şifreli İlerleme (DO-WHILE Döngüsü Zorunluluğu)

void sifreli_ilerleme() {
    printf("\n>>> ÖNÜNÜZDE KİLİTLİ BİR ENGEL VAR. ŞİFRE GEREKİYOR.\n");
    char gizli_karakter = 'Z'; // Geçilmesi gereken doğru karakter
    char tahmin;
    int deneme_sayisi = 0;

    // DO-WHILE Döngüsü Zorunluluğu
    do {
        printf("Kilidi açmak için bir karakter girin (Veya X ile vazgeçin): ");
        scanf(" %c", &tahmin);
        deneme_sayisi++;

        // Büyük harfe çevirme
        if (tahmin >= 'a' && tahmin <= 'z') {
            tahmin -= 32;
        }

        // Enerji kontrolü: Her deneme enerji kaybetsin
        enerji -= 2;
        if (enerji < 0) enerji = 0;

        if (tahmin == 'X') {
            printf("Vazgeçtiniz ve geri döndünüz.\n");
            return;
        }

        if (tahmin != gizli_karakter) {
            printf("YANLIŞ. Kilit açılmadı. -2 Enerji kaybettiniz.\n");
        }

        // Öldü mü kontrolü
        if (enerji <= 0) {
            printf("Kilidi açmaya çalışırken enerjiniz tükendi!\n");
            break;
        }

    } while (tahmin != gizli_karakter);

    if (tahmin == gizli_karakter) {
        printf("\nBAŞARILI! Engeli %d denemede aştınız.\n", deneme_sayisi);
        printf("Güvenli bölgeye geçtiniz. +10 Enerji kazandınız.\n");
        enerji += 10;
        if (enerji > 100) enerji = 100;
    }
}
