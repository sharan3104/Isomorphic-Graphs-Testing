/*
TEAM 9
SHARAN NARAYAN ADDALA - 2021A7PS0335H
SUMAN SEKHAR SAHOO - 2021A7PS2605H
*/

#include <stdio.h>
#include<stdlib.h>

int **nPrs;
long cou=0;

int nPr(int arr[],int a,int n)
{
    if(a==n)
    {   
        nPrs[cou] = malloc(n*sizeof(int));
        for(int i=0;i<n;i++)
            nPrs[cou][i]=arr[i];
        cou++;
    }

    for(int i=a;i<n;i++)
    {
        int temp = arr[a];
        arr[a]=arr[i];
        arr[i]=temp;

        nPr(arr,a+1,n);

        arr[i]=arr[a];
        arr[a]=temp;
        
    }
}

int verify(int n ,int mat1[n][n], int mat2[n][n])
{
    int a[n];
    for(int i=1;i<=n;i++)
        a[i-1]=i;
    
    nPr(a,0,n);
    int f;
   
    for(long x=0;x<cou;x++)
    {
        f=1;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(mat1[i][j] != mat2[nPrs[x][i]-1][nPrs[x][j]-1])
                     f=0;
            }
        }
        
        if(f)
        {
            printf("Isomorphic\n");
            
            for(int i=0;i<n;i++)
                printf("%d %d\n",(i+1),nPrs[x][i]);
            
            return 1;
        }
    }
    return 0;
}

int main(int argc,char *argv[])
{
    int no_of_nodes_1, no_of_nodes_2;
    int no_of_edges_1, no_of_edges_2;
    FILE *fptr1, *fptr2;
    int a,b;
    
    fptr1 = fopen(argv[1], "r");
    
    fscanf(fptr1, "%d%d",&no_of_nodes_1,&no_of_edges_1);
    int adjMat1[no_of_nodes_1][no_of_nodes_1];
    int degree1[no_of_nodes_1];
    
    for(int i=0; i<no_of_nodes_1; i++)
        for(int j=0; j<no_of_nodes_1;j++)
            adjMat1[i][j]=0;
    
    for(int i=0; i<no_of_edges_1; i++)
    {
        fscanf(fptr1, "%d%d",&a,&b);
        adjMat1[a-1][b-1]=1;
        adjMat1[b-1][a-1]=1;
    }
    
    fclose(fptr1);

    for(int i=0; i<no_of_nodes_1; i++)
    {
        int deg=0;
        for(int j=0; j<no_of_nodes_1;j++)
        {
            if(j==i && adjMat1[i][j]==1)
                deg+=(adjMat1[i][j]+1);
            else
                deg+=adjMat1[i][j];
        }
        degree1[i]=deg;
    }
    
    for (int i = 0; i < no_of_nodes_1; ++i)
    {
        for (int j = i + 1; j < no_of_nodes_1; ++j)
        {
            if (degree1[i] < degree1[j])
            {
                int a = degree1[i];
                degree1[i] = degree1[j];
                degree1[j] = a;
            }
        }
    }

    fptr2 = fopen(argv[2], "r");
    
    fscanf(fptr2, "%d%d",&no_of_nodes_2,&no_of_edges_2);
    int adjMat2[no_of_nodes_2][no_of_nodes_2];
    int degree2[no_of_nodes_2];
    
    for(int i=0; i<no_of_nodes_2; i++)
        for(int j=0; j<no_of_nodes_2;j++)
            adjMat2[i][j]=0;
    
    for(int i=0; i<no_of_edges_2; i++)
    {
        fscanf(fptr2, "%d%d",&a,&b);
        adjMat2[a-1][b-1]=1;
        adjMat2[b-1][a-1]=1;
    }
    
    fclose(fptr2);

    for(int i=0; i<no_of_nodes_2; i++)
    {
        int deg=0;
        for(int j=0; j<no_of_nodes_2;j++)
        {
            if(j==i && adjMat2[i][j]==1)
                deg+=(adjMat2[i][j]+1);
            else
                deg+=adjMat2[i][j];
        }
        degree2[i]=deg;
    }
    
    for (int i = 0; i < no_of_nodes_2; ++i)
    {
        for (int j = i + 1; j < no_of_nodes_2; ++j)
        {
            if (degree2[i] < degree2[j])
            {
                int a = degree2[i];
                degree2[i] = degree2[j];
                degree2[j] = a;
            }
        }
    }
    
    if(no_of_nodes_1 != no_of_nodes_2)
    {
        printf("Not Isomorphic");
        return 0;
    }

    if(no_of_edges_1 != no_of_edges_2)
    {
        printf("Not Isomorphic");
        return 0;
    }

    for(int i=0;i<no_of_nodes_1;i++)
    {
        if(degree1[i] != degree2[i])
        {
            printf("Not Isomorphic");
            return 0;
        }
    }

    long size=1;
    for(int i=1;i<=no_of_nodes_1;i++)
        size*=i;
    nPrs = malloc(size*sizeof(int*));
   
    if(! verify(no_of_nodes_1,adjMat1,adjMat2))
    {
        printf("Not Isomorphic, no bijection found.");
        return 0;
    }

    return 0;
}