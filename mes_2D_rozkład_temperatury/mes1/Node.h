#ifndef Node_h
#define Node_h

using namespace std;

class Node {
public:
	double x, y, t;
	int status; //{0,1}

	Node() { status = 0; };
};

#endif // !Node_h

