#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "GlobalData.h"

using namespace std;

GlobalData::GlobalData(const string dataFile) {
	ifstream data;
	data.open(dataFile.c_str());

	string line;
	stringstream ss;

	getline(data, line);
	ss = stringstream(line);
	ss >> this->H>>line;
	cout << this->H << " " << line << endl;

	getline(data, line);
	ss = stringstream(line);
	ss >> this->B >> line;
	cout << this->B<< " " << line << endl;

	getline(data, line);
	ss = stringstream(line);
	ss >> this->nH >> line;
	cout << this->nH << " " << line << endl;

	getline(data, line);
	ss = stringstream(line);
	ss >> this->nB >> line;
	cout << this->nB << " " << line << endl;
	getline(data, line);
	ss = stringstream(line);
	ss >> this->alfa >> line;
	cout << this->alfa << " " << line << endl;
	getline(data, line);
	ss = stringstream(line);
	ss >> this->k >> line;
	cout << this->k << " " << line << endl;
	getline(data, line);
	ss = stringstream(line);
	ss >> this->cp >> line;
	cout << this->cp<< " " << line << endl;
	getline(data, line);
	ss = stringstream(line);
	ss >> this->ro >> line;
	cout << this->ro<< " " << line << endl;
	getline(data, line);
	ss = stringstream(line);
	ss >> this->t8 >> line;
	cout << this->t8<< " " << line << endl;
	getline(data, line);
	ss = stringstream(line);
	ss >> this->t0 >> line;
	cout << this->t0<< " " << line << endl;
	getline(data, line);
	ss = stringstream(line);
	ss >> this->dt >> line;
	cout << this->dt<< " " << line << endl;

	data.close();

	this->nh = nB*nH;
	this->ne = (nB - 1)*(nH - 1);

	cout << nh << " nh" << endl << ne << " ne" << endl;
}