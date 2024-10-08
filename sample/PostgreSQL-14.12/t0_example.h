//
// Created by shecannotsee on 23-10-9.
//

#ifndef PGSQL_CLIENT_TEST_T0_EXAMPLE_H
#define PGSQL_CLIENT_TEST_T0_EXAMPLE_H

#include <libpq-fe.h>
#include <netinet/in.h>

namespace t0_example {

static void exit_nicely(PGconn *conn) {
  PQfinish(conn);
  exit(1);
}

void demo1() {
  const char *conninfo;
  PGconn     *conn;
  PGresult   *res;
  int         nFields;
  int         i,
    j;

  /*
   * If the user supplies a parameter on the command line, use it as the
   * conninfo string; otherwise default to setting dbname=postgres and using
   * environment variables or defaults for all other connection parameters.
   */
  conninfo = "dbname = postgres";

  /* Make a connection to the database */
  conn = PQconnectdb(conninfo);

  /* Check to see that the backend connection was successfully made */
  if (PQstatus(conn) != CONNECTION_OK)
  {
    fprintf(stderr, "%s", PQerrorMessage(conn));
    exit_nicely(conn);
  }

  /* Set always-secure search path, so malicious users can't take control. */
  res = PQexec(conn,
               "SELECT pg_catalog.set_config('search_path', '', false)");
  if (PQresultStatus(res) != PGRES_TUPLES_OK)
  {
    fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
    PQclear(res);
    exit_nicely(conn);
  }

  /*
   * Should PQclear PGresult whenever it is no longer needed to avoid memory
   * leaks
   */
  PQclear(res);

  /*
   * Our test case here involves using a cursor, for which we must be inside
   * a transaction block.  We could do the whole thing with a single
   * PQexec() of "select * from pg_database", but that's too trivial to make
   * a good example.
   */

  /* Start a transaction block */
  res = PQexec(conn, "BEGIN");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
    PQclear(res);
    exit_nicely(conn);
  }
  PQclear(res);

  /*
   * Fetch rows from pg_database, the system catalog of databases
   */
  res = PQexec(conn, "DECLARE myportal CURSOR FOR select * from pg_database");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "DECLARE CURSOR failed: %s", PQerrorMessage(conn));
    PQclear(res);
    exit_nicely(conn);
  }
  PQclear(res);

  res = PQexec(conn, "FETCH ALL in myportal");
  if (PQresultStatus(res) != PGRES_TUPLES_OK)
  {
    fprintf(stderr, "FETCH ALL failed: %s", PQerrorMessage(conn));
    PQclear(res);
    exit_nicely(conn);
  }

  /* first, print out the attribute names */
  nFields = PQnfields(res);
  for (i = 0; i < nFields; i++)
    printf("%-15s", PQfname(res, i));
  printf("\n\n");

  /* next, print out the rows */
  for (i = 0; i < PQntuples(res); i++)
  {
    for (j = 0; j < nFields; j++)
      printf("%-15s", PQgetvalue(res, i, j));
    printf("\n");
  }

  PQclear(res);

  /* close the portal ... we don't bother to check for errors ... */
  res = PQexec(conn, "CLOSE myportal");
  PQclear(res);

  /* end the transaction */
  res = PQexec(conn, "END");
  PQclear(res);

  /* close the connection to the database and cleanup */
  PQfinish(conn);
}

/*
 * This function prints a query result that is a binary-format fetch from
 * a table defined as in the comment above.  We split it out because the
 * main() function uses it twice.
 */
static void show_binary_results(PGresult *res) {
  int         i,
    j;
  int         i_fnum,
    t_fnum,
    b_fnum;

  /* Use PQfnumber to avoid assumptions about field order in result */
  i_fnum = PQfnumber(res, "i");
  t_fnum = PQfnumber(res, "t");
  b_fnum = PQfnumber(res, "b");

  for (i = 0; i < PQntuples(res); i++)
  {
    char       *iptr;
    char       *tptr;
    char       *bptr;
    int         blen;
    int         ival;

    /* Get the field values (we ignore possibility they are null!) */
    iptr = PQgetvalue(res, i, i_fnum);
    tptr = PQgetvalue(res, i, t_fnum);
    bptr = PQgetvalue(res, i, b_fnum);

    /*
     * The binary representation of INT4 is in network byte order, which
     * we'd better coerce to the local byte order.
     */
    ival = ntohl(*((uint32_t *) iptr));

    /*
     * The binary representation of TEXT is, well, text, and since libpq
     * was nice enough to append a zero byte to it, it'll work just fine
     * as a C string.
     *
     * The binary representation of BYTEA is a bunch of bytes, which could
     * include embedded nulls so we have to pay attention to field length.
     */
    blen = PQgetlength(res, i, b_fnum);

    printf("tuple %d: got\n", i);
    printf(" i = (%d bytes) %d\n",
           PQgetlength(res, i, i_fnum), ival);
    printf(" t = (%d bytes) '%s'\n",
           PQgetlength(res, i, t_fnum), tptr);
    printf(" b = (%d bytes) ", blen);
    for (j = 0; j < blen; j++)
      printf("\\%03o", bptr[j]);
    printf("\n\n");
  }
}

