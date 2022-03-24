#include <iostream>
#include <glut.h>
#include <math.h>

float angleRight = 0, angleUp = 0, angleLeft = 0, angleDown = 0;
// угол поворота (скорость) для планет и спутника
float planet = 0.0;
float satellite = 0.0f;


const float light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f}; // интенсивность фонового света
const float light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f}; // устанавливаем диффузный цвет света (рассеянный свет)
const float light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f}; // интенсивность зеркального света (0-белый)
const float light_position[] = { 0.0f, 0.75f, 0.0f, 1.0f}; // устанавливаем положение точечного (w = 1) источника света

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера. 1-очистка экрана
	glLoadIdentity();									// заменяет тек.матрицу матрицей единичной (в начало коорд)

	gluLookAt(2, 4, 60, 0, 0, 0, 0, 1, 0);    //1,2,3-определяют положение глаза наблюдателя
											 //4,5,6-указывает точку, куда направлен его взгляд
											 //7,8,9-указывает направление вытянутой вверх руки наблюдателя

	glRotatef(angleRight, 0.0f, 1.0f, 0.0f);
	glRotatef(angleUp, 1.0f, 0.0f, 0.0f);
	glRotatef(angleLeft, 0.0f, -1.0f, 0.0f);
	glRotatef(angleDown, -1.0f, 0.0f, 0.0f);


	glEnable(GL_LIGHT0); // разблокировка источника света
	glEnable(GL_LIGHTING); // вкл. расчет освещения
	glEnable(GL_COLOR_MATERIAL); //чтобы работала функция glColor3f

	/* Устанавливаем источнику света параметры */
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// Draw Sun : color yellow	
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(3.0f, 100, 100);

	glEnable(GL_LIGHTING); // разблокировка источника света
	glRotatef(planet, 0.0f, 1.0f, 0.0f);
	
	//Venus : drak yellow	
	glColor3f(0.9f, 0.7f, 0.0f);	
	glTranslatef(-14.0f, 0.60, 0.0f);
	glutSolidSphere(0.75f, 60, 60);

	//Mercury : Red
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(7.0f, 0.0f, 4.0f);
	glutSolidSphere(0.60f, 40, 40);

	//Earth : blue	
	glPushMatrix();
	glColor3f(0.0f, 0.7f, 1.0f);
	glTranslatef(17.0f, 0.0f, 8.0f);
	glutSolidSphere(1.5f, 40, 40);	

	//Moon : gray
	glRotatef(satellite, 0.0f, 1.0f, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslatef(2.0, 0.0f, 2.0f);
	glutSolidSphere(0.5f, 40, 40);
	satellite += 1.0f;
	glPopMatrix();

	//Mars : pink
	glColor3f(1.0f, 0.5f, 0.5f);
	glTranslatef(12.0f, 0.0f, -15.0f);
	glutSolidSphere(0.75f, 40, 40);

	//Jupiter: drak yellow
	glColor3f(0.9f, 0.5f, 0.0f);
	glTranslatef(12.0f, 0.0f, 5.0f);
	glutSolidSphere(1.9f, 40, 40);

	//Saturn: brown
	glColor3f(0.7f, 0.6f, 0.2f);
	glTranslatef(5.0f, 0.0f, -10.0f);
	glutSolidSphere(1.5f, 60, 60);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadric* q = gluNewQuadric(); // диск вокруг сатурна
	glColor3f(0.9f, 0.6f, 0.2f);
	gluDisk(q, 2, 3, 60, 60);
	glPopMatrix();

	planet += 0.2f;

	glutSwapBuffers();
}


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

void processSpecialKeys(int key, int xx, int yy) {
	//float fraction = 0.1f;
	switch (key) {
	case GLUT_KEY_LEFT :
		angleLeft += 5.0f;
		break;
	case GLUT_KEY_RIGHT :
		angleRight += 5.1f;
		break;
	case GLUT_KEY_UP :
		angleUp += 5.1f;
		break;
	case GLUT_KEY_DOWN :
		angleDown += 5.1f;
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);                                    // инициализация glut (1-колво аргументов, 2-их описание)
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// определяем режим отображения
															  // 1-буфер глубины, 2-режим двойной буферизации(подходит для анимации)
															  // 3-выбирает цветовое окно
	glutInitWindowPosition(100, 100);                         // (начало координат окна) инициализация окна приложения (х-колво пикс от левой части экрана, у-от верхней
	glutInitWindowSize(1000, 600);                            // размеры окна

	glutCreateWindow("Solar System");						  // создаем окно с именем

	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(renderScene);							  // вызывается функция всякий раз при перерисовке окна
	glutReshapeFunc(ChangeSize);							  // отвечает за изменения окна
	glutIdleFunc(renderScene);								  // отвечает за анимацию
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();											  // вход в главный цикл
	return 0;
}
