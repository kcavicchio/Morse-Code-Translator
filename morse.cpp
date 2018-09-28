#include <iostream>
#include <fstream>
#include <string>
//#include <array>
using namespace std;

/*
	This program reads and writes from 2 files, encoded.txt and alphabet.txt
	It translates whatever is in encoded.txt to english in alphabet.txt
	Or it translates whatever is in alphabet.txt to morse code in encoded.txt
*/

const int MAX = 40;

string cipher[MAX] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
								"....", "..", ".---", "-.-", ".-..", "--", "-.",
								"---", ".--.", "--.-", ".-.", "...", "-", "..-",
								"...-", ".--", "-..-", "-.--", "--..", 
								".----", "..---", "...--", "....-", ".....", 
								"-....", "--...", "---..", "----.", "-----", 
								".-.-.-", "--..--", "..--.."};
string letters[MAX] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
								"k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
								"u", "v", "w", "x", "y", "z", "1", "2", "3", "4",
								"5", "6", "7", "8", "9", "0", ".", ",", "?"};
string upper[MAX] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
								"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
								"U", "V", "W", "X", "Y", "Z" };

bool isPunctuation(char c)
{
	switch (c)
	{
	case '.':
	case ',':
	case '?':
	case '!':
		return true;
	default: 
		return false;
	}
}

string getChar(string code)
{
	for (int i = 0; i < MAX; i++)
	{
		if (code == cipher[i])
		{
			return letters[i];
		}
	}
	return "";
}

string translateCode(string code)
{
	string nextChar;
	string nextWord;
	string output;
	char current;
	char translated;

	for (int i = 0; i < code.size(); i++) //loop through all characters contained in 'code'
	{
		current = code[i];
		if (current == '.' || current == '-')
		{
			nextChar += current;
		}
		else if (current == '…')
		{
			nextChar += "...";
		}
		else if (current == '‘' || current == '’')
		{
			nextWord += (getChar(nextChar) + "'");
			nextChar = "";
		}
		else if (current == ' ' /*&& nextChar != ""*/)
		{
			nextWord += getChar(nextChar); 
			nextChar = "";
		}
		else if (current == ',')
		{
			nextWord += (getChar(nextChar));
			nextChar = "";
			if (output.size() > 0 && output[output.size() - 1] == ' ')
			{
				output = output.substr(0, output.size() - 1);
			}
			output += ", ";
		}
		else if (current == '/')
		{
			if (nextChar != "")
			{
				translated = getChar(nextChar)[0];
				if (isPunctuation(translated))
				{
					if (nextWord.size() > 0 && nextWord[nextWord.size() - 1] == ' ')
					{
						nextWord = nextWord.substr(0, nextWord.size() - 1);
					}
					else if (output.size() > 0 && output[output.size() - 1] == ' ')
					{
						output = output.substr(0, output.size() - 1);
					}
				}
				nextWord += translated;
				nextChar = "";
			}
			output += (nextWord + " ");
			nextWord = "";
		}
		else if (current == '\n')
		{
			if (nextChar != "")
			{
				nextWord += getChar(nextChar);
				nextChar = "";
			}
			output += (nextWord + current);
			nextWord = "";
		}
		else
		{
			nextWord += (getChar(nextChar) + current);
			nextChar = "";
		}
	}
	return output;

}

string getCipher(string letter)
{
	for (int i = 0; i < MAX; i++)
	{
		if (letter == letters[i] || letter == upper[i])
		{
			return cipher[i];
		}
	}
	return letter;
}

string encodePlainText(string plain)
{
	string output;
	for (int i = 0; i < plain.size(); i++)
	{
		if (plain[i] == '\n')
		{
			output += '\n';
		}
		else if (plain[i] == ' ')
		{
			output += "/";
		}
		else
		{
			output += (getCipher(plain.substr(i, 1)) + " ");
		}
	}
	return (output + '\n');
}

string importFile(string fileName)
{
	ifstream file(fileName);
	string output;
	string line;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			output = output + line + "\n";
		}
		file.close();
	}
	return output;
}

void exportFile(string fileName, string input)
{
	ofstream file(fileName);
	if (file.is_open())
	{
		file << input;
		file.close();
	}
}

int main()
{
	//cout << cipher.size();


	int option;
	cout << "Select\n1) Encode\n2) Decode\n";
	cin >> option;
	
	if (option == 1)
	{
		string plain;
		plain = importFile("C:\\Users\\Karen\\Documents\\ProgramProjects\\translator\\alphabet.txt");
		cout << plain;

		//plain = the entire contents of alphabet.txt
		string output = encodePlainText(plain);
		exportFile("C:\\Users\\Karen\\Documents\\ProgramProjects\\translator\\encoded.txt", output);
		cout << output;
	}
	
	if (option == 2)
	{
		string code;
		code = importFile("C:\\Users\\Karen\\Documents\\ProgramProjects\\translator\\encoded.txt");
		cout << code;

		//now code = the entire contents of 'encoded.txt'
		string output = translateCode(code);
		exportFile("C:\\Users\\Karen\\Documents\\ProgramProjects\\translator\\alphabet.txt", output);
		cout << output;
	}
} 