#ifndef PARCIAL_H_INCLUDED
#define PARCIAL_H_INCLUDED

class Pais{
    private:
        int codigoPais;
        char nombrePais[30];
    public:
        int getCodigoPais(){return codigoPais;}
        const char *getNombrePais(){return nombrePais;}
        bool leerDeDisco(int);
};

bool Pais::leerDeDisco(int pos){
FILE *p;
p=fopen("paises.dat","rb");
if(p==NULL)exit(1);
fseek(p, sizeof *this*pos,0);
bool leyo=fread(this, sizeof *this, 1, p);
fclose(p);
return leyo;
}

class Jugador{
private:
char codigoJugador[5];
char nombreJugador[30];
int codigoPais;
int edad;
public:
const char* getCodigoJugador(){return codigoJugador;}
const char* getNombreJugador(){return nombreJugador;}
int getCodigoPais(){return codigoPais;}
bool leerDeDisco(int);
};

bool Jugador::leerDeDisco(int pos){
FILE *p;
p=fopen("jugadores.dat","rb");
if(p==NULL)exit(1);
fseek(p, sizeof *this*pos,0);
bool leyo=fread(this, sizeof *this, 1, p);
fclose(p);
return leyo;
}

class Gol{
private:
int codigoPartido;
int minutos, tiempo;
char codigoJugador[5];
int tipo;
public:
const char *getCodigoJugador(){return codigoJugador;}
int getTipo(){return tipo;}
bool leerDeDisco(int);
};

bool Gol::leerDeDisco(int pos){
FILE *p;
p=fopen("goles.dat","rb");
if(p==NULL)exit(1);
fseek(p, sizeof *this*pos,0);
bool leyo=fread(this, sizeof *this, 1, p);
fclose(p);
return leyo;
}

#endif // PARCIAL_H_INCLUDED
