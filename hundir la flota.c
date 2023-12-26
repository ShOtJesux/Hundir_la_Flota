#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define VERDE 2
#define ROJO 4
#define BLANCO 7
#define AZUL 9
#define ROJO_ROJO 68
#define ROJO_BLANCO 71
#define AZUL_AZUL 153
#define AZUL_BLANCO 159
#define VERDE_ROJO 36 //164
#define VERDE_BLANCO 39 //167
#define VERDE_VERDE 34 //170

void color(int);
void jugarIA(int,int,int,int,char *,char *);
void print_matriz(char [11][11], int);
void ordenar(int *,int);
void colocar_barcos(char [11][11], int);
int atacar(char [11][11], char [11][11], char [11][11], char [11][11], int, int, int);
int atacarIA(char [11][11], char [11][11], char [11][11], int, int [2], int [2]);
int comprobar_casilla(char [11][11],char [11][11], int, int);
void color_casilla(char [11][11], int, int, int);
void gotoxy(int,int);
void ajustes(int *,int *,int *,char *,char *);

int main(){
    int AA=1,CT=0,PN=0;
    char res[3],res_sing,nombre1[70],nombre2[70];

    strcpy(nombre1,"Jugador 1");
    strcpy(nombre2,"Jugador 2");

    srand(time(NULL));

    system("cls");
    printf("Programa creado por:\n");
    printf("    - Twitter: @DurumSoloCarne_\n");
    printf("    - Discord: @durumsolocarne\n\n\n");
    Sleep(1000);

    do{
        printf("---------- HUNDIR LA FLOTA ----------\n\n");
        printf("Seleciona una opci%cn:\n",162);
        printf("    1. Jugar contra la IA\n");
        printf("    2. Jugar contra una persona (Local)\n");
        printf("    3. Configuraci%cn\n",162);
        printf("    4. Informaci%cn\n",162);
        printf("    5. Salir\n");

        fflush(stdin);
        fgets(res,3,stdin);
        if(res[1]=='\n'){
            res_sing=res[0];
        }else{
            res_sing='\0';
        }

        system("cls");

        switch(res_sing){
            case '1':
                strcpy(nombre2,"La IA");
                jugarIA(1,AA,CT,PN,nombre1,nombre2);
                break;
            case '2':
                jugarIA(0,AA,CT,PN,nombre1,nombre2);
                break;
            case '3':
                ajustes(&AA,&CT,&PN,nombre1,nombre2);
                break;
            case '4':

                break;
            case '5':
                printf("Programa creado por:\n");
                printf("    - Twitter: @DurumSoloCarne_\n");
                printf("    - Discord: @durumsolocarne\n\n");
                printf("Muchas gracias por jugar. :P\n\n");
                Sleep(3000);
                return 0;
            default:
                printf("Opci%cn incorrecta\n\n",162);
                Sleep(500);
                break;
        }
        res_sing='\0';

    }while(res_sing!='5');
}

void color(int k){
    HANDLE Consola=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Consola,k);
}

