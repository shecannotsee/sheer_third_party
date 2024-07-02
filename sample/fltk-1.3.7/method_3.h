//
// Created by shecannotsee on 2022/12/9.
//

#ifndef FLTK1_3_7_TEST_FLTK1_3_7_TEST_METHOD_3_H_
#define FLTK1_3_7_TEST_FLTK1_3_7_TEST_METHOD_3_H_

#include <FL/Fl.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <FL/fl_draw.H>

class MyTable : public Fl_Table {
 public:
  // R 表示行索引，C 表示列索引，X 和 Y 表示单元格左上角的坐标，W 和 H 表示单元格的宽度和高度
  void draw_cell(TableContext context, int R = 0, int C = 0, int X = 0, int Y = 0, int W = 0, int H = 0) {
    static char s[40];
    switch (context) {
      case CONTEXT_STARTPAGE:                   // before page is drawn..
        fl_font(FL_HELVETICA, 16);              // 设置绘图操作的字体
        return;
      case CONTEXT_COL_HEADER:// 当前单元格是一个列标题单元格
        fl_push_clip(X, Y, W, H);
        fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, FL_GREEN);// 使用 fl_draw_box() 方法来绘制一个绿色的盒子
        sprintf(s, "%c", 'A' + C);              // 'A', 'B', 'C', etc.
        fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);// 使用 fl_draw_text() 方法来在盒子中绘制列标题
        fl_pop_clip();
        return;
      case CONTEXT_ROW_HEADER:// 当前单元格是一个行标题单元格
        fl_push_clip(X, Y, W, H);
        fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, FL_YELLOW);// 使用 fl_draw_box() 方法来绘制一个黄色的盒子
        sprintf(s, "%03d", R);                  // '001', '002', '003', etc.
        fl_draw(s, X, Y, W, H, FL_ALIGN_RIGHT);
        fl_pop_clip();
        return;
      case CONTEXT_CELL:                        // Draw data in cells
        fl_push_clip(X, Y, W, H);
        // Bg color
        fl_color(R % 2 ? FL_WHITE : 220, 250, 220);
        fl_rectf(X, Y, W, H);
        // Text
        fl_color(FL_BLACK);
        sprintf(s, "%c%03d", 'A' + C, R);
        fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
        fl_pop_clip();
        return;
      default:
        return;
    }
  };

 public:
  MyTable(int X, int Y, int W, int H, const char *L = 0) : Fl_Table(X, Y, W, H, L) {};

  // 设置表格的行和列
  void setCR(int col,int row) {
    cols(col);
    rows(row);
    end();
  };
};

namespace method_3{

int main() {
  Fl_Window *window = new Fl_Window(960, 540);
  MyTable *table = new MyTable(20, 20, 840, 400,"xxxxxx");
  table->setCR(3,4);
  window->end();
  window->show();
  return Fl::run();
}

};// namespace method_3

#endif //FLTK1_3_7_TEST_FLTK1_3_7_TEST_METHOD_3_H_
