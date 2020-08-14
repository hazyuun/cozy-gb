/*
 *  File : LCD.cpp
 *  Description : TODO
 * */

#include "LCD.h"
LCD::LCD(short w, short h, const char* title)
      :width(w), height(h), title(title)
{
      palette[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
      palette[2] = glm::vec4(0.25f, 0.25f, 0.25f, 1.0f);
      palette[1] = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f);
      palette[0] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
      framebuffer = new short[144 * 160];
      setup();
      /* TODO: error handling */
}
int LCD::setup(){
      if(!glfwInit())
            return 1;
      handle = glfwCreateWindow(width, height, title, NULL, NULL);
      if(!handle)
            return 2;
      glfwMakeContextCurrent(handle);
      glfwSetWindowUserPointer(handle, this);

      if(glewInit() != GLEW_OK)
            return 3;
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      return 0;
}

void LCD::clear(){
      glClear(GL_COLOR_BUFFER_BIT);
}

void LCD::update(){
      GLuint screen;
      GLubyte pixels[144 * 160 * 3];
      for(int k = 0; k < 144 * 160 * 3;){
            pixels[  k  ] = palette[framebuffer[k/3]].r * 255;
            pixels[++k] = palette[framebuffer[k/3]].g * 255;
            pixels[++k] = palette[framebuffer[k/3]].b * 255;
            ++k;
      }
      glGenTextures(1, &screen);
      glBindTexture(GL_TEXTURE_2D, screen);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 160, 144, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);         
      glEnable(GL_TEXTURE_2D);

      glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0); glVertex2f(-1.0f, 1.0f);
            glTexCoord2f(1.0, 0.0); glVertex2f( 1.0f, 1.0f);
            glTexCoord2f(1.0, 1.0); glVertex2f( 1.0f,-1.0f);
            glTexCoord2f(0.0, 1.0); glVertex2f(-1.0f,-1.0f);
      glEnd();

      glfwSwapBuffers(handle);
      glfwPollEvents();
}

bool LCD::should_close(){
      return glfwWindowShouldClose(handle);
}

LCD::~LCD(){

}