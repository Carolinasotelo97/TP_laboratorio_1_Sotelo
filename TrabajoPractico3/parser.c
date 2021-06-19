#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    int cant;
    char buffer[4][128];//guardo todo lo que hay en el csv como texto
    Employee* newEmployee;

    if(pFile!=NULL&&pArrayListEmployee!=NULL)
    {
        fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3]);//encabezado

        while(!feof(pFile))
        {
            cant=fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3]);
            if(cant==4)//como hay 4 campos cant tiene que ser igual a 4
            {
                newEmployee=employee_newParametros(buffer[0],buffer[1],buffer[2],buffer[3]);
                if(newEmployee!=NULL)//salio todo bien y se pudo cargar al empleado
                {
                    ll_add(pArrayListEmployee,newEmployee);
                    retorno=0;
                }//fin newEmployee
            }else
            {
                break;
            }
        }
    }//fin validacion parametros
    return retorno;
}
/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    Employee* newEmployee=NULL;
    if(pFile!=NULL&&pArrayListEmployee!=NULL)
    {
        fread(newEmployee,sizeof(Employee),1,pFile);//leo el encabazado
        while(!feof(pFile))
        {
            newEmployee=employee_new();
            if(newEmployee!=NULL)//salio todo bien y se pudo hacer un nuevo empleado
            {
                if(fread(newEmployee,sizeof(Employee),1,pFile))//si la funcion no retorna 0
                {
                    ll_add(pArrayListEmployee,newEmployee);
                    retorno=0;
                }
                //fin newEmployee
            }else
            {
                break;
            }
        }
    }//fin validacion parametros
    return retorno;
}
