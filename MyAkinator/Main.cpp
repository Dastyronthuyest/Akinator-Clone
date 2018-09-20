#include <conio.h>
#include <string.h>
#include <iostream>
#include "GameProcessMethods.h"
#include "FileMethods.h"


int main()
{
	system("cls");

	FILE *treePriviousStory = TryToOpenFile(true);
	FILE *tempTreeStateFile = TryToOpenFile(false);
	
	TreeKnot* tree = *ShowMenuOfTreeCreation(treePriviousStory);
	
	if (tree == nullptr)
	{
		puts("Tree didn't formed");
		system("pause");
		return 1;
	}

	GameProcess(tree);

	NumerateTree(tree);

	TreeTraversalForKeyGeneration(tempTreeStateFile, tree);

	system("pause");

	fclose(tempTreeStateFile);
	fclose(treePriviousStory);
	remove("old.txt");
	rename("new.txt", "old.txt");

	return 0;
}
