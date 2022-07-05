'''
Example
Congratulations! Today is your day. You're off to Great Places! You're off and away!
Grade 3

Formula: index = 0.0588 * L - 0.296 * S - 15.8
L = the average number of letters per 100 words in the text
S = the average number of sentences per 100 words in the text.
Max level is 16 and will be reported as 16+
Anything lower than level one will be reported as Before Grade 1
'''


from cs50 import get_string
import re


def main():
    # Input will be from the user from the terminal
    text = get_input()
    level = formula(text)
    # Account for very small levels
    if level < 1:
        print("Before Grade 1")
    # Account for very high levels
    elif level >= 16:
        print("Grade 16+")
    # Print a rounded integer of the level
    else:
        level_r = round(level)
        str(level_r)
        print("Grade", level_r)


def get_input():
    # Gets input from the user
    s = get_string("Text: ")
    return s


def formula(text):
    # Calculates grade level of text
    letters = len(re.findall("\w", text))
    spaces = len(re.findall("\s", text))
    words = spaces + 1
    sentences = len(re.findall("[\!|\.|\?]", text))

    l = (letters / words) * 100.0
    s = (sentences / words) * 100.0
    level = (0.0588 * l) - (0.296 * s) - 15.8

    return level


if __name__ == "__main__":
    main()