/*
 * controller.c
 *
 *  Created on: 24 jun. 2021
 *      Author: caroo
 */


#include "controller.h"
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "estudiante.h"
#include "validaciones.h"
#include "menu.h"

/** \brief Obtiene el id a cargar a un empleado y lo carga a un puntero
 *
 * \param id int*
 * \return int -1 si el archivo de proxId no existe y sino 0
 *
 */
static int obtenerId(int* id)
{
    int retorno=-1;
    FILE* f;

    if(id!=NULL)
    {
        *id=101;//empiezan en 101 pq si se cargaron estudiantes desde un archivo
        f=fopen("proxId.bin","rb");//guardo el proximo id en archivo binario
        if(f!=NULL)
        {
            fread(id,sizeof(int),1,f);
            retorno=0;

            fclose(f);
        }
    }

    return retorno;
}

/** \brief actualiza el id y carga lo que sera el proximo id en un archivo binario
 *
 * \param id int Id actual para saber cual sera el proximo
 * \return int 0 si salio todo bien y sino -1
 *
 */
static int actualizarId(int id)
{
    int retorno=-1;
    FILE* f;

    id++;

    f=fopen("proxId.bin","wb");//despues del 1er alta se va a crear este archivo
    if(f!=NULL)
    {
        fwrite(&id,sizeof(int),1,f);
        retorno=0;
        fclose(f);
    }

    return retorno;
}

int controller_chargeTxt(LinkedList*pArray,char*path)
{
    int retorno=-1;
    FILE* f;

    if(pArray!=NULL)
    {
        f=fopen(path,"r");//lo abro para leer en modo txt
        if(f!=NULL)
        {
            if(!parserStudentFromTxt(f,pArray))
            {
                retorno=0;
            }

            fclose(f);
        }
    }

    return retorno;
}

int controller_addStudent(LinkedList*pArray)
{
    int retorno=-1;
    Student* newStudent;
    int auxId;
    char auxNombre[25];
    char auxSexo;
    float auxPromedio;

    if(pArray!=NULL)
    {
        system("cls");
        printf("   ***ALTAS***\n\n");

        newStudent=student_new();
        if(newStudent!=NULL)
        {
            obtenerId(&auxId);
            getString(auxNombre,sizeof(auxNombre),"Ingrese nombre:","Ingrese nombre valido:");
            getCharTwoOptions(&auxSexo,"Ingrese sexo (f/m):","Ingrese sexo valido:",'f','m');
            getFloat(&auxPromedio,"Ingrese promedio:","Ingrese promedio valido:");
            while(auxPromedio<0||auxPromedio>10)//promedio solo va de 0 a 10
            {
                getFloat(&auxPromedio,"Ingrese promedio valido:","Ingrese promedio valido:");
            }

            if(!student_setId(newStudent,auxId)&&
               !student_setNombre(newStudent,auxNombre)&&
               !student_setPromedio(newStudent,auxPromedio)&&
               !student_setSexo(newStudent,auxSexo))//si todos los setters retornan ok
            {
                ll_add(pArray,newStudent);
                /*ll_push(pArray,95,newStudent);*/
                actualizarId(auxId);
                retorno=0;
            }
        }
    }

    return retorno;
}

