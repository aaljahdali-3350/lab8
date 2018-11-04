// //
// //
// //optimized by: Abdullah_Aljahdali
// //date:
// //List all students who worked on this program code.
// //
// //Lab-8 framework
// //This program does spell checking of a text article.
// //
// //Original author: Gordon Griesel, May 2016
// //Updated March 2018
// //
// //Assignment:
// //Optimize this program for running time.
// //Your time will be compared to other students in the class.
// //
// //Test like this:
// //   $ time ./lab8 article
// //
// //
// #include <cstdlib>
// #include <cstring>
// #include <cctype>
// #include <fstream>
// using namespace std;
// enum {
// LOWER,
// UPPER };
// const char dictname[] = "/usr/share/dict/cracklib-small";
// int spell_check(char *text);
// int search_for_word(ifstream &din, char *xword);
//
// int main(int argc, char *argv[])
// {
// 	if (argc < 2) {
// 		printf("\nUsage: %s <file name>\n\n", argv[0]);
// 		return 0;
// 	}
// 	char fname[256];
// 	strcpy(fname, argv[1]);
// 	printf("\n");
// 	printf("Lab-8 program optimization.\n");
// 	printf("spell-check this file: **%s**\n", fname);
// 	ifstream fin(fname);
// 	if (fin.fail()) {
// 		printf("ERROR: opening **%s** for input\n", fname);
// 		return 0;
// 	}
// 	int nMisspelled = 0;
// 	char word[256];
// 	fin >> word;
// 	while (!fin.eof()) {
// 		nMisspelled += spell_check(word);
// 		fin >> word;
// 	}
// 	fin.close();
// 	printf("\nTotal misspelled words: %i\n", nMisspelled);
// 	printf("Program complete.\n\n");
// 	return 0;
// }
//
// int spell_check(char *xword)
// {
// 	ifstream din(dictname);
// 	if (din.fail()) {
// 		printf("Dictionary file failed to open!\n\n");
// 		exit(1);
// 	}
// 	int found = search_for_word(din, xword);
// 	if (found != 1) {
// 		printf("  Misspelled: %s\n", xword);
// 	}
// 	din.close();
// 	if (found)
// 		return 0;
// 	else
// 		return 1;
// }
//
// void convert_to_a_case(int case_flag, char *str)
// {
// 	//convert a c-string to a case
// 	//case_flag: 0 = lower
// 	//           1 = upper
// 	int slen = strlen(str);
// 	for (int i=0; i<slen; i++) {
// 		if (case_flag == 0)
// 			str[i] = (char)tolower(str[i]);
// 		if (case_flag == 1)
// 			str[i] = (char)toupper(str[i]);
// 	}
// }
//
// void strip_comma_period(char *str)
// {
// 	//Strip comma or period from end of a string.
// 	char *p = str;
// 	while (*p)
// 		++p;
// 	--p;
// 	while (p >= str && (*p == ',' || *p == '.')) {
// 		*p = '\0';
// 		--p;
// 	}
// }
//
// int search_for_word(ifstream &fin, char *word)
// {
// 	//returns: 0 = word not found.
// 	//         1 = word found.
// 	//
// 	strip_comma_period(word);
// 	//
// 	//Go to the top of the dictionary file.
// 	fin.clear();
// 	fin.seekg(0, fin.beg);
// 	//Now search through the whole file looking for the word.
// 	//Search top to bottom.
// 	char line[256];
// 	int found = 0;
// 	fin >> line;
// 	while (!fin.eof()) {
// 		//Make sure both words are the same case.
// 		convert_to_a_case(LOWER, line);
// 		convert_to_a_case(LOWER, word);
// 		//Now compare words for spelling match.
// 		if (line[0] == word[0])
// 			if (strcmp(line, word) == 0)
// 				found = 1;
// 		fin >> line;
// 	}
// 	if (found == 1)
// 		return 1;
// 	else
// 		return 0;
// }
//
//
//
//
//
//
//
//optimized by:
//date:
//List all students who worked on this program code.
//
//Lab-8 framework
//This program does spell checking of a text article.
//
//Original author: Gordon Griesel, May 2016
//Updated March 2018
//
//Assignment:
//Optimize this program for running time.
//Your time will be compared to other students in the class.
//
//Test like this:
//   $ time ./lab8 article
//
//
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
typedef std::vector<string> string_t;

enum {
LOWER,
UPPER };

const char dictname[] = "/usr/share/dict/cracklib-small";

string_t loadFileToArray(char const *fname);
int spell_check(string_t const text, string_t const dict);


void tolower(char *str) {
	int slen = strlen(str);
	for (int i=0; i<slen; i++)
		str[i] = (char)tolower(str[i]);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("\nUsage: %s <file name>\n\n", argv[0]);
		return 0;
	}
	char fname[256];
	strcpy(fname, argv[1]);
	printf("\n");
	printf("Lab-8 program optimization.\n");
	// printf("Loading cracklib file\n");
	string_t dictionary = loadFileToArray(dictname);
	string_t words = loadFileToArray(fname);
	int nMisspelled = spell_check(words, dictionary);
	printf("\nTotal misspelled words: %i\n", nMisspelled);
	printf("Program complete.\n\n");
	return 0;
}

void strip_comma_period(char *str) {
	// Strip comma or period from end of a string.
	char *p = str;
	do {++p;} while (*p);
	--p;
	while ((*p == ',' || *p == '.') && p >= str) {
		*p = '\0';
		--p;
	}
}

string_t loadFileToArray(char const *fname) {
	ifstream din(fname);
	if (din.fail()) {
		printf("Dictionary file failed to open!\n\n");
		exit(1);
	}
	//
	//Go to the top of the dictionary file.
	din.clear();
	din.seekg(0, din.beg);
	int size = 0;
	char line[256];
	string_t dict = string_t(52876);

	do {
		din >> line;
		tolower(line);
		strip_comma_period(line);
		dict.push_back(line);
		size += 1;
	} while (!din.eof());

	din.close();
	return dict;
}

int spell_check(string_t const words, string_t const dict) {
	int misspelled = 0;
	char word[256];
	for(int i=0; i<words.size(); i++) {
			//Now search through the whole file looking for the word.
			//Search top to bottom.
			strcpy(word, words[i].c_str());
		if (!(find(dict.begin(), dict.end(), word) != dict.end())) {
			printf("  Misspelled: %s\n", word);
			misspelled += 1;
		}
	}
	return misspelled;
}
