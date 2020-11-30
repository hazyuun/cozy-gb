/*
 *  File : LCD.cpp
 *  Description : TODO
 * */

#include "HMI.h"
#include <iostream>
extern bool debug;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

LCD::LCD(short w, short h, const char* title)
      :width(w), height(h), title(title)
{
      palette[3] = glm::vec4(28.0f, 8.0f, 32.0f, 255.0f) / 255.0f;
	 palette[2] = glm::vec4(60.0f, 52.0f, 104.0f, 255.0f)/ 255.0f;

      palette[1] = glm::vec4(112.0f, 176.0f, 192.0f, 255.0f)/ 255.0f;
      palette[0] = glm::vec4(208.0f, 244.0f, 248.0f, 255.0f)/ 255.0f;

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
      glfwSwapInterval(0);
      glfwSetKeyCallback(handle, key_callback);

      return 0;
}

void LCD::clear(){
      glClear(GL_COLOR_BUFFER_BIT);
}

void LCD::update(){

      GLuint screen;
      GLubyte pixels[144 * 160 * 3] = {0};
      for(long k = 0; k < 144 * 160 * 3;){
            pixels[ k ] = palette[framebuffer[k/3]].r * 255;
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
      glDeleteTextures(1, &screen);
      glfwSwapBuffers(handle);
      glfwPollEvents();
}

bool LCD::should_close(){
      return glfwWindowShouldClose(handle);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

      LCD* win = (LCD*) glfwGetWindowUserPointer(window);
      uint8_t temp = 0x0;
	 if(key == GLFW_KEY_D) debug = true;
	 if(key == GLFW_KEY_N) debug = false;

      if(key == GLFW_KEY_RIGHT) temp |= (0x01 << 0);
      if(key == GLFW_KEY_LEFT)  temp |= (0x01 << 1);
      if(key == GLFW_KEY_UP)    temp |= (0x01 << 2);
      if(key == GLFW_KEY_DOWN)  temp |= (0x01 << 3);

      if(key == GLFW_KEY_X)     temp |= (0x10 << 0);
      if(key == GLFW_KEY_C)     temp |= (0x10 << 1);
      if(key == GLFW_KEY_SPACE) temp |= (0x10 << 2);
      if(key == GLFW_KEY_ENTER) temp |= (0x10 << 3);



      switch(action){
      case GLFW_PRESS: win->keys |= temp;
      if((mem.read(INT_ENABLE) & INT_JOYPAD))
            INT_RAISE(INT_JOYPAD);
      break;

      case GLFW_RELEASE: win->keys &= ~temp; break;
      };

}

LCD::~LCD(){
      delete[] framebuffer;
      glfwDestroyWindow(handle);
      glfwTerminate();

}
