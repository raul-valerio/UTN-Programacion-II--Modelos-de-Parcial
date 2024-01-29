#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
#include "parcial1l.h"


///PUNTO B
///Generar un archivo con los deportes de categoría 2 que tengan 2 o mas ALUMNOS inscriptos.
///Cada registro del archivo nuevo debe tener el siguiente formato:
///Id de deporte, nombre, año de origen y cantidad de NO DOCENTES inscriptos
/// similar al del parcial:
///Generar un archivo con los deportes de categoría 5 que tengan más de 50 docentes inscriptos.
///Cada registro del archivo nuevo debe tener el siguiente formato:
///Id de deporte, nombre, año de origen y cantidad de alumnos inscriptos

class DeporteJugador{
 private:
    int idDeporte, anioOrigen;
    char nombre[30];
    int cantInscriptos;
 public:
     int getIdDeporte(){return idDeporte;};
     int getAnioOrigen(){return anioOrigen;};
     const char *getNombre(){return nombre;};
     int  setCantInscriptos(){return cantInscriptos;};

     void setIdDeporte(int id){idDeporte=id;};
     void setAnioOrigen(int a){anioOrigen=a;};
     void setNombre(const char* nom){strcpy(nombre, nom);};
     void setCantInscriptos(int cant){cantInscriptos=cant;};

     void Mostrar(){
        cout << "ID DE DEPORTE: " << idDeporte << endl;
        cout << "NOMBRE: " << nombre << endl;
        cout << "AÑOR ORIGEN: " << anioOrigen << endl;
        cout << "CANTIDAD INSCRITOS: " << cantInscriptos << endl;

    }
     bool escribirRegistro(DeporteJugador reg){
        FILE *p;
        p=fopen("puntoB.dat", "ab");
        if(p==NULL) return false;
        bool escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }

    bool listarArchivo(){
        DeporteJugador reg;
        FILE *p;
        p = fopen("puntoB.dat", "rb");
        if (p == NULL){
        cout << "No se pudo abrir " << endl;
        return false;
        }
        while (fread(&reg, sizeof(reg), 1, p)==1){
        reg.Mostrar();
        cout << endl;
        }
        fclose(p);
        return true;
        }



};

int contarClaustro(int id, int c);

///////////////////////
int contarClaustro(int id, int c){
   Jugador reg;
   ArchivoJugadores archi("jugadores.dat");

   int cant, contador;
   contador=0;
   cant=archi.contarRegistros();

   for(int i=0; i<cant; i++){
        reg=archi.leerRegistro(i);
        if(id==reg.getIdDeporte() && reg.getClaustro()==c){
            contador++;
        }
   }
   return contador;
}


void puntoB(){
 Deporte reg;
 ArchivoDeportes archi("deportes.dat");

 int cant, contAlu;
 cant=archi.contarRegistros();

 DeporteJugador aux;

 for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    contAlu=contarClaustro(reg.getIdDeporte(),2);
    if(contAlu>=2){
        aux.setIdDeporte(reg.getIdDeporte());
        aux.setNombre(reg.getNombre());
        aux.setAnioOrigen(reg.getAnioOrigen());
        aux.setCantInscriptos(contarClaustro(reg.getIdDeporte(),3));
        aux.escribirRegistro(aux);
    }
 }
}

///PUNTO A
//Generar un archivo con los equipos que tengan al menos 10 (2) jugadores inscriptos.
//Cada registro debe tener el ID de equipo, el nombre del equipo, y la categoría del deporte al que pertenece el equipo.
///PUNTO A2
///Hacer un vector dinámico para listar el archivo del punto anterior.
///PUNTO A3
///Sobrecargar el operador == para comparar un objeto Jugador con un objeto Deporte.
///Debe devolver verdadero cuando coinciden los Id de deporte


class EquipoInscriptos {
    private:
        int IdEquipo, idCategoria;
        char nombre[30];
    public:

        void setIdEquipo(int id){IdEquipo = id;}
        void setIdCategoria(int ic){idCategoria = ic;}
        void setNombre(const char* nom){strcpy(nombre, nom);}

        void Mostrar(){
        cout << "ID DE EQUIPO: " << IdEquipo << endl;
        cout << "NOMBRE: " << nombre << endl;
        cout << "ID CATEGORIA DEPORTE: " << idCategoria << endl;
        }

        bool escribirRegistro(EquipoInscriptos reg){
        FILE *p;
        p=fopen("puntoA.dat", "ab");
        if(p==NULL) return false;
        bool escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }

     bool listarArchivo(){
        EquipoInscriptos reg;
        FILE *p;
        p = fopen("puntoA.dat", "rb");
        if (p == NULL){
        cout << "No se pudo abrir " << endl;
        return false;
        }
        while (fread(&reg, sizeof(reg), 1, p)==1){
        reg.Mostrar();
        cout << endl;
        }
        fclose(p);
        return true;
        }

        int contarRegistros(){
        FILE *p;
        p=fopen("puntoA", "rb");
        if(p==NULL) return -1;
        fseek(p, 0,2);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(EquipoInscriptos);
        }

};

