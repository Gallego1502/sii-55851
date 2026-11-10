#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "DatosMemCompartida.h"

using namespace std;

int main() {
    // 1. Declarar una variable de tipo puntero a DatosMemCompartida
    DatosMemCompartida *mem_compartida;

    // 2. Abrir el fichero proyectado en memoria creado en el tenis (open)
    int fd = open("/tmp/datos_bot", O_RDWR);
    if (fd == -1) {
        cout << "Error al abrir. ¡Asegúrate de arrancar primero ./tenis!" << endl;
        return 1;
    }

    // 2 y 4. Proyectarlo en memoria (mmap) y asignar la dirección al puntero
    mem_compartida = (DatosMemCompartida *)mmap(NULL, sizeof(DatosMemCompartida), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // 3. Cerrar el descriptor de fichero
    close(fd);

    // 5. Bucle infinito del bot
    while (true) {
        // Suspender durante 25 ms
        usleep(25000); 

        // LÓGICA: Calculamos el centro de nuestra raqueta sumando sus extremos y dividiendo entre 2
        float centro_raqueta = (mem_compartida->raqueta1.y1 + mem_compartida->raqueta1.y2) / 2.0f;

        // Comparamos la coordenada Y de la pelota con el centro de nuestra raqueta
        if (mem_compartida->esfera.centro.y > centro_raqueta + 0.2f) {
            mem_compartida->accion = 1;  // La pelota está arriba -> movemos arriba
        } 
        else if (mem_compartida->esfera.centro.y < centro_raqueta - 0.2f) {
            mem_compartida->accion = -1; // La pelota está abajo -> movemos abajo
        } 
        else {
            mem_compartida->accion = 0;  // Está centrada -> nos quedamos quietos
        }
    }

    return 0;
}
