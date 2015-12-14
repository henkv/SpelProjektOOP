#include <iostream>
#include <fstream>
#include "FileHandler.h"

using namespace std;

class HighScore
{
	public:
	char name_[4];
	int score_;

	HighScore(char name[], int score)
	{
		score_ = score;
		name_[0] = name[0];
		name_[1] = name[1];
		name_[2] = name[2];	
		name_[3] = '\0';
	}
};

void main()
{
	
	FileHandler<HighScore> fileHandler("highscore.bin");

	HighScore winner("DON", 51050);

	//fileHandler.write(winner);


	HighScore who("", 0);
	fileHandler.read(who);

	cout << who.name_ << " " << who.score_ << endl;

	system("pause");
}