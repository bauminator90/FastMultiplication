#pragma once
using namespace std;

/*
Gewöhnliche Addition von Polynomen - FundamentalAddPoly(IntegerPolynom<B> f,IntegerPolynom<B> g)
Input: Zwei Instanzen der Klasse IntegerPolynom f,g
Output:	Eine Instanz der Klasse IntegerPolynom, welche das Polynom repräsentiert, welches durch Summe von f und g entsteht
Beispiel: h=FundamentalAddPoly<B>(f,g);
*/
template <int B>
IntegerPolynom<B> FundamentalAddPoly(IntegerPolynom<B> const& f, IntegerPolynom<B> const& g)
{
	//Drehe notfalls Eingabe
	if (g.deg > f.deg){
		return FundamentalAddPoly(g,f);
	}

	//Erstelle Koeffizientenvektor
	vector<BadicRepresentation<B>> coeff=g.coefficient;

	//Fülle diesen mit Nullen, damit Addition durchgeführt werden kann
	if (g.deg < f.deg){
		for (unsigned int i = g.deg; i < f.deg; i++){
			coeff.push_back(0);
		}
	}

	//Addiere Koeffizienten
	for (unsigned int k = 0; k <= f.deg; k++){
		coeff.at(k) = FundamentalAdd(f.coefficient.at(k), coeff.at(k));
	}

	//Gebe entstandene Koeffizienten als Polynom zurück
	IntegerPolynom<B> z(coeff);
	return z;
}


/*
Gewöhnliche Subtraktion von Polynomen - FundamentalSubtractPoly(IntegerPolynom<B> f,IntegerPolynom<B> g)
Input: Zwei Instanzen der Klasse IntegerPolynom f,g
Output:	Eine Instanz der Klasse IntegerPolynom, welche das Polynom repräsentiert, welches durch Subtraktion von f und g entsteht
Beispiel: h=FundamentalSubtractPoly<B>(f,g);
*/
template <int B>
IntegerPolynom<B> FundamentalSubtractPoly(IntegerPolynom<B> const& f, IntegerPolynom<B> const& g)
{
	//Erstelle Koeffizientenvektor
	vector<BadicRepresentation<B>> coeff;

	//Passe Vektor so an, dass Subtraktion durchgeführt werden kann und führe Subtraktion durch
	if (g.deg <= f.deg){
		coeff = g.coefficient;
		for (unsigned int i = g.deg; i < f.deg; i++){
			coeff.push_back(0);
		}
		
		//Subtrahiere Koeffizienten
		for (unsigned int k = 0; k <= f.deg; k++){
			coeff.at(k) = FundamentalSubtract(f.coefficient.at(k), coeff.at(k));
		}
	}

	if (g.deg > f.deg){
		coeff = f.coefficient;
		for (unsigned int i = f.deg; i < g.deg; i++){
			coeff.push_back(0);
		}

		//Subtrahiere Koeffizienten
		for (unsigned int k = 0; k <= g.deg; k++){
			coeff.at(k) = FundamentalSubtract(coeff.at(k), g.coefficient.at(k));
		}
	}

	//Gebe entstandene Koeffizienten als Polynom zurück
	IntegerPolynom<B> z(coeff);
	return z;
}


/*
Gewöhnliche Multiplikation von Polynomen - FundamentalMultiplyPoly(IntegerPolynom<B> f,IntegerPolynom<B> g)
Input: Zwei Instanzen der Klasse IntegerPolynom f,g
Output:	Eine Instanz der Klasse IntegerPolynom, welche das Polynom repräsentiert, welches durch Multiplikation von f und g entsteht
Beispiel: h=FundamentalMultiplyPoly<B>(f,g)
*/
template <int B>
IntegerPolynom<B> FundamentalMultiplyPoly(IntegerPolynom<B> const& f, IntegerPolynom<B> const& g)
{
	//Erstelle Koeffizientenvektor
	vector<BadicRepresentation<B>> coeff(f.deg+g.deg+1);
	
	//Führe eigentliche Multiplikation durch
	for (unsigned int i = 0; i <= f.deg; i++){
		for (unsigned int j = 0; j <= g.deg; j++){
			if (coeff.at(i + j).IntRepresentation()==0 ){
				coeff.at(i + j) = FundamentalMultiply(f.coefficient.at(i), g.coefficient.at(j));
			}
			else {
				coeff.at(i + j) = FundamentalAdd(coeff.at(i + j), FundamentalMultiply(f.coefficient.at(i), g.coefficient.at(j)));
			}
		}
	}

	//Gebe entstandene Koeffizienten als Polynom zurück
	IntegerPolynom<B> z(coeff);
	return z;	
}

