#pragma once

struct InformationStackElement
{
	char *info;
	int currentNumber;
	int leftNumber;
	int rightNumber;

	InformationStackElement *next;
	InformationStackElement *prev;
};