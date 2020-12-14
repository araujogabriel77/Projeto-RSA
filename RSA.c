#include <stdio.h>
#include <string.h>

//Retorna o MDC dos dois numeros
int mdc(long long int num1, long long int num2)
{
	if (num2 == 0)
	{
		return num1;
	}
	else
	{
		return mdc(num2, num1 % num2);
	}
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

int main()
{
	int l;
	long long int option, p_prime, q_prime, e_coprime, n_key, d_key, h, i, j, k;

	FILE *file1;				   //Arquivo que recebe a chave pública
	FILE *file2;				   //Arquivo que recebe mensagem criptografada
	FILE *file3;				   //Arquivo que rece mensagem descriptografada
	FILE *file4;				   //Arquivo que recebe mensagem criptografada externa
	char mensagem[10000];		   //Recebe a mensagem
	char descript[10000];		   //Recebe a mensagem descriptografada
	long long int numero_c[10000]; //Recebe o valor inteiro do char depois que foi encriptado
	long long int numero[10000];   //Recebe o valor inteiro do char antes de ser criptado

	//Menu
	printf("Escolha uma tarefa valida:\n");
	printf("1-Gerar chave publica\n");
	printf("2-Criptografar\n");
	printf("3-Descriptografar\n");
	printf("0-Fechar o programa \n");

	//Usuário escolhe a opção
	scanf("%lld", &option);

	//Fica em loop até o usuário digitar 0
	while (option != 0)
	{
		//Fica em loop até o usuário digitar uma escolha válida
		while (option < 1 || option > 3)
		{
			printf("Escolha uma tarefa valida\n");
			scanf("%lld", &option);
		}

		//Gera a chave pública
		if (option == 1)
		{
			printf("escolha um primo 'p':\n");
			scanf("%lld", &p_prime);	//Atribui valor para o primo p
			while (prime(p_prime) == 1) //Fica em loop até o usuário digitar um valor primo
			{
				printf("Numero invalido\n");
				scanf("%lld", &p_prime);
			}

			printf("escolha um primo 'q':\n");
			scanf("%lld", &q_prime);	//Atribui valor para o primo q
			while (prime(q_prime) == 1) //Fica em loop até o usuário digitar um valor primo
			{
				printf("Numero invalido\n");
				scanf("%lld", &q_prime);
			}

			printf("escolha um expoente 'e' coprimo a %lld:\n", fi(p_prime, q_prime));
			scanf("%lld", &e_coprime);						  //Atribui valor para o coprimo e
			while (mdc(e_coprime, fi(p_prime, q_prime)) != 1) //Fica em loop até o usuário digitar um valor válido
			{
				printf("Numero invalido\n");
				scanf("%lld", &e_coprime);
			}

			file1 = fopen("Chave publica.txt", "a");			   //Abre o arquivo da chave pública
			fprintf(file1, "n=%lld\n", pub_key(p_prime, q_prime)); //Salva a chave n no arquivo
			fprintf(file1, "e=%lld\n", e_coprime);				   //Salva a chave e no arquivo
			fclose(file1);										   //Fecha o arquivo

			printf("Arquivo com a chave publica salvo no diretorio de execucao\n");
		}

		if (option == 2) //Gera o arquivo criptografado
		{
			printf("Digite a mensagem para ser encriptada:\n");

			getchar();
			fgets(mensagem, 10000, stdin); //Salva a string

			h = strlen(mensagem); //Salva o tamanho da string

			for (i = 0; i < h; i++) //Converte o char para um valor inteiro
			{
				numero[i] = mensagem[i];
			}

			printf("Digite a chave publica recebida previamente,'n' e 'e' respectivamente:\n"); //Atribui valor para n e e
			scanf("%lld", &n_key);
			scanf("%lld", &e_coprime);

			file2 = fopen("Mensagem encriptada.txt", "a"); //Abre o arquivo

			for (i = 0; i < h; i++) //Criptografa o valor inteiro e salva no arquivo com separador
			{
				j = numero[i];
				numero_c[i] = expmod(j, e_coprime, n_key);
				if (i != h - 1)
				{
					fprintf(file2, "%lld ", expmod(j, e_coprime, n_key));
				}
				else
				{
					fprintf(file2, "%lld", expmod(j, e_coprime, n_key));
				}
			}

			fclose(file2); //Fecha o arquivo
			printf("Arquivo com mensagem encriptada salva no diretorio de execucao\n");
		}

		if (option == 3) //Gera o arquivo descriptografado
		{
			printf("Digite o valor de 'p':\n"); //Atribui valor ao primo p
			scanf("%lld", &p_prime);

			printf("Digite o valor de 'q':\n"); //Atribui valor ao primo q
			scanf("%lld", &q_prime);

			printf("Digite o valor de 'e':\n"); //Atribui valor ao coprimo e
			scanf("%lld", &e_coprime);

			n_key = pub_key(p_prime, q_prime); //Atribui valor o n
			k = fi(p_prime, q_prime);		   //k recebe o valor de (p-1)*(q-1)
			d_key = inverse(e_coprime, k);	   //Atribui valor ao inverso d

			file3 = fopen("Mensagem original.txt", "w");   //Abre o arquivo
			file4 = fopen("Mensagem encriptada.txt", "r"); //Abre o arquivo com a mensagem externa

			fscanf(file4, "%lld", &l);

			descript[0] = descripto(l, d_key, n_key);

			for (i = 1; descript[i - 1] != '\n'; i++)
			{
				fscanf(file4, "%d", &l);
				descript[i] = descripto(l, d_key, n_key);
			}

			fprintf(file3, "%s\n", descript); //Grava a mensagem no arquivo

			fclose(file3); //Fecha o arquivo
			fclose(file4); //Fecha o arquivo
			printf("Mesagem salva no diretorio de execucao\n");
		}
		//Apresenta o menú mais uma vez
		printf("Escolha uma nova tarefa:\n");
		printf("1-Gerar chave publica\n");
		printf("2-Criptografar\n");
		printf("3-Descriptografar\n");
		printf("0-Fechar o programa \n");

		scanf("%lld", &option);
	}
	return 0;
}