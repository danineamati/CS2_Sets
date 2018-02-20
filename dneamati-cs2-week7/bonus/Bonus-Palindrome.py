def palindrome(string):
    '''This function takes a string and checks if there exists an anagram that
    is a palindrome. Note that a palidrom is only possible if at most one 
    character is repeated an odd number of times.'''
    charDict = {}
    
    for char in string:
        if char not in charDict:
            charDict[char] = 1
        elif char in charDict:
            charDict[char] += 1
    
    numberOdd = ('', 0)
    frontstring = ''
    backstring = ''
    
    for char in charDict:
        if charDict[char] % 2 == 1:
            numberOdd = (char, numberOdd[1] + 1);
            if numberOdd[1] > 1:
                return ''
        else:
            frontstring += char
            backstring = char + backstring
    
    return frontstring + numberOdd[0] + backstring


def main():
    print(palindrome("racecar"))
    print(palindrome("asdfasdf"))
    print(palindrome("asdfghjkll"))
    print(palindrome("weatinattewsanitaryrs"))
    


main()