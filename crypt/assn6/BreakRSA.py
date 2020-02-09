#BREAK RSA

# time: 1 hr 30 min

def readCipherText(filename):
    with open(filename, 'r') as f:
        ciphertext = f.read().strip()
        return ciphertext

def intToChar(num):
    return chr(num + 65)

def exgcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = exgcd(b % a, a)
        return (g, x - (b // a) * y, y)

#returns none if a is not invertable mod m
def modInverse(a, m):
    gf, x, y = exgcd(a, m)
    if(gf == 1):
        return x % m
    else:
        return None

def factorN(n):
    for i in range(3, n, 2):
        if(n % i == 0):
            return i
        
    return None

def modularPower(x, a, m):
    bits = format(a, 'b')

    rb = bits[::-1]

    powers = []
    i = 0

    for b in rb:
        if(len(powers) == 0):
            powers.append(x)
        else:
            powers.append((powers[i - 1] * powers[i - 1] % m))
        i += 1

    i = 0
    y = 1
    while(i < len(powers)):
        if(rb[i] == '1'):
            y = y * powers[i] % m
        i += 1

    return y

def decipherRSA(y, a, n):
    return modularPower(y, a, n)

def numToChars(decpiheredNum):
    plaintext = []
    x = decpiheredNum
    while(x > 0):
        plaintext.append(intToChar(int(x % 26)))

        x = int(x / 26)
    
    plaintext.reverse()
    return ''.join(plaintext)
    
#       MAIN        #

n = 2177994659
b = 65537
p = factorN(n)
q = int(n / p)

phi = (p - 1) * (q - 1)
a = modInverse(b, phi)

print('p = ' + str(p))
print('q = ' + str(q))
print('phi = ' + str(phi))
print('a = ' + str(a))


cipherNums = readCipherText('rsa-cipher').split()
#print(cipherNums)

plaintext = ''

for y in cipherNums:
    decpiheredNum = decipherRSA(int(y), a, n)
    plaintext += numToChars(decpiheredNum)

print(plaintext)
