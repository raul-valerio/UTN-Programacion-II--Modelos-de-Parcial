#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
#include "parcial2.h"


class RestauranteCat {

private:
    int codigoRestaurante;
    char nombre[30];
    int cantidadVenta;
public:
    void setCodigoRestaurante(int c){codigoRestaurante=c;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setCantidadVentas(int ca){cantidadVenta=ca;}

    int getCodigoRestaurante(){return codigoRestaurante;}

    void Mostrar(){
        cout<<codigoRestaurante<<endl;
        cout<<nombre<<endl;
        cout<<cantidadVenta<<endl;
    }

    bool grabarRegistro(RestauranteCat reg){
            FILE *p;
            p=fopen("puntoA.dat", "ab");
            if(p==NULL) return false;
            int escribio=fwrite(&reg, sizeof reg,1, p);
            fclose(p);
            return escribio;
        }
    bool listarArchivo(){
        RestauranteCat reg;
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
        ////PUNTO C////////
        bool operator==(const RestauranteCat &obj){
            if(codigoRestaurante==obj.getCodigoRestaurante()) return true
            return false;

        }
};

class ArchivoRestauranteCat {
private:
    char nombre[30];
public:
    ArchivoRestauranteCat(const char *n){
        strcpy(nombre, n);
    }
    RestauranteCat leerRegistro(int pos){
        RestauranteCat reg;
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof(RestauranteCat)*pos,0);
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
        return tam/sizeof(RestauranteCat);
    }
};

//////PROTOTIPOS///////////
void puntoA();
int contarVentas(int id);
void puntoB();
void puntoC();



/////////MAIN////////////
int main(){

puntoC();

/*puntoB();
puntoA();
puntoB();
puntoC();*/




return 0;
}

int contarVentas(int id){

Venta reg;
ArchivoVentas archi("ventas.dat");
int cant=archi.contarRegistros();
int contador=0;

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i); //leer archivo
    if(id==reg.getCodigoRestaurante() && reg.getEstado() && reg.getFechaReserva().getAnio()==2022){
        contador++;
    }
}//fin lectura registro ventas

 return contador;
}

void puntoA(){

Restaurante reg;
ArchivoRestaurantes archi("restaurantes.dat");
int cant=archi.contarRegistros();
int ventas=0;
RestauranteCat aux;

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    if(reg.getEstado() && reg.getCategoria()==2){
        ventas=contarVentas(reg.getCodigoRestaurante());
        aux.setCodigoRestaurante(reg.getCodigoRestaurante());
        aux.setNombre(reg.getNombre());
        aux.setCantidadVentas(ventas);
        aux.grabarRegistro(aux);
    }

} ///fin lectura archivo restaurante

aux.listarArchivo();
}

void puntoB(){

Restaurante reg;
ArchivoRestaurantes archi("restaurantes.dat");
int cant=archi.contarRegistros();
int vProv[24]={0};

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    if(reg.getEstado() && reg.getCategoria()==1){
        vProv[reg.getProvincia()-1]++;
    }
}//fin lectura archivo

int minimo = vProv[0];
int prov=0;
for(int i=1; i<24; i++) {
        if (vProv[i]<minimo) {
            minimo = vProv[i];
            prov=i+1;
        }
}

cout<<"LA PROVINCIA ES : "<<prov<<endl;

}

void puntoC(){

RestauranteCat *v;
ArchivoRestauranteCat archi("puntoA.dat");
int cant=archi.contarRegistros();

v=new RestauranteCat[cant];
if(v==NULL) return;
for(int i=0; i<cant; i++){
    v[i]=archi.leerRegistro(i);
}
for(int i=0; i<cant; i++){
    v[i].Mostrar();
}
delete v;

}
