
#include <stdio.h>
#include <string.h>

void checks(char *word, char dict[10000][25], FILE *outp1) {
    fprintf(outp1, "Suggestions for '%s':\n", word);

    // Check for the valid words that has one different letter from the input word
    for (int index = 0; index < (int)strlen(word); index++) {
        //chang every letter of the word with a-z
        for (char ch = 'a'; ch <= 'z'; ch++) {
            char tmp[25];
            strcpy(tmp, word);
            tmp[index] = ch;
            //each time check the word with the dictionary
            for (int i = 0; i < 10000; i++) {
                if (strcmp(dict[i], tmp) == 0) {
                    fprintf(outp1, "%s\n", tmp) ;
                 }
            }
        }
    }
    // Check for the valid words that missing one letter from the input word
    for (int index = 0; index < strlen(word); index++) {
        char tmp[25];
        strcpy(tmp, word);
        //shift left from current index to get rid of the letter at current index
        for (int j = index; j < strlen(word); j++) {
            tmp[j] = tmp[j + 1];
        }
        //each time check the word with the dictionary
        for (int i = 0; i < 10000; i++) {
            if (strcmp(dict[i], tmp) == 0) {
                fprintf(outp1, "%s\n", tmp);
            }
        }
    }

    // Check for words that have one extra letter added
    for (int y = 0; y <= (int)strlen(word); y++) {
        for (char ch = 'a'; ch <= 'z'; ch++) {
            char tmp[25];
            strcpy(tmp, word);
            //shift right from current index to add the letter a-z at current index
            for (int j = strlen(tmp); j >= y; j--) {
                tmp[j + 1] = tmp[j];
            }
            tmp[y] = ch;
            //each time check the word with the dictionary
            for (int i = 0; i < 10000; i++) {
                if (strcmp(dict[i], tmp) == 0) {
                    fprintf(outp1, "%s\n", tmp);
                }
            }
        }
    }

    // Check for the words that have two letters swapped
    for (int index = 0; index < strlen(word); index++) {
        for (int j = index + 1; j < strlen(word); j++) {
            //swap the letters at index and j(which are next to each other)
            char tmp[25];
            strcpy(tmp, word);
            char tmp2 = tmp[j];
            tmp[j] = tmp[index];
            tmp[index] = tmp2;
            for (int i = 0; i < 10000; i++) {
                if (strcmp(dict[i], tmp) == 0) {
                    fprintf(outp1, "%s\n", tmp);
                }
            }
        }
    }

    fprintf(outp1, "\n");//after complete all suggestions for a word, add a new line.
}

int main() {
    char dict[10000][25];
    FILE *inp = fopen("dict.txt", "r");

  //create dictionary array
  int c=0;
  while(!feof(inp)){//while not end of file read dict file and copy to dict array
    fscanf(inp,"%s",dict[c++]);
  }
    fclose(inp);

    //fixed size 2D array to put sentences from input file
    char input[100][100]; 
    FILE *inputFile = fopen("spell.txt", "r");

    int lines = 0;
    while (fgets(input[lines], 100, inputFile) != NULL) {
        // Remove newline character to handle last word of each sentences correctly
        int len = 0;
        while (input[lines][len] != '\0') {
            len++;
        }
        //if the last character is newline, replace it with null character
        if (len > 0 && input[lines][len - 1] == '\n') {
            input[lines][len - 1] = '\0';
        }
        lines++;
    }
    fclose(inputFile);
    //open output file to write the results
    FILE *outp1 = fopen("outp1.txt", "w");
    int incorrect_word_found = 0;

    for (int line = 0; line < lines; line++) {
        int column = 1;
        char currLine[100];
        strcpy(currLine, input[line]);
        //split the sentence into words
        char *word = strtok(currLine, " \n\t");

        while (word != NULL) {
            int found = 0;

            for (int i = 0; i < 10000; i++) {
                if (strcmp(dict[i], word) == 0) {
                    found = 1;
                    break;
                }
            }

            if (!found) {
                incorrect_word_found = 1; // found
                fprintf(outp1, "Incorrect word: %s at line %d, column %d\n", word, line + 1, column);
                checks(word, dict, outp1);
            }
            //move to column info next word in the sentence by updating the column
            column += strlen(word) + 1;
            //get the next word
            word = strtok(NULL, " \n\t");
        }
    }

    fclose(outp1);

    if (incorrect_word_found == 0) {
        printf("All correct.\n");
    } else {
        printf("Spell check completed. Check outp1.txt.\n");
    }

    return 0;
}
