#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn_biblioteca.h"
#include "Employee.h"
#include "FuncionesVarias.h"
#include "parser.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		FILE* pArch = fopen(path,"r");

		parser_EmployeeFromText(pArch, pArrayListEmployee);

		fclose(pArch);

		retorno = 0;
	}

    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		FILE* pArch = fopen(path,"rb");

		parser_EmployeeFromBinary(pArch, pArrayListEmployee);

		fclose(pArch);
		retorno = 0;
	}
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	char nombreAux[128];
	int horasAux;
	int salarioAux;
	int idAux;
	int retorno = -1;

	if(pArrayListEmployee!=NULL)
	{
		Employee* thisAux = employee_new();

		if(	utn_getText(nombreAux, 128, "Nombre: ", "Mal")==0 &&
			utn_getNumero(&horasAux, "Horas trabajadas: ", "Err Horas")==0 &&
			utn_getNumero(&salarioAux, "Salario: ", "Err Salario")==0)
		{
			idAux = employee_generadorID()+1000;

			employee_setNombre(thisAux, nombreAux);
			employee_setHorasTrabajadas(thisAux, horasAux);
			employee_setSueldo(thisAux, salarioAux);
			employee_setId(thisAux, idAux);

			ll_add(pArrayListEmployee, thisAux);

			retorno = 0;
		}
	}

    return retorno;


}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int i;
	int idAux;
	int idAuxBuscado;
	int opcionAux;
	char nombreAux[128];
	int horasAux;
	int sueldoAux;
	int retorno = -1;
	Employee* aux;

	if(pArrayListEmployee!=NULL)
	{
		if(utn_getNumero(&idAuxBuscado, "ID a editar: ", "Err. edit")==0)
		{
			for(i=0;i<ll_len(pArrayListEmployee);i++)
			{
				aux = ll_get(pArrayListEmployee, i);

				employee_getId(aux, &idAux);

				if(idAux == idAuxBuscado)
				{
					printf(	"\nNombre: %s\n"
							"Horas: %d\n"
							"Sueldo: %d\n"
							"ID: %d\n",aux->nombre,aux->horasTrabajadas,aux->sueldo,aux->id);
					break;
				}
			}
		}


		if(utn_getNumero(&opcionAux,"\nDato a modificar:\n"
									"1) Nombre\n"
									"2) Horas\n"
									"3) Sueldo\n", "Err. edit2")==0)
		{

			switch(opcionAux)
			{
				case 1:
					if(	utn_getText(nombreAux, 128, "\nNuevo nombre: ", "Mal")==0)
					{
						employee_setNombre(aux, nombreAux);
						retorno = 0;
					}
					break;

				case 2:
					if(utn_getNumero(&horasAux, "Cantidad de horas: ", "Maaal")==0)
					{
						employee_setHorasTrabajadas(aux, horasAux);
						retorno = 0;
					}
					break;

				case 3:
					if(utn_getNumero(&sueldoAux, "Nuevo Sueldo: ", "Moool")==0)
					{
						employee_setSueldo(aux, sueldoAux);
						retorno = 0;
					}
					break;
			}
		}

}
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int i;
	int idAux;
	int idAuxBuscado;
	int indexAux;
	int opcionAux;
	int retorno = -1;
	Employee* aux;

	if(pArrayListEmployee!=NULL)
	{
		if(utn_getNumero(&idAuxBuscado, "ID a eliminar", "Err. remove")==0)
		{

			for(i=0;i<ll_len(pArrayListEmployee);i++)
			{
				aux = ll_get(pArrayListEmployee, i);

				employee_getId(aux, &idAux);

				if(idAuxBuscado == idAux)
				{
					indexAux = i;
					printf(	"Nombre: %s\n"
							"Horas: %d\n"
							"Sueldo: %d\n"
							"ID: %d\n",aux->nombre,aux->horasTrabajadas,aux->sueldo,aux->id);
					break;
				}
			}

			utn_getNumero(&opcionAux, 	"¿Eliminar?"
										"1) Confirma"
										"2) Cancela", "Err. remove2");

			switch(opcionAux)
			{
			case 1:
				employee_delete(aux);
				ll_remove(pArrayListEmployee, indexAux);
				retorno = 0;
				break;

			case 2:
				puts("Cancelado\n");
				break;
			}
		}
	}

	return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	Employee* aux;

	if(pArrayListEmployee!=NULL)
	{
		printf("ID Nombre Horas Sueldo\n");
		for(i=0;i<ll_len(pArrayListEmployee);i++)
		{
			aux = ll_get(pArrayListEmployee, i);

			printf(	"%d,%s,%d,%d\n",aux->id,aux->nombre,aux->horasTrabajadas,aux->sueldo);
		}
		printf("\n");
		retorno = 0;
	}
    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	if(pArrayListEmployee!=NULL)
	{
		puts("\nOrdenando...\n");
		ll_sort(pArrayListEmployee, employee_comparaEmpleados, 1);
		puts("Lista ordenada\n");
		retorno = 0;
	}
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	Employee* aux;
	FILE* pArch = fopen(path,"w");

	if(pArch!=NULL)
	{
		fprintf(pArch,"ID Nombre Horas Sueldo\n");

		for(i=0;i<ll_len(pArrayListEmployee);i++)
		{
			aux = ll_get(pArrayListEmployee, i);

			fprintf(pArch,"%d,%s,%d,%d\n",aux->id,aux->nombre,aux->horasTrabajadas,aux->sueldo);
		}

		fclose(pArch);
		retorno = 0;
	}

    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    return 1;
}



