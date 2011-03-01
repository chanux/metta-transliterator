#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define WORDLEN 200 /*Maximum length of a word*/

struct {
	wchar_t character;
	wchar_t secondary;
	wchar_t key;
}vowels[] = {
	{L'අ',L'0',L'a'},{L'අ',L'0',L'A'},
	{L'ආ',L'ා',L'à'},{L'ආ',L'ා',L'â'},
	{L'ඉ',L'ි',L'i'},{L'ඉ',L'ි',L'I'},
	{L'ඊ',L'ී',L'ã'},{L'ඊ',L'ී',L'ä'},
	{L'උ',L'ු',L'u'},{L'උ',L'ු',L'U'},
	{L'ඌ',L'ූ',L'å'},{L'ඌ',L'ූ',L'æ'},
	{L'එ',L'ෙ',L'e'},{L'එ',L'ේ',L'E'},
	{L'ඔ',L'ො',L'o'},{L'ඔ',L'ො',L'O'},
	{L'ං',L'0',L'ý'},{L'ං',L'0',L'ü'}, //Binduva is a vowel/non-vocalic diacritic
	{L'0',L'0',L'0'}
};

struct {
	wchar_t character;
	wchar_t secondary;
	wchar_t key;
}consonants[] = {
	{L'ක',L'ඛ',L'k'},{L'ක',L'ඛ',L'K'},
	{L'ග',L'ඝ',L'g'},{L'ග',L'ඝ',L'G'},
	{L'ච',L'ඡ',L'c'},{L'ච',L'ඡ',L'C'},
	{L'ජ',L'ඣ',L'j'},{L'ජ',L'ඣ',L'J'},
	{L'ත',L'ථ',L't'},{L'ත',L'ථ',L'T'},
	{L'ද',L'ධ',L'd'},{L'ද',L'ධ',L'D'},
	{L'ට',L'ඨ',L'ñ'},{L'ට',L'ඨ',L'ò'},
	{L'ඩ',L'ඪ',L'ó'},{L'ඩ',L'ඪ',L'ô'},
	{L'ප',L'ඵ',L'p'},{L'ප',L'ඵ',L'P'},
	{L'බ',L'භ',L'b'},{L'බ',L'භ',L'B'},
	{L'ල',L'0',L'l'},{L'ල',L'0',L'L'},
	{L'ළ',L'0',L'ë'},{L'ළ',L'0',L'ì'},
	{L'න',L'0',L'n'},{L'න',L'0',L'N'},
	{L'ණ',L'0',L'õ'},{L'ණ',L'0',L'ö'},
	{L'ම',L'0',L'm'},{L'ම',L'0',L'M'},
	{L'ය',L'0',L'y'},{L'ය',L'0',L'Y'},
	{L'ර',L'0',L'r'},{L'ර',L'0',L'R'},
	{L'ව',L'0',L'v'},{L'ව',L'0',L'V'},
	{L'ස',L'0',L's'},{L'ස',L'0',L'S'},
	{L'හ',L'0',L'h'},{L'හ',L'0',L'H'},
	{L'ඤ',L'0',L'¤'},{L'ඤ',L'0',L'¥'},
	{L'ඞ',L'0',L'ï'},{L'0',L'0',L'0'}
};

int isVowel(wchar_t wintChar)
{
	int i=-1;
	while(vowels[++i].character){
		if(wintChar == vowels[i].key)
			return 1;
	}

	return 0;
}

int isAlphabetChar(wchar_t cChar)
{
	if (cChar >=65 && cChar <= 90)
		return 1;
	else if (cChar >=97 && cChar <= 122)
		return 1;
	else if (cChar >=128 && cChar <=254)
		return 1;

	return 0;
}

wchar_t getConsonantChar(wchar_t key)
{
	int i = -1;
	while(consonants[++i].character){
		if(consonants[i].key == key)
			return consonants[i].character;
	}

	return L'0';
}

wchar_t getConsonantSecondary(wchar_t key)
{
	int i = -1;
	while(consonants[++i].character){
		if(consonants[i].key == key)
			return consonants[i].secondary;
	}

	return L'0';
}

wchar_t getVowelChar(wchar_t key)
{
	int i = -1;
	while(vowels[++i].character){
		if(vowels[i].key == key)
			return vowels[i].character;
	}

	return L'0';
}

wchar_t getVowelSecondary(wchar_t key)
{
	int i = -1;
	while(vowels[++i].character){
		if(vowels[i].key == key)
			return vowels[i].secondary;
	}

	return L'0';
}


int isConsonant(wchar_t cChar)
{
	return isAlphabetChar(cChar) && (!isVowel(cChar)) ? 1 : 0;
}

