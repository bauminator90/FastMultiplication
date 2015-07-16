#include <iostream>                                  
#include "BadischeEntwicklung.h"
#include "FundamentaleAlgorithmen.h"
#include "Karatsuba.h"
#include "SchnelleMultiplikation.h"
#include "FundamentaleAlgorithmen_Polynome.h"
#include <stdlib.h>   
#include <time.h>       
using namespace std;




int main(){
	/*
	static const int B = 10;

	vector<int> x = { 2,3,1,4,1,7,7,8,9,1};
	int x_s = 1;
	vector<int> y = { 8,5,2,1,7,1};
	int y_s = 0;


	//erstellt b-adische Darstellung und gibt diese aus
	BadicRepresentation<B> x_b(x);
	x_b.sgn = x_s;
	BadicRepresentation<B> y_b(y);
	y_b.sgn = y_s;

	cout << "X in B-adischer Darstellung: " << x_b << endl;
	cout << "Y in B-adischer Darstellung: " << y_b << endl;
	cout << endl;
	*/

	/*
	//Führe gewöhnliche Addition durch
	BadicRepresentation<B> z_b;
	z_b = FundamentalAdd<B>(x_b, y_b);
	//cout << "Z=X+Y in B-adischer Darstellung: " << z_b << endl;
	//cout << endl;

	//Führe gewöhnliche Subtraktion durch
	z_b = FundamentalSubtract<B>(x_b, y_b);
	//cout << "Z=X-Y in B-adischer Darstellung: " << z_b << endl;
	//cout << endl;


	//Führe gewöhnliche Multiplikation durch
	z_b = FundamentalMultiply(y_b, x_b);
	//cout << "Z=X*Y in B-adischer Darstellung: " << z_b << endl;
	//cout << endl;


	//Führe gewöhnliche Division mit Rest durch
	vector<BadicRepresentation<B>> sol;
	sol = FundamentalDivision<B>(x_b, y_b);
	//cout << "Quotient in B-adischer Darstellung: " << sol.at(0) << endl;
	//cout << "Rest in B-adischer Darstellung: " << sol.at(1) << endl;
	//cout << endl;


	//Führe Karatsuba-Multiplikation durch
	z_b = Karatsuba<B>(x_b, y_b);
	//cout << "Karatsuba Multiplikation: " << endl;
	//cout << "Z=X*Y in B-adischer Darstellung: " << z_b << endl;


	/*
	//Führe schnelle Multiplikation nach Schönhage-Strassen durch
	//cout << endl;
	//cout << "Schnelle Multiplikation: " << endl;
	vector<int> a = { 1, 9, 8, 9, 8, 7, 4, 4, 3, 6, 7, 8, 4, 6, 2, 4};
	int a_s = 1;
	vector<int> b = { 3, 7, 3, 2, 5, 2, 3, 5, 4, 3, 6, 7, 8, 4, 6, 1 };
	int b_s = 0;
	BadicRepresentation<B> a_b(a);
	a_b.sgn = a_s;
	BadicRepresentation<B> b_b(b);
	b_b.sgn = b_s;

	z_b = FastMultiply(a_b, b_b, 2048, 11);




	//Erstelle Polynome und gebe diese aus
	vector<int> fc{ 445,14,354,-2,9,23,33,56,7,45,75,77,3,2,1234,3 };
	vector<int> gc{ 1, 7, -2,-6,-3,231,34,5,35,2,4,325,234,67,-232,32,-53};
	IntegerPolynom<10> f(fc);
	IntegerPolynom<10> g(gc);

	/*cout << endl;
	cout << "Polynome: " << endl;
	cout << "f(X)=" << f << endl;
	cout << "g(X)=" << g << endl;
	cout << endl;

	IntegerPolynom<10> h = FundamentalAddPoly(f, g);
	//cout << "h(X)=f(X)+g(X)="<< h << endl;
	//cout << endl;

	h = FundamentalSubtractPoly(f, g);
	//cout << "h(X)=f(X)-g(X)=" << h << endl;
	//cout << endl;

	h = FundamentalMultiplyPoly(f, g);
	//cout << "h(X)=f(X)*g(X)=" << h << endl;
	//cout << endl;

	vector<IntegerPolynom<B>> z;
	z = FundamentalDivisionPoly(f, g);
	//cout << "h(X)=f(X)/g(X)=" << z.at(0) << endl;
	//cout << endl;
	*/
	/*
	const int B = 10;
	vector<int> fcd{ 5, 2, 9, 7, 4, 6, 7, 18,12,13,14 };
	vector<int> gcd{ 1, 2, 3, 4, 5, 6, 7 };

	vector<BadicRepresentation<B>> zetas;
	BadicRepresentation<B> zeta0(1);
	BadicRepresentation<B> zeta1(8);
	zetas.push_back(zeta0);
	zetas.push_back(zeta1);
	for (unsigned int i = 0; i < 30; i++){
	zetas.push_back(FundamentalMultiply(zetas.back(), zeta1));
	}

	IntegerPolynom<B> f1(fcd);
	IntegerPolynom<B> g1(gcd);
	cout << "f(X)=" << f1 << endl;
	cout << "g(X)=" << g1 << endl;
	IntegerPolynom<B> h1 = FastMultiplyPoly(f1, g1, 32, zetas);
	cout << "h(X)=" << h1 << endl;
	IntegerPolynom<B> k = FundamentalMultiplyPoly(f1, g1);
	cout << "k(X)=" << k << endl;



	//BadicRepresentation<B> z = FastMultiply<B>(x_b, y_b,6); //6, da die Zahlen höchstens n=2^6=64 Stellen in 2-ad. Darstellung besitzen
	//cout << z << endl;
	*/

	/*
	Testet die Geschwindigkeit zwischen gewöhnlicher, Karatsuba und cleverer Karatsuba Multiplikation
	*/
	/*
	const int B = 10;
	srand(time(NULL));
	int randomNumber1;
	int randomNumber2;
	vector<double> times;
	vector<double> karatimes;
	vector<double> cleverkaratimes;
	//Zeitmessung
	for (unsigned int i = 10000; i < 15001; i=i+1000){
	double end = 1;
	for (unsigned int k = 0; k < end; k++){
	//cout << "Started with i=" << i << " :"<< endl;
	vector<int> coeff1;
	vector<int> coeff2;
	for (unsigned int j = 0; j < i; j++){
	randomNumber1 = rand() % 10;
	randomNumber2 = rand() % 10;
	coeff1.push_back(randomNumber1);
	coeff2.push_back(randomNumber2);
	}
	BadicRepresentation<B> x(coeff1);
	//cout << x << endl;
	BadicRepresentation<B> y(coeff2);
	//cout << y << endl;
	BadicRepresentation<B> z;
	//cout << "randomized whole numbers created. Multiplication starts now." << endl;


	double time1 = 0.0, time2 = 0.0, time3 = 0.0, tstart;
	tstart = clock();
	BadicRepresentation<B> z1 = FundamentalMultiply<B>(x, y);
	time1 = clock() - tstart;
	time1 = time1 / CLOCKS_PER_SEC;
	if (k == 0){ times.push_back(time1); }
	else { times.at(times.size() - 1) = times.at(times.size() - 1) + time1; }
	//cout << "Fundamental beendet" << endl;

	tstart = clock();
	BadicRepresentation<B> z2 = Karatsuba<B>(x, y);
	time2 = clock() - tstart;
	time2 = time2 / CLOCKS_PER_SEC;
	if (k == 0){ karatimes.push_back(time2);}
	else { karatimes.at(karatimes.size() - 1) = karatimes.at(karatimes.size() - 1) + time2; }
	//cout << "Kara beendet" << endl;

	tstart = clock();
	BadicRepresentation<B> z3 = CleverKaratsuba<B>(x, y);
	time3 = clock() - tstart;
	time3 = time3 / CLOCKS_PER_SEC;
	if (k == 0){ cleverkaratimes.push_back(time3); }
	else { cleverkaratimes.at(cleverkaratimes.size() - 1) = cleverkaratimes.at(cleverkaratimes.size() - 1) + time3; }
	//cout << "CleverKara beendet" << endl;


	}
	cout << "i=" << i << " - time=" << times.at(times.size() - 1) / end << " & karatime= " << karatimes.at(karatimes.size() - 1) / end << " & cleverkaratime= " << cleverkaratimes.at(cleverkaratimes.size() - 1) / end << endl;
	}
	*/

	/*
	Testet die Geschwindigkeit zwischen gewöhnlicher und schneller Polynom Multiplikation
	*/
	const int B = 10;
	srand(time(NULL));
	int randomNumber1;
	int randomNumber2;
	vector<double> times;
	vector<double> dfttimes;
	//Zeitmessung
	for (unsigned int i = 10; i < 101; i = i + 10){
		double end = 1;
		for (unsigned int k = 0; k < end; k++){
			//cout << "Started with i=" << i << " :"<< endl;
			vector<int> coeff1;
			vector<int> coeff2;
			for (unsigned int j = 0; j < i; j++){
				randomNumber1 = rand() % 1000;
				randomNumber2 = rand() % 1000;
				coeff1.push_back(randomNumber1);
				coeff2.push_back(randomNumber2);
			}
			IntegerPolynom<B> f(coeff1);
			//cout << x << endl;
			IntegerPolynom<B> g(coeff2);
			//cout << y << endl;
			//cout << "randomized whole numbers created. Multiplication starts now." << endl;


			double time1 = 0.0, time2 = 0.0, tstart;
			tstart = clock();
			IntegerPolynom<B> z1 = FundamentalMultiplyPoly<B>(f, g);
			time1 = clock() - tstart;
			time1 = time1 / CLOCKS_PER_SEC;
			if (k == 0){ times.push_back(time1); }
			else { times.at(times.size() - 1) = times.at(times.size() - 1) + time1; }
			//cout << "Fundamental beendet" << endl;

			/*int gradsumme = 2 * i;
			int zweipotenzsumme = 1;
			int i = 1;
			while (gradsumme > zweipotenzsumme){ zweipotenzsumme = pow(2, i); i++; }

			vector<BadicRepresentation<B>> zetas;
			BadicRepresentation<B> zeta0(1);
			BadicRepresentation<B> zeta1(8);
			zetas.push_back(zeta0);
			zetas.push_back(zeta1);
			for (unsigned int i = 0; i < zweipotenzsumme - 2; i++){
			zetas.push_back(FundamentalMultiply(zetas.back(), zeta1));
			}

			tstart = clock();
			IntegerPolynom<B> z2 = FastMultiplyPoly<B>(f, g,zweipotenzsumme,zetas);
			time2 = clock() - tstart;
			time2 = time2 / CLOCKS_PER_SEC;
			if (k == 0){ dfttimes.push_back(time2); }
			else {dfttimes.at(dfttimes.size() - 1) = dfttimes.at(dfttimes.size() - 1) + time2; }
			//cout << "Kara beendet" << endl;
			*/
		}
		cout << "i=" << i << " - time=" << times.at(times.size() - 1) / end << endl;// " & dfttime= " << dfttimes.at(dfttimes.size() - 1) / end << endl;
	}




	/*
	Testet die Funktionalität von der schnellen Multiplikation
	*/
	/*
	BadicRepresentation<2> x_new = ChangeBase(x_b);
	x_new.sgn = x_s;
	BadicRepresentation<2> y_new = ChangeBase(y_b);
	y_new.sgn = y_s;
	cout << "X_new = " << x_new << endl;
	cout << "Y_new = " << y_new << endl;

	BadicRepresentation<2> z = FastMultiply<2>(x_new, y_new);
	cout << z << endl;
	cout << FundamentalMultiply<2>(x_new, y_new)<<endl;
	*/

	//Stellt sicher, dass sich die Konsolenanwendung nicht schließt
	int tra;
	std::cin >> tra;
	return 0;
}
