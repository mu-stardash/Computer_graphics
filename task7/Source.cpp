#include <iostream>
#include <glut.h>
#include "FreeImage.h"

const double PI = 3.141592653589793;
GLuint earth; // текстура Земли
GLuint space; // текстура космоса
GLuint sea;   // текстура водички

/* Загрузка изображения */
FIBITMAP* loadImage(const char* filename)
{
    FIBITMAP* dib = nullptr;
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filename);// Определяет тип графического файла просто по его расширению

    dib = FreeImage_Load(fif, filename, JPEG_DEFAULT); // Загружает в память графический файл с диска.
    /* Проверяем, успешно ли прошла загрузка */
    if (!dib)
    {
        std::cerr << "Image loading ERROR" << std::endl;
        exit(0);
    }
    std::cerr << "Success" << std::endl;
    return dib;
}

GLuint loadTexture(FIBITMAP* dib)
{
    GLuint tex = 0;    // идентификатор текстуры
    int x, y;		   // пиксели
    int height, width; // высота, ширина

    RGBQUAD rgbquad;
    FREE_IMAGE_TYPE type;
    //BITMAPINFOHEADER* header;
    BYTE* bits = nullptr;
    bits = FreeImage_GetBits(dib);		// вытаскиваем биты изображения

    type = FreeImage_GetImageType(dib); // тип
    height = FreeImage_GetHeight(dib);  // высота
    width = FreeImage_GetWidth(dib);    // ширина

    //header = FreeImage_GetInfoHeader(dib); // Эта структура содержит информацию о размерах и цветовом формате независимого от устройства растрового изображения (DIB)

    /* Получаем пиксели изображения  и запоминаем в texels */
    int scanLineWidh = ((3 * width) % 4 == 0) ? 3 * width : ((3 * width) / 4) * 4 + 4;
    unsigned char* texels = (GLubyte*)calloc(height * scanLineWidh, sizeof(GLubyte)); // фактические данные изображения
    for (x = 0; x < width; x++)
        for (y = 0; y < height; y++)
        {
            FreeImage_GetPixelColor(dib, x, y, &rgbquad);
            texels[(y * scanLineWidh + 3 * x) + 0] = ((GLubyte*)&rgbquad)[2]; // RED
            texels[(y * scanLineWidh + 3 * x) + 1] = ((GLubyte*)&rgbquad)[1]; // BLUE
            texels[(y * scanLineWidh + 3 * x) + 2] = ((GLubyte*)&rgbquad)[0]; // GREEN
        }
    glGenTextures(1, &tex);			   // генерация имени текстуры (1 -количество, &tex - куда сохраняет текстуру)
    glBindTexture(GL_TEXTURE_2D, tex); // связываем

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Повторяет текстурное изображение, если вышел за диапазон границ по ОХ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // по ОY
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // фильтрация, когда масштабирование вниз
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // когда масштрабирование вверх

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, // генерация текстуры 
        width, height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, texels);

    free(texels); // освобождаем выделенную память
    return tex;
}

GLuint LoadTextureAUTO(std::string filename)
{
    GLuint tex;								     // идентификатор текстуры
    FIBITMAP* dib = loadImage(filename.c_str()); // загружаем изображение (вызов функции)
    tex = loadTexture(dib);					     // загружаем текстуру (вызов функции)
    FreeImage_Unload(dib);						 // выгружаем
    return tex;
}

