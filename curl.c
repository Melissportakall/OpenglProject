#include <stdio.h>
#include <stdlib.h>

int main() {
    // Çekeceğiniz URL'yi ve hedef dosyanın adını belirtin
    const char *url = "http://bilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt";
    const char *dosyaAdi = "indirilen_veri.txt";

    // `curl` komutunu kullanarak verileri çekme
    char komut[256];
    snprintf(komut, sizeof(komut), "curl -o %s %s", dosyaAdi, url);
    int sonuc = system(komut);

    if (sonuc == 0) {
        printf("Veriler başarıyla çekildi ve '%s' dosyasına kaydedildi.\n", dosyaAdi);
    } else {
        printf("Veriler çekilirken bir hata oluştu.\n");
    }
    FILE *dosya = fopen("indirilen.txt","r");
    if(dosya == NULL)
    {
        perror("dosya acma hatasi");
        return 1;
    }
    return 0;
}