#include <HMI.h>
#include <iostream>
#include <mem.h>

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);

void GB::HMI::setup(GB::Mem *mem) { m_mem = mem; }

GB::HMI::HMI(short w, short h, const char *title, GB::Mem *mem)
    : width(w), height(h), title(title) {

  palette[3] = glm::vec4(28.0f, 8.0f, 32.0f, 255.0f) / 255.0f;
  palette[2] = glm::vec4(60.0f, 52.0f, 104.0f, 255.0f) / 255.0f;
  palette[1] = glm::vec4(212.0f, 146.0f, 182.0f, 255.0f) / 255.0f;
  palette[0] = glm::vec4(255.0f, 224.0f, 228.0f, 255.0f) / 255.0f;

      

  // palette[3] = glm::vec4(28.0f, 8.0f, 32.0f, 255.0f) / 255.0f;
  // palette[2] = glm::vec4(60.0f, 52.0f, 104.0f, 255.0f) / 255.0f;
  // palette[1] = glm::vec4(112.0f, 176.0f, 192.0f, 255.0f) / 255.0f;
  // palette[0] = glm::vec4(208.0f, 244.0f, 248.0f, 255.0f) / 255.0f;

  /*
  palette[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  palette[2] = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f);
  palette[1] = glm::vec4(0.25f, 0.25f, 0.25f, 1.0f);
  palette[0] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  */
  framebuffer = new short[144 * 160]();
  setup();
  /* TODO: error handling */
}

int GB::HMI::setup() {

  if (!glfwInit())
    return 1;
  handle = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!handle)
    return 2;
  glfwMakeContextCurrent(handle);
  glfwSetWindowUserPointer(handle, this);

  if (glewInit() != GLEW_OK)
    return 3;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glfwSwapInterval(0);
  glfwSetKeyCallback(handle, key_callback);
  glfwSetWindowUserPointer(handle, reinterpret_cast<void *>(this));
  return 0;
}

void GB::HMI::clear() { glClear(GL_COLOR_BUFFER_BIT); }

void GB::HMI::update() {

  GLuint screen;
  GLubyte pixels[144 * 160 * 3] = {0};
  for (long k = 0; k < 144 * 160 * 3;) {
    pixels[k] = palette[framebuffer[k / 3]].r * 255;
    pixels[++k] = palette[framebuffer[k / 3]].g * 255;
    pixels[++k] = palette[framebuffer[k / 3]].b * 255;
    ++k;
  }
  glGenTextures(1, &screen);
  glBindTexture(GL_TEXTURE_2D, screen);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 160, 144, 0, GL_RGB, GL_UNSIGNED_BYTE,
               pixels);
  glEnable(GL_TEXTURE_2D);

  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex2f(-1.0f, 1.0f);
  glTexCoord2f(1.0, 0.0);
  glVertex2f(1.0f, 1.0f);
  glTexCoord2f(1.0, 1.0);
  glVertex2f(1.0f, -1.0f);
  glTexCoord2f(0.0, 1.0);
  glVertex2f(-1.0f, -1.0f);
  glEnd();
  glDeleteTextures(1, &screen);
  glfwSwapBuffers(handle);
  glfwPollEvents();
}

bool GB::HMI::should_close() { return glfwWindowShouldClose(handle); }

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {

  GB::HMI *win = (GB::HMI *)glfwGetWindowUserPointer(window);
  uint8_t temp = 0x0;

  if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_K)
    temp |= (0x01 << 0);
  if (key == GLFW_KEY_LEFT || key == GLFW_KEY_H)
    temp |= (0x01 << 1);
  if (key == GLFW_KEY_UP || key == GLFW_KEY_U)
    temp |= (0x01 << 2);
  if (key == GLFW_KEY_DOWN || key == GLFW_KEY_J)
    temp |= (0x01 << 3);

  if (key == GLFW_KEY_X)
    temp |= (0x10 << 0);
  if (key == GLFW_KEY_C)
    temp |= (0x10 << 1);
  if (key == GLFW_KEY_SPACE)
    temp |= (0x10 << 2);
  if (key == GLFW_KEY_ENTER)
    temp |= (0x10 << 3);

  switch (action) {
  case GLFW_PRESS:
    win->keys |= temp;
    
    _INT_RAISE(win->m_mem, INT_JOYPAD);
    break;

  case GLFW_RELEASE:
    win->keys &= ~temp;
    _INT_ACK(win->m_mem, INT_JOYPAD);
    break;
  };
}

GB::HMI::~HMI() {
  delete[] framebuffer;
  glfwDestroyWindow(handle);
  glfwTerminate();
}
