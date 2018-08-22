#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <libpq-fe.h>
#include <string.h>
#include <sstream>

using namespace std;

// Propietarios
  void insert_propietarios();
  void update_propietarios(string propietario_id);
  void listar_propietarios();
  void listar_propietarios();
  string select_propietarios(string propietario_id);
  void editar_propietario();
  void elimnar_propietario(string propietario_id);
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

// Autos
  void insert_autos();
  void update_autos(string auto_id);
  void listar_autos();
  void listar_autos_propietario(string id_propietario);
  string select_autos(string auto_id);
  void editar_auto();
  void elimnar_auto(string auto_id);
  void formulario_autos();
  void formulario_autos_completo(string id_propietario);
  void lista_tipos_vehiculo();
  string tipos_vehiculo_to_s(string tipo);

  // Variables auto
  int opcion_autos;
  string id_auto;
  string auto_marca;
  string auto_tipo;
  string auto_km_actual;
  string auto_modelo;
  string auto_propietario;
  string auto_placa;
  string auto_km_semanal;
  string auto_anio;

// Mantenimientos
  void insert_mantenimientos(bool nuevo);
  void update_mantenimientos(string mantenimiento_id);
  void listar_mantenimientos();
  void listar_mantenimientos_auto(string id_auto);
  string select_mantenimientos(string mantenimiento_id);
  void editar_mantenimiento();
  void elimnar_mantenimiento(string mantenimiento_id);
  void formulario_mantenimientos(bool nuevo);
  void formulario_mantenimientos_completo(bool nuevo, string auto_id);
  void lista_tipos_mantenimiento();
  string tipos_mantenimiento_to_s(string tipo);

  // Variables mantenimiento
  int opcion_mantenimientos;
  string id_mantenimiento;
  string mantenimiento_auto;
  string mantenimiento_tipo;
  string mantenimiento_costo;
  string mantenimiento_km_estimado;
  string mantenimiento_notificado;
  string mantenimiento_proveedor;
  string mantenimiento_fecha_revision;
  string mantenimiento_km_revision;
  string mantenimiento_fecha_agenda;
  string mantenimiento_estado;

// Variables de conexion PSQL
  PGconn *conn;
  PGresult *res;

// Otras variables
  string hole; // la trinchera de los stops

