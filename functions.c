#include <stdio.h>
#include <string.h>

//Retorna o MDC dos dois numeros
int mdc(long long int a, long long int b)
{
	return b == 0 ? a : mdc(b, a % b);
}

//Verifica se o número é primo
int prime(long long int num)
{
	int prime = 2, i;
	if (num == 1 || num == 0)
	{
		prime = 1;
	}
	else
	{
		for (i = 2; i < num; i++)
		{
			if (num % i == 0)
			{
				prime = 1;
				break;
			}
		}
	}
	return prime;
}

//Calcula a função toitente fi(n)
long long int fi(long long int p, long long int q)
{
	long long int toitente;
	toitente = (p - 1) * (q - 1);
	return toitente;
}

//Retorna a chave pública n
long long int pub_key(long long int p, long long int q)
{
	long long int key;
	key = p * q;
	return key;
}

//Retorna o resultado da exponenciação modular
long long int expmod(long long int base, long long int expoente, long long int modulo)
{
	long long int t = 1, i;
	for (i = 0; i < expoente; i++)
	{
		t = t * base % modulo;
	}
	return t;
}

//Calcula o inverso
long long int inverse(long long int chave, long long int modulo)
{
	long long int i = 1, j;
	while (i <= modulo)
	{
		j = chave * i % modulo;
		i++;
		if (j == 1)
		{
			break;
		}
	}
	return i - 1;
}

//Desencripta o char
char descripto(long long int base, long long int expoente, long long int mod)
{
	return (char)expmod(base, expoente, mod);
}