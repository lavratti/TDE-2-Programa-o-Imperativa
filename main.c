/************************
* Desenvolvido por:		*
*	Lucas Lavratti		*
*	Wesley Ribeiro		*
************************/

/* Realiza diversos calculos envolvendo vetores*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "CalculusGA.h"

/*NUMEROS DAS ESCOLHAS NOS MENUS*/
#define PRODUTOS 1
#define DISTANCIAS 2
#define MOSTRA_LOG 3
#define REMOVE_LOG 4

#define PRODUTO_ESCALAR 1
#define PRODUTO_VETORIAL 2
#define PRODUTO_MISTO 3

#define DIST_DOIS_PONTOS 1
#define DIST_PONTO_RETA 2
#define DIST_DUAS_RETAS 3
#define DIST_RETA_PLANO 4
#define DIST_PONTO_PLANO 5

//Para evitar alocaÃ§Ã£o dinamica em lugares que nÃ£o faz muita diferenÃ§a

#define MAGIA_NEGRA 32

FILE *fLog;

/*
 *	Codigo n funfa no linux corretamente,
 *	Abaixo um pedaco de portabilidade
 *	Mude novamente para fflush(stdin) no windows
 */

void clean_stdin(void) {
    fflush(stdin);
    /* UNCOMMENT IF LINUX

    int c;

    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
    /**/

}

float preLog[MAGIA_NEGRA];

int novaEntrada(int argc, float *argv) {

    int i;

    fLog = fopen("historico.log", "a+t");

    if(fLog == NULL)	/* NÃÂ£o foi possivel ler ou o arquivo nÃÂ£o existe */
        fLog = fopen("historico.log", "w+t"); //Linha desnecessaria pois o modo a+t cria o arquivo se ele nao existir

    if(fLog == NULL)
        return 0; // NÃÂ£o foi possÃÂ­vel criar o arquivo

    fprintf(fLog, "%ld;",time(NULL));
    fprintf(fLog, "%d;",argc);

    for (i = 0 ; i < argc; i++) {
        fprintf(fLog, "%f;",*(argv+i));
        //printf(" LOG> %f \n",*(argv+i));
    }
    fprintf(fLog, "\n");
    fflush(fLog); /* Talvez nao seja necessario pois o fclose alem de fechar tambem grava em disco os dados */
    fclose(fLog);
    printf("\n <LOG OK> \n");
    return 1;

}

int Remove_Log() { 

    fLog = fopen("historico.log", "r+t");
    
    /* Se nao foi possivel ler o arquivo e/ou renomear */
    
    if((rename("historico.log", "historico.log.old") != 0) || fLog == NULL)
        return 0;
    /* Se foi possivel ler e renomear */
    else
        return 1; 
}

