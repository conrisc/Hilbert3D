//Konrad Cielecki 273278
//Pracownia_1 2016

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846

unsigned int n;
double s, u, d, x, y, z, fi, psi, segLenght, m_x, m_y, xs, ys, zs;
FILE *fp;

// Funkcja "rysujaca" odcinek
void drawSegment() {	
	//rotate
		//Obrot wzgledem OY
		xs = x*cos(psi) - z*sin(psi);
		zs = x*sin(psi) + z*cos(psi);
		//Obrot wzgledem OX
		ys = y*cos(fi) - zs*sin(fi);
		zs = y*sin(fi) + zs*cos(fi);

	//Normalizacja
	xs = xs*d/(zs+d) + m_x;
	ys = ys*d/(zs+d) + m_y;
	//print
	fprintf(fp, "%f %f lineto\n", xs, ys);
}

// Funkcja odpowiedzialna za poprawne "skrecanie zolwia"
void segment(int dir) {
	if (dir == 0)
		y -= segLenght;
	else if (dir == 1)
		z += segLenght;
	else if (dir == 2)
		x += segLenght;
	else if (dir == 3)
		y += segLenght;
	else if (dir == 4)
		z -= segLenght;
	else  // (dir == 5)
		x -= segLenght;
	drawSegment();
}

// Funkcja "rysujaca" krzywa Hilberta3D
void draw(int n, int T[6]) {  
	if (n < 1) {		
		return;
	}
	else {
		//1
		int T2[6] = { T[3],T[5],T[1],T[4],T[0],T[2] };
		draw(n - 1, T2);			//[3|5|1|4|0|2] - od T
		segment(T[1]);				//DOWN	
		//2
		int T3[6] = { T2[3],T2[5],T2[1],T2[4],T2[0],T2[2] };
		draw(n - 1, T3);			//[3|5|1|4|0|2] - ale od T2
		segment(T[5]);				//WEST
		//3
		draw(n - 1, T3);			// powtorzenie T3
		segment(T[0]);				//UP	
		//4
		int T4[6] = { T[1],T[0],T[2],T[5],T[4],T[3] };
		draw(n - 1, T4);			//[1|0|2|5|4|3] - od T
		segment(T[2]);				//NORTH	
		//5
		draw(n - 1, T4);			//powtorzenie T4
		segment(T[1]);				//DOWN	
		//6
		int T5[6] = { T[2],T[4],T[3],T[0],T[5],T[1] };
		draw(n - 1, T5);			//[2|4|3|0|5|1] - od T 
		segment(T[3]);				//EAST	
		//7
		draw(n - 1, T5);			//powtorzenie T5
		segment(T[0]);				//UP
		//8
		int T6[6] = { T2[0],T2[1],T2[4],T2[5],T2[2],T2[3] };
		draw(n - 1, T6);				//[0|1|4|5|2|3] od T2
	}

}



int main(int argc, char *argv[])
{
	//			 [UP|DN|N|E|S|W]
	int tab[6] = { 3, 0,1,2,4,5 };

	// Wczytywanie danych
	if (argc == 10) {
		n = (int)atof(argv[1]);
		s = atof(argv[2]);
		u = atof(argv[3]);
		d = atof(argv[4]);
		x = atof(argv[5]);
		y = atof(argv[6]);
		z = atof(argv[7]);
		fi = atof(argv[8]);
		psi = atof(argv[9]);
	}
	else {
		fprintf(stderr, "Za malo argumentow! Wpisz je w programie <n,s,u,d,x,y,z,fi,psi>:");
		scanf("%d %lf %lf %lf %lf %lf %lf %lf %lf", &n, &s, &u, &d, &x, &y, &z, &fi, &psi);
	}
	// Ustawienia wektora przesuwajacego obiekt na srodek kartki
	m_x = s / 2 - x - (psi / 90 * u / 2);
	m_y = s / 2 - y - (fi / 90 * u / 2);
	// Zamiana podanych stopni na radiany
	fi = (-fi)*M_PI / 180;
	psi = (-psi)*M_PI / 180;
	// Ustawianie dlugosci pojedynczego odcinka
	segLenght = u / (pow(2, n) - 1);
	// Przesuwanie ukladu wspolrzednych obiektu w centrum
	x += u / 2;
	y += u / 2;
	// Obrocenie i rzutowanie punktu startowego
		//Obrot wzgledem OY
		xs = x*cos(psi) - z*sin(psi);
		zs = x*sin(psi) + z*cos(psi);
		//Obrot wzgledem OX
		ys = y*cos(fi) - zs*sin(fi);
		zs = y*sin(fi) + zs*cos(fi);
	//Normalizacja
	xs = xs*d / (zs + d) + m_x;
	ys = ys*d / (zs + d) + m_y;


	// Otworzenie/Utworzenie pliku do zapisu
	if ((fp = fopen("Hilbert3D.eps", "w")) == NULL) {
		printf("Nie mogê otworzyæ pliku test.txt do zapisu!\n");
		exit(1);
	}
	// Zapis do pliku
	fprintf(fp, "%%!PS-Adobe-2.0 EPSF-2.0\n%%%%BoundingBox: 0 0 %f %f\nnewpath\n%f %f moveto\n", s, s, xs, ys);
	draw(n, tab);
	fprintf(fp, ".4 setlinewidth\nstroke\nshowpage\n%%%%Trailer\n%%EOF");

	// Zamkniecie pliku
	fclose(fp);

	return 0;
}

