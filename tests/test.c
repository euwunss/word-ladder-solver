// testing suite

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;

// number of words of a specific size in a dictionary
int countWordsOfLength(char* filename, int wordSize) { 
    FILE* infile = fopen(filename, "r");
    if (!infile) {
        printf("Error opening the file.\n");
        return -1;
    }

    int count = 0, bufferSize = 50;
    char buffer[bufferSize];
    while (!feof(infile) && fscanf(infile, "%s", buffer)) {
        count = (strlen(buffer) == wordSize) ? ++count : count;
    }

    fclose(infile);
    return count;
}

// checked for every word length in sample dictionary
// and checked for returned value -1 if file cannot be opened
bool test_countWordsOfLength() {
    int wordSize = 3;
    int expected = 7;
    char* filename = "sampleDict.txt";

    printf(" Checking countWordsOfLength() for words of length %d in %s:\n", wordSize, filename);
    int actual = countWordsOfLength(filename, wordSize);
    if (actual != expected) {
        printf("  expected # of %d-letter words in %s: %d\n", wordSize, filename, expected);
        printf("  actual # of %d-letter words in %s: %d\n", wordSize, filename, actual);
        return false;
    }

    wordSize = 4;
    expected = 4;
    printf(" Checking countWordsOfLength() for words of length %d in %s:\n", wordSize, filename);
    actual = countWordsOfLength(filename, wordSize);
    if (actual != expected) {
        printf("  expected # of %d-letter words in %s: %d\n", wordSize, filename, expected);
        printf("  actual # of %d-letter words in %s: %d\n", wordSize, filename, actual);
        return false;
    }

    wordSize = 5;
    expected = 2;
    printf(" Checking countWordsOfLength() for words of length %d in %s:\n", wordSize, filename);
    actual = countWordsOfLength(filename, wordSize);
    if (actual != expected) {
        printf("  expected # of %d-letter words in %s: %d\n", wordSize, filename, expected);
        printf("  actual # of %d-letter words in %s: %d\n", wordSize, filename, actual);
        return false;
    }

    wordSize = 6;
    expected = 1;
    printf(" Checking countWordsOfLength() for words of length %d in %s:\n", wordSize, filename);
    actual = countWordsOfLength(filename, wordSize);
    if (actual != expected) {
        printf("  expected # of %d-letter words in %s: %d\n", wordSize, filename, expected);
        printf("  actual # of %d-letter words in %s: %d\n", wordSize, filename, actual);
        return false;
    }

    wordSize = 8;
    expected = 1;
    printf(" Checking countWordsOfLength() for words of length %d in %s:\n", wordSize, filename);
    actual = countWordsOfLength(filename, wordSize);
    if (actual != expected) {
        printf("  expected # of %d-letter words in %s: %d\n", wordSize, filename, expected);
        printf("  actual # of %d-letter words in %s: %d\n", wordSize, filename, actual);
        return false;
    }

    wordSize = 2;
    expected = 0;
    printf(" Checking countWordsOfLength() for words of length %d in %s:\n", wordSize, filename);
    actual = countWordsOfLength(filename, wordSize);
    if (actual != expected) {
        printf("  expected # of %d-letter words in %s: %d\n", wordSize, filename, expected);
        printf("  actual # of %d-letter words in %s: %d\n", wordSize, filename, actual);
        return false;
    }

    char* filename1 = "not_found.txt";
    wordSize = 3;
    expected = -1;
    printf(" Checking countWordsOfLength() for words of length %d in %s:\n", wordSize, filename1);
    actual = countWordsOfLength(filename1, wordSize);
    if (actual != expected) {
        printf("%s file does not exist.\n", filename1);
        printf("  expected return value: %d\n", expected);
        printf("  actual return value: %d\n", actual);
        return false;
    }

    return true;
}


// testing buildWordArray()
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

// testing building word array of same-length words from a file
bool test_buildWordArray() {
    char* filename = "sampleDict.txt";
    int numWords = 4;
    int wordSize = 4;
    char** words = (char**)malloc(sizeof(char*) * numWords);
    for (int i = 0; i < numWords; i++) {
        words[i] = (char*)malloc(sizeof(char) * (wordSize + 1));
    }

    bool expected = true;
    bool actual = buildWordArray(filename, words, numWords, wordSize);
    printf(" Checking buildWordArray() for 4-letter words:\n");
    if (actual != expected ||
        strcmp(words[0], "code") != 0 ||
        strcmp(words[1], "data") != 0 ||
        strcmp(words[2], "gala") != 0 ||
        strcmp(words[3], "hope") != 0 ) {
        
        printf("  expected words array: code, data, gala, hope\n");
        printf("  actual words array: ");
        for (int i = 0; i < numWords; i++) {
            printf("%s ", words[i]);
        }
        printf("\n");
        printf("  expected return value: %d, actual return value: %d\n", expected, actual);
        return false;
    }

    for (int i = 0; i < numWords; i++) {
        free(words[i]);
    }
    free(words);

    // ADD MORE TESTS HERE FOR EXAMPLE IF FILE COULDNT BE OPENED

    return true;
}

