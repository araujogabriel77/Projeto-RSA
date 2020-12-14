#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//Retorna o MDC dos dois numeros
int mdc(long long int a, long long int b);

//Verifica se o número é primo
int prime(long long int num);

//Calcula a função toitente fi(n)
long long int fi(long long int p, long long int q);

//Retorna a chave pública n
long long int pub_key(long long int p, long long int q);

//Retorna o resultado da exponenciação modular
long long int expmod(long long int base, long long int expoente, long long int modulo);

//Calcula o inverso
long long int inverse(long long int chave, long long int modulo);

//Desencripta o char
char descripto(long long int base, long long int expoente, long long int mod);

#endif // FUNCTIONS_H