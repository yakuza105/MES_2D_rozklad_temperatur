#ifndef globalElement_h
#define globalElement_h
using namespace std;
class globalElement
{
public:
	const static int roz = 121;
	double globalH[roz][roz];
	double globalC[roz][roz];
	double globalP[roz];
	double cdt[roz][roz];
	double Hcdt[roz][roz];
	double P[roz];
	double w[roz];
	globalElement(double zero);
void cprzezdt(double dt);
void lastH();
void lastP(double t0[roz]);
void gauss(int n);//n - rozmiar
	~globalElement(void);
};
#endif
