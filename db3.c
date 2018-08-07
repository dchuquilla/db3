#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <libpq-fe.h>
#include <string.h>

void insert_propietarios(PGconn *conn, char nombre[55], char apellido[55], char email[55], char celular[55], char terminos[10]);
void listar_propietarios(PGconn *conn);
void select_propietarios(PGconn *conn, int propietario_id);

int main() {
  PGconn *conn;
  PGresult *res;
  int i, j, n, opcion, input_character;

  // Variables propietario
  int opcion_propietarios;
  int id_propietario;
  char nombre[55];
  char apellido[55];
  char email[55];
  char celular[55];
  char terminos_txt;
  char terminos[10];

  conn = PQsetdbLogin("localhost","5433",NULL,NULL,"automan_development","postgres","");

  if (PQstatus(conn) == CONNECTION_BAD) {
    printf("\nError general en la conexión");
    return 0;
  }

  do{
    system("clear");
    printf( "BIENVENIDO AL PROGAMA DE PRUEBAS DE AUTOMAN" );
    printf( "\n   1. Probar propietarios.");
    printf( "\n   2. Probar autos.");
    printf( "\n   3. Probar mantenimientos.");
    printf( "\n   4. Prueba completa en un proceso.");
    printf( "\n   0. Salir." );

    /* Filtramos la opción elegida por el usuario */
    do{
      printf( "\n   Introduzca opción (1-4): ");
      scanf( "%d", &opcion );
    } while ( opcion > 0 && (opcion < 1 || opcion > 4) );
    /* La opción sólo puede ser 1, 2, 3 ó 4 */
    system("clear");
    switch ( opcion ){
      case 1:
        printf( "PROBAR PROPIETARIOS" );
        printf( "\n   1. Registrar propietarios (Validar datos)." );
        printf( "\n   2. Editar propietarios (Validar datos)." );
        printf( "\n   3. Eliminar propietarios (Relacion con autos)." );
        printf( "\n   0. Regresar." );

        do{
          printf( "\n   Introduzca opción (1-3): ");
          scanf( "%d", &opcion_propietarios );
        } while ( opcion_propietarios  < 0 && (opcion_propietarios < 1 || opcion_propietarios > 3) );

        system("clear");
        switch (opcion_propietarios) {
          case 1:
            printf( "PROBAR PROPIETARIOS -> Registrar propietarios" );
            printf( "\n   Validar datos de propietarios, campos con * son requeridos, ingrese el mismo email en mas de un usuario y espere la validacion" );
            printf( "\n   Nombre*: "); std::cin >> nombre;
            printf( "   Apellido*: "); std::cin >> apellido;
            printf( "   Email*: "); std::cin >> email;
            printf( "   Celular*: "); std::cin >> celular;
            printf( "   Acepta los terminos se uso y privacidad? [Y/n]: "); std::cin >> terminos_txt;
            if ( terminos_txt == 'Y' || terminos_txt == 'y' ) {
              strcpy(terminos, "TRUE");
            } else {
              strcpy(terminos, "FALSE");
            }

            insert_propietarios(conn, nombre, apellido, email, celular, terminos);
            
            std::cout << "Presione 1 para continuar. "; std::cin>>terminos_txt;
          break;
          case 2:
            printf( "PROBAR PROPIETARIOS -> Editar propietarios" );
            printf( "\n   Seleccione un propietario y edite su informacion " );
            listar_propietarios(conn);
            std::cout << "   Ingrese el id del propietario: "; std::cin>>id_propietario;
            select_propietarios(conn, id_propietario);
            system("clear");
          break;
          case 3:
          break;
        }
      break;

      case 2: 
        if (PQstatus(conn) != CONNECTION_BAD){
          res = PQexec(conn, "select * from usuarios where id =2");
          printf("\n========================================\n");
          if (res != NULL && PGRES_TUPLES_OK == PQresultStatus(res)){
            for (i = PQntuples(res)-1; i >= 0; i--){
              for (j = PQnfields(res)-1; j >= 0; j--)
                printf("%s\t",PQgetvalue(res,i,j));
              printf("\n");
            }
            PQclear(res);
          }
          printf("\n========================================\n");
        }
          //PQfinish(conn);
      break;

      case 3: 
        printf( "\n   Introduzca un n%cmero entero para las opciones: ", 163 );
      break;
      case 4:
        if (PQstatus(conn) != CONNECTION_BAD){
          int id;
          char nombre[20];
          char apellido[20];
          char sql_query[200]; // Variable para almacenar el insert string concatenado
          printf("%s\n", "Insertar datos en la tabla ususerio");
          // printf("%s", "Id: "); scanf("%d", &id);
          // printf("%s", "nombre: "); scanf("%s", &nombre);
          // printf("%s", "apellido: "); scanf("%s", &apellido);
        }
      break;
    }
  } while ( opcion > 0 && opcion != 4 );
    //
  PQfinish(conn);

  
  printf( "\nGracias por usar el programa de pruebas, regrese pronto\n\n\n" );

  return 0;
}

