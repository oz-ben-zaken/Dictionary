/*
Assignment: 4
Campus: Ashdod
name: Oz Ben Zaken
ID: 204015614
*/


#define _CRT_SECURE_NO_WARNINGS
//include to librarys
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define WORD_MAX_SIZE 80 + 1    //max size of word 80   +1 for null
#define DEFINITION_MAX_SIZE 200 + 1  //max size of definition 200   +1 for null

//defines used by the function dictionary size
#define MAX_DINAMIC 1000000  
#define MIN_DINAMIC 1
#define TRASH 200

//enum for dinamic arrey to see if they succseed
typedef enum { ERROR = -1, FALSE, TRUE }boolean;  

                         ///////////////////////////////////   functions   ///////////////////////////////

//function that take acion when a dinamic arrey creation didnt work or when we got to the end of the program
//ether way the function gets pointer char*** to dinamic arrey and free all the dinamic arreys we created along the program
void free_dictionary(char***);

//function that get an int from the user and return the int if it in the range, else return 0
int dictionary_size();

//function that get a char*** pointer to dinamic arrey and place and ask from the user to enter for this place the word and her definitions
int creat_page(char***, int);


                                         ///////////   functions for correction of words    ///////////
//recursive function that gets a char*** pointer to dinamic arrey and use caps_word on each of the **(arrey+i)
//and then change the first letter to upper case
void correct_words(char***);
//recursive function that gets a char* pointer to dinamic arrey(string) and changed all the letter to lower case
void caps_word(char* );

                                       ///////////   functions for correction of definitions    ///////////
//recursive function that gets a char*** pointer to dinamic arrey and use definitions on each of the (*arrey+1)
void correct_definition(char***);
//recursive function that gets a char** pointer to dinamic arrey and use caps_definitions on each of the *(arrey+i)
//and then change the first letter to upper case
void definitions(char**);
//recursive function that gets a char* pointer to dinamic arrey and chnage all the letters to lower case except firsts letter that comes after .
void caps_definition(char*);

                                         ///////////   functions for sorting the dictionary    ///////////
//recursive function that gets a char*** pointer to dinamic arrey and sort it by using qsort algoritem
void sort_dictionary(char***, int, int);
//function that gets a char*** pointer to dinamic arrey and to places at that arrey and changed between thos places
void swap_p(char***, int, int);

                                 ///////////   functions for removing similar words in the dictionary    ///////////
//function that gets a char**** pointer to pointer for dinamic arrey and pointer to the full size the arrey. the function check if there is similar words
//and send the place of the later word to remove_word.
void remove_similar_words(char****, int*);
//function that gets a char*** pointer to pointer for dinamic arrey, the place of the word to remove and pointer to the full size of the arrey.
//the function will free all the word for removal related dinamic arrey, and remove this place from the arrey while reducing the size by 1
void remove_word(char****, int, int*);

                                       ///////////   functions for searching the dictionary    ///////////
//function that gets a char*** pointer to dinamic arrey and the size of that arrey and start the searching phase of words in that arrey
void search_dictiaonary(char***, int);
//recursive function that gets a char*** pointer to dinamic arrey string of the word to search and 2 integer that state the range of places
//at the arrey which get smaller with each call to the function
void search_word(char***, char[], int, int);
//function that gets a char** pointer to dinamic arrey and print the word at that place and all of here definitions
void print_page(char**);


