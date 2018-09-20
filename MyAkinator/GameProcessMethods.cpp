#define _CRT_SECURE_NO_WARNINGS

#include "GameProcessMethods.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>


TreeKnot* CreateMinimalTree()
{
	TreeKnot* newNodeOfTree = (TreeKnot*)malloc(sizeof(TreeKnot));

	if (newNodeOfTree == nullptr) return nullptr;

	newNodeOfTree->left = newNodeOfTree->right = nullptr;
	newNodeOfTree->name = nullptr;

	newNodeOfTree->question = (char*)calloc(200, sizeof(char));
	strcpy(newNodeOfTree->question, "Is your character a person?");

	TreeKnot* temp = newNodeOfTree->left;
	temp = (TreeKnot*)malloc(sizeof(TreeKnot));

	newNodeOfTree->left = temp;
	temp->left = temp->right = nullptr;

	temp->question = (char*)calloc(200, sizeof(char));
	strcpy(temp->question, "Is this the correct answer?");

	temp->name = (char*)calloc(200, sizeof(char));
	strcpy(temp->name, "Batman");

	temp = newNodeOfTree->right;

	temp = (TreeKnot*)malloc(sizeof(TreeKnot));
	newNodeOfTree->right = temp;
	temp->left = temp->right = nullptr;

	temp->question = (char*)calloc(200, sizeof(char));
	strcpy(temp->question, "Is this the correct answer?");

	temp->name = (char*)calloc(200, sizeof(char));
	strcpy(temp->name, "Yoda");

	return newNodeOfTree;
}

InformationStack CreateStack()
{
	InformationStack result;
	result.head = result.tail = nullptr;
	return result;
}

void AddElementToTree(InformationStack &currentStackElement, char* info, int currentNumber, int leftNumber, int rightNumber)
{
	InformationStackElement *elem = (InformationStackElement*)malloc(sizeof(InformationStackElement));
	
	if (elem == nullptr) return;

	elem->info = (char*)calloc(200, sizeof(char));

	if (currentStackElement.head == nullptr)
	{
		currentStackElement.head = currentStackElement.tail = elem;
		currentStackElement.head->next = currentStackElement.head->prev = nullptr;
		elem->next = elem->prev = nullptr;

		strcpy(elem->info, info);

		elem->currentNumber = currentNumber;
		elem->leftNumber = leftNumber;
		elem->rightNumber = rightNumber;
	}
	else
	{
		currentStackElement.tail->next = elem;
		elem->prev = currentStackElement.tail;
		elem->next = nullptr;
		currentStackElement.tail = elem;

		strcpy(elem->info, info);

		elem->currentNumber = currentNumber;
		elem->leftNumber = leftNumber;
		elem->rightNumber = rightNumber;
	}
}

void DeleteTreeNode(InformationStack &currentStackElement, InformationStackElement* element)
{
	if (element == currentStackElement.head && element == currentStackElement.tail)
	{
		currentStackElement.head = currentStackElement.tail = nullptr;
		free(element->info);
		free(element);
		return;
	}

	if (element == currentStackElement.head)
	{
		currentStackElement.head = currentStackElement.head->next;
		currentStackElement.head->prev = nullptr;
		element->prev = element->next = nullptr;
		free(element->info);
		free(element);
	}
	else if (element == currentStackElement.tail)
	{
		currentStackElement.tail = currentStackElement.tail->prev;
		currentStackElement.tail->next = nullptr;
		element->prev = element->next = nullptr;
		free(element->info);
		free(element);
	}
	else
	{
		element->next->prev = element->prev;
		element->prev->next = element->next;
		free(element->info);
		free(element);
	}
}

