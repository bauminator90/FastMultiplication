#pragma once
using namespace std;

/*
Gewöhnliche Addition - FundamentalAdd(BadicRepresentation<B> x,BadicRepresentation<B> y)
Input: Zwei Instanzen der Klasse BadicRepresentation x,y
Output:	Eine Instanz der Klasse BadicRepresentation, welche die Summe von x und y repräsentiert
Beispiel: z=FundamentalAdd<B>(x,y);
*/
template <int B>
BadicRepresentation<B> FundamentalAdd(BadicRepresentation<B> const& xx, BadicRepresentation<B> const& yy)
{
	BadicRepresentation<B> &x = const_cast<BadicRepresentation<B> &>(xx);
	BadicRepresentation<B> &y = const_cast<BadicRepresentation<B> &>(yy);
	BadicRepresentation<B> z;
	if (x.data.size() >= y.data.size()){
		//Neuer Koeffizientenvektor wird angelegt
		vector<int> zdata;
		//Vorzeichen von x wird übernommen
		z.sgn = x.sgn;

		int delta = 0;
		//Anfügen von fehlenden Nullen, die bei der Addition benötigt werden
		x.data.push_back(0);
		int count = x.data.size() - y.data.size();
		for (unsigned int i = 0; i <= (count - 1); i++){
			y.data.push_back(0);
		}

		//Führe Addition der Koeffizienten durch, falls Vorzeichen der Inputparameter identisch
		if (x.sgn == y.sgn){
			for (unsigned int i = 0; i <= x.data.size() - 1; i++){
				zdata.push_back(x.data.at(i) + y.data.at(i) + delta);
				delta = 0;
				if (zdata.at(i) >= B) {
					zdata.at(i) = zdata.at(i) - B;
					delta = 1;
				}
			}
		}
		//ansonsten führe eine Subtraktion durch
		else{
			if (!abslower(x, y)){
				for (unsigned int i = 0; i <= x.data.size() - 1; i++){
					zdata.push_back(x.data.at(i) - y.data.at(i) - delta);
					delta = 0;
					if (zdata.at(i) < 0) {
						zdata.at(i) = zdata.at(i) + B;
						delta = 1;
					}
				}
			}
			else{
				for (unsigned int i = 0; i <= x.data.size() - 1; i++){
					zdata.push_back(y.data.at(i) - x.data.at(i) - delta);
					delta = 0;
					if (zdata.at(i) < 0) {
						zdata.at(i) = zdata.at(i) + B;
						delta = 1;
					}
				}
				z.sgn = y.sgn;
			}
		}
		
		//Lösche überflüssige Nullen aus der B-adischen Entwicklung und gebe das Ergebnis zurück
		while (zdata.at(zdata.size() - 1) == 0){
			if (zdata.size() == 1){ break; }
			else { zdata.erase(zdata.end() - 1); }
		}
		z.data = zdata;

		x.data.pop_back();
		for (unsigned int i = 0; i <= (count - 1); i++){
			y.data.pop_back();
		}
		return z;
	}
	else {
		//Falls y mehr Stellen aufweist als x, vertausche die Eingabe
		return FundamentalAdd<B>(y, x);
	}

}


/*
Gewöhnliche Subtraktion - FundamentalSubtract(BadicRepresentation<B> x,BadicRepresentation<B> y)
Input: Zwei Instanzen der Klasse BadicRepresentation x,y
Output:	Eine Instanz der Klasse BadicRepresentation, welche die Differenz von x und y repräsentiert
Beispiel: z=FundamentalSubtract<B>(x,y);
*/
template <int B>
BadicRepresentation<B> FundamentalSubtract(BadicRepresentation<B> const& xx, BadicRepresentation<B> const& yy)
{
	BadicRepresentation<B> &x = const_cast<BadicRepresentation<B> &>(xx);
	BadicRepresentation<B> &y = const_cast<BadicRepresentation<B> &>(yy);
	BadicRepresentation<B> z;
	//Nutze Addition und Vorzeichenmanagement aus
	if (x.data.size() >= y.data.size() && (!abslower(x,y))){ //TODO: evtl unnötig zu doppeln
		y.sgn = (y.sgn + 1) % 2;
		z = FundamentalAdd(x, y);
		y.sgn = (y.sgn + 1) % 2;
	}
	else {
		//falls y betragsmäßig größer ist als x, vertausche die Eingabe
		z = FundamentalSubtract(y, x);
		z.sgn = (z.sgn + 1) % 2;
	}
	return z;
}


/*
Gewöhnliche Multiplikation - FundamentalMultiply(BadicRepresentation<B> x,BadicRepresentation<B> y)
Input: Zwei Instanzen der Klasse BadicRepresentation x,y
Output:	Eine Instanz der Klasse BadicRepresentation, welche die Multiplikation von x und y repräsentiert
Beispiel: z=FundamentalMultiply<B>(x,y);
*/
template <int B>
BadicRepresentation<B> FundamentalMultiply(BadicRepresentation<B> const& x, BadicRepresentation<B> const& y)
{
	//Instanziiere z und erstelle die nötigen Koeffizienten als 0
	BadicRepresentation<B> z;
	for (unsigned int i = 0; i <= x.data.size() + y.data.size() - 1; i++){ z.data.push_back(0); }

	//führe die eigentliche Multiplikation durch
	for (unsigned int i = 0; i <= x.data.size() - 1; i++){
		for (unsigned int j = 0; j <= y.data.size() - 1; j++){
			int d;
			d = z.data.at(i + j) + x.data.at(i)*y.data.at(j);
			z.data.at(i + j) = d % B;
			if (d >= B){
				int delta = d / B;
				z.data.at(i + j + 1) = z.data.at(i + j + 1) + delta;
			}
		}
	}

	//Setze das Vorzeichen
	z.sgn = (x.sgn + y.sgn) % 2;

	//Lösche vorangesteltte Nullen aus der B-adischen Entwicklung der Lösung z
	while (z.data.at(z.data.size() - 1) == 0){
		if (z.data.size() == 1){ break; }
		else { z.data.erase(z.data.end() - 1); }
	}
	return z;
}


