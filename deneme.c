#include <GLUT/glut.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)
// �zgara i�inde �izim yapmak i�in kullan�lacak koordinatlar
typedef struct koordinatlar
{
    char** satirDizisi;
    size_t satirSayisi;
    char satir[100];
    int* x;
    int* y;
    int size;
    int index;
} t_koordinatlar;
struct koordinatlar x;
char satir[100];
int corner = 1;
int type;
int line = 0;
int alan = 0;
int fcor = 0;
int sondaj;
int platform;
void find_square(int alan)
{

    int i = 0;
    int a, b, c, d, e;
    while (alan > 0)
    {
        if (alan > 256)
        {
            alan = alan % 256;
            e = alan / 256;
            printf("%d", e);
        }
        else if (alan > 64 && alan < 256)
        {
            alan = alan % 64;
            d = alan / 64;
            printf("%d", d);
        }
        else if (alan > 16 && alan < 64)
        {
            alan = alan % 16;
            c = alan / 16;
            printf("%d", c);
        }
        else if (alan > 4 && alan < 16)
        {
            alan = alan % 4;
            b = alan / 4;
            printf("%d", b);
        }
        else if (alan > 1 && alan < 4)
        {
            alan = alan % 1;
            a = alan / 1;
            printf("%d", a);
        }
        else
            printf("hatal� de�er");

        int toplam = a + b + c + d + e;
        int platform_maliyeti = platform * toplam;
        int sondaj_maliyeti = sondaj * toplam;
        int toplam_maliyet = platform_maliyeti + sondaj_maliyeti;
        printf("Platform maliyeti:%d", platform_maliyeti);
        printf("Sondaj maliyeti:%d", sondaj_maliyeti);
        printf("Toplam maliyeti:%d", toplam_maliyet);
    }
}

int find_area(int type)
{

    if (type > 3)
    {
        //Shoelace Form�l�'n� kullanarak �okgenin alan�n� bulduk.
        int temp;
        for (int i = 0; i < type / 2; i++) {
            temp = x.x[i + fcor];
            x.x[i + fcor] = x.x[type - 1 - i + fcor];
            x.x[type - 1 - i + fcor] = temp;

            temp = x.y[i + fcor];
            x.y[i + fcor] = x.y[type - 1 - i + fcor];
            x.y[type - 1 - i + fcor] = temp;
        }
        // Toplam alan� hesaplad�k
        for (int i = 0; i < type; i++) {
            int j = (i + 1 + fcor) % type;
            alan += (x.x[i + fcor] * x.y[j + fcor]) - (x.x[j + fcor] * x.y[i + fcor]);
        }

        // Mutlak de�eri al�p ve 0.5 ile �arpt�k
        alan = 0.5 * fabs(alan);
    }
    else if (type == 3)
    {
        alan = 0.5 * fabs(x.x[fcor] * (x.y[fcor + 1] - x.y[fcor + 2]) + x.x[fcor + 1] * (x.y[fcor + 2] - x.y[fcor]) + x.x[fcor + 2] * (x.y[fcor] - x.y[fcor + 1]));
    }
    return(alan);
}

int flag = 1;
void drawForm(void)
{

    glColor3f(1.0, 0.0, 1.0); // D�rtgenin rengi (k�rm�z�)

    // D�rtgeni �iz
    type = x.size - corner;
    fcor = corner;

    if (type == 4) {
        glBegin(GL_QUADS);
        while (corner <= x.size) {
            glVertex2f(x.x[corner], x.y[corner]);
            corner++;
        }

    }
    else if (type == 3) {
        glBegin(GL_TRIANGLES);
        while (corner <= x.size) {
            glVertex2f(x.x[corner], x.y[corner]);
            corner++;

        }
    }
    else if (type == 5)
    {
        glBegin(GL_POLYGON);
        while (corner <= x.size) {
            glVertex2f(x.x[corner], x.y[corner]);
            corner++;
        }
    }
    else if (type == 6)
    {
        glBegin(GL_POLYGON);
        while (corner <= x.size) {
            glVertex2f(x.x[corner], x.y[corner]);
            corner++;
        }


    }
    else if (type == 7)
    {
        glBegin(GL_POLYGON);
        while (corner <= x.size) {
            glVertex2f(x.x[corner], x.y[corner]);
            corner++;
        }


    }
    else if (type == 8)
    {
        glBegin(GL_POLYGON);
        while (corner <= x.size) {
            glVertex2f(x.x[corner], x.y[corner]);
            corner++;
        }


    }
    else if (type == 9)
    {
        glBegin(GL_POLYGON);
        while (corner <= x.size) {
            glVertex2f(x.x[corner], x.y[corner]);
            corner++;
        }


    }
    
    glEnd();
    glFlush();


    if (flag == 1) {
        fcor--;
        flag = 0;
    }
    int c = find_area(type); // Alan hesaplamas�n� bir kez yap
    printf("\nCokgenin alani: %d\n", c);
    printf("Rezerv alani:%d\n", c * 10);

    c = 0;
}
int getlineee(void) {
    int l;
    printf("0-%lu between Select line: ", x.satirSayisi - 1);
    scanf("%d", &l);
    while (l > x.satirSayisi - 1)
        scanf("%d", &l);
    return (l);
}

