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

//'O'=Barco colocado en ese lugar
//'X'=Barco tocado
//' '=Casilla libre
//'A'=Agua
//'H'=Barco totalmente hundido

void color(int);
void jugarIA(int);
void print_matriz(char [11][11], int);
void ordenar(int *,int);
void colocar_barcos(char [11][11], int);
int atacar(char [10][10], char [11][11], int);
int atacarIA(char [10][10], char [11][11], int, char [2], char [2]);

int main(){
    char res;

    srand(time(NULL));

    system("cls");
    printf("Programa creado por:\n");
    printf("    - Twitter: @DurumSoloCarne_\n");
    printf("    - Discord: @durumsolocarne\n\n\n");
    Sleep(1000);

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
                jugarIA(1);
                break;
            case '2':
                jugarIA(0);
                break;
            case '3':

                break;
            case '4':
                printf("Programa creado por:\n");
                printf("    - Twitter: @DurumSoloCarne_\n");
                printf("    - Discord: @durumsolocarne\n\n");
                printf("Muchas gracias por jugar. :P\n\n");
                Sleep(2000);
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

void jugarIA(int IA){
    int i,j,hundidos1,hundidos2,turno=1;
    char J1[10][10], J1B[11][11], J2[10][10], J2B[11][11], pos_ant1[2]={'\0','\0'}, pos_ant2[2]={'\0','\0'};

    for (i=0;i<10;i++){
        for(j=0;j<10;j++){
            J1[i][j]=' ';
            J2[i][j]=' ';
            J1B[i][j]=' ';
            J2B[i][j]=' ';
        }
    }
    system("cls");

    printf("FASE 1: ");
    Sleep(800);
    printf("COLOCA TUS BARCOS\n\n");
    Sleep(1000);

    //colocar_barcos(J2B,IA);
    //print_matriz(J2B,0);
    //Sleep(10000);
        
    if(IA!=1){
        printf("TURNO DEL JUGADOR 1\n\n");
        Sleep(800);
    }
    colocar_barcos(J1B,0);
    
    if(IA!=1){
        printf("TURNO DEL JUGADOR 2\n\n");
        Sleep(800);
    }
    colocar_barcos(J2B,IA);

    printf("FASE 2: ");
    Sleep(800);
    printf("ATACA AL ENEMIGO\n\n");
    Sleep(1000);

    do{
        if(IA!=1){
            printf("TURNO DEL JUGADOR %i\n\n",turno);
        }
        Sleep(800);

        if(IA!=1){
            if(turno==1){
                hundidos1=atacar(J2,J2B,hundidos1);
                turno++;
            }else{
                hundidos2=atacar(J1,J1B,hundidos2);
                turno--;
            }
        }else{
            if(turno==1){
                hundidos1=atacar(J2,J2B,hundidos1);
                turno++;
            }else{
                hundidos2=atacarIA(J1,J1B,hundidos2,pos_ant1,pos_ant2);
                turno--;
            }
        }

    }while(hundidos1!=5 || hundidos2!=5);
}

void print_matriz(char M[11][11], int selector){
    int i,j;

    if(selector){

    }
    printf("     |     |     |     |     |     |     |     |     |     |     |\n");
    printf("     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |  I  |  J  |\n");
    printf("_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
    for(i=0;i<10;i++){
        printf("     ");
        for(j=0;j<10;j++){
            printf("|");
            if(M[i][j]=='.'){
                color(AZUL_AZUL);
            }
            printf("     ");
            color(BLANCO);
        }
        printf("|\n");
        printf("  %i  ",i);
        printf("|");
        for(j=0;j<10;j++){
            if(M[i][j]=='X'){
                color(ROJO);
            }
            if(M[i][j]=='.'){
                color(AZUL_AZUL);
            }
            printf("  %c  ",M[i][j]);
            color(BLANCO);
            printf("|");
        }
        printf("\n");
        printf("_____");
        for(j=0;j<10;j++){
            color(BLANCO);
            printf("|");
            if(M[i][j]=='.'){
                color(AZUL_BLANCO);
            }
            printf("_____");
        }
        color(BLANCO);
        printf("|\n");
    }
    color(BLANCO);
    printf("\n\n");
}

void ordenar(int *v, int tamaño){
    int i,j,aux;

    for(i=0;i<tamaño;i++){
        for(j=1+i;j<tamaño;j++){
            if(v[i]>v[j]){
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }
        }
    }
}

void colocar_barcos(char M[11][11], int IA){
    int i, j,pos1,pos2, resta1, resta2, sel=0, *v, v_tamaño[5]={5,4,3,3,2}, selector=0, barcos_colocados=0;
    char auxchar[3], res[6];

    v=(int *)malloc(5 * sizeof(int));

    for(i=0;i<5;i++){
        v[i]=i;
    }

    do{
        if(IA!=1){
            print_matriz(M,selector);

            i=1;

            printf("Elige un barco para colocar:\n");
            if(v[0]==0 || v[1]==0 || v[2]==0 || v[3]==0 || v[4]==0){
                printf("    %i. Portaaviones:     5 casillas\n",i);
                i++;
            }
            if(v[0]==1 || v[1]==1 || v[2]==1 || v[3]==1 || v[4]==1){
                printf("    %i. Acorazado:        4 casillas\n",i);
                i++;
            }
            if(v[0]==2 || v[1]==2 || v[2]==2 || v[3]==2 || v[4]==2){
                printf("    %i. Submarino:        3 casillas\n",i);
                i++;
            }
            if(v[0]==3 || v[1]==3 || v[2]==3 || v[3]==3 || v[4]==3){
                printf("    %i. Destructor:       3 casillas\n",i);
                i++;
            }
            if(v[0]==4 || v[1]==4 || v[2]==4 || v[3]==4 || v[4]==4){
                printf("    %i. Barco patrulla:   2 casillas\n",i);
                i++;
            }

            fflush(stdin);
            fgets(auxchar,3,stdin);
            sel=atoi(auxchar);
        }else{
            do{
                pos1=rand()%10;
                pos2=rand()%10;
            }while(pos1+v_tamaño[barcos_colocados]>=10 && pos2+v_tamaño[barcos_colocados]>=10);
        }
        if(IA!=1 && (sel<=0 || sel>=i)){
            system("cls");
            printf("Opcion incorrecta\n\n");
            sel=0;
            Sleep(500);
        }else{
            do{
                if(IA!=1){
                    printf("\nIntroduce los extremos de la ubicacion de tu barco (Ejemplo A2-E2)\n");
                    fflush(stdin);
                    fgets(res,6,stdin);
                    system("cls");
                    if(toupper(res[1])=='A' || toupper(res[1])=='B' || toupper(res[1])=='C' || toupper(res[1])=='D' || toupper(res[1])=='E' || toupper(res[1])=='F' || toupper(res[1])=='G' || toupper(res[1])=='H' || toupper(res[1])=='I' || toupper(res[1])=='J'){
                        auxchar[0]=res[1];
                        res[1]=res[0];
                        res[0]=auxchar[0];
                    }
                    if(toupper(res[4])=='A' || toupper(res[4])=='B' || toupper(res[4])=='C' || toupper(res[4])=='D' || toupper(res[4])=='E' || toupper(res[4])=='F' || toupper(res[4])=='G' || toupper(res[4])=='H' || toupper(res[4])=='I' || toupper(res[4])=='J'){
                        auxchar[0]=res[4];
                        res[4]=res[3];
                        res[3]=auxchar[0];
                    }
                }
                if(IA==1 || (res[5]=='\0' && res[2]=='-' && (toupper(res[0])=='A' || toupper(res[0])=='B' || toupper(res[0])=='C' || toupper(res[0])=='D' || toupper(res[0])=='E' || toupper(res[0])=='F' || toupper(res[0])=='G' || toupper(res[0])=='H' || toupper(res[0])=='I' || toupper(res[0])=='J') && (res[1]=='0' || res[1]=='1' || res[1]=='2' || res[1]=='3' || res[1]=='4' || res[1]=='5' || res[1]=='6' || res[1]=='7' || res[1]=='8' || res[1]=='9') && (toupper(res[3])=='A' || toupper(res[3])=='B' || toupper(res[3])=='C' || toupper(res[3])=='D' || toupper(res[3])=='E' || toupper(res[3])=='F' || toupper(res[3])=='G' || toupper(res[3])=='H' || toupper(res[3])=='I' || toupper(res[3])=='J') && (res[4]=='0' || res[4]=='1' || res[4]=='2' || res[4]=='3' || res[4]=='4' || res[4]=='5' || res[4]=='6' || res[4]=='7' || res[4]=='8' || res[4]=='9'))){
                    if(IA!=1){
                        resta1=abs(res[0]-res[3])+1;
                        resta2=abs(res[1]-res[4])+1;
                    }else{
                        sel=-2;
                        j=rand()%2;
                        if(pos2+v_tamaño[barcos_colocados]<10 && j==0){
                            for(i=pos2;i<v_tamaño[barcos_colocados]+pos2;i++){
                                if(M[i-1][pos1]=='O' || M[i+1][pos1]=='O' || M[i][pos1-1]=='O' || M[i][pos1+1]=='O'){
                                    sel=-1;
                                }
                            }
                            if(sel!=-1){
                                for(i=pos2;i<v_tamaño[barcos_colocados]+pos2;i++){
                                    M[i][pos1]='O';
                                }
                                barcos_colocados++;
                            }
                        }else if(pos1+v_tamaño[barcos_colocados]<10 && j==1){
                            for(i=pos1;i<v_tamaño[barcos_colocados]+pos1;i++){
                                if(M[pos2][i-1]=='O' || M[pos2][i+1]=='O' || M[pos2-1][i]=='O' || M[pos2+1][i]=='O'){
                                    sel=-1;
                                }
                            }
                            if(sel!=-1){
                                for(i=pos1;i<v_tamaño[barcos_colocados]+pos1;i++){
                                    M[pos2][i]='O';
                                }
                                barcos_colocados++;
                            }
                        }
                    }
                    if(IA!=1 &&((resta1==1 && resta2==v_tamaño[sel-1]) || (resta1==v_tamaño[sel-1] && resta2==1))){
                        if(res[0]>res[3]){
                            auxchar[0]=res[0];
                            res[0]=res[3];
                            res[3]=auxchar[0];
                        }
                        if(res[1]>res[4]){
                            auxchar[0]=res[1];
                            res[1]=res[4];
                            res[4]=auxchar[0];
                        }
                        if(resta1!=1){
                            switch(toupper(res[0])){
                                case 'A':
                                    i=0;
                                    break;
                                case 'B':
                                    i=1;
                                    break;
                                case 'C':
                                    i=2;
                                    break;
                                case 'D':
                                    i=3;
                                    break;
                                case 'E':
                                    i=4;
                                    break;
                                case 'F':
                                    i=5;
                                    break;
                                case 'G':
                                    i=6;
                                    break;
                                case 'H':
                                    i=7;
                                    break;
                                case 'I':
                                    i=8;
                                    break;
                                case 'J':
                                    i=9;
                                    break;
                            }
                            for(j=i;j<resta1+i;j++){
                                if(M[(res[1]-'0')-1][j]=='O' || M[(res[1]-'0')+1][j]=='O' || M[res[1]-'0'][j-1]=='O' || M[res[1]-'0'][j+1]=='O'){
                                    sel=-1;
                                }
                            }
                            if(sel!=-1){
                                for(j=i;j<resta1+i;j++){
                                    M[res[1]-'0'][j]='O';
                                }  
                            }       
                        }else{
                            switch(res[1]){
                                case '0':
                                    i=0;
                                    break;
                                case '1':
                                    i=1;
                                    break;
                                case '2':
                                    i=2;
                                    break;
                                case '3':
                                    i=3;
                                    break;
                                case '4':
                                    i=4;
                                    break;
                                case '5':
                                    i=5;
                                    break;
                                case '6':
                                    i=6;
                                    break;
                                case '7':
                                    i=7;
                                    break;
                                case '8':
                                    i=8;
                                    break;
                                case '9':
                                    i=9;
                                    break;
                            }
                            for(j=i;j<resta1+i;j++){
                                if(M[j-1][toupper(res[0])-65]=='O' || M[j+1][toupper(res[0])-65]=='O' || M[j][(toupper(res[0])-65)-1]=='O' || M[j][(toupper(res[0])-65)+1]=='O'){
                                    sel=-1;
                                }
                            }
                            if(sel!=-1){
                                for(j=i;j<resta2+i;j++){
                                    M[j][toupper(res[0])-65]='O';
                                }
                            }
                        }
                        if(sel!=-1){
                            printf("Barco colocado\n\n");
                            if(barcos_colocados!=4){
                                v[sel-1]=v[4-barcos_colocados];
                                v[4-barcos_colocados]=-1;
                                v=(int *)realloc(v,(4-barcos_colocados) * sizeof(int));
                                ordenar(v,4-barcos_colocados);
                                for(i=0;i<=4-barcos_colocados;i++){
                                    switch(v[i]){
                                        case 0:
                                            v_tamaño[i]=5;
                                            break;
                                        case 1:
                                            v_tamaño[i]=4;
                                            break;
                                        case 2:
                                            v_tamaño[i]=3;
                                            break;
                                        case 3:
                                            v_tamaño[i]=3;
                                            break;
                                        case 4:
                                            v_tamaño[i]=2;
                                            break;
                                    }
                                }
                            }
                            barcos_colocados++;
                        }else{
                            printf("Debe de haber al menos una casilla de distancia entre barco y barco\n\n");
                        }
                        
                    }else{
                        if(IA!=1){
                            if(resta1!=1 && resta2!=1){
                                printf("No se pueden colocar barcos en diagonal\n\n");
                            }else if((resta1==1 && resta2<v_tamaño[sel-1]) || (resta1<v_tamaño[sel-1] && resta2==1)){
                                printf("Este barco requiere mas casillas\n\n");
                            }else{
                                printf("Este barco requiere menos casillas\n\n");
                            }
                        }
                    }
                }else{
                    printf("Formato incorrecto\n\n");
                }
                if(IA!=1){
                    Sleep(500);
                }
            }while(sel==0);
        }
    }while(barcos_colocados!=5);
}

int atacar(char M[10][10], char MB[11][11], int barcos_hundidos){
    int i,aux,pos1,pos2;
    char res[3], auxchar;

    do{
        aux=0;
        printf("\nIntroduce la casilla que vas a atacar (Ejemplo: B6)\n");
        fflush(stdin);
        fgets(res,3,stdin);
        system("cls");

        if(toupper(res[1])=='A' || toupper(res[1])=='B' || toupper(res[1])=='C' || toupper(res[1])=='D' || toupper(res[1])=='E' || toupper(res[1])=='F' || toupper(res[1])=='G' || toupper(res[1])=='H' || toupper(res[1])=='I' || toupper(res[1])=='J'){
            auxchar=res[1];
            res[1]=res[0];
            res[0]=auxchar;
        }
        if((toupper(res[0])=='A' || toupper(res[0])=='B' || toupper(res[0])=='C' || toupper(res[0])=='D' || toupper(res[0])=='E' || toupper(res[0])=='F' || toupper(res[0])=='G' || toupper(res[0])=='H' || toupper(res[0])=='I' || toupper(res[0])=='J') && (res[1]=='0' || res[1]=='1' || res[1]=='2' || res[1]=='3' || res[1]=='4' || res[1]=='5' || res[1]=='6' || res[1]=='7' || res[1]=='8' || res[1]=='9')){
            pos1=res[1]-'0';
            pos2=toupper(res[0])-65;

            if(MB[pos1][pos2]==' '){
                for(i=0;i<3;i++){
                    printf(".");
                    Sleep(500);
                }
                system("cls");
                Sleep(1000);
                i=0;
                if(M[pos1][pos2]==' '){
                    printf("AGUA\n\n");
                    MB[pos1][pos2]='A';
                }else{
                    MB[pos1][pos2]='X';
                    if(M[pos1+1][pos2]==' ' && M[pos1-1][pos2]==' '){
                        while(M[pos1][pos2-i]=='X' || M[pos1][pos2-i]=='O'){
                            i++;
                        }
                        i--;
                        while(M[pos1][pos2-i]=='X' || M[pos1][pos2-i]=='O'){
                            if(M[pos1][pos2-i]=='O'){
                                aux=1;
                            }
                            i--;
                        }
                        if(aux==1){
                            i++;
                            while(M[pos1][pos2-i]=='X'){
                                MB[pos1][pos2-i]='H';
                                i++;
                            }
                        }
                    }else{
                        while(M[pos1-i][pos2]=='X' || M[pos1-i][pos2]=='O'){
                            i++;
                        }
                        i--;
                        while(M[pos1-i][pos2]=='X' || M[pos1-i][pos2]=='O'){
                            if(M[pos1-i][pos2]=='O'){
                                aux=1;
                            }
                            i--;
                        }
                        if(aux==1){
                            i++;
                            while(M[pos1-i][pos2]=='X'){
                                MB[pos1-i][pos2]='H';
                                i++;
                            }
                        }
                    }
                    if(aux==1){
                        printf("HUNDIDO !!!\n\n");
                        barcos_hundidos++;
                    }
                }
            }else{
                printf("Ya has atacado esa casilla\n\n");
                aux=2;
            }
        }else{
            printf("Formato incorrecto\n\n");
            aux=2;
        }
    }while(aux==2);

    return barcos_hundidos;
}

int atacarIA(char M[10][10],char MB[11][11],int barcos_hundidos,char pos_ant1[2],char pos_ant2[2]){
    int i,aux,pos1,pos2;

    do{
        aux=0;
        pos1=rand()%10;
        pos2=rand()%10;

        if(MB[pos1][pos2]==' '){
            if(M[pos1][pos2]==' '){
                MB[pos1][pos2]='A';
            }else{
                MB[pos1][pos2]='X';
                if(M[pos1+1][pos2]==' ' && M[pos1-1][pos2]==' '){
                    while(M[pos1][pos2-i]=='X' || M[pos1][pos2-i]=='O'){
                        i++;
                    }
                    i--;
                    while(M[pos1][pos2-i]=='X' || M[pos1][pos2-i]=='O'){
                        if(M[pos1][pos2-i]=='O'){
                            aux=1;
                        }
                        i--;
                    }
                    if(aux==1){
                        i++;
                        while(M[pos1][pos2-i]=='X'){
                            MB[pos1][pos2-i]='H';
                            i++;
                        }
                    }
                }else{
                    while(M[pos1-i][pos2]=='X' || M[pos1-i][pos2]=='O'){
                        i++;
                    }
                    i--;
                    while(M[pos1-i][pos2]=='X' || M[pos1-i][pos2]=='O'){
                        if(M[pos1-i][pos2]=='O'){
                            aux=1;
                        }
                        i--;
                    }
                    if(aux==1){
                        i++;
                        while(M[pos1-i][pos2]=='X'){
                            MB[pos1-i][pos2]='H';
                            i++;
                        }
                    }
                }
                if(aux==1){
                    barcos_hundidos++;
                }
            }
        }else{
            aux=2;
        }
    }while(aux==2);

    return barcos_hundidos;
}

//'O'=Barco colocado en ese lugar
//'X'=Barco tocado
//' '=Casilla libre
//'A'=Agua
//'H'=Barco totalmente hundido
