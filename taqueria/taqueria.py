import cs50
import sys


menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}


total = 0.00
while True:
    try:
        order = input("Item: ")
    except EOFError:
        print()
        break
    order = order.title()
    if order in menu:
        price = menu.get(order)
        total += price
        round(total, 2)
        print("Total: $" + f"{total:.2f}")
    else:
        continue