void demo2() {
  /*
CREATE SCHEMA testlibpq3;
SET search_path = testlibpq3;
SET standard_conforming_strings = ON;
CREATE TABLE test1 (i int4, t text, b bytea);
INSERT INTO test1 values (1, 'joe''s place', '\000\001\002\003\004');
INSERT INTO test1 values (2, 'ho there', '\004\003\002\001\000');
   */
  const char *conninfo;
  PGconn     *conn;
  PGresult   *res;
  const char *paramValues[1];
  int         paramLengths[1];
  int         paramFormats[1];
  uint32_t    binaryIntVal;

  /*
   * If the user supplies a parameter on the command line, use it as the
   * conninfo string; otherwise default to setting dbname=postgres and using
   * environment variables or defaults for all other connection parameters.
   */
  conninfo = "dbname = main_db";

  /* Make a connection to the database */
  conn = PQconnectdb(conninfo);

  /* Check to see that the backend connection was successfully made */
  if (PQstatus(conn) != CONNECTION_OK) {
    fprintf(stderr, "%s", PQerrorMessage(conn));
    exit_nicely(conn);
  }

  /* Set always-secure search path, so malicious users can't take control. */
  res = PQexec(conn, "SET search_path = testlibpq3");
  if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
    PQclear(res);
    exit_nicely(conn);
  }
  PQclear(res);

  /*
   * The point of this program is to illustrate use of PQexecParams() with
   * out-of-line parameters, as well as binary transmission of data.
   *
   * This first example transmits the parameters as text, but receives the
   * results in binary format.  By using out-of-line parameters we can avoid
   * a lot of tedious mucking about with quoting and escaping, even though
   * the data is text.  Notice how we don't have to do anything special with
   * the quote mark in the parameter value.
   */

  /* Here is our out-of-line parameter value */
  paramValues[0] = "joe's place";

  res = PQexecParams(conn,
                     "SELECT * FROM test1 WHERE t = $1",
                     1,       /* one param */
                     NULL,    /* let the backend deduce param type */
                     paramValues,
                     NULL,    /* don't need param lengths since text */
                     NULL,    /* default to all text params */
                     1);      /* ask for binary results */

  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
    PQclear(res);
    exit_nicely(conn);
  }

  show_binary_results(res);

  PQclear(res);

  /*
   * In this second example we transmit an integer parameter in binary form,
   * and again retrieve the results in binary form.
   *
   * Although we tell PQexecParams we are letting the backend deduce
   * parameter type, we really force the decision by casting the parameter
   * symbol in the query text.  This is a good safety measure when sending
   * binary parameters.
   */

  /* Convert integer value "2" to network byte order */
  binaryIntVal = htonl((uint32_t) 2);

  /* Set up parameter arrays for PQexecParams */
  paramValues[0] = (char *) &binaryIntVal;
  paramLengths[0] = sizeof(binaryIntVal);
  paramFormats[0] = 1;        /* binary */

  res = PQexecParams(conn,
                     "SELECT * FROM test1 WHERE i = $1::int4",
                     1,       /* one param */
                     NULL,    /* let the backend deduce param type */
                     paramValues,
                     paramLengths,
                     paramFormats,
                     1);      /* ask for binary results */

  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
    PQclear(res);
    exit_nicely(conn);
  }

  show_binary_results(res);

  PQclear(res);

  /* close the connection to the database and cleanup */
  PQfinish(conn);

}

}

#endif //PGSQL_CLIENT_TEST_T0_EXAMPLE_H
