#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
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
        *id=1001;//empiezan en 1001 pq si se cargaron empleados en archivos no se repetira id
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

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char* Nombre del archivo del que se cargara info
 * \param pArrayListEmployee LinkedList* Array de empleados
 * \return int 0 si salio todo bien y sino -1
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    FILE* pFile;
    if(path!=NULL&&pArrayListEmployee!=NULL)
    {
        pFile=fopen(path,"r");
        if(pFile!=NULL)
        {
            if(!parser_EmployeeFromText(pFile,pArrayListEmployee))
            {
                retorno=0;
            }
            fclose(pFile);
        }
    }
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char* nombre del archivo del que se cargara la info
 * \param pArrayListEmployee LinkedList* Array de empleados
 * \return int 0 si salio todo bien y sino -1
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    FILE* pFile;
    if(path!=NULL&&pArrayListEmployee!=NULL)
    {
        pFile=fopen(path,"rb");
        if(pFile!=NULL)
        {
            if(!parser_EmployeeFromBinary(pFile,pArrayListEmployee))
            {
                retorno=0;
            }
            fclose(pFile);
        }
    }
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param pArrayListEmployee LinkedList* Array de empleados
 * \return int 0 si salio todo bien y sino -1
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    Employee* newEmployee=NULL;
    int auxId;
    char auxNombre[128];
    int auxHoras;
    int auxSueldo;
    if(pArrayListEmployee!=NULL)
    {
        system("cls");
        printf("   ***ALTA EMPLEADO**\n\n");
        newEmployee=employee_new();
        if(newEmployee!=NULL)
        {
            getString(auxNombre,sizeof(auxNombre),"Ingrese nombre del empleado:","Ingrese nombre valido:");
            getInt(&auxHoras,"\nIngrese la cantidad de horas trabajadas:","Ingrese cantidad de horas valida:");
            getInt(&auxSueldo,"\nnIngrese sueldo del empleado:","Ingrese sueldo valido:");
            obtenerId(&auxId);//la 1era vez le va a cargar 1001
            actualizarId(auxId);

            if(!employee_setId(newEmployee,auxId)&&
                !employee_setNombre(newEmployee,auxNombre)&&
                !employee_setHorasTrabajadas(newEmployee,auxHoras)&&
                !employee_setSueldo(newEmployee,auxSueldo))
            {
                ll_add(pArrayListEmployee,newEmployee);//agrego al nuevo empleado a la lista
                retorno=0;//todo salid ok
            }
        }//if newEmployee
    }// if parrayEmployees
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param pArrayListEmployee LinkedList* Array de empleados
 * \return int 0 si se modifico al empleado, 1 si se cancelo la operacion y -1 si hubo alguna falla
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    char bufferNombre[128];//por si tengo que cambiar el nombre
    int bufferInt;//si tengo que cambiar horas o sueldo
    Employee* auxE;
    int auxId;
    int indice;//indice del empleado a editar
    char confirma;

    if(pArrayListEmployee!=NULL)
    {
        system("cls");
        printf("   ***MODIFICACIONES***\n\n");
        getInt(&auxId,"Ingrese el id del empleado a modificar:","Ingrese id valido:");
        indice=findEmployeeById(pArrayListEmployee,auxId);
        if(indice!=-1)//compruebo que el empleado exista
        {
            auxE=ll_get(pArrayListEmployee,indice);
            if(auxE!=NULL)
            {
                printf("\n\n");
                printf("ID      NOMBRE HORAS   SUELDO\n");
                mostrarEmpleado(auxE);
                getCharTwoOptions(&confirma,"\nEs este el empleado que desea modificar? (s/n)\n","Ingrese s o n:",'s','n');
                if(confirma=='s')
                {
                    switch(submenuModificar(pArrayListEmployee))
                    {
                    case 'a':
                        getString(bufferNombre,sizeof(bufferNombre),"\nIngrese nuevo nombre:","Ingrese nombre valido:");
                        if(!employee_setNombre(auxE,bufferNombre))//compruebo que se haya podido cambiar el nombre
                        {
                            retorno=0;
                        }
                        break;
                    case 'b':
                        getInt(&bufferInt,"Ingrese cantidad de horas trabajadas:","Ingrese cantidad valida:");
                        if(!employee_setHorasTrabajadas(auxE,bufferInt))//compruebo que se haya podido cambiar la cant de horas
                        {
                            retorno=0;
                        }
                        break;
                    case 'c':
                        getInt(&bufferInt,"Ingrese nuevo sueldo:","Ingrese sueldo valido:");
                        if(!employee_setSueldo(auxE,bufferInt))//compruebo que se haya podido cambiar el sueldo
                        {
                            retorno=0;
                        }
                        break;
                    default:
                        printf("Opcion no valida\n");
                        break;
                    }
                }
                else
                {
                    retorno=1;//si el usuario no confirma retorno 1
                }
            }
        }
    }
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param pArrayListEmployee LinkedList* Array de empleados
 * \return int 0 si se dio de baja al empleado, 1 si se cancelo la operacion y -1 si hubo alguna falla
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    int auxId;
    int indice; //indice donde esta el empleado a borrar
    char confirma;
    Employee* auxE;

    if(pArrayListEmployee!=NULL)
    {
        system("cls");
        printf("   ***BAJA EMPLEADO***\n\n");
        getInt(&auxId,"Ingrese el id del empleado a dar de baja:","Ingrese id valido:");
        indice=findEmployeeById(pArrayListEmployee,auxId);
        if(indice!=-1)//compruebo que el empleado exista
        {
            auxE=ll_get(pArrayListEmployee,indice);
            printf("\n\n");
            printf("ID      NOMBRE HORAS   SUELDO\n");
            mostrarEmpleado(auxE);
            getCharTwoOptions(&confirma,"\nEs este el empleado que desea modificar? (s/n)\n","Ingrese s o n:",'s','n');
            if(confirma=='s')
            {
                ll_remove(pArrayListEmployee, indice);
                retorno=0;
            }
            else
            {
                retorno=1;//si el usuario no confirma retorno 1
            }
        }
    }
    return retorno;
}

