/*****************************
 **                         **
 **   Asciilines.cpp        **
 **   Author: Dylan Voigt   **
 **   CS461P HW1            **
 **                         **
 *****************************/

#include <fstream>
#include <iostream>

char **table;
int numRows;
int numCols;

//reads canvas size from file and initializes 2d array
void initializeTable(std::ifstream &testFile)
{
	testFile >> numRows;
	testFile >> numCols;
	
	table = new char*[numRows];
	for(int i = 0; i < numRows; i++)
		table[i] = new char[numCols];

	for(int i = 0; i < numRows; i++)
		for(int j = 0; j < numCols; j++)
			table[i][j] = '.';

	return;
}

//parses and executes individual commands from file
void parseCommand(std::ifstream &testFile)
{
	char render, orientation;
	int startRow, startCol, length;
	
	//read info into variables
	testFile >> render >> startRow >> startCol >> orientation >> length;

	int xLength = 1;
	int yLength = 1;

	if(orientation == 'h')
		xLength = length;
	if(orientation == 'v')
		yLength = length;

	//add render character to table if it falls within the canvas size
	for(int i = startRow; i < (startRow + yLength); i++)
	{
		for(int j = startCol; j < (startCol + xLength); j++)
		{
			if(i > -1 && i < numRows && j > -1 && j < numCols)
				table[i][j] = render;
		}
	}
}

//prints contents of 2d array to screen
void printTable()
{
	for(int i = 0; i < numRows; i++) 
	{
		for(int j = 0; j < numCols; j++)
			std::cout << table[i][j];
			//std::cout << table[i][j] << ' ';
		std::cout << '\n';
	}
}

int main(int argc, char* argv[])
{
	//exit if input is invalid
	if(argc != 2) 
	{
		std::cerr << "EXIT: Incorrect number of args.\n";
		return -1;
	}

	//attempt to open specified file
	std::ifstream testFile;
	testFile.open(argv[1]);

	//exit if file cannot be opened
	if(!testFile.is_open())
	{
		std::cerr << "EXIT: Cannot open " << argv[1] << '\n';
		return -2;
	}

	//set array bounds and initialize with '.'s
	initializeTable(testFile);

	//run commands until eof is reached
	while(!testFile.eof())
	{
		parseCommand(testFile);
		testFile >> std::ws; //eliminate whitespace
	}

	//print contents of array
	printTable();

	testFile.close();
	return 0;
}
