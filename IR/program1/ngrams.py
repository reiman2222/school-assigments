import re
import csv

#compute_ngram_charfreq(invertedIndex, charFile, n, text) computes the frequency
#of each word in the given file.
#invertedIndex is the inverted index
#charFreq is the frequency in which each character appears.
#n is the size of grams (number of tokens).
#text is the text we're working with.
def compute_ngram_charfreq(invertedIndex, charFreq, n, text):
	i = 0
	while i < len(text):
		if (i + n) <= len(text):
			ngram_as_list = text[i:i+n] 
			ngram = " ".join(ngram_as_list) #converts ngram to string
			
			#adds/inserts ngram to dictonary invertedIndex
			#print "The current ngram is:  %s" %ngram
			if ngram in invertedIndex:
				invertedIndex[ngram] += 1
			else:
				invertedIndex[ngram] = 1
		
		compute_char_freq(charFreq, text[i])
		
		i = i + 1


#compute_char_freq(char_freq, word) calculates the character frequency 
#char_freq is the character frequency array
def compute_char_freq(char_freq, token):
	for i in token:
		char_freq[rank(i)] += 1

#rank(char) calculates position of character c in charFreq array
#rank('a') = 0
def rank(char):
	return ord(char) - 97

#give_word_list(filename) returns list of words from file called filename
def give_word_list(filename):
    f = open(filename, 'r')
    words = []
    for line in f:
        for token in line.split():
            words.extend(token.split('-'))
    return words

#give_file_path(filename) returns the list of paths
#stored in the file called filename
def give_file_path(filename):
    f = open(filename, 'r')
    words = [token for line in f for token in line.split()]
    return words

#tokenize(word) returns the tokenized string named word
def tokenize(word):
    regex = re.compile('[^a-zA-Z]+')
    w = regex.sub('', word)
    w = w.lower()
    return w

#tokenize_word_list(wordlist) returns a tokenizes a list of words
#wordlist is the list of words to tokenize
def tokenize_word_list(wordlist):
    i = 0
    while i < len(wordlist):
    	#prevents adding empty string to wordlist if string only
    	#contains usless characters
        temp = tokenize(wordlist[i])
        if temp != '':
            wordlist[i] = tokenize(wordlist[i])
            i = i + 1
        else:
            del wordlist[i]
    return wordlist

#write_char_freq(charFreq) writes the character frequency charFreq
#to an output file named 'charfreq.txt'
def write_char_freq(charFreq):
    outf = open('charfreq.txt', 'w')
    i = 0
    while i < len(charFreq):
        outf.write(chr(i + 97) + " : " + str(charFreq[i]) + "\n")
        i += 1
    outf.close()

#processCorpus(inputList, charFreq, invertedIndex) process all files in inputList
#each file is tokenized. The charFreq array and invertedIndex are updated according
#to the contents of the file.
def processCorpus(inputList, charFreq, invertedIndex, n):
    i = 0
    while i < len(inputList):
        text = give_word_list(inputList[i])
	print("processing %s" %inputList[i])
	text = tokenize_word_list(text)
	compute_ngram_charfreq(invertedIndex, charFreq, n, text)
	i +=  1

#printSortedIndex(sortedIndex) prints the first k entrys of the
#sorted index. sortedIndex is the sorted list of tuples 
#to be printed.
def printSortedIndex(sortedIndex, k):
	j = 0
	while j < k and j < len(sortedIndex):
		print sortedIndex[j]
		j += 1

#dictonary_to_csv(invertedIndex, filename) writes dictonary named invertedIndex
#to csv file named filename
def dictonary_to_csv(invertedIndex, filename):
	with open(filename, 'w') as f:  # Just use 'w' mode in 3.x
		w = csv.DictWriter(f, invertedIndex.keys())
   		w.writeheader()
   		w.writerow(invertedIndex)

#list_to_file(filename, invertedIndex) writes the list invertedIndex
#to file called filename
def list_to_file(filename, invertedIndex):
	f = open(filename, 'w')
	
	for item in invertedIndex:
  		f.write("%s\n" % item)

#####Main######


invertedIndex = {}

#charFreq hold the frequency count of characters a-z
#charFreq[0] represents the character a
#charFreq[1] represents the character b
#....
#charFreq[25] represents the character z
charFreq = [0] * 26

#n is the size of the n-gram 
n = 1

inputFiles = give_file_path('input-files.txt')

outputFileNames = ['unigram.txt', 'bigram.txt', 'trigram.txt']

i = 1

#process corpus for unigrams, bigrams and trigrams
while i <= 3:
	charFreq = [0] * 26
	invertedIndex = {}
	
	processCorpus(inputFiles, charFreq, invertedIndex, i)
	
	sortedNgramList = sorted(invertedIndex)
	list_to_file(outputFileNames[i - 1], sortedNgramList)

	i += 1



#print charFreq

#convert invertedIndex to list of tuples to be sorted
#IItuples = [(value, key) for key, value in invertedIndex.iteritems()]
#sortedTuples = sorted(IItuples, key=lambda x: x[0], reverse=True)

#print top ten most frequently occuring ngrams
#printSortedIndex(sortedTuples, 10)

write_char_freq(charFreq)

#dictonary_to_csv(invertedIndex, 'unigrams.csv')
