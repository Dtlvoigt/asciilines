/*****************************
 **                         **
 **   Asciilines            **
 **   Author: Dylan Voigt   **
 **   HW1 for cs461P        **
 **                         **
 *****************************/

#include <fstream>
#include <iostream>

char **table;
int numRows;
int numCols;

/*void loadFile(std::string filename) ////////////////////////
{
	//std::cout << filename + '\n';
	//std::ifstream* testFile = new std::ifstream(filename);

	std::fstream testFile;
	testFile.open(filename);

	if(!testFile.is_open())
	{
		std::cerr << "\nCannot open " + filename + "\n\n";
		exit(-2);
	}

}*/ /////////////////

void initializeTable(std::ifstream &testFile)
{
	//int xSize, ySize;
	//testFile >> xSize;
	testFile >> numRows;
	//testFile >> ySize;
	testFile >> numCols;
	
	std::cout << '\n' << numRows << " " << numCols << '\n'; ///////
	//std::cout << '\n' << xSize << " " << ySize << '\n';

	//table = new *int[numRows][numCols];
	table = new char*[numRows];
	for(int i = 0; i < numRows; i++)
		table[i] = new char[numCols];

	for(int i = 0; i < numRows; i++)
		for(int j = 0; j < numCols; j++)
			table[i][j] = '.';

	return;
}

void parseCommand(std::ifstream &testFile)
{
	char render, orientation;
	int startRow, startCol, length;
	
	testFile >> render >> startRow >> startCol >> orientation >> length;
	std::cout << render << startRow << startCol << orientation << length << '\n'; //////////

	int xLength = 1;
	int yLength = 1;

	if(orientation == 'h')
		xLength = length;
	if(orientation == 'v')
		yLength = length;

	for(int i = startRow; i < (startRow + yLength); i++)
	{
		for(int j = startCol; j < (startCol + xLength); j++)
		{
			if(i > -1 && i < numRows && j > -1 && j < numCols)
				table[i][j] = render;
		}
	}
}

void printTable()
{
	for(int i = 0; i < numRows; i++) 
	{
		for(int j = 0; j < numCols; j++)
			std::cout << table[i][j] << ' ';
		std::cout << '\n';
	}
}

int main(int argc, char* argv[])
{
	if(argc != 2) 
	{
		std::cerr << "Incorrect number of args.\n";
		return -1;
	}

	std::ifstream testFile;

	testFile.open(argv[1]);
	if(!testFile.is_open())
	{
		std::cerr << "\nCannot open " << argv[1] << "\n\n";
		return -2;
	}

	initializeTable(testFile);

	std::string temp;
	while(!testFile.eof())
	{
		parseCommand(testFile);
		testFile >> std::ws;
		//int c = testFile.peek();
		//if(c == EOF)
			//return 0;
		//getline(testFile, temp);
	}

	//loadFile(argv[1]);

	printTable();

	testFile.close();
	return 0;
}
