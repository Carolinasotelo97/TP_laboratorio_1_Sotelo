/*
 * manu.c
 *
 *  Created on: 18 jun. 2021
 *      Author: caroo
 */



#include "menu.h"
#include "validaciones.h"
#include <stdio.h>
#include <stdlib.h>

int menu()
{
    int opcion;

    system("cls");
    printf("   *** M E N U ***\n\n");
     printf("1.Cargar los datos de los empleados desde\n  el archivo data.csv (modo texto)\n");
     printf("2.Cargar los datos de los empleados desde\n  el archivo data.csv (modo binario)\n");
     printf("3.Alta de empleado\n");
     printf("4.Modificar datos de empleado\n");
     printf("5.Baja de empleado\n");
     printf("6.Listar empleados\n");
     printf("7.Ordenar empleados\n");
     printf("8.Guardar los datos de los empleados en el\n  archivo data.csv (modo texto)\n");
     printf("9.Guardar los datos de los empleados en el\n  archivo data.csv (modo binario)\n");
     printf("10.Salir\n");
     printf("_______________________________________________\n");

     getInt(&opcion,"Elija una opcion:","Elija una opcion valida:");

     return opcion;
}

char submenuModificar()
{
    char opcion;

    system("cls");
    printf("   ***MENU MODIFICACIONES***\n\n");

    printf("a.Cambiar nombre\n");
    printf("b.Cambiar cantidad de horas trabajadas\n");
    printf("c.Cambiar sueldo\n");
    printf("_______________________________________\n");

    getChar(&opcion,"Elija nna opcion:","Elija una opcion valida:");

    return opcion;
}

char submenuOrdenar()
{
    char opcion;

    system("cls");
    printf("   ***MENU ORDEN***\n\n");
    printf("a.Ordenar por id\n");
    printf("b.Ordenar por nombre\n");
    printf("c.Ordenar por horas trabajadas\n");
    printf("d.Ordenar por sueldos\n");
    printf("_______________________________\n");

    getChar(&opcion,"Elija una opcion:","Elija una opcion valida:");

    return opcion;
}
