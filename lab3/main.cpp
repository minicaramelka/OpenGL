#include <iostream>
#include <time.h>
#include <cstdlib>
#include <GL/glut.h>
#include <math.h>

using namespace std;

#define WIN_HEIGHT 750
#define WIN_WIDTH 750

GLfloat dx_rotation = 0.5;
GLfloat dy_rotation = 0;
GLfloat light_pos[] = { 0, 0, 0, 1 };
bool light_on = true;
GLfloat sun_rotation = 0;
GLfloat dx_sun_rotation = 1;
int sun_mode = 1;
GLint opened = 0;

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  Light and sphere
    glLoadIdentity();
    glTranslatef(0, 0, -25);
    glRotatef((sun_rotation), 0, 1, 0);
    glTranslatef(0, 0, -20);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLUquadricObj* quadObj;
    quadObj = gluNewQuadric();
    glColor3d(1, 0, 0);
    gluQuadricDrawStyle(quadObj, GLU_LINE);
    gluSphere(quadObj, 2, 20, 10);

    //  Oct
    glLoadIdentity();
    glTranslatef(0, 0, -20);

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 1.0, 0.0);  /// 123 - green
    glNormal3d(-1, -1, 1);
    //  (1, 1, -1)
    glVertex3f(0 + opened, 10 + opened, 0 - opened);
    glVertex3f(0 + opened, 0 + opened, -10 - opened);
    glVertex3f(10 + opened, 0 + opened, 0 - opened);

    glColor3f(1.0, 0.0, 0.0);  ///134 - red
    glNormal3d(-1, -1, -1);
    //  (1, 1, 1)
    glVertex3f(0 + opened, 10 + opened, 0 + opened);
    glVertex3f(10 + opened, 0 + opened, 0 + opened);
    glVertex3f(0 + opened, 0 + opened, 10 + opened);

    glColor3f(0.0, 0.0, 1.0);  /// 145 - blue
    glNormal3d(1, -1, -1);
    //  (-1, 1, 1)
    glVertex3f(0 - opened, 10 + opened, 0 + opened);
    glVertex3f(0 - opened, 0 + opened, 10 + opened);
    glVertex3f(-10 - opened, 0 + opened, 0 + opened);

    glColor3f(0.0, 1.0, 1.0);  /// 236 - light blue
    glNormal3d(1, -1, -1);
    //  (1, -1, -1)
    glVertex3f(0 + opened, 0 - opened, -10 - opened);
    glVertex3f(10 + opened, 0 - opened, 0 - opened);
    glVertex3f(0 + opened, -10 - opened, 0 - opened);

    glColor3f(1.0, 1.0, 0.0);  /// 346 - yellow
    glNormal3d(-1, 1, -1);
    // (1, -1, 1)
    glVertex3f(0 + opened, 0 - opened, 10 + opened);
    glVertex3f(10 + opened, 0 - opened, 0 + opened);
    glVertex3f(0 + opened, -10 - opened, 0 + opened);

    glColor3f(1.0, 0.0, 1.0);  /// 456 - purple
    glNormal3d(-1, -1, 1);
    //  (-1, -1, 1)
    glVertex3f(0 - opened, 0 - opened, 10 + opened);
    glVertex3f(-10 - opened, 0 - opened, 0 + opened);
    glVertex3f(0 - opened, -10 - opened, 0 + opened);

    glColor3f(1.0, 0.5, 0.0);  /// 125 - orange
    glNormal3d(-1, 1, -1);
    //  (-1, 1, -1)
    glVertex3f(0 - opened, 10 + opened, 0 - opened);
    glVertex3f(0 - opened, 0 + opened, -10 - opened);
    glVertex3f(-10 - opened, 0 + opened, 0 - opened);

    glColor3f(1.0, 0.0, 0.0);  /// 256 - rgb
    glNormal3d(1, 1, 1);
    //  (-1, -1, -1)
    glVertex3f(0 - opened, 0 - opened, -10 - opened);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-10 - opened, 0 - opened, 0 - opened);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0 - opened, -10 - opened, 0 - opened);

    glEnd();

    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
    if (h == 0)
        h = 1;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (GLdouble)w / h, 1, 50);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, (GLdouble)w, (GLdouble)h);

    Draw();
}

void TimerFunction(int value) {
    glutPostRedisplay();
    glutTimerFunc(10, TimerFunction, 1);
    sun_rotation += dx_sun_rotation;
}

void glutNormalKeys(unsigned char key, int x, int y) {
    switch (key) {
    case 'e':
        if (!opened)
            opened = 2;
        else
            opened = 0;
        break;
    case 'r':
        if (sun_mode >= 0)
        {
            sun_mode--;
            dx_sun_rotation--;
        }
        else
        {
            sun_mode = 1;
            dx_sun_rotation = 1;
        }
        break;
    case 'z':
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
    cout << "e - open octahedron\nr - change sun mode\nz - exit\n" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Octahedron");
    glutDisplayFunc(Draw);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(5, TimerFunction, 0.5);
    glutKeyboardFunc(glutNormalKeys);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}