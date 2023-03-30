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

int pg_connect(char **args) {
  if (args[2] == NULL) {
    fprintf(stderr, "pg connect: need dbname\n");
    return 1;
  }
  /* Make a connection to the database */
  conn = PQsetdbLogin("localhost", "5432", NULL, NULL, args[2], "postgres", NULL);
  /* Check to see that the backend connection was successfully made */
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
  /* Declare a PGresult pointer */
  PGresult *res =
      PQexec(conn, "SELECT table_name FROM information_schema.tables WHERE "
                   "table_schema = 'public'");
  /* Check to see that the result is successful */
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "pg list: No data retrieved\n");
    PQclear(res);
    return 1;
  }
  /* print out the rows */
  int rows = PQntuples(res);
  for (int i = 0; i < rows; i++) {
    if (i != 0)
      printf(", ");
    printf("%s ", PQgetvalue(res, i, 0));
  }
  printf("\n");
  return 0;
}

int pg_show(char **args) {
  if (conn == NULL) {
    fprintf(stderr, "pg show: not connected to database\n");
    return 1;
  }
  if (args[2] == NULL) {
    fprintf(stderr, \
    "pg show: need table name\n\
    eg: pg show table_name\n");
    return 1;
  }

  char query[LINE_BUF_SIZE];
  sprintf(query, "SELECT * FROM %s", args[2]);
  PGresult *res = PQexec(conn, query);
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "pg show: No data retrieved\n");
    PQclear(res);
    return 1;
  }
  /*neatly print the entire table*/
  int rows = PQntuples(res);
  int cols = PQnfields(res);

  for (int i = 0; i < cols; i++) {
    if (i != 0)
      printf(", ");
    printf("%s ", PQfname(res, i));
  }
  printf("\n");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (j != 0)
        printf(", ");
      printf("%s ", PQgetvalue(res, i, j));
    }
    printf("\n");
  }
  return 0;
}

int pg_insert(char **args) {

  return 0;
}

int pg_run(char **args) {
  if (conn == NULL) {
    fprintf(stderr, "pg run: not connected to database\n");
    return 1;
  }
  if (args[2] == NULL) {
    fprintf(stderr, \
    "pg run: need command\n\
    eg: pg run \"SELECT * FROM table_name\"\n");
    return 1;
  }
  PGresult *res = PQexec(conn, args[2]);
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "pg run: No data retrieved\n");
    PQclear(res);
    return 1;
  }
  /*neatly print the result*/
  int rows = PQntuples(res);
  int cols = PQnfields(res);

  for (int i = 0; i < cols; i++) {
    if (i != 0)
      printf(", ");
    printf("%s ", PQfname(res, i));
  }
  printf("\n");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (j != 0)
        printf(", ");
      printf("%s ", PQgetvalue(res, i, j));
    }
    printf("\n");
  }
  return 0;
}

int dish_pg(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "pg: need arguments\n\
    possible arguments:\n\
    connect: connect to database\n\
    disconnect: disconnect from database\n\
    list: list all tables\n\
    show: show all contents of a table\n\
    insert: insert into a table\n\
    delete: delete from a table\n\
    run: run a custom command\n");
    return 1;
  }
  if (strcmp(args[1], "connect") == 0) {
    return pg_connect(args);
  }

  else if (strcmp(args[1], "disconnect") == 0) {
    if (conn != NULL) {
      PQfinish(conn);
      return 0;
    }
    fprintf(stderr, "pg disconnect: not connected to database\n");
    return 1;

  } else if (strcmp(args[1], "list") == 0) {
    return pg_list();

  } else if (strcmp(args[1], "show") == 0) {
    return pg_show(args);

  } else if (strcmp(args[1], "insert") == 0) {
    return pg_insert(args);
    
  } else if(strcmp(args[1],"run")==0)
  {
    return pg_run(args);
  }
   else
    fprintf(stderr, "pg: invalid argument\n");

  return 1;
}

#endif