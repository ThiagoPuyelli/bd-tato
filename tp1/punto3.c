#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tipo_elemento.c"
#include "listasArray.c"
#include "tipoRegistro.h"

void menuCampo ();
void menuRegistro ();
void altaRegistro (Lista lista);
void bajaRegistro ();
void modificacionRegistro ();
void mostrarRegistros (Lista lista);
Lista listaCampos ();

int main () {
  FILE * fp = fopen("metadata.dat", "rb");
  if (!fp) {
    menuCampo();
  } else {
    menuRegistro();
  }
  return 0;
}

void menuCampo () {
  int cantidad;
  printf("Cantidad de campos: ");
  scanf("%d", &cantidad);
  printf("\n");
  int i = 0;
  struct TipoRegistro reg[20];
  char nombre[30];
  while (i < cantidad) {
    printf("\nIngrese el nombre del campo: ");
    scanf("%s", &nombre);
    strcpy(reg[i].nombre, nombre);
    printf("\nIngrese el cantidad de caracteres del campo: ");
    scanf("%d", &(reg[i].cantidad));
    i++;
  }
  for (i = 0;i < cantidad;i++) {
    printf("%d %s", reg[i].cantidad, reg[i].nombre);
  }
  FILE * fp = fopen("metadata.dat", "wb");
  fwrite(reg, sizeof(struct TipoRegistro), cantidad, fp);
};

void menuRegistro () {
  int opcion;

  Lista campos = listaCampos();

  l_mostrarLista(campos);

  do {
    printf("Elija la opcion\n");
    printf("1: Agregar registro\n");
    printf("2: Eliminar registro\n");
    printf("3: Modificar registro\n");
    printf("4: Mostrar registros\n");
    printf("5: Salir\n");
    scanf("%d", &opcion);
    switch (opcion){
      case 1:
        altaRegistro(campos);
        break;
      case 2:
        //bajaRegistro();
        break;
      case 3:
        //modificacionRegistro();
        break;
      case 4:
        mostrarRegistros(campos);
        break;
      case 5:
        printf("Saliste del programa");
      default:
        printf("Input invalido\n");
    }

  } while (opcion != 5);
}

Lista listaCampos() {
  FILE * fp = fopen("metadata.dat", "rb");
  Lista campos = l_crear();
  struct TipoRegistro reg[20];
  int i = 0;
  while (fread(&(reg[i]), sizeof(struct TipoRegistro), 1, fp)) {
    struct TipoRegistro * registro = malloc(sizeof(struct TipoRegistro));
    strcpy(registro->nombre, reg[i].nombre);
    registro->cantidad = reg[i].cantidad;
    l_agregar(campos, te_crear_con_valor(0, registro));
    i++;
  }
  return campos;
}

void altaRegistro (Lista lista) {
  char campos[10][10];
  Iterador ite = iterador(lista);
  TipoElemento elemento;
  int i = 0;
  int size = 0;
  while (hay_siguiente(ite)) {
    elemento = siguiente(ite);
    struct TipoRegistro *registro = (struct TipoRegistro*)(elemento->valor);
    printf("Ingrese el %s\n", registro->nombre);
    scanf("%s", campos[i]);
    size += (registro->cantidad * sizeof(char));
    i++;
  }
  FILE * fp = fopen("registros.dat", "wb");
  fwrite(campos, size, i, fp);
  fclose(fp);
}

void mostrarRegistros (Lista lista) {
  FILE * fp = fopen("registros.dat", "rb");
  if (fp) {
    Iterador ite = iterador(lista);
    char campo[10];
    TipoElemento elemento;
    while (!feof(fp)) {
      while (hay_siguiente(ite)) {
        elemento = siguiente(ite);
        struct TipoRegistro *registro = (struct TipoRegistro*)(elemento->valor);
        fread(&campo, sizeof(sizeof(char) * 10), 1, fp);
        printf("%s: %s %d\n", registro->nombre, campo, registro->cantidad);
      }
      ite = iterador(lista);
    }
  }
  fclose(fp);
}