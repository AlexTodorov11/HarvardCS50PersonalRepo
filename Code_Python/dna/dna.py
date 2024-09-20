import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return

    # TODO: Read database file into a variable
    database = []
    with open(sys.argv[1], newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            database.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        dna_sequence = file.read()

    # Get the list of STRs from the first line of the CSV (keys other than 'name')
    str_sequences = list(database[0].keys())[1:]

    # TODO: Find longest match of each STR in DNA sequence
    longest_matches = {}
    for str_seq in str_sequences:
        longest_matches[str_seq] = longest_match(dna_sequence, str_seq)

    # TODO: Check database for matching profiles
    for person in database:
        match = True
        for str_seq in str_sequences:
            # Compare the longest match count with the person's STR count in the database
            if int(person[str_seq]) != longest_matches[str_seq]:
                match = False
                break
        if match:
            print(person['name'])
            return

    # If no match found, print "No match"
    print("No match")


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