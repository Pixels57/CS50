import sys
import cs50
from pyfiglet import Figlet

figlet = Figlet()
fontlist = figlet.getFonts()

if (len(sys.argv)) != 3 and (len(sys.argv)) != 1:
    print("Wrong Usage.")
    sys.exit(1)

arguments = sys.argv

if arguments[1] != '-f' and arguments[1] != '--font':
    print("Wrong Usage.")
    sys.exit(1)

isfontavailable = False

if arguments[2] in fontlist:
    isfontavailable = True

if not isfontavailable:
    print("Font is not available.")
    sys.exit(1)

userinput = input("Input: ")
figlet.setFont(font = arguments[2])
print(figlet.renderText(userinput))