int controller_edit(LinkedList*pArray)
{
    int retorno=-1;
    Student* pStudent;
    int idModificar;
    char auxNombre[25];
    char auxSexo;
    float auxProm;
    int indice;

    if(pArray!=NULL)
    {
        system("cls");
        printf("   ***BAJAS***\n\n");
        getInt(&idModificar,"Ingrese id del empleado a modificar:","Ingrese id valido:");
        indice=findStudentById(pArray,idModificar);
        if(indice!=-1)//si el id ess de un estudiante existente
        {
            pStudent=ll_get(pArray,indice);
            switch(menuModificar())
            {
            case 'a':
                getString(auxNombre,sizeof(auxNombre),"\nIngrese nuevo nombre:","Ingrese nombre valido:");
                if(!student_setNombre(pStudent,auxNombre))
                {
                    retorno=0;
                }
                break;
            case 'b':
                getCharTwoOptions(&auxSexo,"\nIngrese sexo:","Ingrese sexo valido (f/m):",'f','m');
                if(!student_setSexo(pStudent,auxSexo))
                {
                    retorno=0;
                }
                break;
            case 'c':
                getFloat(&auxProm,"\nIngrese promedio actualizado:","Ingrese promedio valido:");
                while(auxProm<0||auxProm>10)//promedio puede ir de 0 a 10
                {
                    getFloat(&auxProm,"Ingrese promedio valido:","Ingrese promedio valido:");
                }
                if(!student_setPromedio(pStudent,auxProm))
                {
                    retorno=0;
                }
                break;
            case 'd'://salir
                break;
            default:
                printf("\nOpcion no valida\n\n");
                break;
            }
        }
    }

    return retorno;
}

int controller_remove(LinkedList*pArray)
{
    int retorno=-1;
    Student* pStudent;
    int idEliminar;
    char auxNombre[25];
    int indice;

    if(pArray!=NULL)
    {
        system("cls");
        printf("   ***BAJAS***\n\n");
        controller_listStudents(pArray);
        printf("_______________________________________________\n");
        getInt(&idEliminar,"Ingrese id del empleado a eliminar:","Ingrese id valido:");
        indice=findStudentById(pArray,idEliminar);
        if(indice!=-1)//si el id ess de un estudiante existente
        {
            pStudent=ll_pop(pArray,indice);
            if(pStudent!=NULL)
            {
                student_getNombre(pStudent,auxNombre);
                printf("\n%s ha sido dada/o de baja\n\n",auxNombre);
                retorno=0;
            }
        }//fin indice != -1
    }

    return retorno;
}

int controller_sortStudents(LinkedList*pArray)
{
    int retorno=-1;
    int orden;
    char opcion;

    if(pArray!=NULL)
    {
        opcion=menuOrdenar();
        getInt(&orden,"\nDesea ordenar los estudiantes de forma ascendente (1)\n o descendente (0)?","Ingrese 0 o 1:");
        while(orden!=1&&orden!=0)
        {
            getInt(&orden,"\nIngrese 0 o 1:","Ingrese 0 o 1:");
        }

        printf("\nOrdenando...\n");//hago este printf pq tardan bastante en ordenarse

        switch(opcion)
        {
        case 'a':
            if(!ll_sort(pArray,compararPorId,orden))
            {
                 retorno=0;
            }
            break;
        case 'b':
            if(!ll_sort(pArray,compararPorNombre,orden))
            {
                 retorno=0;
            }
            break;
        case 'c':
            if(!ll_sort(pArray,compararPorSexo,orden))
            {
                 retorno=0;
            }
            break;
        case 'd':
            if(!ll_sort(pArray,compararPorPromedio,orden))
            {
                 retorno=0;
            }
            break;
        default:
            printf("\n\nOpcion no valida\n\n");
            break;
        }
    }

    return retorno;
}

int controller_listStudents(LinkedList* pArray)
{
    int retorno=-1;
    int len;
    Student* auxStudent;

    if(pArray)
    {
        len=ll_len(pArray);
        printf("    ***Lisitado de estudiantes***\n\n");
        printf(" ID  NOMBRE  SEXO PROMEDIO\n");
        for(int i=0;i<len;i++)
        {
            auxStudent=ll_get(pArray,i);
            printStudent(auxStudent);//esta funcion esta en la biblioteca estudiante
        }

        retorno=0;
    }

    return retorno;
}

