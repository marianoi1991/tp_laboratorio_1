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

int buscarPublicaciones(ePublicacion[],char[]);

