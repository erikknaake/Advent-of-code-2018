// Day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

bool areOpositePools(char a, char b)
{
	return a == (b + 32) || a == (b - 32); // Uppercase and lowercase characters are 32 apart in ASCII
}

int main()
{
	std::fstream file("input.txt");
	std::string line;
	std::getline(file, line);
	file.close();

	int i = 0;
	while (i < line.length() - 1)
	{
		if (areOpositePools(line.at(i), line.at(i + 1)))
		{
			line.replace(i, 2, "");
			if (i > 0)
				i--;
		}
		else
			i++;
	}
	std::cout << line.size() << std::endl;
}