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

def intToChar(num):
    return chr(num + 65)

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

#   Main    #

print('Question 2:')
for i in range(0, 26):
    print(str(i) + ', ' + intToChar(i) + '-> ' + str(modularPower(i, 25, 18721)))

print('\n')

print('Question 4:')
print('mod power: 9983^2052765 mod 36581 = ' + str(modularPower(9983, 2052765, 36581)))
v = modularPower(9983, 2052765, 36581)
while(v != 1):
    v0 = v
    print('v0 = ' + str(v0))

    v = modularPower(v, 2, 36581)
    print('v = ' + str(v))

print('v0 = ' + str(v0))

print('\n')

print('mod power: 13461^2052765 mod 36581 = ' + str(modularPower(13461, 2052765, 36581)))
v = modularPower(13461, 2052765, 36581)
while(v != 1):
    v0 = v
    print('v0 = ' + str(v0))

    v = modularPower(v, 2, 36581)
    print('v = ' + str(v))

print('v0 = ' + str(v0))

