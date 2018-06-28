#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <time.h>

int FLAG_einlesen_yAchse=0;
//debug
//double time1=0.0, tstart, time2;

/*fixme
 *
 *
 */


typedef struct fliesen{
   unsigned int x_value;
   unsigned int* y_value;
   int* in;
   unsigned int y_length;
}fliesen;

typedef struct paar{
    long p1[2];
    long p2[2];
}paar;

int x_length=1;
long y_values=0;
int find_f(fliesen** x,int left, int right, unsigned int wanted){

        if (right >= left)
        {
            int pivo = left + (right - left)/2;

            if (x[pivo]->x_value == wanted)
                return pivo;

            if (x[pivo]->x_value > wanted)
                return find_f(x, left, pivo-1, wanted);


            return find_f(x, pivo+1, right, wanted);
        }

        return -1;
    }

int sort_f(fliesen** x, int start, int end){
    int pi=0;
    if (start < end){
        int pivot = x[end]->x_value;
        int i = (start - 1);

        for (int j = start; j <= end - 1; j++)
        {

            if (x[j]->x_value <= pivot)
            {
                i++;

                fliesen* t = x[i];
                x[i] = x[j];
                x[j] = t;
            }
        }

        fliesen* t = x[i + 1];
        x[i + 1] = x[end];
        x[end] = t;

        pi=(i + 1);

        sort_f(x, start, pi - 1);
        sort_f(x, pi + 1, end);
    }
}

int find_i(int* y,int left, int right, unsigned int wanted){

    if (right >= left)
    {
        int pivo = left + (right - left)/2;

        if (y[pivo] == wanted)
            return pivo;

        if (y[pivo] > wanted)
            return find_i(y, left, pivo-1, wanted);


        return find_i(y, pivo+1, right, wanted);
    }

    return -1;
}
int sort_i(unsigned int* y, int start, int end){
    int pi=0;
    if (start < end){
        unsigned int pivot = y[end];
        int i = (start - 1);

        for (int j = start; j <= end - 1; j++)
        {

            if (y[j] <= pivot)
            {
                i++;

                unsigned int t = y[i];
                y[i] = y[j];
                y[j] = t;
            }
        }

        unsigned int t = y[i + 1];
        y[i + 1] = y[end];
        y[end] = t;

        pi=(i + 1);

        sort_i(y, start, pi - 1);
        sort_i(y, pi + 1, end);
    }
}

void freeDataStruct(fliesen** x_achse){
    for (int i = 0; i < x_length; ++i) {
        free(x_achse[i]->y_value);
        free(x_achse[i]);
    }
    free(x_achse);
}

