#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <libpq-fe.h>
#include <string.h>
#include <sstream>

using namespace std;

void insert_propietarios();
void update_propietarios(string propietario_id);
void listar_propietarios();
void select_propietarios(string propietario_id);
void editar_propietario();
void formulario_propietarios();

// Variables propietario
int opcion_propietarios;
string id_propietario;
string propietario_nombre;
string propietario_apellido;
string propietario_email;
string propietario_celular;
string propietario_terminos_txt;
string propietario_terminos;
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
                  propietario_terminos = "";
                  propietario_celular = "";
                  propietario_email = "";
                  propietario_apellido = "";
                  propietario_nombre = "";
                  printf( "PROBAR PROPIETARIOS -> Registrar propietarios" );
                  printf( "\n   Validar datos de propietarios, campos con * son requeridos, ingrese el mismo email en mas de un usuario y espere la validacion" );
                  
                  formulario_propietarios();

                  insert_propietarios();
                  
                  cout << "Presione 1 para continuar. "; cin>>hole;
                break;
                case 2:
                  printf( "PROBAR PROPIETARIOS -> Editar propietarios" );
                  printf( "\n   Seleccione un propietario y edite su informacion " );
                  listar_propietarios();
                  cout << "   Ingrese el id del propietario: "; cin>>id_propietario;
                  system("clear");
                  
                  select_propietarios(id_propietario);
                  
                  formulario_propietarios();

                  update_propietarios(id_propietario);
                  

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
  PGresult *res_p;
  string sql_query ("INSERT INTO owners (agreement_terms, cel_phone, email, last_name, name, created_at, updated_at) VALUES (");
  sql_query = sql_query + propietario_terminos;
  sql_query = sql_query + ", '";
  sql_query = sql_query + propietario_celular;
  sql_query = sql_query + "', '";
  sql_query = sql_query + propietario_email;
  sql_query = sql_query + "', '";
  sql_query = sql_query + propietario_apellido;
  sql_query = sql_query + "', '";
  sql_query = sql_query + propietario_nombre;
  sql_query = sql_query + "', now(), now());";
  const char *c = sql_query.c_str();
  if (PQstatus(conn) != CONNECTION_BAD){
    res_p = PQexec(conn, c);
    printf("\n========================================\n");
    if (PQresultStatus(res_p) != PGRES_COMMAND_OK) {
      cout << "Insersion fallida" << PQerrorMessage(conn);
    }
  }
}

void update_propietarios(string propietario_id) {
  PGresult *res_p;
  string sql_query ("UPDATE owners ");
  sql_query = sql_query + "SET agreement_terms = "+ propietario_terminos + ", ";
  sql_query = sql_query + "SET cel_phone = '" + propietario_celular + "', ";
  sql_query = sql_query + "SET email = '" + propietario_email + "', ";
  sql_query = sql_query + "SET last_name = '" + propietario_apellido + "', ";
  sql_query = sql_query + "SET name = '" + propietario_nombre + "', ";
  sql_query = sql_query + "SET updated_at = now()) WHERE id = " + propietario_id + ";";
  const char *c = sql_query.c_str();
  if (PQstatus(conn) != CONNECTION_BAD){
    res_p = PQexec(conn, c);
    printf("\n========================================\n");
    if (PQresultStatus(res_p) != PGRES_COMMAND_OK) {
      cout << "Actualizacion fallida" << PQerrorMessage(conn);
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

void select_propietarios(string propietario_id) {
  int i, j;
  PGresult *res_p;
  string sql_query ("SELECT agreement_terms, cel_phone, email, last_name, name, id from owners where id =");
  sql_query = sql_query + propietario_id;
  sql_query = sql_query + ";";
  const char *c = sql_query.c_str();
  printf("ID\tNombre\tApellido\tEmail\tCelular\tTerminos\n");
  if (PQstatus(conn) != CONNECTION_BAD){
    res_p = PQexec(conn, c);
    if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p)){
      for (i = PQntuples(res_p)-1; i >= 0; i--){
        propietario_terminos = PQgetvalue(res_p,i,1);
        propietario_celular = PQgetvalue(res_p,i,2);
        propietario_email = PQgetvalue(res_p,i,3);
        propietario_apellido = PQgetvalue(res_p,i,4);
        propietario_nombre = PQgetvalue(res_p,i,5);
        for (j = PQnfields(res_p)-1; j >= 0; j--) {
          printf("%s\t",PQgetvalue(res_p,i,j));
        }
        printf("\n");
      }
      PQclear(res_p);
    }
  }
}

void formulario_propietarios() {
  string input;
  propietario_terminos_txt = 'y';
  cout << "\n";
  cout << "   Nombre*: ";
  cin>>input;
  if ( input.length()>0 ) {
    propietario_nombre = input;
  }
  cout << "   Apellido*: ";
  cin>>input;
  if ( input.length()>0 ) {
    propietario_apellido = input;
  }
  cout << "   Email*: ";
  cin>>input;
  if ( input.length()>0 ) {
    propietario_email = input;
  }
  cout << "   Celular*: ";
  cin>>input;
  if ( input.length()>0 ) {
    propietario_celular = input;
  }
  cout << "   Acepta los terminos se uso y privacidad? [Y/n]: ";
  cin>>input;
  if ( input.length()>0 ) {
    propietario_terminos_txt = input;
  }
  if ( propietario_terminos_txt.compare("Y") == 0 || propietario_terminos_txt.compare("y")  == 0 ) {
    propietario_terminos = "TRUE";
  } else {
    propietario_terminos = "FALSE";
  }
}

