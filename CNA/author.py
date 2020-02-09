class Author:

	def __init__(self):
		name = '' #is the name of the author
		coAuthors = [] #is set of tuples of of the form (coauthor name, coauthor affiliation, # times authored together, ID)
		affiliation = '' #is the affiliation of the author
		


	#createAuthor(paper, authorName) creates a author object for 
	#author authorName of Paper paper.
	@staticmethod
	def createAuthor(paper, authorName):
		author = Author()
		author.name = authorName
		author.affiliation = paper.getAuthorAffiliation(authorName)
		author.coAuthors = paper.buildCoAuthorList(authorName)
		
	#createAuthor(paper, authorName, affiliation) creates a author object for 
	#author authorName of Paper paper.
	@staticmethod
	def createAuthor(paper, authorName, affiliation):
		author = Author()
		author.name = authorName
		author.affiliation = affiliation
		author.coAuthors = paper.buildCoAuthorList(authorName)


		return author

	#expands an authors coAuthor list using authors and affiliation from Paper paper.
	def expandCoAuthorList(self, paper):
		coAuthorsOfPaper = paper.buildCoAuthorList(self.name)

		for coAuth in self.coAuthors:
			for coAuthNewPaper in coAuthorsOfPaper:
				if((coAuth[0] == coAuthNewPaper[0]) and (coAuth[1] == coAuthNewPaper[1])):
					indexOfAuthToUpdate = self.coAuthors.index(coAuth)
					oldCoAuth = self.coAuthors.pop(indexOfAuthToUpdate)

					updatedCoAuth =  (oldCoAuth[0], oldCoAuth[1], 1 + oldCoAuth[2])
					self.coAuthors.insert(indexOfAuthToUpdate, updatedCoAuth)

					coAuthorsOfPaper.remove(coAuthNewPaper)
					break

		self.coAuthors.extend(coAuthorsOfPaper)

	#returns nodeID for author, self.name+self.affiliation
	def getID(self):
		return self.name+self.affiliation

	#prints an author
	def printAuthor(self):
		print(self.name)
		print(self.affiliation)
		print('CoAuthors:')
		for coAuth in self.coAuthors:
			print(coAuth)

############ END CLASS ##########################