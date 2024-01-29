#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
#include "parcial1l.h"

///PUNTO C
///1-Generar un archivo con los jugadores que hayan pagado más de $100 de matrícula y que se hayan inscripto este año.
///Cada registro del archivo debe tener el siguiente formato:
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
///////////////////PROTOTIPOS///////////////

const char *traerNombre(int id);
void puntoC();
void puntoC2();


///////////////MAIN ////////////////////////

int main() {

    puntoC2();


    return 0;
}
///////////////////////////////////////////

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

///2- Crear un vector con los jugadores pertenecientes a un equipo cuyo número de equipo se ingresa por teclado.
///Listar el vector

void puntoC2(){

Jugador *p;
int idEq;
cout<<"Ingrese el numero del equipo"<<endl;
cin>>idEq;
Jugador reg;
ArchivoJugadores archi("jugadores.dat");
int cantReg=archi.contarRegistros();
int contador=0;
for(int i=0; i<cantReg; i++){
    reg=archi.leerRegistro(i);
    if(idEq==reg.getIdEquipo()){
        contador++;
    }
}
cout<<"TAMAÑO DE VECTOR: "<<contador<<endl;

p=new Jugador[contador];
if(p==NULL) return;
int j=0;
for(int i=0; i<cantReg; i++){
    reg=archi.leerRegistro(i);
    if(idEq==reg.getIdEquipo()){
        p[j]=archi.leerRegistro(i);
        j++;
    }
}

for(int i=0; i<contador; i++){
    p[i].Mostrar();
    cout<<"-----------"<<endl;
}

 delete p;


}

///3-Agregar una sobrecarga para el operador > de la clase Jugador de manera tal que sea verdadero cuando
///el año de inscripción sea mayor a un valor de año que se recibe cmo parámetro.
/// VA EN LA CLASE JUGADOR

/*
 bool operator>(int a){
  if(inscripcion.anio>a) return true;
  return false;
}

*/