/** \brief Listar empleados
 *
 * \param pArrayListEmployee LinkedList* Array de empleados
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    int len;
    Employee* auxE;
    int flag=0;
    if(pArrayListEmployee!=NULL)
    {
        system("cls");
        printf("    ***LISTA DE EMPLEADOS***\n\n");
        printf(" ID  NOMBRE  HORAS  SUELDO\n");
        len=ll_len(pArrayListEmployee);
        for(int i=0; i<len; i++)
        {
            auxE=(Employee*) ll_get(pArrayListEmployee,i);
            if(auxE!=NULL)
            {
                mostrarEmpleado(auxE);//esta funcion esta en la biblioteca Employee
                flag=1;
            }
        }
        if(!flag)
        {
            printf("\nNo hay empleados cargados\n\n");
        }
        retorno=0;
    }
    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param pArrayListEmployee LinkedList* Array de empleados
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    int orden;
    int opcion;
    if(pArrayListEmployee!=NULL)
    {
        opcion=submenuOrdenar();
        getInt(&orden,"\nIngrese 1(ascendente) o 0(descendente):","Ingrese 1 o 0:");
        while(orden!=0&&orden!=1)
        {
            getInt(&orden,"Ingrese 1 o 0:","Ingrese 1 o 0:");
        }//valido que se haya ingresado 0 o 1
        printf("\nOrdenando...\n");//hago este printf porque tardan en ordenarse
        switch(opcion)
        {
        case 'a':
            ll_sort(pArrayListEmployee,compararPorId,orden);
            break;
        case 'b':
            ll_sort(pArrayListEmployee,compararPorNombre,orden);
            break;
        case 'c':
            ll_sort(pArrayListEmployee,compararPorHoras,orden);
            break;
        case 'd':
            ll_sort(pArrayListEmployee,compararPorSueldos,orden);
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
        retorno=0;
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char* Nombre del archivo en el que se escribira
 * \param pArrayListEmployee LinkedList* Array de empleados
 * \return int 0 si salio todo bien y sino -1
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    FILE* pFile;
    int len;
    Employee* auxE;
    int auxId;
    char auxNombre[128];
    int auxHoras;
    int auxSueldo;
    if(path!=NULL&&pArrayListEmployee!=NULL)
    {
        pFile=fopen(path,"w");
        if(pFile!=NULL)
        {
            len=ll_len(pArrayListEmployee);
            fprintf(pFile,"id,nombre,horasTrabajadas,sueldo\n");//encabezado
            for(int i=0;i<len;i++)
            {
                auxE=ll_get(pArrayListEmployee,i);
                if(auxE!=NULL)
                {
                    if(!employee_getId(auxE,&auxId)&&
                       !employee_getNombre(auxE,auxNombre)&&
                       !employee_getHorasTrabajadas(auxE,&auxHoras)&&
                       !employee_getSueldo(auxE,&auxSueldo))
                    {
                        fprintf(pFile,"%d,%s,%d,%d\n",auxId,auxNombre,auxHoras,auxSueldo);
                        retorno=0;
                    }
                }
            }
            fclose(pFile);
        }
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char* Nombre del archivo en el que se escribira
 * \param pArrayListEmployee LinkedList*
 * \return int 0 si salio todo bien y sino -1
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    int len;
    Employee* auxE;
    FILE* pFile;
    if(path!=NULL&&pArrayListEmployee!=NULL)
    {
        pFile=fopen(path,"wb");
        if(pFile!=NULL)
        {
            len=ll_len(pArrayListEmployee);
            for(int i=0;i<len;i++)//
            {
                auxE=ll_get(pArrayListEmployee,i);
                if(auxE!=NULL)//el empleado existe
                {
                    fwrite(auxE,sizeof(Employee),1,pFile);
                    retorno=0;
                }
            }
            fclose(pFile);
        }
    }
    return retorno;
}