int controller_insertStudent(LinkedList*pArray)
{
    int retorno=-1;
    int auxIndice;
    int auxId;
    char auxNombre[25];
    char auxSexo;
    float auxPromedio;
    Student* newStudent=NULL;

    if(pArray!=NULL)
    {
        getInt(&auxIndice,"En que lugar desea insertar estudiante?","Ingrese indice valido:");
        if(auxIndice>0&&auxIndice<=ll_len(pArray))
        {
            newStudent=student_new();
            if(newStudent!=NULL)
            {
                obtenerId(&auxId);
                getString(auxNombre,sizeof(auxNombre),"Ingrese nombre:","Ingrese nombre valido:");
                getCharTwoOptions(&auxSexo,"Ingrese sexo (f/m):","Ingrese sexo valido:",'f','m');
                getFloat(&auxPromedio,"Ingrese promedio:","Ingrese promedio valido:");
                while(auxPromedio<0||auxPromedio>10)//promedio solo va de 0 a 10
                {
                    getFloat(&auxPromedio,"Ingrese promedio valido:","Ingrese promedio valido:");
                }

                if(!student_setId(newStudent,auxId)&&
                   !student_setNombre(newStudent,auxNombre)&&
                   !student_setPromedio(newStudent,auxPromedio)&&
                   !student_setSexo(newStudent,auxSexo))//si todos los setters retornan ok
                {
                    ll_push(pArray,auxIndice,newStudent);
                    actualizarId(auxId);
                    if(ll_indexOf(pArray,newStudent)==auxIndice)//verifico que haya funcionado
                    {
                        retorno=0;
                    }//fin comprobacion
                }//fin setters
            }//newStudent!=NULL
        }//validacion indice
    }//validacion params

    return retorno;
}

int controller_clearList(LinkedList*pArray)
{
    int retorno=-1;
    char confirma;

    if(pArray!=NULL)
    {
        printf("\n\nAl vaciar la lista se borraran todos los elementos en ella\n");
        getCharTwoOptions(&confirma,"Esta seguro de que quiere vaciarla? (s/n)","Ingrese s o n:",'s','n');
        if(confirma=='s')
        {
            if(!ll_clear(pArray))
            {
                retorno=0;
            }
        }else
        {
            retorno=1;
        }
    }


    return retorno;
}

int controller_backupFile(LinkedList*pArray,char*path)
{
    int retorno=-1;
    LinkedList* cloneArray=NULL;

    if(pArray!=NULL&&path!=NULL)
    {
        cloneArray=ll_clone(pArray);
        if(cloneArray!=NULL)
        {
            if(ll_containsAll(pArray,cloneArray))//verifico que ambas listas contengan lo mismo
            {
                controller_saveAsTxt(cloneArray,path);
                retorno=0;
            }

            ll_deleteLinkedList(cloneArray);//despues de guardarla la borro
        }
    }

    return retorno;
}

int controller_saveAsTxt(LinkedList*pArray,char*path)
{
    int retorno=-1;
    FILE* pFile;
    int len;
    Student* pStudent;
    int auxId;
    char auxNombre[25];
    char auxSexo;
    float auxPromedio;

    if(pArray!=NULL&&path!=NULL)
    {
        pFile=fopen(path,"w");
        if(pFile!=NULL)
        {
            len=ll_len(pArray);
            fprintf(pFile,"id,nombre,sexo,promedio\n");//escribo el encabezado
            for(int i=0;i<len;i++)
            {
                pStudent=ll_get(pArray,i);

                if(!student_getId(pStudent,&auxId)&&
                   !student_getNombre(pStudent,auxNombre)&&
                   !student_getSexo(pStudent,&auxSexo)&&
                   !student_getPromedio(pStudent,&auxPromedio))//cargo los valores del puntero a estudiante
                {
                    fprintf(pFile,"%d,%s,%c,%f\n",auxId,auxNombre,auxSexo,auxPromedio);
                    retorno=0;
                }
            }//fin for
            fclose(pFile);
        }//fin file!=NULL
    }//fin parametros!=NULL

    return retorno;
}
