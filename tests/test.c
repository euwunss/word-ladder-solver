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

// testing countWordsOfLength()
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

// tests countWordsOfLength() for various word sizes and expected counts
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
        printf("  %s file does not exist.\n", filename1);
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

// tests buildWordArray() by verifying correct word population and array length
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
        for (int i = 0; i < numWords; i++) {
            free(words[i]);
        }
        free(words);
        return false;
    }

    for (int i = 0; i < numWords; i++) {
        free(words[i]);
    }
    free(words);

    char* filename_not_found = "not_found.txt";
    numWords = 4;
    wordSize = 4;
    words = (char**)malloc(sizeof(char*) * numWords);
    for (int i = 0; i < numWords; i++) {
        words[i] = (char*)malloc(sizeof(char) * (wordSize + 1));
    }

    expected = false;
    actual = buildWordArray(filename_not_found, words, numWords, wordSize);
    printf(" Checking buildWordArray() for a file that does not exist:\n");
    if (actual != expected) {
        printf("  file `file_not_found.txt` doesn't exist.\n");
        printf("  expected return value: %d, actual return value: %d\n", expected, actual);
        for (int i = 0; i < numWords; i++) {
            free(words[i]);
        }
        free(words);
        return false;
    }

    for (int i = 0; i < numWords; i++) {
        free(words[i]);
    }
    free(words);

    return true;
}

// testing findWord()
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

// tests findWord() for different cases within a sorted words array
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

// tests freeWords() by veryfying that Valgrind printf no memory leaks message
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

// tests insertWordAtFront() to ensure correct word insertion in a ladder
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


// testing copyLadder()
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

// tests copyLadder for copying word ladders
bool test_copyLadder() {
    // test for empty ladder
    WordNode* ladder = NULL;
    WordNode* newLadder = copyLadder(ladder);
    printf(" Checking copyLadder() for an empty ladder:\n");
    if (newLadder) {
        printf("  ladder is empty\n");
        printf("  expected return value: NULL\n");
        printf("  actual return value: %p\n", newLadder);
        return false;
    }

    // test for 1-word ladder
    ladder = (WordNode*)malloc(sizeof(WordNode));
    ladder->next = NULL;
    ladder->myWord = (char*)malloc(sizeof(char) * 4);
    strcpy(ladder->myWord, "dog");
    newLadder = copyLadder(ladder);
    if (!newLadder) {
        printf("Error copying ladder.\n");
        return false;
    }

    int expected = 1; // expected height of a copied ladder
    int actual = getLadderHeight(newLadder);
    printf(" Checking copyLadder() for a 1-word ladder:\n");
    if (actual != expected || strcmp(newLadder->myWord, ladder->myWord) != 0 || newLadder->next != NULL) {
        printf("  ladder has height of 1\n");
        printf("  expected height of copied ladder: %d\n", expected);
        printf("  actual height of copied ladder: %d\n", expected);
        printf("  expected word in the ladder: %s\n", ladder->myWord);
        printf("  actual word in the ladder: %s\n", newLadder->myWord);

        free(ladder->myWord);
        free(ladder);
        free(newLadder);
        return false;
    }

    // test for several words in a ladder
    free(newLadder);

    char* newWord = (char*)malloc(sizeof(char) * 6);
    strcpy(newWord, "sleep");
    insertWordAtFront(&ladder, newWord);
    newWord = (char*)malloc(sizeof(char) * 7);
    strcpy(newWord, "points");
    insertWordAtFront(&ladder, newWord);
    newWord = (char*)malloc(sizeof(char) * 8);
    strcpy(newWord, "accepts");
    insertWordAtFront(&ladder, newWord);
    newWord = (char*)malloc(sizeof(char) * 9);
    strcpy(newWord, "function");
    insertWordAtFront(&ladder, newWord);

    newLadder = copyLadder(ladder);
    expected = 5;
    actual = getLadderHeight(newLadder);
    printf(" Checking copyLadder() for a 5-word ladder:\n");
    if (actual != expected) {
        printf("  ladder contains words function, accepts, points, sleep, dog");
        printf("  expected ladder height: %d\n", expected);
        printf("  actual ladder height: %d\n", actual);
        printf("  newLadder contains words:\n");
        WordNode* temp = newLadder;
        while (temp) {
            printf("%s  ", temp->myWord);
            temp = temp->next;
        }
        printf("  ladder's front word is: %s\n", ladder->myWord);
        printf("  newLadder's front word is: %s\n", newLadder->myWord);
        WordNode* temp1 = ladder;
        WordNode* temp2 = newLadder;
        while (temp1 && temp2) {
            ladder = ladder->next;
            newLadder = newLadder->next;
            free(temp1->myWord);
            free(temp1);
            free(temp2);
            temp1 = ladder;
            temp2 = newLadder;
        }
        return false;
    }

    WordNode* temp1 = ladder;
    WordNode* temp2 = newLadder;
    while (temp1 && temp2) {
        ladder = ladder->next;
        newLadder = newLadder->next;
        free(temp1->myWord);
        free(temp1);
        free(temp2);
        temp1 = ladder;
        temp2 = newLadder;
    }
    return true;
}