void ajustes(int *AA,int *CT,int *PN,char *nombre1,char *nombre2){
    int longitud;
    char res[3],res_sing,nombre_aux[70];

    do{
        printf("---------- CONFIGURACI%cN ----------\n\n",224);
        printf("Seleciona una opci%cn:\n",162);
        printf("    1. Modificar nombre de jugador\n");
        printf("    2. AYUDA ACU%cTICA  - ",181);
        if(*AA==0){
            color(ROJO);
            printf("Desactivado\n");
        }else{
            color(VERDE);
            printf("Activado\n");
        }
        color(BLANCO);
        printf("    3. CEGUERA TOTAL   - ");
        if(*CT==0){
            color(ROJO);
            printf("Desactivado\n");
        }else{
            color(VERDE);
            printf("Activado\n");
        }
        color(BLANCO);
        printf("    4. PISTA NUM%cRICA  - ",144);
        if(*PN==0){
            color(ROJO);
            printf("Desactivado\n");
        }else{
            color(VERDE);
            printf("Activado\n");
        }
        color(BLANCO);
        printf("    5. Salir de la configuraci%cn\n",162);

        fflush(stdin);
        fgets(res,3,stdin);

        if(res[1]=='\n'){
            res_sing=res[0];
        }else{
            res_sing='\0';
        }

        system("cls");

        switch(res_sing){
            case '1':
                do{
                    printf("Selecciona el jugador para cambiarle el nombre:\n");
                    printf("    1. %s\n",nombre1);
                    printf("    2. %s\n",nombre2);
                    printf("    3. Retroceder\n");

                    fflush(stdin);
                    fgets(res,3,stdin);
                    system("cls");
                    if(res[1]=='\n' && (res[0]=='1' || res[0]=='2')){
                        do{
                            printf("%cC%cmo te llamas, Jugador %c?: ",168,162,res[0]);
                            nombre_aux[0]='\0';
                            fflush(stdin);
                            fgets(nombre_aux,70,stdin);
                            longitud=strlen(nombre_aux);
                            nombre_aux[longitud-1]='\0';
                            system("cls");
                            if((res[0]=='1' && strcasecmp(nombre2,nombre_aux)!=0) || (res[0]=='2' && strcasecmp(nombre1,nombre_aux)!=0)){//Comprobar los nombres de los jugadores son iguales
                                if(res[0]=='1'){
                                    nombre1[0]='\0';
                                    strcpy(nombre1,nombre_aux);
                                }else{
                                    nombre2[0]='\0';
                                    strcpy(nombre2,nombre_aux);
                                }
                                printf("Cambio efectuado.");
                                Sleep(1000);
                                system("cls");
                            }else{
                                system("cls");
                                printf("Ambos jugadores no pueden tener el mismo nombre\n\n");
                                Sleep(500);
                            }
                        }while((res[0]=='1' && strcasecmp(nombre2,nombre_aux)==0) || (res[0]=='2' && strcasecmp(nombre1,nombre_aux)==0));
                    }else{
                        if(res[0]!='3'){
                            system("cls");
                            printf("Opci%cn incorrecta\n\n",162);
                            Sleep(500);
                        }
                    }
                }while(res[1]!='\n' || res[0]!='3');
                break;
            case '2':
                do{
                    printf("AYUDA ACU%cTICA - Al hundir un barco, se mostrar%c rodeado de agua autom%cticamente.\n\n",181,160,160);
                    if(*AA==0){
                        printf("%cActivar? S/N\n",168);
                    }else{
                        printf("%cDesactivar? S/N\n",168);
                    }
                    fflush(stdin);
                    fgets(res,3,stdin);
                    system("cls");
                    if(res[1]=='\n' && (res[0]=='S' || res[0]=='s' || res[0]=='N' || res[0]=='n')){
                        if(res[0]=='S' || res[0]=='s'){
                            if(*AA==0){
                                *AA=1;
                            }else{
                                *AA=0;
                            }
                        }
                    }else{
                        printf("Opci%cn incorrecta\n\n",162);
                        Sleep(500);
                    }
                }while(res[1]!='\n' || (res[0]!='S' && res[0]!='s' && res[0]!='N' && res[0]!='n'));
                break;
            case '3':
                do{
                    printf("CEGUERA TOTAL - No sabr%cs si el barco se ha hundido o sigue a flote.\n\n",160);
                    if(*CT==0){
                        printf("%cActivar? S/N\n",168);
                    }else{
                        printf("%cDesactivar? S/N\n",168);
                    }
                    fflush(stdin);
                    fgets(res,3,stdin);
                    system("cls");
                    if(res[1]=='\n' && (res[0]=='S' || res[0]=='s' || res[0]=='N' || res[0]=='n')){
                        if(res[0]=='S' || res[0]=='s'){
                            if(*CT==0){
                                *CT=1;
                            }else{
                                *CT=0;
                            }
                        }
                    }else{
                        printf("Opci%cn incorrecta\n\n",162);
                        Sleep(500);
                    }
                }while(res[1]!='\n' || (res[0]!='S' && res[0]!='s' && res[0]!='N' && res[0]!='n'));
                break;
            case '4':
                do{
                    printf("PISTA NUM%cRICA - Si tocas agua, se te informar%c a la distancia que est%c el barco m%cs cercano.\n\n",144,160,160,160);
                    if(*PN==0){
                        printf("%cActivar? S/N\n",168);
                    }else{
                        printf("%cDesactivar? S/N\n",168);
                    }
                    fflush(stdin);
                    fgets(res,3,stdin);
                    system("cls");
                    if(res[1]=='\n' && (res[0]=='S' || res[0]=='s' || res[0]=='N' || res[0]=='n')){
                        if(res[0]=='S' || res[0]=='s'){
                            if(*PN==0){
                                *PN=1;
                            }else{
                                *PN=0;
                            }
                        }
                    }else{
                        printf("Opci%cn incorrecta\n\n",162);
                        Sleep(500);
                    }
                }while(res[1]!='\n' || (res[0]!='S' && res[0]!='s' && res[0]!='N' && res[0]!='n'));
                break;
            case '5':
                return;
                break;
            default:
                printf("Opci%cn incorrecta\n\n",162);
                Sleep(500);
                break;
        }
    }while(res_sing!='5');
}

