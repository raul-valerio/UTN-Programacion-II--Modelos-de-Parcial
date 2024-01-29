#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
#include "parcial2.h"



class Proveedor2023 {

private:
    int numeroProveedor;
    char nombre[30];
    int provincia;
    bool activo;
public:
    int getNumeroProveedor(){return numeroProveedor;}
    int getProvincia(){return provincia;}
    const char *getNombre(){return nombre;}
    bool getActivo(){return activo;}

    void setNumeroProveedor(int np){numeroProveedor=np;}
    void setProvincia(int np){provincia=np;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setActivo(bool a){activo=a;}

    void Mostrar(){
        cout<<numeroProveedor<<endl;
        cout<<nombre<<endl;
        cout<<provincia<<endl;
    }

    bool grabarRegistro(Proveedor2023 reg){
            FILE *p;
            p=fopen("puntoA.dat", "ab");
            if(p==NULL) return false;
            int escribio=fwrite(&reg, sizeof reg,1, p);
            fclose(p);
            return escribio;
        }
    bool listarArchivo(){
        Proveedor2023 reg;
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
};


////////////////////////////////
void puntoA();
bool compro2023(int cod);
void puntoB();
void puntoC();
void puntoD();


///////////////////////////////
int main(){

   puntoD();

return 0;
}
//////////////////////////////

///Generar un archivo con los proveedores a los que no se les haya hecho compras el año actual.
///Por cada proveedor al que no se le hayan hecho compras este año
///se debe registrar el número de proveedor, el nombre del proveedor y la provincia del proveedor.

bool compro2023(int cod){

Compra reg;
ArchivoCompras archi("compras.dat");

int cant=archi.contarRegistros();

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    if(cod==reg.getNumeroproveedor() && reg.getFechaCompra().getAnio()==2023 && reg.getActivo()) {
        return false;
    }
}
return true;

}

void puntoA (){

Proveedor reg;
ArchivoProveedores archi("proveedores.dat");
int cant=archi.contarRegistros();

Proveedor2023 aux;

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    if(compro2023(reg.getNumeroProveedor()) && reg.getActivo()){
        aux.setNombre(reg.getNombre());
        aux.setNumeroProveedor(reg.getNumeroProveedor());
        aux.setProvincia(reg.getProvincia());
        aux.setActivo(true);
        aux.grabarRegistro(aux);

    }
}
}
///El estado de ejecución con más obras.
void puntoB(){

Obra reg;
ArchivoObras archi("obras.dat");
int vEstado[5]={0};


int cant=archi.contarRegistros();
for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
        vEstado[reg.getEstadoEjecucion()-1]++;
}
int maximo=vEstado[0];
for(int i=1; i<5; i++){
    if(vEstado[i]>maximo){
        maximo=vEstado[i];
    }
}
cout<<"El estado con mas ejecucion de obra es: "<<maximo<<endl;
}

///Generar un vector dinámico con todos los materiales y listar luego los materiales
///del vector que pertenezcan a una marca que se ingresa por teclado.
void puntoC(){

Material *v;
ArchivoMateriales archi("materiales.dat");
int cant=archi.contarRegistros();

v=new Material[cant];
if(v==NULL) return;
for(int i=0; i<cant; i++){
    v[i]=archi.leerRegistro(i);
}
cout<<"INGRESE LA MARCA DEL MATERIAL A LISTAR: "<<endl;
char marca[30];
cargarCadena(marca,29);
for(int i=0; i<cant; i++){
    if(strcmp(marca,v[i].getMarca()) == 0){
        v[i].Mostrar();
    }
}

delete v;

}


///Sobrecargar el operador < para la clase Obra de manera tal que sea verdadero cuando el objeto que llama al método
///tenga un valor de superficie menor a un valor de tipo float que se recibe como parámetro.
///Nota: dejar el código comentado en el cpp que se entrega para evitar problemas de compilación.

/*
bool operator < (float v){
    if(superficie<v) return true;
    return false;
}
*/

///El tipo de material con menos cantidad de materiales (ignorando los tipos sin materiales)
void puntoD(){

Material reg;
ArchivoMateriales archi("materiales.dat");
int cant=archi.contarRegistros();
int vTipos[6]={0};


for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    vTipos[reg.getTipo()-1]++;
}

int minimo = 1;
int vMinimo[6]={0};

for(int i=0; i<6; i++) {
        if (vTipos[i]<=minimo && vTipos[i]!=0) {
            minimo = vTipos[i];
            vMinimo[i]=1;
        }
}
for(int i=0; i<6; i++){
    if(vMinimo[i]==1){
        cout<<"El tipo de material con menos cantidad de materiales (ignorando los tipos sin materiales)es : "<<i+1<<endl;
    }
}
}
