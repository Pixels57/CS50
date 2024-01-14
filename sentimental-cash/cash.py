# TODO
# imorting needed libraries
from cs50 import get_float
# takes required owed money from the use and checks if it is non negativa value
owed = get_float("Change owed: ")
while owed < 0:
    owed = get_float("Change owed: ")

# variable initialization
c = 0
change = 0

# calculating number of required coins
while change < owed:
    if round((change + 0.25), 2) < owed or round((change + 0.25), 2) == owed:
        c += 1
        change += 0.25
        change = round(change, 2)

    elif round((change + 0.10), 2) <= owed or round((change + 0.25), 2) == owed:
        c += 1
        change += 0.10
        change = round(change, 2)

    elif round((change + 0.05), 2) <= owed or round((change + 0.25), 2) == owed:
        c += 1
        change += 0.05
        change = round(change, 2)

    elif round((change + 0.01), 2) <= owed or round((change + 0.25), 2) == owed:
        c += 1
        change += 0.01
        change = round(change, 2)


# printing end result
print(c)