void jugarIA(int IA,int AA,int CT,int PN,char *nombre1,char *nombre2){
    int i,j,hundidos1,hundidos2,turno=1,pos_inic[2]={-1,-1},pos_rec[2]={-1,-1},aux=0;
    char J1[11][11], J1B[11][11], J2[11][11], J2B[11][11];

    for (i=0;i<11;i++){
        for(j=0;j<11;j++){
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
        printf("TURNO DE %s\n\n",nombre1);
        Sleep(800);
    }
    colocar_barcos(J1B,0);

    if(IA!=1){
        printf("TURNO DE %s\n\n",nombre2);
        Sleep(800);
    }
    colocar_barcos(J2B,IA);

    system("cls");

    printf("FASE 2: ");
    Sleep(800);
    printf("ATACA AL ENEMIGO\n\n");
    Sleep(1000);

    do{
        if(IA!=1 && turno==1){
            printf("TURNO DE %s\n\n",nombre1);
            Sleep(500);
        }
        if(IA!=1 && turno==2){
            printf("TURNO DE %s\n\n",nombre2);
            Sleep(500);
        }

        if(aux==0){
            print_matriz(J1,0);
            print_matriz(J1B,1);
            aux=1;
        }

        if(turno==1){
            hundidos1=atacar(J2,J2B,J1,J1B,hundidos1,IA,turno);
            turno++;
        }else{
            if(IA!=1){
                hundidos2=atacar(J1,J1B,J2,J2B,hundidos2,IA,turno);
            }else{
                hundidos2=atacarIA(J1,J1B,J2,hundidos2,pos_inic,pos_rec);
            }
            turno--;
        }

    }while(hundidos1!=5 && hundidos2!=5);

    system("cls");//////////////////////////

    if(hundidos1==5){
        printf("%c VICTORIA DE %s !\n\n",173,nombre1);
    }else{
        printf("%c VICTORIA DE %s !\n\n",173,nombre2);
    }
//escribir una tablita que sea: Nombre jugador arriba, abajo de eso "Barcos hundidos", y abajo de eso, el numero de barcos hundidos. separar ambas columnas con guiones
    printf("")
}

void print_matriz(char M[11][11], int selector){
    int i,j,x,y;

    if(selector!=0){
        x=80;
        y=1+selector;
        gotoxy(x,y);
        y++;
    }
    printf("     |     |     |     |     |     |     |     |     |     |     |\n");
    if(selector!=0){
        gotoxy(x,y);
        y++;
    }
    printf("     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |  I  |  J  |\n");
    if(selector!=0){
        gotoxy(x,y);
        y++;
    }
    printf("_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
    if(selector!=0){
        gotoxy(x,y);
        y++;
    }
    for(i=0;i<10;i++){
        printf("     |");
        for(j=0;j<10;j++){
            color_casilla(M,i,j,0);
            printf("     ");
            if(j!=9){
                color_casilla(M,i,j,1);
            }else{
                color(BLANCO);
            }
            printf("|");
        }
        color(BLANCO);
        printf("\n");
        if(selector!=0){
            gotoxy(x,y);
            y++;
        }
        printf("  %i  ",i);
        printf("|");
        for(j=0;j<10;j++){
            color_casilla(M,i,j,0);
            printf("  %c  ",toupper(M[i][j]));
            if(j!=9){
                color_casilla(M,i,j,1);
            }else{
                color(BLANCO);
            }
            printf("|");
        }
        color(BLANCO);
        printf("\n");
        if(selector!=0){
            gotoxy(x,y);
            y++;
        }
        printf("_____|");
        for(j=0;j<10;j++){
            color_casilla(M,i,j,2);
            printf("_____");
            if(j!=9){
                color_casilla(M,i,j,1);
            }else{
                color(BLANCO);
            }
            printf("|");
        }
        color(BLANCO);
        printf("\n");
        if(selector!=0){
            gotoxy(x,y);
            y++;
        }
    }
    color(BLANCO);
    printf("\n\n");
}

void gotoxy(int x, int y){
    HANDLE controlador=GetStdHandle(STD_OUTPUT_HANDLE);

    COORD coordenadas;
    coordenadas.X=x;
    coordenadas.Y=y;

    SetConsoleCursorPosition(controlador,coordenadas);
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
    int i, j,pos1,pos2, resta1, resta2, sel=0, *v, v_tamaño[5]={5,4,3,3,2}, barcos_colocados=0;
    char auxchar[3], res[7];

    v=(int *)malloc(5 * sizeof(int));

    for(i=0;i<5;i++){
        v[i]=i;
    }

    do{
        if(IA!=1){
            print_matriz(M,0);

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
            printf("Opc%cn incorrecta\n\n",162);
            sel=0;
            Sleep(500);
        }else{
            do{
                if(IA!=1){
                    printf("\nIntroduce los extremos de la ubicaci%cn de tu barco (Ejemplo A2-E2)\n",162);
                    fflush(stdin);
                    fgets(res,7,stdin);
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
                if(IA==1 || (res[5]=='\n' && res[2]=='-' && (toupper(res[0])=='A' || toupper(res[0])=='B' || toupper(res[0])=='C' || toupper(res[0])=='D' || toupper(res[0])=='E' || toupper(res[0])=='F' || toupper(res[0])=='G' || toupper(res[0])=='H' || toupper(res[0])=='I' || toupper(res[0])=='J') && (res[1]=='0' || res[1]=='1' || res[1]=='2' || res[1]=='3' || res[1]=='4' || res[1]=='5' || res[1]=='6' || res[1]=='7' || res[1]=='8' || res[1]=='9') && (toupper(res[3])=='A' || toupper(res[3])=='B' || toupper(res[3])=='C' || toupper(res[3])=='D' || toupper(res[3])=='E' || toupper(res[3])=='F' || toupper(res[3])=='G' || toupper(res[3])=='H' || toupper(res[3])=='I' || toupper(res[3])=='J') && (res[4]=='0' || res[4]=='1' || res[4]=='2' || res[4]=='3' || res[4]=='4' || res[4]=='5' || res[4]=='6' || res[4]=='7' || res[4]=='8' || res[4]=='9'))){
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
                            color(VERDE);
                            printf("Barco colocado\n\n");
                            color(BLANCO);
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
                                printf("Este barco requiere m%cs casillas\n\n",160);
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

int atacar(char M[11][11], char MB[11][11], char M_propia[11][11], char MB_propia[11][11], int barcos_hundidos, int IA, int turno){
    int i,pos1,pos2,comprobante=0;
    char res[4], auxchar;

    do{
        if(IA==0){///MEJORAR
            if(comprobante==3){
                if(turno==1){
                    print_matriz(M,0);
                    print_matriz(M_propia,1);
                }else{
                    print_matriz(M_propia,0);
                    print_matriz(M,1);
                }
            }else{
                if(turno==1){
                    print_matriz(M,0);
                    print_matriz(M_propia,3);
                }else{
                    print_matriz(M_propia,0);
                    print_matriz(M,3);
                }
            }
        }
        printf("Introduce la casilla que vas a atacar (Ejemplo: B6)\n");
        fflush(stdin);
        fgets(res,4,stdin);
        system("cls");

        if(toupper(res[1])=='A' || toupper(res[1])=='B' || toupper(res[1])=='C' || toupper(res[1])=='D' || toupper(res[1])=='E' || toupper(res[1])=='F' || toupper(res[1])=='G' || toupper(res[1])=='H' || toupper(res[1])=='I' || toupper(res[1])=='J'){
            auxchar=res[1];
            res[1]=res[0];
            res[0]=auxchar;
        }
        if(res[2]=='\n' && (toupper(res[0])=='A' || toupper(res[0])=='B' || toupper(res[0])=='C' || toupper(res[0])=='D' || toupper(res[0])=='E' || toupper(res[0])=='F' || toupper(res[0])=='G' || toupper(res[0])=='H' || toupper(res[0])=='I' || toupper(res[0])=='J') && (res[1]=='0' || res[1]=='1' || res[1]=='2' || res[1]=='3' || res[1]=='4' || res[1]=='5' || res[1]=='6' || res[1]=='7' || res[1]=='8' || res[1]=='9')){
            pos1=res[1]-'0';
            pos2=toupper(res[0])-65;

            comprobante=comprobar_casilla(M,MB,pos1,pos2);

            if(comprobante!=3){
                system("cls");
                for(i=0;i<3;i++){
                    printf(".");
                    Sleep(400);
                }
                Sleep(500);
            }
            system("cls");
            switch(comprobante){
                case 0:
                    color(AZUL);
                    printf("AGUA\n\n");
                    break;
                case 1:
                    color(ROJO);
                    printf("TOCADO\n\n");
                    break;
                case 2:
                    color(ROJO);
                    printf("HUNDIDO !!!\n\n");
                    barcos_hundidos++;
                    break;
                case 3:
                    printf("Ya has atacado esta casilla!\n\n");
                    break;
            }
            color(BLANCO);
        }else{
            printf("Formato incorrecto.\n\n");
            comprobante=3;
        }
        Sleep(500);
        if(comprobante==3){
            print_matriz(M,0);
            print_matriz(MB_propia,1);
        }
    }while(comprobante==3);

    return barcos_hundidos;
}

int atacarIA(char M[11][11],char MB[11][11], char M_usuario[11][11], int barcos_hundidos,int pos_inic[2],int pos_rec[2]){
    int i,pos1,pos2,comprobante,elec_random,resta1,resta2;

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
                            if((pos_rec[0]-1)!=-1 && M[pos_rec[0]-1][pos_rec[1]]==' '){
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
                            if((pos_rec[1]+1)!=10 && M[pos_rec[0]][pos_rec[1]+1]==' '){
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
                        if((pos_rec[1]+1)!=10 && M[pos_rec[0]][pos_rec[1]+1]==' '){
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

    }while(comprobante==3);

    //system("cls");

    print_matriz(M_usuario,0);
    print_matriz(MB,1);

    gotoxy(80,36);

    Sleep(300);
    for(i=0;i<3;i++){
        Sleep(300);
        printf(".");
    }
    Sleep(700);

    printf(" La IA atac%c la casilla ",162);

    print_matriz(MB,1);

    gotoxy(107,36);

    switch(comprobante){
    case 0:
        color(AZUL);
        break;
    case 1:
        color(ROJO);
        pos_rec[0]=pos1;
        pos_rec[1]=pos2;
        if(pos_inic[0]==-1){
            pos_inic[0]=pos1;
            pos_inic[1]=pos2;
        }
        break;
    case 2:
        color(ROJO);
        barcos_hundidos++;
        pos_inic[0]=-1;
        pos_inic[1]=-1;
        pos_rec[0]=-1;
        pos_rec[1]=-1;
        break;
    }

    printf("%c%i\n",pos2+65,pos1);
    color(BLANCO);

    Sleep(500);

    return barcos_hundidos;
}

int comprobar_casilla(char M[11][11],char MB[11][11], int pos1, int pos2){
    int i=0;
    if(M[pos1][pos2]==' '){
        if(MB[pos1][pos2]==' '){
            M[pos1][pos2]='A';
            return 0;
        }else{
            M[pos1][pos2]='x';
            MB[pos1][pos2]='X';
            if(MB[pos1+1][pos2]==' ' && (MB[pos1-1][pos2]==' ' || pos1-1==-1)){
                while(MB[pos1][pos2-i]=='O' || MB[pos1][pos2-i]=='X'){
                    i++;
                }
                i--;
                while(MB[pos1][pos2-i]=='O' || MB[pos1][pos2-i]=='X'){
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
                while(MB[pos1-i][pos2]=='O' || MB[pos1-i][pos2]=='X'){
                    i++;
                }
                i--;
                while(MB[pos1-i][pos2]=='O' || MB[pos1-i][pos2]=='X'){
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

void color_casilla(char M[11][11], int i, int j, int selector){
    switch(selector){
        case 0:
            switch(M[i][j]){
                case 'O':
                    color(VERDE_VERDE);
                    break;
                case 'X':
                    color(VERDE_ROJO);
                    break;
                case 'H':
                    color(ROJO_ROJO);
                    break;
                case ' ':
                    color(BLANCO);
                    break;
                case 'A':
                    color(AZUL_AZUL);
                    break;
                case 'x':
                    color(ROJO);
                    break;
            }
            break;
        case 1:
            if((M[i][j]=='O' || M[i][j]=='X' || M[i][j]=='H' || M[i][j]=='A') && (M[i][j+1]=='O' || M[i][j+1]=='X' || M[i][j+1]=='H' || M[i][j+1]=='A')){
                switch(M[i][j]){
                    case 'O' || 'X':
                        color(VERDE_BLANCO);
                        break;
                    case 'H':
                        color(ROJO_BLANCO);
                        break;
                    case 'A':
                        color(AZUL_BLANCO);
                        break;
                }
            }else{
                color(BLANCO);
            }
            if(((M[i][j]==' ' || M[i][j]=='A') && (M[i][j+1]!=' ' && M[i][j+1]!='A')) || ((M[i][j]!=' ' && M[i][j]!='A') && (M[i][j+1]==' ' || M[i][j+1]=='A'))){
                color(BLANCO);
            }
            break;
        case 2:
            switch(M[i][j]){
                case 'O':
                    color(VERDE_BLANCO);
                    break;
                case 'X':
                    color(VERDE_BLANCO);
                    break;
                case 'H':
                    color(ROJO_BLANCO);
                    break;
                case 'A':
                    color(AZUL_BLANCO);
                    break;
            }
            break;
    }

}


//MATRIZ DE BARCOS                      COLOR=FONDO_LETRA

//'O'=Barco colocado en ese lugar       COLOR=VERDE_VERDE
//'X'=Barco tocado                      COLOR=VERDE_ROJO
//'H'=Barco totalmente hundido          COLOR=ROJO_ROJO
//' '=Casilla libre                     COLOR=BLANCO


//MATRIZ DE ATACAR

//'A'=Agua                              COLOR=AZUL_AZUL
//'x'=Barco tocado                      COLOR=ROJO
//'H'=Barco totalmente hundido          COLOR=ROJO_ROJO
//' '=Casilla libre                     COLOR=BLANCO


//VARIANTES: PARA LA CONTINUIDAD DE BARCOS: ROJO_BLANCO, VERDE_BLANCO, AZUL_BLANCO


//MODOS DE JUEGO:

//AYUDA ACUATICA: Al hundir un barco, se mostrará rodeado de agua automaticamente.
//CEGUERA TOTAL: No sabrás si el barco se ha hundido o sigue a flote.
//PISTA NUMÉRICA: Si tocas agua, se te informará a la distancia que está el barco más cercano.
