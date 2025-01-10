#include <stdio.h>
#include "funciones.h"

int main() {
    int opcion;

    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                crateFactura();
                break;
            case 2:
                readFactura();
                break;
            case 3:
                updateFactura();
                break;
            case 4:
                deleteFactura();
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }
    } while (opcion != 5);

    return 0;
}