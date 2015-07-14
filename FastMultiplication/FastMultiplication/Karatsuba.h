#pragma once
#include <math.h>


/*
Karatsuba Multiplikation zweier ganzer Zahlen - Karatsuba(BadicRepresentation<B> x, BadicRepresentation<B> y, unsigned int k)
Input: zwei ganze Zahlen x und y in B-adischer Entwicklung, ganze Zahl k welche die Zweierpotenz angibt für welche der Algorithmus durchgeführt wird
Output: x*y als Instanz der Klasse BadicRepresentation
Beispiel: BadicRepresentation<10> z = Karatsuba(x,y,4); 
*/
template <int B>
BadicRepresentation<B> Karatsuba(BadicRepresentation<B> x, BadicRepresentation<B> y, unsigned int k)
{
	//Falls x und y eine höhere Bitlänge als 1 haben
	if (k > 0){
		//Falls k falsch gewählt wurde, gebe Fehlermeldung aus
		if ((x.data.size() > pow(2, k)) || (y.data.size() > pow(2, k))){ throw runtime_error("Eingabe zu groß"); }
		else {
			//ansonsten fülle x und y mit Nullen auf und befülle halbiere die Eingabe x in x0,x1 und y in y0,y1 auf
			for (unsigned int i = x.data.size(); i < pow(2, k); i++){ x.data.push_back(0); }
			for (unsigned int i = y.data.size(); i < pow(2, k); i++){ y.data.push_back(0); }
			BadicRepresentation<B> x0;
			BadicRepresentation<B> x1;
			BadicRepresentation<B> y0;
			BadicRepresentation<B> y1;
			for (unsigned int j = 0; j < pow(2, k - 1); j++){
				if (j == 0){
					x0.data.at(0) = x.data.at(0);
					x1.data.at(0) = x.data.at(pow(2, k - 1));
					y0.data.at(0) = y.data.at(0);
					y1.data.at(0) = y.data.at(pow(2, k - 1));
				}
				else{
					x0.data.push_back(x.data.at(j));
					x1.data.push_back(x.data.at(j+pow(2, k - 1)));
					y0.data.push_back(y.data.at(j));
					y1.data.push_back(y.data.at(j+pow(2, k - 1)));
				}
			}

			//Berechne rekursiv z0=x0*y0, z1=(x0-x1)*(y0-y1), z2=x1*y1 mitteles Karatsuba Multiplikation
			BadicRepresentation<B> z0 = Karatsuba(x0, y0, k - 1);
			BadicRepresentation<B> z1 = Karatsuba(FundamentalSubtract<B>(x0, x1), FundamentalSubtract<B>(y0, y1), k - 1);
			BadicRepresentation<B> z2 = Karatsuba(x1, y1, k - 1);
			
			//Shifte (z0+z2)-z1
			BadicRepresentation<B> unshifted0 = FundamentalSubtract<B>(FundamentalAdd<B>(z0,z2),z1);
			BadicRepresentation<B> shifted0;
			for (unsigned int r = 0; r < pow(2, k - 1)-1; r++){
				shifted0.data.push_back(0);
			}
			for (unsigned int r = 0; r < unshifted0.data.size(); r++){
				shifted0.data.push_back(unshifted0.data.at(r));
			}
		
			//Shifte z2
			BadicRepresentation<B> shifted1;
			for (unsigned int r = 0; r < pow(2, k) - 1; r++){
				shifted1.data.push_back(0);
			}
			for (unsigned int r = 0; r < z2.data.size(); r++){
				shifted1.data.push_back(z2.data.at(r));
			}

			//Berechne die Addition der geshifteten Zahlen
			BadicRepresentation<B> z = FundamentalAdd<B>(FundamentalAdd<B>(z0, shifted0), shifted1);

			//Passe das Vorzeichen an
			z.sgn = (x.sgn + y.sgn) % 2;
			//Gebe Ergebnis zurück
			return z;
		}
	}
	else {
		//Falls die Bitlänge von x und y 1 ist, gebe die Multiplikation der Zahlen zurück
		BadicRepresentation<B> ret = FundamentalMultiply(x,y);
		return ret;
	}
}


