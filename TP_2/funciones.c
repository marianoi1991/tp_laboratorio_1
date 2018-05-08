#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"
#define QTY 20

/** \brief funcion que da inicio al programa
 *  \param No recibe
 *  \return No devuelve ningun valor
 */
void ejecutarPrograma()
{
    char auxChar[2];
    int opcion,flagPersonas=0,contMenores=0,cont1835=0,contMas35=0;
    ePersonas personas[QTY];
    blanqueoPersonas(personas,QTY,0);
    do
    {
        if(menu(auxChar))
        {
            opcion=atoi(auxChar);
            if(opcion != 5)
            {
                operaciones(opcion,personas,QTY,&flagPersonas,&contMenores,&cont1835,&contMas35);
            }
        }
        system("cls");
    }while(opcion != 5);
}

/** \brief esta funcion recibe la opcion elegida por el usuario y llama a las operaciones
 *
 * \param int opcion recibo la opcion seleccionada por el usuario
 * \param ePersonas personas[] recibo el array de la estructura ePersonas
 * \param int cantidad recibo el tamaño del array personas
 * \param int* flagPersonas este flag me indica si ya di de alta un usuario
 * \param int* contMenores contador de las personas menores de 18 años
 * \param int* cont1835 contador de las personas de 18 a 35 años
 * \param int* contMas35 contador de las personas mayores de 35 años
 * \return int devuelvo un 0
 *
 */
int operaciones(int opcion,ePersonas personas[], int cantidad,int* flagPersonas,int* contMenores,int* cont1835,int* contMas35)
{
    int posicion;
    switch(opcion)
    {
        case 1:
            if(buscarLugar(personas,cantidad,&posicion))
            {
                if(altaUsuario(posicion,personas,*flagPersonas))
                {
                    *flagPersonas=*flagPersonas+1;
                    verificoEdad(personas[posicion].edad,contMenores,cont1835,contMas35,1);
                    mostrarMensaje("\nAlta de usuario realizada.");
                }
            }
            else
            {
                mostrarMensaje("\nNo hay mas lugar para un nuevo usuario.");
            }
            system("\npause");
            break;
        case 2:
            if(*flagPersonas > 0)
            {
                if(bajaUsuario(personas))
                {
                    *flagPersonas=*flagPersonas-1;
                    verificoEdad(personas[posicion].edad,contMenores,cont1835,contMas35,2);
                    compactar(personas,cantidad);
                    mostrarMensaje("\nBaja de usuario realizada.");
                }
            }
            else
            {
                mostrarMensaje("\nNo hay usuarios ingresados.");
            }
            system("\npause");
            break;
        case 3:
            if(*flagPersonas > 0)
            {
                listarPersonas(personas,*flagPersonas);
            }
            else
            {
                mostrarMensaje("\nNo hay usuarios ingresados.");
            }
            system("\npause");
            break;
        case 4:
            if(*flagPersonas > 0)
            {
                graficoEdades(*contMenores,*cont1835,*contMas35);
            }
            else
            {
                mostrarMensaje("\nNo hay usuarios ingresados.");
            }
            system("\npause");
            break;
        default:
            printf("opcion invalida");
            system("\npause");
            break;
    }

    return 0;
}

/** \brief Presenta al usuario un menu de opciones para que elija la acción a realizar.
 *  \param char* recibe por referencia donde debe guardar el valor ingresado por el usuasrio
 *  \return devuelvo 0 si el valor ingresado no es un numero o 1 si es un valor numerico
 */
int menu(char* auxiliar)
{
    int retorno=-1;
    printf("1- Agregar persona\n2- Borrar persona\n3- Imprimir lista ordenada por  nombre\n4- Imprimir grafico de edades\n5-Salir\nOpcion:");
    scanf("%s",auxiliar);
    if(validoNumeros(auxiliar))
    {
        retorno=1;
    }

    return retorno;
}

/**\brief Inicializa un array con el valor recibido
 * \param ePersonas personas Es el array a ser inicializado
 * \param int cantidad Indica la longitud del array
 * \param int dato Es el valor que sera cargado en el campo estado
 * \return void
 */
void blanqueoPersonas(ePersonas personas[],int cantidad,int dato)
{
    int i;
    for(i=0;i<cantidad; i++)
    {
        personas[i].estado= dato;
    }
}

