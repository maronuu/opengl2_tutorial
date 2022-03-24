#include <stdlib.h>
#include <GL/glut.h>

GLdouble vertex[][3] = {
    {0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {1.0, 1.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 0.0, 1.0},
    {1.0, 1.0, 1.0},
    {0.0, 1.0, 1.0}};

int face[][4] = {
    {0, 1, 2, 3},
    {1, 5, 6, 2},
    {5, 4, 7, 6},
    {4, 0, 3, 7},
    {4, 5, 1, 0},
    {3, 2, 6, 7}};

GLdouble normal[][3] = {
    {0.0, 0.0, -1.0},
    {1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {-1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 1.0, 0.0}};

GLfloat light0pos[] = {0.0, 3.0, 5.0, 1.0};
GLfloat light1pos[] = {5.0, 3.0, 0.0, 1.0};

GLfloat green[] = {0.0, 1.0, 0.0, 1.0};

GLdouble color[][3] = {
    {1.0, 0.0, 0.0}, /* 赤 */
    {0.0, 1.0, 0.0}, /* 緑 */
    {0.0, 0.0, 1.0}, /* 青 */
    {1.0, 1.0, 0.0}, /* 黄 */
    {1.0, 0.0, 1.0}, /* マゼンタ */
    {0.0, 1.0, 1.0}  /* シアン 　*/
};

int edge[][2] = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 0},
    {4, 5},
    {5, 6},
    {6, 7},
    {7, 4},
    {0, 4},
    {1, 5},
    {2, 6},
    {3, 7}};

void idle(void)
{
    glutPostRedisplay();
}

void display(void)
{
    static int r = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
    // rotate
    glRotated((double)r, 0.0, 1.0, 0.0);
    glColor3d(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    // facet: j
    // vertex: i
    for (int j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]);
        for (int i = 0; i < 4; ++i) {
            glVertex3dv(vertex[face[j][i]]);
        }
    }
    glEnd();
    // double buffer
    glutSwapBuffers();

    if (++r >= 360)
    {
        r = 0; // one cycle
    }
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);

    // perspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const double aspect = (double)w / (double)h;
    gluPerspective(30.0, aspect, 1.0, 100.0);

    // model view
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            // start animation
            glutIdleFunc(idle);
        }
        else
        {
            // stop
            glutIdleFunc(0);
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            glutPostRedisplay();
        }
        break;
    default:
        break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
    case 'Q':
    case '\033':
        exit(0);
    default:
        break;
    }
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
    glLightfv(GL_LIGHT1, GL_SPECULAR, green);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}