//////////////////////////   main  ////////////////////////
int main(){
	char*** dictionary = NULL;     
	int i, check = 0, size_of_dictionary=0;   //defining and setting of variables
	printf("welcome to The Dictionary\n");
	do{                  //asking for number of words until user enter a correct input
		printf("Please state how many word you want to enter the dictionary\n");
        size_of_dictionary = dictionary_size();     //getting size if correctly inputed else getting 0 
	} while (size_of_dictionary == 0);
	dictionary = (char***)calloc((size_of_dictionary + 1), sizeof(char**));  //creat dinamic arrey(+1 for null at the end) and point dictionary to the arrey
	if (dictionary == NULL){               //checking that we created the arrey
		printf("ERROR! couldnt create memory\n");
		return 0;    //end program
	} //end if
	for (i = 0; i < size_of_dictionary; i++){
		check = creat_page(dictionary+i,i+1);   //creating the words and definition, returning (ERROR)-1 if dinamuc creation didnt work
		if (check ==  ERROR ) {
			printf("ERROR! couldnt create memory\n");
			free_dictionary(dictionary);            //free all the dinamic arrey we created
			return 0;   //end program
		}   //end if
	}   //end for
	correct_words(dictionary);    //calling for function
	correct_definition(dictionary);      //calling for function
	sort_dictionary(dictionary, 0, size_of_dictionary - 1);  //calling for function
	remove_similar_words(&dictionary, &size_of_dictionary);  //calling for function
	search_dictiaonary(dictionary, size_of_dictionary-1);  //calling for function
	free_dictionary(dictionary);  //calling for function
	printf("\n\n*****************************\n    have a good day!    \n*****************************\n");
	return 0;    //end program
} //end main


//////////////////////////////////////////////////////   FUNCTIONS   ////////////////////////////////////////////

//function that free all the dinamic arrey we created for the dictionary
void free_dictionary(char*** dictionary){
	int i = 0, j = 0;
	while (*(dictionary + i) != NULL){               //while the next place value in the (char**)arrey is not null
		while (*(*(dictionary + i) + j) != NULL){    //while the next place value in the (char*)arrey is not null
			free(*(*(dictionary + i) + j));       //free memory (char*)
			j++;                  //j+1
		} //end while
		free(*(dictionary + i));   //free memory (char**)
		i++;         // i+1
	}  // end while
	free(dictionary);   //free memory (char***)
}  //end function

//function that return the size that the user want if its with-in the range of number allowed or 0 if not
int dictionary_size(){
	int size = 0;
	char trash[TRASH];    //temp string to clean the buffer after each scanf  (in case user enter string)
	scanf("%d", &size);   //user input to size
	gets(trash);        //clean null / string
	if ( size >= MIN_DINAMIC && size < MAX_DINAMIC)   //if size in range while max is 1 million (a ridiculosly high range)
		return size;
	return 0;
} //end of program

//function that get a char*** pointer to dinamic arrey and place and ask from the user to enter for this place the word and her definitions
//then function then will creat for each word and definithon dinamic string
int creat_page(char*** page, int i){
	char word[WORD_MAX_SIZE], definition[DEFINITION_MAX_SIZE];  //creating 2 string with max length for word and definitions
	int number_of_definition, j = 0;       //creating and settiong of variables
	do{
		printf("Please enter number of definitions for the: %d word\n", i);
		number_of_definition = dictionary_size();           //check for number of definithions (from the user) to be a correct input
	} while (number_of_definition == 0);
	*page = (char**)calloc((number_of_definition + 2), sizeof(char*));  //creating of dinamic arrey for the word and her definitions pointers
	if (*page == NULL)                                                  //(number of definitions +1(for word) +1(for null at the end)
		return -1;    //checking that we created the arrey
	printf("please enter the word (max 80 chars). press Enter to finish\n");
	scanf("%s", word);      //user enter the word
	getchar();
	**page = (char*)calloc((strlen(word) + 1), sizeof(char));  //creating of dinamic string for the word
	if (**page == NULL)                //checking that we created the string
		return -1;
	strcpy(**page, word);               //coping the word to the dinamic string
	while (number_of_definition-j){          //number of definitions(>=1) - j
		++j;                     //j+1
		printf("please enter the %d definition (max 200 chars). press Enter to finish\n", j);
		gets(definition);               //get string from the user
		*(*page + j) = (char*)calloc((strlen(definition) + 1), sizeof(char));   //creating of dinamic string for the (j) definition at the j place
		if (*(*page + j) == NULL)                  //checking that we created the stringd
			return -1;
		strcpy(*(*page + j), definition);       //coping the definition to the dinamic string
	}  //end while
	return 0;
}  //end function