void renderScene() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5, 2, 10, 5, 0, 0, 0, 1, 0);

    /* Рисуем нижнюю стенку (пол) и наклкдываем на нее текстуру воды */
    glBindTexture(GL_TEXTURE_2D, sea);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);                     glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 1);                     glVertex3f(0.0f, 0.0f, 10.0f);
    glTexCoord2f(1, 1);                     glVertex3f(10.0f, 0.0f, 10.0f);
    glTexCoord2f(1, 0);                     glVertex3f(10.0f, 0.0f, 0.0f);
    glEnd();

    /* Начинаем рисовать стены */
    glBindTexture(GL_TEXTURE_2D, space); // текстура космоса только для первой (задней стенки)
    /* Задняя стенка */
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);                     glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 1);                     glVertex3f(0.0f, 3.0f, 0.0f);
    glTexCoord2f(1, 1);                     glVertex3f(10.0f, 3.0f, 0.0f);
    glTexCoord2f(1, 0);                     glVertex3f(10.0f, 0.0f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D); // отключаем текстурирование, чтобы другие стены были без текстур
 
    /* Стенка справа */
    glBegin(GL_QUADS);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 3.0f, 0.0f);
    glVertex3f(10.0f, 3.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glEnd();

    /* Передняя стенка */
    glBegin(GL_QUADS);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 3.0f, 10.0f);
    glVertex3f(0.0f, 3.0f, 10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

    /* Стенка слева */
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 3.0f, 0.0f);
    glVertex3f(0.0f, 3.0f, 10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

    /* Верхняя стенка (потолок) */
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 3.0f, 0.0f);
    glVertex3f(10.0f, 3.0f, 0.0f);
    glVertex3f(10.0f, 3.0f, 10.0f);
    glVertex3f(0.0f, 3.0f, 10.0f);
    glEnd();

    /* Рисуем цилиндр */
    glTranslatef(3, 1.5, 2);
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= 360; j += 1) {
        glVertex3f(cos(j * PI / 180), 1, sin(j * PI / 180)); 
        glVertex3f(cos(j * PI / 180), -1, sin(j * PI / 180));
    }
    glEnd();
 
    /* Рисуем сферу */
    glTranslatef(4, 0, 1);                // отодвигаем вправо
    glEnable(GL_TEXTURE_2D);              // включаем текстурирование
    glBindTexture(GL_TEXTURE_2D, earth);  // будем накладывать текстуру Земли
    double r = 1; // радиус
    int nx = 30;  // кол-во окружностей парал. ОХ (для формирования поверхности)
    int ny = 30;  // кол-во окружностей парал. ОY (для формирования поверхности)
    double i, ix, iy;
    double x, y, z;
    glRotatef(90, 1, 0, 0); // поворачиваем
    glBegin(GL_QUAD_STRIP); 
    for (iy = 0; iy <= ny; ++iy) // по y
    {
        for (ix = 0; ix <= nx; ++ix) 
        {
            /* Проекция на оси высчитываем по формулам */
            x = r * sin(iy * PI / ny) * cos(2 * ix * PI / nx); // x = r*sina*cosa 
            y = r * sin(iy * PI / ny) * sin(2 * ix * PI / nx); // y = r*sina*sinb
            z = r * cos(iy * PI / ny);                         // z = rcosa
            /* Нормаль направлена от центра */
            glNormal3f(x, y, z);
            glTexCoord2f((double)ix / (double)nx, (double)iy / (double)ny);
            glVertex3f(x, y, z); // отрисовываем
       
            x = r * sin((iy + 1) * PI / ny) * cos(2 * ix * PI / nx);
            y = r * sin((iy + 1) * PI / ny) * sin(2 * ix * PI / nx);
            z = r * cos((iy + 1) * PI / ny);
            glNormal3f(x, y, z);
            glTexCoord2f((double)ix / (double)nx, (double)(iy + 1) / (double)ny);
            glVertex3f(x, y, z);
        }
    }
    glEnd();

    glutSwapBuffers();
}

/* При изменении размера окна */
void ChangeSize(int w, int h) {
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;   // отношение ширины окна к высоте
    glMatrixMode(GL_PROJECTION); // матрица проекции (проецирование 3д в 2д)
    glLoadIdentity();            // заменяет тек.матрицу матрицей единичной (в начало коорд)
    glViewport(0, 0, w, h);      // область окна, в которой отображается рез работы
    gluPerspective(45.0f, ratio, 0.1f, 100.0f); // перспективное преобразование (для визуализации 3д обьекта)
                                                //3-расстояние от центра проецирования до ближайшей отсек плоскости
                                                //4- расстояние от центра проец до задней плоскости отсечения
    glMatrixMode(GL_MODELVIEW);  // матрица активной камеры. Служит для отрисовки обьемных обьектов сцены
}



void init2() {
    GLfloat light_ambient[] = { 0.7, 0.7, 0.7, 1.0 }; // интенсивность фонового света (цвет света)
    GLfloat light_diffuse[] = { 0.4, 0.4, 0.4, 1.0 }; // устанавливаем диффузный цвет света (рассеянный свет) (зеркальный блик на обьекте)
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };// интенсивность зеркального света (0-белый)
    GLfloat light_position[] = { -4.0, 1.0, -8.0, 1.0 }; // устанавливаем положение точечного (w = 1 - лампочка, 0 -солнце (бесконечный))) источника света

    glMaterialfv(GL_FRONT, GL_SPECULAR, light_diffuse);

    /* Устанавливаем источнику света параметры */
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_specular);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);                // вкл. расчет освещения
    glEnable(GL_LIGHT0);                  // разблокировка источника света
  //  glEnable(GL_DEPTH_TEST);              // буфер глубины
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);                                    // инициализация glut (1-колво аргументов, 2-их описание)
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// определяем режим отображения
                                                              // 1-буфер глубины, 2-режим двойной буферизации(подходит для анимации)
                                                              // 3-выбирает цветовое окно
    glutInitWindowPosition(100, 100);                         // (начало координат окна) инициализация окна приложения (х-колво пикс от левой части экрана, у-от верхней
    glutInitWindowSize(1000, 600);                            // размеры окна

    glutCreateWindow("НАИКРАСИВЕЙШИЙ НАТЮРМОРТ");			      // создаем окно с именем

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    init2();                                                  // инициализация освещения
    glutDisplayFunc(renderScene);							  // вызывается функция всякий раз при перерисовке окна
    glutReshapeFunc(ChangeSize);							  // отвечает за изменения окна
    glutIdleFunc(renderScene);								  // отвечает за анимацию

    /* Загружаем текстуры */
    space = LoadTextureAUTO("SpaceNEW.jpg");
    sea = LoadTextureAUTO("SeaNEW.jpg");
    earth = LoadTextureAUTO("earth.jpg");

    glutMainLoop();											  // вход в главный цикл
    return 0;
}