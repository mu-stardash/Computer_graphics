#include <iostream>
#include <glut.h>
#include "FreeImage.h"

const double PI = 3.141592653589793;
GLuint earth; // �������� �����
GLuint space; // �������� �������
GLuint sea;   // �������� �������

/* �������� ����������� */
FIBITMAP* loadImage(const char* filename)
{
    FIBITMAP* dib = nullptr;
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filename);// ���������� ��� ������������ ����� ������ �� ��� ����������

    dib = FreeImage_Load(fif, filename, JPEG_DEFAULT); // ��������� � ������ ����������� ���� � �����.
    /* ���������, ������� �� ������ �������� */
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
    GLuint tex = 0;    // ������������� ��������
    int x, y;		   // �������
    int height, width; // ������, ������

    RGBQUAD rgbquad;
    FREE_IMAGE_TYPE type;
    //BITMAPINFOHEADER* header;
    BYTE* bits = nullptr;
    bits = FreeImage_GetBits(dib);		// ����������� ���� �����������

    type = FreeImage_GetImageType(dib); // ���
    height = FreeImage_GetHeight(dib);  // ������
    width = FreeImage_GetWidth(dib);    // ������

    //header = FreeImage_GetInfoHeader(dib); // ��� ��������� �������� ���������� � �������� � �������� ������� ������������ �� ���������� ���������� ����������� (DIB)

    /* �������� ������� �����������  � ���������� � texels */
    int scanLineWidh = ((3 * width) % 4 == 0) ? 3 * width : ((3 * width) / 4) * 4 + 4;
    unsigned char* texels = (GLubyte*)calloc(height * scanLineWidh, sizeof(GLubyte)); // ����������� ������ �����������
    for (x = 0; x < width; x++)
        for (y = 0; y < height; y++)
        {
            FreeImage_GetPixelColor(dib, x, y, &rgbquad);
            texels[(y * scanLineWidh + 3 * x) + 0] = ((GLubyte*)&rgbquad)[2]; // RED
            texels[(y * scanLineWidh + 3 * x) + 1] = ((GLubyte*)&rgbquad)[1]; // BLUE
            texels[(y * scanLineWidh + 3 * x) + 2] = ((GLubyte*)&rgbquad)[0]; // GREEN
        }
    glGenTextures(1, &tex);			   // ��������� ����� �������� (1 -����������, &tex - ���� ��������� ��������)
    glBindTexture(GL_TEXTURE_2D, tex); // ���������

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // ��������� ���������� �����������, ���� ����� �� �������� ������ �� ��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // �� �Y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // ����������, ����� ��������������� ����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // ����� ���������������� �����

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, // ��������� �������� 
        width, height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, texels);

    free(texels); // ����������� ���������� ������
    return tex;
}

GLuint LoadTextureAUTO(std::string filename)
{
    GLuint tex;								     // ������������� ��������
    FIBITMAP* dib = loadImage(filename.c_str()); // ��������� ����������� (����� �������)
    tex = loadTexture(dib);					     // ��������� �������� (����� �������)
    FreeImage_Unload(dib);						 // ���������
    return tex;
}

