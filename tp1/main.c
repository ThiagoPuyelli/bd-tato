#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Cliente {
    char nombre[30];
    char apellido[30];
    int cliente;
};

void agregar ();
void menu ();
void mostrarClientes ();
void mostrarCliente (struct Cliente * cliente);
void modificar ();

int main () {
    menu();
    return 0;
}

void menu () {
    int opcion;

    do {
      printf("Inicio de programa de clientes\n");
      printf("Seleccione 0 si quiere agregar un cliente\n");
      printf("Seleccione 1 si quiere modificar un cliente\n");
      printf("Seleccione 2 si quiere borrar un cliente\n");
      printf("Seleccione 3 si quiere mostrar los clientes\n");
      printf("Seleccione 4 para salir del programa\n");
      scanf("%d", &opcion);
      
      switch (opcion) {
        case 0:
          agregar();
          break;
        case 1:
          modificar();
          break;
        case 3:
          mostrarClientes();
          break;
        default:
          printf("La opcion ingresada no es valida\n");
          break;
      }
    } while (opcion != 4);
}

void agregar () {
    struct Cliente cliente;
    printf("\nIngrese codigo del cliente: ");
    scanf("%d", &(cliente.cliente));
    printf("Ingrese nombre del cliente: ");
    scanf("%s", &(cliente.nombre));
    printf("\nIngrese apellido del cliente: ");
    scanf("%s", &(cliente.apellido));

    FILE * fp = fopen("clientes.dat", "wb");
    fwrite(&cliente, sizeof(struct Cliente), 1, fp);
    fclose(fp);

    printf("\n\n Cliente ingresado\n\n");
}

void modificar () {
    int pos;
    FILE * fp = fopen("clientes.dat", "rb+");
    printf("Ingrese la posicion del registro a modificar: ");
    scanf("%d", &pos);
    fseek(fp, sizeof(struct Cliente) * pos, SEEK_SET);
    struct Cliente cliente;
    fread(&cliente, sizeof(struct Cliente), 1, fp);
    fflush(stdin);

    printf("\n Cliente a modificar:\n");
    mostrarCliente(&cliente);
    printf("Que dato quiere cambiar?: ");
    char dato;
    scanf(" %c", &dato);
    printf("\nIngrese el nuevo dato: ");
    switch (dato) {
      case 'c':
        scanf("%d", &(cliente.cliente));
      case 'n':
        scanf("%s", &(cliente.nombre));
      case 'a':
        scanf("%s", &(cliente.apellido));
    }

    fseek(fp, sizeof(struct Cliente) * pos, SEEK_SET);
    fwrite(&cliente, sizeof(struct Cliente), 1, fp);
    fclose(fp);
    printf("\nCliente modificado");
}

void mostrarCliente (struct Cliente * cliente) {
    printf("\n Cliente: %d\n", (*cliente).cliente);
    printf("\n Nombre: %s\n", (*cliente).nombre);
    printf("\n Apellido: %s\n\n", (*cliente).apellido);
}

void mostrarClientes () {
    struct Cliente cliente;
    FILE * fp = fopen("clientes.dat", "r");
    while (!feof(fp)) {
      fread(&cliente, sizeof(struct Cliente), 1, fp);
      mostrarCliente(&cliente);
    }
}