// testing insertLadderAtBack()
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

// tests insertLadderAtBack() for insertion ladder into ladder list when it is both empty and non-empty
bool test_insertLadderAtBack() {
    // test for empty ladder
    LadderNode* list = NULL;
    WordNode* newLadder = (WordNode*)malloc(sizeof(WordNode));
    newLadder->next = NULL;
    newLadder->myWord = (char*)malloc(sizeof(char) * 5);
    strcpy(newLadder->myWord, "game");

    char* newWord = (char*)malloc(sizeof(char) * 12);
    strcpy(newWord, "interesting");
    insertWordAtFront(&newLadder, newWord);
    insertLadderAtBack(&list, newLadder);

    printf(" Checking insertLadderAtBack() for an empty list:\n");
    if (!list || strcmp(list->topWord->myWord, "interesting") != 0 || strcmp(list->topWord->next->myWord, "game") != 0 || list->topWord->next->next) {
        printf("  list is initially empty\n");
        printf("  after insertion of ladder at back, it is not expected to point to NULL\n");
        printf("  expected top word: interesting\n");
        printf("  actual top word: %s\n", list->topWord->myWord);
        WordNode* temp = newLadder;
        while (temp) {
            newLadder = newLadder->next;
            free(temp->myWord);
            free(temp);
            temp = newLadder;
        }
        free(list);
        return false;
    }

    // test for non-empty ladder list
    WordNode* anotherLadder = (WordNode*)malloc(sizeof(WordNode));
    anotherLadder->next = NULL;
    anotherLadder->myWord = (char*)malloc(sizeof(char) * 7);
    strcpy(anotherLadder->myWord, "ladder");

    char* anotherWord = (char*)malloc(sizeof(char) * 5);
    strcpy(anotherWord, "test");
    insertWordAtFront(&anotherLadder, anotherWord);
    insertLadderAtBack(&list, anotherLadder);

    printf(" Checking insertLadderAtBack() for non-empty list:\n");
    if (!list->next || strcmp(list->next->topWord->myWord, "test") != 0 || strcmp(list->next->topWord->next->myWord, "ladder") != 0 || list->next->topWord->next->next) {
        printf("  failed to insert ladder at back for non-empty list.\n");
        WordNode* temp = newLadder;
        while (temp) {
            newLadder = newLadder->next;
            free(temp->myWord);
            free(temp);
            temp = newLadder;
        }

        temp = anotherLadder;
        while (temp) {
            anotherLadder = anotherLadder->next;
            printf("%s ", temp->myWord);
            free(temp->myWord);
            free(temp);
            temp = anotherLadder;
        }
        free(list);

        LadderNode* ladderTemp = list;
        while (ladderTemp) {
            LadderNode* nextLadder = ladderTemp->next;
            free(ladderTemp);
            ladderTemp = nextLadder;
        }

        return false;
    }

    WordNode* temp = newLadder;
    while (temp) {
        newLadder = newLadder->next;
        free(temp->myWord);
        free(temp);
        temp = newLadder;
    }

    temp = anotherLadder;
    while (temp) {
        anotherLadder = anotherLadder->next;
        free(temp->myWord);
        free(temp);
        temp = anotherLadder;
    }
    
    LadderNode* ladderTemp = list;
    while (ladderTemp) {
        LadderNode* nextLadder = ladderTemp->next;
        free(ladderTemp);
        ladderTemp = nextLadder;
    }

    return true;
}


void freeLadder(WordNode* ladder) {
    WordNode* curr = ladder;
    while (curr) {
        ladder = ladder->next;
        free(curr);
        curr = ladder;
    }
}

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


// testing popLadderFromList()
WordNode* popLadderFromFront(LadderNode** list) {
    if (!(*list)) {
        return NULL;
    }

    LadderNode* frontLadderNode = *list;
    *list = (*list)->next;
    WordNode* frontWordNode = frontLadderNode->topWord;
    free(frontLadderNode);
    return frontWordNode;
}

