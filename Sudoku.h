#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
using namespace std;

class Sudoku{
	public:
		void GiveQuestion();
		void ReadIn();
		void Solve();
		void checkpossible(int q[][12]);
		int noanswer(int c[][12]);
	private:
		int q[12][12];		
};

#endif
