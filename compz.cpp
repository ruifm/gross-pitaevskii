#include "compz.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <omp.h>

using namespace std;

Complex::Complex(){}

Complex::Complex(float _re,float _im) : re(_re) , im(_im) {}

Complex::Complex(const Complex& comp) : re(comp.re) , im(comp.im) {} //construtor por copia

//Complex::~Complex() { delete &re; delete &im;}

//Complex::~Complex() { delete &c}

Complex& Complex::operator=(const Complex& c){
  Complex temp(c);
  swap(re,temp.re);
  swap(im,temp.im);
  return *this;
}
ostream& operator<<( ostream& out, const  Complex& c) {
  if (c.im < 0) out << c.re << c.im << "i";
  else out << c.re << " +" << c.im << "i";
  return out;
}

istream& operator>>( istream& in, Complex& c) {
  in >> c.re;
  in >> c.im;
  return in;
}

float mod(const Complex& c){  //modulo
  return sqrt(c.re*c.re+c.im*c.im);
}

Complex operator+(const Complex& c1, const Complex& c2) {  //soma 
  float real, imag;
  real=c1.re+c2.re;
  imag=c1.im+c2.im;
  Complex plus(real, imag);
  return plus;
}

Complex operator-(const Complex& c1, const Complex& c2) {  //subtracao
  float real, imag;
  real=c1.re-c2.re;
  imag=c1.im-c2.im;
  Complex sub(real, imag);
  return sub;
}
 
Complex operator*(const Complex& c1, const Complex& c2) {  //produto
  float real, imag;
  real=c1.re*c2.re - c1.im*c2.im;
  imag=c1.re*c2.im + c1.im*c2.re;
  Complex prod(real, imag);
  return prod;
}

Complex conj(const Complex& c) { //conjugado
  float real, imag;
  real=c.re;
  imag=c.im;
  Complex conju(real, -imag);
  return conju;
}

Complex c(float k){  //real
  Complex res(k,0.);
  return res;
}    

Complex operator/(const Complex& c1, const Complex& c2) {  //divisao
  return c(1./(mod(c2)*mod(c2)))*c1*conj(c2);
}

float arg(const Complex& z){  //argumento do complexo
  if(z.re)
    return atan(z.im/z.re);
  else {
    if(z.im>0){
      return M_PI/2.;
    }
    if(z.im<0){
      return -M_PI/2.;
    }
    if(z.im==0) return 0;
    else return 0;
  }
}

Complex polar(float r,float t){  // complexo na forma polar 
  Complex z(r*cos(t),r*sin(t));
  return z;
}      

Complex exp(const Complex& z){  // exponencial
  return polar(exp(-z.im),z.re);
}

Complex cos(const Complex& z){  //cosseno
  Complex i(0,1);
  return c(0.5)*(exp(i*z)+exp(c(-1.)*i*z));
}

Complex sin(const Complex& z){  //seno
  Complex i(0,1);
  return c(0.5*(-1.))*i*(exp(i*z)-exp(c(-1.)*i*z));
}

Complex tan(const Complex& z){  //tangente
  return sin(z)/cos(z);
}

Complex sinh(const Complex& z){  //seno hiperbolico
  Complex i(0,1);
  return sin(i*z);
}

Complex cosh(const Complex& z){  //cosseno hiperbolico
  Complex i(0,1);
  return cos(i*z);
}

Complex tanh(const Complex& z){  //tangente hiperbolica
  Complex i(0,1);
  return tan(i*z);
}

Complex log(const Complex& z){  //logaritmo
  Complex res(log(mod(z)),arg(z));
  return res;
}

Complex sqrt(const Complex& z){	  //raiz quadrada
  return polar(sqrt(mod(z)),arg(z));
}

Complex pow(const Complex& a,const Complex& b){  //potencia
  return exp(b*log(a));
}
