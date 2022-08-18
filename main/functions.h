//declare so it could be used for c files
#ifndef functions
#define functions 
//actual declartion of functions
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//macros for constraints
#define sLength 21
#define maxLine 44
#define maxItems 10
#define maxEntries 150
#define maxFilename 31
#define maxSentence 151
#define maxTranslated 201
#define maxWords 150

//definitions
typedef char String20[sLength];
typedef char Filename[maxFilename];
typedef char Sentence[maxSentence];
typedef char Translated[maxTranslated];
//structs for data
//pair struct
typedef struct Translation{
	String20 strLanguage;
	String20 strMeaning;
}translation;

typedef struct Entry{
	translation arrEntries[maxItems];
}entry;

typedef struct Statistics{
	int nEntryCount;
	int arrItemPerEntry[maxEntries];
	entry nEntries[maxEntries];
}stats;

typedef struct languageCount{
	String20 strLang;
	int nCount;
}languageCount;

//function prototypes
void swap(translation* translate1, translation* translate2);
void wordSort(translation arr[], int n);
void clear_Buffer();
void lowerString(String20 strWord);
void printEntry(translation* curEntry,int nPairs,int nEntryNum);
void updateTranlsation(translation* trans,String20 s1,String20 s2);
void getPairInput(String20 s1,String20 s2);
void getEntryNumber(int* nChoice, int* nValid, int nEntriesCount);
void addEntry(stats* record);
void addTranslation(stats* record);
void displayAllEntries(stats* record);
void deleteEntry(stats* record);
void deleteTranslation(stats* record);
void modifyEntry(stats* record);
void searchWord(stats* record);
void searchTranslation(stats* record);
void exportData(stats* record,FILE** fPtr);
void importData(stats* record,FILE** fPtr);
void dataMenu(stats* record,FILE** fPtr);
void translateMenu(stats* record,FILE** fPtr);
void importDictionary(stats* record,FILE** fPtr);
void page(stats* record,char cChoice,int* nPage,int nEntriesWithPair,int possibleEntries[maxEntries],int* nViewing);
void split(String20 aWords[], int *pWordCount, Sentence sentence);
void identify(stats* record);
void translate(stats* record);
void combine(Sentence result, String20 aWords[], int nWords);
void askAnother(int* nChoice,int* nOk,int* nValid,int nDialogue);
void sortByCount(languageCount langCount[], int nLanguages);
void swapLanguageCount(languageCount *lang1, languageCount *lang2);
int BinarySearch(int key, int arr[], int n);
int checkLanguage(languageCount langCount[],int nLanguages,String20 language);
int duplicate(translation checked[],int nDups,String20 language,String20 meaning);
int checkUnique(translation* curEntry,int nPairs,String20 word);
int checkSpecial(char letter);
#endif
//end of declaration
