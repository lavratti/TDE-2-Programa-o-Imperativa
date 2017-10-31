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
#include "CalculusGA.h"

/*NUMEROS DAS ESCOLHAS NOS MENUS*/
#define PRODUTOS 1
#define DISTANCIAS 2
#define MOSTRA_LOG 3

#define PRODUTO_ESCALAR 1
#define PRODUTO_VETORIAL 2
#define PRODUTO_MISTO 3

#define DIST_DOIS_PONTOS 1
#define DIST_PONTO_RETA 2
#define DIST_DUAS_RETAS 3
#define DIST_RETA_PLANO 4
#define DIST_PONTO_PLANO 5

FILE *fp;

typedef struct {
    float x[5], y[5], z[5];
    float result;
    time_t timeraw;

} LOG;

/* Renomear para criarArquivoLog(), q tal? */
int Create_Log() {

    /* renomear log.txt -> historico.log, q tal? */
    fLog = fopen("log.txt", "r+b");

    if(fLog == NULL)
        fLog = fopen("log.txt", "w+b");

    if(fLog == NULL)
        return 0;
    else {
        /* SUGEST�O
        fclose(fLog);
        */
        return 1; // Foi possivel criar
    }
}


/* ZONA, ESCLARECER*/
int New_Log_Entry(float *x, float *y, float *z, float resultado) {
	
    int traw, i;
    
    Create_Log();    
    LOG a;
    a.result = resultado;
    printf("a.result = %f\n", a.result);
    
    for(i = 0; i<3; i++) {
        a.x[i] = x[i];
        a.y[i] = y[i];
        a.z[i] = z[i];
    }
    
    traw = time(NULL);
    a.timeraw = traw;
    
    fseek(fp, 0, SEEK_END);
    fwrite(&a, sizeof(a), 1, fp);
    fflush(fp);
    
    return 1;
}

/* TODO
int Remove_Log() {
}
/**/