/**\brief Solicita los datos al usuario para realizar el alta
 * \param ePersonas personas Es el array donde guardo los datos del usuario
 * \param int posicion recibo la posicion del array donde voy a guardar los datos del alta
 * \param int cantidad Indica la longitud del array
 * \return si el alta se realiza devuelvo 1, si no se realizo devuelvo 0
 */
int altaUsuario(int posicion,ePersonas personas[],int cantidad)
{
    int retorno=0;
    char nombreAux[30],dniAux[8],edadAux[3];
    system("cls");
    printf("\nALTA DE USUARIO\n---------------");
    if(getString("\nIngrese su nombre: ","\nError, ingrese solo letras",nombreAux,30,2))
    {
        strcpy(personas[posicion].nombre,nombreAux);
        if(getInt("Ingrese su DNI: ","Error, ingrese solo numeros",dniAux,2,999999,100000000))
        {
            if(validoDni(dniAux,personas,cantidad)==1 || cantidad==0)
            {
                strcpy(personas[posicion].dni,dniAux);
                if(getInt("Ingrese su edad: ","Error, ingrese solo numeros",edadAux,2,1,100))
                {
                    personas[posicion].edad=atoi(edadAux);
                    personas[posicion].estado=1;
                    retorno=1;
                }
                else
                {
                    mostrarMensaje("\nError, no ingreso un dato valido");
                }
            }
            else
            {
                mostrarMensaje("Error, el DNI ingresado ya fue dado de alta");
            }
        }
        else
        {
            mostrarMensaje("\nError, no ingreso un dato valido");
        }
    }
    else
    {
        mostrarMensaje("\nError, no ingreso un dato valido");;
    }

    return retorno;
}


/**\brief Realizo la baja logica de una persona
 * \param ePersonas personas Es el array en el cual realizo la baja
 * \return si baja se realizo devuelvo 1, si no se realizo devuelvo 0
 */
int bajaUsuario(ePersonas personas[])
{
    char dniAux[9],opcion[3],ok[3]={"si"};
    int retorno=0,posicion;

    system("cls");
    printf("BAJA DE USUARIO\n---------------\n");
    if(getInt("Ingrese el DNI del usuario a dar de baja: ","Error, ingrese solo numeros",dniAux,2,999999,100000000))
    {
        if(buscarDni(personas,dniAux,&posicion)==1)
        {
            if(getString("\nConfirma la baja del usuario? SI / NO: ","\nError, ingrese solo letras",opcion,2,2))
            {
                if(strcmp(opcion,ok)==0)
                {
                    personas[posicion].estado=0;
                    retorno=1;
                }
                else
                {
                    printf("\nOperacion cancelada");
                }
            }
            else
            {
                mostrarMensaje("\nEl dni ingresado, no existe");
            }
        }
        else
        {
            mostrarMensaje("\nEl dni ingresado, no existe");
        }
    }

    return retorno;
}


/**\brief listarPersonas la lista de personas, ordenadas por nombre alfabeticamente
 * \param ePersonas personas Es el array donde tengo los datos de las personas
 * \param int cantidad recibo la cantidad de usuarios dados de alta dentro del programa
 * \return void
 */
void listarPersonas(ePersonas personas[],int cantidad)
{
    int i,j;
    ePersonas auxChar;
    system("cls");
    mostrarMensaje("Lista de personas\n----------------\n");
    for (i = 1; i < cantidad; i++)
    {
        auxChar=personas[i];
        j = i-1;
        while (j >= 0 && strcmp(personas[j].nombre,auxChar.nombre)==1)
        {
            personas[j+1]=personas[j];
            j--;
        }
        personas[j+1]=auxChar;
    }
    for(i=0;i<cantidad;i++)
    {
        printf("NOMBRE: %s   DNI: %s    EDAD: %d\n",personas[i].nombre,personas[i].dni,personas[i].edad);
    }
}


/**\brief Obtengo el primer indice del array disponible
 * \param ePeronas personas Es el array donde realizo la busqueda
 * \param int cantidad Indica la logitud del array
 * \return si encontro un lugar disponible devuelve 1, si no encontro nigun ligar devuelve 0
 */
int buscarLugar(ePersonas personas[],int cantidad,int* posicion)
{
    int i=0,retorno=0;
    for(i=0;i<cantidad;i++)
    {
        if(personas[i].estado==0)
        {
            *posicion=i;
            retorno=1;
            return retorno;
        }
    }

    return retorno;
}


