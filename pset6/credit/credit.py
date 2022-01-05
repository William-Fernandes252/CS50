import re

def main():
    number = input("Number: ").replace(" ", "")

    if not re.match("[\d]+$", number) and len(number) not in [13, 15, 16]:
        print("INVALID")
    else:
        number = int(number)
        firstDigit, secondDigit = catFirstTwoDigits(number)
        validate = validateCard(number, firstDigit, secondDigit)
        if validate == 0:
            print("INVALID")
        elif validate == 1:
            print("AMEX")
        elif validate == 2:
            print("VISA")
        elif validate == 3:
            print("MASTERCARD")

def catFirstTwoDigits(number):
    while number > 0:
        number = int(number/10)
        if number < 100 and number > 9:
            secondDigit = number % 10
        elif number < 10 and number > 0:
            firstDigit = number % 10
    return firstDigit, secondDigit

def validateCard(number, firstDigit, secondDigit):
    pairDigitsSum = 0
    checkCardSum = 0
    digitPos = 1
    validation = 0

    while(number > 0):
        digit = number % 10
        if digitPos % 2 == 0:
            if digit * 2 < 10:
                pairDigitsSum += digit * 2
            else:
                aux = digit * 2
                while aux > 0:
                    pairDigitsSum += aux % 10
                    aux = int(aux/10)
        else:
            checkCardSum += digit
        digitPos += 1
        number = int(number/10)
    checkCardSum += pairDigitsSum

    if checkCardSum % 10 == 0:
        if firstDigit == 5 and secondDigit in [1, 2, 3, 4, 5]:
            validation = 3
        elif firstDigit == 4:
            validation = 2
        elif firstDigit == 3 and secondDigit in [4, 7]:
            validation = 1

    return validation

if __name__ == "__main__":
    main()