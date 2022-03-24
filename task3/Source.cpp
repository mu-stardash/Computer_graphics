#include <iostream>
#include <glut.h>

#define PI 3.1415927 // пи
#define ANGLE 5     // угол поворота в градусах 

/* Для подсчета косинуса в радианах */
double Cos(double alpha) {
	alpha = cos(PI / 180 * (alpha));
	return alpha;
}

/* Для подсчет синуса в радианах */
double Sin(double alpha) {
	alpha = sin(PI / 180 * (alpha));
	return alpha;
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера. 1-очистка экрана
	glLoadIdentity();									// заменяет тек.матрицу матрицей единичной (в начало коорд)

	gluLookAt(5, 1, 5, 0, 0, 0, 0, 1, 0);    //1,2,3-определяют положение глаза наблюдателя
											 //4,5,6-указывает точку, куда направлен его взгляд
											 //7,8,9-указывает направление вытянутой вверх руки наблюдателя
	glRotatef(90, 0, 0, 1);
	/* Создаем две параллельные окружности, равноудаленные от т.(0, 0, 0) по OY */
	for (int i = 1; i >= -1; i -= 2) {
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0, 0.1, 0.0);
		glVertex3f(0, i, 0); // центр
		for (double k = 0; k <= 360; k += ANGLE) {
			glColor3f(0.5, 0.0, 0.5);
			glVertex3f(Cos(k), i,  Sin(k));
		}
		glEnd();
	}
	    
	glBegin(GL_TRIANGLE_STRIP); // создаем цилиндр 
	for (int j = 0; j <= 360; j += ANGLE) {
		glColor3f(1.0, 0.1, 0.0);
		glVertex3f(Cos(j), 1, Sin(j));
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(Cos(j), -1, Sin(j));
	}
	glEnd(); 

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

int main(int argc, char** argv) {
	glutInit(&argc, argv);                                    // инициализация glut (1-колво аргументов, 2-их описание)
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// определяем режим отображения
															  // 1-буфер глубины, 2-режим двойной буферизации(подходит для анимации)
															  // 3-выбирает цветовое окно
	glutInitWindowPosition(100, 100);                         // (начало координат окна) инициализация окна приложения (х-колво пикс от левой части экрана, у-от верхней
	glutInitWindowSize(1000, 600);                             // размеры окна

	glutCreateWindow("OpenGL");								  // создаем окно с именем

	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(renderScene);							  // вызывается функция всякий раз при перерисовке окна
	glutReshapeFunc(ChangeSize);							  // отвечает за изменения окна

	glutMainLoop();											  // вход в главный цикл
	return 0;
}