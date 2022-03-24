/* Курсовой проект по компьютерной графике
 * Название: "3Д часы"
 * Выполнили: студенты группы 22205
 * Ефимова Дарья Сергеевна и Кнауб Денис Иванович
 * 24.12.2020
 */

#include <glut.h>
#include <iostream>
#include <time.h>

using namespace std;

struct tm* curr_time;       // время
int old_sec;                // сохраненное (старое) время в секундах
time_t local_time;          // локальное время 

// Массив римских чисел от 1 до 12
string num1[12] = { "I", "II", "III", "IV", "V", "VI",
					"VII", "VIII", "IX", "X", "XI", "XII" };

// Массив арабских чисел от 1 до 12
string num2[12] = { "1","2","3","4","5","6",
					"7","8","9", "10", "11","12" };
string* num = num1;			 // по умолчанию отображаются римские числа

double eyepos[3] = { 0, 0, 15 };		 // положение взгляда пользователя
float arrow_angle[3] = { 90, 90, 90 };   // положения трех стрелок на часах
GLfloat light1[] = { (GLfloat)250 / 255, (GLfloat)12 / 255, (GLfloat)12 / 255, 1.0f, 1.0f }; // цвет рамки часов
float angleR = 0.0, angleL = 0.0, angleU = 0.0, angleD = 0.0; // для поворота кнопками


/* Рисуем n шаров с радиусом r, расстояние между каждым шаром d*/
void drawBalls(GLfloat r, GLfloat d, int n) {
	GLfloat m = r * 2 + d; // учитываем диаметр шаров при их перемещении
	glPushMatrix();
	for (int k = 0; k < n; k++) {
		glutSolidSphere(r, 15, 15);
		glTranslated(m, 0.0, 0.0);
	}
	glPopMatrix();
}

/* Рисуем цифру, состоящую из шариков */
void drawDigit(int i, GLfloat r, GLfloat d) {
	GLfloat m = 2 * r + d; // учитываем диаметр шаров при их перемещении
	switch (i) {
	case 0: // отрисовываем необходимые цифры от 0 до 9
		glPushMatrix();
		drawBalls(r, d, 4);
		glRotated(-90.0, 0, 0, 1);
		glTranslated(m, 0.0, 0.0);
		drawBalls(r, d, 6);
		glPopMatrix();
		glPushMatrix();
		glTranslated(m, -6.0 * m, 0.0);
		drawBalls(r, d, 3);
		glRotated(90, 0, 0, 1);
		glTranslated(m, -2.0 * m, 0);
		drawBalls(r, d, 6);
		glPopMatrix();
		break;
	case 1:
		glPushMatrix();
		glTranslated(3.0 * m, 0.0, 0.0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glPopMatrix();
		break;
	case 2:
		glPushMatrix();
		drawBalls(r, d, 4);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 4);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 4);
		glPopMatrix();
		glPushMatrix();
		glTranslated(3.0 * m, -m, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 2);
		glTranslated(3.0 * m, -3.0 * m, 0);
		drawBalls(r, d, 2);
		glPopMatrix();
		break;
	case 3:
		glPushMatrix();
		drawBalls(r, d, 4);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 4);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 4);
		glPopMatrix();
		glPushMatrix();
		glTranslated(3.0 * m, -m, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 2);
		glTranslated(3.0 * m, 0, 0);
		drawBalls(r, d, 2);
		glPopMatrix();
		break;
	case 4:
		glPushMatrix();
		glTranslated(3.0 * m, 0, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glPopMatrix();
		glPushMatrix();
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 3);
		glTranslated(3.0 * m, 0, 0);
		glRotated(90, 0, 0, 1);
		drawBalls(r, d, 3);
		glPopMatrix();
		break;
	case 5:
		glPushMatrix();
		drawBalls(r, d, 4);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 4);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 4);
		glPopMatrix();
		glPushMatrix();
		glTranslated(0, -m, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 2);
		glTranslated(3.0 * m, 3.0 * m, 0);
		drawBalls(r, d, 2);
		glPopMatrix();
		break;
	case 6:
		glPushMatrix();
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glRotated(90, 0, 0, 1);
		glTranslated(m, -6.0 * m, 0);
		drawBalls(r, d, 3);
		glPopMatrix();
		glPushMatrix();
		glTranslated(m, 0, 0);
		drawBalls(r, d, 3);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 3);
		glTranslated(2.0 * m, 0, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 3);
		glPopMatrix();
		break;
	case 7:
		glPushMatrix();
		drawBalls(r, d, 3);
		glTranslated(3.0 * m, 0.0, 0.0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glPopMatrix();
		break;
	case 8:
		glPushMatrix();
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glRotated(90, 0, 0, 1);
		glTranslated(m, -6.0 * m, 0);
		drawBalls(r, d, 2);
		glPopMatrix();
		glPushMatrix();
		glTranslated(m, 0, 0);
		drawBalls(r, d, 2);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 2);
		glTranslated(2.0 * m, 3.0 * m, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glPopMatrix();
		break;
	case 9:
		glPushMatrix();
		drawBalls(r, d, 3);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 3);
		glRotated(90, 0, 0, 1);
		glTranslated(m, 0, 0);
		drawBalls(r, d, 2);
		glPopMatrix();
		glPushMatrix();
		glTranslated(3.0 * m, 0, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glPopMatrix();
		break;
	}
}

