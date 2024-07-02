//
// Created by shecannotsee on 2022/12/9.
//

#ifndef FLTK1_3_7_TEST_FLTK1_3_7_TEST_METHOD_1_H_
#define FLTK1_3_7_TEST_FLTK1_3_7_TEST_METHOD_1_H_

#include <iostream>
#include <memory>
#include <functional>
#include <thread>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

// 用来创建一个窗口和一个按钮，按钮会有相关的回调函数
namespace method_1 {
void button_click(Fl_Widget *widget) {
  Fl_Button *button = (Fl_Button*) widget;
  std::cout << "Button '" << button->label() << "' was clicked" << std::endl;
};

int main(int argc, char **argv) {
  // 创建窗口
  std::unique_ptr<Fl_Window> window = std::make_unique<Fl_Window>(340, 180);
  // 创建按钮
  std::unique_ptr<Fl_Button> button_ptr = std::make_unique<Fl_Button>(120,70,100,50,"click me!");
  // 定义该按钮的回调函数
  button_ptr->callback(button_click);
  // 显示窗口
  window->show(argc, argv);
  // 运行程序
  return Fl::run();
};

};// namespace method_1

#endif //FLTK1_3_7_TEST_FLTK1_3_7_TEST_METHOD_1_H_
