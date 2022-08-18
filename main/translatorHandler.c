#include "functions.h"

/* 
importDictionary allows the user to choose a file for reference
@param record - the datebase that holds all entries
@param fPtr - a pointer to allow file accessing
*/
void 
importDictionary(stats* record,
				 FILE** fPtr)
{
	int i,
		nPair = 0,
		nEntriesAdded= 0,
		nTempItems = 0;
		
	char* token;
		
	char line[maxLine];
	
	translation temp[maxItems];	
		
	translation* changeTranslation;	
	
	Filename userFile ="";

	printf("\nInput the name of your file: ");
	scanf("%s",userFile);
	//if no file exist then use empty record
	if((*fPtr = fopen(userFile,"r")) == NULL)
		printf("\nNo file with this name will now use empty dictionary\n");
	else{
		*fPtr = fopen(userFile,"r");
		//read all the lines
		while(fgets(line, maxLine, *fPtr) != NULL){
			//if newline then it is a new entry
			if (strcmp(line,"\n") == 0){
				if(record->nEntryCount < maxEntries){
					for(i = 0; i<nTempItems; i++){
						changeTranslation = &record->nEntries[record->nEntryCount].arrEntries[i];
						updateTranlsation(changeTranslation,
										  temp[i].strLanguage,
										  temp[i].strMeaning);
					}
					record->arrItemPerEntry[record->nEntryCount] = nTempItems;
					record->nEntryCount++;
					nEntriesAdded+= 1;
				}
				nTempItems = 0;
			}
			//transfer every translation pair inside the entry
			else{
				line[strlen(line)-1] = '\0';
				nPair = 0;
				token = strtok(line, ": ");
				while (token != NULL){
					if(nPair == 0)
						strcpy(temp[nTempItems].strLanguage,token);
					else if(nPair == 1)
						strcpy(temp[nTempItems].strMeaning,token);
					token = strtok(NULL,  ": ");
					nPair += 1;
				}
				nTempItems += 1;
			}
		}
		fclose (*fPtr);	
	}
}

/* 
checkSpecial checks if it is a ,?!.
@param cLetter - the character to be checked
@return 1 if it is not in .,!? else 0 if it is
*/
int
checkSpecial(char cLetter)
{
	int i;
	//loop through invalid characters to check
	char invalidValues[5] = ".,!?";
	for(i = 0; i < strlen(invalidValues); ++i){
		if(cLetter == invalidValues[i]) 
			return 0;
	}
	return 1;
}

/* 
split tokenizes and splits the sentence to words
@param aWords[] - the arr that will store the words
@param *pWordCount - the word count of the sentence
@param sentence - the sentence to be tokenized and split
Pre-condition: the sentence is at most 150 characters
*/
void 
split(String20 aWords[],
	  int *pWordCount,
	  Sentence sentence)
{
	int i,nIndex = 0;
	//sentence is not empty then check
	if(strlen(sentence) != 0){
		for(i = 0; i <= strlen(sentence);i++){
			//if space or newline the its a new word
			if(sentence[i] == ' ' || sentence[i] == '\0'){
				aWords[*pWordCount][nIndex] = '\0';
				nIndex = 0;
				*pWordCount +=1;
			}
			//if it is not a special character then add it as a letter
			else{
				if(checkSpecial(sentence[i])){
					aWords[*pWordCount][nIndex] = sentence[i];
					nIndex++;
				}
			}
		}
	}
}

/* 
checkLanguage checks if the language has already been counted once or not
@param langCount[] - the arr that will store the language and how many times its present
@param nLanguages - the number of languages
@param language - the language that will be checked
@return index if it is already counted else -1
*/
int
checkLanguage(languageCount langCount[],
			  int nLanguages,
			  String20 language)
{
	int i;
	for(i = 0; i < nLanguages; i++)
		if(strcmp(langCount[i].strLang,language) == 0)
			return i;
	return -1;
}

