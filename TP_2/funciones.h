#ifndef FUNCIONES_H_INCLUDED
typedef struct
{
    char nombre[30];
    char dni[9];
    int edad;
    int estado;
}ePersonas;
#endif // FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

void ejecutarPrograma();
int menu(char[]);
void blanqueoPersonas(ePersonas[],int,int);
int operaciones(int,ePersonas[],int,int*,int*,int*,int*);
int altaUsuario(int,ePersonas[],int);
int bajaUsuario(ePersonas[]);
void listarPersonas(ePersonas[],int);
void graficoEdades(int,int,int);
int getString(char*,char*,char[],int,int);
int getInt(char*,char*,char[],int,int,int);
int buscarLugar(ePersonas[],int,int*);
int buscarDni(ePersonas[],char [],int*);
int validoInt(char[]);
int validoString(char []);
void mostrarMensaje(char*);
void verificoEdad(int,int*,int*,int*,int);
void compactar(ePersonas[],int);