/* Отрисовка текущего времени */
void drawDigitalTime(int h, int m, int s, GLfloat r, GLfloat d) {
	GLfloat l = r * 2 + d;
	if (h >= 10) // если сейчас больше 10 Часов
		drawDigit(h / 10, r, d); // рисуем первую цифру часов
	glPushMatrix();
	glTranslated(1.8, 0, 0);
	drawDigit(h % 10, r, d); // отрисовка второй цифры часов
	glTranslated(2, 0, 0);
	glPushMatrix();
	glRotated(-90, 0, 0, 1); // поворачиваем для отображения по вертикали
	glTranslated(l, 0, 0);
	drawBalls(r, 3 * l, 2); //  отрисовка первых двоеточий
	glPopMatrix();

	glTranslated(1, 0, 0);
	drawDigit(m / 10, r, d); // отрисовываем первую цифру минут
	glTranslated(1.8, 0, 0);
	drawDigit(m % 10, r, d); // вторую
	glTranslated(2, 0, 0);
	glPushMatrix();
	glRotated(-90, 0, 0, 1);
	glTranslated(l, 0, 0);
	drawBalls(r, 3 * l, 2); // отрисовка вторых двоеточий
	glPopMatrix();

	glTranslated(1, 0, 0);
	drawDigit(s / 10, r, d); // отрисовка первой цифры секунд
	glTranslated(1.8, 0, 0);
	drawDigit(s % 10, r, d); // отрисовка второй цифры секунд
	glPopMatrix();
}

/* Преобразует целочисленное значение цвета в GLfloat */
inline GLfloat doColor(int n) {
	return (GLfloat)n / 255.0;
}

/* Процедура рисования многоугольника (стрелок) */
void drawArrow(int n, GLfloat poly[][3])
{
	int i;
	glBegin(GL_POLYGON);
	for (i = 0; i < n; i++) {
		glVertex3f(poly[i][0], poly[i][1], poly[i][2]);
	}
	glEnd();
}

/* Порядок рисования строк */
void drawString(GLfloat fSize, char* str)
{
	char* p;
	glPushMatrix();
	glScalef(fSize / 500, fSize / 500, fSize / 500); // устанавливаем размер шрифта
	for (p = str; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p); // шрифт цифр
	glPopMatrix();
}

