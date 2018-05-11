#include "publicaciones.h"
#ifndef FUNCIONES_H_INCLUDED
typedef struct
{
    char nombre[20];
    char apellido[20];
    char cuit[50];
    int id;
    int publicacionID;
    int estado;
}eCliente;
#endif // FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED


int altaCliente(int,eCliente[],int);
int bajaCliente(eCliente[],ePublicacion[]);
void listarPersonas(eCliente[],int);
int buscarLugar(eCliente[],int,int*);
void compactar(eCliente[],int);
int modificarCliente(eCliente[],int);
int buscarID(eCliente[],char[],int*);

