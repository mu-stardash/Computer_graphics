//#include <iostream>
//#include <glut.h>
//#include <math.h>                                  // для функции Sin()
//
//float points[45][45][3]; // массив точек сетки нашей "волны"
//
//int wiggle_count = 0;        // счетчик для контроля быстроты развевания флага
//GLfloat hold;                // временно содержит число с плавающей запятой
//
//void Volna() {
//	// пройдемся по оси X
//	for (int x = 0; x < 45; x++)
//	{
//		// пройдемся по оси Y
//		for (int y = 0; y < 45; y++)
//		{
//			// применим волну к нашей сетке
//			points[x][y][0] = float((x / 5.0f) - 4.5f);
//			points[x][y][1] = float((y / 5.0f) - 4.5f);
//			points[x][y][2] = float(sin((((x / 5.0f) * 40.0f) / 360.0f) * 3.141592654 * 2.0f));
//		}
//	}
//}
//
//void renderScene() {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера. 1-очистка экрана
//	glLoadIdentity();									// заменяет тек.матрицу матрицей единичной (в начало коорд)
//
//	gluLookAt(4, 4, 4, 0, 0, 0, 0, 1, 0);    //1,2,3-определяют положение глаза наблюдателя
//											 //4,5,6-указывает точку, куда направлен его взгляд
//											 //7,8,9-указывает направление вытянутой вверх руки наблюдателя

//	GLfloat	xrot=0;			// Вращение X
//	GLfloat	yrot=0;			// Y
//	GLfloat	zrot=0;			// Z
//
//	int x, y;  // переменные циклов
//	 // для разбиения флага на маленькие квадраты
//	float float_x, float_y, float_xb, float_yb;
//	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистить экран и буфер глубины
//
////	glLoadIdentity();                                   // сброс текущей матрицы
////	glTranslatef(0.0f, 0.0f, -12.0f);                     // перенести 17 единиц в глубь экрана
//
//	glRotatef(xrot, 1.0f, 0.0f, 0.0f);                     // вращение по оси X
//	glRotatef(yrot, 0.0f, 1.0f, 0.0f);                     // вращение по оси Y 
//	glRotatef(zrot, 0.0f, 0.0f, 1.0f);                     // вращение по оси Z
//
//	//glPolygonMode(GL_BACK, GL_FILL);       // нижняя (задняя) сторона заполнена
//	//glPolygonMode(GL_FRONT, GL_LINE);      // верхняя (передняя) сторона прорисована линиями
//
//	//Volna();
//
//	glBegin(GL_QUADS);              // начинаем рисовать квадраты
//	
//			glVertex3f(0, 0, 0);
//			glVertex3f(0, 1, 0);
//			glVertex3f(1, 1, -1);
//			glVertex3f(1, 0, -1);
//		glEnd();       
//		xrot += 0.3f;             // увеличить значение переменной вращения по X
//		yrot += 0.2f;             // увеличить значение переменной вращения по Y
//		zrot += 0.4f;             // увеличить значение переменной вращения по Z

//		glutSwapBuffers();
//}
//
//void ChangeSize(int w, int h) {
//	if (h == 0)
//		h = 1;
//
//	float ratio = w * 1.0 / h;   // отношение ширины окна к высоте
//	glMatrixMode(GL_PROJECTION); // матрица проекции (проецирование 3д в 2д)
//	glLoadIdentity();            // заменяет тек.матрицу матрицей единичной (в начало коорд)
//	glViewport(0, 0, w, h);      // область окна, в которой отображается рез работы
//	gluPerspective(45.0f, ratio, 0.1f, 100.0f); // перспективное преобразование (для визуализации 3д обьекта)
//												//3-расстояние от центра проецирования до ближайшей отсек плоскости
//												//4- расстояние от центра проец до задней плоскости отсечения
//	glMatrixMode(GL_MODELVIEW);  // матрица активной камеры. Служит для отрисовки обьемных обьектов сцены
//}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);                                    // инициализация glut (1-колво аргументов, 2-их описание)
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// определяем режим отображения
//															  // 1-буфер глубины, 2-режим двойной буферизации(подходит для анимации)
//															  // 3-выбирает цветовое окно
//	glutInitWindowPosition(100, 100);                         // (начало координат окна) инициализация окна приложения (х-колво пикс от левой части экрана, у-от верхней
//	glutInitWindowSize(1000, 600);                             // размеры окна
//
//	glutCreateWindow("OpenGL");								  // создаем окно с именем
//
//	glEnable(GL_DEPTH_TEST);
//	glutDisplayFunc(renderScene);							  // вызывается функция всякий раз при перерисовке окна
//	glutReshapeFunc(ChangeSize);							  // отвечает за изменения окна
//
//	glutMainLoop();											  // вход в главный цикл
//	return 0;
//}


#include <iostream>
#include <glut.h>
#include <math.h> 

const double PI = 3.14159265358979323846;

//пересчитывает при изменении размеров окна
void ChangeSize(int w, int h) {
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

double p = 0;

void renderScene(void) {

    p += 0.01;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(20, -20/2, 60/2, 7.5, 6.5, 0, 0, 1, 0);


    const double z = 0.0;
    const double STEP_X = 0.1; // Шаг по оси X и горизонтальные размеры треугольников.
    double HEIGHT = 13; // Высота фигуры (смещение по Y).

    for (double x = 0; x <= 15; x += STEP_X) {
        double y1 = sin(x + p) * 0.4;           // Значение y для x.
        double y2 = sin(x + p + STEP_X) * 0.4; // Значение y для (x + STEP_X).

        glBegin(GL_TRIANGLES);
        glColor3f(0.8, 0.2, 0.0);
        glVertex3d(x, y1, z);
        glVertex3d(x, y1 + HEIGHT , z);
        glVertex3d(x + STEP_X, y2 + HEIGHT, z);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.8, 0.2, 0.0);
        glVertex3d(x - 0.5, y1 - 0.5, z);
        glVertex3d(x + STEP_X, y2, z);
        glVertex3d(x + STEP_X, y2 + HEIGHT, z);
        glEnd();
    }

    glutSwapBuffers();
    // по новой отрисовываем
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("OpenGL");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(ChangeSize);
    glEnable(GL_DEPTH_TEST); 
    glutMainLoop();
    return 0;
}