void renderScene() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5, 2, 10, 5, 0, 0, 0, 1, 0);

    /* ������ ������ ������ (���) � ����������� �� ��� �������� ���� */
    glBindTexture(GL_TEXTURE_2D, sea);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);                     glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 1);                     glVertex3f(0.0f, 0.0f, 10.0f);
    glTexCoord2f(1, 1);                     glVertex3f(10.0f, 0.0f, 10.0f);
    glTexCoord2f(1, 0);                     glVertex3f(10.0f, 0.0f, 0.0f);
    glEnd();

    /* �������� �������� ����� */
    glBindTexture(GL_TEXTURE_2D, space); // �������� ������� ������ ��� ������ (������ ������)
    /* ������ ������ */
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);                     glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 1);                     glVertex3f(0.0f, 3.0f, 0.0f);
    glTexCoord2f(1, 1);                     glVertex3f(10.0f, 3.0f, 0.0f);
    glTexCoord2f(1, 0);                     glVertex3f(10.0f, 0.0f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D); // ��������� ���������������, ����� ������ ����� ���� ��� �������
 
    /* ������ ������ */
    glBegin(GL_QUADS);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 3.0f, 0.0f);
    glVertex3f(10.0f, 3.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glEnd();

    /* �������� ������ */
    glBegin(GL_QUADS);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 3.0f, 10.0f);
    glVertex3f(0.0f, 3.0f, 10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

    /* ������ ����� */
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 3.0f, 0.0f);
    glVertex3f(0.0f, 3.0f, 10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

    /* ������� ������ (�������) */
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 3.0f, 0.0f);
    glVertex3f(10.0f, 3.0f, 0.0f);
    glVertex3f(10.0f, 3.0f, 10.0f);
    glVertex3f(0.0f, 3.0f, 10.0f);
    glEnd();

    /* ������ ������� */
    glTranslatef(3, 1.5, 2);
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= 360; j += 1) {
        glVertex3f(cos(j * PI / 180), 1, sin(j * PI / 180)); 
        glVertex3f(cos(j * PI / 180), -1, sin(j * PI / 180));
    }
    glEnd();
 
    /* ������ ����� */
    glTranslatef(4, 0, 1);                // ���������� ������
    glEnable(GL_TEXTURE_2D);              // �������� ���������������
    glBindTexture(GL_TEXTURE_2D, earth);  // ����� ����������� �������� �����
    double r = 1; // ������
    int nx = 30;  // ���-�� ����������� �����. �� (��� ������������ �����������)
    int ny = 30;  // ���-�� ����������� �����. �Y (��� ������������ �����������)
    double i, ix, iy;
    double x, y, z;
    glRotatef(90, 1, 0, 0); // ������������
    glBegin(GL_QUAD_STRIP); 
    for (iy = 0; iy <= ny; ++iy) // �� y
    {
        for (ix = 0; ix <= nx; ++ix) 
        {
            /* �������� �� ��� ����������� �� �������� */
            x = r * sin(iy * PI / ny) * cos(2 * ix * PI / nx); // x = r*sina*cosa 
            y = r * sin(iy * PI / ny) * sin(2 * ix * PI / nx); // y = r*sina*sinb
            z = r * cos(iy * PI / ny);                         // z = rcosa
            /* ������� ���������� �� ������ */
            glNormal3f(x, y, z);
            glTexCoord2f((double)ix / (double)nx, (double)iy / (double)ny);
            glVertex3f(x, y, z); // ������������
       
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

/* ��� ��������� ������� ���� */
void ChangeSize(int w, int h) {
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;   // ��������� ������ ���� � ������
    glMatrixMode(GL_PROJECTION); // ������� �������� (������������� 3� � 2�)
    glLoadIdentity();            // �������� ���.������� �������� ��������� (� ������ �����)
    glViewport(0, 0, w, h);      // ������� ����, � ������� ������������ ��� ������
    gluPerspective(45.0f, ratio, 0.1f, 100.0f); // ������������� �������������� (��� ������������ 3� �������)
                                                //3-���������� �� ������ ������������� �� ��������� ����� ���������
                                                //4- ���������� �� ������ ����� �� ������ ��������� ���������
    glMatrixMode(GL_MODELVIEW);  // ������� �������� ������. ������ ��� ��������� �������� �������� �����
}



void init2() {
    GLfloat light_ambient[] = { 0.7, 0.7, 0.7, 1.0 }; // ������������� �������� ����� (���� �����)
    GLfloat light_diffuse[] = { 0.4, 0.4, 0.4, 1.0 }; // ������������� ��������� ���� ����� (���������� ����) (���������� ���� �� �������)
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };// ������������� ����������� ����� (0-�����)
    GLfloat light_position[] = { -4.0, 1.0, -8.0, 1.0 }; // ������������� ��������� ��������� (w = 1 - ��������, 0 -������ (�����������))) ��������� �����

    glMaterialfv(GL_FRONT, GL_SPECULAR, light_diffuse);

    /* ������������� ��������� ����� ��������� */
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_specular);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);                // ���. ������ ���������
    glEnable(GL_LIGHT0);                  // ������������� ��������� �����
  //  glEnable(GL_DEPTH_TEST);              // ����� �������
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);                                    // ������������� glut (1-����� ����������, 2-�� ��������)
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// ���������� ����� �����������
                                                              // 1-����� �������, 2-����� ������� �����������(�������� ��� ��������)
                                                              // 3-�������� �������� ����
    glutInitWindowPosition(100, 100);                         // (������ ��������� ����) ������������� ���� ���������� (�-����� ���� �� ����� ����� ������, �-�� �������
    glutInitWindowSize(1000, 600);                            // ������� ����

    glutCreateWindow("�������������� ���������");			      // ������� ���� � ������

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    init2();                                                  // ������������� ���������
    glutDisplayFunc(renderScene);							  // ���������� ������� ������ ��� ��� ����������� ����
    glutReshapeFunc(ChangeSize);							  // �������� �� ��������� ����
    glutIdleFunc(renderScene);								  // �������� �� ��������

    /* ��������� �������� */
    space = LoadTextureAUTO("SpaceNEW.jpg");
    sea = LoadTextureAUTO("SeaNEW.jpg");
    earth = LoadTextureAUTO("earth.jpg");

    glutMainLoop();											  // ���� � ������� ����
    return 0;
}