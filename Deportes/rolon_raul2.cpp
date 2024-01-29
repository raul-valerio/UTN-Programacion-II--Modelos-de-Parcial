#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
#include "parcial1l.h"


///PUNTO 2
///A- Hacer un archivo con los deportes que tengan jugadores de todos los claustros.
///Los registros del archivo nuevo deben tener el mismo formato que el archivo de deportes.

//////PROTOTIPOS////////////

void puntoA();
bool contarDeportes(int id);
void puntB();

/////////MAIN//////////////
int main() {

    /*puntoA();
    ArchivoDeportes archi("DeportesA.dat");
    archi.listarArchivo();*/
    puntB();

    return 0;
}
///////////////////////////
///FUNCIONAN TODOS LOS PUNTOS


void puntoA(){

cout<<"-----------#################-------"<<endl;

Deporte reg;
ArchivoDeportes archi("deportes.dat");
ArchivoDeportes archiNuevo("deportesA.dat");

int cantReg=archi.contarRegistros();
bool estanTodos=false;


for(int i=0; i<cantReg; i++){
    reg=archi.leerRegistro(i);
    if(reg.getEstado()){
        estanTodos=contarDeportes(reg.getIdDeporte());
    }
    if(estanTodos==true){
           archiNuevo.grabarRegistro(reg);
    }
}
}


bool contarDeportes(int id){

Jugador reg;
ArchivoJugadores archi("jugadores.dat");

int cantReg, vClaustro[4]={0};
cantReg=archi.contarRegistros();

for(int i=0; i<cantReg; i++){
    reg=archi.leerRegistro(i);
    if(id==reg.getIdDeporte() && reg.getEstado()){
            vClaustro[reg.getClaustro()-1]=1;
    }
}

int cont=0;
for(int i=0; i<4; i++){
        cont+=vClaustro[i];
}
if(cont==2)return true;
return false;

}

///B- Crear un vector dinámico con los equipos de nivel inicial. Listar el vector.

void puntB(){

const int NIVEL=1; ///Nivel 1: inicial; 2: intermedio; 3: avanzado
Equipo reg;
ArchivoEquipos archi("equipos.dat");

int cantReg =archi.contarRegistros();
int contador=0;

for(int i=0; i<cantReg; i++){
    reg=archi.leerRegistro(i);
    if(reg.getEstado() && reg.getNivel()==NIVEL){
            contador++;
    }
}///fin lectura registro
Equipo *p;
p=new Equipo[contador];
if(p==NULL) return;

int j=0;
for(int i=0; i<cantReg; i++){
    reg=archi.leerRegistro(i);
    if(reg.getEstado() && reg.getNivel()==NIVEL){
            p[j]=archi.leerRegistro(i); ///graba el registro en el vector
            j++;

    }
}//fin lectura registro

for(int i=0; i<contador; i++){
    p[i].Mostrar();
    cout<<"----------"<<endl;
}
delete p;
}

///C- Sobrecargar el operador == para la clase Jugador, que reciba un valor entero y lo compare con el Id de claustro
/*
void operator == (int id){
   claustro==id;

}
*/





