#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "Plan.h"
#include "FileIO.h"


using namespace std;

class Greeter {

	RecipeDB recipedb;
	PlanDB plandb;
	Calender calender;
	
public:
	
	Greeter(RecipeDB r, PlanDB p, Calender c) { recipedb = r; plandb = p; calender = c; }
	void printOption();
	void selectOption();

	// 1. ������ �˻�
	void searchRecipe() {
		recipedb.sortRecipe();

		string name;
		cout << "Enter Recipe Name or Ingredient to Search: ";
		cin.ignore();
		getline(cin, name);
		cout << "-------Result-------" << endl;
		recipedb.searchRecipe(name);

	}

	// 2. ������ �߰�
	void addRecipe() {

		string name, description;
		vector<string> ingredients;
		string time;
		int timeI;

		cout << "Enter Recipe Name: ";
		cin.ignore();
		getline(cin, name);

		cout << "Enter Ingredients (enter a blank line to finish)\n";
		string ingredient;
		while (true) {
			cout << "Ingredient: ";
			getline(cin, ingredient);

			if (ingredient.empty()) {
				break;
			}

			ingredients.push_back(ingredient);
		}

		while (1) {
			cout << "Enter Recipe Cooking Time (in minutes): ";
			cin >> time;
			if (all_of(time.begin(), time.end(), isdigit)) {
				timeI = stoi(time);
				break;
			}
			else {
				cout << "Not Integer" << endl;
			}
		}

		cin.ignore();

		cout << "Enter Recipe Description: ";
		getline(cin, description);

		Recipe recipe(name, description, timeI, ingredients);
		recipedb.addRecipe(recipe);
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
		recipedb.sortRecipe();
	}
	
	// 3. ������ ����
	void deleteRecipe() {
		string name;
		cout << "-----Recipe List-----" << endl;
		for (Recipe r : recipedb.getRecipes()) {
			cout << r.getName() << endl;
		}
		cout << endl;

		cout << "Enter Recipe Name to Delete: ";
		cin.ignore();
		getline(cin, name);

		recipedb.deleteRecipe(name);
	
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
	
	};

	// 4. ������ ��ü ��ȸ
	void showRecipe() {
		recipedb.sortRecipe();

		cout << "All Recipes:\n";
		recipedb.printAll();
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
	}

	// 5. �÷� �˻�
	void searchPlan() {
		plandb.sortPlan();

		string name;

		cout << "Enter Plan Name to Search: ";
		cin.ignore();
		getline(cin, name);
		cout << "-------Result-------" << endl;
		plandb.searchPlan(name);

	};
	

	// 6. �÷� �߰�
	void addPlan() {

		string name;
		Meal breakfast, lunch, dinner;

		cout << "Enter Plan Name: ";
		cin.ignore();
		getline(cin, name);

		cout << "-----Recipe List-----" << endl;
		for (Recipe r : recipedb.getRecipes()) {
			cout << r.getName() << endl;
		}
		cout << endl;


		cout << "Enter Recipe name for Breakfast (enter a blank line to finish)\n";
		string recipe;
		while (true) {
			cout << "Recipe Name:";
			getline(cin, recipe);

			if (recipe.empty()) {
				break;
			}
			Recipe data = recipedb.getRecipe(recipe);
			if (data.getName() != "NULL") {
				breakfast.addRecipes(data);
			}
			else {
				cout << "Not Exist Recipe" << endl;
			}
			plandb.sortPlan();
		}

		cout << "Enter Recipe name for Lunch (enter a blank line to finish)\n";
		while (true) {
			cout << "Recipe Name:";
			getline(cin, recipe);

			if (recipe.empty()) {
				break;
			}
			Recipe data = recipedb.getRecipe(recipe);
			if (data.getName() != "NULL") {
				lunch.addRecipes(data);
			}
			else {
				cout << "Not Exist Recipe" << endl;
			}
		}

		cout << "Enter Recipe name for Dinner (enter a blank line to finish)\n";
		while (true) {
			cout << "Recipe Name:";
			getline(cin, recipe);

			if (recipe.empty()) {
				break;
			}
			Recipe data = recipedb.getRecipe(recipe);
			if (data.getName() != "NULL") {
				dinner.addRecipes(data);
			}
			else {
				cout << "Not Exist Recipe" << endl;
			}
		}

		Plan plan(name, breakfast, lunch, dinner);
		plandb.addPlan(plan);
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();

	};

