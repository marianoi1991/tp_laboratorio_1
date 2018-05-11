#ifndef FUNCIONES_H_INCLUDED
typedef struct
{
    char idCliente[20];
    int numRubro;
    char textoAviso[60];
    int idPublicacion;
    int estado;
}ePublicacion;
#endif // FUNCIONES_H_INCLUDED
#ifndef FUNCIONES_H_INCLUDED
typedef struct
{
    int idCliente;
    int numRubro;
    char textoAviso[60];
    int idPublicacion;
    int estado;
}ePublicacion;
#endif // FUNCIONES_H_INCLUDED

void ejecutarPrograma();
void harcodeoDatos(eCliente[],ePublicacion[],int);
int menu(char[]);
void blanqueoPersonas(eCliente[],ePublicacion[],int);
int operaciones(int,eCliente[],int,ePublicacion[],int,int*);
int getString(char*,char*,char[],int,int,int);
int getInt(char*,char*,char[],int,int,int);
int validoInt(char[]);
int validoString(char []);
void mostrarMensaje(char*);
int proximoId();
void mostrarMensaje(char*);