void renderScene() {
	// основные цвета цифр и крепежа
	static GLfloat light2[] = { doColor(348), doColor(91), doColor(86), 1.0f, 1.0f };
	static GLfloat light3[] = { doColor(255), doColor(206), doColor(133), 1.0f, 1.0f };

	static GLfloat r = 0.15f, d = 0.05f; // радиус шара и расстояние
	static int k;

	/* Полигоны, использ. для рисования стрелок и шкалы часов */
	GLfloat arrowSec[4][3] = { {-1,0,0},{0,0.2f,0},{10,0,0}, {0,-0.2f,0} }; // координаты секундной стрелки
	GLfloat arrowMin[4][3] = { {-1,0,0},{0,0.6f,0},{8,0,0},{0,-0.6f,0} };   // координаты минутной стрелки
	GLfloat arrowHour[4][3] = { {-1,0,0},{0,0.8f,0},{5,0,0},{0,-0.8f,0} };   // координаты часовой стрелки
	GLfloat scaleHour[4][3] = { {-2,0.5f,0}, {2,0.5f,0}, {2,-0.5f,0},{-2,-0.5f,0} }; // шкала часовая

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана
	glLoadIdentity();
	gluLookAt(eyepos[0], eyepos[1], eyepos[2],    // местоположение просмотра
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	/* Поворачиваем часы при нажатии на клавиши */
	glRotatef(angleR, 0.0f, 1.0f, 0.0f);
	glRotatef(angleU, 1.0f, 0.0f, 0.0f);
	glRotatef(angleL, 0.0f, -1.0f, 0.0f);
	glRotatef(angleD, -1.0f, 0.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1);    // устанавливаем параметры свету (дифф. свет)
	glEnable(GL_LIGHTING);						 // вкл. расчет освещения
	glEnable(GL_LIGHT0);						 // разблокировка источника света

	glutSolidTorus(0.3, 14, 128, 128);           // рисуем рамку часов
	glDisable(GL_LIGHT1);						 // отключаем освещение
	glDisable(GL_LIGHTING);

	glPushMatrix();				// помещаем в матрицу, чтобы двигались только стрекли
	glRotatef(180, 0, 1, 0);    // разворачиваем часы для корректного отображения
	glPushMatrix();
	glRotatef(arrow_angle[0], 0, 0, 1);           // поворачивает объект (изначально 90 градусов)
	glColor3f(doColor(255), doColor(153), doColor(0));       // устанавливает цвет для полигона
	drawArrow(4, arrowSec);                         // рисует полигон (сек. стрелку) по заданным координатам
	glPopMatrix();

	/* Отрисовка минутной стрелки */
	glPushMatrix();
	glRotatef(arrow_angle[1], 0, 0, 1);
	glColor3f(doColor(220), doColor(20), doColor(60));
	drawArrow(4, arrowMin);
	glPopMatrix();

	/* Отрисовка часовой стрелки*/
	glPushMatrix();
	glRotatef(arrow_angle[2], 0, 0, 1);
	glColor3f(doColor(148), doColor(0), doColor(211));
	drawArrow(4, arrowHour);
	glPopMatrix();
	glPopMatrix();

	/* Рисуем часовую шкалу */
	glColor3f(0.82f, 0.72f, 0.32f);
	for (k = 0; k < 12; k++) {
		glPushMatrix();
		glRotatef(k * 30, 0, 0, 1); // каждые 30 градусов
		glTranslatef(13, 0, 0);
		glScalef(0.2f, 0.1f, 1);    // часовая шкала больше минутной
		glColor3f(1, (GLfloat)169 / 255, (GLfloat)112 / 255);
		drawArrow(4, scaleHour);
		glPopMatrix();
	}

	/* Рисуем минутную шкалу */
	for (k = 0; k < 60; k++) {
		glPushMatrix();
		glRotatef(k * 6, 0, 0, 1);
		glTranslatef(13, 0, 0);
		glScalef(0.2f, 1, 1);
		glColor3f(1, (GLfloat)169 / 255, (GLfloat)112 / 255);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(2, 0, 0);
		glEnd();
		glPopMatrix();
	}

	/* Расставляем цифры по часовой шкале */
	glColor3f(doColor(198), doColor(255), doColor(217));
	for (k = 0; k < 12; k++) {
		glPushMatrix();
		glRotatef(60 - k * 30, 0, 0, 1);
		glTranslatef(11, 0, 0);
		glRotatef(-60 + k * 30, 0, 0, 1);
		drawString(6, (char*)num[k].c_str());
		glPopMatrix();
	}

	glEnable(GL_LIGHTING);						// вкл освещение
	glEnable(GL_LIGHT0);					    // вкл источник света
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light2);   // задаем рассеянное излучение

	/* Рисуем сферу (крепеж стрелок в центре часов) */
	glutSolidSphere(0.3, 32, 32);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light3);	// меняем цвет света

	/* Рисует цифровые часы выше центра */
	glTranslatef(-6.5f, 7, 0);
	drawDigitalTime(curr_time->tm_hour, curr_time->tm_min, curr_time->tm_sec, r, d);

	glutSwapBuffers();
}

