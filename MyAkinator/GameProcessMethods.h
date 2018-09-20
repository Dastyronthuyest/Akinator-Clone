#pragma once
#include <stdio.h>
#include "TreeKnot.h"
#include "InformationStackElement.h"
#include "InformationStack.h"


TreeKnot* CreateMinimalTree();

InformationStack CreateStack();

void AddElementToTree(InformationStack&, char*, int, int, int);

void DeleteTreeNode(InformationStack&, InformationStackElement*);

void FillingTreeWithInformation(TreeKnot**, InformationStackElement*, InformationStack&);

int AskQuestion(TreeKnot*);

void TreePassing(TreeKnot*&);

TreeKnot* &AddTreeNodeManually(TreeKnot*&);

void NumerateTree(TreeKnot*&);

void GameProcess(TreeKnot*);