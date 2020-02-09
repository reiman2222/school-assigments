#This program aids in breking a substitution cipher


def readCipherText(filename):
    with open(filename, 'r') as f:
        ciphertext = f.read().strip()

    return ciphertext

def printTable(frequencyDict,n, totalChars):
	print('\tn = ' + str(n))
	print('gram\t\tfreq')
	tuples = list(frequencyDict.items())
	sortedGrams = sorted(tuples, key=lambda k: k[1], reverse=True)
	i = 0
	for tup in sortedGrams:
		if(i > 35 and n >= 3):
			break
		i += 1
		
		print(tup[0] + '\t\t' + str(tup[1])+ '\t' + str(round(tup[1]/ totalChars, 3)))
	print('')

def calcNgramFreq(cipherText, n):
	freqDict = {}

	for i in range(len(cipherText) - n + 1):
		nGram = cipherText[i:i+n]
		if nGram in freqDict:
			freqDict[nGram] += 1
		else:
			freqDict[nGram] = 1
	return freqDict

def calculateCharacterFreq(cipherText):
	i = 1
	while(i <= 5):
		freqDict = calcNgramFreq(cipherText, i)
		printTable(freqDict,i,len(cipherText))
		i+=1

def decipherAndPrint(cipherText, key):
	
	plainText = ""
	for char in cipherText:
		if(key[char] == None):
			plainText = plainText + '-'
		else:
			plainText = plainText + key[char]
	
	incAmmount = 60
	pos = 0
	while(pos < len(cipherText)):
		print(cipherText[pos:pos+incAmmount])
		print(plainText[pos:pos+incAmmount])
		pos += incAmmount


def updateKey(substitution, decryptionAttempts, key, cipherText):
	if ',' in substitution:

		subL = substitution.split(',')

		sub = substitution.replace(',', '->')
		decryptionAttempts.append(sub)
		
		if(subL[1] == 'None'):
			key[subL[0].upper()] = None
		else:
			key[subL[0].upper()] = subL[1].upper()
		decipherAndPrint(cipherText,key)

	else:
		print('invalid substitution')


cipherText = readCipherText('substituion-cipher.txt')

#cipherText = readCipherText('test.txt')


calculateCharacterFreq(cipherText)

#list of tuples of strings
decryptionAttempts = []

key={'A':None, 'B':None, 'C':None, 'D':None, 'E':None,
	'F':None, 'G':None, 'H':None, 'I':None, 'J':None, 'K':None, 'L':None,
	'M':None, 'N':None, 'O':None, 'P':None, 'Q':None, 'R':None, 'S':None, 
	'T':None, 'U':None, 'V':None, 'W':None, 'X':None, 'Y':None, 'Z':None} 



decipherAndPrint(cipherText,key)


curInput = input('Enter substitution in form x,y or end to exit, key to print key, restart to reset key\n')

while(curInput != 'end'):
	if(curInput == 'key'):
		print(key)
	elif(curInput == 'restart'):
		key={'A':None, 'B':None, 'C':None, 'D':None, 'E':None,
			'F':None, 'G':None, 'H':None, 'I':None, 'J':None, 'K':None, 'L':None,
			'M':None, 'N':None, 'O':None, 'P':None, 'Q':None, 'R':None, 'S':None, 
			'T':None, 'U':None, 'V':None, 'W':None, 'X':None, 'Y':None, 'Z':None}

	else:
		updateKey(curInput, decryptionAttempts, key, cipherText)


	curInput = input('\n')

print("\nDecrption Process:")
for i in decryptionAttempts:
	print(i)

