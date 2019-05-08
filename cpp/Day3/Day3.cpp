/*
--- Day 3: No Matter How You Slice It ---
The Elves managed to locate the chimney-squeeze prototype fabric for Santa's suit (thanks to someone who helpfully wrote its box IDs on the wall of the warehouse in the middle of the night). Unfortunately, anomalies are still affecting them - nobody can even agree on how to cut the fabric.

The whole piece of fabric they're working on is a very large square - at least 1000 inches on each side.

Each Elf has made a claim about which area of fabric would be ideal for Santa's suit. All claims have an ID and consist of a single rectangle with edges parallel to the edges of the fabric. Each claim's rectangle is defined as follows:

The number of inches between the left edge of the fabric and the left edge of the rectangle.
The number of inches between the top edge of the fabric and the top edge of the rectangle.
The width of the rectangle in inches.
The height of the rectangle in inches.
A claim like #123 @ 3,2: 5x4 means that claim ID 123 specifies a rectangle 3 inches from the left edge, 2 inches from the top edge, 5 inches wide, and 4 inches tall. Visually, it claims the square inches of fabric represented by # (and ignores the square inches of fabric represented by .) in the diagram below:

...........
...........
...#####...
...#####...
...#####...
...#####...
...........
...........
...........
The problem is that many of the claims overlap, causing two or more claims to cover part of the same areas. For example, consider the following claims:

#1 @ 1,3: 4x4
#2 @ 3,1: 4x4
#3 @ 5,5: 2x2
Visually, these claim the following areas:

........
...2222.
...2222.
.11XX22.
.11XX22.
.111133.
.111133.
........
The four square inches marked with X are claimed by both 1 and 2. (Claim 3, while adjacent to the others, does not overlap either of them.)

If the Elves all proceed with their own plans, none of them will have enough fabric. How many square inches of fabric are within two or more claims?

To begin, g
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Claim {
	Claim(std::string line)
	{
		x = std::stoi(line.substr(line.find('@') + 2, line.find(',') - line.find('@') - 2));
		y = std::stoi(line.substr(line.find(',') + 1, line.find(':') - line.find(',') - 1));
		width = std::stoi(line.substr(line.find(':') + 1, line.find('x') - line.find(':') - 1));
		height = std::stoi(line.substr(line.find('x') + 1, line.size() - line.find('x')));
	}
	unsigned int x, y, width, height;
};

struct Claims
{
public:
	const static unsigned int SIZE = 1000;

	Claims()
	{
		std::vector<unsigned int> temp = std::vector<unsigned int>(SIZE, 1);
		field = { SIZE, temp };
	}

	void applyClaim(Claim claim)
	{
		for (unsigned int i = claim.x; i < claim.x + claim.width; i++)
			for (unsigned int j = claim.y; j < claim.y + claim.height; j++)
				field[i][j]++;
	}

	unsigned int getFieldsClaimedMoreThen(int claimedMin)
	{
		unsigned int numOfSquares = 0;
		for (unsigned int i = 0; i < SIZE; i++)
			for (unsigned int j = 0; j < SIZE; j++)
				if (field[i][j] > claimedMin) 
					numOfSquares++;
		return numOfSquares;
	}
private:
	std::vector<std::vector<unsigned int>> field;
};

int main()
{
	std::fstream file("input.txt");
	std::string line;
	Claims claims;
	while (file.is_open() && std::getline(file, line))
	{
		Claim claim(line);
		claims.applyClaim(claim);
	}
   std::cout << claims.getFieldsClaimedMoreThen(2);
}