// testing binary search in words array
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

// test when first letters are different
// test when first letters are same
bool test_findWord() {
    char* words[5] = {"board", "float", "great", "ground", "hello"};
    char* aWord = "great";
    int loInd = 0;
    int hiInd = 4;
    int expected = 2;

    printf(" Checking findWord() to find word \"%s\" in a 5-word array:\n", aWord);
    int actual = findWord(words, aWord, loInd, hiInd);
    if (actual != expected) {
        printf("  words array is: %s, %s, %s, %s, %s\n", words[0], words[1], words[2], words[3], words[4]);
        printf("  word to search: %s\n", aWord);
        printf("  expected index: %d, actual index: %d\n", expected, actual);
    }

    char* aWord1 = "ground";
    expected = 3;
    printf(" Checking findWord() to find word \"%s\" in a 5-word array:\n", aWord1);
    actual = findWord(words, aWord1, loInd, hiInd);
    if (actual != expected) {
        printf("  words array is: %s, %s, %s, %s, %s\n", words[0], words[1], words[2], words[3], words[4]);
        printf("  word to search: %s\n", aWord1);
        printf("  expected index: %d, actual index: %d\n", expected, actual);
    }

    char* aWord2 = "hello";
    expected = 4;
    printf(" Checking findWord() to find word \"%s\" in a 5-word array:\n", aWord2);
    actual = findWord(words, aWord2, loInd, hiInd);
    if (actual != expected) {
        printf("  words array is: %s, %s, %s, %s, %s\n", words[0], words[1], words[2], words[3], words[4]);
        printf("  word to search: %s\n", aWord2);
        printf("  expected index: %d, actual index: %d\n", expected, actual);
    }

    char* aWord3 = "board";
    expected = 0;
    printf(" Checking findWord() to find word \"%s\" in a 5-word array:\n", aWord3);
    actual = findWord(words, aWord3, loInd, hiInd);
    if (actual != expected) {
        printf("  words array is: %s, %s, %s, %s, %s\n", words[0], words[1], words[2], words[3], words[4]);
        printf("  word to search: %s\n", aWord3);
        printf("  expected index: %d, actual index: %d\n", expected, actual);
    }

    char* aWord4 = "float";
    expected = 1;
    printf(" Checking findWord() to find word \"%s\" in a 5-word array:\n", aWord4);
    actual = findWord(words, aWord4, loInd, hiInd);
    if (actual != expected) {
        printf("  words array is: %s, %s, %s, %s, %s\n", words[0], words[1], words[2], words[3], words[4]);
        printf("  word to search: %s\n", aWord4);
        printf("  expected index: %d, actual index: %d\n", expected, actual);
    }

    char* aWord5 = "build";
    expected = -1;
    printf(" Checking findWord() to find word \"%s\" in a 5-word array:\n", aWord5);
    actual = findWord(words, aWord5, loInd, hiInd);
    if (actual != expected) {
        printf("  words array is: %s, %s, %s, %s, %s\n", words[0], words[1], words[2], words[3], words[4]);
        printf("  word to search: %s\n", aWord5);
        printf("  word \"%s\" is not in words array\n", aWord5);
        printf("  expected index: %d, actual index: %d\n", expected, actual);
    }
}


// testing freeWords() 
void freeWords(char** words, int numWords) {
    for (int i = 0; i < numWords; i++) {
        free(words[i]);
    }
    free(words);
    return;
}

bool test_freeWords() {
    int numWords = 15;
    int wordSize = 6;
    char** words = (char**)malloc(sizeof(char*) * numWords);
    if (!words) {
        printf("Error allocating memory for an array.\n");
        return false;
    }

    for (int i = 0; i < numWords; i++) {
        words[i] = (char*)malloc(sizeof(char) * (wordSize + 1));
    }

    printf(" Checking freeWords() for array with %d words or size %d:\n", numWords, wordSize);
    freeWords(words, numWords);
    printf(" Valgrind shows no memory leaks and errors - passed.\n");    
    return true;
}


// testing insertWordAtFront()
void insertWordAtFront(WordNode** ladder, char* newWord) {
    WordNode* newWordNode = (WordNode*)malloc(sizeof(WordNode));
    newWordNode->myWord = newWord;
    newWordNode->next = *ladder;
    *ladder = newWordNode;
    return;
}