int mostraLog() {

    time_t logData;
    int i, j, argc;
    float aux1, aux2, *argv;
    char legivel[MAGIA_NEGRA];

    fLog = fopen("historico.log", "rt");

    if(fLog == NULL)
        return 0;

    for(i = 0; 1; i++) {

        fscanf(fLog,"%ld;%d;%f;%f;", &logData, &argc, &aux1, &aux2);

        /* Se chegar ao final do arquivo, saia do loop*/
        if(feof(fLog))
            break ;


        strcpy(legivel, asctime(localtime(&logData)));
        legivel[ strlen(legivel) - 1] = 0;

        //printf("%s> ", asctime(localtime(&logData)));
        printf("Log #%d, %s\ns", i, legivel);

        if ((int)aux1 == PRODUTOS) {

            switch((int)aux2) {
            case PRODUTO_ESCALAR:
                printf("Produto Escalar\n");
                break;

            case PRODUTO_VETORIAL:
                printf("Produto Vetorial\n");
                break;

            case PRODUTO_MISTO:
                printf("Produto Misto\n");
                break;
            }

        }

        if ((int)aux1 == DISTANCIAS) {

            switch((int)aux2) {
            case DIST_DOIS_PONTOS:
                printf("Distancia entre dois pontos\n");
                break;

            case DIST_PONTO_RETA:
                printf("Distancia entre ponto e reta\n");
                break;

            case DIST_DUAS_RETAS:
                printf("Distancia entre duas retas\n");
                break;

            case DIST_RETA_PLANO:
                printf("Distancia entre reta e plano\n");
                break;

            case DIST_PONTO_PLANO:
                printf("Distancia entre ponto e plano\n");
                break;
            }

        }

        printf("Entradas: ");

        argv = (float *)malloc((argc-2)*sizeof(float));

        for(j = 0; j < (argc-4); j++) {
            fscanf(fLog,"%f;", argv+j);
            printf("%.2f, ",*(argv+j));
        }

        fscanf(fLog,"%f;", argv+j);
        printf("%.2f\n",*(argv+j));
        j++;

        fscanf(fLog,"%f;", argv+j);
        printf("Resultado = %.2f\n\n",*(argv+j));
    }

    fclose(fLog);
    return 1;
}
/**/
void menuProdutos() {

    int auxMenu = 0;
    float resultado = 0;
    float *x, *y, *z;

    printf("1 - \t Produto Escalar\n"
           "2 - \t Produto Vetorial\n"
           "3 - \t Produto Misto\n"
           "Outro -  Retonar ao menu principal\n"
           "Digite o numero correspondente a opcao desejada: ");

    scanf(" %1d", &auxMenu);

    preLog[1] = auxMenu;

    if (auxMenu >= PRODUTO_ESCALAR && auxMenu <= PRODUTO_MISTO) {
        /* Evita repeti??o de printf e scanf em cada case */
        x = calloc(2, sizeof(float));
        y = calloc(2, sizeof(float));
        z = calloc(2, sizeof(float));

        printf("Digite as coordenadas (x, y, z) do primeiro vetor: ");
        scanf("%f%f%f", x, y, z);
        preLog[2] = *x;
        preLog[3] = *y;
        preLog[4] = *z;


        printf("Digite as coordenadas (x, y, z) do segundo vetor: ");
        scanf("%f%f%f", x+1, y+1, z+1);
        preLog[5] = *(x+1);
        preLog[6] = *(y+1);
        preLog[7] = *(z+1);
        /* O Produto Misto Necessita de 3 vetores para realizar os calculos */
        if (auxMenu == PRODUTO_MISTO) {

            x = realloc(x, 3 * sizeof(float));
            y = realloc(y, 3 * sizeof(float));
            z = realloc(z, 3 * sizeof(float));

            printf("Digite as coordenadas (x, y ,z) do terceiro vetor: ");
            scanf("%f%f%f", x+2, y+2, z+2);
            preLog[8] = *(x+2);
            preLog[9] = *(y+2);
            preLog[10] = *(z+2);

        }

    }

    switch (auxMenu) {

    case PRODUTO_ESCALAR:
        resultado = prod_escalar(x, y, z);
        preLog[8] = resultado;
        printf("Produto escalar = %.9f\n", resultado);
        novaEntrada(9, preLog);
        break;

    case PRODUTO_VETORIAL:
        prod_vet(x, y, z);
        preLog[8] = *(x+2);
        preLog[9] = *(y+2);
        preLog[10] = *(z+2);
        printf("Produto vetorial = (%f, %f, %f)\n", x[2], y[2], z[2]);
        novaEntrada(11, preLog);
        break;

    case PRODUTO_MISTO:
        resultado = prod_misto(x, y, z);
        preLog[11] = resultado;
        printf("Produto misto = %f\n", resultado);
        novaEntrada(12, preLog);
        break;

    }

}

