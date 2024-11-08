// Word Ladder Solver

//----------------------------------------------------
// This program generates the shortest "word ladder" between two user-specified words of the same length.
// A word ladder is a sequence of words where each consecutive word differs by only one letter,
// Progressing step-by-step from the start word to the final word.
// The program reads a dictionary file, extracts words of the specified length,
// And applies a breadth-first search (BFS) to find the shortest transformation sequence.
// If a ladder is found, it displays the ladder and its height;
// If not, it indicates that no such word ladder exists.

// Course: CS 211, Fall 2024, UIC
// Author: Olha Lashchukevych
//----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// structure representing a word in the word ladder
typedef struct WordNode_struct {
    char* myWord;                       // pointer to a word string
    struct WordNode_struct* next;       // pointer to the next word node
} WordNode;

// structure representing a ladder in the ladder list
typedef struct LadderNode_struct {
    WordNode* topWord;                  // pointer to the top word in the ladder
    struct LadderNode_struct* next;     // pointer to the next ladder node
} LadderNode;

// counts words in a file with a specific length
// input: filename - file to read, wordSize - target word length
// returns count of words with the given length; -1 if file couldn't be opened 
int countWordsOfLength(char* filename, int wordSize) { 
    FILE* infile = fopen(filename, "r");
    if (!infile) {
        printf("Error opening the file.\n");
        return -1;
    }

    int count = 0;
    char buffer[50];
    while (fscanf(infile, "%s", buffer) == 1) {
        count = (strlen(buffer) == wordSize) ? ++count : count;
    }

    fclose(infile);
    return count;
}

// builds an array of words from a file that match a given length
// input: filename - file to read, words - pre-allocated array of word C-strings,
//      numWords - expected number of words, wordSize - target word length
// returns true if array is build successfully, false otherwise
bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 
    FILE* infile = fopen(filename, "r");
    if (!infile) {
        printf("Error opening the file.\n");
        return false;
    }

    int ind = 0;
    int wordCount = 0;
    char buffer[50];
    while (fscanf(infile, "%s", buffer) == 1) {
        if (strlen(buffer) == wordSize) {
            strcpy(words[ind++], buffer);
            wordCount++;
        }
    }

    fclose(infile);
    if (wordCount != numWords) {
        printf("Error storing all words in an array.\n");
        return false;
    }

    return true;
}

// finds a word in a sorted array using binary search
// input: words - array of word C-strings, aWord - word to search for,
//      loInd - lower index, hiInd - higher index
// returns index of aWord if found, -1 otherwise
int findWord(char** words, char* aWord, int loInd, int hiInd) { 
    int mid = (loInd + hiInd) / 2;
    while (loInd <= hiInd) {
        int cmpResult = strcmp(aWord, words[mid]);
        if (cmpResult == 0) {
            return mid;
        }
        else if (cmpResult < 0) {
            hiInd = mid - 1;
        }
        else {
            loInd = mid + 1;
        }

        mid = (loInd + hiInd) / 2;
    }

    return -1;
}

// frees all memory for an array of words
// input: words - array of word strings, numWords - number of words
void freeWords(char** words, int numWords) {
    for (int i = 0; i < numWords; i++) {
        free(words[i]);
    }
    free(words);
    return;
}

// inserts a word at the front of a word ladder
// input: ladder - pointer passed by pointer to the ladder's head node, newNord - word to insert
void insertWordAtFront(WordNode** ladder, char* newWord) {
    WordNode* newWordNode = (WordNode*)malloc(sizeof(WordNode));
    newWordNode->myWord = newWord;
    newWordNode->next = *ladder;
    *ladder = newWordNode;
    return;
}

// gets the height of a word ladder (number of words in the ladder)
// input: ladder - pointer to the ladder's head node
// returns height (number of nodes in ladder)
int getLadderHeight(WordNode* ladder) {
    int height = 0;
    while (ladder) {
        height++;
        ladder = ladder->next;
    }
    return height;
}

// makes a copy of a word ladder
// reuses the pointers to C-string words without copying them
// input: ladder - pointer to ladder to copy
// returns pointer to the copied ladder
WordNode* copyLadder(WordNode* ladder) {
    if (!ladder) return NULL;

    WordNode* newLadder = (WordNode*)malloc(sizeof(WordNode));
    WordNode* curr = newLadder;
    newLadder->next = NULL;
    newLadder->myWord = ladder->myWord;
    ladder = ladder->next;

    while (ladder) {
        curr->next = (WordNode*)malloc(sizeof(WordNode));
        curr->next->myWord = ladder->myWord;
        curr = curr->next;
        ladder = ladder->next;
    } 
    curr->next = NULL;
    return newLadder;
}

// frees all nodes in a word array
// input: ladder - pointer to ladder's head node
void freeLadder(WordNode* ladder) {
    WordNode* curr = ladder;
    while (curr) {
        ladder = ladder->next;
        free(curr);
        curr = ladder;
    }
}

