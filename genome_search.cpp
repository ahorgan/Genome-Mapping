/*
	Annika Horgan
	CSCI 598
	Spring 2015

*/
#include<iostream>
#include<bitset>
#include<string>
#include<fstream>
#include<vector>
#include<math.h>
using namespace std;
#define SUFFIX_SIZE 6999

string genome_string;
int suffix_array[SUFFIX_SIZE];
string reverse_compliment(string DNA);
bool find(string DNA, int &pos, char &ch);
int count_mismatches(string DNA, int pos);

int main(int argc, char **argv)
{

    ifstream inFile;
    genome_string = "";
    string line;

    // Extract genome from file
    inFile.open(argv[1]);
    while(getline(inFile, line))
    {
        genome_string += line;
    }
    genome_string += "$";
    inFile.close();

    // Extract suffix array from file
    inFile.open(argv[2]);
    int c = 0;
    int tmp;
    while(inFile >> tmp)
    {
        suffix_array[c++] = tmp;
    }
    inFile.close();

    // Extract reads and analyze by line
    inFile.open(argv[3]);
    string read_DNA;
    int count = 0;
    while(getline(inFile, read_DNA))
    {

        int position = -1;
        char plus = '+';
        char minus = '-';
        count++;
        string reverse = reverse_compliment(read_DNA);
        if(find(read_DNA, position, plus) != find(reverse, position, minus))
        {
            cout << count << "		" << read_DNA << "		";
            if(plus == '+')
                cout << position << "		" << plus;
            else if (minus == '-')
                cout << position << "		" << minus;
            cout << endl;
        }

    }
    inFile.close();
    return 0;
}


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

bool find(string DNA, int &pos, char &direction)
{
        bool found = false;
        string seed = DNA.substr(0, 25);
        int Lw, Rw;
        if(seed <= genome_string.substr(suffix_array[0], seed.size()))
            Lw = 0;
        else if(seed > genome_string.substr(suffix_array[SUFFIX_SIZE-1], seed.size()))
            Lw = SUFFIX_SIZE;
        else
        {
            int L = 0;
            int R = SUFFIX_SIZE - 1;
            int M;
            while (R-L > 1)
            {
                M = (L + R)/2;
                if (seed <= genome_string.substr(suffix_array[M], seed.size()))
                    R = M;
                else
                    L = M;
            }
            Lw = R;
            L = 0;
            R = SUFFIX_SIZE - 1;
            while (R-L > 1)
            {
                M = (L + R)/2;
                if (seed >= genome_string.substr(suffix_array[M], seed.size()))
                    L = M;
                else
                    R = M;
            }
            Rw = L;
            if(Rw == Lw && count_mismatches(DNA.substr(25), suffix_array[Rw]+25) <= 3)
            {
                found = true;
                pos = suffix_array[Rw];
            }
        }
        if(!found)
            direction = '*';

        return found;
}

int count_mismatches(string DNA, int pos)
{
    int mismatches = 0;
    for(int i = 0; i < DNA.length(); i++)
    {
        if(DNA[i] != genome_string[pos + i])
            mismatches++;
    }
    return mismatches;
}
