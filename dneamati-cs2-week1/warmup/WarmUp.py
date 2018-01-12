# Daniel Neamati
# CS2 Warm-Up

def WarmUp(in_string):
    '''This function takes a sting and returns a list containing tuples of
    the letter and the number of times that letter appears in the function.
    
    Time complexity: This Function is of O(n) complexity. While the built-in
    count function will go through the length (n) of the input string 52 times
    (once for each lowercase and uppercaseletter), 52 is a constant. 
    Asymptotically, 52 will become negligible and the function is of O(n) time
    complexity.
    
    Space complexity: Since the output contains a list of 26 tuples (one for 
    each letter), the space complexity is always 26.'''
    
    letters = list(in_string)
    letter_count = []
    
    for letter in 'abcdefghijklmnopqrstuvwxyz':
        letter_count.append((letter.lower(),\
                             letters.count(letter.lower())\
                             + letters.count(letter.upper())))
    return letter_count

def main():
    '''This function handles user input and runs the program.'''
    in_string = input("Enter a string: ")
    Alphabet_count = WarmUp(in_string)
    for pair in Alphabet_count:
        print(pair)
    
    
main()