# SpellChecker
This C program performs spell checking on an input text file  by comparing each word against a dictionary. For each misspelled word, it suggests possible corrections based on common typographical errors. The results are written to an output file .

Features
Dictionary Loading: Reads a dictionary file containing valid words.
Spell Checking: Processes an input file to identify words not present in the dictionary.
Suggestion Generation: For each misspelled word, suggests corrections by:
Replacing each letter with every other letter of the alphabet.
Removing one letter at a time.
Adding one letter at any position.
Swapping adjacent letters.
Output: Logs misspelled words and their suggested corrections.
Requirements
Input Files:
A text file containing a list of valid words, one per line.
A text file containing the text to be spell-checked.
Output File: A text file where results will be written.