//recursive function that gets a char*** pointer to dinamic arrey and send **pointer to caps_word function
//in order to change all the letter exept the first to lower case
void correct_words(char*** dictionary){
	if (!*dictionary)    //if *dictionary == null
		return;        // return
	correct_words(dictionary + 1);  //call for correct_word for the next place in the arrey
	caps_word(**dictionary);        //call for caps_words
	***dictionary -= 'a' - 'A';  //change first letter to upper case
}

//recursive function that gets a char* pointer to dinamic string and change all the letter to lower case
void caps_word(char* word){
	if (!*word)    //if *word == null
		return;     // return
	caps_word(word + 1);    //call for caps_word for the next char in the string
	if ((*word) <= 'Z' && (*word) >= 'A')   // if *word is upper case
		*word += 'a' - 'A';              //chenge it to lower case
}

//recursive function that gets a char*** pointer to dinamic arrey and send **pointer(+1 cuz the first place is for the word) to definitions function
//in order to change all the letter exept the first and the first after a dot to lower case
void correct_definition(char*** dictionary){
	if (!*dictionary)   //if *dictionary==null
		return;   //return
	correct_definition(dictionary + 1);    //call for correct_definition for the next place
	definitions(*dictionary + 1);      //call for definitions function
}

//recursive function that gets a char** pointer to dinamic arrey and send *pointer to caps_definition function to 
//in order to change all the letter exept the first and the first after a dot to lower case
void definitions(char** definition){
	if (!*definition)  //if *definition==null
		return;     //return
	definitions(definition + 1);   //call for defenitions for the next place
	caps_definition(*definition);    //call for caps_definitions function
	**definition -= 'a' - 'A';    //change the first letter to upper case
}

//recursive function that gets a char* pointer to dinamic string and change all the letters exept the first after a dot to lower case
void caps_definition(char* definition){
	if (!*definition)   //if *definition==null
		return;     //return
	caps_definition(definition + 1);  //call for caps_definitions function for the next char
	if (*(definition - 2) == '.') {  //if 2 chars ago there was "."
		if (*definition >= 'a' && *definition <= 'z')   //if *definition is lower case 
			*definition -= 'a' - 'A';          //change to upper case
	}
	else if (*definition >= 'A' && *definition <= 'Z')  //if upper case
		*definition += 'a' - 'A';             //change to lower case
}

//recursive function that gets a char*** pointer to dinamic arrey and sort it by using qsort algoritem
//function uses the swap_p function
void sort_dictionary(char*** dictionary, int left, int right) {
	int i, last, check;       //creating variables
	if (left >= right)  //stop condition where we passed trough the all arrey
		return;         //return
	swap_p(dictionary, left, (left + right) / 2);   //choosing one place at the arrey and making him first, we will sort recording to that value
	check = (left + right) / 2;
	last = left;
	for (i = left + 1; i <= right; i++)  {   //moving all the smaller values
		if (strcmp(*(dictionary[i]) , *(dictionary[left]))<0) {
			swap_p(dictionary, ++last, i);
		}    
		else if (strcmp(*(dictionary[i]), *(dictionary[left])) == 0 && i <= check) {
			swap_p(dictionary, ++last, i);
		}
	}
	swap_p(dictionary, left, last); //moving the value we choosed back to its place
	sort_dictionary(dictionary, left, last - 1);   //continue sorting both sides
	sort_dictionary(dictionary, last + 1, right);
}

//function that gets a char*** pointer to dinamic arrey and to places at that arrey and changed between thos places
void swap_p(char*** dictionary, int first, int second){
	char** temp;    //temp **pointer
	temp = dictionary[first];              
	dictionary[first] = dictionary[second];
	dictionary[second] = temp;
}

//function that gets a char**** pointer to pointer to dinamic arrey and int* pointer to that arrey size and check for similar words
//if there are similar word remove the later and change the arrey size as well
void remove_similar_words(char**** dictionary, int* size){
	int i;    //creating count variable
	for (i = 1; i < *size; i++){                 //cheack for asimilar word in the former place(i-1) because the dictionary is already sorted 
		if (strcmp(**(*dictionary + i), **(*dictionary + i - 1)) == 0){  //if thoe word ar similars
			remove_word(dictionary, i, size);   //call remove_word for the later word and put 
			if (*(*dictionary + i))     //if we are not at the end of the arrey
				i--;                    //i-1
		}   //end if
	}   //end for
}     //end function

