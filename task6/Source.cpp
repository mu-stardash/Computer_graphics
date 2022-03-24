#include <iostream>
#include <glut.h>
#include "FreeImage.h"
#include <string>

#define PI 3.1415927 // пи
#define ANGLE 15     // угол поворота в градусах 
#define RADIUS 1.0f  // радиус окружностей
#define H 6			 // высота цилиндра


float angleRight = 0, angleUp = 0, angleLeft = 0, angleDown = 0; // для поворота при нажатии на стрелки
const float light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };		 // интенсивность фонового света (цвет света)
const float light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };		 // устанавливаем диффузный цвет света (рассеянный свет) (зеркальный блик на обьекте)
const float light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };		 // интенсивность зеркального света (0-белый)
const float light_position[] = { 2.0f, 0.0f, 2.0f, 1.0f};		 // устанавливаем положение точечного (w = 1 - лампочка, 0 -солнце (бесконечный))) источника света

GLuint Texture1; // текстура чачки пипсов
GLuint Texture2; // текстура крышки с промокодом
GLuint Texture3; // текстура дна (железка)
GLuint texture; // текстура

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


void renderScene() {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера. 1-очистка экрана
	//glLoadIdentity();									// заменяет тек.матрицу матрицей единичной (в начало коорд)

	//gluLookAt(-8, 1, 5, 0, 0, 0, 0, 1, 0);    //1,2,3-определяют положение глаза наблюдателя
	//										  //4,5,6-указывает точку, куда направлен его взгляд
	//										  //7,8,9-указывает направление вытянутой вверх руки наблюдателя

	//glEnable(GL_LIGHT0); // разблокировка источника света
	//glEnable(GL_LIGHTING);	

	///* Устанавливаем источнику света параметры */
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	///* Ставим банку нормально */
	//glRotatef(90, 0, 0, 1);

	///* Создаем две параллельные окружности, равноудаленные от т.(0, 0, 0) по OY */	
	//glPushMatrix();
	//glRotatef(-180, 1, 0, 1);
	//glTranslatef(0, 0, H / 2); // верхняя окружность
	//float angle, radian, x1, y1, xcos, ysin, tx, ty;

	//glEnable(GL_TEXTURE_2D); 
	//glBindTexture(GL_TEXTURE_2D, Texture2); // указываем текстуру крышки

	//glBegin(GL_POLYGON);
	//for (angle = 0.0; angle < 360.0; angle += 2.0)
	//{
	//	radian = angle * (PI / 180.0f);

	//	xcos = (float)cos(radian);				 ysin = (float)sin(radian);
	//	x1 = xcos * RADIUS;					     y1 = ysin * RADIUS;
	//	tx = (x1 / RADIUS + 1) * 0.5;			 ty = (y1 / RADIUS + 1) * 0.5;

	//	glTexCoord2f(tx, ty);
	//	glVertex2f(x1, y1);
	//}
	//glEnd();
	//glDisable(GL_TEXTURE_2D);

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, Texture3); // указываем текстуру дна
	//glTranslatef(0, 0, -H);

	//glBegin(GL_POLYGON);
	//for (angle = 0.0; angle < 360.0; angle += 2.0)
	//{
	//	radian = angle * (PI / 180.0f);

	//	xcos = (float)cos(radian);				 ysin = (float)sin(radian);
	//	x1 = xcos * RADIUS;					     y1 = ysin * RADIUS;
	//	tx = (x1 / RADIUS + 1) * 0.5;			 ty = (y1 / RADIUS + 1) * 0.5;

	//	glTexCoord2f(tx, ty);
	//	glVertex2f(x1, y1);
	//}

	//glEnd();
	//glDisable(GL_TEXTURE_2D);
	//glPopMatrix();

	///* Строим сам цилиндр */
	//glPushMatrix();
	//glRotatef(-90, 0, 1, 0);
	//const int n = 360 / ANGLE; // кол-во точек, по которым строится цилиндр
	//double x[n], y[n];
	//for (int k = 0; k < n; k++) {
	//	x[k] = cos((double)2 * PI * k / n);
	//	y[k] = sin((double)2 * PI * k / n);
	//}
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, Texture1);

	//for (int k = 0; k < n; k++) {
	//	int m = (k + 1) % n;

	//	glBegin(GL_POLYGON);
	//	glTexCoord2f(0.99 / n * (k), 0.0);					 glVertex3f(x[k], y[k], H / 2);
	//	glTexCoord2f(0.99 / n * (k), 1.0);					 glVertex3f(x[k], y[k], -H / 2);
	//	glTexCoord2f(0.99 / n * ((double)k + 1), 1.0);		 glVertex3f(x[m], y[m], -H / 2);
	//	glTexCoord2f(0.99 / n * ((double)k + 1), 0.0);		 glVertex3f(x[m], y[m], H / 2);
	//	glEnd();
	//}
	//glDisable(GL_TEXTURE_2D);
	//glPopMatrix();

	//glutSwapBuffers();






	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера. 1-очистка экрана
	glLoadIdentity();									// заменяет тек.матрицу матрицей единичной (в начало коорд)

	gluLookAt(40, 3, 7, 0, 0, 0, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* Поворачиваем при нажатии на стрелки */
	glRotatef(angleRight, 0.0f, 1.0f, 0.0f);
	glRotatef(angleUp, 1.0f, 0.0f, 0.0f);
	glRotatef(angleLeft, 0.0f, -1.0f, 0.0f);
	glRotatef(angleDown, -1.0f, 0.0f, 0.0f);

	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	double r = 10;
	int nx = 30;
	int ny = 30;
	int i, ix, iy;
	double x, y, z;
	glBegin(GL_QUAD_STRIP);
	for (ix = 0; ix <= nx; ++ix)
	{
		for (iy = 0; iy <= ny; ++iy)
		{
			x = r * sin(iy * PI / ny);
			y = r * sin(iy * PI / ny) * cos(2 * ix * PI / nx);
			z = r * sin(iy * PI / ny)* sin(2 * ix * PI / nx);
			//нормаль направлена от центра
			glNormal3f(x, y, z);
			glTexCoord2f((double)ix / (double)nx, (double)iy / (double)ny);
			glVertex3f(x, y, z);
			x = r * sin((iy + 1) * PI / ny) *
				cos(2 * ix * PI / nx);
			y = r * sin((iy + 1) * PI / ny) *
				sin(2 * ix * PI / nx);
			z = r * cos((iy + 1) * PI / ny);
			glNormal3f(x, y, z);
			glTexCoord2f((double)ix / (double)nx, (double)(iy + 1) / (double)ny);
			glVertex3f(x, y, z);
		}
	}
	glEnd();
	glutSwapBuffers();
}

