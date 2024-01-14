# TODO
# importing required libraries
from cs50 import get_string

# getting text from user
text = get_string("Text: ")
lettercount = 0
sentencecount = 0

# counting letter, words, and sentences
for i in range(len(text)):
    if text[i].isalpha():
        lettercount += 1

    if text[i] == '.' or text[i] == '?' or text[i] == '!':
        sentencecount += 1


wordscount = len(text.split())

# calculating grade and printing it
L = (lettercount / wordscount) * 100
S = (sentencecount / wordscount) * 100
index = (0.0588 * L) - (0.296 * S) - 15.8
if index >= 16:
    print("Grade: 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print("Grade: " + str(round(index)))