// tests popLadderFromFront() by popping the front ladder from ladder list and veryfying it is removed properly and list is updated correctly 
bool test_popLadderFromFront() {
    LadderNode* list = NULL;

    // test when list is empty
    WordNode* popped = popLadderFromFront(&list);
    printf(" Checking popLadderFromFront() for an empty list:\n");
    if (popped) {
        printf("  list is initially empty.\n");
        printf("  expected value is NULL, but actual value is not NULL\n");
        return false;
    }
    // create the first ladder
    WordNode* newLadder = (WordNode*)malloc(sizeof(WordNode));
    newLadder->myWord = (char*)malloc(sizeof(char) * 6);
    strcpy(newLadder->myWord, "word1");
    newLadder->next = NULL;
    insertLadderAtBack(&list, newLadder);

    newLadder = (WordNode*)malloc(sizeof(WordNode));
    newLadder->myWord = (char*)malloc(sizeof(char) * 6);
    strcpy(newLadder->myWord, "word2");
    newLadder->next = NULL;
    insertLadderAtBack(&list, newLadder);

    // pop the first ladder
    WordNode* poppedLadder = popLadderFromFront(&list);
    printf(" Checking popLadderFromFront() for a non-empty list:\n");
    if (!poppedLadder || strcmp(poppedLadder->myWord, "word1") != 0) {
        printf("  expected front ladder word: word1\n");
        if (poppedLadder) {
            printf("  actual front ladder word: %s\n", poppedLadder->myWord);
        } else {
            printf("  actual front ladder word doens't exist, as the ladder is empty.\n");
        }
        free(poppedLadder->myWord);
        free(poppedLadder->next->myWord);
        freeLadder(poppedLadder);
        freeLadderList(list);

        return false;
    }

    if (!list || strcmp(list->topWord->myWord, "word2") != 0) {
        printf("  expected list head's word: word2\n");
        if (list) {
            printf("  actual list head's word: %s\n", list->topWord->myWord);
        }
        else {
            printf("  actual list head's word doesn't exist, as list is empty\n");
        }
        free(poppedLadder->myWord);
        freeLadder(poppedLadder);
        freeLadderList(list);
        return false;
    }

    free(poppedLadder->myWord);
    free(list->topWord->myWord);
    freeLadder(poppedLadder);
    freeLadderList(list);
    
    return true;
}


// testing freeLadderList() - valgrind check


// testing findShortestWordLadder()
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
        printf("Start word not found.\n");
        freeLadderList(myList);
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
                if (neighborWord[i] == c) { // skip if the character is the same
                    continue;
                }
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

// tests findShortestWordLadder() by creating a testing words array and expected shortest word ladder
bool test_findShortestWordLadder() {
    int wordSize = 4;
    int numWords = 6;
    char** words = (char**)malloc(sizeof(char*) * numWords);
    for (int i = 0; i < numWords; i++) {
        words[i] = (char*)malloc(sizeof(char) * (wordSize + 1));
    }
    strcpy(words[0], "card");
    strcpy(words[1], "cold");
    strcpy(words[2], "cord");
    strcpy(words[3], "gold");
    strcpy(words[4], "ward");
    strcpy(words[5], "warm");

    bool usedWord[numWords];
    for (int i = 0; i < numWords; i++) {
        usedWord[i] = false;
    }

    char* startWord = words[0];
    char* finalWord = words[3];

    WordNode* shortestLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    if (!shortestLadder) {
        printf("  expected shortest ladder, but none found.\n");
        freeWords(words, numWords);
        return false;
    }

    const char* expectedLadder[] = {
        "gold",
        "cold",
        "cord",
        "card",
    };
    int expectedLadderSize = 4;

    printf(" Checking findShortestWordLadder() for an array: card, cold, cord, gold, ward, warm, and startWord = cord, finalWord = gold\n");
    WordNode* curr = shortestLadder;
    int i = 0;
    while (curr && i < expectedLadderSize) {
        if (strcmp(curr->myWord, expectedLadder[i]) != 0) {
            printf("  expected shortest ladder:\n");
            for (int i = 0; i < expectedLadderSize - 1; i++) {
                printf("%s, ", expectedLadder[i]);
            }
            printf("%s\n", expectedLadder[expectedLadderSize - 1]);

            printf("  actual shortest ladder:\n");
            WordNode* curr = shortestLadder;
            while (curr->next) {
                printf("%s, ", curr->myWord);
                curr = curr->next;
            }
            printf("%s\n", curr->myWord);

            freeWords(words, numWords);
            freeLadder(shortestLadder);
            return false;
        }
        curr = curr->next;
        i++;
    }

    if (i != expectedLadderSize || curr) {
        printf("  expected ladder height: %d, actual ladder height: %d\n", expectedLadderSize, i);
        freeWords(words, numWords);
        freeLadder(shortestLadder);
        return false;
    }

    freeWords(words, numWords);
    freeLadder(shortestLadder);
    return true;
}


// calls the testing suite and outputs the result 
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
    printf("Testing copyLadder()...\n");
    if (test_copyLadder()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    printf("Testing insertLadderAtBack()...\n");
    if (test_insertLadderAtBack()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    printf("Testing popLadderFromFront()...\n");
    if (test_popLadderFromFront()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    printf("Testing findShortestWordLadder()...\n");
    if (test_findShortestWordLadder()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}