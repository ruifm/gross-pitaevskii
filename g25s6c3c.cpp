#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <ctime>
#include <omp.h>
#include "compz.h"

//definicao do valor das constantes
#define g 0.01
#define omega 0.85
#define G 1000.0
#define L 10.0
#define N 128
#define dt 0.001953125
using namespace std;


Complex F(Complex ax1, Complex ax2, Complex ay1, Complex ay2, Complex a,int i,int j){  //funcao F
  Complex k(-g,1.);
  Complex iomg(0.,-omega);
  Complex h=c(2.*L/((double)N-1.));
 	Complex dx2 = (ax1+ax2-a-a)/(h*h);
 	Complex dy2 = (ay1+ay2-a-a)/(h*h);
 	Complex lap = dx2+dy2;
 	Complex dx = (ax1-ax2)/(h*c(2.));
 	Complex dy = (ay1-ay2)/(h*c(2.));
  Complex x=c(-L)+c(i)*h;
  Complex y=c(-L)+c(j)*h;
	
	return (c(-0.5)*lap   +   c(0.5)*(x*x+y*y)*a   +  c(G*mod(a)*mod(a))*a    +  iomg*(x*dy-y*dx))/k;
}


int main(void){
  string name,sfps;
  int i,j,n, cpf;
  double h,tf,sum,fps;
  
  h=2.*L/((double)N-1.);
  cout << "gamma = " << g << endl;
  cout << "Omega = " << omega << endl;
  cout << "G = " << G << endl;
  cout << "N = " << N << endl;
  cout << "L = " << L << endl;
  cout << "h = " << h << endl;
  cout << "dt = " << dt << endl;
  cout << "tf = ";
  cin >> tf;
  int nmax=tf/dt;
  cout << "# cycles = " << nmax << endl;
  cout << "cycles per frame = ";
  cin >> cpf;
  int nframes = nmax/cpf;
  cout << "# frames = " << nframes << endl;
  cout << "About " <<nframes*45./1024. <<" Mb will be used" << endl;
  cout << "fps = ";
  cin >> sfps;
  fps=atoi(sfps.c_str());
  cout << "Lenght of video = " << nframes/fps << " secs" << endl;
  cout << "Video name (no extension) : ";
  cin >> name;
  cout << "Video output will be " << name << ".mp4, about " << nframes/1024. << " Mb" << endl;
  cout << "Progress:" << endl;
  Complex **psi, **psi1, **psi2;
  psi = new Complex*[N];
  psi1 = new Complex*[N];
  psi2 = new Complex*[N];
  
  #pragma omp parallel for
  for(i=0;i<N;++i){
    psi[i] = new Complex[N];
    psi1[i] = new Complex[N];
    psi2[i] = new Complex[N];
  }
  Complex one(1.,0.);
  Complex zero(0.,0.);
  
  #pragma omp parallel for collapse(2)
  for(i=0;i<N;++i){
    for(j=0;j<N;++j){
      if(i==0||j==0||i==N-1||j==N-1) {
	psi[i][j]=zero;
	psi1[i][j]=zero;
	psi2[i][j]=zero;
      }
      else {
	psi[i][j]=c(1./((N-2.)*h))*one;
	psi1[i][j]=c(1./((N-2.)*h))*one;
	psi2[i][j]=c(1./((N-2.)*h))*one;
      }
    }
  }
  ofstream out("../../data3c");
  for(i=1;i<N-1;++i){
    for(j=1;j<N-1;++j){
      out << -L+i*h << "\t" << -L+j*h << "\t" << mod(psi[i][j])*mod(psi[i][j]) << endl;
    }
  }
  clock_t t=clock();
  double v=cpf;
  int pop=v/cpf;
  sum=0;
  for(n=0;n<nmax;n++){
    if(!(n%cpf)){
      out.open("../../data3a");  // abertura do ficheiro de escrita de dados
      ofstream script("../../script3a");  //  criacao do script 
      script << "set term png" << endl;
      script << "set output \"../../frame" << n/cpf << ".png\"" << endl;
      script << "set title \"t = " << (int)(n*dt) << "\"" << endl;
      script << "set xrange [-10:10]" << endl;
      script << "set yrange [-10:10]" << endl;
      script << "set cbrange [0:*]" << endl;
      script << "set size square" << endl;
      script << "set xlabel \"x\"" << endl;
      script << "set ylabel \"y\"" << endl;
      script << "set clabel \"psi*(psi*)\"" << endl;
      script << "plot \"../../data3a\" using 1:2:3 notitle w p pt 7 ps 2 lt palette" << endl;
      script.close();	
    }
    #pragma omp parallel for collapse(2)
    for(int i=1;i<N-1;++i){   //  implementacao do metodo
      for(int j=1;j<N-1;++j){
	psi1[i][j]=psi[i][j]+c(dt)*F(psi[i+1][j],psi[i-1][j],psi[i][j+1],psi[i][j-1],psi[i][j],i,j);
      }
    }
    
    #pragma omp parallel for collapse(2)
    for(int i=1;i<N-1;++i){
      for(int j=1;j<N-1;++j){
	psi2[i][j]=c(0.75)*psi[i][j]+c(0.25)*psi1[i][j]+c(0.25*dt)*F(psi1[i+1][j],psi1[i-1][j],psi1[i][j+1],psi1[i][j-1],psi1[i][j],i,j);
      }
    }
    
    #pragma omp parallel for collapse(2)
    for(int i=1;i<N-1;++i){
      for(int j=1;j<N-1;++j){
	psi[i][j]=c(1.0/3.)*psi[i][j]+c(2.0/3.)*psi2[i][j]+c((2.0/3.)*dt)*F(psi2[i+1][j],psi2[i-1][j],psi2[i][j+1],psi2[i][j-1],psi2[i][j],i,j);
      }
    }
    sum=0.;
    
    #pragma omp parallel for collapse(2) reduction(+:sum) 
    for(int i=1;i<N-1;++i){  //calculo de N para a normalizacao
      for(int j=1;j<N-1;++j){
	sum+=h*h*mod(psi[i][j])*mod(psi[i][j]);
      }
    }
		
		#pragma omp parallel for collapse(2)
    for(int i=1;i<N-1;++i){  //normalizacao
      for(int j=1;j<N-1;++j){
	psi[i][j] = psi[i][j]/c(sqrt(sum));		
      }
    }
		
    if(!(n%cpf)){
      for(i=1;i<N-1;++i){
	for(j=1;j<N-1;++j){		//escrita no ficheiro de dados
	  out << -L+i*h << "\t" << -L+j*h << "\t" << mod(psi[i][j])*mod(psi[i][j]) << endl;
	}
      }
      out.close();  //fecho do ficheiro de escrita de dados
      if(!system("gnuplot ../../script3a &"))  //criacao do frame
	if(!(n%(pop*cpf))){                     //  progress bar
	  v=((double)pop*cpf)/(((double)clock()-(double)t)/CLOCKS_PER_SEC);
	  if(v==0) v=1.;
	  cout << "\r" << n*100./nmax << "%    " << "f = " << v << " cyc/sec    ETA = " << (int)((((double)nmax-(double)n)/v)/60.) << "min  " << (int)(((double)nmax-(double)n)/v)-60*(int)((((double)nmax-(double)n)/v)/60.) << " sec              ";					
	  cout << "\n[ ";
	  for(i=0;i<100*n/nmax;++i) cout << "█";
	  for(i=0;i<100-100*n/nmax;++i) cout << " ";
	  cout << "]";
	  cout  << flush;
	  cout << "\e[A\r";			
	}
    }
    if(!(n%(pop*cpf))){
      t=clock();
      if(v<100.)
	pop=((int)v)/cpf;
      if(pop==0) pop=1;
    }
		
  }
  
  
  #pragma omp parallel for private(i)
  for(i=0;i<N;++i){   // libertacao memoria
    delete [] psi[i];
    delete [] psi1[i];
    delete [] psi2[i];
  }
  
  delete [] psi;
  delete [] psi1;
  delete [] psi2;
  cout << "\n" << endl;
  string compile = "avconv  -r " + sfps + " -i " + "../../frame\%d.png -r " + sfps + " " + name + ".mp4";           //  compilacao video
  char * cstring = new char[compile.length()+1];
  strcpy(cstring,compile.c_str());
	
  string video = "totem " + name + ".mp4 &";
  char * cvideo = new char[video.length()+1];
  strcpy(cvideo,video.c_str());
		
  if(!system(cstring)){   
    if(!system("rm ../../frame*.png")){  // eliminacao frames apos render do video

			return 0;


    }
  }
  else return 1;
}