/* 
duplicate checks if the translation pair is already checked
@param checked[] - the arr that stores the translation pairs checked
@param  nDup - the number of translation pairs
@param language - the language that will be checked
@param meaning - the definition of the language that will be checked
@return 1 if it is already checked else 0
*/
int 
duplicate(translation checked[],
		  int nDups,
		  String20 language,
		  String20 meaning)
{
	int i;
	for(i = 0; i < nDups ;i++)
		if(strcmp(checked[i].strLanguage,language) == 0 
		   && strcmp(checked[i].strMeaning,meaning) == 0)
			return 1;
	return 0;
}

/*
swaps 2 languageCount pointer for the sorting function
@param lang1 - the first language to be swapped
@param lang2 - the second language to be swapped
*/
void
swapLanguageCount(languageCount *lang1, 
				  languageCount *lang2)
{
	languageCount temp;
	temp = *lang1;
	*lang1 = *lang2;
	*lang2 = temp;
}

/*
sorts the array in descending order
@param langCount - the array of languageCounts that is to be sorted
@param nLanguages - the number of languages and its count in the array
*/
void
sortByCount(languageCount langCount[], 
			int nLanguages)
{
	int i, j, max;
	
	for(i = 0; i < nLanguages - 1; i++) {
		max = i;
		for (j = i + 1; j < nLanguages; j++)
			//change maximum if it is less than the current
			if (langCount[max].nCount < langCount[j].nCount)
				max = j;
		//swap the order of the maximum value	
		if (i != max)
			swapLanguageCount(&langCount[i], &langCount[max]);
	}
}

/* 
identify checks the main language of the text
@param record - the datebase that holds all entries
*/
void 
identify(stats* record){
	
	int i,j,
		nWordIndex,
		nWords = 0,
		nLanguages = 0,
		nflag,
		nAvailable,
		nDups,	
		nEntriesCount = record->nEntryCount;
	
	translation curTranslation,
				checked[maxEntries];
				
	Sentence sentence;
	
	String20 aWords[maxWords];
			 
	languageCount langCount[maxWords];
	//get input
	printf("Enter text to be identified: ");
	fgets(sentence, maxSentence, stdin);
	sentence[strlen(sentence) - 1] = '\0';
	//split and tokenize
	split(aWords,&nWords,sentence);
	
	//check if word is in dictionary
	for(nWordIndex = 0; nWordIndex < nWords; nWordIndex++){
		nDups = 0;
		for(i = 0; i < nEntriesCount; i++){
			for(j=0; j < record->arrItemPerEntry[i]; j++){
				curTranslation = record->nEntries[i].arrEntries[j];
				if(strcmp(curTranslation.strMeaning,aWords[nWordIndex]) == 0){
					//flag means if the same translation in different entries is already checked
					nflag = duplicate(checked,
									 nDups,
									 curTranslation.strLanguage,
									 curTranslation.strMeaning);
					if(!nflag){
						updateTranlsation(&checked[nDups],
										  curTranslation.strLanguage,
										  curTranslation.strMeaning);
						nDups += 1;
						nAvailable = checkLanguage(langCount,
												   nLanguages,
												   curTranslation.strLanguage);
												   
						if(nAvailable != -1)
							langCount[nAvailable].nCount += 1;
						else{
							langCount[nLanguages].nCount = 1;
							strcpy(langCount[nLanguages].strLang,curTranslation.strLanguage);
							nLanguages += 1;
						}
					}
				}
			}
		}
	}
	
	//sort the list
	sortByCount(langCount, nLanguages);
	//if there are 0 languages
	if(!nLanguages)
		printf("\nCannot determine language\n");
	else{
		//print the list
		printf("\nWord count list:\n");
		for(i = 0; i < nLanguages; i++)
			printf("%d.)%s-%d\n",i+1,langCount[i].strLang,langCount[i].nCount);
		printf("\n");
		//if there is only one print the first index
		if(nLanguages == 1)
			printf("The main language is %s\n",langCount[0].strLang);
		//if there is more than one print print 1st and 2nd
		else if(nLanguages >= 2){
			printf("The main language is %s\n",langCount[0].strLang);
			printf("The secondary language is %s\n",langCount[1].strLang);
		}
	}
}