	// 7. �÷� ����
	void deletePlan() {
		string name;

		cout << "-----Plan List-----" << endl;
		for (Plan p : plandb.getPlans()) {
			cout << p.getName() << endl;
		}
		cout << endl;

		cout << "Enter Plan Name to Delete: ";
		cin.ignore();
		getline(cin, name);

		plandb.deletePlan(name);

		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();

	};

	// 8. Plan ��ü ��ȸ
	void showPlan() {
		plandb.sortPlan();

		cout << "All Plans:\n";
		plandb.printAll();
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
	};
	

	// 9. Date �˻�
	void searchDate() {
		calender.sortDate();

		vector<string> date;
		string token;
		istringstream iss;

		cout << "Enter Date to Search (yyyy-mm-dd or yyyy-mm or yyyy) : ";
		cin.ignore();
		getline(cin, token);
		iss.str(token);

		while (getline(iss, token, '-')) {
			date.push_back(token);
		}

		for (int i = 0; i < date.size(); i++) {
			if (!all_of(date[i].begin(), date[i].end(), isdigit)) {
				cout << "Wrong Input" << endl;
				return;
			}
		}


		if (date.size() == 1) {
			cout << "-------Result-------" << endl;
			calender.printDate(stoi(date[0]));
		}
		else if (date.size() == 2) {
			cout << "-------Result-------" << endl;
			calender.printDate(stoi(date[0]),stoi(date[1]));
		}
		else if (date.size() == 3) {
			cout << "-------Result-------" << endl;
			calender.printDate(stoi(date[0]),stoi(date[1]),stoi(date[2]));
		}
		else {
			cout << "Wrong Input" << endl;
		}
		
	}

	// 10. Date �߰�
	void addDate() {
		string planname;
		vector<string> date;
		string token;
		istringstream iss;

		cout << "Enter Date (yyyy-mm-dd) to add : ";
		
		cin.ignore();

		getline(cin, token);
		iss.str(token);

		while (getline(iss, token, '-')) {
			date.push_back(token);
		}

		if (date.size() != 3) {
			cout << "Wrong Input" << endl;
			// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
			return;
		}

		for (int i = 0; i < date.size(); i++) {
			if (!all_of(date[i].begin(), date[i].end(), isdigit)) {
				cout << "Wrong Input" << endl;
				// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
				return;
			}
		}

		int y = stoi(date[0]);
		int m = stoi(date[1]);
		int d = stoi(date[2]);

		cout << "-----Plan List-----" << endl;
		for (Plan p : plandb.getPlans()) {
			cout << p.getName() << endl;
		}
		cout << endl;

		cout << "Enter Plan name:\n";
		getline(cin, planname);
		
		Plan p = plandb.getPlan(planname);
		if (p.getName() != "NULL") {
			Date dd(y, m, d, plandb.getPlan(planname));
			calender.addDate(dd);
			calender.sortDate();
			// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
		}
		calender.sortDate();
	}

	// 11. Date ����
	void deleteDate() {
		vector<string> date;
		string token;
		istringstream iss;

		cout << "-----Date List-----" << endl;
		for (Date d : calender.getCalender()) {
			cout << d.getYear() << "-" << d.getMonth() << "-" << d.getDay() << endl;
		}
		cout << endl;

		cout << "Enter Date (yyyy-mm-dd) to add : ";
		
		cin.ignore();
		getline(cin, token);
		iss.str(token);

		while (getline(iss, token, '-')) {
			date.push_back(token);
		}

		if (date.size() != 3) {
			cout << "Wrong Input" << endl;
			// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
			return;
		}

		for (int i = 0; i < date.size(); i++) {
			if (!all_of(date[i].begin(), date[i].end(), isdigit)) {
				cout << "Wrong Input" << endl;
				// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
				return;
			}
		}

		int y = stoi(date[0]);
		int m = stoi(date[1]);
		int d = stoi(date[2]);

		calender.deleteDate(y, m, d);
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
	}