////////////////
void puntoA();
int contarJugadores(int id);
int traeCategoria(int id);

////////////////////////////////
int contarJugadores(int id){
Jugador reg;
ArchivoJugadores archi("jugadores.dat");

int cant, contador;
contador=0;
cant=archi.contarRegistros();

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    if(id==reg.getIdEquipo()){
        contador++;
    }
}
return contador;

}

int traeCategoria(int id){
   Jugador reg1;
   Deporte reg2;

   ArchivoJugadores archi1("jugadores.dat");
   ArchivoDeportes archi2("deportes.dat");

   int cantRegJugadores, cantRegDeportes, valor;

   cantRegJugadores=archi1.contarRegistros();
   cantRegDeportes=archi2.contarRegistros();

   for(int i=0; i<cantRegJugadores; i++){
     reg1=archi1.leerRegistro(i);
     for(int j=0; j<cantRegDeportes; j++){
            reg2=archi2.leerRegistro(j);
        if(id==reg1.getIdEquipo() && reg1.getIdDeporte()==reg2.getIdDeporte()){
            valor=reg2.getIdCtegoria();
        }
     }
   }
   return valor;
}
void PRUEBA(){
  /*Equipo reg;
  ArchivoEquipos archi("equipos.dat");

  int cant, valor;
  cant=archi.contarRegistros();

  for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    valor=contarJugadores(reg.getIdEquipo());
    cout<<reg.getNombre()<<": "<<valor<<endl;
  }

  Equipo reg;
  ArchivoEquipos archi("equipos.dat");

  int cant, valor;
  cant=archi.contarRegistros();

  for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    valor=traeCategoria(reg.getIdEquipo());
    cout<<reg.getNombre()<<": "<<valor<<endl;
  }
*/
}
void puntoA(){
  Equipo reg;
  ArchivoEquipos archi("equipos.dat");

  int cant, cantJugadores;
  cant=archi.contarRegistros();

  EquipoInscriptos aux;

  for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    cantJugadores= contarJugadores(reg.getIdEquipo());

    if(cantJugadores>=2){
        aux.setNombre(reg.getNombre());
        aux.setIdEquipo(reg.getIdEquipo());
        aux.setIdCategoria(traeCategoria(reg.getIdEquipo()));
        aux.escribirRegistro(aux);
    }
  }

}


///PUNTO C
///Generar un archivo con los jugadores que hayan pagado más de $100 de matrícula y que se hayan inscripto este año.
//Cada registro del archivo debe tener el siguiente formato:
///DNI, nombre, apellido, claustro y nombre del deporte.

class JugadorMatricula{

private:
    int DNI, claustro;
    char nombre[25], apellido[30], nombreD[30];
    bool estado;
public:

    void setDNI(int d){DNI = d;}
    void setClaustro(int c){claustro = c;}
    void setNombre(const char* nom){strcpy(nombre, nom);}
    void setApellido(const char* ap){strcpy(apellido, ap);}
    void setNombreD(const char* nomd){strcpy(nombreD, nomd);}
    void setEstado(bool e){estado=e;}

   void Mostrar(){
       cout<<"DNI: "<<DNI<<endl;
        cout<<"CLAUSTRO: "<<claustro<<endl;
        cout<<"NOMBRE: "<<nombre<<endl;
        cout<<"APELLIDO: "<<apellido<<endl;
        cout<<"NOMBRE DEL DEPORTE: "<<nombreD<<endl;
   }

   bool escribirRegistro(JugadorMatricula reg){
        FILE *p;
        p=fopen("puntoC.dat", "ab");
        if(p==NULL) return false;
        bool escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }

     bool listarArchivo(){
        JugadorMatricula reg;
        FILE *p;
        p = fopen("puntoC.dat", "rb");
        if (p == NULL){
        cout << "No se pudo abrir " << endl;
        return false;
        }
        while (fread(&reg, sizeof(reg), 1, p)==1){
        reg.Mostrar();
        cout << endl;
        }
        fclose(p);
        return true;
        }

};


const char *traerNombre(int id){
  Deporte reg;
  ArchivoDeportes archi("deportes.dat");

  int cant;
  cant=archi.contarRegistros();

  for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    if(id==reg.getIdDeporte()){
        return (reg.getNombre());

    }
  }
 return "no exite";
}

void puntoC(){

    Jugador reg;
    ArchivoJugadores archi("jugadores.dat");

    int cant;
    cant=archi.contarRegistros();

    JugadorMatricula aux;

    for(int i=0; i<cant; i++){
        reg=archi.leerRegistro(i);
        if(reg.getMatricula()>100){

            aux.setDNI(reg.getDNI());
            aux.setNombre(reg.getNombre());
            aux.setApellido(reg.getApellido());
            aux.setClaustro(reg.getClaustro());
            aux.setNombreD(traerNombre(reg.getIdDeporte()));
            aux.escribirRegistro(aux);
        }

    }

}



/////////MAIN////////
int main() {

    puntoA2();


    return 0;
}
////////////////////
