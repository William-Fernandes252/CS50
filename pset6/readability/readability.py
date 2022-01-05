from cs50 import get_string

def main():
    text = get_string("Text: ")

    nSentences = countSentences(text)
    nWords = countWords(text)
    nLetters = countLetters(text);
    gradeLevel = computeLiauIndex(nLetters, nWords, nSentences)

    if gradeLevel - int(gradeLevel) > 0.5:
        gradeLevel = int(gradeLevel) + 1
    else:
        gradeLevel = int(gradeLevel)

    if gradeLevel < 1:
        print("Before Grade 1")
    elif gradeLevel > 16:
        print("Grade 16+")
    else:
        print(f"Grade {gradeLevel}")

def countWords(text):
    return text.count(" ") + 1

def countSentences(text):
    counter = 0
    for c in text:
        if c in ".!?":
            counter += 1
    return counter

def countLetters(text):
    counter = 0
    for c in text:
        if c.isalpha():
            counter += 1
    return counter

def computeLiauIndex(nLetters, nWords, nSentences):
    return 0.0588 * (nLetters * 100.0 / nWords) - 0.296 * (nSentences * 100.0 / nWords) - 15.8;

if __name__ == "__main__":
    main()