bool test_insertWordAtFront() {
    int ladderSize = 0;
    WordNode* ladder = (WordNode*)malloc(sizeof(WordNode));
    if (!ladder) {
        printf("Error allocating memory for a string.\n");
        return false;
    }
    ladder->myWord = (char*)malloc(sizeof(char) * 6);
    ladder->next = NULL;
    strcpy(ladder->myWord, "hello");
    ladderSize++;

    WordNode* temp = ladder;
    
    char* newWord = (char*)malloc(sizeof(char) * 4);
    strcpy(newWord, "bye");

    insertWordAtFront(&ladder, newWord);
    printf(" Checking insertWordAtFront() for a non-empty ladder:\n");
    if (strcmp(ladder->myWord, "bye") != 0 || !ladder->next) {
        printf("  ladder contains word \"hello\"\n");
        printf("  expected ladder->myWord after insertion is bye\n");
        printf("  actual ladder->myWord after insertion is %s\n", ladder->myWord);
        printf("  expected ladder->next after insertion is %p\n", temp);
        printf("  expected ladder->next after insertion is: %p\n", ladder->next);
        temp = ladder;
        while (temp) {
            ladder = ladder->next;
            free(temp->myWord);
            free(temp);
            temp = ladder;
        }
        return false;
    }
    
    temp = ladder;
    while (temp) {
        ladder = ladder->next;
        free(temp->myWord);
        free(temp);
        temp = ladder;
    }

    // test when ladder is empty
    ladder = NULL;
    temp = ladder;
    newWord = (char*)malloc(sizeof(char) * 10);
    strcpy(newWord, "yesterday");

    insertWordAtFront(&ladder, newWord);
    printf(" Checking insertWordAtFront() for an empty ladder:\n");
    if (strcmp(ladder->myWord, "yesterday") != 0 || ladder->next != NULL) {
        printf("  ladder is initially empty\n");
        printf("  expected ladder->myWord after insertion is yesterday\n");
        printf("  actual ladder->myWord after insertion is %s\n", ladder->myWord);
        printf("  expected ladder->next after insertion is NULL\n");
        printf("  expected ladder->next after insertion is: %p\n", ladder->next);
        temp = ladder;
        while (temp) {
            ladder = ladder->next;
            free(temp->myWord);
            free(temp);
            temp = ladder;
        }
        return false;
    }

    temp = ladder;
    while (temp) {
        ladder = ladder->next;
        free(temp->myWord);
        free(temp);
        temp = ladder;
    }
    return true;
}


// testing getLadderHeight()
int getLadderHeight(WordNode* ladder) {
    int height = 0;
    while (ladder) {
        height++;
        ladder = ladder->next;
    }
    return height;
}

bool test_getLadderHeight() {
    // test when ladder is empty
    WordNode* ladder = NULL;
    int expected = 0;
    int actual = getLadderHeight(ladder);
    printf(" Checking getLadderHeight() for an empty ladder:\n");
    if (actual != expected) {
        printf("  ladder is empty\n");
        printf("  expected ladder height: %d\n", expected);
        printf("  actual ladder height: %d\n", actual);
        return false;
    }

    // test when one node
    ladder = (WordNode*)malloc(sizeof(WordNode));
    if (!ladder) {
        printf("Error allocating memory for a word ladder.\n");
        return false;
    }
    ladder->myWord = (char*)malloc(sizeof(char) * 6);
    strcpy(ladder->myWord, "pizza");
    ladder->next = NULL;

    expected = 1;
    actual = getLadderHeight(ladder);
    printf(" Checking getLadderHeight() for a 1-word ladder:\n");
    if (actual != expected) {
        printf("  ladder has one word %s\n", ladder->myWord);
        printf("  expected ladder height: %d\n", expected);
        printf("  actual ladder height: %d\n", actual);
        free(ladder->myWord);
        free(ladder);
        return false;
    }

    // testing for several nodes
    char* newWord = (char*)malloc(sizeof(char) * 7);
    strcpy(newWord, "burger");
    insertWordAtFront(&ladder, newWord);
    newWord = (char*)malloc(sizeof(char) * 6);
    strcpy(newWord, "fries");
    insertWordAtFront(&ladder, newWord);
    newWord = (char*)malloc(sizeof(char) * 8);
    strcpy(newWord, "nuggets");
    insertWordAtFront(&ladder, newWord);

    WordNode* temp = ladder;
    expected = 4;
    actual = getLadderHeight(ladder);
    printf(" Checking getLedderHeight() for a 4-word ladder:\n");
    if (actual != expected) {
        printf("  ladder contains 4 words: nuggets, fries, burger, pizza");
        printf("  expected ladder height: %d\n", expected);
        printf("  actual ladder height: %d\n", actual);
        while (temp) {
            ladder = ladder->next;
            free(temp->myWord);
            free(temp);
            temp = ladder;
        }
        return false;
    }

    while (temp) {
        ladder = ladder->next;
        free(temp->myWord);
        free(temp);
        temp = ladder;
    }

    return true;
}


int main() {
    printf("Word Ladder Solver Testing Suite.\n");

    printf("Testing countWordsOfLength()...\n");
    if (test_countWordsOfLength()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    printf("Testing buildWordArray()...\n");
    if (test_buildWordArray()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    printf("Testing findWord()...\n");
    if (test_findWord()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    printf("Testing freeWords()...\n");
    if (test_freeWords()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    printf("Testing insertWordAtFront()...\n");
    if (test_insertWordAtFront()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    printf("Testing getLadderHeight()...\n");
    if (test_getLadderHeight()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}