void FillingTreeWithInformation(TreeKnot** rootOfTree, InformationStackElement* element, InformationStack &currentStackElement)
{
	TreeKnot* newKnot = (TreeKnot*)malloc(sizeof(TreeKnot));

	if (newKnot == nullptr) return;

	if (*rootOfTree == nullptr)
	{
		*rootOfTree = newKnot;
	}
	else newKnot = *rootOfTree;

	newKnot->left = newKnot->right = nullptr;

	if (element->info[strlen(element->info) - 1] == '?')
	{
		newKnot->name = nullptr;

		newKnot->question = (char*)calloc(200, sizeof(char));
		strcpy(newKnot->question, element->info);
	}
	else
	{
		newKnot->name = (char*)calloc(200, sizeof(char));
		strcpy(newKnot->name, element->info);

		newKnot->question = (char*)calloc(200, sizeof(char));
		strcpy(newKnot->question, "Is this the correct answer?");
	}

	if (element->leftNumber)
	{
		FillingTreeWithInformation(&newKnot->left, element->next, currentStackElement);
	}

	if (element->rightNumber)
	{
		FillingTreeWithInformation(&newKnot->right, element->next, currentStackElement);
	}

	if (element != nullptr)
	{
		DeleteTreeNode(currentStackElement, element);
	}
}

int AskQuestion(TreeKnot *currentKnot)
{
	int answer = 0;
	bool flag = false;

	puts(currentKnot->question);

	puts("If yes, input 1, if not - 0");

	do
	{
		rewind(stdin);

		if (flag)
		{
			puts("Incorrect input");
		}

		flag = true;
	} while (!scanf("%d", &answer) || (answer < 0 || answer > 1));

	return answer;
}

void TreePassing(TreeKnot* &currentKnot)
{
	if (currentKnot->name != nullptr)
	{
		puts(currentKnot->name);
		TreeKnot *newKnot = AddTreeNodeManually(currentKnot);
		currentKnot = newKnot;
		return;
	}

	int answer = AskQuestion(currentKnot);
	answer == 1 ? TreePassing(currentKnot->left) : TreePassing(currentKnot->right);
}

TreeKnot* &AddTreeNodeManually(TreeKnot* &currentKnot)
{
	int answer = AskQuestion(currentKnot);

	if (answer == 1)
	{
		return currentKnot;
	}

	char *buffer = (char*)calloc(200, sizeof(char));
	char *buf = (char*)calloc(200, sizeof(char));

	TreeKnot* newLeafOfTree = (TreeKnot*)malloc(sizeof(TreeKnot));
	
	if (newLeafOfTree == nullptr)
	{
		return newLeafOfTree;
	}

	newLeafOfTree->name = (char*)calloc(200, sizeof(char));
	newLeafOfTree->question = (char*)calloc(200, sizeof(char));

	TreeKnot* newKnotOfTree = (TreeKnot*)malloc(sizeof(TreeKnot));
	
	if (newKnotOfTree == nullptr)
	{
		return newKnotOfTree;
	}

	newKnotOfTree->name = nullptr;
	newKnotOfTree->question = (char*)calloc(200, sizeof(char));

	puts("What kind of character did you make?");
	rewind(stdin);

	fgets(buffer, 200, stdin);
	strcpy(newLeafOfTree->name, buffer);

	strcpy(newLeafOfTree->question, "Is this the correct answer?");

	puts("What is the difference between your character and the proposed one ? (Example of answer : villain)");
	rewind(stdin);
	fgets(buffer, 200, stdin);

	strcpy(newKnotOfTree->question, "Your character ");
	strncpy(buf, buffer, strlen(buffer) - 1);
	strcat(buf, "?");
	strcat(newKnotOfTree->question, buf);

	newKnotOfTree->right = currentKnot;
	newKnotOfTree->left = newLeafOfTree;
	newLeafOfTree->left = newLeafOfTree->right = nullptr;

	puts("You beat me!!!");
	system("pause");
	return newKnotOfTree;
}

void NumerateTree(TreeKnot* &currentKnot)
{
	static int num = 1;

	if (currentKnot != nullptr)
	{
		currentKnot->num = num++;
		NumerateTree(currentKnot->left);
		NumerateTree(currentKnot->right);
	}
}

void GameProcess(TreeKnot* currentKnot)
{
	int answer = 2;

	do
	{
		system("cls");
		bool flag = false;

		puts("Hi, I'm great compiler, I know any characters and can guess whem, wanna play?");
		puts("If yes, input 1, if not - 0");

		do
		{
			rewind(stdin);

			if (flag)
			{
				puts("Incorrect input");
			}

			flag = true;

		} while (!scanf("%d", &answer) || (answer < 0 || answer > 1));

		switch (answer)
		{
		case 1:
			TreePassing(currentKnot);
			break;
		default:
			break;
		}

	} while (answer);
}