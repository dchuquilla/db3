#include <stdio.h>
#include <libpq-fe.h>

int main()
{
PGconn *conn;
PGresult *res;
int i,j;

conn = PQsetdbLogin("localhost","5433",NULL,NULL,"dbejemplos","postgres","");

if (PQstatus(conn) != CONNECTION_BAD)
{
res = PQexec(conn, "select * from usuarios");

if (res != NULL && PGRES_TUPLES_OK == PQresultStatus(res))
{
for (i = PQntuples(res)-1; i >= 0; i--)
{
for (j = PQnfields(res)-1; j >= 0; j--)
printf("%s\t",PQgetvalue(res,i,j));
printf("\n");
}
PQclear(res);
}
}

PQfinish(conn);
return 0;
}
