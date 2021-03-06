#include "validaciones.h"
#include "ArrayEmployees.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int menu()
{
    system("cls");
    int opcion;
    printf("****ADMINISTRAR EMPLEADOS****\n\n");
    printf("1-Alta de empleado\n");
    printf("2-Modificar empleado\n");
    printf("3-Baja empleado\n");
    printf("4-Informes\n");
    printf("5-Salir\n");
    opcion = getInt("Ingrese una opcion:","Esa opcion no es valida:");
    return opcion;
}
void inicializarEmpleados(eEmpleado listaEmpleados[],int cant)
{
    for(int i = 0;i<cant;i++)
    {
        listaEmpleados[i].isEmpty = 0;
    }
}
eEmpleado cargarEmpleado(int id)
{
    eEmpleado miEmpleado;
    miEmpleado.id = id;
    getString(miEmpleado.name,51,"Ingrese nombre:","Ese no es un nombre valido:");
    getString(miEmpleado.lastName,51,"Ingrese apellido:","Ese no es un apellido valido:");
    miEmpleado.salary = getFloat("Ingrese sueldo:","Ese no es un sueldo valido:");
    miEmpleado.sector = getInt("Ingrese sector:","Ese no es un sector valido:");
    miEmpleado.isEmpty = 1;
    return miEmpleado;
}
void cargarTodosLosEmpleados(eEmpleado listaEmpleados[],int cant,int id)
{
    system("cls");
    printf("****INGRESO DE EMPLEADOS****\n\n");
    int i;
    i = buscarLibre(listaEmpleados,cant);
    if(i==-1)
    {
        printf("No hay mas espacio disponible\n");
    }
    else{
        listaEmpleados[i] = cargarEmpleado(id);
        printf("Carga realizada con exito\n");
    }
}
int buscarLibre(eEmpleado listaEmpleados[],int cant)
{
    int index = -1;
    int i;
    for(i=0;i<cant;i++)
    {
        if(listaEmpleados[i].isEmpty == 0)
        {
            index = i;
            break;
        }
    }
    return index;
}
void mostrarUnEmpleado(eEmpleado unEmpleado)
{
    printf("%d   %s    %s      %.3f        %d\n",unEmpleado.id,unEmpleado.name,unEmpleado.lastName,unEmpleado.salary,unEmpleado.sector);
}
void mostrarNominaEmpleados(eEmpleado listaEmpleados[],int cant)
{
    system("cls");
    printf("****LISTA DE EMPLEADOS****\n\n");
    printf("ID     Nombre    Apellido  Sueldo      Sector\n");
    int i;
    for(i=0;i<cant;i++)
    {
       if(listaEmpleados[i].isEmpty == 1)
       {
           mostrarUnEmpleado(listaEmpleados[i]);
       }
    }
}
void modificarEmpleado(eEmpleado listaEmpleados[],int cant)
{
    int legajo;
    int pregunta;
    int estado;
    system("cls");
    printf("****Modificar empleados****\n\n");
    mostrarNominaEmpleados(listaEmpleados,cant);
    legajo = getInt("Ingrese el id del empleado que desea modificar:","Ese no es un numero de id valido:");
    estado = verificarSiEsta(listaEmpleados,cant,legajo);
    if(estado == -1)
    {
        printf("Ese id no existe, ingrese un id de la lista\n");
    }
    else{
        pregunta = preguntarModificacion();
        confirmarModificacion(listaEmpleados,cant,estado,pregunta);
    }
}
int preguntarModificacion()
{
    int estado = 0;
    char pregunta[50];
    getString(pregunta,50,"Esta seguro que desea modificar el usuario?","Esa no es una respuesta valida");
    if(strcmp(pregunta,"si")==0)
    {
        estado = 1;
    }
    return estado;
}
void confirmarModificacion(eEmpleado listaEmpleados[],int cant,int legajo,int dato)
{
    if(dato == 1)
    {
            opcionesDeModificar(listaEmpleados,legajo);
            printf("Modificacion realizada con exito\n");
    }
    else{
            printf("Modificacion cancelada\n");
    }
}
void opcionesDeModificar(eEmpleado lista[],int legajo)
{
    char seguir = 's';
    char confirmar;
    do{
    switch(menuModificar())
    {
    case 1:
        getString(lista[legajo].name,25,"Ingrese nuevo nombre:","Ese no es un nombre valido:");
        break;
    case 2:
        getString(lista[legajo].lastName,25,"Ingrese nuevo apellido:","Ese no es un apellido valido:");
        break;
    case 3:
        lista[legajo].salary = getFloat("Ingrese nuevo sueldo:","Ese no es un sueldo valido:");
        break;
    case 4:
        lista[legajo].sector =  getInt("Ingrese nuevo sector:","Ese no es un sector valido:");
        break;
    case 5:
        confirmar = getChar("Si desea seguir realizando modificaciones presione n,de lo contrario pulse s:","Ese no es un valor valido:");
        if(confirmar == 's')
        {
            seguir='n';
        }
        break;
    }
    }while(seguir == 's');
}
int verificarSiEsta(eEmpleado listaEmpleados[],int cant,int dato)
{
    int i;
    int estado = -1;
    for(i=0;i<cant;i++)
    {
        if(listaEmpleados[i].id == dato && listaEmpleados[i].isEmpty == 1)
        {
            estado = i;
            break;
        }
    }
    return estado;
}
int menuModificar()
{
    system("cls");
    int opcion;
    printf("****OPCIONES PARA MODIFICAR****\n\n");
    printf("1-Cambiar nombre\n");
    printf("2-Cambiar apellido\n");
    printf("3-Cambiar sueldo\n");
    printf("4-Cambiar sector\n");
    printf("5-Salir\n");
    opcion = getInt("Ingrese una opcion:","Esa opcion no es valida:");
    return opcion;
}
void eliminarEmpleados(eEmpleado listaEmpleados[],int cant)
{
    int legajo;
    int pregunta;
    int estado;
    system("cls");
    printf("****Eliminar empleados****\n\n");
    mostrarNominaEmpleados(listaEmpleados,cant);
    legajo = getInt("Ingrese el id del empleado que desea eliminar:","Ese no es un numero de id valido:");
    estado = verificarSiEsta(listaEmpleados,cant,legajo);
    if(estado == -1)
    {
        printf("Ese id no existe, ingrese un id de la lista\n");
    }
    else{
        pregunta = preguntar();
        confirmarEliminacion(listaEmpleados,cant,legajo,pregunta);
    }
}
void eliminar(eEmpleado listaEmpleados[],int cant,int dato)
{
    int i;
    for(i=0;i<cant;i++)
    {
        if(listaEmpleados[i].id == dato && listaEmpleados[i].isEmpty == 1)
        {
            listaEmpleados[i].isEmpty = 0;
        }
    }
}
int preguntar()
{
    int estado = 0;
    char pregunta[50];
    getString(pregunta,50,"Esta seguro que desea eliminar el usuario?","Esa no es una respuesta valida");
    if(strcmp(pregunta,"si")==0)
    {
        estado = 1;
    }
    return estado;
}
void confirmarEliminacion(eEmpleado listaEmpleados[],int cant,int legajo,int respuesta)
{
    if(respuesta ==1)
    {
            eliminar(listaEmpleados,cant,legajo);
            printf("Baja realizada con exito\n");
    }
    else{
            printf("Baja cancelada\n");
    }
}
int menuInformar()
{
    system("cls");
    int opcion;
    printf("****INFORMES****\n\n");
    printf("1-Listado de empleados ordenados alfabeticamente por apellido y sector\n");
    printf("2-Total y promedio de los salarios,y cuantos empleados superan el salario promedio\n");
    printf("3-Salir\n");
    opcion = getInt("Ingrese una opcion:","Esa opcion no es valida:");
    return opcion;
}
void opcionesInformes(eEmpleado lista[],int cant)
{
    char seguir = 's';
    char confirmar;
    do{
    switch(menuInformar())
    {
    case 1:
        ordenarEmpleados(lista,cant);
        system("cls");
        printf("LISTA DE EMPLEADOS ORDENADOS\n");
        mostrarNominaEmpleados(lista,cant);
        break;
    case 2:
        totalYpromedioSalarios(lista,cant);
        break;
    case 3:
        confirmar = getChar("Si desea seguir viendo informes presione n,de lo contrario pulse s:","Ese no es un valor valido:");
        if(confirmar == 's')
        {
            seguir='n';
        }
        break;
    }
    system("pause");
    }while(seguir == 's');
}
void opcionesPrincipales(eEmpleado listaEmpleados[],int cant,int id)
{
    char seguir = 's';
    char confirmar;
    int flag;
    do{
    switch(menu())
    {
    case 1:
        cargarTodosLosEmpleados(listaEmpleados,cant,id);
        id++;
        flag = 1;
        break;
    case 2:
        if(flag == 1)
        {
            modificarEmpleado(listaEmpleados,cant);
        }
        else{
            printf("Para usar esta opcion primero ingrese un empleado\n");
        }
        break;
    case 3:
        if(flag == 1)
        {
            eliminarEmpleados(listaEmpleados,cant);
        }
        else{
            printf("Para usar esta opcion primero ingrese un empleado\n");
        }
        break;
    case 4:
        if(flag == 1)
        {
            opcionesInformes(listaEmpleados,cant);
        }
        else{
            printf("Para usar esta opcion primero ingrese un empleado\n");
        }
        break;
    case 5:
        confirmar = getChar("Esta seguro que desea salir?:","Ese no es un valor valido:");
        if(confirmar == 's')
        {
            seguir='n';
        }
        break;
    }
    system("pause");
    }while(seguir == 's');
}
float totalYpromedioSalarios(eEmpleado listaEmpleados[],int cant)
{
    float acumulador;
    float promedio;
    int contador;
    int superanElPromedio;
    acumulador = acumular(listaEmpleados,cant);
    contador = contarEmpleados(listaEmpleados,cant);
    promedio = acumulador / contador;
    superanElPromedio = cantidadEmpleadosQueSuperanSalarioPromedio(listaEmpleados,cant,promedio);
    mostrarPromediosYsalarios(contador,acumulador,superanElPromedio,promedio);
    return 0;
}
int contarEmpleados(eEmpleado listaEmpleados[],int cant)
{
    int i;
    int contador = 0;
    for(i=0;i<cant;i++)
    {
        if(listaEmpleados[i].isEmpty == 1)
        {
            contador++;
        }
    }
    return contador;
}
int cantidadEmpleadosQueSuperanSalarioPromedio(eEmpleado listaEmpleados[],int cant,int dato)
{
    int i;
    int cantidadSuperan = 0;
    for(i=0;i<cant;i++)
    {
        if(listaEmpleados[i].isEmpty == 1 && listaEmpleados[i].salary>dato)
        {
            cantidadSuperan++;
        }
    }
    return cantidadSuperan;
}
float acumular(eEmpleado listaEmpleados[],int cant)
{
    int i;
    float acumulador = 0;
    for(i=0;i<cant;i++)
    {
        if(listaEmpleados[i].isEmpty == 1)
        {
            acumulador = acumulador + listaEmpleados[i].salary;
        }
    }
    return acumulador;
}
void mostrarPromediosYsalarios(int contador,float acumulador,int SuperanPromedio,float promedio)
{
    system("cls");
    printf("***RESULTADOS INFORME 2:\n\n");
    printf("La cantidad total de los sueldos es %.3f\n",acumulador);
    printf("El salario promedio de los empleados es %.3f\n",promedio);
    printf("La cantidad de empleados que superan el salario promedio es %d\n",SuperanPromedio);
}
void ordenarEmpleados(eEmpleado listaEmpleados[],int cant)
{
    int i;
    int j;
    eEmpleado auxString;
    for(i=0;i<cant-1;i++)
    {
        for(j=i+1;j<cant;j++)
        {
            if(strcmpi(listaEmpleados[i].name,listaEmpleados[j].name)>0)
            {
                auxString = listaEmpleados[i];
                listaEmpleados[i] = listaEmpleados[j];
                listaEmpleados[j] = auxString;
            }
            if(listaEmpleados[i].name[0] == listaEmpleados[j].name[0] && listaEmpleados[i].sector <listaEmpleados[j].sector)
            {
                auxString = listaEmpleados[i];
                listaEmpleados[i] = listaEmpleados[j];
                listaEmpleados[j] = auxString;
            }
        }
    }
}
