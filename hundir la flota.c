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
    int i, j, sel=0, aux[5]={0,0,0,0,0};
    char selchar[2], res[3], J1[10][10], J1B[10][10], J2[10][10], J2B[10][10];

    for (i=0;i<10;i++){
        for(j=0;j<10;j++){
            J1[i][j]=' ';
            J2[i][j]=' ';
            J1B[i][j]=' ';
            J2B[i][j]=' ';
        }
    }
    printf("%c",J2[1][1]);
    printf("%c",J2B[1][1]);
    printf("%c",J1B[1][1]);

    system("cls");

    printf("FASE 1: ");
    Sleep(800);
    printf("COLOCA TUS BARCOS\n\n");
    Sleep(1000);

    do{

        printf("     |     |     |     |     |     |     |     |     |     |     |\n");
        printf("     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |  I  |  J  |\n");
        printf("_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
        for(i=0;i<10;i++){
            printf("     ");
            for(j=0;j<10;j++){
                printf("|");
                if(J1[i][j]=='.'){
                    color(AZUL_AZUL);
                }
                printf("     ");
                color(BLANCO);
            }
            printf("|\n");
            printf("  %i  ",i);
            printf("|");
            for(j=0;j<10;j++){
                if(J1[i][j]=='X'){
                    color(ROJO);
                }
                if(J1[i][j]=='.'){
                    color(AZUL_AZUL);
                }
                printf("  %c  ", J1[i][j]);
                color(BLANCO);
                printf("|");
            }
            printf("\n");
            printf("_____");
            for(j=0;j<10;j++){
                color(BLANCO);
                printf("|");
                if(J1[i][j]=='.'){
                    color(AZUL_BLANCO);
                }
                printf("_____");
            }
            color(BLANCO);
            printf("|\n");
        }
        color(BLANCO);
        printf("\n\n");

        i=2;
        j=1;

        printf("Elige un barco para colocar:\n");
        if(aux[0]!=1){
            if(sel==i-1){
                aux[0]=1;
            }else{
                printf("    %i. Portaaviones:     5 casillas\n",j);
                j++;
            }
            i++;
        }
        if(aux[1]!=1){
            if(sel==i-1){
                aux[1]=1;
            }else{
                printf("    %i. Acorazado:        4 casillas\n",j);
                j++;
            }
            i++;
        }
        if(aux[2]!=1){
            if(sel==i-1){
                aux[2]=1;
            }else{
                printf("    %i. Submarino:        3 casillas\n",j);
                j++;
            }
            i++;
        }
        if(aux[3]!=1){
            if(sel==i-1){
                aux[3]=1;
            }else{
                printf("    %i. Destructor:       3 casillas\n",j);
                j++;
            }
            i++;
        }
        if(aux[4]!=1){
            if(sel==i-1){
                aux[4]=1;
            }else{
                printf("    %i. Barco patrulla:   2 casillas\n",j);
                j++;
            }
            i++;
        }
        //printf("%i,%i,%i,%i,%i\n",aux[0],aux[1],aux[2],aux[3],aux[4]);
        if(j!=1){
            fflush(stdin);
            fgets(selchar,sizeof(selchar),stdin);
            sel=atoi(selchar);
            system("cls");
            if(sel<=0 || sel>=j){
                printf("Opcion incorrecta\n\n");
                sel=0;
                Sleep(500);
            }
        }
    }while(j!=2 || sel<=0);

}