/*
Karatsuba Multiplikation zweier ganzer Zahlen - Karatsuba(BadicRepresentation<B> x, BadicRepresentation<B> y)
Input: zwei ganze Zahlen x und y in B-adischer Entwicklung
Output: x*y als Instanz der Klasse BadicRepresentation
Beispiel: BadicRepresentation<10> z = Karatsuba(x,y);
*/
template <int B>
BadicRepresentation<B> Karatsuba(BadicRepresentation<B> x, BadicRepresentation<B> y)
{
	//Falls x mehr Koeffizienten hat als y
	if (x.data.size() > y.data.size()){
		//Berechne die Karatsuba Multiplikation von x und y mit der nächstgrößeren 2er-Potenz, die größer ist als die Bitlänge von x
		double k_d = log(x.data.size()) / log(2);
		int k = k_d + 1;
		return Karatsuba(x,y,k);
	}
	else{
		//ansonsten nehme analog die 2er-Potenz, die größer ist als die Bitlänge von y
		double k_d = log(y.data.size()) / log(2);
		int k = k_d + 1;
		return Karatsuba(x, y, k);
	}
}


/*
Karatsuba Multiplikation zweier ganzer Zahlen ohne Auffüllung mit Nullen - CleverKaratsuba(BadicRepresentation<B> const& x, BadicRepresentation<B> const& y)
Input: zwei ganze Zahlen x und y in B-adischer Entwicklung
Output: x*y als Instanz der Klasse BadicRepresentation
Beispiel: BadicRepresentation<10> z = CleverKaratsuba(x,y);
*/
template <int B>
BadicRepresentation<B> CleverKaratsuba(BadicRepresentation<B> const& x, BadicRepresentation<B> const& y)
{
	//Falls die Bitlänge von x und y größer ist als 1
	if (x.data.size() > 1 && y.data.size() > 1){
		//berechne die halbe Bitlängen von x und y
		int m, n;
		if (x.data.size() % 2 == 0){ m = x.data.size() / 2; }
		else{ m = x.data.size() / 2 + 1; }
		if (y.data.size() % 2 == 0){ n = y.data.size() / 2; }
		else{ n = y.data.size() / 2 + 1; }
		//setze m als die größere der beiden Zahlen
		if (n > m){ m = n; }

		//Halbiere x und y in x0, x1, y0, y1 
		vector<int> x0data(m); 
		vector<int> x1data(m);
		vector<int> y0data(m);
		vector<int> y1data(m);

		for (int i =0; i < m; i++){
			if (x.data.size() > i){ x0data.at(m-1-i) = x.data.at(i); }
			if (x.data.size() > i + m){ x1data.at(m-1-i) = x.data.at(i + m); }
			if (y.data.size() > i){ y0data.at(m-1-i) = y.data.at(i); }
			if (y.data.size() > i + m){ y1data.at(m-1-i) = y.data.at(i + m); }
		}

		BadicRepresentation<B> x0(x0data);
		BadicRepresentation<B> x1(x1data);
		BadicRepresentation<B> y0(y0data);
		BadicRepresentation<B> y1(y1data);

		//Berechne rekursiv z0=x0*y0, z1=(x0-x1)*(y0-y1), z2=x1*y1 mitteles cleverer Karatsuba Multiplikation
		BadicRepresentation<B> z0 = CleverKaratsuba(x0, y0);
		BadicRepresentation<B> z1 = CleverKaratsuba(FundamentalSubtract<B>(x0, x1), FundamentalSubtract<B>(y0, y1));
		BadicRepresentation<B> z2 = CleverKaratsuba(x1, y1);
		
		//Shifte (z0+z2)-z1
		BadicRepresentation<B> unshifted0 = FundamentalSubtract<B>(FundamentalAdd<B>(z0, z2), z1);
		BadicRepresentation<B > shifted0;
		vector<int> shifteddata(m);
		shifted0.data = shifteddata;
		for (unsigned int r = 0; r < unshifted0.data.size(); r++){
			if ((r==0) && (m == 0)){
				shifted0.data.at(0)=unshifted0.data.at(0);
			}
			else{
				shifted0.data.push_back(unshifted0.data.at(r));
			}
		}

		//Shifte z2
		BadicRepresentation<B> shifted1;
		vector<int> shifteddata1(2*m);
		shifted1.data = shifteddata1;
		for (unsigned int r = 0; r < z2.data.size(); r++){
			if ((r == 0) && (2*m == 0)){
				shifted1.data.at(0) = z2.data.at(0);
			}
			else{
				shifted1.data.push_back(z2.data.at(r));
			}
		}
		
		//Berechne die Addition der geshifteten Zahlen und passe das Vorzeichen an
		BadicRepresentation<B> z = FundamentalAdd<B>(FundamentalAdd<B>(z0, shifted0), shifted1);
		z.sgn = (x.sgn + y.sgn) % 2;
		//gebe das Ergebnis der Multiplikation zurück
		return z;

	}
	else {
		//Falls x und y Bitlänge 1 haben multipliziere x und y direkt
		return FundamentalMultiply<B>(x, y);
	}
}