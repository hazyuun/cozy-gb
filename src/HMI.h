
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace GB {

class Mem;

class HMI {
public:
  GLFWwindow *handle;
  short width;
  short height;
  const char *title;
  glm::vec4 palette[4];
  int setup();
  uint8_t keys;
  uint8_t m_joypad_reg = 0xFF;
  GB::Mem *m_mem;

public:
  short *framebuffer;

  HMI(short w, short h, const char *title, GB::Mem *mem);
  void setup(GB::Mem *mem);
  void clear();

  inline uint8_t get_joypad_reg() const {
    return m_joypad_reg;
  };
  inline void set_joypad_reg(uint8_t value){
    m_joypad_reg = value;
  }

  void update();
  bool should_close();
  friend void key_callback(GLFWwindow *window, int key, int scancode,
                           int action, int mods);
  ~HMI();
};
}