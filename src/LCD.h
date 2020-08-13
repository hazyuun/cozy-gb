/*
 *  File : lcd.h
 *  Description : TODO
 * */


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class LCD{
      GLFWwindow* handle;
      short width;
      short height;
      const char* title;
      glm::vec4 palette[4];
      int setup();
public:
      LCD(short w, short h, const char* title);
      void clear();
      void update(short* framebuffer);
      bool should_close();
      ~LCD();
};
