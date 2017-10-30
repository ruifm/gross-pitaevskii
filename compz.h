#include <cstdlib> 
#include <cmath>
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <omp.h>

using namespace std;

class Complex { 
 public: //variaveis publicas
  float re; //parte rea
  float im; //parte imaginaria
  explicit Complex(); 
  explicit Complex(float _re,float _im); // construcao explicita
  Complex(const Complex& comp); //construtor por copia
  Complex& operator=(const Complex& c);
  friend ostream& operator<<( ostream& out, const  Complex& c);
  friend istream& operator>>( istream& in, Complex& c);
};
float mod(const Complex& c); //modulo
Complex operator+(const Complex& c1, const Complex& c2); //soma
Complex operator-(const Complex& c1, const Complex& c2); //subtracao
Complex operator*(const Complex& c1, const Complex& c2); //produto
Complex operator/(const Complex& c1, const Complex& c2); //divisao
Complex c(float k);
Complex conj(const Complex& c);
float arg(const Complex& z);
Complex polar(const float r,const float t);
Complex exp(const Complex& z);
Complex cos(const Complex& z);
Complex sin(const Complex& z);
Complex tan(const Complex& z);
Complex sinh(const Complex& z);
Complex cosh(const Complex& z);
Complex tanh(const Complex& z);
Complex log(const Complex& z);
Complex sqrt(const Complex& z);
Complex pow(const Complex& a,const Complex& b);
//Complex random(float re,float im);
//size_t operator==(Complex& c1, Complex& c2);
//float operator!=(Complex& c1, Complex& c2);
