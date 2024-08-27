#ifndef CONTREF_H_INCLUDED
#define CONTREF_H_INCLUDED

#include <stddef.h> // Para usar size_t (transforma bytes em valores inteiros)

void* malloc2(size_t tamanho);
void atrib2(void* endereco1, void* endereco2);
void dump();

#endif // CONTREF_H_INCLUDED
