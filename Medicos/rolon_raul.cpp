#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
#include "parcial2.h"

class SocioImporte{
private:
    char codigoSocio[5];
    char nombre[30];
    Fecha fechaTurno;
    bool estado;
public:

    void Mostrar(){
        cout<<codigoSocio<<endl;
        cout<<nombre<<endl;
        fechaTurno.Mostrar();
    }


    void setCodigoSocio(const char *cs){strcpy(codigoSocio,cs);}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setEstado(bool a){estado=a;}
    void setFechaTurno(Fecha t){fechaTurno=t;};

    const char *getCodigoSocio(){return codigoSocio;}
    const char *getNombre(){return nombre;}
    bool getEstado(){return estado;}
    Fecha getFechaTurno(){return fechaTurno;};

    bool grabarRegistro(SocioImporte reg){
        FILE *p;
        p=fopen("puntoA.dat", "ab");
        if(p==NULL) return false;
        bool escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }

};

class ArchivoSocioImporte{
private:
     char nombre[30];
public:
    ArchivoSocioImporte(const char *n){
        strcpy(nombre, n);
    }
    SocioImporte leerRegistro(int pos){
        SocioImporte reg;
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof(SocioImporte)*pos,0);
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
        return tam/sizeof(SocioImporte);
    }
    bool listarArchivo(){
        SocioImporte reg;
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
////////PROTOTIPOS////////
void puntoA();
     Fecha traerFecha(const char *cod);
void puntoB();

///////MAIN///////////////
int main(){
/*puntoA();
ArchivoSocioImporte archi("puntoA.dat");
archi.listarArchivo();*/
puntoB();

return 0;
}
/////////////////////////
Fecha traerFecha(const char *cod){

Turno reg;
ArchivoTurnos archi("turnos.dat");
int cant= archi.contarRegistros();

Fecha fecha;

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    if(strcmp(reg.getCodigoSocio(),cod)==0 && reg.getEstado() && reg.getImporte()<15000){
        return reg.getFechaTurno();
    }
}

fecha.setAnio(2000);
return fecha;
}


void puntoA(){

Socio reg;
ArchivoSocios archi("socios.dat");
int cant=archi.contarRegistros();

Fecha fecha;
SocioImporte aux;

for(int i=0; i<cant; i++){
    reg=archi.leerRegistro(i);
    fecha=traerFecha(reg.getCodigoSocio());
    if(fecha.getAnio()>2020 && reg.getEstado()){
         aux.setCodigoSocio(reg.getCodigoSocio());
         aux.setNombre(reg.getNombre());
         aux.setFechaTurno(fecha);
         aux.grabarRegistro(aux);
    }


}
}

void puntoB(){

puntoA();

SocioImporte *v;
ArchivoSocioImporte archi("puntoA.dat");
int cant=archi.contarRegistros();

v=new SocioImporte[cant];
if(v==NULL) return;
for(int i=0; i<cant; i++){
    v[i]=archi.leerRegistro(i);
}
for(int i=0; i<cant; i++){
    v[i].Mostrar();;
}
delete v;

}

