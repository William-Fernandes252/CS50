# Given a sequence of DNA and a CSV file containing STR counts for a list of individuals outputs to whom the DNA (most likely) belongs.

import csv
import sys

def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit()
    STRs = {}
    data = {}
    # Read data into memory from data.csv as dictionaries (name: [occurences of each STR])
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        dictReader = csv.DictReader(file)
        # Read STRs as dictionaries whose values will be the number of occurences of the key in the sequence
        for field in dictReader.fieldnames:
            STRs[field] = 0
        STRs.pop("name")
        for line in reader:
            data[line[0]] = [int(i) for i in line[1:]]
    # Read DNA sequence from file and count the occurences of each STRs on the data
    with open(sys.argv[2], "r") as file:
        DNA = file.readline()
    # Count max number of consecutive occurences of each STR in the DNA and store in the values of the STRs dictionary
    for STR in STRs:
        STRs[STR] = countSTRinDNA(DNA, STR);
    # Print the name of the person whose the STRs count matches the sequence read
    print(matchDNA(STRs, data))

# Count max number of consecutive occurences of STR in the DNA sequence
def countSTRinDNA(DNA, STR):
    maxConsecOcc = 0
    STRlen = len(STR)
    DNAlen = len(DNA)
    for i in range(DNAlen):
        if DNA[i:(i + STRlen)] == STR:
            consecOcc = 1
            for j in range((i + STRlen), DNAlen, STRlen):
                if DNA[j:(j + STRlen)] == STR:
                    consecOcc += 1
                else:
                    break
            if consecOcc > maxConsecOcc:
                maxConsecOcc = consecOcc
    return maxConsecOcc

# Return the name of the person whose STR data match the STRs count or "No match" if the STRs does not match any person
def matchDNA(STRs, data):
    match = "No match"
    occurences = list(STRs.values())
    for name in data:
        if occurences == data[name]:
            match = name
            break
    return match

if __name__ == "__main__":
    main()