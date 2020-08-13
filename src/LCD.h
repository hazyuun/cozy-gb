/*
 *  File : lcd.h
 *  Description : TODO
 * */


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class LCD{
      GLFWwindow* m_handle;
      short m_width;
      short m_height;
      const char* m_title;
      short* m_framebuffer;
      glm::vec4 m_palette[4];
      int setup();
public:
      LCD(short w, short h, const char* title);
      inline void set_fb(short* fb){ m_framebuffer = fb;};
      void clear();
      void update(short* framebuffer);
      bool should_close();
      ~LCD();
};
