#include <iostream>

using namespace std;

void Array2d(){

	/// 100*200

	const int row = 100;
	const int column = 200;

	std::vector<vector<double>*> *X = new std::vector<std::vector<double>*>();
	std::vector<double>  *Y = new std::vector<double>();

	for(int j = 0; j < row; j++){
		Y->clear();
		for(int i = 0; i < column; i++){
			Y->push_back(11111111);
		}
		X->push_back(Y);
	}

	///////////////////////////////
	/// check it:
	/// output row = 1, column = 2:

	cout<<X->at(99)->size()
		<<endl
		<<X->at(1)->at(2)
		<<endl;

	delete X, Y;


	///// after delete it, if you want to use again:

	X = new std::vector<std::vector<double>*>();
	Y = new std::vector<double>();

	for(int j = 0; j < row; j++){
		Y->clear();
		for(int i = 0; i < column; i++){
			Y->push_back(22222222);
		}
		X->push_back(Y);
	}

}