void menuDistancias() {

    float d[1] = {0};
    float resultado = 0;
    float *x, *y, *z;

    x = calloc(3, sizeof(float));
    y = calloc(3, sizeof(float));
    z = calloc(3, sizeof(float));


    printf("1 - \t Distancia entre dois pontos\n"
           "2 - \t Distancia entre ponto e reta\n"
           "3 - \t Distancia entre duas retas\n"
           "4 - \t Distancia entre reta e plano\n"
           "5 - \t Distancia entre ponto e plano\n"
           "Outro -  Retornar ao menu principal\n"
           "Informe o numero correspondente a opcao desejada: ");

    clean_stdin();

    switch(getchar()-48) {

    case DIST_DOIS_PONTOS:
        preLog[1] = DIST_DOIS_PONTOS;

        printf("Informe as coordenadas (x,y,z) do primeiro ponto: ");
        scanf("%f%f%f", &x[0], &y[0], &z[0]);
        preLog[2] = *x;
        preLog[3] = *y;
        preLog[4] = *z;

        printf("Informe as coordenads (x,y,z) do segundo ponto: ");
        scanf("%f%f%f", &x[1], &y[1], &z[1]);
        preLog[5] = *(x+1);
        preLog[6] = *(y+1);
        preLog[7] = *(z+1);

        resultado = dist_pontos(x, y, z);
        preLog[8] = resultado;
        novaEntrada(9, preLog);

        printf("A distancia entre o ponto e o ponto eh: %f\n", resultado);

        break;

    case DIST_PONTO_RETA:
        preLog[1] = DIST_PONTO_RETA;

        printf("Informe as coordenadas (x, y, z) do vetor diretor: ");
        scanf("%f%f%f", &x[0], &y[0], &z[0]);
        preLog[2] = *x;
        preLog[3] = *y;
        preLog[4] = *z;

        printf("Informe as coordenadas (x,y,z) do ponto desejado: ");
        scanf("%f%f%f", &x[1], &y[1], &z[1]);
        preLog[5] = *(x+1);
        preLog[6] = *(y+1);
        preLog[7] = *(z+1);

        printf("Informe as coordenads (x,y,z) de um ponto pertencente a reta: ");
        scanf("%f%f%f", &x[2], &y[2], &z[2]);
        preLog[8] = *(x+2);
        preLog[9] = *(y+2);
        preLog[10] = *(z+2);

        resultado = dist_ponto_reta(x, y, z);
        preLog[11] = resultado;
        novaEntrada(12, preLog);

        printf("A distancia entre o ponto e a reta eh: %f\n", resultado);

        break;

    case DIST_DUAS_RETAS:
        preLog[1] = DIST_DUAS_RETAS;

        printf("Informe as coordenadas (x, y, z) do vetor diretor da reta r: ");
        scanf("%f%f%f", &x[0], &y[0], &z[0]);
        preLog[2] = *x;
        preLog[3] = *y;
        preLog[4] = *z;
        printf("Informe as coordenadas (x, y, z) do vetor diretor da reta s: ");
        scanf("%f%f%f", &x[1], &y[1], &z[1]);
        preLog[5] = *(x+1);
        preLog[6] = *(y+1);
        preLog[7] = *(z+1);

        if (x[0]/x[1] == y[0]/y[1] && y[0]/y[1] == z[0]/z[1]) {
            printf("Informe as coordenadas (x,y,z) do ponto  a reta s: ");
            scanf("%f%f%f", &x[1], &y[1], &z[1]);
            preLog[8] = *(x+2);
            preLog[9] = *(y+2);
            preLog[10] = *(z+2);

            printf("Informe as coordenads (x,y,z) de um ponto  a reta r: ");
            scanf("%f%f%f", &x[2], &y[2], &z[2]);
            preLog[11] = *(x+3);
            preLog[12] = *(y+3);
            preLog[13] = *(z+3);

            resultado = dist_retas(x, y, z);
            preLog[14] = resultado;
            novaEntrada(15, preLog);

            printf("A distancia entre as reta eh: %f\n", resultado);

        } else {
            printf("Informe as coordenadas (x, y, z) de um ponto da reta r: ");
            scanf("%f%f%f", &x[2], &y[2], &z[2]);
            preLog[8] = *(x+2);
            preLog[9] = *(y+2);
            preLog[10] = *(z+2);

            printf("Informe as coordenadas (x, y, z) de um ponto da reta s: ");
            scanf("%f%f%f", &x[3], &y[3], &z[3]);
            preLog[11] = *(x+3);
            preLog[12] = *(y+3);
            preLog[13] = *(z+3);

            resultado = dist_retas_reversas(x, y, z);
            preLog[14] = resultado;
            novaEntrada(15, preLog);


            printf("A distancia entre as duas retas eh: %f\n", resultado);

        }

        break;

    case DIST_RETA_PLANO:
        preLog[1] = DIST_RETA_PLANO;

        printf("Digite as coordenadas (x, y, z) do vetor diretor do plano e o termo 'd': ");

        scanf("%f%f%f%f", &x[0], &y[0], &z[0], &d);

        preLog[2] = *x;
        preLog[3] = *y;
        preLog[4] = *z;

        printf("Informe um ponto da reta (x, y, z): ");
        scanf("%f%f%f", &x[1], &y[1], &z[1]);
        preLog[5] = *(x+1);
        preLog[6] = *(y+1);
        preLog[7] = *(z+1);

        resultado = dist_reta_plano(x, y, z, d);
        preLog[8] = resultado;
        novaEntrada(9, preLog);

        printf("A distancia entre a reta e o plano eh: %f\n", resultado);

        break;

    case DIST_PONTO_PLANO:
        preLog[1] = DIST_PONTO_PLANO;

        printf("Digite as coordenadas (x, y, z) do vetor diretor do plano e o termo 'd': ");

        scanf("%f%f%f%f", &x[0], &y[0], &z[0], &d);

        preLog[2] = *x;
        preLog[3] = *y;
        preLog[4] = *z;
        preLog[5] = *d;

        printf("Digite as coordenadas (x, y, z) do ponto: ");
        scanf("%f%f%f", &x[1], &y[1], &z[1]);
        preLog[6] = *(x+1);
        preLog[7] = *(y+1);
        preLog[8] = *(z+1);

        resultado = dist_ponto_plano(x, y, z, d);
        preLog[9] = resultado;
        novaEntrada(10, preLog);

        printf("A distancia entre o ponto e o plano eh: %f\n", resultado);

        break;

    }

}

