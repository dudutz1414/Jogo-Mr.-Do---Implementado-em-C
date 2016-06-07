//Nomes: Eduardo Brito e Tatiane Stivelman
#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>
#include<windows.h>
#include<time.h>
#define NUMLIN 23
#define NUMCOL 61

typedef struct
{
    int score;
    int ghosts;
} GameState;


typedef struct
{
    char name[40];
    int score;
} Highscore;



typedef struct
{

    char ultima_dir;

} TIRO;

int menu();//prototipo da funcao, para arruamar probelmas relacionado a ordem das funcoes

void gotoxy1 (int x, int y) //Serve para posicionar o cursor na tela
{
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void salvascore (Highscore high[], GameState est) //pega a pontuacao do jogo em est e atribui ao jogo pela variavel high
{
    int numentradas = 0, k, i;
    FILE *hs;
    Highscore temp;

    fflush(stdin); //limpando lixos de memoria
    printf("\nEntre a nova entrada (nome): ");
    gets(high[numentradas].name);
    high[0].score = est.score;
    hs = fopen("highscores.bin","rb");
    if(hs != NULL) //testa se o arquivo abriu direito
    {
        //printf("Erro ao abrir o arquivo, arquivo sendo criado");




        do
        {
            numentradas ++;
            fread(&high[numentradas], sizeof(high[numentradas]),1,hs);

        }
        while(!feof(hs));
        fclose(hs);


        for (i=0; i<6; i++) //para que fique ordenado essa passagem de comparação precisa ser feita uma quantidade equivalente ao numero de pontuacoes
        {
            for (k=0; k<6; k++)
            {
                if(high[k].score<high[k+1].score) //verifica de dois qual pe maior e faz a troca de posição caso o primeiro for maior que o segundo
                {
                    temp = high[k]; //move para variavel temporaria o score
                    high[k] =high[k+1]; //faz a troca dos scores
                    high[k+1] = temp; //finaliza a troca
                }
            }
        }

    }

    hs = fopen("highscores.bin","wb"); //abre para escrever os novos 5 melhores scores
    rewind(hs); //garantindo que o arquivo inteiro seja lido
    for(numentradas = 0; numentradas < 6; numentradas++)
        if((fwrite(&high[numentradas], sizeof(high[numentradas]), 1, hs)) != 1)
            printf("----Erro--- nao deu para salvar o highscore -----\n");
    fclose(hs);
}

/*responsavel pelo movimento dos fantasmas uma vez que eles já sairam do ninho*/
int movefantasmadepoisdenascer (char mat[NUMLIN][NUMCOL], int pos_do[2], GameState *est, Highscore high[])
{
    int l,c,ln, cn , lg, cg,direcao_if,flag_direcao=0,uc=0,ul=0, ultimadiri;
    FILE *salvafase;
    for(l=0; l<NUMLIN; l++)
    {
        for(c=0; c<NUMCOL; c++)
        {

{




            direcao_if = rand() % 4;



            if(mat[l][c]=='i' && c!=uc && l!=ul) //atribui o lugar da matriz a posicao do fantasma
            {
                lg = l;
                cg = c;

                if (pos_do[0] == lg && pos_do[1] == cg) //identifica se a posicao do fantasma é a mesma do mr. do
                {

                    salvafase = fopen("qualfase.txt","w"); //Após ganhar o jogo se salva o valor 0 novamente para que se possa jogar de novo
                    {
                        fprintf(salvafase,"%d",0); //Coloca o valor zero no arquivo
                    }
                    fclose(salvafase);

                    system("cls");
                    gotoxy1(0,0);
                    printf("Mr. Do abotoou o paleto! \n");
                    salvascore (high,*est);
                    menu();


                }



                switch (direcao_if) //define a proxima direcao do fantasma
                {
                case 0:
                    if(mat[lg][cg+1] != 'p' && mat[lg][cg+1] != 'n' && mat[lg][cg+1] != 'i')//direita
                    {
                        mat[lg][cg+1] = 'i';
                        mat[lg][cg]='v';
                        uc = c+1; //registra ultima coluna e linha que foram ocupadas
                        ul = l;
                        ultimadiri = 0;

                    }
                    break;
                case 1:
                    if(mat[lg-1][cg]!= 'p' && mat[lg-1][cg]!= 'n' && mat[lg-1][cg]!= 'i')//cima
                    {
                        mat[lg-1][cg] = 'i';
                        mat[lg][cg]='v';
                        uc = c;
                        ul = l-1;
                        ultimadiri = 1;
                    }
                    break;
                case 2:
                    if(mat[lg][cg-1]!= 'p' && mat[lg][cg-1]!= 'n' && mat[lg][cg-1]!= 'i' )//esquerda
                    {
                        mat[lg][cg-1] = 'i';
                        mat[lg][cg]='v';

                        uc = c-1;
                        ul = l;
                        ultimadiri = 2;
                    }
                    break;
                case 3:
                    if(mat[lg+1][cg] != 'p' && mat[lg+1][cg] != 'n' && mat[lg+1][cg] != 'i' )//baixo
                    {
                        mat[lg+1][cg] = 'i';
                        mat[lg][cg]='v';

                        uc = c;
                        ul = l+1;

                        ultimadiri = 3;
                    }
                    break;
                }


                switch(ultimadiri)
                {
                case 0:
                    direcao_if = (rand() % 4);
                    if(direcao_if == 2)
                        direcao_if = 0;
                    break;
                case 1:
                    direcao_if = (rand() % 4);
                    if(direcao_if == 3)
                        direcao_if = 0;
                    break;
                case 2:
                    direcao_if = (rand() % 4);

                    break;
                case 3:
                    direcao_if = (rand() % 4);
                    if(direcao_if == 1)
                        direcao_if = 0;

                    break;
                }


            }


        }
    }
}
}


/*nascimento do fantasma a partir do ninho*/

void fantasma(char mat[NUMLIN][NUMCOL], int pos_do[2], GameState *est)
{
    int l,c,ln, cn , lg, cg,direcao_if,flag_direcao=0, ultima_dir_i;

    for(l=0; l<NUMLIN; l++)
    {
        for(c=0; c<NUMCOL; c++)
        {


            if(mat[l][c]=='n' && (*est).ghosts<10) //ninho; contador da quantidade de fantasmas
            {
                ln = l; //f vai nascer no ln e cn e no ln e cn somente
                cn = c;
                //  mat[ln][cn]='i';


                direcao_if = rand() % 4;

                switch (direcao_if)
                {
                case 0:
                    if(mat[ln][cn+1] == 'v')//direita
                    {
                        mat[ln][cn+1] = 'i';
                        mat[ln][cn]='n';
                        (*est).ghosts = (*est).ghosts+1;

                        ultima_dir_i = 4;
                    }
                    break;
                case 1:
                    if(mat[ln-1][cn] == 'v')//cima
                    {
                        mat[ln-1][cn] = 'i';
                        mat[ln][cn]='n';
                        (*est).ghosts = (*est).ghosts+1;

                        ultima_dir_i = 5;
                    }
                    break;
                case 2:
                    if(mat[ln][cn-1] == 'v')//esquerda
                    {
                        mat[ln][cn-1] = 'i';
                        mat[ln][cn]='n';
                        (*est).ghosts = (*est).ghosts+1;

                        ultima_dir_i = 6;
                    }
                    break;
                case 3:
                    if(mat[ln+1][cn] == 'v') //baixo
                    {
                        mat[ln+1][cn] = 'i';
                        mat[ln][cn]='n';
                        (*est).ghosts = (*est).ghosts+1;

                        ultima_dir_i = 7;
                    }
                    break;

                }
                //  switch(ultima_dir_i)
                //{

                //}


            }


        }
    }
}
/* identifica lugar de onde o tiro sai e o seu respectivo trajeto*/
int dispara_tiro(int ultima,char mat[NUMLIN][NUMCOL],int pos_do[], GameState est, Highscore high[], TIRO shot)
{
    int c=0,l=0,retorno;
    char dir;
    c = pos_do[1];
    l = pos_do[0];
    time_t segundos_2,segundos_novo_2;
    if(ultima == 72) //verifica a ultima direção andada para dar o tiro nessa direção
    {
        if(mat[l - 1][c] != 'p')
        {
            l--;
            segundos_2 =  GetTickCount();
            while(mat[l][c] == 'v') //enquanto tiver vazio o tiro anda até colidir com algo
            {
                segundos_novo_2 =  GetTickCount();
                mat[l][c] = 't';

                if(mat[l+1][c]!='d')
                    mat[l+1][c] = 'v';
                if(mat[l+1][c]=='i')
                {
                    mat[l+1][c] = 'v';

                }
                l--;
                gotoxy1 (0,0);
                imprime_matriz(mat,pos_do,high,&est);
                if((segundos_novo_2 - segundos_2)>200)
                {
                    segundos_2 = segundos_novo_2;
                    segundos_novo_2 =  GetTickCount();
                    movefantasmadepoisdenascer(mat,pos_do,&est,high); //função que analisa a matriz e faz os fantasmas se moverem
                }
                if(kbhit()) //esse teste é feito para que ele só peça a tecla que foi clicada, caso algo alguma tecla seja pressionada, se não o jogo
                {
                    dir = toupper(getch()); //ficaria parado enquanto nada fosse pressionado
                    gotoxy1(63,15);
                    puts("              ");
                    gotoxy1(63,16);
                    puts("            ");
                }
                if(dir!=0 && dir!=32) //como cada vez que ele move o Mr.Do ele coloca a direção em zero (para evitar que escolha uma direção e ele continue sempre nela só se vai para a função de mover se não está zerado a direção
                    retorno = move_do(mat,pos_do,&dir,high,&est,&shot); // chama a função de mover o Mr.Do e retorna -1 caso o movimento é inválido
                if(dir!=27)
                    dir=0;
                if(retorno == -1) //caso deu erro no movimento, é retornado da função move_do o valor -1, indicando que o movimento não é possível
                {
                    gotoxy1(63,15);
                    puts("Movimento nao");
                    gotoxy1(63,16);
                    puts("eh possivel");
                }
            }
            if (mat[l][c] == 'i') //se colidir com o fantasma ele some
            {

                mat[l][c] = 'v';
                mat[l+1][c] = 'v';
                return 10; //retorna 10, isso para que a função que chama souber que tem que somar 10 a pontuação
            }



            l++;
            mat[l][c] = 'v';
        }



    }

 //mesma lógica aplicada nas outras direções
    if(ultima == 80) //verifica a ultima direção andada para dar o tiro nessa direção
    {
        if(mat[l + 1][c] != 'p')
        {
            l++;
            segundos_2 =  GetTickCount();
            while(mat[l][c] == 'v')
            {
                segundos_novo_2 =  GetTickCount();
                mat[l][c] = 't';

                if(mat[l-1][c]!='d')
                    mat[l-1][c] = 'v';
                if(mat[l-1][c]=='i')
                {
                    mat[l-1][c] = 'v';

                }
                l++;
                gotoxy1 (0,0);
                imprime_matriz(mat,pos_do,high,&est);
                if((segundos_novo_2 - segundos_2)>200)
                {
                    segundos_2 = segundos_novo_2;
                    segundos_novo_2 =  GetTickCount();
                    movefantasmadepoisdenascer(mat,pos_do,&est,high); //função que analisa a matriz e faz os fantasmas se moverem
                }
                if(kbhit()) //esse teste é feito para que ele só peça a tecla que foi clicada, caso algo alguma tecla seja pressionada, se não o jogo
                {
                    dir = toupper(getch()); //ficaria parado enquanto nada fosse pressionado
                    gotoxy1(63,15);
                    puts("              ");
                    gotoxy1(63,16);
                    puts("            ");
                }
                if(dir!=0 && dir!=32) //como cada vez que ele move o Mr.Do ele coloca a direção em zero (para evitar que escolha uma direção e ele continue sempre nela só se vai para a função de mover se não está zerado a direção
                    retorno = move_do(mat,pos_do,&dir,high,&est,&shot); // chama a função de mover o Mr.Do e retorna -1 caso o movimento é inválido
                if(dir!=27)
                    dir=0;
                if(retorno == -1) //caso deu erro no movimento, é retornado da função move_do o valor -1, indicando que o movimento não é possível
                {
                    gotoxy1(63,15);
                    puts("Movimento nao");
                    gotoxy1(63,16);
                    puts("eh possivel");
                }
            }
            if (mat[l][c] == 'i')
            {

                mat[l][c] = 'v';
                mat[l-1][c] = 'v';
                return 10;
            }



            l--;
            mat[l][c] = 'v';

        }


    }



    if(ultima == 77) //verifica a ultima direção andada para dar o tiro nessa direção
    {
        if(mat[l][c + 1] != 'p')
        {
            c++;
            segundos_2 =  GetTickCount();
            while(mat[l][c] == 'v')
            {
                segundos_novo_2 =  GetTickCount();
                mat[l][c] = 't';

                if(mat[l][c-1]!='d')
                    mat[l][c-1] = 'v';
                if(mat[l][c-1]=='i')
                {
                    mat[l][c-1] = 'v';

                }
                c++;
                gotoxy1 (0,0);
                imprime_matriz(mat,pos_do,high,&est);
                if((segundos_novo_2 - segundos_2)>200)
                {
                    segundos_2 = segundos_novo_2;
                    segundos_novo_2 =  GetTickCount();
                    movefantasmadepoisdenascer(mat,pos_do,&est,high); //função que analisa a matriz e faz os fantasmas se moverem
                }
                if(kbhit()) //esse teste é feito para que ele só peça a tecla que foi clicada, caso algo alguma tecla seja pressionada, se não o jogo
                {
                    dir = toupper(getch()); //ficaria parado enquanto nada fosse pressionado
                    gotoxy1(63,15);
                    puts("              ");
                    gotoxy1(63,16);
                    puts("            ");
                }
                if(dir!=0 && dir!=32) //como cada vez que ele move o Mr.Do ele coloca a direção em zero (para evitar que escolha uma direção e ele continue sempre nela só se vai para a função de mover se não está zerado a direção
                    retorno = move_do(mat,pos_do,&dir,high,&est,&shot); // chama a função de mover o Mr.Do e retorna -1 caso o movimento é inválido
                if(dir!=27)
                    dir=0;
                if(retorno == -1) //caso deu erro no movimento, é retornado da função move_do o valor -1, indicando que o movimento não é possível
                {
                    gotoxy1(63,15);
                    puts("Movimento nao");
                    gotoxy1(63,16);
                    puts("eh possivel");
                }
            }
            if (mat[l][c] == 'i')
            {

                mat[l][c] = 'v';
                mat[l][c-1] = 'v';
                return 10;
            }



            c--;
            mat[l][c] = 'v';
        }



    }


    if(ultima == 75) //verifica a ultima direção andada para dar o tiro nessa direção
    {
        if(mat[l][c - 1] != 'p')
        {
            c--;
            segundos_2 =  GetTickCount();
            while(mat[l][c] == 'v')
            {
                segundos_novo_2 =  GetTickCount();
                mat[l][c] = 't';

                if(mat[l][c+1]!='d')
                    mat[l][c+1] = 'v';
                if(mat[l][c+1]=='i')
                {
                    mat[l][c+1] = 'v';

                }
                c--;
                gotoxy1 (0,0);
                imprime_matriz(mat,pos_do,high,&est);
                if((segundos_novo_2 - segundos_2)>200)
                {
                    segundos_2 = segundos_novo_2;
                    segundos_novo_2 =  GetTickCount();
                    movefantasmadepoisdenascer(mat,pos_do,&est,high); //função que analisa a matriz e faz os fantasmas se moverem
                }
                if(kbhit()) //esse teste é feito para que ele só peça a tecla que foi clicada, caso algo alguma tecla seja pressionada, se não o jogo
                {
                    dir = toupper(getch()); //ficaria parado enquanto nada fosse pressionado
                    gotoxy1(63,15);
                    puts("              ");
                    gotoxy1(63,16);
                    puts("            ");
                }
                if(dir!=0 && dir!=32) //como cada vez que ele move o Mr.Do ele coloca a direção em zero (para evitar que escolha uma direção e ele continue sempre nela só se vai para a função de mover se não está zerado a direção
                    retorno = move_do(mat,pos_do,&dir,high,&est,&shot); // chama a função de mover o Mr.Do e retorna -1 caso o movimento é inválido
                if(dir!=27)
                    dir=0;
                if(retorno == -1) //caso deu erro no movimento, é retornado da função move_do o valor -1, indicando que o movimento não é possível
                {
                    gotoxy1(63,15);
                    puts("Movimento nao");
                    gotoxy1(63,16);
                    puts("eh possivel");
                }
            }
            if (mat[l][c] == 'i')
            {

                mat[l][c] = 'v';
                mat[l][c+1] = 'v';
                return 10;
            }



            c++;
            mat[l][c] = 'v';




        }


    }



}


//funcao responsavel pleo movimento do mr do e atribuindo os cenarios para algumas situacoes
int move_do(char mat[NUMLIN][NUMCOL], int pos_do[2], char *pont_dir,  Highscore high[] , GameState *est , TIRO *shot)
{
    int retorna = 0, i, acertou = 0;
    FILE *salvafase;
    if(*pont_dir != 32) //salva a última direcao para definir a direcao do tiro
        (*shot).ultima_dir = (*pont_dir) ;

    switch(*pont_dir)
    {
    case 72:
        if( mat[pos_do[0] - 1 ][pos_do[1]] == 'i')
        {
            salvafase = fopen("qualfase.txt","w"); //Após perder o jogo se salva o valor 0 novamente para que se possa jogar de novo
            {
                fprintf(salvafase,"%d",0); //Coloca o valor zero no arquivo
            }
            fclose(salvafase);

            system("cls");
            gotoxy1(0,0);
            printf("Mr. Do abotoou o paleto! \n");
            salvascore (high,*est);
            return -2; //retorna -2 pois Mr. Do morreu
        }
        if( mat[pos_do[0] - 1 ][pos_do[1]] == 'f')
        {
            (*est).score = (*est).score + 50; //Caso colida com fruta, rece 50 pontos
        }
        if(pos_do[0]==0 ||  mat[pos_do[0] - 1 ][pos_do[1]] == 'n' )
        {
            retorna = -1; //Retorna -1 avisando que não pode se mover nessa direção
        }
        else
        {
            mat[pos_do[0]][pos_do[1]] = 'v';
            pos_do[0]--; //linha decrementa, fazendo ele subir
            mat[pos_do[0]][pos_do[1]] = 'd';
            retorna = 1;
        }
        break;
//Mesma lógica é aplicada a todas as direções
    case 80:
        if( mat[pos_do[0] + 1 ][pos_do[1]] == 'i')
        {
            salvafase = fopen("qualfase.txt","w"); //Após perder o jogo se salva o valor 0 novamente para que se possa jogar de novo
            {
                fprintf(salvafase,"%d",0); //Coloca o valor zero no arquivo
            }
            fclose(salvafase);

            system("cls");
            gotoxy1(0,0);
            printf("Mr. Do abotoou o paleto! \n");
            salvascore (high,*est);
            return -2;
        }
        if( mat[pos_do[0] + 1 ][pos_do[1]] == 'f')
        {
            (*est).score = (*est).score + 50;
        }
        if(pos_do[0]==NUMLIN-1  ||  mat[pos_do[0] + 1 ][pos_do[1]] == 'n')
        {
            retorna = -1;
        }
        else
        {
            mat[pos_do[0]][pos_do[1]] = 'v';
            pos_do[0]++; //linha incrementa, fazendo ele descer
            mat[pos_do[0]][pos_do[1]] = 'd';
            retorna = 1;
        }
        break;

    case 77:
        if( mat[pos_do[0] ][pos_do[1] + 1] == 'i')
        {
            salvafase = fopen("qualfase.txt","w"); //Após perder o jogo se salva o valor 0 novamente para que se possa jogar de novo
            {
                fprintf(salvafase,"%d",0); //Coloca o valor zero no arquivo
            }
            fclose(salvafase);

            system("cls");
            gotoxy1(0,0);
            printf("Mr. Do abotoou o paleto! \n");
            salvascore (high,*est);
            return -2;
        }
        if( mat[pos_do[0]][pos_do[1] + 1] == 'f')
        {
            (*est).score = (*est).score + 50;
        }
        if(pos_do[1]==NUMCOL-2 ||  mat[pos_do[0] ][pos_do[1] + 1] == 'n')
        {
            retorna = -1;
        }
        else
        {
            mat[pos_do[0]][pos_do[1]] = 'v';
            pos_do[1]++; //coluna decrementa, fazendo ele ir para a direita
            mat[pos_do[0]][pos_do[1]] = 'd';
            retorna = 1;
        }
        break;

    case 75:
        if( mat[pos_do[0]  ][pos_do[1] - 1] == 'i')
        {
            salvafase = fopen("qualfase.txt","w"); //Após ganhar o jogo se salva o valor 0 novamente para que se possa jogar de novo
            {
                fprintf(salvafase,"%d",0); //Coloca o valor zero no arquivo
            }
            fclose(salvafase);

            system("cls");
            gotoxy1(0,0);
            printf("Mr. Do abotoou o paleto! \n");
            salvascore (high,*est);
            return -2;
        }
        if( mat[pos_do[0]][pos_do[1] - 1] == 'f')
        {
            (*est).score = (*est).score + 50;
        }
        if(pos_do[1]==0 ||  mat[pos_do[0] ][pos_do[1] - 1] == 'n')
        {
            retorna = -1;
        }
        else
        {
            mat[pos_do[0]][pos_do[1]] = 'v';
            pos_do[1]--; //coluna decrementa, fazendo ele ir para esquerda
            mat[pos_do[0]][pos_do[1]] = 'd';
            retorna = 1;
        }
        break;

    case 32:

        acertou = dispara_tiro((*shot).ultima_dir,mat,pos_do, *est, high, *shot);
        if(acertou == 10) //retorno da flag funcao dispara_tiro; conta pontos quando tiro acerta fantasma
        {
            acertou = 0; //zerando a flag
            (*est).score = (*est).score + 10;
        }
        break;






    }







    return retorna;
}

int imprime_matriz(char mat[NUMLIN][NUMCOL],int pos_do[], Highscore high[], GameState *est) //faz a varredura na matriz, printando o mapa atualizado
{
    int l=0,c, i,j, k = 0, conta_fruta=0, conta_fantasma=0, fase=0;
    FILE *cenario;
    FILE *salvafase;

    //Nessa função ela varre toda a matriz 'mat' e printa na tela o respectivo caracter correspondente ao caracter da matriz
    for(l=0; l<NUMLIN; l++)
    {
        for(c=0; c<NUMCOL; c++)
        {
            if(mat[l][c]=='p') //Caso for p, printa o caracter equivalente a parede
            {
                textcolor(GREEN);
                printf( "%c", 176);

            }
            else if(mat[l][c]=='i') //Caso for i, printa o caracter equivalente ao fantasma
            {
                conta_fantasma++; //É incrementado o numero de fantasmas, para sempre se ter a contagem deles, pois caso chegue a zero, significa que se passou de fase/ganhou
                textcolor(LIGHTBLUE);
                printf( "%c", 153);
            }
            else if(mat[l][c]=='f') // Caso f, coloca o caracter correspondente a fruta
            {
                conta_fruta++; //É incrementado o número de frutas, para sempre se ter a contagem deles, pois caso chegue a zero, significa que se passou de fase/ganhou
                textcolor(LIGHTGREEN);
                printf( "%c", 229);
            }
            else if(mat[l][c]=='d') //Caso d, colocao caracter equivalente ao Mr Do
            {
                pos_do[0] = l; //obtem a posição do Mr.Do, para se salvar no estado por exemplo, para quando continuar o jogo ele está na posição correta
                pos_do[1] = c;
                textcolor(LIGHTMAGENTA);
                printf( "%c", 227);
            }
            else if(mat[l][c]=='v')//Caso v, colocao caracter equivalente ao vazio
            {
                textcolor(BLACK);
                printf( "%c", 32);
            }
            else if(mat[l][c]=='n') //Caso n, colocao caracter equivalente ao ninho onde nascerá os fantasmas
            {
                textcolor(BROWN);
                printf( "%c", 206);
            }
            else if(mat[l][c]=='t') //caso t, printa o tiro dispadaro pelo Mr.Do
            {
                textcolor(YELLOW);
                printf( "%c", 250);
            }

        }
        printf("\n");


    }

    if(conta_fruta==0) //Caso não tenha mais frutas o jogador passa de fase ou ganha o jogo
    {
        salvafase = fopen("qualfase.txt","r"); //esse arquivo serve para controlar se o jogador está na primeira ou segunda fase
        if(salvafase!=NULL) //caso não tenha aberto ele será criado
        {
            fscanf(salvafase,"%d",&fase); //lê o que possui no arquivo e coloca em 'fase'
        }
        fclose(salvafase);

        if(fase==1) //se a fase for 1, significa que o Mr.Do já passou a primeira fase e então se acabou as frutas novamente ele ganhou o jogo
        {

            salvafase = fopen("qualfase.txt","w"); //Após ganhar o jogo se salva o valor 0 novamente para que se possa jogar de novo
            {
                fprintf(salvafase,"%d",0); //Coloca o valor zero no arquivo
            }
            fclose(salvafase);
            system("cls");
            gotoxy1(0,0);
            printf("Voce ganhou!!! \n"); //mensagem avisando da vitoria
            salvascore (high,*est); //Chama função que se coloca o nome e caso seja um highscore aparecerá na opção
            return 1;
        }

        //Caso a fase não for 1, vai então ter passado de fase e vai salvar 1 no arquivo para que a proxima vez ele ganhe o jogo
        salvafase = fopen("qualfase.txt","w");
        {
            fprintf(salvafase,"%d",1);
        }
        fclose(salvafase);

//Trecho que carrega o segundo cenário, colocando ele na matriz
        (*est).ghosts = 0;
        cenario = fopen("fase2.txt","r");

        for(i=0; i<NUMLIN; i++)
        {
            for(j=0; j<NUMCOL; j++)
            {

                fscanf(cenario,"%c",&mat[i][j]);
            }
        }
        for(i=0; i<NUMLIN; i++)
        {
            for(j=0; j<NUMCOL; j++)
            {

                if(mat[i][j]=='d') //Caso d, colocao caracter equivalente ao Mr Do
                {
                    pos_do[0] = i; //obtem a posição do Mr.Do, para se salvar no estado por exemplo, para quando continuar o jogo ele está na posição correta
                    pos_do[1] = j;

                }
            }
        }

        fclose(cenario);

    }




//Exatamente a mesma lógica se aplica caso não tiver mais fantasmas
    if(conta_fantasma==0 && (*est).ghosts != 0)
    {
        salvafase = fopen("qualfase.txt","r");
        if(salvafase!=NULL)
        {
            fscanf(salvafase,"%d",&fase);
        }
        fclose(salvafase);

        if(fase==1)
        {

            salvafase = fopen("qualfase.txt","w");
            {
                fprintf(salvafase,"%d",0);
            }
            fclose(salvafase);
            system("cls");
            gotoxy1(0,0);
            printf("Voce ganhou!!!! \n");
            salvascore (high,*est);
            return 1;
        }


        salvafase = fopen("qualfase.txt","w");
        {
            fprintf(salvafase,"%d",1);
        }
        fclose(salvafase);


        (*est).ghosts = 0;
        cenario = fopen("fase2.txt","r"); //atribui matriz fase2 para o cenario
        //system("cls");
        for(i=0; i<NUMLIN; i++)
        {
            for(j=0; j<NUMCOL; j++)
            {
                fscanf(cenario,"%c",&mat[i][j]);
            }
        }
        for(i=0; i<NUMLIN; i++)
        {
            for(j=0; j<NUMCOL; j++)
            {

                if(mat[i][j]=='d') //Caso d, colocao caracter equivalente ao Mr Do
                {
                    pos_do[0] = i; //obtem a posição do Mr.Do, para se salvar no estado por exemplo, para quando continuar o jogo ele está na posição correta
                    pos_do[1] = j;

                }
            }
        }

        fclose(cenario);


    }



}



int novojogo (FILE *cenario, int pos_do[], FILE *estado, Highscore high[], GameState est)
{
    char mat[NUMLIN][NUMCOL], mat_compara[NUMLIN][NUMCOL], dir;
    TIRO shot;
    int i,j,k,o,p, retorno;
    time_t segundos,segundos_novo,segundos_2,segundos_novo_2;
    for(i=0; i<NUMLIN; i++) //faz a passagem por toda as linas
    {
        for(j=0; j<NUMCOL; j++)//faz a passagem por toda as colunas
        {

            fscanf(cenario,"%c",&mat[i][j]); //dessa forma é "povoada" a matriz 'mat' com tudo que há dentro do arquivo aberto no menu
        }
    }
    gotoxy1 (0,0); //serve para colocar o cursor na posição inicial da tela
    imprime_matriz(mat,pos_do,high,&est); //função que imprie a matriz 'mat'
    fclose(cenario); //fecha o arquivo depois de lido

    for(i=0; i<NUMLIN; i++) //faz a passagem por toda as linas
    {
        for(j=0; j<NUMCOL; j++)//faz a passagem por toda as colunas
        {
            mat_compara[i][j] =  mat[i][j];
        }

    }
    segundos =  GetTickCount(); //pega os milisegundos desde 1970 e comparará com os segundos atuais pra ver se passou 3
    segundos_2 =  GetTickCount(); //pega os milisegundos desde 1970 e comparará com os segundos atuais pra ver se passou 3

    while(dir!=27) //enquanto não for ESQ fica neste while que faz o jogo acontecer
    {
        segundos_novo =  GetTickCount();
        segundos_novo_2 =  GetTickCount();
        if((segundos_novo - segundos)>3000) //Dessa forma só a cada 3 segundos nasce um fantasma
        {
            segundos = segundos_novo;
            segundos_novo =  GetTickCount();
            fantasma(mat,pos_do,&est); //Função que faz nascerem os fantasmas
        }
        if((segundos_novo_2 - segundos_2)> 200)
        {
            segundos_2 = segundos_novo_2;
            segundos_novo_2 =  GetTickCount();
            movefantasmadepoisdenascer(mat,pos_do,&est,high); //função que analisa a matriz e faz os fantasmas se moverem
        }





        //  printf("%d",est.ghosts);


        gotoxy1 (0,0);
        // Sleep(10);
        for(i=0; i<NUMLIN; i++) //faz a passagem por toda as linas
        {
            for(j=0; j<NUMCOL; j++)//faz a passagem por toda as colunas
            {
                if (mat_compara[i][j] !=  mat[i][j]) //Se a matriz modificou vai imprimir novamente, caso contrário não imprime a matriz. Assim evita de ficar lento o jogo.
                {
                    gotoxy1(69,10); // move o cursor para imprimir na tela o score sem ser em cima do próprio mapa
                    printf("%5d\n",est.score);
                    gotoxy1 (0,0);
                    if(imprime_matriz(mat,pos_do,high,&est) == 1) //se o imprime matriz retornou 1 significa que deve retornar ao menu
                        return;
                    for(o=0; o<NUMLIN; o++) //faz a passagem por toda as linas
                    {
                        for(p=0; p<NUMCOL; p++)//faz a passagem por toda as colunas
                        {
                            mat_compara[o][p] =  mat[o][p];
                        }

                    }

                }


            }

        }

        if(kbhit()) //esse teste é feito para que ele só peça a tecla que foi clicada, caso algo alguma tecla seja pressionada, se não o jogo
        {
            dir = toupper(getch()); //ficaria parado enquanto nada fosse pressionado
            gotoxy1(63,15);
            puts("              ");
            gotoxy1(63,16);
            puts("            ");
        }
        if(dir!=0) //como cada vez que ele move o Mr.Do ele coloca a direção em zero (para evitar que escolha uma direção e ele continue sempre nela só se vai para a função de mover se não está zerado a direção
            retorno = move_do(mat,pos_do,&dir,high,&est,&shot); // chama a função de mover o Mr.Do e retorna -1 caso o movimento é inválido
        if(dir!=27)
            dir=0;
        if(retorno == -1) //caso deu erro no movimento, é retornado da função move_do o valor -1, indicando que o movimento não é possível
        {
            gotoxy1(63,15);
            puts("Movimento nao");
            gotoxy1(63,16);
            puts("eh possivel");
        }

        if(retorno == -2) //caso deu -2 significa que voltou da função por que morreu. Ai volta ao menu
            return;






    }





    textcolor(YELLOW);
    cenario = fopen("continua.txt","w"); //abre o arquivo continua onde será salvo a matriz modificada para poder continuar o jogo depois
    estado = fopen("estado.bin","wb"); //abre o arquivo de estado onde será salvo o estado do score e numero de fantasmas para poder continuar o jogo depois
    for(i=0; i<NUMLIN; i++)
    {
        for(j=0; j<NUMCOL; j++)
        {

            fputc(mat[i][j],cenario); //se passa por toda a matirz colocando ela dentro do arquivo caracter a caracter
        }
    }



    fwrite(&est, sizeof(GameState), 1, estado); //salva-se o estado
    fclose(estado); //fecha-se o aquivo
    fclose(cenario); //fecha-se o aquivo
}
void imprime_highscores(Highscore high[])
{
    int cont=0, numentradas=0;
    FILE *hs;
    hs = fopen("highscores.bin","rb"); //Abre o arquivo binario com as informações do highscore
    if(hs == NULL)
    {
        printf("Erro ao abrir o arquivo, arquivo sendo criado");
        return;
    }

    do
    {
        fread(&high[numentradas], sizeof(high[numentradas]), 1,hs); //Lê o conteudo do arquivo e coloca no vetor de struct
        numentradas ++;
    }
    while(!feof(hs));
    fclose(hs);
    for(cont=0; cont<6; cont++)
    {
        printf("\t%s ----- %d\n ",high[cont].name,high[cont].score); //Imprime as informações de cada struct do vetor
    }
}

int menu () //nome de funcao auto explicativo
{
    textcolor(YELLOW);
    Highscore high[6] = {0,0,0,0,0,0};

    GameState est = {0,0};
    int op, pos_do[2], i;
    FILE *cenario;
    FILE *estado;
    FILE *salvafase;

    do
    {
        printf("Mr. Do\n\n1 - Novo Jogo\n2 - Continuar\n3 - High Scores\n4 - Sair\n\nEntre com a opcao desejada:\n"); //imprime menu e lê a opcao do jogador
        scanf("%d",&op);
        printf("\n\n");


        switch (op)
        {
        case 1: //novo jogo
            salvafase = fopen("qualfase.txt","w");
            {
                fprintf(salvafase,"%d",0);
            }
            fclose(salvafase);
            est.score = 0;
            cenario = fopen("fase1.txt","r"); //atribui a matriz fase1 para a variavel cenario
            estado = fopen("estado.bin","wb"); //abre um novo arquivo estado
            gotoxy1(63,10); //imprime o score do lado da matriz
            printf("Score: ");

            novojogo(cenario, pos_do, estado, high ,est);
            break;

        case 2:
            cenario = fopen("continua.txt","r"); //atribui a matriz continua para a variavel cenario
            estado = fopen("estado.bin","rb"); //lê o estado do último jogo nao encerrado

            for (i = 0; i < 2; i++)
                fread(&est, sizeof(GameState), 1, estado);

            fclose(estado);

            gotoxy1(63,10);
            printf("Score: ");
            novojogo(cenario, pos_do, estado, high,est);
            break;

        case 3:
            imprime_highscores(high);//high scores
            system("pause"); //jogador precisa apertar tecla qualquer para continuar depois de imprimir os scores

            break;

        case 4:
            exit(1); //fecha o programa
            break;

        default:
            printf("opcao invalida");
            break;
        }
        system("cls");
    }
    while(op!=4);
    return;
}


int main ()
{
    gotoxy1 (0,0); // apgaga a matriz antes do movimento imprime a proxima sempre no mesmo lugar
    srand(time(NULL));
    menu(); //Chama o menu
    return 0;

}

