#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	int dataNascimento[3];
	char cpf[50], rg[50], telefone[50][50], nome[50], sexo[50];
} Faxineiro;

typedef struct
{
	int dataNascimento[3];
	char cpf[50], nome[50], cep[50], cidade[50], endereco[50], email[50][50], telefone[50][50];
} Cliente;

typedef struct
{
	int dataServico[3];
	float valorServico;
	char cpfFaxineiro[50], cpfCliente[50];
} Servico;

void menuPrincipal(int *op)
{
	printf("Menu principal\n");
	printf("1. Submenu de Faxineiros\n");
	printf("2. Submenu de Clientes\n");
	printf("3. Submenu de Servi�os\n");
	printf("4. Submenu de Relat�rios\n");
	printf("5. Sair\n");
	printf("Entre com a op��o: ");
	scanf("%d", &(*op));
	printf("\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void lendoDadosFaxineiros(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	// Crinado um ponteiro para o Arquivo de Faxineiros
	FILE *arquivoFaxineiros;

	// Abre o Arquivo Bin�rio no modo de Escrita e Leitura
	arquivoFaxineiros = fopen("dados_faxineiros", "rb+");

	// Verifica se o Arquivo Existe ou est� Vazio
	// Caso o Arquivo n�o exista ou est� vazio, ent�o o vetor faxineiro e o contador s�o utilizados como vazio assim como definidos na main
	// Caso o arquivo exista os dados s�o carregados para o vetor e o contador
	if (arquivoFaxineiros != NULL)
	{
		// L� os dados do arquivo
		*contadorFaxineiros = fread(faxineiro, sizeof(Faxineiro), 100, arquivoFaxineiros); // Tenta ler 100 elementos de dados do Arquivo de Faxineiro
	}
	else
	{
		// O arquivo n�o existe, ent�o tentamos criar um novo
		arquivoFaxineiros = fopen("dados_faxineiros", "wb+");
		if (arquivoFaxineiros == NULL)
		{
			printf("Erro ao criar o arquivo!\n");
		}
	}

	// Fecha o Arquivo ap�s a Leitura dos Dados ou a Cria��o do Arquivo
	fclose(arquivoFaxineiros);
}

void gravandoDadosFaxineiros(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	// Crinado um ponteiro para o Arquivo de Faxineiros
	FILE *arquivoFaxineiros;

	// Abre o Arquivo Bin�rio no modo de Escrita e Leitura
	arquivoFaxineiros = fopen("dados_faxineiros", "rb+");

	// Posiciona o ponteiro no in�cio do arquivo para substituir os dados j� carregados (SEEK_SET)
	fseek(arquivoFaxineiros, 0, SEEK_SET);

	// Gravando os Dados dos Faxineiros no Arquivo Bin�rio
	fwrite(faxineiro, sizeof(Faxineiro), *contadorFaxineiros, arquivoFaxineiros); // o contadorCadastros representa quantos faxineiros est�o sendo gravados

	// Fecha o Arquivo ap�s a Leitura dos Dados ou a Cria��o do Arquivo
	fclose(arquivoFaxineiros);
}

int verificarFaxineiro(Faxineiro *faxineiro, char cpfFaxineiro[], int contadorFaxineiros)
{
	int i, resultado;
	for (i = 0; i < contadorFaxineiros; i++)
	{
		resultado = strcmp(faxineiro[i].cpf, cpfFaxineiro);
		if (resultado == 0)
		{
			return i;
		}
	}
	return -1;
}

int listarTodosFaxineiros(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	if (*contadorFaxineiros == 0)
	{
		return -1;
	}
	else
	{
		printf("Imprimindo todos os Faxineiros...\n\n");
		int i, y = 0;
		for (i = 0; i < *contadorFaxineiros; i++)
		{
			printf("Nome: %s\n", faxineiro[i].nome);
			printf("Sexo: %s\n", faxineiro[i].sexo);
			printf("Data de nascimento: ");
			printf("%d/%d/%d\n", faxineiro[i].dataNascimento[0], faxineiro[i].dataNascimento[1], faxineiro[i].dataNascimento[2]);
			printf("RG: %s\n", faxineiro[i].rg);
			printf("CPF: %s\n", faxineiro[i].cpf);
			printf("Telefones: | ");
			for (y = 0; faxineiro[i].telefone[y][0] != '\0'; y++)
			{
				printf("%s | ", faxineiro[i].telefone[y]);
			}
			printf("\n\n");
		}
	}
	return 0;
}

int listarUmFaxineiro(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	char cpfFaxineiro[50];
	int achou;

	printf("Informe o CPF do Faxineiro: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
	if (achou == -1)
	{
		return -1;
	}
	else
	{
		int i = 0;
		printf("\nNome: %s\n", faxineiro[achou].nome);
		printf("Sexo: %s\n", faxineiro[achou].sexo);
		printf("Data de nascimento: %d/%d/%d\n", faxineiro[achou].dataNascimento[0], faxineiro[achou].dataNascimento[1], faxineiro[achou].dataNascimento[2]);
		printf("RG: %s\n", faxineiro[achou].rg);
		printf("CPF: %s\n", faxineiro[achou].cpf);
		printf("Telefones: | ");
		for (i = 0; faxineiro[achou].telefone[i][0] != '\0'; i++)
		{
			printf("%s | ", faxineiro[achou].telefone[i]);
		}
		printf("\n\n");
	}
	return 0;
}

int incluiFaxineiro(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	// Aqui voc� pode realocar o vetor, se necess�rio, para acomodar mais faxineiros, estopu usando o limite para 100
	// Por exemplo:
	// *faxineiro = (Faxineiro *)realloc(*faxineiro, (*contadorFaxineiros + 1) * sizeof(Faxineiro));
	// se usar o realloc verificar se a aloca��o foi bem-sucedida antes de usar o ponteiro realocado.

	if (*contadorFaxineiros == 100)
	{
		printf("O n�mero(100) m�ximo de Faxineiros no sistema foi atingido!\n");
	}
	else
	{
		char cpfFaxineiro[50];
		int achou;

		printf("Informe o CPF do Faxineiro: ");
		fflush(stdin);
		gets(cpfFaxineiro);

		achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
		if (achou != -1)
		{
			return 1;
		}
		else
		{
			// Armazenando cpf
			strcpy(faxineiro[*contadorFaxineiros].cpf, cpfFaxineiro);
			// Armazenando nome
			printf("Informe o nome do Faxineiro: ");
			fflush(stdin);
			gets(faxineiro[*contadorFaxineiros].nome);
			// Armazenando sexo
			printf("Informe o sexo do Faxineiro: ");
			gets(faxineiro[*contadorFaxineiros].sexo);
			// Armazenando data de nascimento
			printf("Informe a data de nascimento: \n");
			printf("Dia: ");
			scanf("%d", &faxineiro[*contadorFaxineiros].dataNascimento[0]);
			printf("M�s: ");
			scanf("%d", &faxineiro[*contadorFaxineiros].dataNascimento[1]);
			printf("Ano: ");
			scanf("%d", &faxineiro[*contadorFaxineiros].dataNascimento[2]);
			// Armazena rg
			printf("Informe o RG do Faxineiro: ");
			fflush(stdin);
			gets(faxineiro[*contadorFaxineiros].rg);
			// Armazena telefone
			int maisTelefone = 1, contadorTelefones = 0;
			do
			{
				if (contadorTelefones == 50)
				{
					printf("N�mero m�ximo de telefones atingido!\n");
				}
				else if (maisTelefone == 1)
				{
					printf("Informe o telefone do Faxineiro: ");
					fflush(stdin);
					gets(faxineiro[*contadorFaxineiros].telefone[contadorTelefones]);
					contadorTelefones++;
				}
				printf("Deseja adicionar outro telefone? (1 para Sim e 0 para N�o) :");
				scanf("%d", &maisTelefone);
			} while (maisTelefone == 1);
			// Incrementa o contador de faxineiros
			(*contadorFaxineiros)++;
			return -1;
			// Retorna valores de acordo com a situa��o:
			// return 1;  Faxineiro j� existe
			// return -1; Inclus�o bem-sucedida
		}
	}
	return 0;
}

int alterarDadosFaxineiro(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	char cpfFaxineiro[50];
	int achou;

	printf("Informe o CPF do Faxineiro: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
	if (achou == -1)
	{
		return -1;
	}
	else
	{
		int opcao;
		printf("Se pretende alterar o CPF, tente excluir o Faxineiro do sistema e depois inserir novamente!\n");
		printf("Qual dos dados a seguir deseja alterar ?\n");
		printf("1. Nome\n");
		printf("2. Sexo\n");
		printf("3. Data de Nascimento\n");
		printf("4. RG\n");
		printf("5. Telefone\n");
		printf("6. Voltar para o Menu de Faxineiros\n");
		printf("Entre com a op��o: ");
		scanf("%d", &opcao);
		printf("\n");

		switch (opcao)
		{
		case 1:
		{
			printf("Nome Atual: %s\n", faxineiro[achou].nome);
			printf("Informe o novo Nome: ");
			fflush(stdin);
			gets(faxineiro[achou].nome);
			break;
		}
		case 2:
		{
			printf("Sexo Atual: %s\n", faxineiro[achou].sexo);
			printf("Informe o novo Sexo: ");
			fflush(stdin);
			gets(faxineiro[achou].sexo);
			break;
		}
		case 3:
		{
			printf("Data de Nascimento Atual: %d/%d/%d\n", faxineiro[achou].dataNascimento[0], faxineiro[achou].dataNascimento[1], faxineiro[achou].dataNascimento[2]);
			printf("Informe a nova Data de Nascimento: \n");
			printf("Dia: ");
			scanf("%d", &faxineiro[achou].dataNascimento[0]);
			printf("M�s: ");
			scanf("%d", &faxineiro[achou].dataNascimento[1]);
			printf("Ano: ");
			scanf("%d", &faxineiro[achou].dataNascimento[2]);
			break;
		}
		case 4:
		{
			printf("RG Atual: %s\n", faxineiro[achou].rg);
			printf("Informe o novo RG: ");
			fflush(stdin);
			gets(faxineiro[achou].rg);
			break;
		}
		case 5:
		{
			int i = 0;
			char telefoneAlterar[50];

			printf("Telefones Atuais: | ");
			for (i = 0; faxineiro[achou].telefone[i][0] != '\0'; i++)
			{
				printf("%s | ", faxineiro[achou].telefone[i]);
			}
			printf("\nDigite o Telefone que deseja alterar: ");
			fflush(stdin);
			gets(telefoneAlterar);
			for (i = 0; faxineiro[achou].telefone[i][0] != '\0'; i++)
			{
				if (strcmp(faxineiro[achou].telefone[i], telefoneAlterar) == 0)
				{
					printf("Informe o novo Telefone: ");
					gets(faxineiro[achou].telefone[i]);
					return 1;
				}
			}
			printf("\nO Faxineiro n�o possui esse telefone!\n");
			return -2;
		}
		case 6:
		{
			printf("Voltando para o Menu de Faxineiros\n");
			break;
		}
		default:
		{
			printf("Op��o inv�lida, tente novamente!\n\n");
			break;
		}
		}
		return 1;
	}
}

int excluirFaxineiro(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	char cpfFaxineiro[50];
	int achou, i;

	printf("Informe o CPF do Faxineiro: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
	if (achou == -1)
	{
		return -1;
	}
	else
	{
		printf("Dados do Faxineiro: \n");
		printf("Nome: %s\n", faxineiro[achou].nome);
		printf("Sexo: %s\n", faxineiro[achou].sexo);
		printf("Data de nascimento: \n");
		printf("%d/%d/%d\n", faxineiro[achou].dataNascimento[0], faxineiro[achou].dataNascimento[1], faxineiro[achou].dataNascimento[2]);
		printf("RG: %s\n", faxineiro[achou].rg);
		printf("Telefones: | ");
		for (i = 0; faxineiro[achou].telefone[i][0] != '\0'; i++)
		{
			printf("%s | ", faxineiro[achou].telefone[i]);
		}
		printf("\nCPF: %s\n", faxineiro[achou].cpf);
		printf("\nExcluindo do Sistema...\n");

		for (i = achou; i < *contadorFaxineiros - 1; i++)
		{ // achou representa o �ndice do faxineiro que deseja excluir
			faxineiro[i] = faxineiro[i + 1];
		}
		(*contadorFaxineiros)--;

		return 1;
	}
}

void menuFaxineiros(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	// Carrega os dados do Arquivo de Faxineiros para o vetor faxineiro e para o contadorFaxineiros
	lendoDadosFaxineiros(faxineiro, &(*contadorFaxineiros));

	int opcao;
	system("cls");

	do
	{
		printf("Abrindo Submenu de Faxineiros...\n");
		printf("\nMenu de Faxineiros: \n");
		printf("1. Listar todos Faxineiros\n");
		printf("2. Listar um Faxineiro\n");
		printf("3. Incluir Faxineiro no sistema\n");
		printf("4. Alterar dados de um Faxineiro\n");
		printf("5. Excluir Faxineiro do sistema\n");
		printf("6. Voltar para o Menu Principal\n");
		printf("Entre com a op��o: ");
		scanf("%d", &opcao);
		printf("\n");

		switch (opcao)
		{
		case 1:
		{
			system("cls");
			int resultado = listarTodosFaxineiros(faxineiro, &(*contadorFaxineiros));
			if (resultado == -1)
			{
				printf("N�o existe nenhum Faxineiro cadastrado no sistema!\n");
			}
			break;
		}
		case 2:
		{
			system("cls");
			int resultado = listarUmFaxineiro(faxineiro, &(*contadorFaxineiros));
			if (resultado == -1)
			{
				printf("N�o existe nenhum Faxineiro com esse CPF no sistema!\n");
			}
			break;
		}
		case 3:
		{
			system("cls");
			int resultado;
			resultado = incluiFaxineiro(faxineiro, &(*contadorFaxineiros));
			if (resultado == 1)
			{
				printf("\nEste Faxineiro j� estava cadastrado no sistema!\n");
			}
			else if (resultado == -1)
			{
				printf("\nFaxineiro cadastrado com sucesso!\n");
			}
			break;
		}
		case 4:
		{
			system("cls");
			int resultado = alterarDadosFaxineiro(faxineiro, &(*contadorFaxineiros));
			if (resultado == -1)
			{
				printf("N�o existe nenhum Faxineiro com esse CPF no sistema!\n");
			}
			else if (resultado == -2)
			{
				printf("\nN�o foi poss�vel alterar os dados!\n");
			}
			else
			{
				printf("\nDados alterados com sucesso!\n");
			}
			break;
		}
		case 5:
		{
			system("cls");
			int resultado = excluirFaxineiro(faxineiro, &(*contadorFaxineiros));
			if (resultado == -1)
			{
				printf("N�o existe nenhum Faxineiro com esse CPF no sistema!\n");
			}
			else
			{
				printf("\nFaxineiro exclu�do do sistema com sucesso!\n");
			}
			break;
		}
		case 6:
		{
			system("cls");
			printf("Voltando para o menu principal...\n\n");
			// Grava os dados do vetor faxineiro e do contadorFaxineiros para o Arquivo de Faxineiros
			gravandoDadosFaxineiros(faxineiro, &(*contadorFaxineiros));
			break;
		}
		default:
		{
			system("cls");
			printf("Op��o inv�lida, tente novamente!\n\n");
			break;
		}
		}
	} while (opcao != 6);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void lendoDadosClientes(Cliente *cliente, int *contadorClientes)
{
	// Crinado um ponteiro para o Arquivo de Clientes
	FILE *arquivoClientes;

	// Abre o Arquivo Bin�rio no modo de Escrita e Leitura
	arquivoClientes = fopen("dados_clientes", "rb+");

	// Verifica se o Arquivo Existe ou est� Vazio
	// Caso o Arquivo n�o exista ou est� vazio, ent�o o vetor cliente e o contador s�o utilizados como vazio assim como definidos na main
	// Caso o arquivo exista os dados s�o carregados para o vetor e o contador
	if (arquivoClientes != NULL)
	{
		// L� os dados do arquivo
		*contadorClientes = fread(cliente, sizeof(Cliente), 100, arquivoClientes); // Tenta ler 100 elementos de dados do Arquivo de Clientes
	}
	else
	{
		// O arquivo n�o existe, ent�o tentamos criar um novo
		arquivoClientes = fopen("dados_clientes", "wb+");
		if (arquivoClientes == NULL)
		{
			printf("Erro ao criar o arquivo!\n");
		}
	}

	// Fecha o Arquivo ap�s a Leitura dos Dados ou a Cria��o do Arquivo
	fclose(arquivoClientes);
}

void gravandoDadosClientes(Cliente *cliente, int *contadorClientes)
{
	// Crinado um ponteiro para o Arquivo de Clientes
	FILE *arquivoClientes;

	// Abre o Arquivo Bin�rio no modo de Escrita e Leitura
	arquivoClientes = fopen("dados_clientes", "rb+");

	// Posiciona o ponteiro no in�cio do arquivo para substituir os dados j� carregados (SEEK_SET)
	fseek(arquivoClientes, 0, SEEK_SET);

	// Gravando os Dados dos Faxineiros no Arquivo Bin�rio
	fwrite(cliente, sizeof(Cliente), *contadorClientes, arquivoClientes); // o contadorCadastros representa quantos clientes est�o sendo gravados

	// Fecha o Arquivo ap�s a Leitura dos Dados ou a Cria��o do Arquivo
	fclose(arquivoClientes);
}

int verificarCliente(Cliente *cliente, char cpfCliente[], int contadorClientes)
{
	int i, resultado;
	for (i = 0; i < contadorClientes; i++)
	{
		resultado = strcmp(cliente[i].cpf, cpfCliente);
		if (resultado == 0)
		{
			return i;
		}
	}
	return -1;
}

int listarTodosClientes(Cliente *cliente, int *contadorClientes)
{
	if (*contadorClientes == 0)
	{
		return -1;
	}
	else
	{
		printf("Imprimindo todos os Clientes...\n\n");
		int i, y;
		for (i = 0; i < *contadorClientes; i++)
		{
			printf("Nome: %s\n", cliente[i].nome);
			printf("Data de nascimento: ");
			printf("%d/%d/%d\n", cliente[i].dataNascimento[0], cliente[i].dataNascimento[1], cliente[i].dataNascimento[2]);
			printf("Endere�o: %s\n", cliente[i].endereco);
			printf("CPF: %s\n", cliente[i].cpf);
			printf("CEP: %s\n", cliente[i].cep);
			printf("Cidade: %s\n", cliente[i].cidade);
			printf("E-mails: | ");
			for (y = 0; cliente[i].email[y][0] != '\0'; y++)
			{
				printf("%s | ", cliente[i].email[y]);
			}
			printf("\n");
			printf("Telefones: | ");
			for (y = 0; cliente[i].telefone[y][0] != '\0'; y++)
			{
				printf("%s | ", cliente[i].telefone[y]);
			}
			printf("\n\n");
		}
	}
	return 0;
}

int listarUmCliente(Cliente *cliente, int *contadorClientes)
{
	char cpfCliente[50];
	int achou;

	printf("Informe o CPF do Cliente: ");
	fflush(stdin);
	gets(cpfCliente);
	achou = verificarCliente(cliente, cpfCliente, *contadorClientes); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
	if (achou == -1)
	{
		return -1;
	}
	else
	{
		printf("Nome: %s\n", cliente[achou].nome);
		printf("Data de nascimento: ");
		printf("%d/%d/%d\n", cliente[achou].dataNascimento[0], cliente[achou].dataNascimento[1], cliente[achou].dataNascimento[2]);
		printf("Endere�o: %s\n", cliente[achou].endereco);
		printf("CPF: %s\n", cliente[achou].cpf);
		printf("CEP: %s\n", cliente[achou].cep);
		printf("Cidade: %s\n", cliente[achou].cidade);
		printf("E-mails: | ");
		int y;
		for (y = 0; cliente[achou].email[y][0] != '\0'; y++)
		{
			printf("%s | ", cliente[achou].email[y]);
		}
		printf("\n");
		printf("Telefones: | ");
		for (y = 0; cliente[achou].telefone[y][0] != '\0'; y++)
		{
			printf("%s | ", cliente[achou].telefone[y]);
		}
		printf("\n\n");
	}
	return 0;
}

int incluiCliente(Cliente *cliente, int *contadorClientes)
{
	// Aqui voc� pode realocar o vetor, se necess�rio, para acomodar mais clientes, estou usando o limite para 100
	// Por exemplo:
	// *cliente = (Cliente *)realloc(*cliente, (*contadorClientes + 1) * sizeof(Cliente));
	// Se usar o realloc, verifique se a aloca��o foi bem-sucedida antes de usar o ponteiro realocado.

	if (*contadorClientes == 100)
	{
		printf("O n�mero m�ximo (100) de clientes no sistema foi atingido!\n");
	}
	else
	{
		char cpfCliente[50];
		int achou;

		printf("Informe o CPF do Cliente: ");
		fflush(stdin);
		gets(cpfCliente);

		achou = verificarCliente(cliente, cpfCliente, *contadorClientes); // chama a fun��o que verifica se j� existe um cliente com esse CPF
		if (achou != -1)
		{
			return 1;
		}
		else
		{
			// Armazenando CPF
			strcpy(cliente[*contadorClientes].cpf, cpfCliente);
			// Armazenando nome
			printf("Informe o nome do Cliente: ");
			fflush(stdin);
			gets(cliente[*contadorClientes].nome);
			// Armazenando data de nascimento
			printf("Informe a data de nascimento: \n");
			printf("Dia: ");
			scanf("%d", &cliente[*contadorClientes].dataNascimento[0]);
			printf("M�s: ");
			scanf("%d", &cliente[*contadorClientes].dataNascimento[1]);
			printf("Ano: ");
			scanf("%d", &cliente[*contadorClientes].dataNascimento[2]);
			// Armazenar endere�o
			printf("Informe o Endere�o do Cliente: ");
			fflush(stdin);
			gets(cliente[*contadorClientes].endereco);
			// Armazenar CEP
			printf("Informe o CEP do Cliente: ");
			fflush(stdin);
			gets(cliente[*contadorClientes].cep);
			// Armazenar cidade
			printf("Informe a Cidade do Cliente: ");
			fflush(stdin);
			gets(cliente[*contadorClientes].cidade);
			// Armazenar email
			int maisEmail = 1, contadorEmails = 0;
			do
			{
				if (contadorEmails == 50)
				{
					printf("N�mero m�ximo de e-mails atingido!\n");
				}
				else if (maisEmail == 1)
				{
					printf("Informe o e-mail do Cliente: ");
					fflush(stdin);
					gets(cliente[*contadorClientes].email[contadorEmails]);
					contadorEmails++;
				}
				printf("Deseja adicionar outro e-mail? (1 para Sim e 0 para N�o) :");
				scanf("%d", &maisEmail);
			} while (maisEmail == 1);
			// Armazena telefone
			int maisTelefone = 1, contadorTelefones = 0;
			do
			{
				if (contadorTelefones == 50)
				{
					printf("N�mero m�ximo de telefones atingido!\n");
				}
				else if (maisTelefone == 1)
				{
					printf("Informe o telefone do Cliente: ");
					fflush(stdin);
					gets(cliente[*contadorClientes].telefone[contadorTelefones]);
					contadorTelefones++;
				}
				printf("Deseja adicionar outro telefone? (1 para Sim e 0 para N�o) :");
				scanf("%d", &maisTelefone);
			} while (maisTelefone == 1);
			// Incrementar o contador de clientes
			(*contadorClientes)++;
			return -1;
			// Retorna valores de acordo com a situa��o:
			// return 1;  Cliente j� existe
			// return -1; Inclus�o bem-sucedida
		}
	}
	return 0;
}

int alterarDadosCliente(Cliente *cliente, int *contadorClientes)
{
	char cpfCliente[50];
	int achou;

	printf("Informe o CPF do Cliente: ");
	fflush(stdin);
	gets(cpfCliente);
	achou = verificarCliente(cliente, cpfCliente, *contadorClientes); // chama a fun��o que verifica se j� existe um cliente com esse cpf
	if (achou == -1)
	{
		return -1;
	}
	else
	{
		int opcao;
		printf("Se pretende alterar o CPF, tente excluir o Cliente do sistema e depois inserir novamente!\n");
		printf("Qual dos dados a seguir deseja alterar ?\n");
		printf("1. Nome\n");
		printf("2. Data de Nascimento\n");
		printf("3. Endere�o\n");
		printf("4. CEP\n");
		printf("5. Cidade\n");
		printf("6. E-mails\n");
		printf("7. Telefone\n");
		printf("8. Voltar para o Menu de Faxineiros\n");
		printf("Entre com a op��o: ");
		scanf("%d", &opcao);
		printf("\n");

		switch (opcao)
		{
		case 1:
		{
			printf("Nome Atual: %s\n", cliente[achou].nome);
			printf("Informe o novo Nome: ");
			fflush(stdin);
			gets(cliente[achou].nome);
			break;
		}
		case 2:
		{
			printf("Data de Nascimento Atual: %d/%d/%d\n", cliente[achou].dataNascimento[0], cliente[achou].dataNascimento[1], cliente[achou].dataNascimento[2]);
			printf("Informe a nova Data de Nascimento: \n");
			printf("Dia: ");
			scanf("%d", &cliente[achou].dataNascimento[0]);
			printf("M�s: ");
			scanf("%d", &cliente[achou].dataNascimento[1]);
			printf("Ano: ");
			scanf("%d", &cliente[achou].dataNascimento[2]);
			break;
		}
		case 3:
		{
			printf("Endere�o Atual: %s\n", cliente[achou].endereco);
			printf("Informe o novo Endere�o: ");
			fflush(stdin);
			gets(cliente[achou].endereco);
			break;
		}
		case 4:
		{
			printf("CEP Atual: %s\n", cliente[achou].cep);
			printf("Informe o novo CEP: ");
			fflush(stdin);
			gets(cliente[achou].cep);
			break;
		}
		case 5:
		{
			printf("Cidade Atual: %s\n", cliente[achou].cidade);
			printf("Informe a nova Cidade: ");
			fflush(stdin);
			gets(cliente[achou].cidade);
			break;
		}
		case 6:
		{
			int i = 0;
			char emailAlterar[50];

			printf("E-mails Atuais: | ");
			;
			for (i = 0; cliente[achou].email[i][0] != '\0'; i++)
			{
				printf("%s | ", cliente[achou].email[i]);
			}
			printf("\nDigite o E-mail que deseja alterar: ");
			fflush(stdin);
			gets(emailAlterar);
			for (i = 0; cliente[achou].email[i][0] != '\0'; i++)
			{
				if (strcmp(cliente[achou].email[i], emailAlterar) == 0)
				{
					printf("Informe o novo E-mail: ");
					gets(cliente[achou].email[i]);
					return 1;
				}
			}
			printf("\nO Cliente n�o possui esse E-mail!\n");
			return -2;
		}
		case 7:
		{
			int i = 0;
			char telefoneAlterar[50];

			printf("Telefones Atuais: | ");
			for (i = 0; cliente[achou].telefone[i][0] != '\0'; i++)
			{
				printf("%s | ", cliente[achou].telefone[i]);
			}
			printf("\nDigite o Telefone que deseja alterar: ");
			fflush(stdin);
			gets(telefoneAlterar);
			for (i = 0; cliente[achou].telefone[i][0] != '\0'; i++)
			{
				if (strcmp(cliente[achou].telefone[i], telefoneAlterar) == 0)
				{
					printf("Informe o novo Telefone: ");
					gets(cliente[achou].telefone[i]);
					return 1;
				}
			}
			printf("\nO Cliente n�o possui esse Telefone!\n");
			return -2;
		}
		default:
		{
			printf("Op��o inv�lida, tente novamente!\n\n");
			break;
		}
		}
		return 1;
	}
}

int excluirCliente(Cliente *cliente, int *contadorClientes)
{
	char cpfCliente[50];
	int achou, i;

	printf("Informe o CPF do Cliente: ");
	fflush(stdin);
	gets(cpfCliente);
	achou = verificarCliente(cliente, cpfCliente, *contadorClientes); // chama a fun��o que verifica se j� existe um cliente com esse cpf
	if (achou == -1)
	{
		return -1;
	}
	else
	{
		printf("Dados do Cliente: \n");
		printf("Nome: %s\n", cliente[achou].nome);
		printf("Data de nascimento: ");
		printf("%d/%d/%d\n", cliente[achou].dataNascimento[0], cliente[achou].dataNascimento[1], cliente[achou].dataNascimento[2]);
		printf("Endere�o: %s\n", cliente[achou].endereco);
		printf("CEP: %s\n", cliente[achou].cep);
		printf("Cidade: %s\n", cliente[achou].cidade);
		printf("E-mails:\n");
		for (i = 0; cliente[achou].email[i][0] != '\0'; i++)
		{
			printf("%s | ", cliente[achou].email[i]);
		}
		printf("\n");
		for (i = 0; cliente[achou].email[i][0] != '\0'; i++)
		{
			printf("%s | ", cliente[achou].email[i]);
		}
		printf("Telefones: | ");
		for (i = 0; cliente[achou].telefone[i][0] != '\0'; i++)
		{
			printf("%s | ", cliente[achou].telefone[i]);
		}
		printf("\n");
		printf("\nExcluindo do Sistema...\n");

		for (i = achou; i < *contadorClientes - 1; i++)
		{ // achou representa o �ndice do cliente que deseja excluir
			cliente[i] = cliente[i + 1];
		}
		(*contadorClientes)--;

		return 1;
	}
}

void menuClientes(Cliente *cliente, int *contadorClientes)
{
	// Carrega os dados do Arquivo de Clientes para o vetor cliente e para o contadorClientes
	lendoDadosClientes(cliente, &(*contadorClientes));

	int opcao;
	system("cls");

	do
	{
		printf("Abrindo Submenu de Clientes...\n");
		printf("\nMenu de Clientes: \n");
		printf("1. Listar todos Clientes\n");
		printf("2. Listar um Cliente\n");
		printf("3. Incluir Cliente no sistema\n");
		printf("4. Alterar dados de um Cliente\n");
		printf("5. Excluir Cliente do sistema\n");
		printf("6. Voltar para o Menu Principal\n");
		printf("Entre com a op��o: ");
		scanf("%d", &opcao);
		printf("\n");

		switch (opcao)
		{
		case 1:
		{
			system("cls");
			int resultado = listarTodosClientes(cliente, &(*contadorClientes));
			if (resultado == -1)
			{
				printf("N�o existe nenhum Cliente cadastrado no sistema!\n");
			}
			break;
		}
		case 2:
		{
			system("cls");
			int resultado = listarUmCliente(cliente, &(*contadorClientes));
			if (resultado == -1)
			{
				printf("N�o existe nenhum Cliente com esse CPF no sistema!\n");
			}
			break;
		}
		case 3:
		{
			system("cls");
			int resultado;
			resultado = incluiCliente(cliente, &(*contadorClientes));
			if (resultado == 1)
			{
				printf("\nEste Cliente j� estava cadastrado no sistema!\n");
			}
			else if (resultado == -1)
			{
				printf("\nCliente cadastrado com sucesso!\n");
			}
			break;
		}
		case 4:
		{
			system("cls");
			int resultado = alterarDadosCliente(cliente, &(*contadorClientes));
			if (resultado == -1)
			{
				printf("N�o existe nenhum Cliente com esse CPF no sistema!\n");
			}
			else if (resultado == -2)
			{
				printf("\nN�o foi poss�vel alterar os dados!\n");
			}
			else
			{
				printf("\nDados alterados com sucesso!\n");
			}
			break;
		}
		case 5:
		{
			system("cls");
			int resultado = excluirCliente(cliente, &(*contadorClientes));
			if (resultado == -1)
			{
				printf("N�o existe nenhum Cliente com esse CPF no sistema!\n");
			}
			else
			{
				printf("\nCliente exclu�do do sistema com sucesso!\n");
			}
			break;
		}
		case 6:
		{
			system("cls");
			printf("Voltando para o menu principal...\n\n");
			// Grava os dados do vetor cliente e do contadorClientes para o Arquivo de Clientes
			gravandoDadosClientes(cliente, &(*contadorClientes));
			break;
		}
		default:
		{
			system("cls");
			printf("Op��o inv�lida, tente novamente!\n\n");
			break;
		}
		}
	} while (opcao != 6);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function for reading service data
// Takes a pointer to an array of Servico structures (servico) and a pointer to an integer (contadorServicos)
void lendoDadosServicos(Servico *servico, int *contadorServicos)
{
	// Creating a pointer to the Service File
	FILE *arquivoServicos;

	// Opens the Binary File in Read and Write mode
	arquivoServicos = fopen("dados_servicos", "rb+");

	// Checks if the File Exists or is Empty
	// If the file does not exist or is empty, then the servico array and the contadorServicos are used as empty, as defined in the main function
	// If the file exists, the data is loaded into the array and the counter
	if (arquivoServicos != NULL)
	{
		// Reads data from the file
		*contadorServicos = fread(servico, sizeof(Servico), 100, arquivoServicos); // Attempts to read 100 data elements from the Service File
	}
	else
	{
		// The file does not exist, so we try to create a new one
		arquivoServicos = fopen("dados_servicos", "wb+");
		if (arquivoServicos == NULL)
		{
			printf("Erro ao criar o arquivo!\n");
		}
	}

	// Closes the File after Reading the Data or Creating the File
	fclose(arquivoServicos);
}

// Function for saving service data
// Takes a pointer to an array of Servico structures (servico) and a pointer to an integer (contadorServicos)
void gravandoDadosServicos(Servico *servico, int *contadorServicos)
{
	// Creating a pointer to the Service File
	FILE *arquivoServicos;

	// Opens the Binary File in Read and Write mode
	arquivoServicos = fopen("dados_servicos", "rb+");

	// Positions the pointer at the beginning of the file to replace the already loaded data (SEEK_SET)
	fseek(arquivoServicos, 0, SEEK_SET);

	// Writing the Janitors' Data to the Binary File
	fwrite(servico, sizeof(Servico), *contadorServicos, arquivoServicos); // the contadorCadastros represents how many services are being saved

	// Closes the File after Writing the Data
	fclose(arquivoServicos);
}

// Function to check for a service
// Takes an array of Servico structures (servico), two strings representing CPFs (cpfFaxineiro, cpfCliente),
// an array representing the date of service (dataServico), and an integer (contadorServicos)
int verificarServico(Servico *servico, char cpfFaxineiro[], char cpfCliente[], int dataServico[], int contadorServicos)
{
	int i;
	// Iterate through the array of services
	for (i = 0; i < contadorServicos; i++)
	{
		// Compare the CPF of the current janitor (servico[i].cpfFaxineiro) with the provided CPF (cpfFaxineiro)
		// and also the CPF of the current client (servico[i].cpfCliente) with the provided CPF (cpfCliente).
		// Additionally, compare each service date.
		if (strcmp(servico[i].cpfFaxineiro, cpfFaxineiro) == 0 && strcmp(servico[i].cpfCliente, cpfCliente) == 0 &&
			servico[i].dataServico[0] == dataServico[0] && servico[i].dataServico[1] == dataServico[1] && servico[i].dataServico[2] == dataServico[2])
		{
			return i; // Return the index if the service is found
		}
	}
	return -1; // Return -1 if the service is not found
}

// Function to list all services
// Takes an array of Servico structures (servico) and a pointer to an integer (contadorServicos)
int listarTodosServicos(Servico *servico, int *contadorServicos)
{
	// Check if there are no services
	if (*contadorServicos == 0)
	{
		return -1; // Return -1 to indicate no services
	}
	else
	{
		printf("Imprimindo todos os Servi�os...\n\n");
		int i;
		// Iterate through the array and print information for each service
		for (i = 0; i < *contadorServicos; i++)
		{
			printf("Data do Servi�o: %d/%d/%d\n", servico[i].dataServico[0], servico[i].dataServico[1], servico[i].dataServico[2]);
			printf("CPF do Faxineiro: %s\n", servico[i].cpfFaxineiro);
			printf("CPF do Cliente: %s\n", servico[i].cpfCliente);
			printf("Valor do Servi�o: %.2f\n", servico[i].valorServico);
			printf("\n");
		}
	}
	return 0; // Return 0 to indicate that services were found
}

// Function to list details of a specific service
// Takes an array of Servico structures (servico) and a pointer to an integer (contadorServicos)
int listarUmServico(Servico *servico, int *contadorServicos)
{
	char cpfFaxineiro[50], cpfCliente[50];
	int achou, dataServico[3];
	// Prompt the user to enter the service date
	printf("Informe a data do Servi�o: \n");
	printf("Dia: ");
	scanf("%d", &dataServico[0]);
	printf("M�s: ");
	scanf("%d", &dataServico[1]);
	printf("Ano: ");
	scanf("%d", &dataServico[2]);
	// Prompt the user to enter the janitor's CPF for the service
	printf("Informe o CPF do Faxineiro do Servi�o: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	// Prompt the user to enter the client's CPF for the service
	printf("Informe o CPF do Cliente do Servi�o: ");
	gets(cpfCliente);
	// Call the function to check if a service with the same janitor/client CPF and date already exists
	achou = verificarServico(servico, cpfFaxineiro, cpfCliente, dataServico, *contadorServicos);
	// If a matching service is found, print its details
	if (achou != -1)
	{
		printf("\nDados do Servi�o: \n");
		printf("Data do Servi�o: %d/%d/%d\n", servico[achou].dataServico[0], servico[achou].dataServico[1], servico[achou].dataServico[2]);
		printf("CPF do Faxineiro: %s\n", servico[achou].cpfFaxineiro);
		printf("CPF do Cliente: %s\n", servico[achou].cpfCliente);
		printf("Valor do Servi�o: %.2f\n", servico[achou].valorServico);
		printf("\n");
	}
	else
	{
		return -1; // Return -1 if no matching service is found
	}
	return 0; // Return 0 to indicate that a matching service was found
}

// Function to include a service
// Takes arrays of Servico structures (servico), Faxineiro structures (faxineiro), and Cliente structures (cliente),
// along with pointers to integers representing the counters (contadorServicos, contadorFaxineiros, contadorClientes)
int incluiServico(Servico *servico, int *contadorServicos, Faxineiro *faxineiro, int *contadorFaxineiros, Cliente *cliente, int *contadorClientes)
{
	// Here you can reallocate the array if necessary to accommodate more janitors, currently using the limit of 100
	// For example:
	// *faxineiro = (Faxineiro *)realloc(*faxineiro, (*contadorFaxineiros + 1) * sizeof(Faxineiro));
	// If using realloc, check if the allocation was successful before using the reallocated pointer.

	if (*contadorServicos == 100)
	{
		printf("O n�mero(100) m�ximo de Servi�os no sistema foi atingido!\n");
	}
	else
	{
		char cpfFaxineiro[50], cpfCliente[50];
		int achouServico, achouFaxineiro, achouCliente, dataServico[3];
		// Prompt the user to enter the service date
		printf("Informe a data do Servi�o: \n");
		printf("Dia: ");
		scanf("%d", &dataServico[0]);
		printf("M�s: ");
		scanf("%d", &dataServico[1]);
		printf("Ano: ");
		scanf("%d", &dataServico[2]);
		// Prompt the user to enter the janitor's CPF for the service
		printf("Informe o CPF do Faxineiro do Servi�o: ");
		fflush(stdin);
		gets(cpfFaxineiro);
		// Prompt the user to enter the client's CPF for the service
		printf("Informe o CPF do Cliente do Servi�o: ");
		gets(cpfCliente);
		// Call the function to check if a service with the same janitor/client CPF and date already exists
		achouServico = verificarServico(servico, cpfFaxineiro, cpfCliente, dataServico, *contadorServicos);
		// If a matching service is found, return 1
		if (achouServico != -1)
		{
			return 1;
		}
		else
		{
			// Check if the janitor with the given CPF is already in the system
			achouFaxineiro = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros);
			if (achouFaxineiro == -1)
			{
				// If the janitor is not found, return 2
				return 2;
			}
			// Check if the client with the given CPF is already in the system
			achouCliente = verificarCliente(cliente, cpfCliente, *contadorClientes);
			if (achouCliente == -1)
			{
				// If the client is not found, return 3
				return 3;
			}
			// Store the janitor's CPF
			strcpy(servico[*contadorServicos].cpfFaxineiro, cpfFaxineiro);
			// Store the client's CPF
			strcpy(servico[*contadorServicos].cpfCliente, cpfCliente);
			// Store the service date
			servico[*contadorServicos].dataServico[0] = dataServico[0];
			servico[*contadorServicos].dataServico[1] = dataServico[1];
			servico[*contadorServicos].dataServico[2] = dataServico[2];
			// Store the service value
			printf("Informe o valor do Servi�o: ");
			scanf("%f", &servico[*contadorServicos].valorServico);
			// Increment the service counter
			(*contadorServicos)++;
			return -1;
			// Return values according to the situation:
			// return 1;  Service already exists
			// return -1; Successful inclusion
			// return 2; Unable to register, janitor's CPF is not registered in the system
			// return 3; Unable to register, client's CPF is not registered in the system
		}
	}
	return 0;
}

// Function to modify service data
// Takes an array of Servico structures (servico) and a pointer to an integer (contadorServicos)
int alterarDadosServicos(Servico *servico, int *contadorServicos)
{
	char cpfFaxineiro[50], cpfCliente[50];
	int achou, dataServico[3];
	// Prompt the user to enter the service date
	printf("Informe a data do Servi�o: \n");
	printf("Dia: ");
	scanf("%d", &dataServico[0]);
	printf("M�s: ");
	scanf("%d", &dataServico[1]);
	printf("Ano: ");
	scanf("%d", &dataServico[2]);
	// Prompt the user to enter the janitor's CPF for the service
	printf("Informe o CPF do Faxineiro do Servi�o: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	// Prompt the user to enter the client's CPF for the service
	printf("Informe o CPF do Cliente do Servi�o: ");
	gets(cpfCliente);
	// Call the function to check if a service with the same janitor/client CPF and date already exists
	achou = verificarServico(servico, cpfFaxineiro, cpfCliente, dataServico, *contadorServicos);
	// If a matching service is found, proceed with modification
	if (achou != -1)
	{
		// Inform the user to try excluding and reinserting the service if they want to change CPF or date
		printf("\nSe pretende alterar algum CPF ou a Data, tente excluir o Servi�o do sistema e depois inserir novamente!\n");
		// Display the current service value
		printf("\nValor Atual do Servi�o: %.2f\n", servico[achou].valorServico);
		// Prompt the user to enter the new service value
		printf("Digite o novo Valor do Servi�o: ");
		scanf("%f", &servico[achou].valorServico);
		printf("\n");
		return 1; // Return 1 for successful modification
	}
	else
	{
		return -1; // Return -1 if no matching service is found
	}
}

// Function to delete a service
// Takes an array of Servico structures (servico) and a pointer to an integer (contadorServicos)
int excluirServico(Servico *servico, int *contadorServicos)
{
	char cpfFaxineiro[50], cpfCliente[50];
	int achou, dataServico[3];
	// Prompt the user to enter the service date
	printf("Informe a data do Servi�o: \n");
	printf("Dia: ");
	scanf("%d", &dataServico[0]);
	printf("M�s: ");
	scanf("%d", &dataServico[1]);
	printf("Ano: ");
	scanf("%d", &dataServico[2]);
	// Prompt the user to enter the janitor's CPF for the service
	printf("Informe o CPF do Faxineiro do Servi�o: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	// Prompt the user to enter the client's CPF for the service
	printf("Informe o CPF do Cliente do Servi�o: ");
	gets(cpfCliente);
	// Call the function to check if a service with the same janitor/client CPF and date already exists
	achou = verificarServico(servico, cpfFaxineiro, cpfCliente, dataServico, *contadorServicos);
	if (achou == -1)
	{
		return -1; // If no matching service is found, return -1
	}
	else
	{ // Display the details of the service to be deleted
		printf("\nDados do Servi�o: \n");
		printf("Data do Servi�o: %d/%d/%d\n", servico[achou].dataServico[0], servico[achou].dataServico[1], servico[achou].dataServico[2]);
		printf("CPF do Faxineiro: %s\n", servico[achou].cpfFaxineiro);
		printf("CPF do Cliente: %s\n", servico[achou].cpfCliente);
		printf("Valor do Servi�o: %.2f\n", servico[achou].valorServico);
		printf("\nExcluindo do Sistema...\n");

		// Shift the remaining services to fill the gap of the deleted service
		int i;
		// "achou" represents the index of the service you want to exclude
		for (i = achou; i < *contadorServicos - 1; i++)
		{
			servico[i] = servico[i + 1];
		}
		(*contadorServicos)--;

		return 1; // Return 1 for successful deletion
	}
}

// Function to manage the Services submenu
// Takes arrays of Servico structures (servico), Faxineiro structures (faxineiro), and Cliente structures (cliente),
// along with pointers to integers representing the counters (contadorServicos, contadorFaxineiros, contadorClientes)
void menuServicos(Servico *servico, int *contadorServicos, Faxineiro *faxineiro, int *contadorFaxineiros, Cliente *cliente, int *contadorClientes)
{
	// Load data from the Janitor File into the faxineiro array and the contadorFaxineiros counter
	lendoDadosFaxineiros(faxineiro, &(*contadorFaxineiros));
	// Load data from the Clients File into the cliente array and the contadorClientes counter
	lendoDadosClientes(cliente, &(*contadorClientes));
	// Load data from the Services File into the servico array and the contadorServicos counter
	lendoDadosServicos(servico, &(*contadorServicos));

	int opcao;
	system("cls");

	do
	{
		printf("Abrindo Submenu de Servi�os...\n");
		printf("\nMenu de Servi�os: \n");
		printf("1. Listar todos Servi�os\n");
		printf("2. Listar um Servi�o\n");
		printf("3. Incluir Servi�o no sistema\n");
		printf("4. Alterar dados de um Servi�o\n");
		printf("5. Excluir Servi�o do sistema\n");
		printf("6. Voltar para o Menu Principal\n");
		printf("Entre com a op��o: ");
		scanf("%d", &opcao);
		printf("\n");

		switch (opcao)
		{
		case 1:
		{
			system("cls");
			int resultado = listarTodosServicos(servico, &(*contadorServicos));
			if (resultado == -1)
			{
				printf("N�o existe nenhum Servi�o cadastrado no sistema!\n");
			}
			break;
		}
		case 2:
		{
			system("cls");
			int resultado = listarUmServico(servico, &(*contadorServicos));
			if (resultado == -1)
			{
				printf("\nN�o existe nenhum Servi�o cadastrado com esses dados no Sistema!\n");
			}
			break;
		}
		case 3:
		{
			system("cls");
			int resultado;
			resultado = incluiServico(servico, &(*contadorServicos), faxineiro, &(*contadorFaxineiros), cliente, &(*contadorClientes));
			if (resultado == 1)
			{
				printf("\nEste Servi�o j� estava cadastrado no sistema!\n");
			}
			else if (resultado == -1)
			{
				printf("\nServi�o cadastrado com sucesso!\n");
			}
			else if (resultado == 2)
			{
				printf("\nN�o foi poss�vel cadastrar o Servi�o pois n�o existe nenhum Faxineiro com esse CPF no Sistema!\n");
			}
			else if (resultado == 3)
			{
				printf("\nN�o foi poss�vel cadastrar o Servi�o pois n�o existe nenhum Cliente com esse CPF no Sistema!\n");
			}
			break;
		}
		case 4:
		{
			system("cls");
			int resultado = alterarDadosServicos(servico, &(*contadorServicos));
			if (resultado == -1)
			{
				printf("\nN�o existe nenhum Servi�o com esses dados no Sistema!\n");
			}
			else
			{
				printf("\nDados alterados com sucesso!\n");
			}
			break;
		}
		case 5:
		{
			system("cls");
			int resultado = excluirServico(servico, &(*contadorServicos));
			if (resultado == -1)
			{
				printf("\nN�o existe nenhum Servi�o com esses dados no Sistema!\n");
			}
			else
			{
				printf("\nServi�o exclu�do do sistema com sucesso!\n");
			}
			break;
		}
		case 6:
		{
			system("cls");
			printf("Voltando para o menu principal...\n\n");
			// Save the data from the servico array and contadorServicos counter to the Services File
			gravandoDadosServicos(servico, &(*contadorServicos));
			break;
		}
		default:
		{
			system("cls");
			printf("Op��o inv�lida, tente novamente!\n\n");
			break;
		}
		}
	} while (opcao != 6);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void diferencaDatas(int dataInicial[], int dataFinal[], int *diferencaDias, int *diferencaMeses, int *diferencaAnos)
{
	struct tm data1 = {0};
	struct tm data2 = {0};

	data1.tm_year = dataInicial[0] - 1900;
	data1.tm_mon = dataInicial[1] - 1;
	data1.tm_mday = dataInicial[2];
	data2.tm_year = dataFinal[0] - 1900;
	data2.tm_mon = dataFinal[1] - 1;
	data2.tm_mday = dataFinal[2];

	time_t segundos1 = mktime(&data1);
	time_t segundos2 = mktime(&data2);

	double diferenca = difftime(segundos2, segundos1);
	*diferencaDias = diferenca / 86400;
	*diferencaMeses = *diferencaDias / 30; // Considerando meses de 30 dias (ajuste se necess�rio)
	*diferencaAnos = *diferencaMeses / 12;
}

int relatorio1(Servico *servico, int *contadorServicos, Faxineiro *faxineiro, int *contadorFaxineiros, Cliente *cliente, int *contadorClientes)
{
	FILE *arquivo;			 // Ponteiro para o arquivo
	char nomeDoArquivo[256]; // 256 m�ximo de caracteres para o nome de um arquivo

	printf("Digite o nome do arquivo para salvar o relat�rio ou sobrescrev�-lo: ");
	scanf("%s", nomeDoArquivo);
	strcat(nomeDoArquivo, ".txt");

	arquivo = fopen(nomeDoArquivo, "w"); // Abre o arquivo para escrita ("w")

	char cpfFaxineiro[50];
	int achou;

	printf("\nInforme o CPF do Faxineiro: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
	if (achou == -1)
	{
		fclose(arquivo);	   // Fecha o arquivo ap�s o uso
		remove(nomeDoArquivo); // excluir o arquivo caso n�o haja os dados necess�rios
		return -1;
	}
	else
	{
		int dataInicial[3], dataFinal[3], i;
		int faxineiroCont = 0;

		printf("\nInforme a data inicial: \n");
		fprintf(arquivo, "\nInforme a data inicial: \n");
		printf("Dia: ");
		scanf("%d", &dataInicial[0]);
		printf("M�s: ");
		scanf("%d", &dataInicial[1]);
		printf("Ano: ");
		scanf("%d", &dataInicial[2]);
		fprintf(arquivo, "%d/%d/%d: \n", dataInicial[0], dataInicial[1], dataInicial[2]);

		printf("\nInforme a data final: \n");
		fprintf(arquivo, "Informe a data final: \n");
		printf("Dia: ");
		scanf("%d", &dataFinal[0]);
		printf("M�ss: ");
		scanf("%d", &dataFinal[1]);
		printf("Ano: ");
		scanf("%d", &dataFinal[2]);
		fprintf(arquivo, "%d/%d/%d: \n", dataFinal[0], dataFinal[1], dataFinal[2]);

		int diferencaDias, diferencaMeses, diferencaAnos;

		diferencaDatas(dataInicial, dataFinal, &diferencaDias, &diferencaMeses, &diferencaAnos); // chama a fun��o que calcula a diferen�a entre as datas

		for (i = 0; i < *contadorServicos; i++)
		{
			if (strcmp(servico[i].cpfFaxineiro, cpfFaxineiro) == 0)
			{
				// Compara��o de datas
				int diaServico = servico[i].dataServico[0];
				int mesServico = servico[i].dataServico[1];
				int anoServico = servico[i].dataServico[2];

				if ((anoServico > dataInicial[2] || (anoServico == dataInicial[2] && mesServico > dataInicial[1]) ||
					 (anoServico == dataInicial[2] && mesServico == dataInicial[1] && diaServico >= dataInicial[0])) &&
					(anoServico < dataFinal[2] || (anoServico == dataFinal[2] && mesServico < dataFinal[1]) ||
					 (anoServico == dataFinal[2] && mesServico == dataFinal[1] && diaServico <= dataFinal[0])))
				{

					char cpfCliente[50];
					strcpy(cpfCliente, servico[i].cpfCliente);
					achou = verificarCliente(cliente, cpfCliente, *contadorClientes);
					printf("\nContratou servi�o neste per�odo: \n");
					fprintf(arquivo, "\nContratou servi�o neste per�odo: \n");
					printf("Nome do Cliente: %s\n", cliente[achou].nome);
					fprintf(arquivo, "Nome: %s\n", cliente[achou].nome);
					printf("E-mails: | ");
					fprintf(arquivo, "E-mails: | ");
					int y;
					for (y = 0; cliente[achou].email[y][0] != '\0'; y++)
					{
						printf("%s | ", cliente[achou].email[y]);
						fprintf(arquivo, "%s | ", cliente[achou].email[y]);
					}
					printf("\nTelefones: | ");
					fprintf(arquivo, "\nTelefones: | ");
					for (y = 0; cliente[achou].telefone[y][0] != '\0'; y++)
					{
						printf("%s | ", cliente[achou].telefone[y]);
						fprintf(arquivo, "%s | ", cliente[achou].telefone[y]);
					}
					faxineiroCont++;
					printf("\n\n");
					fprintf(arquivo, "\n");
				}
			}
		}
		if (faxineiroCont == 0)
		{
			fclose(arquivo);	   // Fecha o arquivo ap�s o uso
			remove(nomeDoArquivo); // excluir o arquivo caso n�o haja os dados necess�rios
			return -2;
		}
	}
	fclose(arquivo); // Fecha o arquivo ap�s o uso
	return 1;
}

int relatorio2(Servico *servico, int *contadorServicos, Faxineiro *faxineiro, int *contadorFaxineiros, Cliente *cliente, int *contadorClientes)
{
	FILE *arquivo;			 // Ponteiro para o arquivo
	char nomeDoArquivo[256]; // 256 m�ximo de caracteres para o nome de um arquivo

	printf("Digite o nome do arquivo para salvar o relat�rio ou sobrescrev�-lo: ");
	scanf("%s", nomeDoArquivo);
	strcat(nomeDoArquivo, ".txt");

	arquivo = fopen(nomeDoArquivo, "w"); // Abre o arquivo para escrita ("w")

	int data[3], i, achouFaxineiro, achouCliente, contadorServicosFaxineiro = 0;

	printf("Informe a data espec�fica: \n");
	printf("Dia: ");
	scanf("%d", &data[0]);
	printf("M�s: ");
	scanf("%d", &data[1]);
	printf("Ano: ");
	scanf("%d", &data[2]);

	for (i = 0; i < *contadorServicos; i++)
	{
		if (servico[i].dataServico[0] == data[0] && servico[i].dataServico[1] == data[1] && servico[i].dataServico[2] == data[2])
		{
			printf("\nServi�o realizado no dia %d/%d/%d: \n", data[0], data[1], data[2]);
			fprintf(arquivo, "\nDados dos Servi�os para o dia %d/%d/%d: \n", data[0], data[1], data[2]);

			printf("\nData do Servi�o: %d/%d/%d\n", servico[i].dataServico[0], servico[i].dataServico[1], servico[i].dataServico[2]);
			fprintf(arquivo, "\nData do Servi�o: %d/%d/%d\n", servico[i].dataServico[0], servico[i].dataServico[1], servico[i].dataServico[2]);
			printf("Valor do Servi�o: %.2f\n", servico[i].valorServico);
			fprintf(arquivo, "Valor do Servi�o: %.2f\n", servico[i].valorServico);

			printf("CPF do Faxineiro: %s\n", servico[i].cpfFaxineiro);
			fprintf(arquivo, "CPF do Faxineiro: %s\n", servico[i].cpfFaxineiro);
			achouFaxineiro = verificarFaxineiro(faxineiro, servico[i].cpfFaxineiro, *contadorFaxineiros); // procura o endere�o do faxineiro no vetor de faxineiros
			printf("Nome do Faxineiro: %s\n", faxineiro[achouFaxineiro].nome);
			fprintf(arquivo, "Nome do Faxineiro: %s\n", faxineiro[achouFaxineiro].nome);

			printf("CPF do Cliente: %s\n", servico[i].cpfCliente);
			fprintf(arquivo, "CPF do Cliente: %s\n", servico[i].cpfCliente);
			achouCliente = verificarCliente(cliente, servico[i].cpfCliente, *contadorClientes); // procura o endere�o do cliente no vetor de faxineiros
			printf("Nome do Cliente: %s\n", cliente[achouCliente].nome);
			fprintf(arquivo, "Nome do Cliente: %s\n", cliente[achouCliente].nome);

			contadorServicosFaxineiro++;
		}
	}
	if (contadorServicosFaxineiro == 0)
	{
		fclose(arquivo);
		remove(nomeDoArquivo); // excluir o arquivo caso n�o haja os dados necess�rios
		return -1;
	}
	printf("\n");
	fprintf(arquivo, "\n");
	fclose(arquivo); // Fecha o arquivo ap�s o uso
	return 1;
}

int relatorio3(Servico *servico, int *contadorServicos, Faxineiro *faxineiro, int *contadorFaxineiros)
{
	FILE *arquivo;			 // Ponteiro para o arquivo
	char nomeDoArquivo[256]; // 256 m�ximo de caracteres para o nome de um arquivo

	printf("Digite o nome do arquivo para salvar o relat�rio ou sobrescrev�-lo: ");
	scanf("%s", nomeDoArquivo);
	strcat(nomeDoArquivo, ".txt");

	arquivo = fopen(nomeDoArquivo, "w"); // Abre o arquivo para escrita ("w")

	char cpfFaxineiro[50];
	int achou;

	printf("Informe o CPF do Faxineiro: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
	if (achou == -1)
	{
		return -1;
	}
	else
	{
		int i, contadorServicosFaxineiro = 0;

		printf("\nDados do Faxineiro: \n");
		fprintf(arquivo, "\nDados do Faxineiro: \n");
		printf("CPF: %s\n", faxineiro[achou].cpf);
		fprintf(arquivo, "CPF: %s\n", faxineiro[achou].cpf);
		printf("Nome: %s\n", faxineiro[achou].nome);
		fprintf(arquivo, "Nome: %s\n", faxineiro[achou].nome);
		printf("RG: %s\n", faxineiro[achou].rg);
		fprintf(arquivo, "RG: %s\n", faxineiro[achou].rg);
		printf("Sexo: %s\n", faxineiro[achou].sexo);
		fprintf(arquivo, "Sexo: %s\n", faxineiro[achou].sexo);
		printf("Data de nascimento: ");
		fprintf(arquivo, "Data de nascimento: ");
		printf("%d/%d/%d\n", faxineiro[achou].dataNascimento[0], faxineiro[achou].dataNascimento[1], faxineiro[achou].dataNascimento[2]);
		fprintf(arquivo, "%d/%d/%d\n", faxineiro[achou].dataNascimento[0], faxineiro[achou].dataNascimento[1], faxineiro[achou].dataNascimento[2]);
		printf("Telefones: | ");
		fprintf(arquivo, "Telefones: | ");
		for (i = 0; faxineiro[achou].telefone[i][0] != '\0'; i++)
		{
			printf("%s | ", faxineiro[achou].telefone[i]);
			fprintf(arquivo, "%s | ", faxineiro[achou].telefone[i]);
		}
		printf("\n\nDados dos Servi�os: \n");
		fprintf(arquivo, "\n\nDados dos Servi�os: \n");
		for (i = 0; i < *contadorServicos; i++)
		{
			if (strcmp(servico[i].cpfFaxineiro, cpfFaxineiro) == 0)
			{
				printf("\nData do Servi�o: %d/%d/%d\n", servico[i].dataServico[0], servico[i].dataServico[1], servico[i].dataServico[2]);
				fprintf(arquivo, "\nData do Servi�o: %d/%d/%d\n", servico[i].dataServico[0], servico[i].dataServico[1], servico[i].dataServico[2]);
				printf("CPF do Faxineiro: %s\n", servico[i].cpfFaxineiro);
				fprintf(arquivo, "CPF do Faxineiro: %s\n", servico[i].cpfFaxineiro);
				printf("CPF do Cliente: %s\n", servico[i].cpfCliente);
				fprintf(arquivo, "CPF do Cliente: %s\n", servico[i].cpfCliente);
				printf("Valor do Servi�o: %.2f\n", servico[i].valorServico);
				fprintf(arquivo, "Valor do Servi�o: %.2f\n", servico[i].valorServico);
				contadorServicosFaxineiro++;
			}
		}
		if (contadorServicosFaxineiro == 0)
		{
			fclose(arquivo);	   // Fecha o arquivo ap�s o uso
			remove(nomeDoArquivo); // excluir o arquivo caso n�o haja os dados necess�rios
			return -2;
		}
	}
	printf("\n");
	fprintf(arquivo, "\n");
	fclose(arquivo); // Fecha o arquivo ap�s o uso
	return 1;
}

void menuRelatorios(Servico *servico, int *contadorServicos, Faxineiro *faxineiro, int *contadorFaxineiros, Cliente *cliente, int *contadorClientes)
{
	// Carrega os dados do Arquivo de Faxineiros para o vetor faxineiro e para o contadorFaxineiros
	lendoDadosFaxineiros(faxineiro, &(*contadorFaxineiros));
	// Carrega os dados do Arquivo de Clientes para o vetor cliente e para o contadorClientes
	lendoDadosClientes(cliente, &(*contadorClientes));
	// Carrega os dados do Arquivo de Servi�os para o vetor servico e para o contadorServicos
	lendoDadosServicos(servico, &(*contadorServicos));

	int opcao;
	system("cls");

	do
	{
		printf("\nAbrindo Submenu de Relat�rios...\n");
		printf("\nMenu de Relat�rios: \n");
		printf("1. Mostrar o nome, os e-mails e telefones de todos(as) os(as) clientes que contrataram o servi�o de determinado(a) faxineiro(a) entre as datas X e Y.\nO CPF do(a) faxineiro(a) e as datas dever�o ser fornecidos pelo usu�rio;\n");
		printf("\n");
		printf("2. Mostrar os dados de todos os servi�os contratados para uma data espec�fica a ser fornecida pelo usu�rio.\nApresente tamb�m o nome do(a) faxineiro(a) e do(a) cliente;\n");
		printf("\n");
		printf("3. Mostrar os dados de todos os servi�os realizados por determinado(a) faxineiro(a), cujo CPF ser� fornecido pelo usu�rio.\n");
		printf("\n");
		printf("4. Voltar para o Menu Principal\n");
		printf("Entre com a op��o: ");
		scanf("%d", &opcao);
		printf("\n");

		switch (opcao)
		{
		case 1:
		{
			system("cls");
			int resultado = relatorio1(servico, &(*contadorServicos), faxineiro, &(*contadorFaxineiros), cliente, &(*contadorClientes));
			if (resultado == -1)
			{
				printf("\nN�o existe nenhum Faxineiro com esse CPF no Sistema!\n");
			}
			else if (resultado == -2)
			{
				printf("\nEsse faxineiro n�o possui nenhum servi�o entre as datas fornecidas...\n");
			}
			break;
		}
		case 2:
		{
			system("cls");
			int resultado = relatorio2(servico, &(*contadorServicos), faxineiro, &(*contadorFaxineiros), cliente, &(*contadorClientes));
			if (resultado == -1)
			{
				printf("\nN�o existe nenhum Servi�o cadastrado com esses dados no Sistema!\n\n");
			}
			break;
		}
		case 3:
		{
			system("cls");
			int resultado = relatorio3(servico, &(*contadorServicos), faxineiro, &(*contadorFaxineiros));
			if (resultado == -1)
			{
				printf("\nN�o existe nenhum Faxineiro com esse CPF no Sistema!\n\n");
			}
			else if (resultado == -2)
			{
				printf("\nN�o foi poss�vel realizar o relat�rio pois n�o existe nenhum servi�o realizado por esse Faxineiro!\n\n");
			}
			break;
		}
		case 4:
		{
			system("cls");
			printf("Voltando para o menu principal...\n\n");
			break;
		}
		default:
		{
			system("cls");
			printf("Op��o inv�lida, tente novamente!\n\n");
			break;
		}
		}
	} while (opcao != 4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	setlocale(LC_ALL, "Portuguese");
	int op, limiteSistema = 100;
	int contadorFaxineiros = 0, contadorClientes = 0, contadorServicos = 0; // contador para quantos faxineiros/clientes/servicos est�o inseridos no sistema

	// faxineiro � um ponteiro para uma vetor que armazena registros Faxineiro
	Faxineiro *faxineiro;
	faxineiro = (Faxineiro *)malloc(limiteSistema * sizeof(Faxineiro)); // aloca dinamicamente na mem�ria para um vetor do tipo Servico
	// cliente � um ponteiro para uma vetor que armazena registros Cliente
	Cliente *cliente;
	cliente = (Cliente *)malloc(limiteSistema * sizeof(Cliente));
	// servico � um ponteiro para uma vetor que armazena registros Servico
	Servico *servico;
	servico = (Servico *)malloc(limiteSistema * sizeof(Servico)); // aloca dinamicamente na mem�ria para um vetor do tipo Servico

	menuPrincipal(&op);

	do
	{
		switch (op)
		{
		case 1:
		{ // caso a op��o digitada for 1
			menuFaxineiros(faxineiro, &contadorFaxineiros);
			menuPrincipal(&op);
			break;
		}

		case 2:
		{ // caso a op��o digitada for 2
			printf("Abrindo Submenu de Clientes...\n");
			menuClientes(cliente, &contadorClientes);
			menuPrincipal(&op);
			break;
		}

		case 3:
		{ // caso a op��o digitada for 3
			printf("Abrindo Submenu de Servi�os...\n");
			menuServicos(servico, &contadorServicos, faxineiro, &contadorFaxineiros, cliente, &contadorClientes);
			menuPrincipal(&op);
			break;
		}

		case 4:
		{ // caso a op��o digitada for 4
			printf("Abrindo Submenu de Relat�rios...\n");
			menuRelatorios(servico, &contadorServicos, faxineiro, &contadorFaxineiros, cliente, &contadorClientes);
			menuPrincipal(&op);
			break;
		}

		case 5:
		{ // caso a op��o digitada for 5
			// sai do loop e finaliza o programa, pois n�o chama o Menu Principal novamente
			break;
		}

		default:
		{ // caso a op��o digitada n�o est� entre as op��es dispon�veis
			system("cls");
			printf("Op��o inv�lida, tente novamente!\n\n");
			menuPrincipal(&op);
			break;
		}
		}
		if (op == 5)
		{
			printf("Finalizando o programa...");
			free(faxineiro);
			free(cliente);
			free(servico);
		}
	} while (op != 5); // mant�m o Menu Principal em loop at� que op seja igual a 5
	return 0;
}
