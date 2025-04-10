#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

const int WIDTH = 800, HEIGHT = 600;

float x = 100.0f, y = 100.0f;
float radius = 30.0f;
float dx = 2.0f, dy = 2.0f;

float red = 1.0f, green = 0.0f, blue = 0.0f;

void changeColor() {
    red = static_cast<float>(rand()) / RAND_MAX;
    green = static_cast<float>(rand()) / RAND_MAX;
    blue = static_cast<float>(rand()) / RAND_MAX;
}

void drawPolygon(float cx, float cy, float r, int sides) {
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= sides; i++) {
            float angle = 2.0f * 3.1415926f * i / sides;
            float px = r * cosf(angle);
            float py = r * sinf(angle);
            glVertex2f(cx + px, cy + py);
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(red, green, blue);
    drawPolygon(x, y, radius, 6); // Changed from 5 to 6 for hexagon
    glutSwapBuffers();
}

void update(int value) {
    x += dx;
    y += dy;

    if (x + radius > WIDTH || x - radius < 0) {
        dx = -dx;
        changeColor();
    }
    if (y + radius > HEIGHT || y - radius < 0) {
        dy = -dy;
        changeColor();
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int, int) {
    if (key == '+') {
        dx *= 1.2f; dy *= 1.2f;
    } else if (key == '-') {
        dx *= 0.8f; dy *= 0.8f;
        if (fabs(dx) < 0.1f) dx = (dx < 0 ? -0.1f : 0.1f);
        if (fabs(dy) < 0.1f) dy = (dy < 0 ? -0.1f : 0.1f);
    } else if (key == 'a') {
        radius += 5.0f;
        if (radius > 200.0f) radius = 200.0f;
    } else if (key == 's') {
        radius -= 5.0f;
        if (radius < 5.0f) radius = 5.0f;
    }
}

void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    srand(static_cast<unsigned>(time(0)));
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Bouncing Hexagon - OpenGL"); // Updated window title

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