/**\brief Busco un dni dentro de la estructura  ePersonas
 * \param ePersonas personas Es el array sobre el cual realizo la busqueda
 * \param char dni contiene el dato a ser buscado dentro del array
  * \param int* posicion  si encuentro el dato que busco, guardo el indice del array dentro de esta variable
 * \return si encontro el dni devuelvo un 1, si no devuelvo 0
 */
int buscarDni(ePersonas personas[],char dni[],int* posicion)
{
    int retorno=0,i=0;
    for(i=0;personas[i].estado==1;i++)
    {
        if(atoi(personas[i].dni)==atoi(dni))
        {
            *posicion=i;
            retorno=1;
            return retorno;
        }
    }

    return retorno;
}


/**\brief Valido que el dato contenga solo caracteres numericos
 * \param char numero contiene el dato a validar
 * \return devuelvo 1 si el dato solo contiene numeros, si no 0
 */
int validoNumeros(char numero[])
{
    int i,retorno=-1;
    for(i=0;i<strlen(numero);i++)
    {
        if(isdigit(numero[i]))
        {
            retorno=1;
        }
        else
        {
            retorno=0;
            return retorno;
        }
    }

    return retorno;
}

/**\brief Valido que el dato contenga solo letras
 * \param char dato[] contiene el dato a validar
 * \return devuelvo 1 si el dato solo contiene letras, si no 0
 */
int validoString(char dato[])
{
    int i,retorno=0;
    for(i=0;i<strlen(dato);i++)
    {
        if(dato[0] != ' ')
        {
            if(isalpha(dato[i]) || dato[i]==' ')
            {

                retorno=1;
             }
             else
             {
                retorno=0;
                continue;
             }
        }
        else
        {
            retorno=0;
            return retorno;
        }
    }

    return retorno;
}

/**\brief Valido que el dato contenga solo numeros
 * \param char dato[] contiene el dato a validar
 * \return devuelvo 1 si el dato solo contiene numeros, si no 0
 */
int validoInt(char dato[])
{
    int i,retorno=0;
    for(i=0;i<strlen(dato);i++)
    {
        if(isdigit(dato[i]))
        {
            retorno=1;
        }
        else
        {
            retorno=0;
            return retorno;
        }
    }

    return retorno;
}


/**\brief Muestra un grafico de edades de las personas dadas de alta
 * \param cont1 contiene la cantidad de personas menores de edad
 * \param cont2 contiene la cantidad de personas con edad entre 18 y 35
 * \param cont3 contiene la canidad de personas con edad superior a 36
 * \return void
 */
void graficoEdades(int cont1,int cont2,int cont3)
{
    int i,mayor;
    if(cont1 >= cont2 && cont1 >= cont3)
    {
        mayor = cont1;
    }
    else
    {
        if(cont2 >= cont1 && cont2 >= cont3)
        {
            mayor = cont2;
        }
        else
        {
            mayor = cont3;
        }
    }
    system("cls");
    mostrarMensaje("GRAFICO DE EDADES\n---------------\n");
    for(i=mayor;i>0;i--)
    {
        if(cont1>=i)
        {
            printf("\n *  ");
        }
        else
        {
            printf("\n    ");
        }
        if(cont2>=i)
        {
            printf("   *   ");
        }
        else
        {
            printf("     ");
        }
        if(cont3>=i)
        {
            printf("  *  ");
        }
        else
        {
            printf("    ");
        }
    }
    printf("\n<18  19-35  35>");
}


/**\brief Muestra un mensaje
 * \param no recibe
 * \return void
 */
void mostrarMensaje(char* mensaje)
{
    printf(mensaje);
}

/** \brief Pide al usuario que ingrese un dato numerico que se encuentre dentre dentro del rango especificado
 *
 * \param char* mensaje recibo el mensaje que debo mostrarle al usuario
 * \param char* mensajeError recibo el mensaje de error a mostrar su el dato ingresado no es correcto
 * \param char dato[] variable donde guardo el dato ingresao
 * \param int intentos la cantidad de intentos que tiene el usuario para ingresar el dato
 * \param int minimo recibo es el valor minimo que puede ingresar el usuario
 * \param int maximo recibo el valor maximo que puede ingresar el usuario
 * \return int devuelvo 1 si el valor ingresado es correcto y esta dentro del maximo y minimo, devuelvo 0 si no lo esta
 *
 */
