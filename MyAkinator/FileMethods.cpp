#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "FileMethods.h"
#include "GameProcessMethods.h"


char* IndicateFileName(bool isOld)
{
	char *name = (char*)calloc(100, sizeof(char));

	if (name == nullptr)
	{
		return nullptr;
	}

	char *buffer = (char*)calloc(50, sizeof(char));

	if (buffer == nullptr)
	{
		return nullptr;
	}

	if (isOld == true)
	{
		strcpy(name, "old.txt");
	}
	else
	{
		strcpy(name, "new.txt");
	}

	return name;
}

FILE* TryToOpenFile(bool isOld)
{
	errno_t err;
	FILE *fileToOpen;
	char* name = (char*)calloc(100, sizeof(char));

	if (name == nullptr)
	{
		return nullptr;
	}

	name = IndicateFileName(isOld);

	if (name == nullptr)
	{
		return nullptr;
	}

	if (isOld == true)
	{
		if ((err = fopen_s(&fileToOpen, name, "r+t")) != 0)
		{
			printf("File didn't open\n");
			fileToOpen = nullptr;
		}
	}
	else
	{
		if ((err = fopen_s(&fileToOpen, name, "wt")) != 0)
		{
			printf("File didn't open\n");
			fileToOpen = nullptr;
		}
	}

	fseek(fileToOpen, 0, SEEK_SET);

	return fileToOpen;
}

InformationStack RestoreTreeFromFile(FILE* infoFile)
{
	InformationStack line = CreateStack();
	TreeKnot* newNode = nullptr;
	TreeKnot* root = newNode;

	char *symbol = (char*)calloc(200, sizeof(char));
	char *buffer = (char*)calloc(200, sizeof(char));

	int tempCurrentNumber = 0, tempLeftNumber = 0, tempRightNumber = 0;

	fseek(infoFile, 0, SEEK_END);
	long pos = ftell(infoFile);

	if (pos <= 2)
	{
		line.head = nullptr;
		line.tail = nullptr;
		return line;
	}

	fseek(infoFile, 0, SEEK_SET);

	while (!feof(infoFile))
	{
		fscanf(infoFile, "%[, . | \n ! \t]", buffer);

		if (feof(infoFile)) break;

		fscanf(infoFile, "%[0-9]", symbol);
		tempCurrentNumber = atoi(symbol);

		fseek(infoFile, 1, SEEK_CUR);

		if (fscanf(infoFile, "%[0-9]", symbol))
		{
			tempLeftNumber = atoi(symbol);
		}
		else
		{
			fseek(infoFile, 1, SEEK_CUR);
			tempLeftNumber = 0;
		}

		fseek(infoFile, 1, SEEK_CUR);

		if (fscanf(infoFile, "%[0-9]", symbol))
		{
			tempRightNumber = atoi(symbol);
		}
		else
		{
			fseek(infoFile, 1, SEEK_CUR);
			tempRightNumber = 0;
		}

		fseek(infoFile, 1, SEEK_CUR);
		fgets(symbol, 2, infoFile);

		if (!strcmp(symbol, "-"))
		{
			fgets(buffer, 200, infoFile);
			int size = strlen(buffer) - 2;
			buffer[size + 1] = '\0';
		}
		else
		{
			fseek(infoFile, -1, SEEK_CUR);
			fgets(buffer, 200, infoFile);
			int size = strlen(buffer) - 2;
			buffer[size] = '\0';
		}

		AddElementToTree(line, buffer, tempCurrentNumber, tempLeftNumber, tempRightNumber);
	}
	return line;
}

TreeKnot** ShowMenuOfTreeCreation(FILE* infoFile)
{
	if (infoFile == nullptr)
		return nullptr;

	TreeKnot* tree = nullptr;
	int num;
	bool flag = false;

	puts("Do You want to create basic tree of answers or restore existing?");
	puts("For create basic tree, input one (1)");
	puts("For restore existing tree, input two (2)");
	puts("For exit, input zero (0)");

	do
	{
		rewind(stdin);

		if (flag)
		{
			puts("Incorrect input");
		}

		flag = true;
	} while (!scanf("%d", &num) || (num < 0 || num > 2));

	if (!num)
	{
		return &tree;
	}
	else
	{
		switch (num)
		{
		case 1:
			tree = CreateMinimalTree();
			break;
		case 2:
			if (infoFile == nullptr) return nullptr;

			InformationStack line = RestoreTreeFromFile(infoFile);

			if (line.head == nullptr && line.tail == nullptr)
			{
				puts("That's no data, creating a new tree of answers..");
				system("pause");
				tree = CreateMinimalTree();
			}
			else
			{
				FillingTreeWithInformation(&tree, line.head, line);
			}
			break;
		default:
			break;
		}
	}
	return &tree;
}

void GenerateKeyForStorage(FILE* infoFile, TreeKnot* currentKnot, bool isLeaf)
{
	char *buffer = (char*)calloc(200, sizeof(char));
	_itoa(currentKnot->num, buffer, 10);

	fputs(buffer, infoFile);
	fputc(':', infoFile);

	if (currentKnot->left)
	{
		_itoa(currentKnot->left->num, buffer, 10);
		fputs(buffer, infoFile);
	}
	else fputc('-', infoFile);

	fputc(',', infoFile);

	if (currentKnot->right)
	{
		_itoa(currentKnot->right->num, buffer, 10);
		fputs(buffer, infoFile);
	}
	else fputc('-', infoFile);

	fputc(' ', infoFile);

	if (!isLeaf)
	{
		fputs(currentKnot->question, infoFile);
	}

	fputc('-', infoFile);

	if (isLeaf)
	{
		fputs(currentKnot->name, infoFile);
	}

	fputc('\n', infoFile);
}

void TreeTraversalForKeyGeneration(FILE* infoFile, TreeKnot* currentKnot)
{
	if (currentKnot != nullptr)
	{
		currentKnot->name == nullptr ? GenerateKeyForStorage(infoFile, currentKnot, false) : GenerateKeyForStorage(infoFile, currentKnot, true);
		TreeTraversalForKeyGeneration(infoFile, currentKnot->left);
		TreeTraversalForKeyGeneration(infoFile, currentKnot->right);
	}
}