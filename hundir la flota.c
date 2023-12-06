#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define BLANCO 7
#define AZUL_AZUL 153
#define AZUL_BLANCO 159

void color(int);
void jugarIA(int);
void print_matriz(char [11][11], int);
void ordenar(int *,int);
void colocar_barcos(char [11][11], int);
int atacar(char [10][10], char [11][11], int);
int atacarIA(char [10][10], char [11][11], int, int [2], int [2]);
int comprobar_casilla(char [10][10],char [11][11], int, int);

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
    int i,j,hundidos1,hundidos2,turno=1,pos_inic[2]={-1,-1},pos_rec[2]={-1,-1};
    char J1[10][10], J1B[11][11], J2[10][10], J2B[11][11];

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

        if(turno==1){
            hundidos1=atacar(J2,J2B,hundidos1);
            turno++;
        }else{
            if(IA!=1){
                hundidos2=atacar(J1,J1B,hundidos2);
            }else{
                hundidos2=atacarIA(J1,J1B,hundidos2,pos_inic,pos_rec);
            }
            turno--;
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
            printf("|");///////////////////////////
            if(M[i][j]=='.'){
                color(AZUL_AZUL);
            }
            printf("     ");///// 
            color(BLANCO);
        }
        printf("|\n");
        printf("  %i  ",i);
        printf("|");
        for(j=0;j<10;j++){
            if(M[i][j]=='x'){
                color();
            }
            if(M[i][j]=='X'){
                color();
            }
            if(M[i][j]=='A'){
                color(AZUL_AZUL);
            }
            printf("  %c  ",M[i][j]);/////
            color(BLANCO);
            printf("|");/////////////////////////
        }
        printf("\n");
        printf("_____");
        for(j=0;j<10;j++){
            color(BLANCO);
            printf("|");/////////////////////////////////
            if(M[i][j]=='.'){
                color(AZUL_BLANCO);
            }
            printf("_____");/////
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
    int i,pos1,pos2,comprobante;
    char res[3], auxchar;

    do{
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

            comprobante=comprobar_casilla(M,MB,pos1,pos2);

            system("cls");
            for(i=0;i<3;i++){
                printf(".");
                Sleep(500);
            }
            Sleep(300);
            system("cls");
            switch(comprobante){
                case 0:
                    printf("AGUA");
                    break;
                case 1:
                    printf("TOCADO");
                    break;
                case 2:
                    printf("HUNDIDO !!!");
                    barcos_hundidos++;
                    break;
                case 3:
                    printf("Ya has atacado esta casilla!");
                    break;
            }
        }else{
            printf("Formato incorrecto.");
            comprobante=3;
        }
    }while(comprobante==3);

    return barcos_hundidos;
}

