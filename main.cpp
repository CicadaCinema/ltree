// clang-format off
#include <GL/glew.h>
#include <GL/freeglut.h>
// clang-format on

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>
#include <cstddef>
#include <sstream>
#include <vector>

struct Vertex {
  glm::vec4 pos;
  glm::vec4 color;
};
std::vector<Vertex> verts;
GLuint vbo = 0;
GLuint dlist = 0;

void init() {
  // init geometry
  for (size_t i = 0; i < 10000000; i++) {
    Vertex vert;
    vert.pos = glm::vec4(glm::linearRand(glm::vec3(-1.0f, -1.0f, -1.0f),
                                         glm::vec3(1.0f, 1.0f, 1.0f)),
                         1.0f);
    vert.color = glm::vec4(glm::linearRand(glm::vec3(0.00f, 0.0f, 0.0f),
                                           glm::vec3(1.0f, 1.0f, 1.0f)),
                           1.0f);
    verts.push_back(vert);
  }

  // create VBO
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verts.size(), verts.data(),
               GL_STATIC_DRAW);
}

void keyboard(unsigned char key, int x, int y) {}

void display() {
  // timekeeping
  static std::chrono::steady_clock::time_point prv =
      std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point cur = std::chrono::steady_clock::now();
  const float dt = std::chrono::duration<float>(cur - prv).count();
  prv = cur;

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double w = glutGet(GLUT_WINDOW_WIDTH);
  double h = glutGet(GLUT_WINDOW_HEIGHT);
  gluPerspective(60.0, w / h, 0.1, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2, 2, 2, 0, 0, 0, 0, 0, 1);

  static float angle = 0.0f;
  angle += dt * 6.0f;
  glRotatef(angle, 0, 0, 1);

  // render
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(4, GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, pos));
  glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, color));
  glDrawArrays(GL_POINTS, 0, verts.size());
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // info/frame time output
  std::stringstream msg;
  msg << "Using vertex buffer object";
  msg << std::endl;
  msg << "Frame time: " << (dt * 1000.0f) << " ms";
  glColor3ub(255, 255, 0);
  glWindowPos2i(10, 25);
  glutBitmapString(GLUT_BITMAP_9_BY_15,
                   (unsigned const char *)(msg.str().c_str()));

  glutSwapBuffers();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(600, 600);
  glutCreateWindow("GLUT");
  glewInit();
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(display);
  glutMainLoop();
  return 0;
}
