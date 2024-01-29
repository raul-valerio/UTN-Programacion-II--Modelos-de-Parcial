#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
#include "parcial1l.h"


///A-Generar un archivo con los equipos que tengan al menos 10 (2) jugadores inscriptos.
///Cada registro debe tener el ID de equipo, el nombre del equipo, y la categoría del deporte al que pertenece el equipo.

class EquipoInscriptos {
    private:
        int IdEquipo, idCategoria;
        char nombre[30];
        bool estado;
    public:

        void setIdEquipo(int id){IdEquipo = id;}
        void setIdCategoria(int ic){idCategoria = ic;}
        void setNombre(const char* nom){strcpy(nombre, nom);}
        void setEstado(bool e){estado=e;}

        void Mostrar(){
        cout << "ID DE EQUIPO: " << IdEquipo << endl;
        cout << "NOMBRE: " << nombre << endl;
        cout << "ID CATEGORIA DEPORTE: " << idCategoria << endl;
        }
};

class ArchivoEquipoInscriptos {

private:
    char nombre[30];
public:
    ArchivoEquipoInscriptos(const char *n){
        strcpy(nombre, n);
    }
    EquipoInscriptos leerRegistro(int pos){
        EquipoInscriptos reg;
        reg.setEstado(false);
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof reg*pos,0);
        fread(&reg, sizeof reg,1, p);
        fclose(p);
        return reg;
    }
    int contarRegistros(){
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return -1;
        fseek(p, 0,2);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(EquipoInscriptos);
    }
    bool escribirRegistro(EquipoInscriptos reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }
    bool listarArchivo(){
        EquipoInscriptos reg;
        FILE *p;
        p = fopen(nombre, "rb");
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
    if(id==reg.getIdEquipo() && reg.getEstado()){
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

void puntoA(){
  Equipo reg;
  ArchivoEquipos archi("equipos.dat");

  int cant, cantJugadores;
  cant=archi.contarRegistros();

  EquipoInscriptos aux;
  ArchivoEquipoInscriptos archiF("puntoA1.dat");

  for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    cantJugadores= contarJugadores(reg.getIdEquipo());

    if(cantJugadores>=2){
        aux.setNombre(reg.getNombre());
        aux.setIdEquipo(reg.getIdEquipo());
        aux.setIdCategoria(traeCategoria(reg.getIdEquipo()));
        archiF.escribirRegistro(aux);
    }
  }

}

///B-Hacer un vector dinámico para listar el archivo del punto anterior.


void puntoB(){

    EquipoInscriptos *v;
    ArchivoEquipoInscriptos archi("puntoA1.dat");

    int cantReg;
    cantReg=archi.contarRegistros();
    if(cantReg==0){
        cout<<"NO HAY REGISTROS EN EL ARCHIVO"<<endl;
        return;
    }
    v=new EquipoInscriptos[cantReg];
    if(v==NULL) return;
    for(int i=0;i<cantReg;i++){
            v[i]=archi.leerRegistro(i);
    }
    for(int i=0;i<cantReg;i++){
        v[i].Mostrar();
    }
    delete v;
}

///C-Sobrecargar el operador == para comparar un objeto Jugador con un objeto Deporte.
///Debe devolver verdadero cuando coinciden los Id de deporte
///debe ir en la clase JUGADOR

/*
bool operator ==(Deporte &obj){
   if(idDeporte==obj.getIdDeporte()) return true;
    return false;

}

*/


/////////MAIN////////
int main() {


    /*puntoA();
    ArchivoEquipoInscriptos archi("puntoA1.dat");
    archi.listarArchivo();*/
    puntoB();

    return 0;
}
////////////////////

///PROBADO Y FUNCIONAN TODOS LOS PUNTOS
