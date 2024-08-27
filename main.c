#include "contref.h"

int main(int argc, char const *argv[]) {
    int *v = (int *)malloc2(sizeof(int));
    *v = 10;
    int *w = (int *)malloc2(sizeof(int));
    dump();

    *w = 20;
    atrib2(v, w);
    dump();

    char *c = (char *)malloc2(sizeof(char));
    *c = 'Z';
    dump();

    atrib2(w, NULL);
    dump();

    return 0;
}
