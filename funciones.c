#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu() {
    int opcion;
    printf("\n--- Menu ---\n");
    printf("1. Crear factura\n");
    printf("2. Leer facturas\n");
    printf("3. Actualizar factura\n");
    printf("4. Borrar factura\n");
    printf("5. Salir\n");
    printf(">> ");
    scanf("%d", &opcion);
    return opcion;
}

void savefactura(struct Factura *factura) {
    FILE *file = fopen("factura.dat", "ab+");
    if (file == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }
    fwrite(factura, sizeof(struct Factura), 1, file);
    printf("Factura guardada exitosamente\n");
    fclose(file);
}

void leerCadena(char *cadena, int num) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(cadena, num, stdin);
    int len = strlen(cadena);
    if (len > 0 && cadena[len - 1] == '\n') {
        cadena[len - 1] = '\0';
    }
}

int validarCedulaUnica(int cedula) {
    FILE *file = fopen("factura.dat", "rb");
    struct Factura factura;

    if (file == NULL) return 1; // Si no existe archivo, no hay duplicados

    while (fread(&factura, sizeof(struct Factura), 1, file)) {
        if (factura.cedula == cedula) {
            fclose(file);
            return 0; // Cedula duplicada
        }
    }

    fclose(file);
    return 1; // Cedula única
}

void crateFactura() {
    struct Factura factura;

    printf("Ingrese la cedula del cliente: ");
    scanf("%d", &factura.cedula);
    while (factura.cedula <= 0 || !validarCedulaUnica(factura.cedula)) {
        if (factura.cedula <= 0) {
            printf("La cedula no puede ser negativa o cero. Intente nuevamente: ");
        } else {
            printf("La cedula ya existe. Intente nuevamente: ");
        }
        scanf("%d", &factura.cedula);
    }

    printf("Ingrese el nombre del cliente: ");
    leerCadena(factura.nombre, 20);

    printf("Ingrese el numero de productos: ");
    scanf("%d", &factura.numProductos);
    while (factura.numProductos <= 0) {
        printf("El numero de productos debe ser mayor que cero. Intente nuevamente: ");
        scanf("%d", &factura.numProductos);
    }

    factura.total = 0;
    for (int i = 0; i < factura.numProductos; i++) {
        printf("\nProducto %d\n", i + 1);

        printf("  Ingrese el nombre del producto: ");
        leerCadena(factura.productos[i].nombre, 50);

        printf("  Ingrese la cantidad del producto: ");
        scanf("%d", &factura.productos[i].cantidad);
        while (factura.productos[i].cantidad <= 0) {
            printf("La cantidad no puede ser negativa o cero. Intente nuevamente: ");
            scanf("%d", &factura.productos[i].cantidad);
        }

        printf("  Ingrese el precio del producto: ");
        scanf("%f", &factura.productos[i].precio);
        while (factura.productos[i].precio <= 0) {
            printf("El precio no puede ser negativo o cero. Intente nuevamente: ");
            scanf("%f", &factura.productos[i].precio);
        }

        factura.total += factura.productos[i].cantidad * factura.productos[i].precio;
    }

    savefactura(&factura);
}

void readFactura() {
    FILE *file = fopen("factura.dat", "rb");
    struct Factura factura;

    if (file == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    printf("\n--- Lista de Facturas ---\n");
    while (fread(&factura, sizeof(struct Factura), 1, file)) {
        printf("\nCedula: %d\n", factura.cedula);
        printf("Nombre del cliente: %s\n", factura.nombre);
        printf("Total: %.2f\n", factura.total);
        printf("Productos:\n");
        for (int i = 0; i < factura.numProductos; i++) {
            printf("  Producto %d: %s\n", i + 1, factura.productos[i].nombre);
            printf("    Cantidad: %d\n", factura.productos[i].cantidad);
            printf("    Precio: %.2f\n", factura.productos[i].precio);
        }
    }
    fclose(file);
}


void updateFactura() {
    int cedula, found = 0;
    printf("Ingrese la cedula de la factura a actualizar: ");
    scanf("%d", &cedula);

    FILE *file = fopen("factura.dat", "rb+");
    if (file == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    struct Factura factura;
    while (fread(&factura, sizeof(struct Factura), 1, file)) {
        if (factura.cedula == cedula) {
            found = 1;
            printf("Factura encontrada. ¿Qué desea actualizar?\n");
            printf("1. Nombre del cliente\n");
            printf("2. Productos\n");
            printf(">> ");
            int opcion;
            scanf("%d", &opcion);

            switch (opcion) {
                case 1:
                    printf("Ingrese el nuevo nombre del cliente: ");
                    leerCadena(factura.nombre, 20);
                    break;

                case 2:
                    printf("Ingrese el numero de productos: ");
                    scanf("%d", &factura.numProductos);
                    while (factura.numProductos <= 0) {
                        printf("El numero de productos debe ser mayor que cero. Intente nuevamente: ");
                        scanf("%d", &factura.numProductos);
                    }

                    factura.total = 0; // Reinicia el total y lo recalcula
                    for (int i = 0; i < factura.numProductos; i++) {
                        printf("\nProducto %d\n", i + 1);

                        printf("  Ingrese el nombre del producto: ");
                        leerCadena(factura.productos[i].nombre, 50);

                        printf("  Ingrese la cantidad del producto: ");
                        scanf("%d", &factura.productos[i].cantidad);
                        while (factura.productos[i].cantidad <= 0) {
                            printf("La cantidad no puede ser negativa o cero. Intente nuevamente: ");
                            scanf("%d", &factura.productos[i].cantidad);
                        }

                        printf("  Ingrese el precio del producto: ");
                        scanf("%f", &factura.productos[i].precio);
                        while (factura.productos[i].precio <= 0) {
                            printf("El precio no puede ser negativo o cero. Intente nuevamente: ");
                            scanf("%f", &factura.productos[i].precio);
                        }

                        factura.total += factura.productos[i].cantidad * factura.productos[i].precio;
                    }
                    break;

                default:
                    printf("Opcion no válida. No se realizaron cambios.\n");
                    break;
            }

            // Posicionar el puntero al inicio del registro actual
            fseek(file, -(long)sizeof(struct Factura), SEEK_CUR);
            fwrite(&factura, sizeof(struct Factura), 1, file);
            printf("Factura actualizada correctamente.\n");
            break;
        }
    }

    if (!found) {
        printf("Factura no encontrada.\n");
    }

    fclose(file);
}


void deleteFactura() {
    printf("Esta funcion no elimina directamente para evitar problemas de manipulacion directa del archivo.\n");
}