/* Обработка нажатия стрелок на клавиатуре */
void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_LEFT:
		angleLeft += 5.0f;
		break;
	case GLUT_KEY_RIGHT:
		angleRight += 5.1f;
		break;
	case GLUT_KEY_UP:
		angleUp += 5.1f;
		break;
	case GLUT_KEY_DOWN:
		angleDown += 5.1f;
		break;
	}
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

/* Главная функция */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                                    // инициализация glut (1-колво аргументов, 2-их описание)
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// определяем режим отображения
															  // 1-буфер глубины, 2-режим двойной буферизации(подходит для анимации)
															  // 3-выбирает цветовое окно
	glutInitWindowPosition(100, 100);                         // (начало координат окна) инициализация окна приложения (х-колво пикс от левой части экрана, у-от верхней
	glutInitWindowSize(1000, 600);                            // размеры окна

	glutCreateWindow("ЧАЧКА ПИПСОВ К ПИВУ");			      // создаем окно с именем

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glutDisplayFunc(renderScene);							  // вызывается функция всякий раз при перерисовке окна
	glutReshapeFunc(ChangeSize);							  // отвечает за изменения окна
	glutIdleFunc(renderScene);								  // отвечает за анимацию
	glutSpecialFunc(processSpecialKeys);					  // отвечает за нажатие спец. символов (стрелки)

   // Texture1 = LoadTextureAUTO("pringlesNEW.jpeg");
	//Texture2 = LoadTextureAUTO("krishkaNEW.jpg");
	//Texture3 = LoadTextureAUTO("Gelezo.jpg");
	texture = LoadTextureAUTO("earth.jpg");

	glutMainLoop();											  // вход в главный цикл
	return 0;
}