#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;

void* hilo_funcion(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("Hola desde el hilo %ld\n", (long)arg);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void ejecutar_con_hilos(int num_hilos) {
    pthread_t hilos[num_hilos];

    pthread_mutex_init(&mutex, NULL);

    clock_t start = clock(); // Inicio del temporizador

    for (long i = 0; i < num_hilos; i++) {
        pthread_create(&hilos[i], NULL, hilo_funcion, (void*)(i + 1));
    }

    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], NULL);
    }

    clock_t end = clock(); // Fin del temporizador

    pthread_mutex_destroy(&mutex);

    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo total de ejecución con %d hilos: %f segundos\n\n", num_hilos, cpu_time_used);
}

int main() {
    printf("Ejecutando con 1 hilo...\n");
    ejecutar_con_hilos(1);

    printf("Ejecutando con 5 hilos...\n");
    ejecutar_con_hilos(5);

    printf("Ejecutando con 10 hilos...\n");
    ejecutar_con_hilos(10);

    printf("Finalizó la ejecución del programa principal\n");
    return 0;
}