void Show_Log() {

    Create_Log();    
    LOG a;
    fseek(fp, 0, SEEK_SET);  
	  
    while(fread(&a, sizeof(a), 1, fp) == 1) {    	
        puts("---------------------");
        printf("%s", ctime(&a.timeraw));
        printf("Resultado: %f\n", a.result);        
    }

}

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

    if (auxMenu >= PRODUTO_ESCALAR && auxMenu < PRODUTO_MISTO) {
        /* Evita repeti��o de printf e scanf em cada case */
        x = calloc(2, sizeof(float));
        y = calloc(2, sizeof(float));
        z = calloc(2, sizeof(float));

        printf("Digite as coordenadas (x, y, z) do primeiro vetor: ");
        scanf("%f%f%f", x, y, z);

        printf("Digite as coordenadas (x, y, z) do segundo vetor: ");
        scanf("%f%f%f", x+1, y+1, z+1);

        /* O Produto Misto Necessita de 3 vetores para realizar os calculos */
        if (auxMenu == PRODUTO_MISTO) {
            x = realloc(x, 3 * sizeof(float));
            y = realloc(y, 3 * sizeof(float));
            z = realloc(z, 3 * sizeof(float));

            printf("Digite as coordenadas (x, y ,z) do terceiro vetor: ");
            scanf("%f%f%f", x+2, y+2, z+2);

        }

    }

    switch (auxMenu) {

	    case PRODUTO_ESCALAR:
	        resultado = prod_escalar(x, y, z);
	        printf("Produto escalar = %.9f\n", resultado);
	        New_Log_Entry(x, y, z, resultado);
	        break;
	
	    case PRODUTO_VETORIAL:
	        prod_vet(x, y, z);
	        printf("Produto vetorial = (%f, %f, %f)\n", x[2], y[2], z[2]);
	        break;
	
	    case PRODUTO_MISTO:
	        printf("Produto misto = %f\n", prod_misto(x, y, z));
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
    
	fflush(stdin);    
    switch(getchar()-48) {
	
	    case DIST_DOIS_PONTOS:
	        printf("Informe as coordenadas (x,y,z) do primeiro ponto: ");
	        scanf("%f%f%f", &x[0], &y[0], &z[0]);
	
	        printf("Informe as coordenads (x,y,z) do segundo ponto: ");
	        scanf("%f%f%f", &x[1], &y[1], &z[1]);
	
	        resultado = dist_pontos(x, y, z);
	
	        break;
	
	    case DIST_PONTO_RETA:
	        printf("Informe as coordenadas (x, y, z) do vetor diretor: ");
	        scanf("%f%f%f", &x[0], &y[0], &z[0]);
	
	        printf("Informe as coordenadas (x,y,z) do ponto desejado: ");
	        scanf("%f%f%f", &x[1], &y[1], &z[1]);
	
	        printf("Informe as coordenads (x,y,z) de um ponto pertencente a reta: ");
	        scanf("%f%f%f", &x[2], &y[2], &z[2]);
	
	        printf("A distancia entre o ponto e a reta eh: %f\n", dist_ponto_reta(x, y, z));
	
	        break;
	
	    case DIST_DUAS_RETAS:
	        printf("Informe as coordenadas (x, y, z) do vetor diretor da reta r: ");
	        scanf("%f%f%f", &x[0], &y[0], &z[0]);
	
	        printf("Informe as coordenadas (x, y, z) do vetor diretor da reta s: ");
	        scanf("%f%f%f", &x[1], &y[1], &z[1]);
	
	        if (x[0]/x[1] == y[0]/y[1] && y[0]/y[1] == z[0]/z[1]) {
	            printf("Informe as coordenadas (x,y,z) do ponto  a reta s: ");
	            scanf("%f%f%f", &x[1], &y[1], &z[1]);
	
	            printf("Informe as coordenads (x,y,z) de um ponto  a reta r: ");
	            scanf("%f%f%f", &x[2], &y[2], &z[2]);
	
	            printf("A distancia entre as reta eh: %f\n", dist_retas(x, y, z));
	
	        } else {
	            printf("Informe as coordenadas (x, y, z) de um ponto da reta r: ");
	            scanf("%f%f%f", &x[2], &y[2], &z[2]);
	
	            printf("Informe as coordenadas (x, y, z) de um ponto da reta s: ");
	            scanf("%f%f%f", &x[3], &y[3], &z[3]);
	
	            printf("A distancia entre as duas retas eh: %f\n", dist_retas_reversas(x, y, z));
	
	        }
	        
	        break;
	
	    case DIST_RETA_PLANO:
	        printf("Digite as coordenadas (x, y, z) do vetor diretor do plano e o termo 'd': ");
	        scanf("%f%f%f%f", &x[0], &y[0], &z[0], &d);
	
	        printf("Informe um ponto da reta (x, y, z): ");
	        scanf("%f%f%f", &x[1], &y[1], &z[1]);
	
	        printf("A distancia entre a reta e o plano eh: %f\n", dist_reta_plano(x, y, z, d));
	
	        break;
	
	    case DIST_PONTO_PLANO:
	        printf("Digite as coordenadas (x, y, z) do vetor diretor do plano e o termo 'd': ");
	        scanf("%f%f%f%f", &x[0], &y[0], &z[0], &d);
	
	        printf("Digite as coordenadas (x, y, z) do ponto: ");
	        scanf("%f%f%f", &x[1], &y[1], &z[1]);
	
	        printf("A distancia entre o ponto e o plano eh: %f\n", dist_ponto_plano(x, y, z, d));
	
	        break;
	        
    }

}

int main() {

    while (1) {
        /* Menu Prim�rio*/
        printf("1 - \t Produtos entre vetores\n"
               "2 - \t Distancias\n"
               "3 - \t Sair do programa\n"
               "4 - \t Mostrar log\n"
               "Digite o numero correspondente a opcao desejada: ");
        fflush(stdin);
        switch (getchar()-48) {
        	
	        case PRODUTOS:
	            menuProdutos();
	            break;
	
	        case DISTANCIAS:
	            menuDistancias();
	            break;
	
	        case MOSTRA_LOG:
	            Show_Log();
	            break;
	    }

        printf("Deseja continuar? (1 - Sim) (Outro - Nao)\n");
        fflush(stdin);
        if (getchar() != '1')
            return 0;

        printf("Retornando ao meu principal... \n");
        system("pause");
        system("cls");


    }
    /* Remover? vide sugest�o*/
    fclose(fp);
    return 0;
    
}