/*
Gewöhnliche Division mit Rest - FundamentalDivision(BadicRepresentation<B> x,BadicRepresentation<B> y)
Input: Zwei Instanzen der Klasse BadicRepresentation x,y
Output:	Ein Vektor bestehend aus zwei Instanzen der Klasse BadicRepresentation q und r, wobei q der Quotient und r der Rest der Division von x durch y ist - es ist also x=q*y+r
Beispiel:
vect=FundamentalDivision<B>(x,y);
q=vect.at(0);
r=vect.at(1);
*/
template <int B>
vector<BadicRepresentation<B>> FundamentalDivision(BadicRepresentation<B> const& x, BadicRepresentation<B> const& y,bool compr=true)
{
	BadicRepresentation<B> q;
	BadicRepresentation<B> r;
	vector<BadicRepresentation<B>> z;
	//Falls Leitkoeffizient von y ungleich 0 und x betragsmäßig größer als y, führe Division durch
	if ((y.data.at(y.data.size() - 1) != 0) && (x.data.size() >= y.data.size())){   
		q.data.resize(x.data.size() - y.data.size() + 1, 0);

		//Finde d analog zum Algorithmus und multipliziere d an die Eingaben x und y
		int d = B / (y.data.at(y.data.size() - 1) + 1);
		BadicRepresentation<B> x1;
		BadicRepresentation<B> y1;
		BadicRepresentation<B> d_b(d);
		x1 = FundamentalMultiply(x, d_b);
		x1.sgn = 0;
		y1 = FundamentalMultiply(y, d_b);
		y1.sgn = 0;

		//führe eigentliche Division von x*d durch y*d schrittweise durch (vgl. schriftliche Division)
		for (int i = x.data.size(); i >= y.data.size(); i--){
			//Finde "Versuchsquotienten" qs
			int qs = 0;
			if (x1.data.size() > i){
				qs = (x1.data.at(i)*B + x1.data.at(i - 1)) / y1.data.at(y1.data.size() - 1);
			}
			else {
				if (x1.data.size() > i - 1) {
					qs = (x1.data.at(i - 1)) / y1.data.at(y1.data.size() - 1);
				}
				else {
					qs = 0;
				}
			}
			if (qs > B - 1){ qs = B - 1; }
			BadicRepresentation<B> qs_b;
			qs_b.data.at(0) = qs;

			//Führe Shift durch
			int shift = i - y.data.size();
			BadicRepresentation<B> sum;
			for (unsigned int j = 0; j <= y.data.size(); j++){
				if (j == 0){
					if (x1.data.size() > shift){ sum.data.at(0) = x1.data.at(shift); }
					else { sum.data.at(0) = 0; }
				}
				else {
					if (x1.data.size() > shift + j){
						sum.data.push_back(x1.data.at(shift + j));
					}
					else {
						sum.data.push_back(0);
					}
				}
			}

			//Echte B-adische Entwicklung muss für nachfolgende Subtraktion sichergestellt werden
			while (sum.data.at(sum.data.size() - 1) == 0){
				if (sum.data.size() == 1){ break; }
				else {sum.data.pop_back();}
			}

			//Subtrahiere Vielfaches von y*d von der geshifteten Zahl
			sum = FundamentalSubtract<B>(sum, FundamentalMultiply<B>(y1, qs_b));
			//falls zu viel abgezogen wurde, passe Versuchsquotienten qs an
			while (sum.sgn == 1){
				qs = qs - 1;
				if (qs < 0){ cout << "qs < 0"; }
				qs_b.data.at(0) = qs;
				sum = FundamentalAdd<B>(sum, y1);
			}
			q.data.at(shift) = qs;

			//Führe geshiftete Subtraktion auch an x*d durch
			BadicRepresentation<B> Bshift_B;
			for (int i = 0; i < shift - 1; i++){
				Bshift_B.data.push_back(0);
			}
			if (shift == 0){
				Bshift_B.data.at(0) = qs;
			}
			else{
				Bshift_B.data.push_back(qs);
			}
			//if (Bshift_B.IntRepresentation() != 0){
			x1 = FundamentalSubtract(x1, FundamentalMultiply<B>(y1, Bshift_B));
			//}
		}

		//Bestimme den Rest der Division
		//ORIGINAL: int rest = x1.IntRepresentation() / d; 
		if (compr == true){
			vector<BadicRepresentation<B>> rhelp = FundamentalDivision(x1, d_b, false);
			r = rhelp.at(0);
			r.sgn = x.sgn;
		}

		//Stelle B-adische Darstellung des Quotienten sicher
		while (q.data.at(q.data.size() - 1) == 0){
			if (q.data.size() == 1){ break; }
			else { q.data.pop_back(); }
		}
		q.sgn = (x.sgn + y.sgn) % 2;

		z.push_back(q);
		z.push_back(r);
		return z;
	}
	else{
		//Falls Leitkoeffizient von y Null ist, gebe Fehlermeldung aus
		if (y.data.at(y.data.size() - 1) == 0) { throw runtime_error("Division durch 0"); }
		//Falls x betragsmäßig kleiner ist als y, gebe Null als Quotient und x als Rest zurück
		z.push_back(q);
		z.push_back(x);
		return z;
	}
}