/* 
combine concatenates all the splitted translated words
@param result - the string that will store the sentence
@param aWords[] - the arr that contains the splitted sentence to be identified
@param nWords - the word count of the splitted sentence
*/
void 
combine(Translated result,
		String20 aWords[],
		int nWords)
{
	int i;
	result[0] = '\0';
	for(i =0; i < nWords; i++)
		strcat(result,strcat(aWords[i]," "));
	result[strlen(result) - 1] = '\0';
}

/* 
translate allows user to translate a given text
@param record - the datebase that holds all entries
*/
void 
translate(stats* record)
{
	int nWords,
		nPresent,
		nTranslationIndex,
		nWordIndex,
		nEntriesCount = record->nEntryCount,
		nflag,
		nContinue =1,
		nOk,nTransAnother,
		i,j;
		
	String20 strTextLang = "",
			 strTextTranslated = "",
			 aWords[maxWords];
	
	Sentence sentence;
			
	Translated translatedSentence;
	
	translation curTranslation;
	
	//get input
	printf("Enter the language of the text: ");
	scanf("%s",strTextLang);
	clear_Buffer();
	printf("Enter language to translate to: ");
	scanf("%s",strTextTranslated);
	clear_Buffer();
	
	while(nContinue){
		//reset values of variables
		nTransAnother = -1;
		nOk = 0;
		sentence[0] = '\0';
		nWords = 0;
		printf("Enter text to be Translated: ");
		fgets(sentence, maxSentence, stdin);
		sentence[strlen(sentence) - 1] = '\0';
		//split and tokenize
		split(aWords,&nWords,sentence);
		
		for(nWordIndex = 0; nWordIndex < nWords; nWordIndex++){
			nflag = 0;
			for(i = 0; i < nEntriesCount; i++){
				nPresent = 0;
				nTranslationIndex = -1;
				//if it is not yet translated then translate it
				if(!nflag){
					for(j=0; j < record->arrItemPerEntry[i]; j++){
						curTranslation = record->nEntries[i].arrEntries[j];
						//make sure it is inside the dictionary
						if(strcmp(curTranslation.strLanguage,strTextLang) == 0 
						   && strcmp(curTranslation.strMeaning,aWords[nWordIndex])==0)
							nPresent = 1;
						//the translation pair used for translation
						if(strcmp(curTranslation.strLanguage,strTextTranslated) == 0)
							nTranslationIndex = j;
						//if it is inside the dictionary and the translation is available
						if(nPresent && nTranslationIndex != -1){
							nflag = 1;
							strcpy(aWords[nWordIndex],
								   record->nEntries[i].arrEntries[nTranslationIndex].strMeaning);
						}
					}
				}
			}
		}
		//concatenate the whole sentence
		combine(translatedSentence,aWords,nWords);
		printf("\nTranslated sentence:\n%s\n",translatedSentence);
		//ask if another translation is made
		askAnother(&nTransAnother,&nOk,&nContinue,6);
	}
}

/* 
translateMenu allows the user to interact with the translation tools
@param record - the datebase that holds all entries
@param fPtr - a pointer to allow file accessing
*/
void 
translateMenu(stats* record,
			  FILE** fPtr)
{
	
	int nChoice,
		nValid,
		nStep =0,
		nRunning = 1,
		i;
		
	for(i = 0; i < maxEntries;i++)
		record->arrItemPerEntry[i] = 0;
	
	record->nEntryCount =0;
	importDictionary(record,&*fPtr);
	while(nRunning){
		switch (nStep)
		{
			case 0:
				nChoice = -1;
				nValid = 0;
				while(!nValid){
					printf("\nLanguage Translator\n");
					printf("1.) Identify Language\n");
					printf("2.) Translate text\n");
					printf("3.) Exit\n");
					printf("\nInput choice: ");
					scanf("%d",&nChoice);
					clear_Buffer();
					if(nChoice >= 1 && nChoice <=3)
						nValid = 1;
					else
						printf("\nInvalid number please enter again\n");
				}
				nStep = nChoice;
				break;
				
		    case 1:
		      	identify(record);
			  	nStep = 0;
		      	break;
		    
		    case 2:
		      	translate(record);
			  	nStep = 0;
		      	break;
		    
		    case 3:
		    	nRunning = 0;
		    	*record = (stats){0};
		    	printf("\nReturning to main menu\n\n");
		    	break;
		}
	}
}

