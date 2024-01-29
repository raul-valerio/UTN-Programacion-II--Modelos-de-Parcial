#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
#include "parcial2.h"

///Generar un archivo con el nombre del restaurante,categoria y edad promedio de cliente

class RestauranteEdad{
private:

    char nombre[30];
    int categoria;
    float promEdad;

public:

    void setNombre(const char *n){strcpy(nombre,n);}
    void setCategoria(int c){categoria=c;}
    void setPromEdad(float e){promEdad=e;}

    ////////////////////////
    void Mostrar() {

        cout <<nombre << endl;
        cout <<categoria << endl;
        cout << promEdad<< endl;
    }
    bool grabarRegistro(RestauranteEdad reg){
            FILE *p;
            p=fopen("puntoG.dat", "ab");
            if(p==NULL) return false;
            int escribio=fwrite(&reg, sizeof reg,1, p);
            fclose(p);
            return escribio;
        }
    bool listarArchivo(){
        RestauranteEdad reg;
        FILE *p;
        p = fopen("puntoG.dat", "rb");
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
void puntoG();
int traerCliente(int id);


/////////////MAIN/////////////
int main(){

puntoG();

return 0;
}
/////////////////////////////
int traerEdad(int id){
Cliente reg;
ArchivoClientes archi("clientes.dat");
int cant=archi.contarRegistros();

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    if(id==reg.getDNI()){
        return reg.getEdad();
    }
}
return 0;
}

float sacarPromedio(int id){
Venta reg;
ArchivoVentas archi("ventas.dat");
int cant=archi.contarRegistros();

int edad=0;
float contador=0;

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    if(id==reg.getCodigoRestaurante()){
        edad+=traerEdad(reg.getDNI());
        contador++;
    }
}
return edad/contador;
}


void puntoG(){

Restaurante reg;
ArchivoRestaurantes archi("restaurantes.dat");
int cant=archi.contarRegistros();

float prom=0;

RestauranteEdad aux;

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    prom=sacarPromedio(reg.getCodigoRestaurante());
    if(prom>0){
        aux.setCategoria(reg.getCategoria());
        aux.setNombre(reg.getNombre());
        aux.setPromEdad(prom);
        aux.grabarRegistro(aux);
    }

}

aux.listarArchivo();

}
