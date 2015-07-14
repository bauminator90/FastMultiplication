#pragma once
#include<vector>
#include<math.h>

using namespace std;

template<int B>
class BadicRepresentation
{
public:
	BadicRepresentation(int x = 0);				//Konstruktor mit Defaultparameter x=0
	BadicRepresentation(vector<int> const& x);	//Konstruktor 
	~BadicRepresentation();						//Destruktor 
	vector<int> data;							//Array der Koeffizienten der B-adischen Darstellung
	int sgn = 0;								//Vorzeichen der dargestellten Zahl
	int IntRepresentation();					//gibt den Zahlwert der B-adischen Entwicklung zur�ck
	BadicRepresentation<B> operator% (BadicRepresentation<B> const& b) const;	//modulo Operator f�r zwei B-adisch entwickelte ganze Zahlen
	bool operator< (BadicRepresentation<B> const& b);	//Vergleichsoperator f�r zwei B-adisch entwickelte ganze Zahlen
};


/*
Konstruktor - BadicRepresentation(int x)
Input: ganze Zahl x, falls kein Input x=0
Output: x als Instanz der Klasse BadicRepresentation
Beispiel: BadicRepresentation<10> xb(100);
*/
template <int B>
BadicRepresentation<B>::BadicRepresentation(int x)
{
	if (x < 0) {x = -x; sgn = 1; }	//falls ganze Zahl vorliegt, setze Vorzeichen auf 1 und f�hre restlichen Algorithmus mit dem Betrag der Zahl aus
	if (x < B){						
		data.push_back(x);			//falls x bereits zwischen 0 und B-1 liegt �bernehme x als Koeffizienten
	}
	else {							//ansonsten
		while (x>=B){				
			int y = x / B;			
			data.push_back(x-y*B);	//ziehe gr��tm�glichstes Vielfaches von B von x ab und �bernehme dies als Koeffizienten
			x = y;					//verfahre danach analog mit dem Ergebnis der Subtraktion
		}
		data.push_back(x);			
	}
}


/*
Konstruktor - BadicRepresentation(vector<int> const& x)
Input: Vektor x ganzer Zahlen 
Output: x als Instanz der Klasse BadicRepresentation
Beispiel: BadicRepresentation<10> xb({100,10,2});
*/
template <int B>
BadicRepresentation<B>::BadicRepresentation(vector<int> const& x)
{
	for (unsigned int i = 0; i < x.size(); i++){	//�berpr�fe Eingabe
		if (x.at(i) >= B){
			throw runtime_error("Falsche Eingabe");
		}
	}
	data = x;										
	vector<int> data2(data.rbegin(), data.rend());	//drehe Eingabevektor
	data = data2;									//setze Daten entsprechend der Eingabe
}

/*
Destruktor - ~BadicRepresentation()
Input: Instanz der Klasse BadicRepresentation
Output: Instanz wurde gel�scht
Beispiel: delete xb;
*/
template <int B>
BadicRepresentation<B>::~BadicRepresentation()
{
}


/*
Zahlwert der B-adischen Repr�sentation - IntRepresentation()
Input: 
Output: Zahlwert der Instanz der Klasse BadicRepresentation
Beispiel: xb.IntRepresentation();
*/
template <int B>
int BadicRepresentation<B>::IntRepresentation()
{
	long ret=0;
	for (unsigned int i = 0; i <= data.size() - 1; i++){	//Summiert f�r jeden Koeffizienten
		ret = ret + data.at(i)*pow(B,i);					//Koeffizient * Potenz der Basis B
	}
	if (sgn == 1) { return -ret; }							//falls Vorzeichen der B-adischen Entwicklung =1, gebe negativen Zahlwert zur�ck
	else { return ret; }									//ansonsten gebe positiven Zahlwert zur�ck
}


/*
Vergleichsoperator B-adischer Repr�sentationen - <
Input: eine weitere ganze Zahl b in B-adischer Entwicklung
Output: Wahrheitswert TRUE oder FALSE
Beispiel: if (x < b){...}
*/
template <int B>
bool BadicRepresentation<B>::operator< (BadicRepresentation<B> const& b)
{
	if (b.data.size() == 1 && b.data.at(0) == 0 && data.size() == 1 && data.at(0) == 0) { return false; } //Fall: beide Zahlen sind 0
	if (sgn == b.sgn){												//bei gleichem Vorzeichen
		if (sgn == 0){												//und positiven Zahlen
			if (data.size() < b.data.size()){ return true; }		//Falls der Koeffizientenarray kleiner ist als der der anderen Zahl, gebe TRUE zur�ck
			else if (data.size() > b.data.size()) { return false; }	//Falls umgekehrtes gilt, gebe FALSE zur�ck
			else {													//bei gleich gro�en Koeffizientenarrays:
				for (int i = b.data.size() - 1; i >= 0; i--){
					if (data.at(i)>b.data.at(i)) { return false; }	//Vergleiche vom h�chsten Koeffizienten an
					else if (data.at(i)<b.data.at(i)) { return true; }
				}
				return false;
			}
		}
		else {														//bei negativen Zahlen verfahre gegens�tzlich
			if (data.size() < b.data.size()){ return false; }
			else if (data.size() > b.data.size()) { return true; }
			else {
				for (int i = b.data.size() - 1; i >= 0; i--){
					if (data.at(i)>b.data.at(i)) { return true; }
					else if (data.at(i)<b.data.at(i)) { return false; }
				}
				return true;
			}
		}
	}
	else{															//bei unterschiedlichem Vorzeichen
		if (sgn == 1) { return true; }								//gebe TRUE zur�ck wenn negative Zahl mit positiver verglichen wird
		else { return false; }										//gebe im anderen Fall FALSE zur�ck
	}
}


