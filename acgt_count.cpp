#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
#define READ_SIZE 50
#define BASES 4

string reverse_compliment(string DNA)
{
    string reverse_DNA = DNA;
    int i = 0;
    for(int j = (int)DNA.size()-1; j >= 0; j--)
    {
        if(DNA[j] == 'A')
            reverse_DNA[i] = 'T';
        else if(DNA[j]== 'C')
            reverse_DNA[i] = 'G';
        else if(DNA[j] == 'G')
            reverse_DNA[i] = 'C';
        else if(DNA[j] == 'T')
            reverse_DNA[i] = 'A';
        i++;
    }
    return reverse_DNA;
}

int main(int argc, char **argv)
{
	ifstream inFile;
	vector<int *> acgt_count;
	string genome_string;
	string buffer;
	stringstream ss;
	int read_num;
	string read;
	int pos;
	char direction;

	genome_string = "";

	// Extract genome
	inFile.open(argv[1]);
	while(getline(inFile, buffer))
		genome_string += buffer;
	inFile.close();

	// Initialize table
	for(int y = 0; y < genome_string.size(); y++)
	{
		acgt_count.push_back(new int[BASES]);

		for(int x = 0; x < BASES; x++)
		{
			acgt_count[y][x] = 0;
		}
	}

	// Extract output and fill table
	inFile.open(argv[2]);
	while(getline(inFile, buffer))
	{
		ss << buffer;
		ss >> read_num; // read number
		ss >> read;
		ss >> pos;
		ss >> direction; // direction

		if(direction == '-')
			read = reverse_compliment(read);

		for(int i = 0; i < read.size(); i++)
		{
			int base;
			switch(read[i])
			{
				case 'A':	base = 0;
							break;
				case 'C':	base = 1;
							break;
				case 'G':	base = 2;
							break;
				case 'T':	base = 3;
							break;
			}

			(acgt_count[pos + i][base])++;
		}

	}
	inFile.close();

	// Output results
	for(int y = 0; y < genome_string.size(); y++)
	{
		for(int x = 0; x < BASES; x++)
			cout << acgt_count[y][x] << '\t';
		cout << endl;
	}

	return 0;
}
