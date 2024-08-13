import csv
from sys import argv
from os.path import isfile


def main():
    names = []
    rows = []
    sequences = ""
    result = {}
    # TODO: Check for command-line usage
    if (len(argv) != 3):
        print("You should provide 2 files")
    elif not isfile(argv[1]) or not isfile(argv[2]):
        print("One of your file path doesn't exists")
        return

    # TODO: Read database file into a variable

    with open(argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)
        reader.fieldnames.pop(0)
        names = reader.fieldnames

    # TODO: Read DNA sequence file into a variable

    with open(argv[2], 'r') as file:
        sequences = file.read()

    # TODO: Find longest match of each STR in DNA sequence

    for name in names:
        match_length = longest_match(sequences, name)
        result[name] = str(match_length)

    # TODO: Check database for matching profiles
    winner = "No match"
    for row in rows:
        match = True
        for name in names:
            if row[name] != result[name]:
                match = False
                break
        if match:
            winner = row["name"]
            break

    print(winner)
    return


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

            # print(start, end, sequence[start:end])

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
