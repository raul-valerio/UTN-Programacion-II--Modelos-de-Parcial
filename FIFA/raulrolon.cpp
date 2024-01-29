#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
#include "parcial.h"

///Generar un archivo con el código y el nombre del jugador, el nombre del país al
///que pertenece, y la cantidad de goles convertidos. En el archivo sólo deben
///aparecer los jugadores que hicieron goles, sin tener en cuenta los goles en contra.


class JugadorGol {
 private:
        char codigoJugador[5];
        char nombreJugador[30];
        char nombrePais[30];
        int cantidadGoles;
 public:
    void setCodigoDeJugador(const char* cod) { strcpy(codigoJugador, cod);}
    void setNombreDeJugador(const char* nom) { strcpy(nombreJugador, nom);}
    void setNombrePais(const char* nomp) { strcpy(nombrePais, nomp);}
    void setCantidadGoles(int goles){cantidadGoles=goles;};

    int getCantidadGoles(){return cantidadGoles;}
    const char* getCodigoJugador(){return codigoJugador;}

    bool escribirRegistro(JugadorGol reg){
        FILE *p;
        p=fopen("puntoA.dat", "ab");
        if(p==NULL) return false;
        bool escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }
    void mostrar(){


    }
    int contarRegistros(){
        FILE *p;
        p=fopen("puntoA", "rb");
        if(p==NULL) return -1;
        fseek(p, 0,2);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(JugadorGol);
    }


};

////////////////PROTOTIPOS///////////////

void puntoA();
int contarGoles(const char *cod);
const char *traerNombreDePais(int cod);

/////////////////////////////////////////


int main(){

puntoA();

return 0;
}

//////////////////////////////////////

int contarGoles(const char *cod){
 Gol reg;
 int pos=0;
 int contador=0;

 while(reg.leerDeDisco(pos++)){
    if(strcmp(reg.getCodigoJugador(),cod) == 0 && reg.getTipo()!=2){
        contador++;
    }
 }
 return contador;
}

const char *traerNombreDePais(int cod){

 Pais reg;
 int pos=0;

 while(reg.leerDeDisco(pos++)){
    if(cod==reg.getCodigoPais()){
        return reg.getNombrePais();
    }
 }
 return "NO EXISTE";
}


void puntoA(){

Jugador reg;
JugadorGol aux;
int cantGoles;
int pos=0;
while(reg.leerDeDisco(pos++)){
    cantGoles=contarGoles(reg.getCodigoJugador());

    if(cantGoles>0){
            aux.setCodigoDeJugador(reg.getCodigoJugador());
            aux.setNombreDeJugador(reg.getNombreJugador());
            aux.setNombrePais(traerNombreDePais(reg.getCodigoPais()));
            aux.setCantidadGoles(cantGoles);
            aux.escribirRegistro(aux);
    }
}
}


///Informar los datos del jugador que más cantidad de goles a favor convirtió.
///se usa la misma clase que la anterior al igual de la funcioón.

////////////////PROTOTIPOS///////////////

void puntoB();


////////////////////////////////////////

void puntoB(){
 JugadorGol reg, aux;
 int golesMax=0;
 int cant;
 cant=reg.contarRegistros();
 for(int i=0; i<cant; i++){
    if(reg.getCantidadGoles()>golesMax){
            golesMax=contarGoles(reg.getCodigoJugador());
            aux=reg;
        }
 }
 aux.mostrar();


}