int main(int argc, char *argv[]) {

    while (1) {
        /* Menu Prim?rio*/
        printf("1 - \t Produtos entre vetores\n"
               "2 - \t Distancias\n"
               "3 - \t Mostrar log\n"
               "4 - \t Remover log\n"
               "Outro -  Sair do programa\n"
               "Digite o numero correspondente a opcao desejada: ");

        /*clean_stdin() reposicionado pro fim do loop
         * estava bugando a primeira execucao
         * pedindo 2x entrada do usuario
         */
        switch (getchar()-48) {

        case PRODUTOS:
            preLog[0] = PRODUTOS;
            menuProdutos();
            break;

        case DISTANCIAS:
            preLog[0] = DISTANCIAS;
            menuDistancias();
            break;

        case MOSTRA_LOG:
            mostraLog();
            break;

        case REMOVE_LOG:
            Remove_Log();
            break;
        }

        printf("Deseja continuar? (1 - Sim) (Outro - Nao)\n");
        clean_stdin();
        if (getchar() != '1')
            return 0;

        clean_stdin();
        printf("Retornando ao meu principal... \n");
        //system("pause"); /* SUGESTAO: Substituir por getchar(), pois nao funciona no linux */
        system("clear || cls");  /* Para 'limpar' a tela tanto no linux quanto no windows*/
        

    }

    return 0;

}
