#pragma once
#include<vector>
#include<math.h>

using namespace std;

template <int B>
class IntegerPolynom
{
public:
	IntegerPolynom(vector<int> const& x);											//Konstruktor mit Vector
	IntegerPolynom(int x[]);														//Konstruktor mit Array
	IntegerPolynom(vector<BadicRepresentation<B>> const& xb);						//Konstruktor mit B-adischen Darstellungen 
	~IntegerPolynom();																//Destruktor 
	BadicRepresentation<B> operator()(int i) const;									//Zugriffsoperator auf Koeffizienten
	vector<BadicRepresentation<B>> coefficient;										//Array der Koeffizienten des Polynoms
	BadicRepresentation<B> lp;														//Leitkoeffizient des Polynoms
	int deg;																		//Grad des Polynoms
};


/*
Konstruktor - IntegerPolynom(vector<int> x)
Input: Vektor ganzer Zahlen x
Output: x als Koeffizienten eines Polynoms der Klasse IntegerPolynom
Beispiel:	vector<int> x {19,0,12};
			IntegerPolynom f(x); //f(X)=19X^2+12
*/
template <int B>
IntegerPolynom<B>::IntegerPolynom(vector<int> const& x)
{
	for (unsigned int i = 0; i <= x.size()-1; i++){			
		coefficient.push_back(BadicRepresentation<B>(x[i]));	//setzte Koeffizienten auf die ArrayWerte
	}
	deg = coefficient.size() - 1;								//passe Polynomgrad an
	lp = coefficient.at(deg);									//passe Leitkoeffizienten an
	
}


/*
Konstruktor - IntegerPolynom(vector<BadicRepresentation<B>> xb)
Input: Vektor ganzer Zahlen x in B-adischer Darstellung
Output: xb als Koeffizienten eines Polynoms der Klasse IntegerPolynom
Beispiel:	vector<BadicRepresentation<B>> x;
			IntegerPolynom f(x);
*/
template <int B>
IntegerPolynom<B>::IntegerPolynom(vector<BadicRepresentation<B>> const& x)
{
	coefficient = x;				//übernehme Koeffizienten
	deg = coefficient.size() - 1;   //passe Polynomgrad an
	lp = coefficient.at(deg);		//passe Leitkoeffizienten an
}

/*
Destruktor - ~IntegerPolynom()
Input: Instanz der Klasse IntegerPolynom
Output: Instanz wurde gelöscht
Beispiel: delete f;
*/
template <int B>
IntegerPolynom<B>::~IntegerPolynom()
{
}


/*
Zugriffsoperator auf Koeffizienten - operator()(int i) 
Input: Instanz der Klasse IntegerPolynom und Index i
Output: Koeffzizient des Polynoms am Index i
Beispiel: BadicRepresentation<B> koeff = x(i);
*/
template <int B>
BadicRepresentation<B> IntegerPolynom<B>::operator()(int i) const
{
	if (i < 0 || i >= coefficient.size()){		//Falls Index nicht im Koeffizientenvektor vertreten ist
		return BadicRepresentation<B>(0);		//gebe 0 zurück
	}
	else{
		return coefficient.at(i);				//ansonsten den Koeffizienten des Polynoms am Index i
	}
}

/*
Überladung des Ausgabeoperators << - operator<<(ostream& os, const IntegerPolynom& f)
Input: Instanz der Klasse IntegerPolynom
Output: Ausgabe der Koeffizienten dieser Instanz
Beispiel: std::cout << f << endl;
*/
template <int B>
ostream& operator<<(ostream& os, const IntegerPolynom<B>& f)
{
	for (unsigned int i = 0; i <= f.deg; i++){	//nehme Koeffizient des Polynoms und die Variablenpotenz auf
		os << "(" << f.coefficient.at(i) << ")" << " X^" << i; 
		if (i < f.coefficient.size() - 1) { os << " + "; }
	}
	return os;	//gebe entstandenen Stream zurück
}