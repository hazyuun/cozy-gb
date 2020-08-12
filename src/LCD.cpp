/*
 *  File : LCD.cpp
 *  Description : TODO
 * */

#include "LCD.h"
LCD::LCD(short w, short h, const char* title)
      :m_width(w), m_height(h), m_title(title)
{
      setup();
      /* TODO: error handling */
}
int LCD::setup(){
      if(!glfwInit())
            return 1;
      m_handle = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
      if(!m_handle)
            return 2;
      glfwMakeContextCurrent(m_handle);
      glfwSetWindowUserPointer(m_handle, this);

      if(glewInit() != GLEW_OK)
            return 3;

      return 0;
}

void LCD::clear(){
      glClear(GL_COLOR_BUFFER_BIT);
}
void LCD::update(){
      glfwSwapBuffers(m_handle);
      glfwPollEvents();
}
bool LCD::should_close(){
      return glfwWindowShouldClose(m_handle);
}
LCD::~LCD(){

}