fliesen** einlesen (){
    fliesen** x_achse;
    char* line;
    char** part;
    char* delimiter = " ";
    char character='!';
    int start=0;

    //time1=0.0;//debug
    //tstart = clock();//debug

    line = (char*) calloc(70, sizeof(char));
    part = (char**) malloc(2* sizeof(char*));
    part[0] = (char*) malloc(70* sizeof(char));
    part[1] = (char*) malloc(70* sizeof(char));

    char* temp;
    int i=0;
    int x_y_coord=0;
    int zero=0;
    while(character!=EOF) {


        character = getchar();
        while ((character != 10) && (character != EOF)) {

            if (zero == 0 && character == '0') {
                continue;
            }
            if (zero == 1 && character == 32) {
                zero = 0;
            }
            zero = 1;
            line[i] = character;
            i++;
            character = getchar();
        }

        if (character == EOF) {
            break;
        }

        i = 0;


        if (start == 0) {

            x_achse = (fliesen **) calloc(1, sizeof(fliesen *));
            start = 1;
        }


        x_y_coord = 0;
        temp = strtok(line, delimiter);

        while (temp != NULL) {
            if (x_y_coord > 1) {
                printf("To many coordinates!\n");
                free(line);
                free(part);
                exit(-1);
            }

            strcpy(part[x_y_coord], temp);
            temp = strtok(NULL, delimiter);

            x_y_coord++;

        }

        if (x_achse[0] == NULL) {

            fliesen *newFliese = (fliesen *) malloc(sizeof(fliesen));
            newFliese->x_value = atoi(part[0]);
            newFliese->y_value = (unsigned int *) malloc(1 * sizeof(unsigned int));
            newFliese->y_value[0] = atoi(part[1]);
            newFliese->y_length = 1;
            newFliese->in = (int *) malloc(1 * sizeof(int));
            newFliese->in[0] = -1;
            x_achse[0] = newFliese;

        } else {

            unsigned int x = atoi(part[0]);
            int x_pos;

            if ((x_pos = find_f(x_achse, 0, x_length - 1, x)) == -1) {

                fliesen **newArray = (fliesen **) calloc((x_length + 1), sizeof(fliesen *));

                for (int j = 0; j < x_length; ++j) {
                    newArray[j] = x_achse[j];
                }

                free(x_achse);

                x_achse = newArray;
                x_length++;

                fliesen *newFilese = (fliesen *) malloc(sizeof(fliesen));

                newFilese->x_value = x;
                newFilese->y_value = (unsigned int *) malloc(1 * sizeof(unsigned int));
                newFilese->in = (int *) malloc(1 * sizeof(int));
                newFilese->in[0] = -1;

                newFilese->y_value[0] = atoi(part[1]);
                newFilese->y_length = 1;

                x_achse[x_length - 1] = newFilese;

                sort_f(x_achse, 0, x_length - 1);
            } else {

                //printf("\n--------------------------\n");//debug
                //printf("x: %d, x_pos:%d, x_value: %d, y_length:%d\n", x, x_pos, x_achse[x_pos]->x_value,//debug
                //       x_achse[x_pos]->y_length);//debug
                //printf("\n--------------------------\n");//debug

                unsigned int y_length = x_achse[x_pos]->y_length;

                if (find_i(x_achse[x_pos]->y_value, 0, y_length, atoi(part[1])) < 0) {


                    unsigned int *newY = (unsigned int *) malloc((y_length + 1) * sizeof(unsigned int));
                    unsigned int *newin = (int *) malloc((y_length + 1) * sizeof(int));

                    for (int j = 0; j < y_length; ++j) {
                        newY[j] = x_achse[x_pos]->y_value[j];
                        newin[j] = -1;

                    }
                    free(x_achse[x_pos]->y_value);
                    free(x_achse[x_pos]->in);
                    x_achse[x_pos]->y_value = newY;
                    x_achse[x_pos]->in = newin;


                    x_achse[x_pos]->y_value[y_length] = atoi(part[1]);
                    x_achse[x_pos]->y_length = (x_achse[x_pos]->y_length + 1);
                    x_achse[x_pos]->in[y_length] = -1;
                    sort_i(x_achse[x_pos]->y_value, 0, y_length);
                }
            }


        }
    }

    //time1 = clock() - tstart;//debug
    //time2 = time1/CLOCKS_PER_SEC;//debug
    //printf("\n/////////////////////////\n");//debug
    //printf("Einlesezeit:%f",time2);//debug
    //printf("\n/////////////////////////\n");//debug
    free(line);
    free(part[0]);
    free(part[1]);
    free(part);
    free(temp);
    return x_achse;
}



long*** teilmenge(fliesen** x_achse){
    for (int i = 0; i < x_length; ++i) {
        long size = x_achse[i]->y_length;
        y_values=y_values+size;
    }

    //printf("Erste Schleife OK\n");//debug

    if (y_values%2!=0){
        printf("Es ist kein matching moeglich: ungerade Anzahl von Fliesen.\n");
        exit(0);
    }
    //printf("y_values: %d\n",y_values);
    //printf("y_values / 2: %d\n",y_values/2);
    long** A = (long**)malloc((y_values/2)* sizeof(long*));
    long** B = (long**)malloc((y_values/2)* sizeof(long*));
    long*** graph =(long***)malloc(2* sizeof(long**));

    if(A==NULL || B==NULL ||graph==NULL){
        printf("Nicht genug Speicher vorhanden.\n");
        exit(-1);
    }

    for (int j = 0; j < (y_values/2) ; ++j) {
        A[j]=(long*)malloc(3* sizeof(long));
        B[j]=(long*)malloc(3* sizeof(long));
        A[j][0]=-1;
        A[j][1]=-1;
        A[j][2]=0;
        B[j][0]=-1;
        B[j][1]=-1;
        B[j][2]=0;
    }


    //printf("Zweite Schleife OK\n");//debug

    graph[0]=A;
    graph[1]=B;
    return graph;
}


