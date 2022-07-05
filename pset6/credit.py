'''
Checks that a credit card number is likely valid and for valid cards
     returns the card manufacturer as a string to the terminal.

Luhn's Algorithm for checksum:
1. Multiply every other digit by 2, starting with the number's
    second-to-last digit, and then add those products' digits together.
2. Add the sum to the sum of the digits that weren't multiplied by 2.
3. If the total's last digit is 0 (or, put more formally,
     if the total modulo 10 is congruent to 0), the number is valid!

Card definitions:
AMEX: 15-digit number. Starts with 34 or 37.
MASTERCARD: 16-digit number. Starts with 51, 52, 53, 54, or 55.
VISA: 13- or 16-digit number. Starts with 4.
'''

# Define variables
list_amex = ['34', '37']
list_mastercard = ['51', '52', '53', '54', '55']
list_visa = ['4']


def main():

    # The while loop will continue to prompt for input until a reasonable prompt is provided by the user
    while True:
        try:
            card_num_str = (input("Number: "))
            # Check the length of the input string and run checksum using Luhns formula
            if num_check(card_num_str) == False:
                print("INVALID")
                break
            else:
                if len(card_num_str) == 15:    # Could be AMEX
                    prefix = card_num_str[0:2]
                    if prefix in list_amex:
                        print("AMEX")
                        break
                    else:
                        print("INVALID")
                        break
                elif len(card_num_str) == 13:    # Could be AMEX
                    prefix = card_num_str[0:2]
                    if prefix in list_amex:
                        print("AMEX")
                        break
                    else:
                        print("INVALID")
                        break
                elif len(card_num_str) == 16:    # Could be MASTERCARD or VISA
                    prefix_a = card_num_str[0]
                    prefix_b = card_num_str[0:2]
                    if prefix_a == '5':
                        if prefix_b in list_mastercard:
                            print("MASTERCARD")
                            break
                        else:
                            print("INVALID")
                            break
                    else:
                        if prefix_a in list_visa:
                            print("VISA")
                            break
                        else:
                            print("INVALID")
                            break
        except Exception as e:    # Exception catcher. Underutilized here, but could be expanded upon.
            continue


def luhn_check(number):
    '''Does the actual check of the credit card number using the Luhn algorithm.
    Returns a boolean.'''
    num_len = len(number)
    even, odd = 0, 0
    if num_len % 2 == 0:    # card number has even number of digits
        for i in range(num_len):
            n = int(number[i])
            if i % 2 == 0:    # is even
                m = n * 2
                if m >= 10:
                    even += m // 10
                    even += m % 10
                else:
                    even += m
            else:    # is odd
                odd += n
    else:
        for i in range(num_len):
            n = int(number[i])
            if i % 2 != 0:    # is even
                m = n * 2
                if m >= 10:
                    even += m // 10
                    even += m % 10
                else:
                    even += m
            else:    # is odd
                odd += n
    checksum = (even + odd) % 10
    if checksum == 0:
        return True
    else:
        return False


def num_check(card_num_str):
    '''Checks that the input string is free of non-integer characters
    and is the appropriate length'''
    list_lengths = [13, 15, 16]
    card_num_strip = card_num_str.strip()    # Should remove interspersed whitespace, but I don't think it is working as intended.
    if len(card_num_strip) not in list_lengths:
        return False
    else:
        if card_num_strip.isdigit():    # Checks that string is composed of digits. May not account for whitespace characters.
            b = luhn_check(card_num_strip)
            if b == True:
                return True
            else:
                return False
        else:
            return False


if __name__ == "__main__":
    main()