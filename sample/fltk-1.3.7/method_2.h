//
// Created by shecannotsee on 2022/12/9.
//

#ifndef FLTK1_3_7_TEST_FLTK1_3_7_TEST_METHOD_2_H_
#define FLTK1_3_7_TEST_FLTK1_3_7_TEST_METHOD_2_H_

#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>

// 该命名空间里实现了一个输入和回显框，通过按钮将输入框的数据在回显框中进行展示
namespace method_2 {

struct i_o {
  i_o(){
    Fl_Input_ptr= nullptr;
    Fl_Output_ptr = nullptr;
  }
  // 当程序执行到 Fl::run() 方法时，FLTK 库会调用每一个 widget 的析构函数，此时程序会崩溃。
//  ~i_o() {
//    Fl_Input_ptr= nullptr;
//    Fl_Output_ptr = nullptr;
//  }
  void* Fl_Input_ptr;
  void* Fl_Output_ptr;
};

void button_callback(Fl_Widget* widget,void* p) {
  i_o* pp = (i_o*)p;
  std::cout<<"has click"<<std::endl;
  Fl_Input* input = (Fl_Input*)(pp->Fl_Input_ptr);
  Fl_Output* output = (Fl_Output*)(pp->Fl_Output_ptr);
  std::cout<<input->value()<<std::endl;
  output->value(input->value());
  Fl::check();
};

int main(int argc, char **argv) {
  // 创建窗口
  std::unique_ptr<Fl_Window> window = std::make_unique<Fl_Window>(340, 180);
  // 创建输入框
  std::unique_ptr<Fl_Input> input_ptr = std::make_unique<Fl_Input>(10, 10, 100, 30);/* 加入到窗口中 */ {
    window->add(input_ptr.get());
  };
  // 创建回显框
  std::unique_ptr<Fl_Output> output_prt = std::make_unique<Fl_Output>(10,100,100,30);/**/ {
    window->add(output_prt.get());
  };
  // 创建按钮
  std::unique_ptr<Fl_Button> button_ptr = std::make_unique<Fl_Button>(120,70,100,50,"click me!");/**/ {
    i_o p;
    p.Fl_Input_ptr  = (void*)input_ptr.get();
    p.Fl_Output_ptr = (void*)output_prt.get();
    button_ptr->callback(button_callback,&p);
    window->add(button_ptr.get());
  }
  // 显示窗口
  window->show(argc, argv);
  // 运行程序
  return Fl::run();
};

};// namespace method_2

#endif //FLTK1_3_7_TEST_FLTK1_3_7_TEST_METHOD_2_H_