int messWithTheWord(wchar_t *wordIn, FILE *outputFile)
{
	wchar_t wordOut[WORDLEN];
	int i,j = 0;
	int err;

	memset(wordOut, 0, WORDLEN*sizeof(wchar_t));
	
	for(i=0; wordIn[i] != 0; i++){
		if(isAlphabetChar(wordIn[i])){
			if(!isVowel(wordIn[i])){
				if(i == 0)
					wordOut[j++] = getConsonantChar(wordIn[i]);
				else if(wordIn[i] == L'h' && getConsonantSecondary(wordIn[i-1]) != L'0')
					wordOut[j-1] = getConsonantSecondary(wordIn[i-1]);
				//For conjunct letters kva ttha, tva, ntha, nda, ndha, nva
				else if((wordIn[i-1] == L't' && ((wordIn[i] == L't' && wordIn[i+1] == L'h') || wordIn[i] == L'v')) ||
						(wordIn[i-1] == L'n' && (wordIn[i] == L'd' || wordIn[i] == L'v')) ||							 
						(wordIn[i-1] == L'k' && wordIn[i] == L'v')){
					wordOut[j++] = L'්';
					wordOut[j++] = L'‍';
					wordOut[j++] = getConsonantChar(wordIn[i]);
				}
				//For rakaransaya and yansaya
				else if(isConsonant(wordIn[i-1]) && (wordIn[i] == L'r' || wordIn[i] == L'y')){
					wordOut[j++] = L'්';
					wordOut[j++] = L'‍';
					wordOut[j++] = getConsonantChar(wordIn[i]);
				}
				//For touching letters
				else if(isConsonant(wordIn[i-1]) && isConsonant(wordIn[i])){
					wordOut[j++] = L'‍';
					wordOut[j++] = L'්';				
					wordOut[j++] = getConsonantChar(wordIn[i]);
				}							
				else
					wordOut[j++] = getConsonantChar(wordIn[i]);
			}
			else{
				if(i == 0)
					wordOut[j++] = getVowelChar(wordIn[i]);
				else if(!isAlphabetChar(wordIn[i-1]))
					wordOut[j++] = getVowelChar(wordIn[i]);
				else if(isVowel(wordIn[i-1]))
					wordOut[j++] = getVowelChar(wordIn[i]);
				else if(getVowelSecondary(wordIn[i]) != L'0')
					wordOut[j++] = getVowelSecondary(wordIn[i]);
				else if(wordIn[i] == L'ý' || wordIn[i] == L'ü')
					wordOut[j++] = getVowelChar(wordIn[i]); // For binduwa
			}
		}
		else
			wordOut[j++] = (wchar_t) wordIn[i];
	}
			
	if(fwprintf(outputFile, wordOut) == -1){ 
			fprintf(stderr, "Error writing to file!\n");
			return(-1);
	}

	return 0;
}

int main(int argc, char * argv[])
{
	if(argc != 3){
		fprintf(stderr, "Usage:\n\t %s <input file> <output file>\n", argv[0]);
		return(-1);
	}

	FILE *inputFile, *outputFile;
	wchar_t c;
	wchar_t wordIn[WORDLEN];
	wchar_t bracedContent[WORDLEN];

	setlocale(LC_ALL, "");

	inputFile = fopen(argv[1], "rb");
	outputFile = fopen(argv[2], "w");

	memset(wordIn, 0, WORDLEN*sizeof(wchar_t));
	memset(bracedContent, 0, WORDLEN*sizeof(wchar_t));
	
	c = (wchar_t) fgetc(inputFile);

	while(!feof(inputFile)){
		int i = 0, j = 0;

		while(wordIn[i-1] != ' ' && c!= '[' && !feof(inputFile)){
			wordIn[i] = c;
			i++;
			c = (wchar_t) fgetc(inputFile);
		}

		if(messWithTheWord(wordIn, outputFile) != 0){
			fprintf(stderr, "Conversion Eror!\n");
			return -1;
		}

		if(c == '['){
			while(bracedContent[j-1] != ']'){
				bracedContent[j] = c;
				c = (wchar_t) fgetc(inputFile);
				j++;
			}

			if(fwprintf(outputFile, bracedContent) == -1){
				fprintf(stderr, "Error writing to file!\n");
				return(-1);
			}			
		}
		
		memset(wordIn, 0, WORDLEN*sizeof(wchar_t));
		memset(bracedContent, 0, WORDLEN*sizeof(wchar_t));		
	}

	fclose(inputFile);
	fclose(outputFile);
	return 0;
}
