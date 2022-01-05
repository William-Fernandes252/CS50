from cs50 import get_int

def main():
    while True:
        height = get_int("Height: ")
        if height >= 1 and height <= 8:
            break

    printPyramid(height)

def printPyramid(height):
    spaces = height - 1
    blocks = 1
    for h in range(height):
        for s in range(spaces):
            print(" ", end = "")
        for b in range(blocks):
            print("#", end = "")
        print("  ", end = "")
        for b in range(blocks):
            print("#", end = "")
        blocks += 1
        spaces -= 1
        print()

if __name__ == "__main__":
    main()