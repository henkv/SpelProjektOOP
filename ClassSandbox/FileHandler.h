#pragma once
#include <string>
#include <fstream>
using namespace std;

template<typename T>
class FileHandler
{
	private:
	string fileName_;
	ifstream inFile_;
	ofstream outFile_;

	public:
	FileHandler(string fileName);
	virtual ~FileHandler();

	void read(T& data);
	void write(T const& data);
};

template<typename T>
FileHandler<T>::FileHandler(string fileName)
	: fileName_(fileName)
{}

template<typename T>
FileHandler<T>::~FileHandler()
{}

template<typename T>
void FileHandler<T>::read(T& data)
{
	inFile_.open(fileName_, ios::in | ios::binary);
	inFile_.read((char*)&data, sizeof(T));
	inFile_.close();
}

template<typename T>
void FileHandler<T>::write(T const& data)
{
	outFile_.open(fileName_, ios::out | ios::binary);
	outFile_.write((char*)&data, sizeof(T));
	outFile_.close();
}
