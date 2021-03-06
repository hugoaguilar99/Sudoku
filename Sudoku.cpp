#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

void gotoxy(int,int);//Funcion declarada despues del main

void Change(int color){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void Ocultarcursor () {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 100;
    cci.bVisible =  FALSE;

    SetConsoleCursorInfo(hCon,&cci);
}
void renglon (int request,int nively) {
    int temp=0;

    if (request==1){ //             IMPRIME EL TOP DEL TABLERO
        cout <<"        "<<(char)218;
        for (int nylon=1;nylon<28;nylon++){
            cout<<(char)196; temp++;
            if ((temp%3)==0&&nylon!=27){
                cout<<(char)194;
            }
        }
        cout<<(char)191<<endl;
    }

    if (request==2){ //               IMPRIME ELINTERMEDIO DEL TABLERO
        cout <<"        "<<(char)195;
        for (int nylon=1;nylon<28;nylon++){
            cout<<(char)196; temp++;
            if ((temp%3)==0&&nylon!=27){
                cout<<(char)197;
            }
        }
        cout<<(char)180;
        Change(253);
        if (nively==1) {//              TODOS LOS "NIVELY" SON PARA ELMENU A LA DERECHA nivel del renglon
            cout << "   "<<(char)201;
            for (int iterate=0;iterate<20;iterate++)
                cout << (char)205;
            cout <<(char)187;
        }
        if (nively==2) {
            cout << "   "<<(char)200;
            for (int iterate=0;iterate<20;iterate++)
                cout << (char)205;
            cout <<(char)188;
        }
        if (nively==3) {
                cout << "     (C) CARGAR la partida.                         ";
        }
        if (nively==4) {
            cout << "   "<<(char)201;
            for (int iterate=0;iterate<63;iterate++)
                cout << (char)205;
            cout <<(char)187;
        }
        if (nively==5) {
            cout << "   "<<(char)200;
            for (int iterate=0;iterate<63;iterate++)
                cout << (char)205;
            cout <<(char)188;
        }
        cout <<endl;
        Change(240);
    }

    if (request==3){//                  IMPRIME LO DE ABAJO DEL TABLERO
        cout <<"        "<<(char)192;
        for (int nylon=1;nylon<28;nylon++){
            cout<<(char)196; temp++;
            if ((temp%3)==0&&nylon!=27){
                cout<<(char)193;
            }
        }
        cout<<(char)217<<endl;
    }

}

void celda (int num, int point, int cc, int colorFONT){
    /* COLOR FONT
    0 = Nada
    1 = Letra VERDE
    2 = Letra ROJA
    3 =
    4
    5
    */
    if (colorFONT==1)
        Change(242);
    if (colorFONT==2)
        Change(244);
    if (colorFONT==3)
        Change(248);
    if (colorFONT==4)
        Change(248);

    if (point==0) {     //          | 6 |
        if (num == 0) {
            cout << "  ";
        } else {
            cout << " "<< num;
        }
        if (cc==1) { //             | 6[|
            cout << (char)176;
        } if (cc!=1) {
            cout << " ";
        }
    } else if (point==1) {//        |> <|
        //Change(240);
        if (num == 0) {
            cout << (char)175<<" ";
        } else {
            cout << (char)175<< num;
        }
        if (cc==1) { //             |> [|
            cout << (char)176;
        } else {
            cout << (char)174;
        }
    }
    Change(240);
}
bool EncontrarCeldaVacia(int n[9][9], int &xSol, int &ySol){
    for(xSol = 0; xSol < 9; xSol++)
        for(ySol = 0; ySol < 9; ySol++)
            if(n[xSol][ySol] == 0)
                return true;
    return false;
}

bool ComprobarFila(int n[9][9], int xSol, int numSol) {

    for(int ySol = 0; ySol < 9; ySol++)
        if(n[xSol][ySol] == numSol)
            return true;
    return false;
}

bool ComprobarColumna(int n[9][9], int ySol, int numSol) {

    for(int xSol = 0; xSol < 9; xSol++)
        if(n[xSol][ySol] == numSol)
            return true;
    return false;
}

bool Comprobar3x3(int n[9][9], int boxStartX, int boxStartY, int numSol){

    for(int xSol = 0; xSol < 3; xSol++)
        for(int ySol = 0; ySol < 3; ySol++)
            if(n[xSol+boxStartX][ySol+boxStartY] == numSol)
                return true;
    return false;
}

bool Legal(int n[9][9], int xSol, int ySol, int numSol){

    return !ComprobarFila(n, xSol, numSol) &&
           !ComprobarColumna(n, ySol, numSol) &&
           !Comprobar3x3(n, xSol - xSol%3 , ySol - ySol%3, numSol);
}

bool SolveSudoku(int n[9][9],int imprimir){				// Funcion que recibe la partida en la posicion actual y la devuelve e imprime resuelta

    int xSol, ySol; 															//

    if(!EncontrarCeldaVacia(n, xSol, ySol))
       return true;
    for(int numSol = 1; numSol <= 9; numSol++){
        if(Legal(n, xSol, ySol, numSol))
        {
            n[xSol][ySol] = numSol;

            if (imprimir==1) {
                gotoxy((xSol*4)+9,(ySol*2)+7);
                celda(numSol,0,0,1);
            }

            if(SolveSudoku(n,imprimir))
                return true;

            n[xSol][ySol] = 0;
        }
    }
    return false;
}
int antes_de_resolver(int n[9][9], int e[9][9]) {
    int fatal1[9][9] =
    {
        {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}
    };
    int fatal2[9][9] =
    {
        {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}
    };
    int DeamSon=0;

    // COMPARACION DE    F I L A S    Y    C O L U M N A S
    for (int x=0; x<9;x++){ //  COMPARATIVA INICIAL
        for (int y=0;y<9;y++){
            for (int xt=0; xt<9;xt++){ //  COMPARATIVA MOMENTANEA
                for (int yt=0;yt<9;yt++){
                    if (x==xt||y==yt)
                        if (n[x][y]==n[xt][yt])
                            if (n[x][y]!=0)
                                fatal1[x][y]++;
                }
            }
        }
    }
        int floe=0, flae=0;
    // COMPARACION DE   C U A D R O S    D E    9 X 9
    for (int lineo = 0; lineo <3;lineo++){
            floe = lineo*3;

        for (int loneo = 0; loneo <3;loneo++){
                flae = loneo*3;

            for (int x=0+floe; x<3+floe;x++){ //  1 2 3
                for (int y=0+flae;y<3+flae;y++){

                    for (int xt=0+floe; xt<3+floe;xt++){
                        for (int yt=0+flae;yt<3+flae;yt++){

                            if (n[x][y]==n[xt][yt])
                                if (n[x][y]!=0)
                                    fatal2[x][y]++;
                        }
                    }
                }
            }
        }
    }
        //      IMPRIMIR ERRORES
        for (int x=0; x<9;x++){
            for (int y=0;y<9;y++){
                for (int xt=0; xt<9;xt++){
                    for (int yt=0;yt<9;yt++){
                        if (fatal1[x][y]==2||fatal2[x][y]==2) {
                            DeamSon=1;
                            gotoxy((x*4)+9,(y*2)+7);
                            if (e[x][y]!=1)
                                celda(n[x][y],0,e[x][y],3);
                        }
                        if (fatal1[x][y]>2||fatal2[x][y]>2) {
                            DeamSon=1;
                            gotoxy((x*4)+9,(y*2)+7);
                            if (e[x][y]!=1)
                                celda(n[x][y],0,e[x][y],3);
                        }
                    }
                }
            }
        }
    return DeamSon;
}

void sudoku (int & zeldax, int & zelday, int & nc, int & cn) {
    int u=220,d=223,m=219;

            if (zelday==0&&zeldax==0) {         //         PRIMER / n RENGLON
Change(249);printf("                            %c%c%c%c%c%c%c   %c%c    %c%c   %c%c%c%c%c%c       %c%c%c%c%c%c   %c%c    %c%c%c   %c%c    %c%c\n",u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u);
Change(251);printf("                           %c%c%c        %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c  %c%c%c%c    %c%c    %c%c\n",m,m,d,m,m,m,m,m,m,m,m,m,m,m,m,m,m,u,m,m,d,m,m,m,m);
Change(243);printf("                           %c%c%c%c%c%c%c    %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c%c%c%c%c      %c%c    %c%c\n",d,m,m,u,u,u,u,m,m,m,m,m,m,m,m,m,m,m,m,m,m,u,m,m,d,m,m,m,m);
Change(241);printf("                                %c%c%c   %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c %c%c%c%c     %c%c    %c%c\n",d,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,d,m,m,u,m,m,m,m);
Change(240);printf("                           %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c   %c%c%c%c   %c%c%c%c%c%c%c%c\n\n",u,u,u,u,u,m,m,d,m,m,u,u,u,u,d,d,m,m,u,u,u,u,d,d,m,m,u,u,u,u,d,d,m,m,d,m,m,u,m,m,u,u,u,u,d,d);

                renglon(1,0);
            } else if (zeldax==0) {
                renglon(2,zelday);
            }
            if (zeldax==0)
                cout << "        ";
            cout <<(char)179;   //          CELDA INDIVIDUAL
                celda(nc,0,cn,0);
            //                                          MANEJO DE VALORES POR EJE X

            zeldax++;

                                                    //  MANEJO DE VALORES POR EJE y
            if(zeldax == 9){
                cout <<(char)179<<"\t";
                Change(253);
                switch (zelday) {
                    case 1: cout << (char)186 << " TECLAS DE COMANDOS "<< (char)186;
                        break;
                    case 2: cout << "  (S) GUARDAR la partida.  (R) REINICIAR TABLERO.";
                        break;
                    case 3: cout << "  (ESC) SALIR del tablero.";
                        break; //                 =================================================================
                    case 4: Change(253);cout << (char)186 << " Mensajes:                                                     "<< (char)186;Change(240);
                        break;
                }
                Change(240);
                cout << endl;
                zeldax=0;
                zelday++;
            }
            if(zelday==9) //                              ULTIMO RENGLON
                renglon(3,0);

}
//funcion hecha por terminos de eficiencia de excritura de un menor numero de lineas de codigo al evitarnos escribir lo mismo en dos case del switch
void SudokuMaker(bool choice){
    system("cls");
    system("color F0");
    ifstream Lista;//declaracion para apertura de archivo de la plantilla preestablecida
    ofstream myfile; // declaracion para guardar en un archivo la plantilla resuelta
    int keys, px=0, py=0;
    int celdax=0, celday=0;
    int operandi=0, advertencia, error_sudoku;
    int gotx=9, goty=7, solving=0;
    int n[9][9] =
    {
        {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}
    };
    int e[9][9]=
    {
        {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}
    };
    int r[9][9];

    if(choice== true){
        Lista.open("plantilla1.txt");
        if(!Lista.is_open()){
          //esto es para imprimir un titulo llamativo
            int u=220,d=223,m=219;
            Change(249);printf("                            %c%c%c%c%c%c%c   %c%c    %c%c   %c%c%c%c%c%c       %c%c%c%c%c%c   %c%c    %c%c%c   %c%c    %c%c\n",u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u);
            Change(251);printf("                           %c%c%c        %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c  %c%c%c%c    %c%c    %c%c\n",m,m,d,m,m,m,m,m,m,m,m,m,m,m,m,m,m,u,m,m,d,m,m,m,m);
            Change(243);printf("                           %c%c%c%c%c%c%c    %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c%c%c%c%c      %c%c    %c%c\n",d,m,m,u,u,u,u,m,m,m,m,m,m,m,m,m,m,m,m,m,m,u,m,m,d,m,m,m,m);
            Change(241);printf("                                %c%c%c   %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c %c%c%c%c     %c%c    %c%c\n",d,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,d,m,m,u,m,m,m,m);
            Change(240);printf("                           %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c   %c%c%c%c   %c%c%c%c%c%c%c%c\n\n",u,u,u,u,u,m,m,d,m,m,u,u,u,u,d,d,m,m,u,u,u,u,d,d,m,m,u,u,u,u,d,d,m,m,d,m,m,u,m,m,u,u,u,u,d,d);


            cout << "\n Error: El archivo 'plantilla1.txt' no esta en la ubicaci"<<(char)162<<"n de este programa.\n"<< endl;
            getch();
            exit(1);
        }
        for (int y=0;y<9;y++) { //   ASIGNACION DE LISTA A LA VARIABLE N
            for (int x=0;x<9;x++){
                Lista>>n[x][y];
                    e[x][y] = 0;
                if (n[x][y]!=0)
                    e[x][y] = 1;
            }
        }
        Lista.close();
        myfile.open("plantilla3.txt");
        SolveSudoku(n,0);
        for (int y=0;y<9;y++) { //   GUARDA EL SUDOKU RESUELTO
            for (int x=0;x<9;x++){
                myfile<<n[x][y]<<"\n";
            }
        }
        myfile.close();
        for (int y=0;y<9;y++) { //            DESRESUELVE A N y ASIGNA A R
            for (int x=0;x<9;x++){
                r[x][y]=n[x][y];
                if (e[x][y]==0)
                    n[x][y]=0;
            }
        }
    }

    for (int y=0;y<9;y++) { //               IMPRIME EL SUDOKU
        for (int x=0;x<9;x++){
            sudoku(celdax,celday,n[x][y],e[x][y]);
        }
    }

    gotoxy(60,15);
        Change(242);cout << "Tablero Inicializado.";Change(240);

    celdax=0; celday=0;

    while (0==0) { //   ESTE WHILE ES EL MANEJO DE LA TABLA DEL SUDOKU Y SUS VALORES

        Ocultarcursor(); // EN CASO DE JUGAR A "PANTALLA COMPLETA"
        gotoxy(gotx,goty); // ESTO "LIMPIA LA CELDA QUE ESTABA APUNTANDO"
        if (e[px][py]==0)
            celda(n[px][py],1,e[px][py],0);
        if (e[px][py]==1)
            celda(n[px][py],1,e[px][py],0);
        if (e[px][py]==2)
            celda(n[px][py],0,e[px][py],1);

        // SECCION DE MENSAJES DE ADVERTENCIA
            gotoxy(59,15);
            Change(241);
            if (advertencia==0&&solving==0)
                cout << " Ningun mensaje hasta ahora.                        ";
            if (advertencia==0&&solving==1)
                cout << " Para ingresar otro sudoku, rein"<<(char)161<<"cie el tablero.    ";
            Change(47);
            if (advertencia==1)
                cout << " TABLERO CARGADO EXITOSAMENTE!                      ";
            if (advertencia==2)
                cout << " TABLERO GUARDADO EXITOSAMENTE!                     ";
            if (advertencia==3)
                cout << " SE REINICIO EL TABLERO EXITOSAMENTE!               ";
            Change(79);
            if (advertencia==4)
            cout << " ERROR: No se encontr"<<(char)162<<" el archivo de guardado!      ";
            if (advertencia==7)
            cout << " ERROR: Hay datos erroneos en el tablero      ";
            Change(241);
            if (advertencia==5)
                cout << " LISTO! Abajo tienes las estadisticas.              ";
            if (advertencia==6)
                cout << " LISTO! El Sudoku fue resuelto exitosamente!        ";
            Change(240);

        gotoxy(gotx+1,goty); //ESTO APUNTA A LA SELECCIÓN DE LA CELDA ACTUAL

        keys=_getch();
        advertencia=0;

        if (keys==LEFT) { //======//

            gotoxy(gotx,goty);
            if (e[px][py]!=2)
                celda(n[px][py],0,e[px][py],0);
            if (e[px][py]==2)
                celda(n[px][py],0,e[px][py],1);
            px--;
            if (px==-1)
                px=0;
            gotx=(px*4)+9;

        }
        if (keys==RIGHT) { //======//

            gotoxy(gotx,goty);
            if (e[px][py]!=2)
                celda(n[px][py],0,e[px][py],0);
            if (e[px][py]==2)
                celda(n[px][py],0,e[px][py],1);
            px++;
            if (px==9)
                px=8;
            gotx=(px*4)+9;

        }
        if (keys==UP) { //======//

            gotoxy(gotx,goty);
            if (e[px][py]!=2)
                celda(n[px][py],0,e[px][py],0);
            if (e[px][py]==2)
                celda(n[px][py],0,e[px][py],1);
            py--;
            if (py==-1)
                py=0;
            goty=(py*2)+7;

        }
        if (keys==DOWN) { //======//

            gotoxy(gotx,goty);
            if (e[px][py]!=2)
                celda(n[px][py],0,e[px][py],0);
            if (e[px][py]==2)
                celda(n[px][py],0,e[px][py],1);
            py++;
            if (py==9)
                py=8;
            goty=(py*2)+7;

        }               //======//
        if (e[px][py]==0) {         //  ACCESO A PODER MODIFICAR VALORES
            switch (keys) {
                case 49:
                    n[px][py] =    1   ;
                    cout << "1";
                    break;
                case 50:
                    n[px][py] =    2   ;
                    cout << "2";
                    break;
                case 51:
                    n[px][py] =    3   ;
                    cout << "3";
                    break;
                case 52:
                    n[px][py] =    4   ;
                    cout << "4";
                    break;
                case 53:
                    n[px][py] =    5   ;
                    cout << "5";
                    break;
                case 54:
                    n[px][py] =    6   ;
                    cout << "6";
                    break;
                case 55:
                    n[px][py] =    7   ;
                    cout << "7";
                    break;
                case 56:
                    n[px][py] =    8   ;
                    cout << "8";
                    break;
                case 57:
                    n[px][py] =    9   ;
                    cout << "9";
                    break;
            }
        }
        if (keys==8||keys==48) { // "BORRAR UN VALOR EN LA TABLA"
            if (e[px][py]==0) {
                n[px][py]=0;
                cout <<" ";
            }
        }
        if (keys==27) { //  ESTE LUGAR TIENE COMO FUNCION SALIR DE LA TABLA
            system("cls");
            break;
        }
        if (keys==115&&choice==TRUE) { //  ESTE LUGAR GUARDA GUARDA EL JUEGO
            myfile.open("plantilla2.txt");
            if (myfile.is_open())
            {
                for (int y=0;y<9;y++) { //   ASIGNACION DE LISTA A LA VARIABLE N
                    for (int x=0;x<9;x++){
                        myfile<<n[x][y]<<"\n";
                    }
                }
                myfile.close();
                advertencia=2;
                system("cls");
                celdax=0; celday=0;
                for (int y=0;y<9;y++) { //               IMPRIME EL SUDOKU
                    for (int x=0;x<9;x++){
                        sudoku(celdax,celday,n[x][y],e[x][y]);
                    }
                }
            } else {
            cout << "Error, no se encuentra el archivo 'plantilla2.txt' para el guardado";
            }
        }
        if (keys==99) { //          CARGA EL DOCUMENTO PLANTILLA 2
            celdax=0; celday=0;
            Lista.open("plantilla2.txt");
            if (!Lista.is_open()) {
                advertencia=4;
            } else {
                system("cls");
                for (int y=0;y<9;y++) { //
                    for (int x=0;x<9;x++){
                        Lista>>n[x][y];
                    }
                }
                Lista.close();
                advertencia=1;
                for (int y=0;y<9;y++) { //               IMPRIME EL SUDOKU
                    for (int x=0;x<9;x++){
                        sudoku(celdax,celday,n[x][y],e[x][y]);
                    }
                }
            }
        }
        if (keys==114) {        //              RESETEA EL SUDOKU COMPLETAMENTE
            if (choice==1){
                celdax=0; celday=0;
                system("cls");
                for (int y=0;y<9;y++) { //  INICIALIZACION DE CONDICION A LA VARIABLE E
                    for (int x=0;x<9;x++){
                            e[x][y]=0;
                    }
                }
                Lista.open("plantilla1.txt");
                for (int y=0;y<9;y++) { //   ASIGNACION DE LISTA A LA VARIABLE N
                    for (int x=0;x<9;x++){
                        Lista>>n[x][y];
                        if (n[x][y]!=0)
                            e[x][y] = 1;
                    }
                }
                Lista.close();
                advertencia=3;
                for (int y=0;y<9;y++) { //               IMPRIME EL SUDOKU
                    for (int x=0;x<9;x++){
                        sudoku(celdax,celday,n[x][y],e[x][y]);
                    }
                }
                advertencia=3;
            } else {
            celdax=0; celday=0;
            system("cls");
            for (int y=0;y<9;y++) { //               IMPRIME EL SUDOKU
                    for (int x=0;x<9;x++){
                        n[x][y]=0;
                        e[x][y]=0;
                        sudoku(celdax,celday,n[x][y],e[x][y]);
                    }
                }
        }
        }
        if (keys==109) {//                                RESOLVER EL SUDOKU
            advertencia=6; solving=1;
            gotoxy(59,15); cout << " Comprovando Sudoku...                               ";
            error_sudoku = antes_de_resolver(n,e);
            if (error_sudoku==0) {
                gotoxy(59,15); cout << "Resolviendo Sudoku...                               ";
                SolveSudoku(n,1);
                for (int x=0; x<9;x++){
                    for (int y=0;y<9;y++){
                        for (int xt=0; xt<9;xt++){
                            if (n[x][y]==0) {
                                error_sudoku=1;
                            }
                        }
                    }
                }
                if (error_sudoku==0) {
                    for (int y=0;y<9;y++) { //
                        for (int x=0;x<9;x++){
                            e[x][y]=2;
                            gotoxy((x*4)+9,(y*2)+7);
                            celda(n[x][y],0,e[x][y],1);
                        }
                    }
                } else {  //               EN CASO DE NO RESOLVERSE EL SUDOKU
                    for (int y=0;y<9;y++) { //
                        for (int x=0;x<9;x++){
                            gotoxy((x*4)+9,(y*2)+7);
                            if (e[x][y]==0){
                                celda(n[x][y],0,e[x][y],2);
                            } else {
                                celda(n[x][y],0,e[x][y],0);
                            }
                        }
                    }
                }
            } if (error_sudoku==1) {
                advertencia=7;
                solving=0;
            }
        }
        //system("cls");
        //cout<< keys;
    }
}


int main()
{
    system("color F0");
    int u=220,d=223,m=219, n[9][9];
	int menu_item=0, x=7;//menu_item es para la seleccion que haga el usuario en
	bool running = true,choice;//running boleano que maneja el while principal, choice depende de la opcion que de el usuario
  	gotoxy(18,2); cout<< "UNIVERSIDAD AUTONOMA DEL ESTADO DE CHIHUAHUA"<<endl;
    gotoxy(18,3);cout<< "           FACULTAD DE INGENIERIA           "<<endl<<endl;
    gotoxy(18,4); cout <<"     CONCEPTOS AVANZADOS DE PROGRAMACION     "<<endl;
    gotoxy(18,5); cout << "         Dr. Raimundo Cornejo Garcia          "<<endl;
    gotoxy(18,7); cout << "           PROYECTO FINAL SUDOKU"<<endl;
    gotoxy(18,9);cout<< "                INTEGRANTES:                "<<endl;
    gotoxy(18,10);cout<< "     Victor Hugo Aguilar Parra    320663"<<endl;
    gotoxy(18,11);cout<< "     Angel Eidu Macias Saenz      320670"<<endl;
    gotoxy(18,12);cout<< "     Sebastian Terrazas Sandoval  320808"<<endl;
    gotoxy(18,15); cout << "        para continuar presione enter"<<endl;
    getch();
    system("cls");//funcion para hacer una limpia de pantalla

    Change(249);printf("                            %c%c%c%c%c%c%c   %c%c    %c%c   %c%c%c%c%c%c       %c%c%c%c%c%c   %c%c    %c%c%c   %c%c    %c%c\n",u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u);
    Change(251);printf("                           %c%c%c        %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c  %c%c%c%c    %c%c    %c%c\n",m,m,d,m,m,m,m,m,m,m,m,m,m,m,m,m,m,u,m,m,d,m,m,m,m);
    Change(243);printf("                           %c%c%c%c%c%c%c    %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c%c%c%c%c      %c%c    %c%c\n",d,m,m,u,u,u,u,m,m,m,m,m,m,m,m,m,m,m,m,m,m,u,m,m,d,m,m,m,m);
    Change(241);printf("                                %c%c%c   %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c %c%c%c%c     %c%c    %c%c\n",d,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,d,m,m,u,m,m,m,m);
    Change(240);printf("                           %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c   %c%c%c%c   %c%c%c%c%c%c%c%c\n\n",u,u,u,u,u,m,m,d,m,m,u,u,u,u,d,d,m,m,u,u,u,u,d,d,m,m,u,u,u,u,d,d,m,m,d,m,m,u,m,m,u,u,u,u,d,d);
		//imprime el menu
		gotoxy(18,7);  cout << "->";//el apuntador del menu
    gotoxy(20,7);  cout << "1) Jugar con una plantilla prestablecida";
    gotoxy(20,8);  cout << "2) Poner tu propia plantilla";
    gotoxy(20,9);  cout << "3) Cerrar programa";

	while(running)
	{
		menu_item =0;
    x=7;
		system("pause>nul"); // the >nul bit causes it the print no message
		//GetAsyncKeyState detecta si la tecla esta presionada
		if(GetAsyncKeyState(VK_DOWN) && x != 9) //down button pressed
			{
				gotoxy(18,x); cout << "  ";//limpia el espacio anterior
				x++; // le aumenta a la variable x
				gotoxy(18,x); cout << "->";//imprime el puntero de nuevo
				menu_item++;
				continue;

			}

		if(GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
			{
				gotoxy(18,x); cout << "  ";
				x--;
				gotoxy(18,x); cout << "->";
				menu_item--;
				continue;
			}

		if(GetAsyncKeyState(VK_RETURN)){ // Enter key pressed
            system("cls");
			switch(menu_item){

				case 0:
                    choice=true;
				    system("cls");
				    SudokuMaker(choice);

                Change(249);printf("                            %c%c%c%c%c%c%c   %c%c    %c%c   %c%c%c%c%c%c       %c%c%c%c%c%c   %c%c    %c%c%c   %c%c    %c%c\n",u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u);
                Change(251);printf("                           %c%c%c        %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c  %c%c%c%c    %c%c    %c%c\n",m,m,d,m,m,m,m,m,m,m,m,m,m,m,m,m,m,u,m,m,d,m,m,m,m);
                Change(243);printf("                           %c%c%c%c%c%c%c    %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c%c%c%c%c      %c%c    %c%c\n",d,m,m,u,u,u,u,m,m,m,m,m,m,m,m,m,m,m,m,m,m,u,m,m,d,m,m,m,m);
                Change(241);printf("                                %c%c%c   %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c %c%c%c%c     %c%c    %c%c\n",d,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,d,m,m,u,m,m,m,m);
                Change(240);printf("                           %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c   %c%c%c%c   %c%c%c%c%c%c%c%c\n\n",u,u,u,u,u,m,m,d,m,m,u,u,u,u,d,d,m,m,u,u,u,u,d,d,m,m,u,u,u,u,d,d,m,m,d,m,m,u,m,m,u,u,u,u,d,d);

                gotoxy(18,7); cout << "->";
                gotoxy(20,7);  cout << "1) Jugar con una plantilla prestablecida";
                gotoxy(20,8);  cout << "2) Poner tu propia plantilla";
                gotoxy(20,9);  cout << "3) Cerrar programa";

                break;

            case 1  :
                choice=false;
                system("cls");
                SudokuMaker(choice);

                Change(249);printf("                            %c%c%c%c%c%c%c   %c%c    %c%c   %c%c%c%c%c%c       %c%c%c%c%c%c   %c%c    %c%c%c   %c%c    %c%c\n",u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u);
                Change(251);printf("                           %c%c%c        %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c  %c%c%c%c    %c%c    %c%c\n",m,m,d,m,m,m,m,m,m,m,m,m,m,m,m,m,m,u,m,m,d,m,m,m,m);
                Change(243);printf("                           %c%c%c%c%c%c%c    %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c%c%c%c%c      %c%c    %c%c\n",d,m,m,u,u,u,u,m,m,m,m,m,m,m,m,m,m,m,m,m,m,u,m,m,d,m,m,m,m);
                Change(241);printf("                                %c%c%c   %c%c    %c%c   %c%c    %c%c   %c%c    %c%c   %c%c %c%c%c%c     %c%c    %c%c\n",d,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,d,m,m,u,m,m,m,m);
                Change(240);printf("                           %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c   %c%c%c%c   %c%c%c%c%c%c%c%c\n\n",u,u,u,u,u,m,m,d,m,m,u,u,u,u,d,d,m,m,u,u,u,u,d,d,m,m,u,u,u,u,d,d,m,m,d,m,m,u,m,m,u,u,u,u,d,d);

                gotoxy(18,7); cout << "->";
                gotoxy(20,7);  cout << "1) Jugar con una plantilla prestablecida";
                gotoxy(20,8);  cout << "2) Poner tu propia plantilla";
                gotoxy(20,9);  cout << "3) Cerrar programa";
                break;

            case 2 :
                system("cls");
                gotoxy(18,5); cout << "gracias por jugar " << endl;
                running = false;
                break;

            }
        }
	}
	getch();
}


void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition);
}
