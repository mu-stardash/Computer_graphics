#include <iostream>
#include <glut.h>

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера. 1-очистка экрана
	glLoadIdentity();									// заменяет тек.матрицу матрицей единичной (в начало коорд)

	gluLookAt(-15, -15, -15, 0, 0, 0, 0, 1, 0); //1,2,3-определяют положение глаза наблюдателя
											 //4,5,6-указывает точку, куда направлен его взгляд
											 //7,8,9-указывает направление вытянутой вверх руки наблюдателя
	

	//glRotatef(-85, 1, 0, 0);

	glBegin(GL_QUADS); // left
	glVertex3f(-1.0*4, 1.0*4, 1.0*4);
	glColor3f(0, 1, 0);
	glVertex3f(-1.0*4, 1.0*4, -1.0*4);
	glColor3f(0, 1, 0);
	glVertex3f(-1.0*4, -1.0*4, -1.0*4);
	glColor3f(0, 1, 0);
	glVertex3f(-1.0*4, -1.0*4, 1.0*4);
	glColor3f(0, 1, 0);
	glEnd();

	glBegin(GL_QUADS); // right
	glVertex3f(1.0*4, 1.0*4, 1.0*4);
	glColor3f(1, 0, 0);
	glVertex3f(1.0*4, -1.0*4, 1.0*4);
	glColor3f(1, 0, 0);
	glVertex3f(1.0*4, -1.0*4, -1.0*4);
	glColor3f(1, 0, 0);
	glVertex3f(1.0*4, 1.0*4, -1.0*4);
	glColor3f(1, 0, 0);
	glEnd();

	glBegin(GL_QUADS); // down
	glVertex3f(1.0*4, -1.0*4, 1.0*4);
	glColor3f(0, 0, 1);
	glVertex3f(-1.0*4, -1.0*4, 1.0*4);
	glColor3f(0, 0, 1);
	glVertex3f(-1.0*4, -1.0*4, -1.0*4);
	glColor3f(0, 0, 1);
	glVertex3f(1.0*4, -1.0*4, -1.0*4);
	glColor3f(0, 0, 1);
	glEnd();

	glBegin(GL_QUADS); // up
	glVertex3f(1.0*4, 1.0*4, 1.0*4);
	glColor3f(1, 0, 1);
	glVertex3f(1.0*4, 1.0*4, -1.0*4);
	glColor3f(1, 0, 1);
	glVertex3f(-1.0*4, 1.0*4, -1.0*4);
	glColor3f(1, 0, 1);
	glVertex3f(-1.0*4, 1.0*4, 1.0*4);
	glColor3f(1, 0, 1);
	glEnd();

	glBegin(GL_QUADS); // front
	glVertex3f(1.0*4, 1.0*4, 1.0*4);
	glColor3f(1, 1, 0);
	glVertex3f(-1.0*4, 1.0*4, 1.0*4);
	glColor3f(1, 1, 0);
	glVertex3f(-1.0*4, -1.0*4, 1.0*4);
	glColor3f(1, 1, 0);
	glVertex3f(1.0*4, -1.0*4, 1.0*4);
	glColor3f(1, 1, 0);
	glEnd();

	glBegin(GL_QUADS); // back
	glVertex3f(1.0*4, 1.0*4, -1.0*4);
	glColor3f(0, 1, 1);
	glVertex3f(1.0*4, -1.0*4, -1.0*4);
	glColor3f(0, 1, 1);
	glVertex3f(-1.0*4, -1.0*4, -1.0*4);
	glColor3f(0, 1, 1);
	glVertex3f(-1.0*4, 1.0*4, -1.0*4);
	glColor3f(0, 1, 1);
	glEnd();
	
	glutSwapBuffers(); // обменивает буфера, отображая окно целиком, после того как оно сформир-но
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