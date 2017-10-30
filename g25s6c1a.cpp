#include <iostream>
#include <complex> //numeros complexos
#include <cstdlib>
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include <fstream>

using namespace std;

void printLists (const list<int>& l1, const list<int>& l2)
{
    cout << "list1: ";
    copy (l1.begin(), l1.end(), ostream_iterator<int>(cout," "));
    cout << endl << "list2: ";
    copy (l2.begin(), l2.end(), ostream_iterator<int>(cout," "));
    cout << endl << endl;
}

int main(void)
{
  double re, im, re2, im2;
  

  cout << "complexo c1" << endl << "real(c1) = ";
  cin >> re;
  cout << "im(c1) = ";
  cin >> im;

  complex<double> c(re, im);

  cout << "abs" << c << " = " << abs(c) << endl;
  cout << "exp" << c << " = " << exp(c) << endl;
  cout << "conj" << c << " = " << conj(c) << endl;
  cout << "log" << c << " = " << log(c) << endl;
  cout << "norma" << c << " = " << norm(c) << endl;
  cout << "sqrt" << c << " = " << sqrt(c) << endl;

  cout << endl << "complexo c2" << endl << "real(c2) = ";
  cin >> re2;
  cout << "im(c2) = ";
  cin >> im2;

  complex<double> c2(re2, im2);

  cout << "Abs" << c2 << " = " << abs(c2) << endl;
  cout << "Exp" << c2 << " = " << exp(c2) << endl;
  cout << "Conj" << c2 << " = " << conj(c2) << endl;
  cout << "log" << c2 << " = " << log(c2) << endl;
  cout << "Norma" << c2 << " = " << norm(c2) << endl;
  cout << "sqrt" << c2 << " = " << sqrt(c2) << endl;

  cout << endl << "soma: " << c << " + " << c2 << " = " << c+c2 << endl; //soma

  cout << "diferenca: "<< c <<" - "<< c2 <<" = " << c-c2 << endl; //subtracao
  cout << "\t "<< c2 <<" - "<< c <<" = " << c2-c << endl;

  cout << "produto: "<< c <<" * "<< c2 <<" = " << c*c2 << endl; //produto

  cout << "divisao: "<< c <<" / "<< c2 <<" = " << c/c2 << endl; //divisao
  cout << "\t "<< c2 <<" / "<< c <<" = " << c2/c << endl;

	cout << endl << "Uso de containers: LIST" << endl;
    
    list<int> l1, l2; // criacao de duas listas

    for (int i=0; i<6; ++i) {  //preenchimento das listas
        l1.push_back(i);
        l2.push_front(i);
    }
    printLists(l1, l2);

    // o primeiro elemento passa para o fim
    l2.splice(l2.end(),        // destino
                 l2,              // lista da fonte
                 l2.begin());     // posicao da fonte
    printLists(l1, l2);

   // juncao das duas listas na primeira
   l1.merge(l2);
   printLists(l1, l2);
	
  return 0;
}
