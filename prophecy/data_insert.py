from cs50 import SQL
import csv

students = []
original_roster = SQL("sqlite:///roster.db")
with open ("students.csv") as file:
    file_reader = csv.DictReader(file)
    for student in file_reader:
        students.append(student)

houses = []
heads = []
for student in students:
    if student["house"] not in houses:
        houses.append(student["house"])
    if student["head"] not in heads:
        heads.append(student["head"])

for no_of_houses in range(len(houses)):
    row_houses = original_roster.execute("INSERT INTO houses (house, head) VALUES (?, ?);", houses[no_of_houses], heads[no_of_houses])

for student in students:
    cur = original_roster.cursor()
    cursor.execute("SELECT id FROM houses WHERE house = ?", student["house"])
    house_id_query = cursor.fetchone()
    row_assignments = original_roster.execute("INSERT INTO assignments (student_id, house_id) VALUES (?, SELECT id FROM houses WHERE house = ?);", student["id"], student["house"])