int main() {
  int i, j, n, opcion, input_character;
  string respuesta_elimina;


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
        do {
          printf( "PROBAR PROPIETARIOS" );
          printf( "\n   1. Registrar propietarios (Validar datos)." );
          printf( "\n   2. Editar propietarios (Validar datos)." );
          printf( "\n   3. Eliminar propietarios (Relacion con autos)." );
          printf( "\n   4. Mostrar todos." );
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
              
              getline(cin, hole);
              system("clear");
            break;
            case 2:
              printf( "PROBAR PROPIETARIOS -> Editar propietarios" );
              printf( "\n   Seleccione un propietario y edite su informacion " );
              listar_propietarios();
              cout << "   ID: "; cin>>id_propietario;
              system("clear");
              
              id_propietario = select_propietarios(id_propietario);
              
              if (id_propietario != "0") {
                formulario_propietarios();
                update_propietarios(id_propietario);
              } else {
                cout << "   Propietario no encontrado.";
              }
              getline(cin, hole);
              getline(cin, hole);
            break;
            case 3:
              printf( "PROBAR PROPIETARIOS -> Eliminar propietarios" );
              printf( "\n   Seleccione un propietario que quiera eliminar. " );
              listar_propietarios();
              cout << "   ID: "; cin>>id_propietario;
              system("clear");
              
              id_propietario = select_propietarios(id_propietario);
              
              if (id_propietario != "0") {
                respuesta_elimina = "n";
                cout << "   Está seguro? y/N: ";
                cin >> respuesta_elimina;
                if (respuesta_elimina.compare("Y") == 0 || respuesta_elimina.compare("y") == 0) {
                  elimnar_propietario(id_propietario);
                  getline(cin, hole);
                  getline(cin, hole);
                }
              } else {
                cout << "   Propietario no encontrado.";
              }
              system("clear");
            break;
            case 4:
              printf( "PROBAR PROPIETARIOS -> Mostrar todos" );
              listar_propietarios();
              getline(cin, hole);
              getline(cin, hole);
              system("clear");
            break;
          }
        } while (opcion_propietarios != 0);
      break;

      case 2: 
        do {
          printf( "PROBAR AUTOS" );
          printf( "\n   1. Registrar autos (Validar datos)." );
          printf( "\n   2. Editar autos (Validar datos)." );
          printf( "\n   3. Eliminar autos (Relacion con autos)." );
          printf( "\n   4. Mostrar todos." );
          printf( "\n   0. Regresar." );

          do{
            printf( "\n   Introduzca opción (1-3): ");
            scanf( "%d", &opcion_autos );
          } while ( opcion_autos  < 0 && (opcion_autos < 1 || opcion_autos > 3) );

          system("clear");
          switch (opcion_autos) {
            case 1:
              auto_marca = "";
              auto_tipo = "";
              auto_km_actual = "";
              auto_modelo = "";
              auto_propietario = "";
              auto_placa = "";
              auto_km_semanal = "";
              auto_anio = "";
              printf( "PROBAR AUTOS -> Registrar autos" );
              printf( "\n   Validar datos de autos, campos con * son requeridos." );
              
              formulario_autos();

              insert_autos();
              
              getline(cin, hole);
              system("clear");
            break;
            case 2:
              printf( "PROBAR AUTOS -> Editar autos" );
              printf( "\n   Seleccione un auto y edite su informacion " );
              listar_autos();
              cout << "   ID: "; cin>>id_auto;
              system("clear");
              
              id_auto = select_autos(id_auto);
              
              if (id_auto != "0") {
                formulario_autos();
                update_autos(id_auto);
              } else {
                cout << "   auto no encontrado.";
              }
              getline(cin, hole);
              system("clear");
            break;
            case 3:
              printf( "PROBAR AUTOS -> Eliminar autos" );
              printf( "\n   Seleccione un auto que quiera eliminar. " );
              listar_autos();
              cout << "   ID: "; cin>>id_auto;
              system("clear");
              
              id_auto = select_autos(id_auto);
              
              if (id_auto != "0") {
                respuesta_elimina = "n";
                cout << "   Está seguro? y/N: ";
                cin >> respuesta_elimina;
                if (respuesta_elimina.compare("Y") == 0 || respuesta_elimina.compare("y") == 0) {
                  elimnar_auto(id_auto);
                  getline(cin, hole);
                  getline(cin, hole);
                }
              } else {
                cout << "   auto no encontrado.";

              }
              system("clear");
            break;
            case 4:
              printf( "PROBAR AUTOS -> Mostrar todos" );
              listar_autos();
              getline(cin, hole);
              getline(cin, hole);
              system("clear");
            break;
          }
        } while (opcion_autos != 0);
      break;

      case 3: 
        do {
          printf( "PROBAR MANTENIMIENTOS" );
          printf( "\n   1. Registrar mantenimientos (Validar datos)." );
          printf( "\n   2. Editar mantenimientos (Validar datos)." );
          printf( "\n   3. Eliminar mantenimientos (Relacion con autos)." );
          printf( "\n   4. Mostrar todos." );
          printf( "\n   0. Regresar." );

          do{
            printf( "\n   Introduzca opción (1-3): ");
            scanf( "%d", &opcion_mantenimientos );
          } while ( opcion_mantenimientos  < 0 && (opcion_mantenimientos < 1 || opcion_mantenimientos > 3) );

          system("clear");
          switch (opcion_mantenimientos) {
            case 1:
              mantenimiento_auto = "";
              mantenimiento_tipo = "";
              mantenimiento_costo = "NULL";
              mantenimiento_km_estimado = "";
              mantenimiento_notificado = "";
              mantenimiento_proveedor = "";
              mantenimiento_fecha_revision = "NULL";
              mantenimiento_km_revision = "NULL";
              mantenimiento_fecha_agenda = "";
              mantenimiento_estado = "";
              printf( "PROBAR MANTENIMIENTOS -> Registrar mantenimientos" );
              printf( "\n   Validar datos de mantenimientos, campos con * son requeridos." );
              
              formulario_mantenimientos(true);

              insert_mantenimientos(true);
              
              getline(cin, hole);
              system("clear");
            break;
            case 2:
              printf( "PROBAR MANTENIMIENTOS -> Editar mantenimientos" );
              printf( "\n   Seleccione un mantenimiento y edite su informacion " );
              listar_mantenimientos();
              cout << "   ID: "; cin>>id_mantenimiento;
              system("clear");
              
              id_mantenimiento = select_mantenimientos(id_mantenimiento);
              
              if (id_mantenimiento != "0") {
                formulario_mantenimientos(false);
                update_mantenimientos(id_mantenimiento);
              } else {
                cout << "   mantenimiento no encontrado.";
              }
              getline(cin, hole);
              system("clear");
            break;
            case 3:
              printf( "PROBAR MANTENIMIENTOS -> Eliminar mantenimientos" );
              printf( "\n   Seleccione un mantenimiento que quiera eliminar. " );
              listar_mantenimientos();
              cout << "   ID: "; cin>>id_mantenimiento;
              system("clear");
              
              id_mantenimiento = select_mantenimientos(id_mantenimiento);
              
              if (id_mantenimiento != "0") {
                respuesta_elimina = "n";
                cout << "   Está seguro? y/N: ";
                cin >> respuesta_elimina;
                if (respuesta_elimina.compare("Y") == 0 || respuesta_elimina.compare("y") == 0) {
                  elimnar_mantenimiento(id_mantenimiento);
                  getline(cin, hole);
                  getline(cin, hole);
                }
              } else {
                cout << "   mantenimiento no encontrado.";
                  getline(cin, hole);
                  getline(cin, hole);
              }
              system("clear");
            break;
            case 4:
              printf( "PROBAR MANTENIMIENTOS -> Mostrar todos" );
              printf( "\n   Seleccione un mantenimiento para ver todos sus detalles" );
              listar_mantenimientos();
              cout << "   ID: "; cin>>id_mantenimiento;
              system("clear");
              
              id_mantenimiento = select_mantenimientos(id_mantenimiento);
              getline(cin, hole);
              getline(cin, hole);
              system("clear");
            break;
          }
        } while (opcion_mantenimientos != 0);
      break;

      case 4:
        string input;
        string continuar_completo;
        do {
          cout << "PRUEBA COMPLETA EN UN PROCESO";
          cout << "\n   Deberá seleccionar un propietario, para luego trabajar con los mantenimientos de sus autos.";
          cout << "\n   Presion ENTER para continuar.";
          getline(cin, hole);
          getline(cin, hole);
          listar_propietarios();
          cout << "   ID: "; cin>>id_propietario;
          system("clear");
          id_propietario = select_propietarios(id_propietario);
          
          if (id_propietario != "0") {
            cout << "\n   Seleecione un auto de este propietario";
            listar_autos_propietario(id_propietario);
            cout << "   ID: "; cin>>id_auto;
            system("clear");
            id_propietario = select_propietarios(id_propietario);
            id_auto = select_autos(id_auto);
            if (id_auto != "0") {
              listar_mantenimientos_auto(id_auto);
              cout << "   ID: "; cin>>id_mantenimiento;
              id_mantenimiento = select_mantenimientos(id_mantenimiento);

              do {
                printf( "PRUEBA COMPLETA EN UN PROCESO -> Mantenimientos" );
                printf( "\n   1. Agregar mantenimientos." );
                printf( "\n   2. Editar mantenimientos." );
                printf( "\n   3. Eliminar mantenimientos." );
                printf( "\n   0. Regresar." );

                do{
                  printf( "\n   Introduzca opción (1-3): ");
                  scanf( "%d", &opcion_mantenimientos );
                } while ( opcion_mantenimientos  < 0 && (opcion_mantenimientos < 1 || opcion_mantenimientos > 3) );

                switch (opcion_mantenimientos) {
                  case 1:
                    mantenimiento_auto = "";
                    mantenimiento_tipo = "";
                    mantenimiento_costo = "NULL";
                    mantenimiento_km_estimado = "";
                    mantenimiento_notificado = "";
                    mantenimiento_proveedor = "";
                    mantenimiento_fecha_revision = "NULL";
                    mantenimiento_km_revision = "NULL";
                    mantenimiento_fecha_agenda = "";
                    mantenimiento_estado = "";
                    printf( "MANTENIMIENTOS -> Registrar mantenimientos" );
                    printf( "\n   Validar datos de mantenimientos, campos con * son requeridos." );
                    
                    formulario_mantenimientos_completo(true, id_auto);

                    insert_mantenimientos(true);
                    
                    getline(cin, hole);
                    system("clear");
                  break;
                  case 2:
                    printf( "MANTENIMIENTOS -> Editar mantenimientos" );
                    printf( "\n   Seleccione un mantenimiento y edite su informacion " );
                    listar_mantenimientos();
                    cout << "   ID: "; cin>>id_mantenimiento;
                    
                    id_mantenimiento = select_mantenimientos(id_mantenimiento);
                    
                    if (id_mantenimiento != "0") {
                      formulario_mantenimientos_completo(false, id_auto);
                      update_mantenimientos(id_mantenimiento);
                    } else {
                      cout << "   mantenimiento no encontrado.";
                    }
                    getline(cin, hole);
                    system("clear");
                  break;
                  case 3:
                    printf( "MANTENIMIENTOS -> Eliminar mantenimientos" );
                    printf( "\n   Seleccione un mantenimiento que quiera eliminar. " );
                    listar_mantenimientos();
                    cout << "   ID: "; cin>>id_mantenimiento;
                    system("clear");
                    
                    id_mantenimiento = select_mantenimientos(id_mantenimiento);
                    
                    if (id_mantenimiento != "0") {
                      respuesta_elimina = "n";
                      cout << "   Está seguro? y/N: ";
                      cin >> respuesta_elimina;
                      if (respuesta_elimina.compare("Y") == 0 || respuesta_elimina.compare("y") == 0) {
                        elimnar_mantenimiento(id_mantenimiento);
                        getline(cin, hole);
                        getline(cin, hole);
                      }
                    } else {
                      cout << "   mantenimiento no encontrado.";
                        getline(cin, hole);
                        getline(cin, hole);
                    }
                    system("clear");
                  break;
                }
              } while (opcion_mantenimientos != 0);
            } else {
              cout << "   auto no encontrado - Agregar un nuevo auto.";
              auto_marca = "";
              auto_tipo = "";
              auto_km_actual = "";
              auto_modelo = "";
              auto_propietario = "";
              auto_placa = "";
              auto_km_semanal = "";
              auto_anio = "";
              printf( "   AUTOS -> Registrar autos" );
              
              formulario_autos_completo(id_propietario);

              insert_autos();
              
              getline(cin, hole);
              system("clear");
            }
          } else {
            cout << "   Propietario no encontrado.";
          }
          continuar_completo = "Y";
          cout << "Desea continuar con la prueba completa (Y/n): ";
          getline(cin, input);
          getline(cin, input);
          if ( !input.empty() ) {
            continuar_completo = input;
          }
          system("clear");
        } while (continuar_completo.compare("Y") == 0 || continuar_completo.compare("y") == 0);
      break;
    }
  } while ( opcion > 0 && opcion != 4 );
    //
  PQfinish(conn);

  
  printf( "\nGracias por usar el programa de pruebas, regrese pronto\n\n\n" );

  return 0;
}

