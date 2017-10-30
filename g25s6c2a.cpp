#include "compz.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

int main(void)
{
  double re1, im1, re2, im2;
  //Complex c;

  cout << "complexo c1" << endl << "real(c1) = ";
  cin >> re1;
  cout << "im(c1) = ";
  cin >> im1;

  Complex c1(re1, im1);//inicializacao do complexo1

  cout << "mod(" << c1 << ") = " << mod(c1) << endl; //modulo ou valor absoluto
  cout << "arg(" << c1 << ") = " << arg(c1) << endl; //argumento
  cout << "conjugado(" << c1 << ") = " << conj(c1) << endl; //conjugado
  cout << "exp(" << c1 << ") = " << exp(c1) << endl; //exponencial
  cout << "log(" << c1 << ") = " << log(c1) << endl; //logaritmo
  cout << "sqrt(" << c1 << ") = " << sqrt(c1) << endl; //raiz quadrada

  cout << endl << "complexo c2" << endl << "real(c2) = ";
  cin >> re2;
  cout << "im(c2) = ";
  cin >> im2;

  Complex c2(re2, im2);//inicializacao do complexo2




  cout << "mod(" << c2 << ") = " << mod(c2) << endl;
  cout << "arg(" << c2 << ") = " << arg(c2) << endl;
  cout << "conjugado(" << c2 << ") = " << conj(c2) << endl; //conjugado
  cout << "exp(" << c2 << ") = " << exp(c2) << endl; //exponencial
  cout << "log(" << c2 << ") = " << log(c2) << endl; //logaritmo
  cout << "sqrt(" << c2 << ") = " << sqrt(c2) << endl; //raiz quadrada

  cout << endl << "soma: "<< c1 <<" + "<< c2 <<" = " << c1+c2 << endl; //soma

  cout << "diferenca: "<< c1 <<" - ("<< c2 <<") = " << c1-c2 << endl; //subtracao
  cout << "\t "<< c2 <<" - ("<< c1 <<") = " << c2-c1 << endl;

  cout << "produto: ("<< c1 <<") * ("<< c2 <<") = " << c1*c2 << endl; //produto

  cout << "divisao: ("<< c1 <<") / ("<< c2 <<") = " << c1/c2 << endl; //divisao
  cout << "\t ("<< c2 <<") / ("<< c1 <<") = " << c2/c1 << endl;

  return 0;
}