long*** raum_bestimmen_intern(fliesen** x_achse, long x_koord, long y_koord, long*** graph){

    int x_pos=find_f(x_achse,0,x_length,x_koord);

    if(x_pos==-1){
        printf("Error no x_koord found!\n");
        exit(-1);
    }

    int y_pos=find_i(x_achse[x_pos]->y_value,0,x_achse[x_pos]->y_length,y_koord);

    if(y_pos==-1){
        printf("Error no y_koord found!\n");
        exit(-1);
    }

    int y2_pos;

    //printf("x_koord: %ld x_pos: %d\n",x_koord,x_pos);//debug
    //printf("y_koord: %ld y_pos: %d\n",y_koord,y_pos);//debug
    if (x_achse[x_pos]->in[y_pos]==-1){
        x_achse[x_pos]->in[y_pos]=1; //A=1, B=2
        for (int i = 0; i < y_values/2; ++i) {
            if(graph[0][i][0]==-1){
                graph[0][i][0]=x_koord;
                graph[0][i][1]=y_koord;
                break;
            }
        }
        //printf("first is ok\n");//debug
    }
    int menge=x_achse[x_pos]->in[y_pos];//1=A 2=B
    //printf("menge: %d\n",menge);//debug
    if(menge==1) {
        if (0 <= y_pos - 1) {
            if (x_achse[x_pos]->y_value[y_pos] - 1 == x_achse[x_pos]->y_value[y_pos - 1]) {
                if (x_achse[x_pos]->in[y_pos - 1] == -1) {
                    for (int i = 0; i < y_values / 2; ++i) {
                        if (graph[1][i][0] == -1) {
                            graph[1][i][0] = x_koord;
                            graph[1][i][1] = y_koord - 1;
                            x_achse[x_pos]->in[y_pos - 1] = 2;
                            graph=raum_bestimmen_intern(x_achse, x_koord, (y_koord - 1), graph);
                            break;
                        }
                    }
                }
            }
        }
        if (x_achse[x_pos]->y_length >= y_pos + 1) {
            if (x_achse[x_pos]->y_value[y_pos] + 1 == x_achse[x_pos]->y_value[y_pos + 1]) {
                if (x_achse[x_pos]->in[y_pos + 1] == -1) {
                    for (int i = 0; i < y_values / 2; ++i) {
                        if (graph[1][i][0] == -1) {
                            graph[1][i][0] = x_koord;
                            graph[1][i][1] = y_koord + 1;
                            x_achse[x_pos]->in[y_pos + 1] = 2;
                            graph=raum_bestimmen_intern(x_achse, x_koord, (y_koord + 1), graph);
                            break;
                        }
                    }
                }
            }
        }
        if (x_length-1 >= x_pos + 1) {
            y2_pos=find_i(x_achse[x_pos + 1]->y_value,0,x_achse[x_pos + 1]->y_length,x_achse[x_pos]->y_value[y_pos]);
            if (y2_pos!=-1) {
                if (x_achse[x_pos + 1]->in[y2_pos] == -1) {
                    for (int i = 0; i < y_values / 2; ++i) {
                        if (graph[1][i][0] == -1) {
                            graph[1][i][0] = x_koord + 1;
                            graph[1][i][1] = y_koord;
                            x_achse[x_pos + 1]->in[y2_pos] = 2;
                            graph=raum_bestimmen_intern(x_achse, (x_koord + 1), y_koord, graph);
                            break;
                        }
                    }
                }
            }
        }
        if (0 <= x_pos - 1) {
            y2_pos=find_i(x_achse[x_pos - 1]->y_value,0,x_achse[x_pos - 1]->y_length,x_achse[x_pos]->y_value[y_pos]);
            if (y2_pos!=-1) {
                if (x_achse[x_pos - 1]->in[y2_pos] == -1) {
                    for (int i = 0; i < y_values / 2; ++i) {
                        if (graph[1][i][0] == -1) {
                            graph[1][i][0] = x_koord - 1;
                            graph[1][i][1] = y_koord;
                            x_achse[x_pos - 1]->in[y2_pos] = 2;
                            graph=raum_bestimmen_intern(x_achse, (x_koord - 1), y_koord, graph);
                            break;
                        }
                    }
                }
            }
        }
    }
    if(menge==2){
        if (0 <= y_pos - 1) {
            if (x_achse[x_pos]->y_value[y_pos] - 1 == x_achse[x_pos]->y_value[y_pos - 1]) {
                if (x_achse[x_pos]->in[y_pos - 1] == -1) {
                    for (int i = 0; i < y_values / 2; ++i) {
                        if (graph[0][i][0] == -1) {
                            graph[0][i][0] = x_koord;
                            graph[0][i][1] = y_koord - 1;
                            x_achse[x_pos]->in[y_pos - 1] = 1;
                            graph=raum_bestimmen_intern(x_achse, x_koord, (y_koord - 1), graph);
                            break;
                        }
                    }
                }
            }
        }
        if (x_achse[x_pos]->y_length >= y_pos + 1) {
            if (x_achse[x_pos]->y_value[y_pos] + 1 == x_achse[x_pos]->y_value[y_pos + 1]) {
                if (x_achse[x_pos]->in[y_pos + 1] == -1) {
                    for (int i = 0; i < y_values / 2; ++i) {
                        if (graph[0][i][0] == -1) {
                            graph[0][i][0] = x_koord;
                            graph[0][i][1] = y_koord + 1;
                            x_achse[x_pos]->in[y_pos + 1] = 1;
                            graph=raum_bestimmen_intern(x_achse, x_koord, (y_koord + 1), graph);
                            break;
                        }
                    }
                }
            }
        }
        if (x_length-1 >= x_pos + 1) {
            y2_pos=find_i(x_achse[x_pos + 1]->y_value,0,x_achse[x_pos + 1]->y_length,x_achse[x_pos]->y_value[y_pos]);
            if (y2_pos!=-1) {
                if (x_achse[x_pos + 1]->in[y2_pos] == -1) {
                    for (int i = 0; i < y_values / 2; ++i) {
                        if (graph[0][i][0] == -1) {
                            graph[0][i][0] = x_koord + 1;
                            graph[0][i][1] = y_koord;
                            x_achse[x_pos + 1]->in[y2_pos] = 1;
                            graph=raum_bestimmen_intern(x_achse, (x_koord + 1), y_koord, graph);
                            break;
                        }
                    }
                }
            }
        }
        if (0 <= x_pos - 1) {
            y2_pos=find_i(x_achse[x_pos - 1]->y_value,0,x_achse[x_pos - 1]->y_length,x_achse[x_pos]->y_value[y_pos]);
            if (y2_pos!=-1) {
                if (x_achse[x_pos - 1]->in[y2_pos] == -1) {
                    for (int i = 0; i < y_values / 2; ++i) {
                        if (graph[0][i][0] == -1) {
                            graph[0][i][0] = x_koord - 1;
                            graph[0][i][1] = y_koord;
                            x_achse[x_pos - 1]->in[y2_pos] = 1;
                            graph=raum_bestimmen_intern(x_achse, (x_koord - 1), y_koord, graph);
                            break;
                        }
                    }
                }
            }
        }
    }
    return graph;


}

