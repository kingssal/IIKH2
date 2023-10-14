#include <iostream>
#include <fstream>
#include <string>

#include "Greeter.h"
#include "FileIO.h"

using namespace std;


int main() { //File에서 정보를 불러와 DB에 저장한후 Greeter객체를 생성하여 프로그램 시작
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