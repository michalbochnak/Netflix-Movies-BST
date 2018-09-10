/*main.c*/

//
// Searching for movies in a binary search tree.
//
// << Michal Bochnak, mbochn2@uic.edu >>
// U. of Illinois, Chicago
// CS251, Spring 2017
// Project #02
//

// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



typedef int     BSTKey;
typedef char	BSTValue[256];

typedef struct BSTNode
{
	BSTKey    Key;
	BSTValue  Value[256];
	char MovieName[256];
	struct BSTNode  *Left;
	struct BSTNode  *Right;
} BSTNode;

typedef struct BST
{
	BSTNode *Root;
	int      Count;
} BST;


//
// BSTCreate: dynamically creates and returns an empty
// binary search tree:
//
BST *BSTCreate()
{
	BST *tree;

	tree = (BST *)malloc(sizeof(BST));
	tree->Root = NULL;
	tree->Count = 0;

	return tree;
}

//
// BSTCompareKeys: compares key1 and key2, returning
//   value < 0 if key1 <  key2
//   0         if key1 == key2
//   value > 0 if key1 >  key2
//
int BSTCompareKeys(BSTKey key1, BSTKey key2)
{
	if (key1 < key2)
		return -1;
	else if (key1 == key2)
		return 0;
	else
		return 1;
}


//
// BSTSearch: searches the binary search tree for a node containing the
// same key.  If a match is found, a pointer to the node is returned, 
// otherwise NULL is returned.
//
BSTNode *BSTSearch(BST *tree, BSTKey key)
{
	BSTNode *cur = tree->Root;

	if (cur == NULL) {
		return NULL;
	}
	else {
		while (cur != NULL) {
			if (key == cur->Key) {
				printf(">>Visiting %d: '%s'\n", cur->Key, cur->MovieName);
				return cur;
			}
			else if (key < cur->Key) {
				printf(">>Visiting %d: '%s'\n", cur->Key, cur->MovieName);
				cur = cur->Left;
			}
			else {
				printf(">>Visiting %d: '%s'\n", cur->Key, cur->MovieName);
				cur = cur->Right;
			}
		}
		return NULL;
	}	
}


//
// BSTInsert: inserts the given (key, value) pair into the binary search
// tree.  Returns true (non-zero) if the insert was successful, returns 
// false (0) if the given key is already in the tree -- in which case the
// given (key, value) pair is not inserted.
//
int BSTInsert(BST *tree, BSTKey key, BSTValue value)
{
	// create new node
	BSTNode *node;
	node = (BSTNode *)malloc(sizeof(BSTNode));
	node->Key = key;
	strcpy(node->MovieName, value);
	node->Left = NULL;
	node->Right = NULL;

	// empty tree
	if (tree->Root == NULL) {
		tree->Root = node;
		tree->Count++;
		return 1;
	}
	else {
		// create pointer to current Node
		BSTNode *cur = tree->Root;

		while (cur != NULL) {
			if (key == cur->Key) {
				return 0;
			}
			else if (key < cur->Key) {
				if (cur->Left == NULL) {
					cur->Left = node;
					tree->Count++;
					return 1;
				}
				cur = cur->Left;
			}
			else {
				if (cur->Right == NULL) {
					cur->Right = node;
					tree->Count++;
					return 1;
				}
				cur = cur->Right;
			}
		}
	}

	return 0;
}


//
// getFileName: inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be opened, an
// error message is output and the program is exited.
//
char *getFileName()
{
	char filename[512];
	int  fnsize = sizeof(filename) / sizeof(filename[0]);

	// input filename from the keyboard:
	fgets(filename, fnsize, stdin);
	filename[strcspn(filename, "\r\n")] = '\0';  // strip EOL char(s):

												 // make sure filename exists and can be opened:
	FILE *infile = fopen(filename, "r");
	if (infile == NULL)
	{
		printf("**Error: unable to open '%s'\n\n", filename);
		exit(-1);
	}

	fclose(infile);

	// duplicate and return filename:
	char *s = (char *)malloc((strlen(filename) + 1) * sizeof(char));
	strcpy(s, filename);

	return s;
}


// inputs and discards the remainder of the current line for the 
// given input stream, including the EOL character(s):
void skipRestOfInput(FILE *stream)
{
	char restOfLine[256];
	int rolLength = sizeof(restOfLine) / sizeof(restOfLine[0]);

	fgets(restOfLine, rolLength, stream);
}


// Create the Binary Search Tree
void MoviesBSTCreate(moviesTree, pMoviesFile) {
	char line[200];
	int lineLength = 300;
	double value = 0;
	

	// skip the first line of the input file
	fgets(line, lineLength, pMoviesFile);
	line[strcspn(line, "\r\n")] = '\0';		// avoid errors on different platforms

	while (fgets(line, lineLength, pMoviesFile) != NULL) {
		line[strcspn(line, "\r\n")] = '\0';	// avoid errors on different platforms
		BSTNode Node;
		Node.Key = atoi(strtok(line, ","));
		strcpy(Node.MovieName, (strtok(NULL, ",")));
		BSTInsert(moviesTree, Node.Key, Node.MovieName);
	}
}




int main()
{
	// get movies filename from the user/stdin:
	char *moviesFileName = getFileName();
	FILE *pMoviesFile = fopen(moviesFileName, "r");		// file pointer
	int searchFor = 0;
	BSTNode *searchResult = NULL;
	
	// create empty tree
	BST *moviesTree = BSTCreate();

	// store movies into BST
	MoviesBSTCreate(moviesTree, pMoviesFile);	

	// read in ID to search for
	scanf("%d", &searchFor);

	searchResult = BSTSearch(moviesTree, searchFor);


	// Display results
	if (searchResult != NULL) {
		printf("Movie %d: '%s'\n", searchResult->Key, searchResult->MovieName);
	}
	else {
		printf("Movie %d: not found\n", searchFor);
	}

	return 0;
}
