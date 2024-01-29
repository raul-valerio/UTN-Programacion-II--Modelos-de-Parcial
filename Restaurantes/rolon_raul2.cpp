#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
#include "parcial2.h"

///Generar un archivo con el dni cliente, el nombre y el importe total

class ClienteImporte{
private:
    int DNI;
    char nombre[30];
    float totalImporte;

public:
    void setDNI(int d){DNI=d;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setTotalImporte(float imp){totalImporte=imp;}

    ////////////////////////
    void Mostrar() {
        cout <<DNI << endl;
        cout <<nombre << endl;
        cout << totalImporte<< endl;
    }
    bool grabarRegistro(ClienteImporte reg){
            FILE *p;
            p=fopen("puntoD.dat", "ab");
            if(p==NULL) return false;
            int escribio=fwrite(&reg, sizeof reg,1, p);
            fclose(p);
            return escribio;
        }
    bool listarArchivo(){
        ClienteImporte reg;
        FILE *p;
        p = fopen("puntoD.dat", "rb");
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

////////PROTOTIPOS////////////
void puntoD();
float sumarImporte(int id);
void puntoE();
void puntoF();

/////////////MAIN/////////////
int main(){

puntoF();
/*puntoD();
puntoE();*/

return 0;
}
/////////////////////////////
float sumarImporte(int id){
Venta reg;
ArchivoVentas archi("ventas.dat");
int cant=archi.contarRegistros();

float acum=0;

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    if(id==reg.getDNI()){
        acum+=reg.getImporte();
    }
}
return acum;
}


void puntoD(){
Cliente reg;
ArchivoClientes archi("clientes.dat");
int cant=archi.contarRegistros();

float importeTotal=0;

ClienteImporte aux;

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    if(reg.getEstado()){
        importeTotal=sumarImporte(reg.getDNI());
        if(importeTotal>0){
            aux.setDNI(reg.getDNI());
            aux.setNombre(reg.getNombre());
            aux.setTotalImporte(importeTotal);
            aux.grabarRegistro(aux);
        }
    }
}

aux.listarArchivo();

}
///Informar el cliente mas joven (menor edad) y de mayor edad

void puntoE(){

Cliente reg;
ArchivoClientes archi("clientes.dat");
int cant=archi.contarRegistros();

int DNImin;
char nombreMin[30];

int DNImax;
char nombreMax[30];

int edadMin=1000;
int edadMax=1;

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    if(reg.getEdad()<edadMin){
        edadMin=reg.getEdad();
        DNImin=reg.getDNI();
        strcpy(nombreMin,reg.getNombre());
    }
    if(reg.getEdad()>edadMax){
        edadMax=reg.getEdad();
        DNImax=reg.getDNI();
        strcpy(nombreMax,reg.getNombre());
    }
}


cout<<"EL DNI DEL CLIENTE DE MENOR EDAD ES: "<<DNImin<<" EL NOMBRE: "<<nombreMin<<" EDAD: "<<edadMin<<endl;
cout<<"EL DNI DEL CLIENTE DE MAYOR EDAD ES: "<<DNImax<<" EL NOMBRE: "<<nombreMax<<" EDAD: "<<edadMax<<endl;

}

///Hacer un vector dinamico con las ventas y mostrar las ventas totales de un restauran ingresado por teclado
void puntoF(){

ArchivoVentas archi("ventas.dat");
int cant=archi.contarRegistros();

Venta *v;
v=new Venta[cant];
if(v==NULL) return;
for(int i=0; i<cant; i++){
    v[i]=archi.leerRegistro(i);
}
cout<<"INGRESE EL NUMERO DEL RESTAURANTE: "<<endl;
int cod;
cin>>cod;

for(int i=0; i<cant; i++){
    if(cod==v[i].getCodigoRestaurante()){
        v[i].Mostrar();
    }
}

}