void takelocation(int line) {
    int i = 0;
    int n = 0;
    char* token;
    printf("%s", x.satirDizisi[line]);
    token = strstr(x.satirDizisi[line], "(");
    while (token)
    {
        // Virg�l�n solundaki de�eri al�n
        x.x[i] = atoi(token + 1); // +1, '(' karakterini atlamak i�indir
        token = strstr(token, ",");
        // Bir sonraki parantezi bulun
        if (token == NULL) {
            break; // Parantez bulunamazsa d�ng�y� sonland�r�n
        }

        // Virg�l�n sa��ndaki de�eri al�n
        x.y[i] = atoi(token + 1); // +1, ')' karakterini atlamak i�indir

        // Bir sonraki parantezi aray�n
        token = strstr(token, "(");
        i++;

    }
    /* for (int n = 0; x.x[n]; n++)
     {
        //printf("\nx= %d, y= %d", x.x[n], x.y[n]);
     }*/
    int index = 1;
    while (x.x[index]) {
        if ((x.x[n] == x.x[index]) && (x.y[n] == x.y[index])) {
            n = ++index;
            x.size = n;
            drawForm();
        }
        index++;
    }
}

void drawGrid()
{
    glColor3f(0.5, 0.5, 0.5);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    for (int i = -100; i <= 100; i++) {
        glVertex2f(i, -100);
        glVertex2f(i, 100);
        glVertex2f(-100, i);
        glVertex2f(100, i);
    }
    glEnd();
    takelocation(line);
    glFlush();

}

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Derinlik pufunu temizle
    //Grid cizimi
    drawGrid();
    glFlush();


}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 100, 0);
    glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char** argv) {
    // �ekece�iniz URL'yi ve hedef dosyan�n ad�n� belirtin
    const char* url = " "; 
    const char* dosyaAdi = "indirilen_veri.txt";

    // curl komutunu kullanarak verileri �ekme
    char komut[256];
    snprintf(komut, sizeof(komut), "curl -o %s %s", dosyaAdi, url);
    int sonuc = system(komut);

    if (sonuc == 0) {
        printf("Veriler ba�ar�yla �ekildi ve '%s' dosyas�na kaydedildi.\n", dosyaAdi);
    }
    else {
        printf("Veriler �ekilirken bir hata olu�tu.\n");
    }


    FILE* dosya = fopen("indirilen_veri.txt", "r"); // Okunacak dosyay� a��n
    if (dosya == NULL) {
        perror("Dosya a�ma hatas�");
        return 1;
    }
    int i = 0;
    x.satirSayisi = 0;
    x.satirDizisi = (char**)malloc(sizeof(char) * 100);
    x.x = (int*)malloc(sizeof(int) * 100);
    x.y = (int*)malloc(sizeof(int) * 100);
    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        x.satirDizisi[i] = strdup(satir);
        i++;
        x.satirSayisi++;
    }
    line = getlineee();
    printf("birim sondaj maliyetini giriniz:");
    scanf("%d", &sondaj);
    printf("birim platform maliyetini giriniz:");
    scanf("%d", &platform);
    glutInit(&argc, argv);
    //glClear(GL_COLOR_BUFFER_BIT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL sekil");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    glEnd();
    glFlush();

 
    return(0);
}