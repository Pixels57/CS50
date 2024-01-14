import cs50

greeting = input("Greeting: ")
greeting = greeting.lower()
wordlist = greeting.split()
greetlist = ["hello", "hello,"]
if wordlist[0] in greetlist:
    print("$0")
elif wordlist[0][0] == "h":
    print("$20")
else:
    print("$100")