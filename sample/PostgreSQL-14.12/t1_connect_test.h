//
// Created by shecannotsee on 23-10-9.
//

#ifndef PGSQL_CLIENT_TEST_T1_CONNECT_TEST_H
#define PGSQL_CLIENT_TEST_T1_CONNECT_TEST_H

#include <libpq-fe.h>
#include <iostream>
#include <netinet/in.h>

namespace t1_connect_test {

static void exit_nicely(PGconn *conn) {
  PQfinish(conn);
  exit(1);
}

void main() {
  // create db name
  std::string db_name = "main_db";
  std::string conninfo = "dbname = " + db_name;
  // make connect
  PGconn* conn = PQconnectdb(conninfo.c_str());/* check connect */ {
    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK) {
      std::cout << "\033[31m" << "connect failed:" << PQerrorMessage(conn) << "\033[0m" << std::endl;
      exit_nicely(conn);
    } else {
      std::cout << "\033[32m" << "connect success" << "\033[0m" << std::endl;
    }
  }

  PGresult* res = nullptr;
  /* 设置始终安全的搜索路径，这样恶意用户就无法控制 */
  res = PQexec(conn,"SET search_path = private");/* check set */ {
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cout << "\033[31m" << "SET failed:" << PQerrorMessage(conn) << "\033[0m" << std::endl;
      PQclear(res);
      exit_nicely(conn);
    } else {
      std::cout << "\033[32m" << "set safe search path success" << "\033[0m" << std::endl;
    }
    /* clear res to avoid memory leaks */
    PQclear(res);
  }

  /* Fetch rows from pg_database, the system catalog of databases */
  res = PQexec(conn, "SELECT name, price FROM private.book");/* check success */ {
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
      fprintf(stderr, "DECLARE CURSOR failed: %s", PQerrorMessage(conn));
      PQclear(res);
      exit_nicely(conn);
    }
    PQclear(res);
  }

  // 获取结果集中的行数
  int numRows = PQntuples(res);

// 遍历结果集并输出书名和价格
  for (int i = 0; i < numRows; i++) {
    const char *name = PQgetvalue(res, i, 0);
    const char *price = PQgetvalue(res, i, 1);
    if (name && price) {
      printf("书名: %s, 价格: %s\n", name, price);
    } else {
      printf("无效的书名或价格\n");
    }
  }

  /* close the connection to the database and cleanup */
  PQfinish(conn);
}


}// namespace t1_connect_test

#endif //PGSQL_CLIENT_TEST_T1_CONNECT_TEST_H