//function that gets a char**** pointer to pointer to dinamic arrey, int place and int* pointer to that arrey size 
//and remove the word at the corrent place by freeing all related dinamic arrey and resizing the arrey size to size -1
void remove_word(char**** dictionary, int place, int* size){
	int j = 0;  //creating count variable
	while (*(*(*dictionary + place) + j)){   //while the arrey that contain the word and her define is not at the end
		free(*(*(*dictionary + place) + j));       //free dinamic arrey (char*)
		j++;                 //j+1
	}   //end while
	free(*(*dictionary + place));              //free dinamic arrey  (char**)
	while (*(*dictionary + place + 1)){               //while not null
		*(*dictionary + place) = *(*dictionary + place + 1);   //directing corrent place to the next
		place++;    //place+1
	}   //end while
	char***p = (char***)calloc(*size, sizeof(char**));      //creating new temp arrey whiche is smaller by one from the original
	for (j = 0; j < *size; j++)
		p[j] = *(*dictionary + j);   //copy the old arrey to the new one(which is smaller by 1)
	free(*dictionary);     //free old dinamic arrey
	*dictionary = p;     //directiong pointer of the old arrey to the new arrey
	*(*dictionary + place) = NULL;  //making sure that the arrey end with null
	(*size)--;        //size-1
}  // end function


//function that start the last phase. the search phase. get char*** pointer to dinamic arrey and int size of that arrey
//function will call to the search_word function which will call to print_page function
void search_dictiaonary(char*** dictionary, int size_of_dictionary){
	char exit[] = "exit";  //creating and setting string
	int from = 0;  //creating and setting integer
	char buffer[WORD_MAX_SIZE];   //creating buffer for word (size of the max size of the word)
	printf("\n\n*******************************\n  welcome to the search phase  \n*******************************\n\n");
	printf("Please enter the word (max 80 chars) you want to search.\nwrite exit to end the progrem.\n");
	gets(buffer);    //get word from the user
	while (strcmp(buffer, exit)){  //while the word the user enter is not "exit"
		search_word(dictionary, buffer, from, size_of_dictionary);  //call for function search_word
		printf("\n\nPlease enter the next word (max 80 chars) you want to search.\nwrite exit to end the progrem.\n");
		gets(buffer);    // get the next word from the user
	} 
}

//recursive function that get char*** pointer to dinamic arrey(dictionary) string of word to search and 2 int that indicate from where to where 
//to search. the function will check if the word to search is in the dinamic arrey and print the word and her definitions if it is or else 
//print "unknown word"
void search_word(char*** dictionary, char buffer[], int from, int to){
	if (strcmp(buffer, **(dictionary + (to + from) / 2)) == 0){  //if the middle places word value is similar to the buffer
		print_page(*(dictionary + (to + from) / 2)+1);  //call for print_page function (+1 cuz we dont need to print the word again
		return;    //return
	}  // end if
	if (to - from == 0){   //if to equle to from   (stop condition)
		printf("XXXXXXXXXXXXXXX   Unknown word!    XXXXXXXXXXXXXXX");
		return;   //return
	}   //end if
	if (strcmp(buffer, **(dictionary + (to + from) / 2)) > 0)    //buffer value > midell of the range value
		search_word(dictionary, buffer, (to + from) / 2 + 1, to);   //call for search_word with higher "starting point"
	else 
		search_word(dictionary, buffer, from, (to + from) / 2 - 1);//call for search_word with lower "ending point"
}   //end function

//function that get char** pointer and print that words definitions
void print_page(char** page){
	int i, num_of_def = 0;  //creating variables
	while (page[num_of_def])   //checking how much definition there are
		num_of_def++;
	printf("The word have %d definition/s\n", num_of_def);
	for (i = 0; i < num_of_def; i++){     //print all the definitions
		printf("definition %d: ", i + 1); 
		puts(page[i]);
	}   //end for
}   //end function