/*
Modulo-Operator f�r zwei B-adische Repr�sentationen - %
Input: eine weitere ganze Zahl b in B-adischer Entwicklung
Output: B-adische Entwicklung des Divisionsrestes
Beispiel: BadicRepresetation<B> r = x % b;
*/
template <int B>
BadicRepresentation<B> BadicRepresentation<B>::operator% (BadicRepresentation<B> const& b) const
{
	vector<BadicRepresentation<B>> division;			//erstelle neuen Koeffizientenvektor
	division = FundamentalDivision(*this, b);			//f�hre gew�hnliche Division durch
	if (division.at(1) < BadicRepresentation<B>(0)){ return FundamentalAdd(division.at(1), b); }	//passe R�ckgabewert an, falls dieser negativ ist
	else { return division.at(1); }						//ansonsten gebe Divisionsrest direkt zur�ck
}


/*
Potenzierung einer B-adischen Entwicklung - pow(BadicRepresentation<B> const& a, int n)
Input: eine ganze Zahl a in B-adischer Entwicklung, der Exponent n als ganze Zahl
Output: B-adische Entwicklung der Potenz a^n
Beispiel: BadicRepresentation<B> potenz = pow(a,4);
*/
template <int B>
BadicRepresentation<B> pow(BadicRepresentation<B> const& a, int n)
{
	if (n == 0){ return BadicRepresentation<B>(1); }		//Falls n=0 ist, so ist das Ergebnis 1
	else if (n < 0){										//Falls n negativ ist
		throw runtime_error("Falsche Eingabe");				//so wurde eine falsche Eingabe get�tigt
	}
	else{													//Falls n>0 ist
		BadicRepresentation<B> p = pow(a, (n / 2));			//F�hre die Potenz mit halbem Exponenten durch
		if (n % 2 == 0){									//Falls die urspr�ngliche Potenz gerade ist
			return FundamentalMultiply(p, p);				//gebe das Quadrat der neuen Basis zur�ck
		}
		else{
			return FundamentalMultiply(a,FundamentalMultiply(p, p));	//ansonsten multipliziere zus�tzlich den Eingabewert a hinzu
		}
	}
}

/*
�berladung des Ausgabeoperators << - operator<<(ostream& os, const BadicRepresentation<B>& b)
Input: Instanz der Klasse BadicRepresentation
Output: Ausgabe der B-adischen Repr�sentation dieser Instanz
Beispiel: std::cout << xb << endl;
*/
template <int B>
ostream& operator<<(ostream& os, const BadicRepresentation<B>& b)
{
	os << "(-1)^" << b.sgn << "* (";						//nehme Vorzeichen auf
	for (unsigned int i = 0; i <= b.data.size() - 1; i++){	//nehme einzelne Koeffizienten mit der passenden Basispotenz auf
		os << b.data.at(i) << "*" << B << "^" << i;
		if (i < b.data.size() - 1) { os << " + "; }
		else { os << ")"; }
	}
	return os;												//gebe entstandenen Stream zur�ck
}


/*
�berladung des Ausgabeoperators << f�r B=10 - operator<<(ostream& os, const BadicRepresentation<10>& b)
Input: Instanz der Klasse BadicRepresentation mit B=10
Output: Ausgabe der 10-adischen Repr�sentation dieser Instanz
Beispiel: std::cout << xb << endl;
*/
ostream& operator<<(ostream& os, const BadicRepresentation<10>& b)
{
	if (b.sgn == 1){ os << "-"; }							//nehme Vorzeichen auf
	for (unsigned int i = 0; i <= b.data.size() - 1; i++){	//nehme einzelne Koeffizienten mit der passenden Zehnerpotenz auf
		os << b.data.at(b.data.size()-i-1);
	}
	return os;												//gebe entstandenen Stream zur�ck
}


/*
Vergleich der Absolutbetr�ge zweier B-adischer Entwicklungen - abslower(BadicRepresentation<B> x, BadicRepresentation<B> y)
Input: zwei Instanzen x und y der Klasse BadicRepresentation
Output: Wahrheitswert, ob x im Betrag kleiner ist als y oder nicht
Beispiel: bool kleiner = abslower(x,y);
*/
template <int B>
bool abslower(BadicRepresentation<B> x, BadicRepresentation<B> y){
	if (x.data.size() < y.data.size()){ return true; }				//Falls x weniger Koeffizienten hat als y, gebe TRUE zur�ck
	else if (x.data.size() > y.data.size()) { return false; }		//Falls y weniger Koeffizienten hat, gebe FALSE zur�ck
	else {															//Falls beide gleich viele Koeffizienten haben
		for (int i = y.data.size() - 1; i >= 0; i--){				//gehe einzelne Koeffizienten durch und gebe passendes zur�ck
			if (x.data.at(i) > y.data.at(i)) { return false; }
			else if (x.data.at(i) < y.data.at(i)) { return true; }
		}
		return false;
	}
}