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
    char* filename = "../sampleDict.txt";

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


int main() {
    printf("Word Ladder Solver Testing Suite.\n");

    printf("Testing countWordsOfLength()...\n");
    if (test_countWordsOfLength()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}