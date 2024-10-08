//
// Created by shecannotsee on 2022/9/30.
//

#ifndef LIBEVENT_TEST_TEST_SQLITE3_TEST_METHOD_1_H_
#define LIBEVENT_TEST_TEST_SQLITE3_TEST_METHOD_1_H_

#include <string>
#include <iostream>
#include <sqlite3.h>

namespace method1 {

int sql_run_over_display(void *NotUsed, int argc, char **argv, char **azColName){
/*****************************************************************************
    sqlite 每查到一条记录，就调用一次这个回调
    NotUsed是你在 sqlite3_exec 里传入的 void * 参数, 通过para参数，你可以传入一些特殊的指针（比如类指  针、结构指针），然后在这里面强制转换成对应的类型（这里面是void*类型，必须强制转换成你的类型才可用）。然后操作这些数据
    argc是这一条(行)记录有多少个字段 (即这条记录有多少列)
    char ** argv 是个关键值，查出来的数据都保存在这里，它实际上是个1维数组（不要以为是2维数组），每一个元素都是一个 char* 值，是一个字段内容（用字符串来表示，以/0结尾）
    char ** azColName 跟argv是对应的，表示这个字段的字段名称, 也是个1维数组
*****************************************************************************/
  std::cout<<"=============sql_run_over_display=============\n";
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  std::cout<<"=============sql_run_over_display=============\n";
  return 0;
};

void main() {
  sqlite3 *db;
  char* error = NULL;

  /* Open database,and get handle */
  if (sqlite3_open("../test.db", &db)) {
    std::cout << "open db failed, " << sqlite3_errmsg(db) << std::endl;
  } else {
    std::cout << "open db success\n";
  }

  /* run sql */
  std::string sql_insert = "INSERT INTO user (id,name,product_type,create_time,update_time) VALUES (2,'Carry','???','2022-10-31 15:59:00','2022-10-31 15:59:00');";
  std::string sql_select = "select * from user;";

  if (SQLITE_OK != sqlite3_exec(db,sql_select.c_str(),sql_run_over_display,NULL,&error)) {
    std::cout<<"sql failed : "<<error<<std::endl;
    sqlite3_free(error);
  }
  else {
    std::cout<<"sql exec success."<<std::endl;
  }

  /* close db handle */
  sqlite3_close(db);

};
};// namespace method1


#endif //LIBEVENT_TEST_TEST_SQLITE3_TEST_METHOD_1_H_