// inserts a word ladder at the back of a list of ladders
// input: list - pointer passed by pointer to list head, newLadder - ladder to insert
void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
    LadderNode* newLadderNode = (LadderNode*)malloc(sizeof(LadderNode));
    newLadderNode->topWord = newLadder;
    newLadderNode->next = NULL;

    if (!(*list)) {
        *list = newLadderNode;
        return;
    }

    LadderNode* curr = *list;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = newLadderNode;
    return;
}

// pops the first ladder from a list of ladders
// input: list - pointer passed by pointer to the list head
// returns pointer to the head of the popped ladder
WordNode* popLadderFromFront(LadderNode** list) {
    if (!(*list)) return NULL;

    LadderNode* frontLadderNode = *list;
    *list = (*list)->next;
    WordNode* frontWordNode = frontLadderNode->topWord;
    free(frontLadderNode);
    return frontWordNode;

}

// frees all ladders in a ladder list
// input: myList - pointer to ladder list
void freeLadderList(LadderNode* myList) {
    LadderNode* curr = myList;
    while (curr) {
        myList = myList->next;
        freeLadder(curr->topWord);
        free(curr);
        curr = myList;
    }
    return;
}

// finds the shortest ladder from startWord to finalWord
// input: words - array of words, usedWord - boolean array that indicates which words were previously used,
//      wordSize - size of each word, startWord - start of ladder, finalWord - end of ladder
// returns pointer to the shortest word ladder found, or NULL if none found
WordNode* findShortestWordLadder(   char** words, 
                                    bool* usedWord, 
                                    int numWords, 
                                    int wordSize, 
                                    char* startWord, 
                                    char* finalWord ) {
    // initialize empty list of ladders and the first ladder with the starting word
    LadderNode* myList = NULL;
    WordNode* myLadder = NULL;
    insertWordAtFront(&myLadder, startWord);
    insertLadderAtBack(&myList, myLadder);

    // find index of the startWord in the words array
    int startWordInd = findWord(words, startWord, 0, numWords - 1);
    if (startWordInd == -1) {
        freeLadderList(myList);
        printf("Start word not found.\n");
        return NULL;
    }
    usedWord[startWordInd] = true;

    // process each ladder in the list
    while (myList) {
        // pop the first ladder from myList for exploration
        myLadder = popLadderFromFront(&myList);

        // allocate memory for a copy of the current word at the top of myLadder
        char* neighborWord = (char*)malloc(sizeof(char) * (wordSize + 1));
        if (!neighborWord) {
            printf("Error allocating memory for a neighbor word.\n");
            return NULL;
        }
        strcpy(neighborWord, myLadder->myWord);
        
        // change each character in to form new words
        for (int i = 0; i < wordSize; i++) {
            char charBefore = neighborWord[i];

            // replace with each letter from 'a' to 'z'
            for (char c = 'a'; c <= 'z'; c++) {
                // skip if the character is the same 
                if (neighborWord[i] == c) continue;
                
                neighborWord[i] = c;

                // check if the modified word exists in the dictionary and is unused
                int neighborInd = findWord(words, neighborWord, 0, numWords - 1);
                if (neighborInd != -1 && !usedWord[neighborInd]) {
                    
                    // check if the modified word matches the final word
                    if (strcmp(words[neighborInd], finalWord) == 0) {
                        insertWordAtFront(&myLadder, words[neighborInd]); // add finalWord to the ladder
                        free(neighborWord);
                        freeLadderList(myList);
                        return myLadder; // return the found ladder
                    }
                    else {
                        // create a copy of the current ladder and add the modified word
                        WordNode* anotherLadder = copyLadder(myLadder);
                        insertWordAtFront(&anotherLadder, words[neighborInd]);
                        insertLadderAtBack(&myList, anotherLadder); // add the new ladder to the back of the list
                        usedWord[neighborInd] = true; // mark word as used
                    }
                }
                neighborWord[i] = charBefore;
            }
        }
        free(neighborWord);
        freeLadder(myLadder);
    }

    // if no ladder found, free all remaining ladders in myList and return NULL
    freeLadderList(myList);
    return NULL;
}

// interactive user-input to set a word; 
//  ensures sure the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize); 
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}


int main() {
    srand((int)time(0));
    
    printf("\nWelcome to the CS 211 Word Ladder Generator!\n\n");

    // set word length using interactive user-input
    int wordSize;
    printf("Enter the word size for the ladder: ");
    scanf("%d",&wordSize);
    printf("\n");

    printf("This program will make the shortest possible\n"); 
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize]
    char dict[100];
    printf("Enter filename for dictionary: ");
    scanf("%s", dict);
    printf("\n");
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        printf("  Dictionary %s not found...\n",dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever 
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i] 
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize); 
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n"); 

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array, 
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    char startWord[30];
    char finalWord[30];
    printf("Setting the start %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, startWord);
    printf("\n");
    printf("Setting the final %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, finalWord);
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");

    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);    
    } else {
        printf("Shortest Word Ladder found!\n");
        printLadder(myLadder);
    }
    printf("Word Ladder height = %d\n",getLadderHeight(myLadder));
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    return 0;
}
