#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define AZUL 1
#define VERDE 2
#define ROJO 4
#define AMARILLO 6
#define BLANCO 7
#define AZUL_AZUL 153
#define AZUL_ROJO 156
#define AZUL_BLANCO 159

void color(int);
void jugarIA();

int main(){
    char res;
    system("cls");
    printf("Programa creado por:\n");
    printf("    - Twitter: @DurumSoloCarne_\n");
    printf("    - Discord: @durumsolocarne\n\n\n");
    Sleep(1000);
    /*system("cls");
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(700);
    system("cls");
    printf("AGUA\n\n");
    Sleep(1000);*/
    do{
        printf("---------- HUNDIR LA FLOTA ----------\n\n");
        printf("Seleciona una opcion: \n");
        printf("1. Jugar contra la IA\n");
        printf("2. Jugar contra una persona (Local)\n");
        printf("3. Informacion\n");
        printf("4. Salir\n");

        fflush(stdin);
        scanf("%c", &res);

        system("cls");

        switch(res){
            case '1':
                jugarIA();
                break;
            case '2':

                break;
            case '3':

                break;
            case '4':
                printf("Programa creado por:\n");
                printf("    - Twitter: @DurumSoloCarne_\n");
                printf("    - Discord: @durumsolocarne\n\n");
                printf("Muchas gracias por jugar. :P\n\n");
                Sleep(3000);
                return 0;
            default:
                printf("Opcion incorrecta\n\n");
                break;
        }

    }while(res!='4');
}

void color(int k){
    HANDLE Consola = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(Consola,k);
}

void jugarIA(){
    char J1[10][10], J2[10][10], i, j;

    for (i=0;i<10;i++){
        for(j=0;j<10;j++){
            J1[i][j]=' ';
            J2[i][j]=' ';
        }
    }
    J1[5][5]='.';

    system("cls");
    printf("________________________________________\n");
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            printf("|");
            if(J1[i][j]=='.'){
                color(AZUL_AZUL);
            }
            printf("   ");
            color(BLANCO);
        }
        printf("|");
        printf("\n");
        printf("|");
        for(j=0;j<10;j++){
            if(J1[i][j]=='X'){
                color(ROJO);
            }
            if(J1[i][j]=='.'){
                color(AZUL_AZUL);
            }
            printf(" %c ", J1[i][j]);
            color(BLANCO);
            printf("|");
        }
        printf("\n");
        for(j=0;j<10;j++){
            color(BLANCO);
            printf("|");
            if(J1[i][j]=='.'){
                color(AZUL_BLANCO);
            }
            printf("___");
        }
        color(BLANCO);
        printf("|");
        printf("\n");
        /*printf("|");
        for(j=0;j<10;j++){
            if(MU[i][j]=='X'){
                color(ROJO);
            }
            if(MU[i][j]=='.'){
                color(AZUL_AZUL);
            }
            printf("%c ", MU[i][j]);
            color(BLANCO);
            printf("|");
        }
        printf("\n");
        for(j=0;j<10;j++){
            color(BLANCO);
            printf("|");
            if(MU[i][j]=='.'){
                color(AZUL_BLANCO);
            }
            printf("__");
        }
        color(BLANCO);
        printf("|");
        printf("\n");*/
    }
    color(BLANCO);

    printf("\n\n");

    sleep(60);
}