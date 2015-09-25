#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#define MAX 300

int X[MAX],h[MAX][MAX],n,l,m;
int p,pad;
int tmpx[MAX],mx = 1;
int xn = 0;
int result_seq[MAX],rs = 0,prevrs = 0;
	
struct xmat{
	int d[MAX][MAX];
	int n,m;
}x[MAX];

void push(struct xmat *x,int xindex,int d,int i,int j){
	if(x[xindex].n == MAX-1 && x[xindex].m == MAX-1){
		printf("paths OverFlow");
	}else{
		x[xindex].d[i][j] = d;
		x[xindex].n = i;
		x[xindex].m = j;
	}
}


void convol_mat(struct xmat *x,int xindex,int tp[],int n,int l){
	int i,o,p,j,f = n-1;
	for(i = 0;i<pad;i++){
		tp[n++] = 0;
	}
	for(o = 0; o<l ;o++){
		for(p = o-pad-1; p>=0 ; p--){
			push(x,xindex,tp[f-2],p,o);
			f--;
		}
		for(i = 1,p = o; i< n && p< n-1; i++,p++){
			push(x,xindex,tp[i],p,o);
		}
		f = n-1;
	}
}	

void divide_seq(int *X,int n,int l){
	int i;
	for(i = 1;i <= n ;i++){
		tmpx[mx++] = X[i];
		if(i%(l) == 0){
			convol_mat(x,xn,tmpx,mx,l);
			xn++;
			mx=1;
		}
	}
}

void print_seq(struct xmat *x,int xindex,int m,int n){
	int i,j;
	for(i = 0 ;i<m ;i++){
		for(j = 0 ;j<n;j++){
			printf("%d\t",x[xindex].d[i][j]);
		}
		printf("\n");
	}
}

void matrixmul(struct xmat *x,int xindex){
	int n = x[xindex].n,m = x[xindex].m,sum,i,j,k;
	int o = l+pad;p = 0;
	for(i = 0;i<n;i++){
		for(j = 0;j<= p;j++){
			sum=0;
           	for(k=0;k<n;k++){
            	sum=sum+(x[xindex].d[i][k]*h[k][0]);
           	}
          	if(i ==0  && j == 0){
           		//printf("\ta>%d + %d =  ",result_seq[prevrs],sum);
           		result_seq[prevrs] = result_seq[prevrs]+sum;
           		//printf("\ta>%d",result_seq[prevrs]);
           		rs = prevrs+1;
           	}else{
           		result_seq[rs++] = sum;
           		//printf("\tb>%d",result_seq[rs-1]);
           	}
		}
	}
	//printf("\n");
	prevrs = rs-1;
}
void overload_add(){
	int i;
	p = l+m-1;
	pad = p-l;
	divide_seq(X,n,l);
	for(i = 0;i<xn;i++){
		print_seq(x,i,l+2,l);
		printf("\n");
	}
	for(i = 0;i<l;i++){
		printf("%d\n",h[i][0]);
	}
	for(i = 0; i<xn;i++){
		matrixmul(x,i);
	}
	printf("Output Sequence :\n{ ");
	for(i = 0;i<rs;i++){
		printf("%d ",result_seq[i]);	
	}
	printf("}");
	printf("\n");
}

void main(){
	//Take inputs X
	X[1] = 5;X[2] = -1;X[3] = 2;X[4] = 3;X[5] = -4;X[6] = 2;X[7] = 5;X[8] = 4;X[9] = 1;X[10] = 2;X[11] = 1;X[12] = 5;
	//Take inputs H
	h[0][0] = 1;h[1][0] = 2;h[2][0] = 3,h[3][0] = 1;
	//Take input n l m
	n = 12;
	l = 4;
	m = 3;
	overload_add();
}