long*** raum_bestimmen(fliesen** x_achse, long x_koord, long y_koord, long*** graph){
    graph=raum_bestimmen_intern(x_achse,x_koord,y_koord,graph);
    for (int i = 0; i < x_length-1; ++i) {
       free(x_achse[i]->in);
    }
    return graph;
}

paar** loesen(long*** graph,fliesen** x_achse){
    paar**loesung=(paar**)malloc((y_values/2)*sizeof(paar*));
    for (int i = 0; i < y_values/2; ++i) {
        loesung[i]=(paar*)malloc(sizeof(paar));
    }
    int count=0;
    for (int j = 0; j < y_values/2; ++j) {
        int Ax_koord=graph[0][j][0];
        int Ay_koord=graph[0][j][1];
        if(graph[0][j][0]==-1||graph[1][j][0]==-1){
            break;
        }
        for (int i = 0; i < y_values/2; ++i) {
            int Bx_koord=graph[1][i][0];
            int By_koord=graph[1][i][1];
            int gepaart=graph[1][i][2];
            if(gepaart==0) {
                if (Ax_koord - 1 == Bx_koord && Ay_koord == By_koord) {
                    graph[1][i][2]=1;
                    graph[0][j][2]=1;
                    loesung[count]->p1[0]=Ax_koord;
                    loesung[count]->p1[1]=Ay_koord;
                    loesung[count]->p2[0]=Bx_koord;
                    loesung[count]->p2[1]=By_koord;
                    count++;
                    break;
                }
                if (Ax_koord + 1 == Bx_koord && Ay_koord == By_koord) {
                    graph[1][i][2]=1;
                    graph[0][j][2]=1;
                    loesung[count]->p1[0]=Ax_koord;
                    loesung[count]->p1[1]=Ay_koord;
                    loesung[count]->p2[0]=Bx_koord;
                    loesung[count]->p2[1]=By_koord;
                    count++;
                    break;
                }
                if (Ax_koord == Bx_koord && Ay_koord - 1 == By_koord) {
                    graph[1][i][2]=1;
                    graph[0][j][2]=1;
                    loesung[count]->p1[0]=Ax_koord;
                    loesung[count]->p1[1]=Ay_koord;
                    loesung[count]->p2[0]=Bx_koord;
                    loesung[count]->p2[1]=By_koord;
                    count++;
                    break;
                }
                if (Ax_koord == Bx_koord && Ay_koord + 1 == By_koord) {
                    graph[1][i][2]=1;
                    graph[0][j][2]=1;
                    loesung[count]->p1[0]=Ax_koord;
                    loesung[count]->p1[1]=Ay_koord;
                    loesung[count]->p2[0]=Bx_koord;
                    loesung[count]->p2[1]=By_koord;
                    count++;
                    break;
                }
            }
        }
    }
    return loesung;
}

