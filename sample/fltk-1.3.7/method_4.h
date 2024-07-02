//
// Created by shecannotsee on 2022/12/23.
//

#ifndef FLTK1_3_7_TEST_FLTK1_3_7_TEST_METHOD_4_H_
#define FLTK1_3_7_TEST_FLTK1_3_7_TEST_METHOD_4_H_

#include <FL/Fl.H>
#include <FL/gl.h>
#include <FL/Fl_Gl_Window.H>

namespace method_4{

class MyWindow : public Fl_Gl_Window {
  void draw() {

  };
  int handle(int) {

  };

 public:
  MyWindow(int X, int Y, int W, int H, const char *L)
      : Fl_Gl_Window(X, Y, W, H, L) {}
};

int main(int argc, char **argv) {
  MyWindow window(400, 400, 400, 300, "fltk openGl test");
  window.show(argc, argv);
  return Fl::run();
};


};// namespace method_4

#endif //FLTK1_3_7_TEST_FLTK1_3_7_TEST_METHOD_4_H_
