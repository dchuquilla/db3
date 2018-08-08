#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <libpq-fe.h>
#include <string.h>

void insert_propietarios();
void listar_propietarios();
void select_propietarios(char propietario_id[5]);
void editar_propietario();
void formulario_propietarios();

// Variables propietario
int opcion_propietarios;
char id_propietario[5];
char propietario_nombre[55];
char propietario_apellido[55];
char propietario_email[55];
char propietario_celular[55];
char propietario_terminos_txt;
char terminos[10];
PGconn *conn;
PGresult *res;

int main() {
  int hole; // la trinchera de los stops
  int i, j, n, opcion, input_character;


  conn = PQsetdbLogin("ec2-54-243-235-153.compute-1.amazonaws.com","5432",NULL,NULL,"da5o8diaj47q2f","lgiihovsucecaa","200179f5506cfb252aa3acce06de0a24e290dd259d00db06703913b84e607a22");

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
            formulario_propietarios();

            insert_propietarios();
            
            std::cout << "Presione 1 para continuar. "; std::cin>>hole;
          break;
          case 2:
            printf( "PROBAR PROPIETARIOS -> Editar propietarios" );
            printf( "\n   Seleccione un propietario y edite su informacion " );
            listar_propietarios();
            std::cout << "   Ingrese el id del propietario: "; std::cin>>id_propietario;
            system("clear");
            select_propietarios(id_propietario);
            formulario_propietarios();
            

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
          // char nombre[20];
          // char apellido[20];
          // char sql_query[200]; // Variable para almacenar el insert string concatenado
          // printf("%s\n", "Insertar datos en la tabla ususerio");
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

void insert_propietarios() {
  char sql_query[255];
  PGresult *res_p;
  strcpy (sql_query, "INSERT INTO owners (agreement_terms, cel_phone, email, last_name, name, created_at, updated_at) VALUES (");
  strcat (sql_query, terminos);
  strcat (sql_query, ", '");
  strcat (sql_query, propietario_celular);
  strcat (sql_query, "', '");
  strcat (sql_query, propietario_email);
  strcat (sql_query, "', '");
  strcat (sql_query, propietario_apellido);
  strcat (sql_query, "', '");
  strcat (sql_query, propietario_nombre);
  strcat (sql_query, "', now(), now());");
  if (PQstatus(conn) != CONNECTION_BAD){
    res_p = PQexec(conn, sql_query);
    printf("\n========================================\n");
    if (PQresultStatus(res_p) != PGRES_COMMAND_OK) {
      std::cout << "Insersion fallida" << PQerrorMessage(conn);
    }
  }
}

void listar_propietarios() {
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

void select_propietarios(char propietario_id[5]) {
  int i, j;
  char sql_query[255];
  PGresult *res_p;
  strcpy(sql_query, "SELECT agreement_terms, cel_phone, email, last_name, name, id from owners where id =");
  strcat(sql_query, propietario_id);
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

void formulario_propietarios() {
  printf( "\n   Nombre*: "); std::cin >> propietario_nombre;
  printf( "   Apellido*: "); std::cin >> propietario_apellido;
  printf( "   Email*: "); std::cin >> propietario_email;
  printf( "   Celular*: "); std::cin >> propietario_celular;
  printf( "   Acepta los terminos se uso y privacidad? [Y/n]: "); std::cin >> propietario_terminos_txt;
  if ( propietario_terminos_txt == 'Y' || propietario_terminos_txt == 'y' ) {
    strcpy(terminos, "TRUE");
  } else {
    strcpy(terminos, "FALSE");
  }
}