// Implementacion propietarios
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
      if (PQresultStatus(res_p) != PGRES_COMMAND_OK) {
        cout << "\n   !!! Error al insertar: " << PQerrorMessage(conn);
      } else {
        cout << "\n   Propietario registrado.";
      }
    }
  }
  void update_propietarios(string propietario_id) {
    PGresult *res_p;
    string sql_query ("UPDATE owners SET ");
    sql_query = sql_query + "agreement_terms = "+ propietario_terminos + ", ";
    sql_query = sql_query + "cel_phone = '" + propietario_celular + "', ";
    sql_query = sql_query + "email = '" + propietario_email + "', ";
    sql_query = sql_query + "last_name = '" + propietario_apellido + "', ";
    sql_query = sql_query + "name = '" + propietario_nombre + "', ";
    sql_query = sql_query + "updated_at = now() WHERE id = " + propietario_id + ";";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      printf("\n========================================\n");
      if (PQresultStatus(res_p) != PGRES_COMMAND_OK) {
        cout << "Actualizacion fallida" << PQerrorMessage(conn);
      } else {
        cout << "Propietario actualizado" << PQerrorMessage(conn);
      }
    }
  }
  void listar_propietarios() {
    int i, j;
    char sql_query[255];
    PGresult *res_p;
    printf("\n%s\n", "   Lista de propietarios.");
    strcpy(sql_query, "SELECT agreement_terms, cel_phone, email, last_name, name, id FROM owners ORDER BY id DESC;");
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, sql_query);
      if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p)){
        cout << right << setw(3) << "ID" << right << setw(25) << "Nombre" << right << setw(25) << "Apellido" << right << setw(50) << "Email" << right << setw(15) << "Celular" << right << setw(15) << "Terminos" << "\n";
        cout << right << setw(118) << "-------------------------------------------------------------------------------------------------------------------------------------\n";
        for (i = PQntuples(res_p)-1; i >= 0; i--){
          for (j = PQnfields(res_p)-1; j >= 0; j--){
            if (j == PQnfields(res_p)-1) {
              cout << right << setw(3) << PQgetvalue(res_p,i,j);
            } else if (j == PQnfields(res_p)-2 || j == PQnfields(res_p)-3) {
              cout << right << setw(25) << PQgetvalue(res_p,i,j);
            } else if (j == PQnfields(res_p)-4) {
              cout << right << setw(50) << PQgetvalue(res_p,i,j);
            } else if (j == PQnfields(res_p)-5) {
              cout << right << setw(15) << PQgetvalue(res_p,i,j);
            } else {
              cout << right << setw(15) << PQgetvalue(res_p,i,j);
            }
          }
          printf("\n");
        }
        PQclear(res_p);
      }
    }
  }
  string select_propietarios(string propietario_id) {
    int i, j;
    PGresult *res_p;
    string sql_query ("SELECT agreement_terms, cel_phone, email, last_name, name, id from owners where id = ");
    sql_query = sql_query + propietario_id;
    sql_query = sql_query + ";";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p) && PQntuples(res_p) > 0){
        cout << right << setw(3) << "ID" << right << setw(25) << "Nombre" << right << setw(25) << "Apellido" << right << setw(50) << "Email" << right << setw(15) << "Celular" << right << setw(15) << "Terminos" << "\n";
        cout << right << setw(118) << "-------------------------------------------------------------------------------------------------------------------------------------\n";
        for (i = PQntuples(res_p)-1; i >= 0; i--){
          propietario_terminos = PQgetvalue(res_p,i,0);
          propietario_celular  = PQgetvalue(res_p,i,1);
          propietario_email    = PQgetvalue(res_p,i,2);
          propietario_apellido = PQgetvalue(res_p,i,3);
          propietario_nombre   = PQgetvalue(res_p,i,4);
          for (j = PQnfields(res_p)-1; j >= 0; j--){
            if (j == PQnfields(res_p)-1) {
              cout << right << setw(3) << PQgetvalue(res_p,i,j);
            } else if (j == PQnfields(res_p)-2 || j == PQnfields(res_p)-3) {
              cout << right << setw(25) << PQgetvalue(res_p,i,j);
            } else if (j == PQnfields(res_p)-4) {
              cout << right << setw(50) << PQgetvalue(res_p,i,j);
            } else if (j == PQnfields(res_p)-5) {
              cout << right << setw(15) << PQgetvalue(res_p,i,j);
            } else {
              cout << right << setw(15) << PQgetvalue(res_p,i,j);
            }
          }
          printf("\n");
        }
        PQclear(res_p);
        return propietario_id;
      } else {
        return "0";
      }
    }
  }
  void elimnar_propietario(string propietario_id) {
    PGresult *res_p;
    string sql_query ("DELETE FROM owners WHERE id = ");
    sql_query = sql_query + propietario_id;
    sql_query = sql_query + ";";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p)) {
        cout << "\n   Propietario eliminado.";
      } else {
        cout << "\n   !!!" << PQerrorMessage(conn);
      }
    }
  }
  void formulario_propietarios() {
    string input;
    propietario_terminos_txt = 'y';
    cout << "\n";
    cout << "   Nombre*: ";
    getline(cin, input); // Duplicado para arreglar error de valores por defecto
    getline(cin, input);
    if ( !input.empty() ) {
      propietario_nombre = input;
    }
    cout << "   Apellido*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      propietario_apellido = input;
    }
    cout << "   Email*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      propietario_email = input;
    }
    cout << "   Celular*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      propietario_celular = input;
    }
    cout << "   Acepta los terminos se uso y privacidad? [Y/n]: ";
    getline(cin, input);
    if ( !input.empty() ) {
      propietario_terminos_txt = input;
    }
    if ( propietario_terminos_txt.compare("Y") == 0 || propietario_terminos_txt.compare("y")  == 0 ) {
      propietario_terminos = "TRUE";
    } else {
      propietario_terminos = "FALSE";
    }
  }

