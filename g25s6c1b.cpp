#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <omp.h>
#include <complex>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

//processadores
void proc(){
  int N, Nmax;
  N = omp_get_num_threads();
  Nmax = omp_get_max_threads();
  
  cout<<"Processadores: "<<omp_get_num_procs()<<endl;
  
  if(N==1 && Nmax==1){
    cout<<"Esta activo " << N << " thread, de um total de " << Nmax << " thread permitido" <<endl;
  }
  
  else if(N==1 && Nmax>1){
    cout<<"Esta activo " << N << " thread, de um total de " << Nmax << " threads permitidos" <<endl;
  }
  
  else{
    cout<<"Estao activos " << N << " threads, de um total de " << Nmax << " threads permitidos" <<endl;
  }
}

void primos(){ 
  long int limit,n,i,j;
  short int *prime;
	
  long int sum=1;
	
  cout << "Limite: ";
  cin >> limit;
	
  //ATKIN metodo para encontrar os primos
  prime=( short int *)malloc((limit+1)*sizeof( short int));
	#pragma omp parallel for
  for(i=0;i<=limit;i++)
    prime[i]=0;
	
  prime[2]=1;
  prime[3]=1;
	
  clock_t t1=clock(); //start clock
int sqlimit= (int)sqrt(limit);
#pragma omp parallel for collapse(2) private(n)
  for(i=1;i<=sqlimit;i++){     // encontrar candidatos
    for(j=1;j<=sqlimit;j++){
      n=4*i*i+j*j;
      if((n<=limit)&&(n%12==1||n%12==5))
	prime[n]= (prime[n]? 0 : 1);
      n=3*i*i+j*j;
      if((n<=limit)&&(n%12==7))
	prime[n]=(prime[n]? 0 : 1);
      n=3*i*i-j*j;
      if((i>j)&&(n<=limit)&&(n%12==11))
	prime[n]= (prime[n]? 0 : 1);
    }
  
  }
  int n0;
	#pragma omp parallel for private(n,n0)
  for(i=5;i<=sqlimit;i+=2){   // eliminar multiplos dos quadrados
    if(prime[i]){
      n0=i*i;
      for(n=n0;n<=limit;n+=n0)
	prime[n]= 0;
    }
  }
  #pragma omp parallel for reduction(+:sum)
  for(i=3;i<=limit;i+=2){
    if(prime[i]) sum++;
  }
  cout << "# primos: " << sum;
  sum=1;

  for(i=3;i<=limit;i+=2){
    if(prime[i]){
      sum++;
				
      if(!(sum%7)){
      }
    }
  }
  cout << endl << "RUNTIME: " << (double)((clock()-t1)/(double)CLOCKS_PER_SEC) << endl; //stop clock
  cout << endl;
}

int main(){

  int a;

  cout << "Escolha a opcao desejada" << endl;
  cout << "1: Numero de processadores e threads" << endl; 
  cout << "2: Calculo dos numeros primos" << endl; //adaptacao programacao 1 ano
  cin >> a;

  if(a==1){
    proc();
  }
		
  if(a==2){
    primos();
  } 

  return 0;
}
