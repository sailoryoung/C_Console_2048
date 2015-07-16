#include <stdio.h>
#include <stdlib.h>


int mat_init(int ***mat);

int mat_left(int **mat);
int mat_right(int **mat);
int mat_up(int **mat);
int mat_down(int **mat);

int mat_reach(int **mat);
int mat_insert(int **mat);
void mat_print(int **mat);

int main(){
    int **mat;
    int state;
    char key;
    while(1){
        mat_init(&mat);
        scanf("%c",&key);

        while(key){
            switch(key){
                case 'h':state=mat_left(mat);break;
                case 'j':state=mat_down(mat);break;
                case 'k':state=mat_up(mat);break;
                case 'l':state=mat_right(mat);break;
                case 'q':return 0;
                default:scanf("%c",&key);continue;
            }
            if(state==0){
                printf("can't add,try again!:");
                scanf("%c",&key);
                continue;
            }
            if(mat_reach(mat)){
                printf("succeed!\n");
                break;
            }
            if(!mat_insert(mat)){
                printf("fail\n");
                break;
            }
            system("clear");
            mat_print(mat);
            printf("type in the direction(h j k l):");
            scanf("%c",&key);
        }

        printf("another one?(y or n):");
        scanf("%c",&key);
        if(key=='n') break;
    }
    return 0;
}

int mat_init(int ***mat){
    int i;
    *mat=(int **)malloc(sizeof(int *)*4);
    for(i=0;i<4;i++){
        (*mat)[i]=(int *)malloc(sizeof(int)*4);
        memset((*mat)[i],0,sizeof(int)*4);
    }
    srand(time(0));
    mat_insert(*mat);
    mat_insert(*mat);
    mat_print(*mat);
    return 0;
}

int mat_left(int **mat){
    int i,j;
    int flag=0;
    int k=0,temp[4]={0},last=0;
    for(i=0;i<4;i++){
        memset(temp,0,sizeof(int)*4);
        for(j=0,k=0,last=0;j<4;j++){
            if(mat[i][j]!=0){
                temp[k]=mat[i][j];
                mat[i][j]=0;
                last=j+1;
                k++;
            }
        }
        if(k<last) flag=1;
        for(j=0;j<3;j++){
            if(temp[j]>0&&temp[j]==temp[j+1]){
                temp[j]+=temp[j];
                temp[j+1]=0;
                flag=1;
            }
        }
        for(j=0,k=0;k<4;k++){
            if(temp[k]!=0){
                mat[i][j]=temp[k];
                j++;
            }
        }
    }
    return flag;
}

int mat_right(int **mat){
    int i,j;
    int flag=0;
    int k=0,temp[4]={0},last=0;
    for(i=0;i<4;i++){
        memset(temp,0,sizeof(int)*4);
        for(j=3,k=3,last=3;j>=0;j--){
            if(mat[i][j]!=0){
                temp[k]=mat[i][j];
                mat[i][j]=0;
                last=j-1;
                k--;
            }
        }
        if(k>last) flag=1;
        for(j=3;j>=0;j--){
            if(temp[j]>0&&temp[j]==temp[j+1]){
                temp[j]+=temp[j];
                temp[j+1]=0;
                flag=1;
            }
        }
        for(j=3,k=3;k>=0;k--){
            if(temp[k]!=0){
                mat[i][j]=temp[k];
                j--;
            }
        }
    }
    return flag;
}

int mat_up(int **mat){
    int i,j;
    int flag=0;
    int k=0,temp[4]={0},last=0;
    for(i=0;i<4;i++){
        memset(temp,0,sizeof(int)*4);
        for(j=0,k=0,last=0;j<4;j++){
            if(mat[j][i]!=0){
                temp[k]=mat[j][i];
                mat[j][i]=0;
                last=j+1;
                k++;
            }
        }
        if(k<last) flag=1;
        for(j=0;j<3;j++){
            if(temp[j]>0&&temp[j]==temp[j+1]){
                temp[j]+=temp[j];
                temp[j+1]=0;
                flag=1;
            }
        }
        for(j=0,k=0;k<4;k++){
            if(temp[k]!=0){
                mat[j][i]=temp[k];
                j++;
            }
        }
    }
    return flag;
}

int mat_down(int **mat){
    int i,j;
    int flag=0;
    int k=0,temp[4]={0},last=0;
    for(j=0;j<4;j++){
        memset(temp,0,sizeof(int)*4);
        for(i=3,k=3,last=3;i>=0;i--){
            if(mat[i][j]!=0){
                temp[k]=mat[i][j];
                mat[i][j]=0;
                last=i-1;
                k--;
            }
        }
        if(k>last) flag=1;
        for(i=3;i>0;i--){
            if(temp[i]>0&&temp[i]==temp[i-1]){
                temp[i]+=temp[i];
                temp[i-1]=0;
                flag=1;
            }
        }
        for(i=3,k=3;k>=0;k--){
            if(temp[k]!=0){
                mat[i][j]=temp[k];
                i--;
            }
        }
    }
    return flag;
}

int mat_reach(int **mat){
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(mat[i][j]==2048) return 1;
        }
    }
    return 0;
}

int mat_insert(int **mat){
    int temp[16]={0};
    int i,j,k=0;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(mat[i][j]==0){
                temp[k]=j+i*4;
                k++;
            }
        }
    }
    if(k==0) return 0;
    srand(time(0));
    k=temp[rand()%k];
    mat[(k-k%4)/4][k%4]=2<<(rand()%2);
    return 1;
}

void mat_print(int **mat){
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            printf("\t%d",mat[i][j]);
        }
        printf("\n");
    }
}
