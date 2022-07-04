# Python implementation of the mario-more problem set

import sys

while True:
    try:
        height = int(input("Height: "))
        if (height > 0) & (height < 9):
            for i in range(height):
                # Variable to keep track of number of spaces
                j = (height - i) - 1

                # Variable to keep track of number of blocks
                k = i + 1
                print(j*" "+k*"#"+"  "+k*"#")
            break
    except Exception as e:
        continue