// Implementacion autos
  void insert_autos() {
    PGresult *res_p;
    string sql_query ("INSERT INTO cars ( brand, car_type, current_km, model, owner_id, plate, week_km, year, created_at, updated_at) VALUES ('");
    sql_query = sql_query + auto_marca;
    sql_query = sql_query + "', '";
    sql_query = sql_query + auto_tipo;
    sql_query = sql_query + "', ";
    sql_query = sql_query + auto_km_actual;
    sql_query = sql_query + ", '";
    sql_query = sql_query + auto_modelo;
    sql_query = sql_query + "', ";
    sql_query = sql_query + auto_propietario;
    sql_query = sql_query + ", '";
    sql_query = sql_query + auto_placa;
    sql_query = sql_query + "', ";
    sql_query = sql_query + auto_km_semanal;
    sql_query = sql_query + ", ";
    sql_query = sql_query + auto_anio;
    sql_query = sql_query + ", now(), now());";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      if (PQresultStatus(res_p) != PGRES_COMMAND_OK) {
        cout << "\n   !!! Error al insertar: " << PQerrorMessage(conn);
      } else {
        cout << "\n   auto registrado.";
      }
    }
  }
  void update_autos(string auto_id) {
    PGresult *res_p;
    string sql_query ("UPDATE cars SET ");
    sql_query = sql_query + "brand = '" + auto_marca + "', ";
    sql_query = sql_query + "car_type = '" + auto_tipo + "', ";
    sql_query = sql_query + "current_km = " + auto_km_actual + ", ";
    sql_query = sql_query + "model = '" + auto_modelo + "', ";
    sql_query = sql_query + "owner_id = " + auto_propietario + ", ";
    sql_query = sql_query + "plate = '" + auto_placa + "', ";
    sql_query = sql_query + "week_km = " + auto_km_semanal + ", ";
    sql_query = sql_query + "year = " + auto_anio + ", ";
    sql_query = sql_query + "updated_at = now() WHERE id = " + auto_id + ";";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      printf("\n========================================\n");
      if (PQresultStatus(res_p) != PGRES_COMMAND_OK) {
        cout << "Actualizacion fallida" << PQerrorMessage(conn);
      } else {
        cout << "Auto actualizado" << PQerrorMessage(conn);
      }
    }
  }
  void listar_autos() {
    int i, j;
    char sql_query[255];
    PGresult *res_p;
    printf("\n%s\n", "   Lista de autos.");
    strcpy(sql_query, "SELECT week_km, current_km, car_type, year, model, brand, (select owners.name || ' ' || owners.last_name from owners where id = cars.owner_id limit 1) as propietario, plate, id FROM cars ORDER BY id DESC;");
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, sql_query);
      if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p)){
        cout << right << setw(3) << "ID" << right << setw(10) << "Placa" << right << setw(30) << "Propietario" << right << setw(20) << "Marca" << right << setw(20) << "Modelo" << right << setw(9) << "Año" << right << setw(20) << "Tipo" << right << setw(15) << "KM Actual" << right << setw(15) << "KM Semanal" << "\n";
        cout << right << setw(150) << "---------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        for (i = PQntuples(res_p)-1; i >= 0; i--){
          cout << right << setw(3) << PQgetvalue(res_p,i,8); // ID
          cout << right << setw(10) << PQgetvalue(res_p,i,7); // Placa
          cout << right << setw(30) << PQgetvalue(res_p,i,6); // Propietario
          cout << right << setw(20) << PQgetvalue(res_p,i,5); // Marca
          cout << right << setw(20) << PQgetvalue(res_p,i,4); // Modelo
          cout << right << setw(8) << PQgetvalue(res_p,i,3); // Año
          cout << right << setw(20) << PQgetvalue(res_p,i,2); // Tipo
          cout << right << setw(15) << PQgetvalue(res_p,i,1); // KM actual
          cout << right << setw(15) << PQgetvalue(res_p,i,0); // KM Semanal
          printf("\n");
        }
        PQclear(res_p);
      }
    }
  }
  void listar_autos_propietario(string id_propietario) {
    int i, j;
    PGresult *res_p;
    printf("\n%s\n", "   Lista de autos.");
    string sql_query ("SELECT week_km, current_km, car_type, year, model, brand, (select owners.name || ' ' || owners.last_name from owners where id = cars.owner_id limit 1) as propietario, plate, id FROM cars where owner_id = ");
    sql_query = sql_query + id_propietario;
    sql_query = sql_query + " ORDER BY id DESC;";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p)){
        cout << right << setw(3) << "ID" << right << setw(10) << "Placa" << right << setw(30) << "Propietario" << right << setw(20) << "Marca" << right << setw(20) << "Modelo" << right << setw(9) << "Año" << right << setw(20) << "Tipo" << right << setw(15) << "KM Actual" << right << setw(15) << "KM Semanal" << "\n";
        cout << right << setw(150) << "---------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        for (i = PQntuples(res_p)-1; i >= 0; i--){
          cout << right << setw(3) << PQgetvalue(res_p,i,8); // ID
          cout << right << setw(10) << PQgetvalue(res_p,i,7); // Placa
          cout << right << setw(30) << PQgetvalue(res_p,i,6); // Propietario
          cout << right << setw(20) << PQgetvalue(res_p,i,5); // Marca
          cout << right << setw(20) << PQgetvalue(res_p,i,4); // Modelo
          cout << right << setw(8) << PQgetvalue(res_p,i,3); // Año
          cout << right << setw(20) << PQgetvalue(res_p,i,2); // Tipo
          cout << right << setw(15) << PQgetvalue(res_p,i,1); // KM actual
          cout << right << setw(15) << PQgetvalue(res_p,i,0); // KM Semanal
          printf("\n");
        }
        PQclear(res_p);
      }
    }
  }
  string select_autos(string auto_id) {
    int i, j;
    PGresult *res_p;
    string sql_query ("SELECT week_km, current_km, car_type, year, model, brand, (select owners.name || ' ' || owners.last_name from owners where id = cars.owner_id limit 1) as propietario, plate, id, owner_id FROM cars WHERE id = ");
    sql_query = sql_query + auto_id;
    sql_query = sql_query + ";";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p) && PQntuples(res_p) > 0){
        cout << right << setw(3) << "ID" << right << setw(10) << "Placa" << right << setw(30) << "Propietario" << right << setw(20) << "Marca" << right << setw(20) << "Modelo" << right << setw(9) << "Año" << right << setw(20) << "Tipo" << right << setw(15) << "KM Actual" << right << setw(15) << "KM Semanal" << "\n";
        cout << right << setw(150) << "---------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        for (i = PQntuples(res_p)-1; i >= 0; i--){
          auto_placa = PQgetvalue(res_p,i,7);
          auto_propietario = PQgetvalue(res_p,i,9);
          auto_marca = PQgetvalue(res_p,i,5);
          auto_modelo = PQgetvalue(res_p,i,4);
          auto_anio = PQgetvalue(res_p,i,3);
          auto_tipo = PQgetvalue(res_p,i,2);
          auto_km_actual = PQgetvalue(res_p,i,1);
          auto_km_semanal = PQgetvalue(res_p,i,0);
          cout << right << setw(3) << PQgetvalue(res_p,i,8); // ID
          cout << right << setw(10) << PQgetvalue(res_p,i,7); // Placa
          cout << right << setw(30) << PQgetvalue(res_p,i,6); // Propietario
          cout << right << setw(20) << PQgetvalue(res_p,i,5); // Marca
          cout << right << setw(20) << PQgetvalue(res_p,i,4); // Modelo
          cout << right << setw(8) << PQgetvalue(res_p,i,3); // Año
          cout << right << setw(20) << PQgetvalue(res_p,i,2); // Tipo
          cout << right << setw(15) << PQgetvalue(res_p,i,1); // KM actual
          cout << right << setw(15) << PQgetvalue(res_p,i,0); // KM Semanal
          printf("\n");
        }
        PQclear(res_p);
        return auto_id;
      } else {
        return "0";
      }
    }
  }
  void elimnar_auto(string auto_id) {
    PGresult *res_p;
    string sql_query ("DELETE FROM cars WHERE id = ");
    sql_query = sql_query + auto_id;
    sql_query = sql_query + ";";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p)) {
        cout << "\n   Auto eliminado.";
      } else {
        cout << "\n   !!!" << PQerrorMessage(conn);
      }
    }
  }
  void formulario_autos() {
    string input;
    cout << "\n";
    
    cout << "   Placa*: ";
    getline(cin, input);
    getline(cin, input); // Duplicado para arreglar error de valores por defecto
    if ( !input.empty() ) {
      auto_placa = input;
    }
    cout << "   Marca*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_marca = input;
    }
    cout << "   Modelo*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_modelo = input;
    }
    lista_tipos_vehiculo();
    cout << "   Tipo*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_tipo = tipos_vehiculo_to_s(input);
    }
    listar_propietarios();
    cout << "   Propietario ID*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_propietario = input;
    }
    cout << "   KM Actual*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_km_actual = input;
    }
    cout << "   KM Semanal*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_km_semanal = input;
    }
    cout << "   Anio*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_anio = input;
    }
  }

  void formulario_autos_completo(string id_propietario) {
    string input;
    cout << "\n";
    
    cout << "   Placa*: ";
    getline(cin, input);
    getline(cin, input); // Duplicado para arreglar error de valores por defecto
    if ( !input.empty() ) {
      auto_placa = input;
    }
    cout << "   Marca*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_marca = input;
    }
    cout << "   Modelo*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_modelo = input;
    }
    lista_tipos_vehiculo();
    cout << "   Tipo*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_tipo = tipos_vehiculo_to_s(input);
    }
    auto_propietario = id_propietario;
    cout << "   KM Actual*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_km_actual = input;
    }
    cout << "   KM Semanal*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_km_semanal = input;
    }
    cout << "   Anio*: ";
    getline(cin, input);
    if ( !input.empty() ) {
      auto_anio = input;
    }
  }

  void lista_tipos_vehiculo() {
    cout << "\n     Tipos de vehículo";
    cout << "\n     [1] Liviano";
    cout << "\n     [2] Camion";
    cout << "\n     [3] Camioneta";
    cout << "\n     [4] Autobus";
    cout << "\n     [5] Motocicleta";
    cout << "\n\n";
  }

  string tipos_vehiculo_to_s(string tipo) {
    int i_tipo;
    i_tipo = atoi(tipo.c_str());
    switch(i_tipo) {
      case 1:
        return "Liviano";
      break;
      case 2:
        return "Camion";
      break;
      case 3:
        return "Camioneta";
      break;
      case 4:
        return "Autobus";
      break;
      case 5:
        return "Motocicleta";
      break;
    }
  } 

