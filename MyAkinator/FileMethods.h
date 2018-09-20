#pragma once
#include <stdio.h>
#include "InformationStack.h"
#include "TreeKnot.h"


char* IndicateFileName(bool);

FILE* TryToOpenFile(bool);

InformationStack RestoreTreeFromFile(FILE*);

TreeKnot** ShowMenuOfTreeCreation(FILE*);

void GenerateKeyForStorage(FILE*, TreeKnot*, bool);

void TreeTraversalForKeyGeneration(FILE*, TreeKnot*);