/* При изменении окна */
void ChangeSize(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;   // отношение ширины окна к высоте
	glMatrixMode(GL_PROJECTION); // матрица проекции (проецирование 3д в 2д)
	glLoadIdentity();            // заменяет тек.матрицу матрицей единичной (в начало коорд)
	glViewport(0, 0, w, h);      // область окна, в которой отображается рез работы
	gluPerspective(90.0, ratio, 1.0, 256.0); // перспективное преобразование (для визуализации 3д обьекта)
												//3-расстояние от центра проецирования до ближайшей отсек плоскости
												//4- расстояние от центра проец до задней плоскости отсечения
	glMatrixMode(GL_MODELVIEW);  // матрица активной камеры. Служит для отрисовки обьемных обьектов сцены
}

void getting_time(void) {
	time(&local_time);						// получаем текущее каледнарное время в секундах (аргумент также получает это значение)
	curr_time = localtime(&local_time);		// преобразование получ. календарного времени в локальное 

	/* Устанавление правильного угла для стрелок часов */
	if (curr_time->tm_sec != old_sec) {		// если время поменялось
		old_sec = curr_time->tm_sec;	    // старое время = новому
		arrow_angle[0] = 90 + curr_time->tm_sec * 6; // новое значение секундой стрелки
		arrow_angle[1] = 90 + curr_time->tm_min * 6 + curr_time->tm_sec / 10;  // минутной
		arrow_angle[2] = 90 + curr_time->tm_hour * 30 + curr_time->tm_min / 2; // часовой
		renderScene(); // функция для отображения
	}
}

/* Обработка нажатия клавиш */
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'x': // отдаление
	{
		eyepos[2] += 2; break;
		light1[2] += 0.01f; break;
	} break;
	case 'z': // приближение
	{
		eyepos[2] -= 2; break;
		light1[2] -= 0.01f; break;
	} break;
	case 't': // смена цифр на часах
		if (num == num1) {
			num = num2;
		}
		else {
			num = num1;
		} break;
	case 'a': angleL += 5.0; // поворот влево
		break;
	case 'd': angleR += 5.1; // вправо
		break;
	case 'w': angleU += 5.1; // вверх
		break;
	case 's': angleD += 5.1; // вниз
	}
	getting_time(); // новая отрисовка часов
}

/* Устанавливает режим освещения и затенения */
void init() {
	GLfloat light_position[] = { 50, 50, 50.0, 0.0 };    // положение света
	GLfloat mat_specular[] = { 0.8f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);   // передняя грань отражает свет
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); // степень отраженного света
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);   // устанавливаем положения источника света

	glEnable(GL_DEPTH_TEST);    // буфер глубины вкл
	glViewport(0, 0, 600, 600); // glViewport — настройка видового экрана
	glShadeModel(GL_SMOOTH);    // сглаживание
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);									  // инициализация glut (1-колво аргументов, 2-их описание)
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// определяем режим отображения
															  // 1-буфер глубины, 2-режим двойной буферизации(подходит для анимации)
															  // 3-выбирает цветовое окно
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);                         // (начало координат окна) инициализация окна приложения (х-колво пикс от левой части экрана, у-от верхней
	glutCreateWindow("3D CLOCK (Dasha & Denis)");             // создаем окно с именем
	init();													  // инициализация освещения
	glutReshapeFunc(ChangeSize);							  // отвечает за изменения окна
	glutKeyboardFunc(keyboard);								  // обработка клавиш
	glutDisplayFunc(renderScene);							  // вызывается функция всякий раз при перерисовке окна
	glutIdleFunc(getting_time);							      // отвечает за анимацию
	glutMainLoop();										      // вход в главный цикл
	return 0;
}