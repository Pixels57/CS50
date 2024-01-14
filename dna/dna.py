import csv
import sys
import pathlib


def main():

    # TODO: Check for command-line usage

    argument = sys.argv

    if len(argument) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    elif pathlib.Path(argument[1]).suffix != '.csv':
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    elif pathlib.Path(argument[2]).suffix != '.txt':
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable

    database = []

    with open(argument[1]) as file:
        file_reader = csv.DictReader(file)
        for data in file_reader:
            database.append(data)

    # TODO: Read DNA sequence file into a variable

    f = open(argument[2], 'r')
    seq = f.readline()
    f.close()

    # TODO: Find longest match of each STR in DNA sequence
    if len(list(database[0].keys())) == 4:
        agatc_count = longest_match(seq, 'AGATC')
        aatg_count = longest_match(seq, 'AATG')
        tatc_count = longest_match(seq, 'TATC')

    if len(list(database[0].keys())) == 9:
        agatc_count = longest_match(seq, "AGATC")
        aatg_count = longest_match(seq, "AATG")
        tatc_count = longest_match(seq, "TATC")
        tttct_count = longest_match(seq, "TTTTTTCT")
        tctag_count = longest_match(seq, "TCTAG")
        gata_count = longest_match(seq, "GATA")
        gaaa_count = longest_match(seq, "GAAA")
        tctg_count = longest_match(seq, "TCTG")

    # TODO: Check database for matching profiles
    if len(list(database[0].keys())) == 4:
        for data in database:
            if data["AGATC"] == str(agatc_count) and data["AATG"] == str(aatg_count) and data["TATC"] == str(tatc_count):
                return print(data["name"])

        return print("No match")

    if len(list(database[0].keys())) == 9:
        for data in database:
            if data["AGATC"] == str(agatc_count) and data["AATG"] == str(aatg_count) and data["TATC"] == str(tatc_count) and data["TTTTTTCT"] == str(tttct_count) and data["TCTAG"] == str(tctag_count) and data["GATA"] == str(gata_count) and data["GAAA"] == str(gaaa_count) and data["TCTG"] == str(tctg_count):
                return print(data["name"])

        return print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
