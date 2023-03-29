#include "postgres.h"
#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>
#ifdef POSTGRES

static PGconn *conn;

int pg_connect(char *args) {
  if (args == NULL) {
    fprintf(stderr, "pg connect: need dbname\n");
    return 1;
  }
  conn = PQsetdbLogin("localhost", "5432", NULL, NULL, args, "postgres", NULL);
  if (PQstatus(conn) == CONNECTION_BAD) {
    fprintf(stderr, "pg connect: Connection to database failed: %s",
            PQerrorMessage(conn));
    return 1;
  }
  return 0;
}
int pg_list() {
  if (conn == NULL) {
    fprintf(stderr, "pg list: not connected to database\n");
    return 1;
  }
  PGresult *res =
      PQexec(conn, "SELECT table_name FROM information_schema.tables WHERE "
                   "table_schema = 'public'");
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "pg list: No data retrieved\n");
    PQclear(res);
    return 1;
  }
  int rows = PQntuples(res);
  for (int i = 0; i < rows; i++) {
    if (i != 0)
      printf(", ");
    printf("%s ", PQgetvalue(res, i, 0));
  }
  printf("\n");
  return 0;
}

int pg_show(char *args) {
  if (conn == NULL) {
    fprintf(stderr, "pg show: not connected to database\n");
    return 1;
  }
  if (args == NULL) {
    fprintf(stderr, "pg show: need table name\n");
    return 1;
  }
  char *query = malloc(100);
  sprintf(query, "SELECT * FROM %s", args);
  PGresult *res = PQexec(conn, query);
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "pg show: No data retrieved\n");
    PQclear(res);
    return 1;
  }
  int rows = PQntuples(res);
  int cols = PQnfields(res);

  //print header
  for (int i = 0; i < cols; i++) {
    if (i != 0)
      printf(", ");
    printf("%s ", PQfname(res, i));
  }
  printf("\n");
  //print whole table
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (j != 0)
        printf(", ");
      printf("%s ", PQgetvalue(res, i, j));
    }
    printf("\n");
  }


  printf("\n");
  free(query);
  return 0;
}

int dish_pg(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "pg: need arguments\n\
    possible arguments:\n\
    connect: connect to database\n\
    list: list all tables\n\
    show: show all contents of a table\n");
    return 1;
  }
  if (strcmp(args[1], "connect") == 0) {
    pg_connect(args[2]);
  }
  if (strcmp(args[1], "list") == 0) {
    pg_list();
  }
  if (strcmp(args[1], "show") == 0) {
    pg_show(args[2]);
  }

  return 0;
}

#endif