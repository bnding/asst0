#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//replaces anything that isn't in alphabet to space
char* toSpace(char* sentence){
	int i;
	for(i = 0; i < strlen(sentence); i++){
		if(!isalpha(sentence[i]) && sentence[i] != ' '){
			sentence[i] = ' ';
		}
	}
	return sentence;
}

//counts number of words in sentence
int wordCount(char* sentence){
	int count = 0;
	int flag = 0;
	int i;
	for(i = 0; i < strlen(sentence); i++){
		if(flag == 0 && !isspace(sentence[i])){
			count++;
			flag = 1;
		} else if (isspace(sentence[i])){
			flag = 0;
		}
	}
	return count;
}

//parses sentence into array
char** makeArr(char* sentence, int numWords){
	char** arr2 = (char**) malloc(numWords * sizeof(char*));
	char* word = strtok(sentence, " ");
	int count = 0;

	while(word != NULL){
		arr2[count] = word;
		word = strtok(NULL, " ");
		count++;
	}
	return arr2;
}

//traverse through array of words
void traverse(char** arr, int numWords){
	int i;
	for(i = 0; i < numWords; i++){
		printf("%s\n", arr[i]);
	}
}

//swaps values between two indexes
char** swap(char** words, int index1, int index2){
	char* temp = words[index1];
	words[index1] = words[index2];
	words[index2] = temp;
	return words;
}

//sorts character by character. swaps when finds greater character
char** sort(char** words, int numWords){
	int i;
	int j;
	int k;
	int l;

	for(i = 0; i < numWords; i++){
		for(j = i+1; j < numWords; j++){
			int flag = 0;
			for(k = 0, l = 0; k < strlen(words[i]) && l < strlen(words[j]); k++, l++){
				if(words[i][k] >= 97 && words[j][l] <= 90){
					words = swap(words, i, j);
					break;
				}  else if ((words[i][k] <= 90 && words[j][l] <= 90) || (words[i][k] >= 97 && words[j][l] >= 97)){
					if(words[i][k] < words[j][l]){
						words = swap(words, i, j);
						break;
					} else if (words[i][k] > words[j][l]){
						break;
					} else if ((k == strlen(words[i])-1 && l != strlen(words[j])-1) ){
						words = swap(words, i, j);
						break;
					}
				} else if ((words[i][k] <= 90 && words[j][l] >= 97)){
					break;
				}

			}
		}
	}
	return words;
}

int main(int argc, char** argv){
	//seems to work. test it!!!!
	if(argc != 2){
		fprintf(stderr, "Fatal Error: Found %d arguments, was expecting 1\nUsage: ./pointersorter inputstring\n\n", argc-1, 96); 
		return 0;
	} 

	//testing with fprintf(stderr...) uncomment this if it doesn't work 
	
	//if(argc != 2){
	//	printf("Fatal Error: Found %d arguments, was expecting 1\nUsage: ./pointersorter \"inputstring\"\n\n", argc-1);
	//	return 0;
	//}
	int charSize = strlen(argv[1]);
	char* sentence = (char*) malloc(argc * charSize* sizeof(char));
	strcat(sentence, argv[1]);
	strcat(sentence, " ");
	sentence = toSpace(sentence);


	int numWords = wordCount(sentence);
	if(numWords == 0){
		fprintf(stderr, "Warning: No tokens found in input.\n\n", 42);
		return 0;
	}
	char** arr = makeArr(sentence, numWords);

	


	arr = sort(arr, numWords);

	traverse(arr, numWords);

	//we only allocated memory to one variable throughout this assignment
	free(arr);

	return 0;
}
