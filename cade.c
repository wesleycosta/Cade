/**********************************************
*** Programa ......: Cade.c                 ***
*** Autor .........: Wesley Costa           ***
*** Portuário......: 1510797                ***
*** Data ..........: Junho de 2016          ***
************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/types.h>
#define  tString 512

typedef struct _Arquivo
{
    char nome[tString];
    char caminho [tString];
} Arquivo;

Arquivo *pArquivos = NULL;

unsigned int arqAchados = 0;
unsigned int arqPercorridos = 0;
unsigned int dirPercorridos = 0;

char barraOS[2] = "\\";
char dirInicial[tString] = "C:\\";

void AddArquivo(Arquivo x)
{
    arqAchados++;
    pArquivos = (Arquivo *) realloc(pArquivos, arqAchados * sizeof(Arquivo));

    if (pArquivos == NULL)
    {
        printf("*** Memoria insuficiente ***\n");
        free(pArquivos);
        exit(1);
    }
    else
     pArquivos[arqAchados - 1] = x;
}

void Procurar(char dir[], char nome[])
{
    DIR *diretorio = opendir(dir);
    struct dirent *leitor;

    if(diretorio)
    {
        dirPercorridos++;
        while(leitor = readdir(diretorio))
            if(strcmp(leitor->d_name, ".") != 0 && strcmp(leitor->d_name, "..") != 0 )
            {
                char dirAtual[tString];
                sprintf(dirAtual, "%s%s%s", dir, barraOS, leitor->d_name);
                arqPercorridos++;

                if(strcmp(leitor->d_name, nome) == 0)
                {
                    Arquivo x;
                    strcpy(x.nome , leitor->d_name);
                    strcpy(x.caminho, dirAtual);
                    AddArquivo(x);
                }
                Procurar(dirAtual, nome);
            }
        closedir(diretorio);
    }
}

void ImprimirPesquisa()
{
    int i = 0;

    if(arqAchados == 0)
        printf("\n\n O arquivo nao foi encontrado...\n\n");
    else
    {
        printf("\n\n");
        printf(" Arquivo(s) encontrado(s)....: %8d\n", arqAchados);
        printf(" Arquivo(s) verificado(s)....: %8d\n", arqPercorridos);
        printf(" Diretorio(s) percorrido(s)..: %8d\n\n", dirPercorridos);

        for (i = 0; i < arqAchados; i++)
        {
           printf(" Numero...: %d \n", i + 1);
           printf(" Nome.....: %s\n", pArquivos[i].nome);
           printf(" Caminho..: %s\n\n", pArquivos[i].caminho);
        }
    }
}

void RealizaPesquisa(char arqPesquisar[])
{
    printf("\n Aguarde, procurando o arquivo...");
    Procurar(dirInicial, arqPesquisar);
    ImprimirPesquisa();
}

int main(int argc, char *argv[])
{
    if(argc == 1)
         printf("\nCade o que? \n\n");
    else if(argc > 3)
        printf("\n Entrada invalida... \n\n");
    else
    {
        if(argc == 3)
            strcpy(dirInicial, argv[2]);

        RealizaPesquisa(argv[1]);
    }

    free(pArquivos);
	return 0;
}