#ifndef FUNCIONES_H
#define FUNCIONES_H

// Estructura para representar un producto
struct Producto {
    char nombre[50];
    int cantidad;
    float precio;
};

// Estructura para representar una factura
struct Factura {
    char nombre[20];
    int cedula;
    int numProductos;
    float total;
    struct Producto productos[5];
};

// Prototipos de funciones
int menu();
void savefactura(struct Factura *factura);
void leerCadena(char *cadena, int num);
int validarCedulaUnica(int cedula);
void crateFactura();
void readFactura();
void updateFactura();
void deleteFactura();

#endif