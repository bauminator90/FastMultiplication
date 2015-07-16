#pragma once
#include<vector>
#include<math.h>
#include<algorithm>
#include"Polynome.h"
#include"BadischeEntwicklung.h"

using namespace std;

/*
Quadrierung der n-ten Einheitswurzeln in einem Vektor - zetaquad(vector<BadicRepresentation<B>> zeta)
Input: Vektor ganzer Zahlen (Einheitswurzeln) in B-adischer Entwicklung
Output: Vektor der Quadrate in B-adischer Entwicklung
Beispiel:	vector<BadicRepresentation<B>> quad = zetaquad(zeta) ;
*/
template <int B>
vector<BadicRepresentation<B>> zetaquad(vector<BadicRepresentation<B>> zeta){
	//Erstelle neuen Vektor
	vector<BadicRepresentation<B>> zeta2;
	int n = zeta.size();
	//Permutiere die Einträge passend für den neuen Vektor
	for (unsigned int i = 0; i < n; i++){
		zeta2.push_back(zeta.at((2*i)%n));
	}
	//gebe den entstandenen Vektor zurück
	return zeta2;
}


/*
Invertierung der n-ten Einheitswurzeln in einem Vektor - zetainv(vector<BadicRepresentation<B>> zeta)
Input: Vektor ganzer Zahlen (Einheitswurzeln) in B-adischer Entwicklung
Output: Vektor der invertierten Einheitswurzeln in B-adischer Entwicklung
Beispiel:	vector<BadicRepresentation<B>> inv = zetainv(zeta) ;
*/
template <int B>
vector<BadicRepresentation<B>> zetainv(vector<BadicRepresentation<B>> zeta){
	//Erstelle neuen Vektor
	vector<BadicRepresentation<B>> zetai;
	int n = zeta.size();
	//Permutiere die Einträge passend für den neuen Vektor
	for (unsigned int i = 0; i < n; i++){
		zetai.push_back(zeta.at(((-1 * i) + n) % n));
	}
	//gebe den entstandenen Vektor zurück
	return zetai;
}


/*
Anpassung der Basis für die schnelle Multiplikation - FindBnew(int r)
Input: ganze Zahl r
Output: 2^r in 2-adischer Entwicklung
Beispiel:	BadicRepresentation<2> B_new = FindBnew(5);
*/
BadicRepresentation<2> FindBnew(int r){
	//Erstelle neue 2-adische Entwicklung
	BadicRepresentation<2> B_new;
	//Füge r-1 Nullen an
	for (unsigned int i = 0; i < r - 1; i++){
		B_new.data.push_back(0);
	}
	//füge eine 1 an
	B_new.data.push_back(1);
	//gebe die entstandene 2-adische Entwicklung zurück
	return B_new;
}


/*
Schnelle Fouriertransformierung - FastdFT(IntegerPolynom<B> const& f, int n, vector<BadicRepresentation<B>> const& zeta)
Input: Polynom f mit ganzen Zahlen als Koeffizienten, ganze Zahl n (Zweierpotenz größer als der Grad von f), Vektor mit Einheitswurzeln in B-adischer Entwicklung
Output: Vektor der Auswertungen von f an den Einheitswurzeln in B-adischer Entwicklung
Beispiel:	vector<BadicRepresentation<B>> auswertung = FastdFT(f,16,zeta);
*/
template <int B>
vector<BadicRepresentation<B>> FastdFT(IntegerPolynom<B> const& f, int n, vector<BadicRepresentation<B>> const& zeta){
	//Falls der Grad von f Null ist
	if (n == 1) { 
		//gebe den Koeffizienten am Index 0 zurück
		vector<BadicRepresentation<B>> ret;
		ret.push_back(f.coefficient.at(0)); 
		return ret;
	}
	//Falls der Grad von f höher ist
	else {
		//Befülle die Polynome r0 und r1
		vector<BadicRepresentation<B>> r0_coeff;
		vector<BadicRepresentation<B>> r1_coeff;
		for (unsigned int i = 0; i <= (n / 2) - 1; i++){
			r0_coeff.push_back(FundamentalAdd(f(i), f(i + (n / 2))));
			r1_coeff.push_back(FundamentalMultiply(FundamentalSubtract(f(i), f(i + (n / 2))),zeta.at(i)));
		}
		IntegerPolynom<B> r0(r0_coeff);
		IntegerPolynom<B> r1(r1_coeff);
		//führe die Fouriertransformation für r0 und r1 durch
		r0_coeff = FastdFT(r0, (n / 2), zetaquad(zeta));
		r1_coeff = FastdFT(r1, (n / 2), zetaquad(zeta));
		//befülle den Rückgabevektor
		vector<BadicRepresentation<B>> ret;
		for (unsigned int j = 0; j < r0_coeff.size(); j++){
			ret.push_back(r0_coeff.at(j));
			ret.push_back(r1_coeff.at(j));
		}
		//gebe den Rückgabevektor zurück
		return ret;
	}
}