	// 12. �޷� ��ȸ
	void showCalender() {
		cout << "All Dates:\n";
		calender.sortDate();
		calender.printAll();
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
	};
};

void Greeter::printOption() {

	cout << "                         -------------------------------------------\n";
	cout << "                        ��  ######   ######    ##  ###   ###  ###  ��\n";
	cout << "                        ��    ##       ##      ## ##      ##  ##   ��\n";
	cout << "                        ��    ##       ##      ###        ######   ��\n";
	cout << "                        ��    ##       ##      ## ##      ##  ##   ��\n";
	cout << "                        ��  ######   ######    ##  ###   ###  ###  ��\n";
	cout << "                         -------------------------------------------\n";
	cout << endl;
	cout << "        --------------------------------------------------------------------------\n";
	cout << "             1.Search recipe                           9.Search Date\n";
	cout << "             2.Add recipe                              10.Add Date\n";
	cout << "             3.Delete recipe                           11.Delete Date\n";
	cout << "             4.Show all recipe                         12.Show Calender\n";
	cout << "             5.Search plan                             13.Save\n";
	cout << "             6.Add plan                                14.Load\n";
	cout << "             7.Delete plan                             15.Exit Without Saving\n";
	cout << "             8.Show all plan                           16.Save & Exit\n";   
	cout << "        --------------------------------------------------------------------------\n";
	cout << endl;
	cout << "        Enter Number:";

}

void Greeter::selectOption() {

	string selectedOption;
	cin >> selectedOption;
	int select;

	if (all_of(selectedOption.begin(), selectedOption.end(), isdigit)) {
		select = stoi(selectedOption);
	}
	else {
		select = -1;
	}

	system("CLS");
	switch (select) {
	case 1: {
		cout << " Search recipe " << endl;
		searchRecipe();
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
		break;
	}
	case 2:
	{
		cout << " Add recipe" << endl;
		addRecipe();
		break;
	}
	case 3:
	{
		cout << " Delete recipe" << endl;
		deleteRecipe();
		break;

	}
	case 4: {
		showRecipe();
		break;
	}
	case 5: {
		cout << " Search Plan" << endl;
		searchPlan();
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
		break;
	}
	case 6: {
		cout << " Add Plan" << endl;
		addPlan();
		break;
	}
	case 7:
	{
		cout << " Delete Plan" << endl;
		deletePlan();
		break;
	}
	case 8: {
		showPlan();
		break;
	}
	case 9: { //search Date
		cout << " Search Date" << endl;
		searchDate();
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
		break;
	}
	case 10: { //add Date
		cout << " Add Date" << endl;
		addDate();
		break;
	}
	case 11: { // delete Date
		cout << " Delete Date" << endl;
		deleteDate();
		break;
	}
	case 12: { // Show Calender
		showCalender();
		break;
	}
	case 13: { // Save
		FileIO fileio = FileIO();
		fileio.saveRecipe(recipedb);
		fileio.savePlan(plandb);
		fileio.saveCalender(calender);
		break;
	}
	case 14: { // Load
		FileIO fileio = FileIO();
		fileio.loadRecipe(recipedb);
		fileio.loadPlan(plandb);
		fileio.loadCalender(calender);
		break;
	}
	case 15: {
		cout << "Exit the program without saving changes\n";
		exit(0);
	}

	case 16:
	{
		FileIO fileio = FileIO();
		fileio.saveRecipe(recipedb);
		fileio.savePlan(plandb);
		fileio.saveCalender(calender);
		cout << "Save changes and Exit the program.\n";
		exit(0);
		break;
	}
	default: 
	{
		cout << "Entered it incorrectly. Enter a number between 1 and 16.\n";
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
	}

	}
}
