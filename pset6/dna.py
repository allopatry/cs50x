'''
Checks the number of short tandem repeats from an input database in a reference DNA sequence.
Then compares the maximum number of each STR sequence against a 'fingerprint' of reference names and their
list of STR repeats.

Returns a name with the most likely person who can be identified by the reference sequence given the database of STRs.
'''

import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database file into a variable
    names = []
    with open(sys.argv[1], newline='') as csvfile:
        reader = csv.DictReader(csvfile, delimiter=',')
        header = reader.fieldnames
        subseq_list = header[1:]
        subseq_num = len(subseq_list)

        for name in reader:
            names.append(name)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as f:
        seq = f.read()

    # Find longest match of each STR in DNA sequence
    subseqs = {}
    for subseq in subseq_list:
        longest = longest_match(seq, subseq)
        subseqs[subseq] = longest

    # Check database for matching profiles
    for n in names:
        i = 0
        for subseq in subseq_list:
            foo = int(n[subseq])
            bar = int(subseqs[subseq])
            if foo == bar:
                if i == subseq_num-1:
                    answer = n['name']
                    print(answer)
                    sys.exit(1)
                else:
                    i += 1
                    continue
            else:
                break
    print("No match")
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