void check(paar** losung, long*** graph){
    int k=1;
    for (int i = 0; i < y_values/2; ++i) {
        if(graph[0][i][0]==-1){
            break;
        }
        if(graph[0][i][2]!=1||graph[1][i][2]!=1){
            printf("%d,%d or %d,%d\n",graph[0][i][0],graph[0][i][1],graph[1][i][0],graph[1][i][1]);
            k=0;
        }
    }
    if(k==1) {
        printf("\nvvvvvvvvvvvvvvvvvv--loesung--vvvvvvvvvvvvv\n");
        for (int k = 0; k < y_values / 2; ++k) {
            if(graph[0][k][0]==-1){
                break;
            }
            printf("\n--------------Paar %d--------------\n", k);
            printf("Aus A: (%ld,%ld)  ||  Aus B: (%ld,%ld)\n", losung[k]->p1[0], losung[k]->p1[1], losung[k]->p2[0], losung[k]->p2[1]);
        }
    } else{
        //fixme statt printf neue lösung suchen.
        printf("keine loesung.\n");
        exit(0);
    }
}
/*
 * TestFunktion
 */
void TEST_FKT(fliesen** x_achse){
    printf("Start TEST_FKT\n");
    //time1=0.0;
    //tstart = clock();
    //time1 = clock() - tstart;
    //time2 = time1/CLOCKS_PER_SEC;


    for(int i=0;i<x_length;i++){
        int size = x_achse[i]->y_length;
        for (int j = 0; j < size ; ++j) {
           // printf("X:%d Y:%d\n",x_achse[i]->x_value,x_achse[i]->y_value[j]);
        }
        printf("\n");
    }
    printf("\n\n");
    for (int j = 0; j < x_length; ++j) {
        //printf("x[j]= %d\n",x_achse[j]->x_value);
    }
    long*** graph;
    graph=teilmenge(x_achse);
    graph=raum_bestimmen(x_achse,x_achse[0]->x_value,x_achse[0]->y_value[0],graph);

    for (int k = 0; k <(y_values/2) ; ++k) {
        //printf("A[%d]:(%ld,%ld)        B[%d]:(%ld,%ld)\n",k,graph[0][k][0],graph[0][k][1],k,graph[1][k][0],graph[1][k][1]);
    }
    paar** losung=loesen(graph,x_achse);
    check(losung,graph);
    freeDataStruct(x_achse);
}

int main (void){
    fliesen** x=einlesen();
    return 0;
    //TEST_FKT(x);
    //return  0;
}