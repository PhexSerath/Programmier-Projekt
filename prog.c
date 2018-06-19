#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

int FLAG_f_len=0;
int FLAG_i_len=0;

int FLAG_find_x=0;
int FLAG_find_y=0;

int FLAG_sort_x=0;
int FLAG_sort_y=0;

int FLAG_einlesen_xAchse=0;
int FLAG_einlesen_yAchse=0;
int FLAG_einlesen_X=0;
int FLAG_einlesen_Y=0;
int FLAG_einlesen_free=0;
int FLAG_einlesen_firstX=0;
int FLAG_einlesen_firstY=0;
int FLAG_einlesen_file=0;
int FLAG_einlesen_line=0;
int FLAG_einlesen_line_2=0;

int FLAG_einlesen_loop=0;
int loop =6;

//debug
        int Z0=0;
        int Z1=0;
        int Z2=0;
        int Z3=0;
        int Z4=0;
        int Z5=0;
        int Z6=0;
        int Z7=0;
        int Z8=0;
        int Z9=0;



/*fixme
 *
 *
 */


typedef struct fliesen{
   unsigned int x_value;
   unsigned int* y_value;
   unsigned int y_length;
}fliesen;


int x_length=1;
int find_f(fliesen** x, int x_length, unsigned int wanted){


    //debug
    if(FLAG_find_x==1){
        printf("\nsearch for x\n");
        printf("x_achse lenght: %d wanted x: %d\n",x_length,wanted);
    }

    int len = x_length;
    int rest=0;

    //debug
    if(FLAG_find_x==1)printf("len: %d\n",len);

    if(len %2==1){
        rest=1;
    }

    len = len/2;
    //debug
    if(FLAG_find_x==1)printf("find_f try search in array\n");

    if(x[len]->x_value==wanted){

        //debug
        if(FLAG_i_len==1) printf("x find length: %d\n\n",len);

        return len;
    } else{

        if(len==0){
            if(FLAG_find_x==1)printf("find_f didnt find %d\n\n",wanted);
            return -1;
        }
        //debug
        if(FLAG_find_x==1)printf("find_f try search in array\n");

        if(wanted<x[len]->x_value){
            //debug
            if(FLAG_find_x==1)printf("find_f first half\n");

            find_f(x, len, wanted);
        }else{

            //debug
            if(FLAG_find_x==1)printf("find_f try uper array\n");

            fliesen** uper = &x[len];

            //debug
            if(FLAG_find_x==1)printf("find_f split array\n");

            find_f(uper,len+rest,wanted);
        }
    }
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

int find_i(unsigned int* y, int y_length, unsigned int wanted){

    //debug
    if(FLAG_find_y==1){
        printf("\nsearch for y\n");
        printf("y_achse wanted y: %d\n",wanted);
    }

    int len = y_length;
    int rest=0;

    if(len %2==1){
        rest=1;
    }

    len = len/2;

    if(y[len]==wanted){

        //debug
        if(FLAG_i_len==1) printf("y find length: %d\n\n",len);

        return len;
    } else{
        if(len==0){
            if(FLAG_find_y==1)printf("find_i didnt find %d\n\n",wanted);
            return -1;
        }
        if(wanted<y[len]){
            find_i(y, len, wanted);
        }else{
            unsigned int* uper = &y[len];
            find_i(uper,len+rest,wanted);
        }
    }
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

    line = (char*) calloc(70, sizeof(char));
    part = (char**) malloc(2* sizeof(char*));
    part[0] = (char*) malloc(70* sizeof(char));
    part[1] = (char*) malloc(70* sizeof(char));

    char* temp;
    int i=0;
    int x_y_coord=0;
    int zero=0;
    while(character!=EOF) {

        //debug
        if(FLAG_einlesen_file==1) printf("File read\n");
        if(FLAG_einlesen_loop==1){
            if(loop==0){
                break;
            }
            loop--;
        }

        character=getchar();
        while((character!=10)&&(character!=EOF)){

            //debug
            if(FLAG_einlesen_line==1) printf("read line char: %c, pos: %d\n",character,i);

            if(zero==0&&character=='0'){
                continue;
            }
            if(zero==1&&character==32){
                zero=0;
            }
            zero=1;
            line[i]=character;
            i++;
            character=getchar();
        }

        if(character==EOF){
            //debug
            if(FLAG_einlesen_file==1) printf("EOF\n");
            break;
        }
        //debug
        if(FLAG_einlesen_line_2==1) printf("line: %s\n",line);

        i=0;


        if(start==0){
            //debug
            if(FLAG_einlesen_firstX==1) printf("create first x_achse\n");

            x_achse=(fliesen**)calloc(1, sizeof(fliesen*));
            start=1;
        }


        x_y_coord=0;
        temp = strtok(line, delimiter);

        //debug
        if(FLAG_einlesen_line==1) printf("Start der Zerteilung\n");

        while(temp != NULL){
            if(x_y_coord>1){
                printf("To many coordinates!\n");
                free(line);
                free(part);
                exit(-1);
            }

            //debug
            if(FLAG_einlesen_line==1) printf("temp: %s\n",temp);

            strcpy(part[x_y_coord],temp);
            temp = strtok(NULL, delimiter);

            x_y_coord++;

        }

            if(x_achse[0]==NULL){
            //debug
                if(FLAG_einlesen_firstX==1) printf("firstX: %d\n",atoi(part[0]));

                fliesen* newFliese =(fliesen*)malloc(sizeof(fliesen));
                newFliese->x_value=atoi(part[0]);
                newFliese->y_value=(unsigned int*)malloc(1* sizeof(unsigned int));
                newFliese->y_value[0]=atoi(part[1]);
                newFliese->y_length=1;
                x_achse[0]=newFliese;

        }else{

            //debug
                if(FLAG_einlesen_X==1){
                    printf("part[0] x zuweisen\n");
                    printf("x_length %d\n\n",x_length);

                    for(int i=0;i<x_length;i++){
                        printf("i: %d x: %d\n",i,x_achse[i]->x_value);
                    }
                    printf("\n");
                }

            unsigned int x = atoi(part[0]);
            sort_f(x_achse,0,x_length-1);
            int x_pos;
            if((x_pos=find_f(x_achse,x_length,x))==-1) {

                //debug
                if(FLAG_einlesen_xAchse==1) {
                    printf("X_achseLength=%d\n", x_length);
                    printf("\n");
                    for (int k = 0; k < x_length; ++k) {
                        printf("x_achse[%d]->x_value=%d\n", k, x_achse[k]->x_value);
                    }
                    printf("\n");
                    switch (x) {
                        case 0:
                            if (Z0 == 1) printf("X=%d vorhanden.\n", x);
                            else Z0 = 1;
                            break;
                        case 1:
                            if (Z1 == 1) printf("X=%d vorhanden.\n", x);
                            else Z1 = 1;
                            break;
                        case 2:
                            if (Z2 == 1) printf("X=%d vorhanden.\n", x);
                            else Z2 = 1;
                            break;
                        case 3:
                            if (Z3 == 1) printf("X=%d vorhanden.\n", x);
                            else Z3 = 1;
                            break;
                        case 4:
                            if (Z4 == 1) printf("X=%d vorhanden.\n", x);
                            else Z4 = 1;
                            break;
                        case 5:
                            if (Z5 == 1) printf("X=%d vorhanden.\n", x);
                            else Z5 = 1;
                            break;
                        case 6:
                            if (Z6 == 1) printf("X=%d vorhanden.\n", x);
                            else Z6 = 1;
                            break;
                        case 7:
                            if (Z7 == 1) printf("X=%d vorhanden.\n", x);
                            else Z7 = 1;
                            break;
                        case 8:
                            if (Z8 == 1) printf("X=%d vorhanden.\n", x);
                            else Z8 = 1;
                            break;
                        case 9:
                            if (Z9 == 1) printf("X=%d vorhanden.\n", x);
                            else Z9 = 1;
                            break;

                    }
                }


                fliesen **newArray = (fliesen **) calloc((x_length + 1), sizeof(fliesen *));

                //debug
                if(FLAG_einlesen_xAchse==1) printf("newArray calloc x_Achse for %d ok\n\n",x);

                for (int j = 0; j < x_length; ++j) {
                    newArray[j]=x_achse[j];
                }

                //debug
                if(FLAG_einlesen_xAchse==1){
                    printf("copy x_Achse for %d ok\n",x);
                    printf("x_Achse length for %ld ok\n",(sizeof(newArray[0])/ sizeof(newArray)));
                    printf("x_length %d\n",x_length);
                    printf("x_Achse byte: %ld\n\n", sizeof(x_achse));
                }

                free(x_achse);

                //debug
                if(FLAG_einlesen_xAchse==1) printf("free old x_Achse for %d ok\n",x);

                x_achse = newArray;
                x_length++;

                //debug
                if(FLAG_einlesen_xAchse==1) printf("X_achseLength new=%d\n",x_length);

                fliesen *newFilese = (fliesen *) malloc(sizeof(fliesen));

                //debug
                if(FLAG_einlesen_xAchse==1) printf("newFliese malloc for %d ok\n",x);

                newFilese->x_value = x;
                newFilese->y_value = (unsigned int *) malloc(1 * sizeof(unsigned int));

                //debug
                if(FLAG_einlesen_xAchse==1) printf("newArray malloc y_Achse for %d ok\n",x);

                newFilese->y_value[0] = atoi(part[1]);
                newFilese->y_length=1;

                //debug
                if(FLAG_einlesen_xAchse==1) printf("newArray y_zuweisung for x:%d y:%d ok\n",x, atoi(part[1]));

                x_achse[x_length-1] = newFilese;

                //debug
                if(FLAG_einlesen_xAchse==1) printf("newFliese newArray zuweisen for %d ok\n",x);

                //debug
                if(FLAG_einlesen_xAchse==1)
                    printf("x_Achse length for %ld ok\n",(sizeof(x_achse))/sizeof(x_achse[0]));

            }else{

                //debug
                if(FLAG_einlesen_X==1) printf("And x allready exsist part[0] x zuweisen\n");

                unsigned int y_length = x_achse[x_pos]->y_length;

                //debug
                if(FLAG_einlesen_yAchse==1)printf("SIZE Y: %d\n",y_length);

                sort_i(x_achse[x_pos]->y_value,0,y_length-1);

                if(find_i(x_achse[x_pos]->y_value,y_length,atoi(part[1]))<0){

                    //debug
                    if(FLAG_einlesen_yAchse==1) printf("\nbigger Y for X=%d\n",x_pos);

                    unsigned int *newY= (unsigned int *) malloc((y_length+1) * sizeof(unsigned int));
                    for (int j = 0; j < y_length; ++j) {
                        newY[j]=x_achse[x_pos]->y_value[j];

                        //debug
                        if(FLAG_einlesen_yAchse==1) printf("newY[%d]=x_achse[%d]->y_value[%d]=%d\n",j,x_pos,j,x_achse[x_pos]->y_value[j]);
                    }
                    free(x_achse[x_pos]->y_value);
                    x_achse[x_pos]->y_value=newY;

                    //debug
                    if(FLAG_einlesen_yAchse==1) printf("Y_len=%d\n",y_length);

                    x_achse[x_pos]->y_value[y_length]=atoi(part[1]);
                    x_achse[x_pos]->y_length=(x_achse[x_pos]->y_length+1);

                    //debug
                    if(FLAG_einlesen_yAchse==1) printf("Y_len new=%d\n",x_achse[x_pos]->y_length);
                    for (int j = 0; j < x_achse[x_pos]->y_length; ++j) {
                        if(FLAG_einlesen_yAchse==1)printf("x_achse[%d]->y_value[%d]=%d\n",x_pos,j,x_achse[x_pos]->y_value[j]);
                    }
                    if(FLAG_einlesen_yAchse==1)printf("\n");
                }
            }



        }

    }
    free(line);
    free(part[0]);
    free(part[1]);
    free(part);
    free(temp);
    return x_achse;
}





/*
 * TestFunktion
 */
void TEST_FKT(fliesen** x_achse){
    printf("Start TEST_FKT\n");
    for(int i=0;i<x_length;i++){
        int size = x_achse[i]->y_length;
        for (int j = 0; j < size ; ++j) {
            printf("X:%d Y:%d\n",x_achse[i]->x_value,x_achse[i]->y_value[j]);
        }
        printf("\n");
    }
    printf("\n\n");
    for (int j = 0; j < x_length; ++j) {
        printf("x[j]= %d\n",x_achse[j]->x_value);
    }
    freeDataStruct(x_achse);
}

int main (void){
    fliesen** x=einlesen();
    TEST_FKT(x);
    return  0;
}