int getInt(char* mensaje,char* mensajeError,char dato[],int intentos,int minimo,int maximo)
{
    int i,retorno=0;
    i=intentos;
    do
    {
        i--;
        printf(mensaje);
        fflush(stdin);
        scanf("%s",dato);
        if(validoInt(dato))
        {
            if(atoi(dato)>minimo && atoi(dato)<maximo)
            {
                retorno=1;
            }
            else
            {
                mostrarMensaje("Fuera de rango,intente de nuevo");
            }
        }
        else
        {
            printf(mensajeError);
            system("pause");
        }
    }while(i>0 && retorno ==0);

    return retorno;
}

/** \brief Pide al usuario que ingrese un dato alfanumerico
 *
 * \param char* mensaje recibo el mensaje que debo mostrarle al usuario
 * \param char* mensajeError recibo el mensaje de error a mostrar su el dato ingresado no es correcto
 * \param char dato[] variable donde guardo el dato ingresao
 * \param int cantidad recibo la longitud maxima que puede tener el dato ingresado
 * \param int intentos la cantidad de intentos que tiene el usuario para ingresar el dato
 * \return int devuelvo 1 si el valor es correcto y su longitud esta dentro del maximo y minimo, devuelvo 0 si no lo esta
 */
int getString(char* mensaje,char* mensajeError,char dato[], int cantidad,int intentos)
{
    int i,retorno=0;
    i=intentos;
    do
    {
        i--;
        printf(mensaje);
        fflush(stdin);
        gets(dato);
        if(validoString(dato))
        {
            retorno=1;
        }
        else
        {
            printf(mensajeError);
            system("pause");
        }
    }while(i>0 && retorno ==0);

    return retorno;
}

/** \brief verifico en que rango se encuentra la edad del usuario que estoy dando de alta
 *
* \param int* contMenores contador de las personas menores de 18 años
 * \param int* cont1835 contador de las personas de 18 a 35 años
 * \param int* contMas35 contador de las personas mayores de 35 años
 * \param int orden si recibo un 1 es una alta y debo incrementar el contador que corresponda, si recibo un 2 se trata de una baja y debo restar 1 al contador que corresponda
 * \return void
 */
void verificoEdad(int edad,int* contMenores,int* cont1835,int* contMas35,int orden)
{
    if(orden == 1)
    {
        if(edad < 18)
        {
            *contMenores=*contMenores+1;
        }
        else
        {
            if(edad > 17 && edad < 36)
            {
                *cont1835=*cont1835+1;
            }
            else
            {
                *contMas35=*contMas35+1;
            }
        }
    }
    else
    {
        if(edad < 18)
        {
            *contMenores=*contMenores-1;
        }
        else
        {
            if(edad > 17 && edad < 36)
            {
                *cont1835=*cont1835-1;
            }
            else
            {
                *contMas35=*contMas35-1;
            }
        }
    }
}

/** \brief compacta el array juntando a los que tienen datos cargados al principio del array y dejando a los dados de baja o vacios o lo ultimo
 *
 * \param ePersonas personas[] recibo el array a compactar
 * \param int cantidad  longitud del array
 * \return void
 *
 */
void compactar(ePersonas personas[],int cantidad)
{
    int i,j;
    ePersonas auxiliar;
    for (i = 1; i < cantidad; i++)
    {
        auxiliar=personas[i];
        j = i-1;
        while (j >= 0 && personas[j].estado < auxiliar.estado)
        {
            personas[j+1]=personas[j];
            j--;
        }
        personas[j+1]=auxiliar;
    }
}

/** \brief busco dentro del array un dato
 *
 * \param char dni[] reibo el dato a buscar dentro del array
 * \param ePersonas personas[]  el array donde busco el dato
 * \param int cantidad  recibo la longitud del array
 * \return int devuelvo 1 si encuentro el dato, devuelvo 0 si no lo encuentro
 *
 */
int validoDni(char dni[],ePersonas personas[],int cantidad)
{
    int i,retorno=1;
    for(i=0;i<cantidad;i++)
    {
        if(atoi(personas[i].dni)== atoi(dni))
        {
            retorno=0;
        }
    }

    return retorno;
}
