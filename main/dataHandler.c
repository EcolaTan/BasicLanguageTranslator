#include "functions.h"

/* 
swap switches the position of 2 strings during wordSort
@param translate1 - a pointer that will be swapped
@param translate2 - a pointer that will be swapped
Pre-condition: s1 and s2 are valid strings
*/
void 
swap(translation* translate1,
	 translation* translate2)
{
	translation temp;
	temp = *translate1;
	*translate1 = *translate2;
	*translate2 = temp;
}

/* 
wordSort sorts an entry by language
@param arr - an array containing the translations in an entry
@param n - the number of elements inside arr
Pre-condition: arr is an entry of the dictionary
*/
void 
wordSort(translation arr[],
		 int n) 
{
    int i, j;

    for(i = 1; i < n; i++){
        for(j = i; j > 0 && strcmp(arr[j].strLanguage,arr[j-1].strLanguage) < 0; j--){
			swap(&arr[j],&arr[j-1]);
        }
    }
}

/* 
BinarySearch searchs a key inside an array
@param key - the item to be searched
@param arr - the array to be searched
@param n - the number of elements inside arr
@return index of key if present in array else return -1 if not found
Pre-condition: key is an integer
*/
int
BinarySearch(int key, 
			 int arr[], 
			 int n)
{
	int low = 0, high = n - 1, mid;
	int nFound = 0;
	while(!nFound && low <= high){
		mid = low + (high - low)/2;
		if (key == arr[mid])
			nFound = 1;
		else if (key < arr[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	if(nFound)
		return mid;
	else
		return -1;
}

/*
This function clears the input stream to avoid causing an infinite loop
*/
void 
clear_Buffer()
{
    int userInput;
    /*clear input until a newline and if it is the end of a file*/
    while
		((userInput = fgetc (stdin)) != EOF && userInput != '\n');
}

/* 
lowerString converts the string to lowercase
@param strChecked - the string to be lowered
*/
void
lowerString(String20 strWord)
{
	int i;
	for(i = 0; strWord[i]; i++)
  		strWord[i] = tolower(strWord[i]);
}

/* 
printEntry prints an entry of the database
@param curEntry - the entry to be printed
@param nPairs - the translations count inside an entry
@param nEntryNum - the number of the entry
Pre-condition: curEntry is inside the database
*/
void
printEntry(translation* curEntry,
		   int nPairs,
		   int nEntryNum)
{
	translation curTranslation;
	int j;
	printf("\nEntry #%d\n",nEntryNum+1);
	for(j=0; j < nPairs; j++){
		printf("%d.) ",j+1);
		curTranslation = curEntry[j];
		printf("%s: %s\n",curTranslation.strLanguage,
						  curTranslation.strMeaning);
	}
}

/* 
updateTranlsation changes the value of a translation pair
@param trans - the translation pair that is going to be modified
@param s1 - the language that will be assigned to the translation
@param s2 - the meaning that will be assigned to the translation
Pre-condition: trans is a translation pair inside the database
*/
void 
updateTranlsation(translation* trans,
				  String20 s1,
				  String20 s2)
{
	strcpy(trans->strLanguage,s1);
	strcpy(trans->strMeaning,s2);
}

/* 
getPairInput asks the user for an input for the translation pair
@param s1 - the language that will be assigned to the translation
@param s2 - the meaning that will be assigned to the translation
Pre-condition: s1 and s2 is a string based on the assumptions
*/
void 
getPairInput(String20 s1,
			 String20 s2)
{
	printf("\nInput language: ");
	scanf("%s",s1);
	clear_Buffer();
	printf("Input translation: ");
	scanf("%s",s2);	
	clear_Buffer();
}

/* 
getEntryNumber asks the user which entry he wants
@param nChoice - a pointer that store the users choice
@param nValid - a pointer that checks if the chosen option is valid or not
@param nEntriesCount - number of array available
Pre-condition: nEntriesCount is greater or equal to 1
*/
void 
getEntryNumber(int* nChoice, 
			   int* nValid,
			   int nEntriesCount)
{
	scanf("%d",nChoice);
	clear_Buffer();
	if(*nChoice >= 1 && *nChoice <= nEntriesCount)
		*nValid = 1;
	else
		printf("\nInvalid entry number returning to main menu\n");
}

/* 
checkUnique check if the language is inside the entry
@param curEntry - the entry to be printed
@param nPairs - the number of pairs inside the entry
@param word - the language to be checked
Pre-condition: nEntriesCount is greater or equal to 1
@return 1 language is present else return 0
*/
int
checkUnique(translation* curEntry,int nPairs,String20 word){
	String20 language;
	int j;

	for(j=0; j < nPairs; j++){
		strcpy(language,curEntry[j].strLanguage);
		if(strcmp(language,word) == 0)
			return 1;
	}
	return 0;
}

/* 
askAnother asks if the user wants to continue using a certain functionality
@param nChoice - the pointer that store the user's inputs
@param nOk - the sentinel value to terminate loop
@param nValid - the sentinel value of the main function
@param nDialogue - the value that determines which gui is used by this function
@return 1 language is present else return 0
*/

void
askAnother(int* nChoice,
		   int* nOk,
		   int* nValid,
		   int nDialogue)
{
	while(!*nOk){
		switch (nDialogue)
		{
			case 1:
		    	printf("\nDo you want to add another translation for this entry\n1.)yes\n2.)no\n");
		    	break;
		
		    case 2:
		    	printf("\nDo you want to delete another pair\n1.)yes\n2.)no\n");
		    	break;
		    
		    case 3:
		    	printf("\nDo you want to still delete something\n1.)yes\n2.)no\n");
		    	break;
		    	
		    case 4:
		    	printf("\nWhich do you want to replace\n1.)Language\n2.)Translation\n");
		    	break;
		    	
		    case 5:
		    	printf("\nDo you want to modify another pair\n1.)yes\n2.)no\n");
		    	break;
		    	
		    case 6:
		    	printf("\nDo you want to translate another text\n1.)Yes\n2.)No\n");
		    	break;
		    
		}
		scanf("%d",nChoice);
		clear_Buffer();
		if(*nChoice == 1 || *nChoice == 2)
			*nOk = 1;
		else
			printf("\nInvalid number please enter again\n");
		if(*nChoice == 2)
			*nValid = 0;
	}	
}

/* 
addEntry adds a new entry to the database
@param record - the datebase that holds all entries
*/
void 
addEntry(stats* record)
{
	
	String20 strLang = "",
		 	 strMean = "",
			 strRespond = "";
			 
	int i,j,
		nFlag = 0,
		nFound = 0,
		nAdded = 0,
		nValid = 1, 
		nAddAnother, 
		nOk,
		nEntriesCount;
	
	//if not pointer its ready only
	translation curTranslation;
	//pointer for the translation to be changed
	translation* changeTranslation;	
	//total number of entries	
	nEntriesCount = record->nEntryCount;
	
	if(nEntriesCount < maxEntries){
		//take input and validate
		getPairInput(strLang,strMean);
		//loop through all entries
		for(i = 0; i < nEntriesCount; i++){
			nFlag = 0;
			//check if language pair is inside an entry
			for(j=0; j < record->arrItemPerEntry[i]; j++){
				curTranslation = record->nEntries[i].arrEntries[j];
				if(strcmp(curTranslation.strLanguage,strLang) == 0 
				   && strcmp(curTranslation.strMeaning,strMean) == 0){
					nFlag = 1;
					nFound = 1;
				}
			}
			//if an entry has this pair then sort and display it
			if(nFlag){
				wordSort(record->nEntries[i].arrEntries,
						 record->arrItemPerEntry[i]);
				printEntry(record->nEntries[i].arrEntries,
						   record->arrItemPerEntry[i],i);
			}
		}
		//the first translation pair in the entry
		changeTranslation = &record->nEntries[nEntriesCount].arrEntries[0];
		
		if(nFound){
			printf("\n");
			while(strcmp(strRespond,"yes")!= 0 && strcmp(strRespond,"no")!= 0){
				printf("Is this a new entry yes/no: ");
				scanf("%s",strRespond);
				clear_Buffer();
				lowerString(strRespond);
				if(strcmp(strRespond,"yes")!= 0 && strcmp(strRespond,"no")!= 0)
					printf("\nInvalid input please enter again\n");
			}
			//if this is a new entry update
			if(strcmp(strRespond,"yes")== 0){
				updateTranlsation(changeTranslation,
								  strLang,
								  strMean);
				record->arrItemPerEntry[nEntriesCount]++;
				nAdded = 1;
			}
		}
		//add since no duplicate
		else{
			updateTranlsation(changeTranslation,
							  strLang,
							  strMean);
			record->arrItemPerEntry[nEntriesCount]++;
			nAdded = 1;
		}
		if(nAdded){
		 	do{
		 		// adds a new traslation pair
		 		if(record->arrItemPerEntry[nEntriesCount] < maxItems){
		 			strLang[0] = '\0';
			 		strMean[0] = '\0';
			 		nAddAnother = -1;
			 		nOk = 0;
					// ask if the user wants to input another translation
					askAnother(&nAddAnother,&nOk,&nValid,1);
					// if yes then add a translation pair to the entry
					if(nAddAnother == 1){
			 			getPairInput(strLang,strMean);
				 		//check if language already exist
				 		if(!checkUnique(record->nEntries[nEntriesCount].arrEntries,
						 				record->arrItemPerEntry[nEntriesCount],
										 strLang)){
				 			changeTranslation = &record->nEntries[nEntriesCount].arrEntries[record->arrItemPerEntry[nEntriesCount]];
							updateTranlsation(changeTranslation,
										      strLang,
											  strMean);
							record->arrItemPerEntry[nEntriesCount]++;
						 } 
						 else
						 	printf("\nThere is already a translation pair with this language\n");
					}
				}
				// # of translation pairs will exceed the maxItems
				else{
					printf("\nThere is not enough space in this entry\n");
					nValid = 0;
				}
			}while(nValid);
			record->nEntryCount++;
		}
	}	
	else
		printf("\nThere is not enough space for a new entry\n");
}

/* 
addTranslation adds a new translation to an entry
@param record - the datebase that holds all entries
*/
void
addTranslation(stats* record)
{
	int possibleEntries[maxEntries],
		i,j,
		nFound = 0,
		nFlag =0,
		nEntriesWithPair = 0,
		nEntryChoice,
		nPresent,
		nOk,
		nAddAnother,
		nContinue,
		nEntriesCount;
	
	String20 strLang = "",
		 	 strMean = "",
		 	 strTransLang = "",
		 	 strTransMean = "";
	
	//if not pointer its ready only
	translation curTranslation;
	//pointer for the translation to be changed
	translation* changeTranslation;	
	//total number of entries	
	nEntriesCount = record->nEntryCount;
	
	getPairInput(strLang,strMean);
	
	//loop through all entries
	for(i = 0; i < nEntriesCount; i++){
		nFlag = 0;
		//check if language pair is inside an entry
		for(j=0; j < record->arrItemPerEntry[i]; j++){
			curTranslation = record->nEntries[i].arrEntries[j];
			
			if(strcmp(curTranslation.strLanguage,strLang) == 0 && 
			   strcmp(curTranslation.strMeaning,strMean) == 0 && 
			   !nFlag){
				nFlag = 1;
				nFound = 1;
				possibleEntries[nEntriesWithPair] = i;
				nEntriesWithPair++;
			}
		}
		//print the entry
		if(nFlag){
			wordSort(record->nEntries[i].arrEntries,
				 record->arrItemPerEntry[i]);
				 
			printEntry(record->nEntries[i].arrEntries,
					   record->arrItemPerEntry[i],
					   i);
		}
	}
	//there is no such entry that has the input
	if(!nFound){
		printf("\nPlease add this entry first!\n");
	}
	else{
		nContinue = 1;
		nPresent = -1;
		nEntryChoice = -1;
		//when there is more than one entry
		if(nEntriesWithPair > 1){
			//check if the input of the user is a found entry
			while(nPresent == -1){
				printf("\nEntries that match your input:\n");
				for(i = 0; i < nEntriesWithPair; i++)
					printf("Entry #%d\n",possibleEntries[i]+1);
				printf("Choose entry: ");
				scanf("%d",&nEntryChoice);
				clear_Buffer();
				nPresent = BinarySearch(nEntryChoice-1, 
										possibleEntries,
										nEntriesWithPair);
				if(nPresent == -1)
					printf("Invalid entry please try again\n");
			}
		}
		else
			nEntryChoice = possibleEntries[0]+1;
		
		printf("\nEntry chosen: %d",nEntryChoice);
		while(nContinue){
			//if translation less than 10
			if(record->arrItemPerEntry[nEntryChoice-1] < maxItems){
				strTransLang[0] = '\0';
		 		strTransMean[0] = '\0';
		 		
				getPairInput(strTransLang,strTransMean);
				if(!checkUnique(record->nEntries[nEntryChoice-1].arrEntries,
								record->arrItemPerEntry[nEntryChoice-1],
								strTransLang)){
					//this part updates the translation
					changeTranslation = &record->nEntries[nEntryChoice-1].arrEntries[record->arrItemPerEntry[nEntryChoice-1]];
				
					updateTranlsation(changeTranslation,
								  	  strTransLang,
								  	  strTransMean);
								  
					record->arrItemPerEntry[nEntryChoice-1]++;	
				}
				else
					printf("\nThere is already a translation pair with this language\n");
				nOk = 0;
				nAddAnother = -1;
				//ask if add another translation
				askAnother(&nAddAnother,&nOk,&nContinue,1);
			}
			//not enough space
			else{
				printf("\nThere is not enough space for a new translation\n");
				nContinue = 0;
			}
		}
	}
}

/* 
displayAllEntries allows the user to view the entries
@param record - the datebase that holds all entries
*/
void 
displayAllEntries(stats* record)
{
	int i,
		nPage = 0,
		nEntriesCount,
		nViewing = 1;
		
	char cChoice ='\0';	
	
	nEntriesCount = record->nEntryCount;
	
	//sort all entries
	for(i = 0; i < nEntriesCount; i++)
		wordSort(record->nEntries[i].arrEntries,
			 record->arrItemPerEntry[i]);
	
	//if 0 entries just print message
	if(nEntriesCount == 0)
		printf("\nNo available entries\n");
	else{
		//while the user is viewing
		while(nViewing){ 
			printEntry(record->nEntries[nPage].arrEntries,
				   	   record->arrItemPerEntry[nPage],
				       nPage);
	
			cChoice = '\0';
			printf("\nView all entries menu\nN.)Next\nP.)Previous\nX.)Exit\n");
			scanf("%c",&cChoice);
			clear_Buffer();
			//to catch lower and uppercase
			cChoice = tolower(cChoice);
			//if there is next entry print else warn user
			if(cChoice == 'n'){
				if(nPage + 1 >= nEntriesCount)
					nPage = 0;
				else
					nPage += 1;
			}
			//if there is previous entry print else warn user
			else if(cChoice == 'p'){
				if(nPage - 1 < 0)
					nPage = nEntriesCount-1;
				else
					nPage -= 1;
			}
			//stop viewing
			else if(cChoice == 'x')
				nViewing = 0;
			else
			   	printf("\nInvalid character please enter again\n");
		}
	}
}

/* 
deleteEntry allows the user to delete an entry
@param record - the datebase that holds all entries
*/
void 
deleteEntry(stats* record)
{
	int i,k,
		nChoice,
		nValid = 0,
		nFlag = 0,
		nEntriesCount = record->nEntryCount;
		
	if(nEntriesCount > 0){
		printf("\nChoose an entry to be deleted from the %d entries: ",nEntriesCount);
		getEntryNumber(&nChoice,
					   &nValid,
					   nEntriesCount);
		
		if(nValid){
			nChoice -=1;
			//loop all entries
			for(i = nChoice; i < record->nEntryCount; i++){
		    	//if the deletion is not yet made
				if(!nFlag){
		    		nFlag = 1;
		    		//modify entry item count array
		    		for(k = i; k < record->nEntryCount; k++){
		    			record->arrItemPerEntry[k] = record->arrItemPerEntry[k+1];
		    			record->nEntries[k] = record->nEntries[k+1];
					}
		    		record->nEntryCount-=1;
		    		i--;	
		    	} 
	    	}
	    	printf("\nSuccessfully deleted entry# %d\n",nChoice+1);
		}
	}
}

/* 
deleteTranslation allows the user to delete a translation inside an entry
@param record - the datebase that holds all entries
*/
void 
deleteTranslation(stats* record)
{
	int i,j,k,
		nChoice,
		nValid = 0,
		nOk,
		nReturn,
		nContinue = 1,
		nTranslation,
		nAnother,
		nReturnMenu,
		nFlag,
		nEntriesCount = record->nEntryCount;
	// if there is atleast 1 entry
	if(nEntriesCount > 0){
		printf("\nChoose an entry that includes the translation be deleted from %d entries: ",
			   nEntriesCount);
		getEntryNumber(&nChoice, &nValid,nEntriesCount);
		// if the entry chosen is present
		if(nValid){
			nChoice -=1;
			printf("\nSelect a translation pair to delete from this entry\n");
			while(nContinue){
				printEntry(record->nEntries[nChoice].arrEntries,
						   record->arrItemPerEntry[nChoice],
						   nChoice);
				nFlag = 0;
				printf("\nTranslation number: ");
				scanf("%d",&nTranslation);
				clear_Buffer();
				nTranslation -= 1;
				if(nTranslation >= 0 && nTranslation < record->arrItemPerEntry[nChoice]){
					// if only 1 translation pair delete the entry
					if(record->arrItemPerEntry[nChoice] == 1){
						for(i = nChoice; i < record->nEntryCount; i++){
					    	//if the entry number is found
							if(!nFlag){
					    		nFlag = 1;
					    		//modify entry item count array
					    		for(k = i; k < record->nEntryCount; k++){
					    			record->arrItemPerEntry[k] = record->arrItemPerEntry[k+1];
					    			record->nEntries[k] = record->nEntries[k+1];
								}
					    		record->nEntryCount-=1;
					    		i--;	
					    	} 
				    	}
					   	printf("\nDeleting entry since no more elements inside\n");
					    nContinue = 0;
					}
					//if there are more than 1 just delete the translation
					else{
						for(i = nTranslation; i < record->arrItemPerEntry[nChoice]; i++){
							if(!nFlag){
								nFlag = 1;
								for(j = i; j < record->arrItemPerEntry[nChoice]; j++)
									record->nEntries[nChoice].arrEntries[j] = record->nEntries[nChoice].arrEntries[j+1];
								record->arrItemPerEntry[nChoice]-=1;
								i--;
							}		    	
					   	}
					   	printf("\nSuccessfully deleted translation\n");
					    nAnother = -1;
					    nOk = 0;
					    // ask if another translaton is deleted
					    askAnother(&nAnother,&nOk,&nContinue,2);
					}
				} 
				// if the translation chosen is not a valid number then ask if delete will continue
				else{
					nReturnMenu = -1;
					nReturn = 0;
					askAnother(&nReturnMenu,&nReturn,&nContinue,3);	
				}
			}
		}
	}
}

/* 
modifyEntry allows the user to modify a translation inside the entry
@param record - the datebase that holds all entries
*/
void
modifyEntry(stats* record)
{
	int nChoice,
		nValid = 0,
		nPair,
		nContinue = 1,
		nFirst,
		nOk,
		nTemp,
		nModify,
		nAnother,
		nEntriesCount = record->nEntryCount;
		
	String20 strInput = "";
	//if there is atleast 1 entry
	if(nEntriesCount > 0){
		printf("\nChoose an entry that includes the translation be modified from %d entries: ",
			   nEntriesCount);
		getEntryNumber(&nChoice,
					   &nValid,
					   nEntriesCount);
		//if chosen entry is valid
		if(nValid){
			nChoice -=1;
			while(nContinue){
				
				nOk = 0;
				strInput[0] = '\0';
				nFirst =-1;
				printEntry(record->nEntries[nChoice].arrEntries,
						   record->arrItemPerEntry[nChoice],
						   nChoice);
				//asks for which translation pair
				printf("\nTranslation number: ");
				scanf("%d",&nPair);
				clear_Buffer();
				nPair -= 1;
				// pair to be modified exists
				if(nPair >= 0 && nPair < record->arrItemPerEntry[nChoice]){
					//asks for word that is going to be used for the modification
					printf("\nWord that will replace the value: ");
					scanf("%s",strInput);
					clear_Buffer();
					//ask what is going to be modified the language or the definition
					nFirst = -1;
					nTemp = 0;
					//added temp for place holder to meet other functions
					askAnother(&nFirst,&nOk,&nTemp,4);
					//change the language
					if(nFirst == 1){
						if(!checkUnique(record->nEntries[nChoice].arrEntries,
										record->arrItemPerEntry[nChoice],
										strInput))
							strcpy(record->nEntries[nChoice].arrEntries[nPair].strLanguage,strInput);
						else
							printf("\nThere is already a translation pair with this language\n");
					}
					//change the definition
					else if(nFirst == 2)
						strcpy(record->nEntries[nChoice].arrEntries[nPair].strMeaning,strInput);
					//ask if the another modification is going to be made
					nAnother = -1;
					nModify = 0;
					askAnother(&nAnother,&nModify,&nContinue,5);
				}
				else
					printf("\nThis is not a valid pair please input another one\n");
			}
		}
	}
}

/* 
page allows the user to view entries with the word or translation pair
@param record - the datebase that holds all entries
@param nChoice - the users choice
@param nPage - the entry# where the user is at
@param nEntriesWithPair - entries that have the requirement
@param nIndex - the index of the entry to be displayed
@param possibleEntries[maxEntries] - the entries that can be viewed
@param nViewing - status to exit the display view option
*/
void 
page(stats* record,
	 char cChoice,
	 int* nPage,
	 int nEntriesWithPair,
	 int possibleEntries[maxEntries],
	 int* nViewing)
{
	//to catch lower and uppercase
	cChoice = tolower(cChoice);
	//if there is no next entry print cycle back to the first
	if(cChoice == 'n'){
		if(*nPage + 1 >= nEntriesWithPair)
			*nPage = 0;
		else
			*nPage += 1;
	}
	//if there is no previous entry print cycle back to the last
	else if(cChoice == 'p'){
		if(*nPage - 1 < 0)
			*nPage = nEntriesWithPair-1;
		else
			*nPage -= 1;
	}
	//stop viewing
	else if(cChoice == 'x')
		*nViewing = 0;
	else
		printf("\nInvalid character please enter again\n");
}


/* 
searchWord allows the user to view entries with the word input
@param record - the datebase that holds all entries
*/
void
searchWord(stats* record)
{
	
	int possibleEntries[maxEntries], 
		i,j,
		nPage = 0,
		nEntriesWithPair =0,
		nViewing = 1,
		nFlag = 0,
		nIndex,
		nEntriesCount = record->nEntryCount;
	
	char cChoice = '\0';	
	
	String20 strInput = "";
	
	translation curTranslation;
	
	printf("\nWord to be searched: ");
	scanf("%s",strInput);
	clear_Buffer();
	
	for(i = 0; i < nEntriesCount; i++){
		nFlag = 0;
		//check if language pair is inside an entry
		for(j=0; j < record->arrItemPerEntry[i]; j++){
			curTranslation = record->nEntries[i].arrEntries[j];
			if(strcmp(curTranslation.strMeaning,strInput) == 0 
					  && !nFlag){
				nFlag = 1;
				possibleEntries[nEntriesWithPair] = i;
				nEntriesWithPair++;
			}
		}
	}
	// no available entries meet the condition
	if(!nEntriesWithPair)
		printf("\nNo entries found with this word\n");
	// user is move to display all entries that has the word
	else{
		for(i = 0; i < nEntriesWithPair; i++)
			wordSort(record->nEntries[possibleEntries[i]].arrEntries,
					 record->arrItemPerEntry[possibleEntries[i]]);
		nPage = 0;
				
		//enter view entries display
		while(nViewing){
			//display the current entry
			nIndex = possibleEntries[nPage];
			printEntry(record->nEntries[nIndex].arrEntries,
				       record->arrItemPerEntry[nIndex],
				       nIndex);
			//ask input
			cChoice = '\0';
			printf("\nView all entries menu\nN.)Next\nP.)Previous\nX.)Exit\n");
			scanf("%c",&cChoice);
			clear_Buffer();
			//process user choice
			page(record,
				 cChoice,
				 &nPage,
				 nEntriesWithPair,
				 possibleEntries,
				 &nViewing);
		}
	}
}

/* 
searchTranslation allows the user to view entries with the translation pair input
@param record - the datebase that holds all entries
*/
void
searchTranslation(stats* record)
{
	
	int possibleEntries[maxEntries], 
		i,j,
		nPage = 0,
		nEntriesWithPair =0,
		nViewing = 1,
		nFlag = 0,
		nIndex,
		nEntriesCount = record->nEntryCount;
		
	char cChoice = '\0';
		
	String20 strLang = "",
		 	 strMean = "";
	
	translation curTranslation;
	
	getPairInput(strLang,strMean);
	
	for(i = 0; i < nEntriesCount; i++){
		nFlag = 0;
		//check if language pair is inside an entry
		for(j=0; j < record->arrItemPerEntry[i]; j++){
			curTranslation = record->nEntries[i].arrEntries[j];
			if(strcmp(curTranslation.strLanguage,strLang) == 0
			   && strcmp(curTranslation.strMeaning,strMean) == 0
			   && !nFlag){
				nFlag = 1;
				possibleEntries[nEntriesWithPair] = i;
				nEntriesWithPair++;
			}
		}
	}
	//if word is not present
	if(!nEntriesWithPair)
		printf("\nNo entries found with this pair\n");
	//allow user to view all entries that has the translation pair
	else{
		
		for(i = 0; i < nEntriesWithPair; i++)
			wordSort(record->nEntries[possibleEntries[i]].arrEntries,
					 record->arrItemPerEntry[possibleEntries[i]]);
					 
		while(nViewing){
			//display the current entry
			nIndex = possibleEntries[nPage];
			printEntry(record->nEntries[nIndex].arrEntries,
				       record->arrItemPerEntry[nIndex],
				       nIndex);
			//ask input
			cChoice = '\0';
			printf("\nView all entries menu\nN.)Next\nP.)Previous\nX.)Exit\n");
			scanf("%c",&cChoice);
			clear_Buffer();
			//process user choice
			page(record,
				 cChoice,
				 &nPage,
				 nEntriesWithPair,
				 possibleEntries,
				 &nViewing);
		}
	}
}

/* 
exportData saves the data to a file
@param record - the datebase that holds all entries
@param fPtr - a pointer to allow file accessing
*/
void
exportData(stats* record,
		   FILE** fPtr)
{
	int i,j;
	Filename userFile ="";
	translation curTranslation;
	printf("\nInput a name for your file: ");
	scanf("%s",userFile);
	//write all entries to the file
	if ((*fPtr = fopen(userFile,"w")) != NULL){
		//loop through all entries
		for(i = 0; i < record->nEntryCount; i++){
			for(j=0; j < record->arrItemPerEntry[i]; j++){
				curTranslation = record->nEntries[i].arrEntries[j];
				//write with the following format word: word
				fprintf(*fPtr, "%s: %s\n",
						curTranslation.strLanguage,
						curTranslation.strMeaning);
			}
			fprintf (*fPtr, "\n");
		}
		fclose (*fPtr);
	} 
	else
		printf("\nUnable to save data into the file\n");
}

/* 
importData allows the user to import data from a file
@param record - the datebase that holds all entries
@param fPtr - a pointer to allow file accessing
*/
void 
importData(stats* record,
		   FILE** fPtr)
{
	
	int i,
		nAdd =-1,
		nPair = 0,
		nEntriesAdded= 0,
		nTempItems = 0,
		nFileEntry = 0;
		
	char* token;	
	
	char line[maxLine];
	
	translation temp[maxItems];
				
	translation* changeTranslation;	
	
	Filename userFile ="";

	printf("\nInput the name of your file: ");
	scanf("%s",userFile);
	//if file dosen't exist
	if((*fPtr = fopen(userFile,"r")) == NULL)
		printf("\nNo file with this name found failed to import data\n");
	else{
		*fPtr = fopen(userFile,"r");
		nFileEntry = 0;
		//if its not end of file
		while(fgets(line, maxLine, *fPtr) != NULL){
			//if it is a new entry
			if (strcmp(line,"\n") == 0){
				nAdd = -1;
				//if there are space for new entries
				if(record->nEntryCount < maxEntries){
					//ask to import or skip entry
					do{
						printf("\nTotal entries added from this file = %d\n",
							   nEntriesAdded);
						printEntry(temp,nTempItems,nFileEntry);
						printf("\nDo you want to import this entry\n1.)Add\n2.)Skip\n");
						scanf("%d",&nAdd);
						if(nAdd != 1 && nAdd != 2)
							printf("Invalid input try again\n");
					}while(nAdd != 1 && nAdd != 2);
						
					nFileEntry +=1;
						
					if(nAdd == 1){
						for(i = 0; i<nTempItems; i++){
							changeTranslation = &record->nEntries[record->nEntryCount].arrEntries[i];
							updateTranlsation(changeTranslation,
											  temp[i].strLanguage,
											  temp[i].strMeaning);
						}
						record->arrItemPerEntry[record->nEntryCount]= nTempItems;
						record->nEntryCount++;
						nEntriesAdded+= 1;
					}
				}
				nTempItems = 0;
			}
			//if it is the same entry tokenize and add to current entry
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
dataMenu allows the user to interact with the data tools
@param record - the datebase that holds all entries
@param fPtr - a pointer to allow file accessing
*/
void 
dataMenu(stats* record,
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
	//the menu of possible operations a user can use
	while(nRunning){
		switch (nStep)
		{
			case 0:
				nChoice = -1;
				nValid = 0;
				while(!nValid){
					printf("\nData Manager\n");
					printf("1.) Add entry\n");
					printf("2.) Add Translation\n");
					printf("3.) View all entries\n");
					printf("4.) Delete an entry\n");
					printf("5.) Delete a translation\n");
					printf("6.) Modify an entry\n");
					printf("7.) Search word\n");
					printf("8.) Search Translation\n");
					printf("9.) Export data\n");
					printf("10.) Import data\n");
					printf("11.) Exit\n");
					printf("\nInput choice: ");
					scanf("%d",&nChoice);
					clear_Buffer();
					if(nChoice >= 1 && nChoice <=11)
						nValid = 1;
					else
						printf("\nInvalid number please enter again\n");
				}
				nStep = nChoice;
				break;
				
		    case 1:
		      	addEntry(record);
			  	nStep = 0;
		      	break;
		    
		    case 2:
		    	addTranslation(record);
		    	nStep = 0;
		    	break;
			
			case 3:
				displayAllEntries(record);
				nStep = 0;
		    	break;
		    	
		    case 4:
		    	displayAllEntries(record);
		    	deleteEntry(record);
		    	nStep = 0;
		    	break;
		    
			case 5:
				displayAllEntries(record);
		    	deleteTranslation(record);
		    	nStep = 0;
		    	break;
		    	
		    case 6:
		    	displayAllEntries(record);
		    	modifyEntry(record);
		    	nStep = 0;
		    	break;
		    
		    case 7:
		    	searchWord(record);
		    	nStep = 0;
		    	break;
		    	
			case 8:
		    	searchTranslation(record);
		    	nStep = 0;
		    	break;
		    	
		    case 9:
		    	exportData(record,&*fPtr);
		    	nStep = 0;
		    	break;
		    	
		    case 10:
		    	importData(record,&*fPtr);
		    	nStep = 0;
		    	break;
		    	
		    case 11:
		    	nRunning = 0;
		    	*record = (stats){0};
		    	printf("\nReturning to main menu\n\n");
		    	break;
		}
	}
}
