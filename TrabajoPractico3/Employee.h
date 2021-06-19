#include "LinkedList.h"

#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

/** \brief crea un nuevo empleado en la memoria dinamica
 *
 * \return Employee* puntero al nuevo empleado
 *
 */
Employee* employee_new();

/** \brief crea un nuevo empleado en la memoria dinamica y carga sus campos
 *
 * \param idStr char* Id a cargar al nuevo empleado
 * \param nombreStr char* Nombre a cargar al nuevo empleado
 * \param horasTrabajadasStr char* Horas a cargar al nuevo empleado
 * \param sueldoStr char* Sueldo a cargar al nuevo empleado
 * \return Employee*
 *
 */
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr);

/** \brief libera la memoria que ocupa un empleado y hace que apunte a NULL
 *
 * \param this Employee* puntero a empleado a borrar
 * \return void
 *
 */
void employee_delete(Employee* this);

/** \brief busca el indice de un empleado segun su id
 *
 * \param pArrayEmpleados LinkedList* array de punteros a empleados
 * \param id int El id a buscar
 * \return int -1 si no se encontro un empleado con ese id y sno el indice de donde esta
 *
 */
int findEmployeeById(LinkedList* pArrayEmpleados,int id);


/** \brief setter del campo id
 *
 * \param this Employee* puntero a empleado en el que cagrar ese id
 * \param id int Id a cargar
 * \return int 0 si salio todo bien y sino -1
 *
 */
int employee_setId(Employee* this,int id);

/** \brief Getter del campo id
 *
 * \param this Employee* empleado del que se tomara el id
 * \param id int* Puntero a id en el que se cargara el id de ese empleado
 * \return int 0 si salio todo bien y sino -1
 *
 */
int employee_getId(Employee* this,int* id);

/** \brief setter del campo nombre
 *
 * \param this Employee* puntero a empleado en el que cagara ese nombre
 * \param char* nombre Nombre a cargar
 * \return int 0 si salio todo bien y sino -1
 *
 */
int employee_setNombre(Employee* this,char* nombre);

/** \brief Getter del campo nombre
 *
 * \param this Employee* empleado del que se tomara el nombre
 * \param nombre Char* Puntero a nombre en el que se cargara el nombre de ese empleado
 * \return int 0 si salio todo bien y sino -1
 *
 */
int employee_getNombre(Employee* this,char* nombre);


/** \brief setter del campo horasTrabajadas
 *
 * \param this Employee* puntero a empleado en el que cagrar esa cantidad de horas
 * \param horas int Cantidad de horas a cargar
 * \return int 0 si salio todo bien y sino -1
 *
 */
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);

/** \brief Getter del campo id
 *
 * \param this Employee* empleado del que se tomara el id
 * \param id int* Puntero a id en el que se cargara el id de ese empleado
 * \return int 0 si salio todo bien y sino -1
 *
 */
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

/** \brief setter del campo id
 *
 * \param this Employee* puntero a empleado en el que cagrar ese id
 * \param id int Id a cargar
 * \return int 0 si salio todo bien y sino -1
 *
 */
int employee_setSueldo(Employee* this,int sueldo);

/** \brief Getter del campo id
 *
 * \param this Employee* empleado del que se tomara el id
 * \param id int* Puntero a id en el que se cargara el id de ese empleado
 * \return int 0 si salio todo bien y sino -1
 *
 */
int employee_getSueldo(Employee* this,int* sueldo);

/** \brief muestra a un empleado
 *
 * \param empleado Employee* puntero al empleado a mostrar
 * \return int 0 si salio todo bien y sino -1
 *
 */
int mostrarEmpleado(Employee* empleado);

/** \brief compara a dos empleados por id
 *
 * \param emp1 void* puntero a uno de los empleados a comparar
 * \param emp2 void* puntero de otro de los empleados a comparar
 * \return int -1 si el id de emp1 es mayor al de emp 2, 1 si viceversa o 0 si son iguales
 *
 */
int compararPorId(void* emp1,void* emp2);

/** \brief compara a dos empleados por nombre
 *
 * \param emp1 void* puntero a uno de los empleados a comparar
 * \param emp2 void* puntero de otro de los empleados a comparar
 * \return int -1 si el nombre de emp1 es mayor al de emp 2, 1 si viceversa o 0 si son iguales
 *
 */
int compararPorNombre(void* emp1,void* emp2);

/** \brief compara a dos empleados por horas trabajadas
 *
 * \param emp1 void* puntero a uno de los empleados a comparar
 * \param emp2 void* puntero de otro de los empleados a comparar
 * \return int -1 si el horas trabajadas de emp1 es mayor al de emp 2, 1 si viceversa o 0 si son iguales
 *
 */
int compararPorHoras(void* emp1,void* emp2);

/** \brief compara a dos empleados por sueldo
 *
 * \param emp1 void* puntero a uno de los empleados a comparar
 * \param emp2 void* puntero de otro de los empleados a comparar
 * \return int -1 si el sueldo de emp1 es mayor al de emp 2, 1 si viceversa o 0 si son iguales
 *
 */
int compararPorSueldos(void* emp1,void* emp2);

#endif // employee_H_INCLUDED
