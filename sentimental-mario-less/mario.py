# TODO
# imorting needed libraries
import cs50
# takes required height of half pyramid from user
h = cs50.get_int("Height:")
# checks for number validity
while h > 8 or h < 1:
    h = cs50.get_int("Height:")

# prints half pyramid
for i in range(h):
    for j in range(h - (i+1)):
        print(" ", end="")

    for k in range(i + 1):
        print("#", end="")

    print()