/*
Schnelle Multiplikation für Polynome - FastMultiplyPoly(IntegerPolynom<B> const& f, IntegerPolynom<B> const& g, int n, vector<BadicRepresentation<B>> const& zeta)
Input: zwei Polynome f und g mit ganzzahligen Koeffizienten, ganze Zahl n (2er-Potenz größer als die Summe der Polynomgrade), Vektor mit Einheitswurzeln in B-adischer Entwicklung 
Output: h=f*g als Polynom mit ganzzahligen Koeffizienten
Beispiel:	IntegerPolynom<B> z = FastMultiplyPoly(f,g,16,zeta);
*/
template <int B>
IntegerPolynom<B> FastMultiplyPoly(IntegerPolynom<B> const& f, IntegerPolynom<B> const& g, int n, vector<BadicRepresentation<B>> const& zeta){
	//führe Fouriertransformation für f und g durch
	vector<BadicRepresentation<B>> f_coeff;
	vector<BadicRepresentation<B>> g_coeff;
	f_coeff = FastdFT(f, n, zeta);
	g_coeff = FastdFT(g, n, zeta);
	//Multipliziere die einzelnen Werte der Fouriertransformationen
	vector<BadicRepresentation<B>> h_coeff;
	for (unsigned int i = 0; i < n; i++){
		if (i >= f_coeff.size() || i >= g_coeff.size()) { h_coeff.push_back(0); }
		else{
			h_coeff.push_back(FundamentalMultiply(f_coeff.at(i), g_coeff.at(i)));
		}
	}
	//erstelle Polynom aus den multiplizierten Werten
	IntegerPolynom<B> hi(h_coeff);
	vector<BadicRepresentation<B>> h_dFT;
	//Führe inverse dFT für das entstandene Polynom durch
	h_dFT = FastdFT(hi, n , zetainv(zeta));
	
	//Berechne den Modul in welchem die Multiplikation durchgeführt wird: m=2^(3n/2)+1
	BadicRepresentation<B> modul=FundamentalAdd(pow(BadicRepresentation<B>(2), (3 * n / 2)),BadicRepresentation<B>(1));

	//Führe Moduloberechnung durch
	for (unsigned int i = 0; i < h_dFT.size(); i++){
		cout << i << endl;
		h_dFT.at(i) = h_dFT.at(i) % modul;
		h_dFT.at(i) = FundamentalDivision(h_dFT.at(i), BadicRepresentation<B>(n)).at(0);
	}

	//gebe entstandenes Polynom zurück
	IntegerPolynom<B> h(h_dFT);
	return h;
}


/*
Umformung einer ganzen Zahl in ihre 2-adische Entwicklung - IntToBadRep2(int x)
Input: ganze Zahl x
Output: 2-adische Entwicklung von x
Beispiel:	BadicRepresentation<2> x2 = IntToBadRep2(x);
*/
BadicRepresentation<2> IntToBadRep2(int x){
	//Falls x Null ist, gebe 2-adische Entwicklung von Null zurück
	if (x == 0){
		return BadicRepresentation<2>(0);
	}
	//ansonsten
	else{
		vector<int> z;
		//teile restliche Zahl durch 2 und speichere Divisionsrest
		while (x >= 1){
			z.push_back(x % 2);
			x = x / 2;
		}
		//drehe entstandenen Vektor um und gebe diesen als 2-adische Entwicklung zurück
		reverse(z.begin(), z.end());
		BadicRepresentation<2> ret(z);
		return ret;
	}
}


