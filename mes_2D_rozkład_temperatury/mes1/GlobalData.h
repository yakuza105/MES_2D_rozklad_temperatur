#ifndef GlobalData_h
#define GlobalData_h

#include <string>

using namespace std;

class GlobalData {
public:
	double H, B, nH, nB, nh, ne , k, alfa ,cp,ro , t8 , t0 ,dt;

	GlobalData(const string dataFile);
};

#endif // !GlobalData_h

