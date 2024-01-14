# TODO
# Importing required libraries
import re
from cs50 import get_string
import sys

# getting card number from user and checks if user entered a full digit input
no = get_string("Number: ")
while not no.isdigit():
    no = get_string("Number: ")

# calculating validity of card according to Luhn's algorithm
multipliednumbers = []
for i in range((len(no) - 2), -1, -2):
    pro = int(no[i]) * 2
    if pro >= 10:
        twodigstr = str(pro)
        for j in range(len(twodigstr)):
            digit = int(twodigstr[j])
            multipliednumbers.append(digit)

    else:
        multipliednumbers.append(pro)

sum = 0
for i in range(len(multipliednumbers)):
    sum += multipliednumbers[i]

for i in range(len(no), 0, -2):
    sum += int(no[i - 1])

if not (sum % 10 == 0):
    print("INVALID")
    sys.exit(1)

# after checking for card validity checking card type below
if len(no) == 15 and re.search("^37|^34", no):
    print("AMEX")

elif len(no) == 16 and re.search("^51|^52|^53|^54|55", no):
    print("MASTERCARD")

elif (len(no) == 13 or len(no) == 16) and re.search("^4", no):
    print("VISA")

else:
    print("INVALID")