/*
Umformung einer B-adischen Entwicklung in eine 2-adische Entwicklung - ChangeBase(BadicRepresentation<B> x)
Input: B-adische Entwicklung einer ganzen Zahl x
Output: 2-adische Entwicklung von x
Beispiel:	BadicRepresentation<2> x2 = ChangeBase(x);
*/
template <int B>
BadicRepresentation<2> ChangeBase(BadicRepresentation<B> x){
	int B_copy = B;

	//Stelle Basis B in 2-adischer Darstellung dar
	BadicRepresentation<2> B2=IntToBadRep2(B_copy);

	vector<BadicRepresentation<2>> xdata;
	//Forme die einzelnen Koeffizienten der B-adischen Entwicklung um
	for (unsigned int i = 0; i < x.data.size(); i++){
		xdata.push_back(IntToBadRep2(x.data.at(i)));
	}

	BadicRepresentation<2> xNew(xdata.at(xdata.size() - 1));
	//Multipliziere die so entstandene "kaputte" B-adische Entwicklung aus um eine echte 2-adische Entwicklung zu erhalten
	for (int i = xdata.size() - 2; i >= 0; i--){
		xNew = FundamentalAdd(FundamentalMultiply(B2, xNew), xdata.at(i));
	}
	//Gebe die entstandene 2-adische Entwicklung zurück
	return xNew;
}


/*
Umformung einer 2-adischen Entwicklung in eine ganze Zahl - BadRep2toInt(BadicRepresentation<2> x)
Input: 2-adische Entwicklung einer ganzen Zahl x
Output: ganze Zahl x
Beispiel:	int x_int = BadRep2toInt(x);
*/
int BadRep2toInt(BadicRepresentation<2> x){
	int ret=0;
	//berechne 2-adische Entwicklung durch naives Ausmultiplizieren und addieren
	for (unsigned int i = 0; i < x.data.size(); i++){
		ret = ret + x.data.at(i)*pow(2, i);
	}
	//gebe entstandenen Integer-Wert zurück
	return ret;
}


/*
Umformung einer 2-adischen Entwicklung in eine B-adische Entwicklung - ChangeBase2to10(BadicRepresentation<2> x)
Input: 2-adische Entwicklung einer ganzen Zahl x
Output: B-adische Entwicklung der Zahl x
Beispiel:	BadicRepresentation<B> x_b = ChangeBase2to10(x);
*/
template<int B>
BadicRepresentation<B> ChangeBase2to10(BadicRepresentation<2> x){
	if (B == 2) { return x; }
	else{
		//Stelle B als 2-adische Entwicklung dar
		BadicRepresentation<2> B2 = IntToBadRep2(B);

		BadicRepresentation<B> xNew;
		BadicRepresentation<2> xcopy = x;
		int i = 0;

		//erstelle neue B-adische Entwicklung
		while (B2 < xcopy){
			//berechne hierfür die Division von x durch die neue Basisentwicklung
			vector<BadicRepresentation<2>> div = FundamentalDivision(xcopy, B2);
			//speichere den Divisionsrest
			if (i == 0){ xNew.data.at(0) = BadRep2toInt(div.at(1)); }
			else{ xNew.data.push_back(BadRep2toInt(div.at(1))); }
			//und setze x neu
			xcopy = div.at(0);
			i++;
		}
		xNew.data.push_back(BadRep2toInt(xcopy));
		//gebe die so entstandene B-adische Entwicklung von x zurück
		return xNew;
	}
}


/*
Multiplikation einer ganzer Zahl in 2-adischer Entwicklung mit einer 2er Potenz - TwoMultiply(BadicRepresentation<2> const& x, BadicRepresentation<2> const& y)
Input: zwei ganze Zahlen x und y in 2-adischer Entwicklung, wobei y eine 2er-Potenz ist und kein Vorzeichen aufweist
Output: 2-adische Entwicklung der Zahl z=x*y
Beispiel:	BadicRepresentation<2> z = TwoMultiply(x,y);
*/
BadicRepresentation<2> TwoMultiply(BadicRepresentation<2> const& x, BadicRepresentation<2> const& y){
	vector<int> ydata = y.data;
	//ersetze die 1 von y.data durch x
	for (unsigned int i = 0; i < x.data.size(); i++){
		if (i == 0){ ydata.at(y.data.size() - 1) = x.data.at(i); }
		else { ydata.push_back(x.data.at(i)); }
	}
	reverse(ydata.begin(), ydata.end());
	//erstelle aus dem entstandenen Koeffizientenvektor eine 2-adische Entwicklung
	BadicRepresentation<2> z(ydata);
	//übernehme das Vorzeichen von x
	z.sgn = x.sgn;
	return z;
}


