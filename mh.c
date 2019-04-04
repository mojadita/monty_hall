#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000000

#define P(f) __FILE__":%d: " f, __LINE__

int main()
{
    int cambio = 0, i;

    srandom(time(NULL));

    for (i = 0; i < N; i++) {
        int premio = random() % 3;  /* donde está el coche */
        int jugador = random() % 3;  /* donde juega el jugador inicialmente */
        /* el presentador siempre elegirá la primera puerta que
         * no contenga coche ni haya sido elegida por el concursante */
        int presentador;
        int opt = (premio << 3) | jugador;
        switch (opt) {
        /*    ,------ puerta premio. */
        /*    |,----- puerta jugador. */
        /*    vv */
        case 000: case 002: case 020: case 022: presentador = 1; break;
        case 001: case 010: presentador = 2; break;
        case 011: case 012: case 021: presentador = 0; break;
        default: fprintf(stderr,
                         P("Error, combinación imposible: 0%02o\n"),
                         opt);
                 exit(EXIT_FAILURE);
        } /* switch */
        opt = (presentador << 3) | jugador;
        /* cambio */
        switch (opt) {
        /*    ,------ puerta abierta presentador. */
        /*    |,----- puerta jugador. */
        /*    vv */
        case 001: case 010: jugador = 2; break;
        case 002: case 020: jugador = 1; break;
        case 012: case 021: jugador = 0; break;
        default: fprintf(stderr,
                         P("Error, combinación imposible: 0%02o\n"),
                         opt);
                 exit(EXIT_FAILURE);
        } /* switch */
        if (jugador == premio) {
            cambio++;
        }
    } /* for */
    long percent_cambio = cambio * 100000L / N;
    printf(P("aciertos cambio: %d/%d (%d.%03d%)\n"),
            cambio, N,
            percent_cambio / 1000,
            percent_cambio % 1000);
    exit(EXIT_SUCCESS);
} /* main */

