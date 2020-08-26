/*
 *  File : lcd.h
 *  Description : TODO
 * */
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "mem.h"

extern Mem mem;

class LCD{
public:
      GLFWwindow* handle;
      short width;
      short height;
      const char* title;
      glm::vec4 palette[4];
      int setup();
      uint8_t keys;
public:
      short* framebuffer;
      
      LCD(short w, short h, const char* title);
      void clear();
      
      void update();
      bool should_close();
      ~LCD();
};