/*
Schnelle Multiplikation zweier ganzer Zahlen in B-adischer Entwicklung - FastMultiply(BadicRepresentation<B> x, BadicRepresentation<B> y, int q)
Input: zwei ganze Zahlen x und y in B-adischer Entwicklung, ganze Zahl q (Logarithmus der 2-adischen Bitlänge)
Output: B-adische Entwicklung der Zahl z=x*y
Beispiel:	BadicRepresentation<B> x_b = FastMultiply(x,y,6);
*/
template <int B>
BadicRepresentation<2> FastMultiply(BadicRepresentation<B> x, BadicRepresentation<B> y){
	//Ändere x und y in 2-adisch entwickelte Zahlen ab
	BadicRepresentation<2> x_new = ChangeBase(x);
	BadicRepresentation<2> y_new = ChangeBase(y);

	//Berechne q, h und r
    int q_x = ceil(log(x_new.data.size()) / log(2));
    int q_y = ceil(log(y_new.data.size()) / log(2));
    int q = max(q_x, q_y);
	
    int h = (q - 1) / 2 + 1;
//	cout << "q= "<< q << endl;
//	cout << "h= " << h << endl;
	int r = pow(2, h);
//    cout << "r= " << r << endl;
	//erstelle die neue Basis
	BadicRepresentation<2> B_new = FindBnew(r);
	
	//Berechne m als Modul
    BadicRepresentation<2> modulo = FindBnew(3*r);
	modulo = FundamentalAdd<2>(modulo, BadicRepresentation<2>(1));
//	cout << "MODUL: " << modulo << endl;

//	cout << "Passe Basis an" << endl;
	//Passe Koeffizientenvektor so an dass xcoeff die Koeffizienten der neuen B=2^r-adischen Entwicklung enthält
    vector<BadicRepresentation<2> > xcoeff;
	for (unsigned int i = 0; i < x_new.data.size(); i=i+r){
		BadicRepresentation<2> coeff;
		for (unsigned int j = 0; j < r; j++){
			if (i + j < x_new.data.size()){
				if (j == 0){
					coeff.data.at(0) = x_new.data.at(i + j);
				}
				else{
					coeff.data.push_back(x_new.data.at(i + j));
				}
			}
		}
        while (coeff.data.size() > 1 && coeff.data.back() == 0)
            coeff.data.erase(coeff.data.end()-1);
		xcoeff.push_back(coeff);
		//cout << "Koeffizient von x_new an " << i << ": " << coeff << endl;
    }

//	cout << "Passe Basis an" << endl;
	//Passe Koeffizientenvektor so an dass ycoeff die Koeffizienten der neuen B=2^r-adischen Entwicklung enthält
	vector<BadicRepresentation<2>> ycoeff;
	for (unsigned int i = 0; i < y_new.data.size(); i = i + r){
		BadicRepresentation<2> coeff;
		for (unsigned int j = 0; j < r; j++){
			if (i + j < y_new.data.size()){
				if (j == 0){
					coeff.data.at(0) = y_new.data.at(i + j);
				}
				else{
					coeff.data.push_back(y_new.data.at(i + j));
				}
			}
		}
        while (coeff.data.size() > 1 && coeff.data.back() == 0)
            coeff.data.erase(coeff.data.end()-1);
		ycoeff.push_back(coeff);
		//cout << "Koeffizient von y_new an " << i << ": " << coeff << endl;
	}

//	cout << "Fuege Nullen an" << endl;
	//Füge nötige Nullen an
	for (unsigned int k = xcoeff.size(); k < 2 * r-1; k++){
		xcoeff.push_back(BadicRepresentation<2>(0));
	}
	for (unsigned int k = ycoeff.size(); k < 2 * r-1; k++){
		ycoeff.push_back(BadicRepresentation<2>(0));
	}
//	cout << "Erstelle Polynome" << endl;
	//Erstelle Polynome analog zur B-adischen Entwicklung
	IntegerPolynom<2> xpoly(xcoeff);
	IntegerPolynom<2> ypoly(ycoeff);

//	cout << "Erstelle Einheitswurzeln" << endl;
	//erstelle die Einheitswurzeln
    vector<BadicRepresentation<2> > zetas;
	BadicRepresentation<2> zeta0(1);
	BadicRepresentation<2> zeta1(8);
	zetas.push_back(zeta0);
	zetas.push_back(zeta1);
	for (unsigned int i = 0; i < 2*r-2; i++){
		zetas.push_back(TwoMultiply(zetas.back(), zeta1) % modulo);
	}

//	cout << "Führe dFT aus" << endl;
	//Führe die Fouriertransformationen durch
	vector<BadicRepresentation<2>> x_hat;
	x_hat = FastdFT(xpoly, 2*r, zetas);

//	cout << "Führe dFT aus" << endl;
	vector<BadicRepresentation<2>> y_hat;
	y_hat = FastdFT(ypoly, 2 * r, zetas);

//	cout << "Führe Modulorechnung durch" << endl;
	//Führe Moduloberechnung durch
	for (unsigned int i = 0; i < x_hat.size(); i++){
		x_hat.at(i) = x_hat.at(i) % modulo;
		y_hat.at(i) = y_hat.at(i) % modulo;
	}

//	cout << "Berechne z" << endl;
	//berechne z als komponentenweises Produkt der Fouriertransformierten
	vector<BadicRepresentation<2>> z_hat;
	for (unsigned int i = 0; i < 2 * r; i++){
        /*if (h>2){
			//nutze rekursiv FastMultiply zur Berechnung
            z_hat.push_back(FastMultiply<2>(x_hat.at(i), y_hat.at(i)));
		}
        else{*/
			//und falls Eingabe klein genug die gewöhnliche Multiplikation
			z_hat.push_back(FundamentalMultiply<2>(x_hat.at(i), y_hat.at(i)));
        //}
	}

//	cout << "Führe Modulorechnung durch" << endl;
	//führe erneut eine Moduloberechnung durch
	for (unsigned int i = 0; i < z_hat.size(); i++){
		z_hat.at(i) = z_hat.at(i) % modulo;
	}
	
//	cout << "Führe dFT aus" << endl;
	//berechne nun die inverse Fouriertransformation
	vector<BadicRepresentation<2>> z_hat_new;
	IntegerPolynom<2> zpoly(z_hat);
	z_hat_new = FastdFT(zpoly, 2 * r, zetainv(zetas));
	
	for (unsigned int i = 0; i < z_hat_new.size(); i++){
		z_hat_new.at(i) = z_hat_new.at(i) % modulo;
		z_hat_new.at(i) = FundamentalDivision<2>(z_hat_new.at(i), BadicRepresentation<2>(2*r)).at(0);
	}
//	cout << z_hat_new.size() << endl;

//	cout << modulo << endl;
//	cout << "B_new: " << B_new << endl;
//	for (unsigned int i = 0; i < z_hat_new.size(); i++){
//		cout << z_hat_new.at(i) % modulo << endl;
//	}



	//FALSCH AB HIER!
//	cout << "Stelle Darstellung von z sicher" << endl;
	//berechne nun die entstandene Zahl aus den bisherigen Ergebnissen
	vector<BadicRepresentation<2>> z_end;
	for (unsigned int i = 0; i < z_hat_new.size(); i++){
		vector<BadicRepresentation<2>> first = FundamentalDivision<2>(z_hat_new.at(i), B_new);
		BadicRepresentation<2> z0 = first.at(1);	
		vector<BadicRepresentation<2>> second = FundamentalDivision<2>(first.at(0), B_new);
		BadicRepresentation<2> z1 = second.at(1);	
		BadicRepresentation<2> z2 = second.at(0);

		if (i == 0){
			z_end.push_back(z0);
			z_end.push_back(z1);
			z_end.push_back(z2);
		}
		else{
			z_end.at(i) = FundamentalAdd<2>(z_end.at(i), z0);
			z_end.at(i + 1) = FundamentalAdd<2>(z_end.at(i + 1), z1);
			z_end.push_back(z2);
		}
	}

	BadicRepresentation<2> z_ret=z_end.at(z_end.size()-1);
	for (int i = z_end.size() - 2; i >= 0; i--){
		z_ret = FundamentalAdd<2>(TwoMultiply(z_ret, B_new), z_end.at(i));
	}
	
	//Gebe nun das Ergebnis als B-adische Entwicklung zurück
	//BadicRepresentation<B> zret= ChangeBase2to10<B>(z_2);
	return z_ret;
}
