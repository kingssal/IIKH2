#include <iostream>
#include <fstream>
#include <string>

#include "Greeter.h"
#include "FileIO.h"

using namespace std;


int main() { //File���� ������ �ҷ��� DB�� �������� Greeter��ü�� �����Ͽ� ���α׷� ����
	FileIO fileio = FileIO();

	RecipeDB recipedb;
	fileio.loadRecipe(recipedb);
	PlanDB plandb;
	fileio.loadPlan(plandb);
	Calender calender;
	fileio.loadCalender(calender);
	Greeter greeter(recipedb,plandb,calender);


	while (1) {
		system("cls");
		greeter.printOption();
		greeter.selectOption();
	}

}