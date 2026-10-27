#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char **argv) {
    int fd;
    char buffer[1024];
    
    // Es buena práctica guardar el nombre de la tubería en una variable
    const char *ruta_fifo = "/tmp/fifo_tenis";

    // borrar FIFO por si existiera previamente
    unlink(ruta_fifo);

    /* crear el FIFO con permisos de lectura y escritura (0666) */
    if (mkfifo(ruta_fifo, 0666) < 0) {
        perror("No puede crearse el FIFO");
        return(1);
    }
    
    /* Abrir el FIFO en modo solo lectura (O_RDONLY) y guardar su identificador (fd) */
    if ((fd = open(ruta_fifo, O_RDONLY)) < 0) {
        perror("No puede abrirse el FIFO");
        return(1);
    }
    
    /* Leer de la FIFO en bucle mientras haya datos (read devuelva > 0) */
    while (read(fd, buffer, sizeof(buffer)) > 0) {
        // Imprimir el texto en la pantalla
        printf("%s", buffer);
    }
    
    /* Cerrar y destruir */
    close(fd);
    unlink(ruta_fifo);
    
    return(0);
}