int atacarIA(char M[10][10],char MB[11][11],int barcos_hundidos,int pos_inic[2],int pos_rec[2]){
    int pos1,pos2,comprobante,elec_random,resta1,resta2;

    do{
        if(pos_inic[0]==-1){
            pos1=rand()%10;
            pos2=rand()%10;
        }else{
            if(pos_inic[0]==pos_rec[0] && pos_inic[1]==pos_rec[1]){
                do{
                    elec_random=rand()%4;
                    switch(elec_random){
                        case 0:
                            if((pos_rec[0]-1)!=-1 && M[pos_rec[0]-1][pos_rec[1]]==' '){//M[pos_rec[0]-1][pos_rec[1]]!='X' && M[pos_rec[0]-1][pos_rec[1]]!='H' && M[pos_rec[0]-1][pos_rec[1]]!='A'
                                pos1=pos_rec[0]-1;
                                pos2=pos_rec[1];
                            }else{
                                elec_random=4;
                            }
                            break;
                        case 1:
                            if((pos_rec[0]+1)!=10 && M[pos_rec[0]+1][pos_rec[1]]==' '){
                                pos1=pos_rec[0]+1;
                                pos2=pos_rec[1];
                            }else{
                                elec_random=4;
                            }
                            break;
                        case 2:
                            if((pos_rec[1]-1)!=-1 && M[pos_rec[0]][pos_rec[1]-1]==' '){
                                pos2=pos_rec[1]-1;
                                pos1=pos_rec[0];
                            }else{
                                elec_random=4;
                            }
                            break;
                        case 3:
                            if((pos_rec[1]+1)!=10 && M[pos_rec[0]][pos_rec[1]-1]==' '){
                                pos2=pos_rec[1]+1;
                                pos1=pos_rec[0];
                            }else{
                                elec_random=4;
                            }
                            break;
                    }
                }while(elec_random==4);
            }else{//Esto para cuando la pos_rec sea distinta de pos_inic
                resta1=pos_rec[0]-pos_inic[0];
                resta2=pos_rec[1]-pos_inic[1];
                if(resta1!=0){
                    if(resta1<0){//La casilla reciente está a la izq de la inicial
                        if((pos_rec[0]-1)!=-1 && M[pos_rec[0]-1][pos_rec[1]]==' '){
                            pos1=pos_rec[0]-1;
                            pos2=pos_rec[1];
                        }else{
                            pos1=pos_inic[0]+1;
                            pos2=pos_inic[1];
                        }
                    }else{//La casilla reciente está a la derecha de la inicial
                        if((pos_rec[0]+1)!=10 && M[pos_rec[0]+1][pos_rec[1]]==' '){
                            pos1=pos_rec[0]+1;
                            pos2=pos_rec[1];
                        }else{
                            pos1=pos_inic[0]-1;
                            pos2=pos_inic[1];
                        }
                    }
                }else{
                    if(resta2<0){
                        if((pos_rec[1]-1)!=-1 && M[pos_rec[0]][pos_rec[1]-1]==' '){
                            pos2=pos_rec[1]-1;
                            pos1=pos_rec[0];
                        }else{
                            pos2=pos_inic[1]+1;
                            pos1=pos_inic[0];
                        }
                    }else{
                        if((pos_rec[1]+1)!=10 && M[pos_rec[0]][pos_rec[1]-1]==' '){
                            pos2=pos_rec[1]+1;
                            pos1=pos_rec[0];
                        }else{
                            pos2=pos_inic[1]-1;
                            pos1=pos_inic[0];
                        }
                    }
                }
            }
        }

        comprobante=comprobar_casilla(M,MB,pos1,pos2);

        if(comprobante==1){
            pos_rec[0]=pos1;
            pos_rec[1]=pos2;
            if(pos_inic[0]==-1){
                pos_inic[0]=pos1;
                pos_inic[1]=pos2;
            }
        }

        if(comprobante==2){
            barcos_hundidos++;
            pos_inic[0]=-1;
            pos_inic[1]=-1;
            pos_rec[0]=-1;
            pos_rec[1]=-1;
        }
        
    }while(comprobante==3);

    return barcos_hundidos;
}

int comprobar_casilla(char M[10][10],char MB[11][11], int pos1, int pos2){
    int i;

    if(M[pos1][pos2]==' '){
        if(MB[pos1][pos2]==' '){
            M[pos1][pos2]='A';
            return 0;
        }else{
            M[pos1][pos2]='x';
            if(MB[pos1+1][pos2]==' ' && MB[pos1-1][pos2]==' '){
                while(MB[pos1][pos2-i]=='O'){
                    i++;
                }
                i--;
                while(MB[pos1][pos2-i]=='O'){
                    if(M[pos1][pos2-i]==' '){
                        return 1;
                    }
                    i--;
                }
                i++;
                while(M[pos1][pos2-i]=='x'){
                    M[pos1][pos2-i]='H';
                    MB[pos1][pos2-i]='H';
                    i++;
                }
            }else{
                while(MB[pos1-i][pos2]=='O'){
                    i++;
                }
                i--;
                while(MB[pos1-i][pos2]=='O'){
                    if(M[pos1-i][pos2]==' '){
                        return 1;
                    }
                    i--;
                }
                i++;
                while(M[pos1-i][pos2]=='x'){
                    M[pos1-i][pos2]='H';
                    MB[pos1-i][pos2]='H';
                    i++;
                }
            }
            return 2;
        }
    }else{
        return 3;
    }
}


//MATRIZ DE BARCOS                      COLOR=FONDO_LETRA

//'O'=Barco colocado en ese lugar       COLOR=VERDE_VERDE
//'X'=Barco tocado                      COLOR=VERDE_ROJO
//'H'=Barco totalmente hundido          COLOR=ROJO_ROJO
//' '=Casilla libre                     COLOR=BLANCO


//MATRIZ DE ATACAR

//'A'=Agua                              COLOR=AZUL_AZUL
//'x'=Barco tocado                      COLOR=BLANCO_ROJO

//'H'=Barco totalmente hundido          COLOR=ROJO_ROJO
//' '=Casilla libre                     COLOR=BLANCO


//VARIANTES: PARA LA CONTINUIDAD DE BARCOS: ROJO_BLANCO, VERDE_BLANCO, AZUL_BLANCO