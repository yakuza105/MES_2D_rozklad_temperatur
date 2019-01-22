#ifndef Grid_h
#define Grid_h

using namespace std;

class Grid {
public:
	Node *ND;
	Element *EL;
	double alfa;
	double k;
	double cp;
	double ro;
	double t8;
	double t0;
	double dt;
	const static int r = 121;
	//double globalH[16][16];

	Grid(GlobalData data);
	void jakobian(double e[4][4] , double ni[4][4], int roz );
	void transpozycja(double tab[4][4]);
	void mnozeniemaciezy(double tab[4][4], double tab2[4][4] , double tab3[4][4][4]);
	void ca³kowanie(int roz);
	void warunki(int roz);
	void calka2(double alfa, int roz );
	void calkaC(int roz,double N[4][4] , double cp,double ro);
	void lokaleH(int roz);
	void globalH(int roz ,double globalH[r][r],double globalC[r][r]);
	void wektorP(int roz,double alfa,double t8 , double globalP[r]);

	//double[4][4] cos();

};

#endif // !Grid_h