void insert_propietarios(PGconn *conn, char nombre[55], char apellido[55], char email[55], char celular[55], char terminos[10]) {
  char sql_query[255];
  PGresult *res_p;
  strcpy (sql_query, "INSERT INTO owners (agreement_terms, cel_phone, email, last_name, name, created_at, updated_at) VALUES (");
  strcat (sql_query, terminos);
  strcat (sql_query, ", '");
  strcat (sql_query, celular);
  strcat (sql_query, "', '");
  strcat (sql_query, email);
  strcat (sql_query, "', '");
  strcat (sql_query, apellido);
  strcat (sql_query, "', '");
  strcat (sql_query, nombre);
  strcat (sql_query, "', now(), now());");
  if (PQstatus(conn) != CONNECTION_BAD){
    res_p = PQexec(conn, sql_query);
    printf("\n========================================\n");
    if (PQresultStatus(res_p) != PGRES_COMMAND_OK) {
      std::cout << "Insersion fallida" << PQerrorMessage(conn);
    }
//    if (res != NULL && PGRES_TUPLES_OK == PQresultStatus(res)){
//      for (i = PQntuples(res)-1; i >= 0; i--){
//        for (j = PQnfields(res)-1; j >= 0; j--)
//          printf("%s\t",PQgetvalue(res,i,j));
//        printf("\n");
//      }
//      PQclear(res);
//    }
//    printf("\n========================================\n");
  }
}

void listar_propietarios(PGconn *conn) {
  int i, j;
  char sql_query[255];
  PGresult *res_p;
  printf("\n%s\n", "   Lista de propietarios.");
  strcpy(sql_query, "SELECT agreement_terms, cel_phone, email, last_name, name, id from owners;");
  printf("ID\tNombre\tApellido\tEmail\tCelular\tTerminos\n");
  if (PQstatus(conn) != CONNECTION_BAD){
    res_p = PQexec(conn, sql_query);
    if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p)){
      for (i = PQntuples(res_p)-1; i >= 0; i--){
        for (j = PQnfields(res_p)-1; j >= 0; j--)
          printf("%s\t",PQgetvalue(res_p,i,j));
        printf("\n");
      }
      PQclear(res_p);
    }
  }
}

void select_propietarios(PGconn *conn, int propietario_id) {
  int i, j;
  char *id = propietario_id;
  char sql_query[255];
  PGresult *res_p;
  strcpy(sql_query, "SELECT agreement_terms, cel_phone, email, last_name, name, id from owners where id =");
  strcat(sql_query, id);
  strcat(sql_query, ";");
  printf("ID\tNombre\tApellido\tEmail\tCelular\tTerminos\n");
  if (PQstatus(conn) != CONNECTION_BAD){
    res_p = PQexec(conn, sql_query);
    if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p)){
      for (i = PQntuples(res_p)-1; i >= 0; i--){
        for (j = PQnfields(res_p)-1; j >= 0; j--)
          printf("%s\t",PQgetvalue(res_p,i,j));
        printf("\n");
      }
      PQclear(res_p);
    }
  }
}

