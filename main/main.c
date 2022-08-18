/***********************************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
 																				<Adriel Joseph Donato>, DLSU ID# <12189669>
 																				<Arvin Teri Tan>, DLSU ID# <12116304>
************************************************************************************************************************/

/*
Description: A simple translation program
Programmed by: Arvin Teri L Tan and Adriel Joseph Donato S20B
Last modified: 06/15/2022
Version: 2
[Acknowledgements:
https://stackoverflow.com/questions/6891720/initialize-reset-struct-to-zero-null
https://stackoverflow.com/questions/10159230/validating-user-input-for-filenames
https://stackoverflow.com/questions/55273376/let-the-user-specify-a-file-name-in-c
https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
https://stackoverflow.com/questions/55684606/how-do-i-read-a-file-until-a-new-line-is-encounterd
https://stackoverflow.com/questions/7109964/creating-your-own-header-file-in-c
https://www.geeksforgeeks.org/isalnum-function-c-language/ 
]
*/

#include "dataHandler.c"
#include "translatorHandler.c"

int main()
{
	stats record;
	int nChoice,
		nValid,
		nStep =0,
		nRunning = 1;
		
	FILE *dataFile;
	//Main menu
	while(nRunning){
		switch (nStep)
		{
			case 0:
				nChoice = -1;
				nValid = 0;
				while(!nValid){
					printf("Main Menu\n");
					printf("1.) Data Menu\n");
					printf("2.) Translate Menu\n");
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
		      	dataMenu(&record,&dataFile);
			  	nStep = 0;
		      	break;
		      	
		    case 2:
		      	translateMenu(&record,&dataFile);
			  	nStep = 0;
		      	break;
		    
		    case 3:
		    	nRunning = 0;
		    	printf("\nProgram is closing goodbye!");
		    	break;
		}
	}
	return 0;
}