// Implementacion mantenimientos
  void insert_mantenimientos(bool nuevo) {
    PGresult *res_p;
    string sql_query ("INSERT INTO maintenance_histories (car_id, maintenance_type, cost, scheduled_date, estimated_km, review_date, review_km, provider, notified, status, created_at, updated_at) VALUES (");
    sql_query = sql_query + mantenimiento_auto;
    sql_query = sql_query + ", '";
    sql_query = sql_query + tipos_mantenimiento_to_s(mantenimiento_tipo);
    sql_query = sql_query + "', ";
    sql_query = sql_query + mantenimiento_costo;
    sql_query = sql_query + ", '";
    sql_query = sql_query + mantenimiento_fecha_agenda;
    sql_query = sql_query + "', ";
    sql_query = sql_query + mantenimiento_km_estimado;
    if (nuevo == true) {
      sql_query = sql_query + ", ";
      sql_query = sql_query + mantenimiento_fecha_revision;
      sql_query = sql_query + ", ";
    } else {
      sql_query = sql_query + ", '";
      sql_query = sql_query + mantenimiento_fecha_revision;
      sql_query = sql_query + "', ";
    }
    sql_query = sql_query + mantenimiento_km_revision;
    sql_query = sql_query + ", '";
    sql_query = sql_query + mantenimiento_proveedor;
    sql_query = sql_query + "', ";
    sql_query = sql_query + mantenimiento_notificado;
    sql_query = sql_query + ", '";
    sql_query = sql_query + mantenimiento_estado;
    sql_query = sql_query + "', now(), now());";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      if (PQresultStatus(res_p) != PGRES_COMMAND_OK) {
        cout << "\n   !!! Error al insertar: " << PQerrorMessage(conn);
      } else {
        cout << "\n   Mantenimiento registrado.";
      }
    }
  }
  void update_mantenimientos(string mantenimiento_id) {
    PGresult *res_p;
    string sql_query ("UPDATE maintenance_histories SET ");
    sql_query = sql_query + "car_id = " + mantenimiento_auto + ", ";
    sql_query = sql_query + "maintenance_type = '" + mantenimiento_tipo + "', ";
    sql_query = sql_query + "cost = " + mantenimiento_costo + ", ";
    sql_query = sql_query + "scheduled_date = '" + mantenimiento_fecha_agenda + "', ";
    sql_query = sql_query + "estimated_km = " + mantenimiento_km_estimado + ", ";
    sql_query = sql_query + "review_date = '" + mantenimiento_fecha_revision + "', ";
    sql_query = sql_query + "review_km = " + mantenimiento_km_revision + ", ";
    sql_query = sql_query + "provider = '" + mantenimiento_proveedor + "', ";
    sql_query = sql_query + "notified = " + mantenimiento_notificado + ", ";
    sql_query = sql_query + "status = '" + mantenimiento_estado + "', ";
    sql_query = sql_query + "updated_at = now() WHERE id = " + mantenimiento_id + ";";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      printf("\n========================================\n");
      if (PQresultStatus(res_p) != PGRES_COMMAND_OK) {
        cout << "   Actualizacion fallida" << PQerrorMessage(conn);
      } else {
        cout << "   Mantenimiento actualizado" << PQerrorMessage(conn);
      }
    }
  }
  void listar_mantenimientos() {
    int i, j;
    char sql_query[255];
    PGresult *res_p;
    printf("\n%s\n", "   Lista de mantenimientos.");
    strcpy(sql_query, "SELECT id, (SELECT plate FROM cars WHERE id = maintenance_histories.car_id) as auto, maintenance_type, cost, scheduled_date, estimated_km, provider, notified, status, created_at, updated_at FROM maintenance_histories ORDER BY id DESC;");
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, sql_query);
      if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p)){
        cout << right << setw(10) << "ID";
        cout << right << setw(10) << "Auto";
        cout << right << setw(35) << "Mantenimiento";
        cout << right << setw(10) << "Costo";
        cout << right << setw(33) << "Fecha Agenda";
        cout << right << setw(10) << "Km Estimado";
        cout << right << setw(20) << "Proveedor";
        cout << right << setw(7) << "Notif";
        cout << right << setw(15) << "Estado";
        cout << "\n";
        cout << right << setw(105) << "---------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        for (i = PQntuples(res_p)-1; i >= 0; i--){
          cout << right << setw(10) << PQgetvalue(res_p,i,0); // ID
          cout << right << setw(10) << PQgetvalue(res_p,i,1); // Auto
          cout << right << setw(35) << PQgetvalue(res_p,i,2); // Mantenimiento
          cout << right << setw(10) << PQgetvalue(res_p,i,3); // Costo
          cout << right << setw(33) << PQgetvalue(res_p,i,4); // Fecha Agenda
          cout << right << setw(10) << PQgetvalue(res_p,i,5); // Km Estimado
          cout << right << setw(20) << PQgetvalue(res_p,i,6); // Proveedor
          cout << right << setw(7) << PQgetvalue(res_p,i,7); // Notif
          cout << right << setw(15) << PQgetvalue(res_p,i,8); // Estado
          printf("\n");
        }
        PQclear(res_p);
      }
    }
  }
  void listar_mantenimientos_auto(string id_auto) {
    int i, j;
    PGresult *res_p;
    printf("\n%s\n", "   Lista de mantenimientos.");
    string sql_query ("SELECT id, (SELECT plate FROM cars WHERE id = maintenance_histories.car_id) as auto, maintenance_type, cost, scheduled_date, estimated_km, provider, notified, status, created_at, updated_at FROM maintenance_histories WHERE car_id = ");
    sql_query = sql_query + id_auto;
    sql_query = sql_query + " ORDER BY id DESC;";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p)){
        cout << right << setw(10) << "ID";
        cout << right << setw(10) << "Auto";
        cout << right << setw(35) << "Mantenimiento";
        cout << right << setw(10) << "Costo";
        cout << right << setw(33) << "Fecha Agenda";
        cout << right << setw(10) << "Km Estimado";
        cout << right << setw(20) << "Proveedor";
        cout << right << setw(7) << "Notif";
        cout << right << setw(15) << "Estado";
        cout << "\n";
        cout << right << setw(105) << "---------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        for (i = PQntuples(res_p)-1; i >= 0; i--){
          cout << right << setw(10) << PQgetvalue(res_p,i,0); // ID
          cout << right << setw(10) << PQgetvalue(res_p,i,1); // Auto
          cout << right << setw(35) << PQgetvalue(res_p,i,2); // Mantenimiento
          cout << right << setw(10) << PQgetvalue(res_p,i,3); // Costo
          cout << right << setw(33) << PQgetvalue(res_p,i,4); // Fecha Agenda
          cout << right << setw(10) << PQgetvalue(res_p,i,5); // Km Estimado
          cout << right << setw(20) << PQgetvalue(res_p,i,6); // Proveedor
          cout << right << setw(7) << PQgetvalue(res_p,i,7); // Notif
          cout << right << setw(15) << PQgetvalue(res_p,i,8); // Estado
          printf("\n");
        }
        PQclear(res_p);
      }
    }
  }
  string select_mantenimientos(string mantenimiento_id) {
    int i, j;
    PGresult *res_p;
    string sql_query ("SELECT id, (SELECT plate FROM cars WHERE id = maintenance_histories.car_id) as auto, maintenance_type, cost, scheduled_date, estimated_km, review_date, review_km, provider, notified, status, car_id FROM maintenance_histories WHERE id = ");
    sql_query = sql_query + mantenimiento_id;
    sql_query = sql_query + ";";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p) && PQntuples(res_p) > 0){
        for (i = PQntuples(res_p)-1; i >= 0; i--){
          mantenimiento_auto = PQgetvalue(res_p,i,11);
          mantenimiento_tipo = PQgetvalue(res_p,i,2);
          mantenimiento_costo = PQgetvalue(res_p,i,3);
          mantenimiento_fecha_agenda = PQgetvalue(res_p,i,4);
          mantenimiento_km_estimado = PQgetvalue(res_p,i,5);
          mantenimiento_fecha_revision = PQgetvalue(res_p,i,6);
          mantenimiento_km_revision = PQgetvalue(res_p,i,7);
          mantenimiento_proveedor = PQgetvalue(res_p,i,8);
          mantenimiento_notificado = PQgetvalue(res_p,i,9);
          mantenimiento_estado = PQgetvalue(res_p,i,10);
          cout << right << setw(40) << "ID: " << left << setw(50) << PQgetvalue(res_p,i,0) << "\n"; // ID
          cout << right << setw(40) << "AUTO: " << left << setw(50) << PQgetvalue(res_p,i,1) << "\n"; // Auto
          cout << right << setw(40) << "MANTENIMIENTO: " << left << setw(50) << PQgetvalue(res_p,i,2) << "\n"; // Mantenimiento
          cout << right << setw(40) << "COSTO: " << left << setw(50) << PQgetvalue(res_p,i,3) << "\n"; // Costo
          cout << right << setw(40) << "FECHA AGENDA: " << left << setw(50) << PQgetvalue(res_p,i,4) << "\n"; // Fecha Agenda
          cout << right << setw(40) << "KM ESTIMADO: " << left << setw(50) << PQgetvalue(res_p,i,5) << "\n"; // Km Estimado
          cout << right << setw(41) << "FECHA REVISIÓN: " << left << setw(50) << PQgetvalue(res_p,i,6) << "\n"; // Fecha Revisión
          cout << right << setw(41) << "KM REVISIÓN: " << left << setw(50) << PQgetvalue(res_p,i,7) << "\n"; // Km Revisión
          cout << right << setw(40) << "PROVEEDOR: " << left << setw(50) << PQgetvalue(res_p,i,8) << "\n"; // Proveedor
          cout << right << setw(40) << "NOTIF: " << left << setw(50) << PQgetvalue(res_p,i,9) << "\n"; // Notif
          cout << right << setw(40) << "ESTADO: " << left << setw(50) << PQgetvalue(res_p,i,10) << "\n"; // Estado
          printf("\n");
        }
        PQclear(res_p);
        return mantenimiento_id;
      } else {
        return "0";
      }
    }
  }
  void elimnar_mantenimiento(string mantenimiento_id) {
    PGresult *res_p;
    string sql_query ("DELETE FROM maintenance_histories WHERE id = ");
    sql_query = sql_query + mantenimiento_id;
    sql_query = sql_query + ";";
    const char *c = sql_query.c_str();
    if (PQstatus(conn) != CONNECTION_BAD){
      res_p = PQexec(conn, c);
      if (res_p != NULL && PGRES_TUPLES_OK == PQresultStatus(res_p)) {
        cout << "\n   !!!" << PQerrorMessage(conn);
      } else {
        cout << "\n   Mantenimiento eliminado.";
      }
    }
  }
  void formulario_mantenimientos(bool nuevo) {
    string input;
    cout << "\n";

    if (nuevo == true) {
      listar_autos();
      cout << "   Auto [ID]*: ";
      getline(cin, input);
      getline(cin, input); // Duplicado para arreglar error de valores por defecto
      if ( !input.empty() ) {
        mantenimiento_auto = input;
      }
      lista_tipos_mantenimiento();
      cout << "   Tipo de mantenimiento*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_tipo = input;
      }
      cout << "   Fecha Agenda (YYYY-mm-dd)*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_fecha_agenda = input;
      }
      cout << "   Km Estimado*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_km_estimado = input;
      }
      input = "n";
      mantenimiento_notificado = "FALSE";
      mantenimiento_estado = "Pendiente";
    } else {
      listar_autos();
      cout << "   Auto [ID]*: ";
      getline(cin, input);
      getline(cin, input); // Duplicado para arreglar error de valores por defecto
      if ( !input.empty() ) {
        mantenimiento_auto = input;
      }
      lista_tipos_mantenimiento();
      cout << "   Tipo de mantenimiento*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_tipo = tipos_mantenimiento_to_s(input);
      }
      mantenimiento_costo = "NULL";
      cout << "   Costo*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_costo = input;
      }
      cout << "   Fecha Agenda (YYYY-mm-dd)*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_fecha_agenda = input;
      }
      cout << "   Km Estimado*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_km_estimado = input;
      }
      mantenimiento_fecha_revision = mantenimiento_fecha_agenda;
      cout << "   Fecha Revision (YYYY-mm-dd)*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_fecha_revision = input;
      }
      mantenimiento_km_revision = "NULL";
      cout << "   Km Revision*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_km_revision = input;
      }
      cout << "   Proveedor*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_proveedor = input;
      }
      input = "n";
      cout << "   Notificado? y/n*: ";
      getline(cin, input);
      if ( input.compare("N") == 0 || input.compare("n") == 0 ) {
        mantenimiento_notificado = "FALSE";
      } else {
        mantenimiento_notificado = "TRUE";
      }
      cout << "   Estado*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_estado = input;
      }
    }
  }
  void formulario_mantenimientos_completo(bool nuevo, string auto_id) {
    string input;
    cout << "\n";

    if (nuevo == true) {
      mantenimiento_auto = auto_id;
      lista_tipos_mantenimiento();
      cout << "   Tipo de mantenimiento*: ";
      getline(cin, input);
      getline(cin, input); // Duplicado para arreglar error de valores por defecto
      if ( !input.empty() ) {
        mantenimiento_tipo = input;
      }
      cout << "   Fecha Agenda (YYYY-mm-dd)*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_fecha_agenda = input;
      }
      cout << "   Km Estimado*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_km_estimado = input;
      }
      input = "n";
      mantenimiento_notificado = "FALSE";
      mantenimiento_estado = "Pendiente";
    } else {
      mantenimiento_auto = auto_id;
      lista_tipos_mantenimiento();
      cout << "   Tipo de mantenimiento*: ";
      getline(cin, input);
      getline(cin, input); // Duplicado para arreglar error de valores por defecto
      if ( !input.empty() ) {
        mantenimiento_tipo = input;
      }
      mantenimiento_costo = "NULL";
      cout << "   Costo*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_costo = input;
      }
      cout << "   Fecha Agenda (YYYY-mm-dd)*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_fecha_agenda = input;
      }
      cout << "   Km Estimado*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_km_estimado = input;
      }
      mantenimiento_fecha_revision = mantenimiento_fecha_agenda;
      cout << "   Fecha Revision (YYYY-mm-dd)*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_fecha_revision = input;
      }
      mantenimiento_km_revision = "NULL";
      cout << "   Km Revision*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_km_revision = input;
      }
      cout << "   Proveedor*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_proveedor = input;
      }
      input = "n";
      cout << "   Notificado? y/n*: ";
      getline(cin, input);
      if ( input.compare("N") == 0 || input.compare("n") == 0 ) {
        mantenimiento_notificado = "FALSE";
      } else {
        mantenimiento_notificado = "TRUE";
      }
      cout << "   Estado*: ";
      getline(cin, input);
      if ( !input.empty() ) {
        mantenimiento_estado = input;
      }
    }
  }

  void lista_tipos_mantenimiento() {
    cout << "\n     Tipos de mantenimiento";
    cout << "\n     [1] Cambio de bandas";
    cout << "\n     [2] Cambio de aceite y filtros";
    cout << "\n     [3] Inspección de líquidos";
    cout << "\n     [4] Alineación y balanceo";
    cout << "\n     [5] Inspección de frenos";
    cout << "\n\n";
  }

  string tipos_mantenimiento_to_s(string tipo) {
    int i_tipo;
    i_tipo = atoi(tipo.c_str());
    switch(i_tipo) {
      case 1:
        return "Cambio de bandas";
      break;
      case 2:
        return "Cambio de aceite y filtros";
      break;
      case 3:
        return "Inspección de líquidos";
      break;
      case 4:
        return "Alineación y balanceo";
      break;
      case 5:
        return "Inspección de frenos";
      break;
    }
  } 
