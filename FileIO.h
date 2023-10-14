#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm> 
#include <fstream>
#include <sstream>

#include "Greeter.h"

using namespace std;

class FileIO { //���� ����¿� ���� ������ �ϴ� Ŭ����
private:

public:
	FileIO() {};

	// Plan ����
	void savePlan(PlanDB pdb) {
		vector<Plan> plans = pdb.getPlans();
		ofstream ofs;
		ofs.open("plan.txt", ios::out);
		if (ofs.fail()) {
			cerr << "Error!" << endl;
			return;
		}
		vector<Recipe> recipes;
		for (Plan p : plans) {
			ofs << p.getName() << "|";
			recipes = p.getBreakfast().getRecipes();
			for (Recipe r : recipes) {
				ofs << r.getName() << ",";
			}
			ofs << "|";
			recipes = p.getLunch().getRecipes();
			for (Recipe r : recipes) {
				ofs << r.getName() << ",";
			}
			ofs << "|";
			recipes = p.getDinner().getRecipes();
			for (Recipe r : recipes) {
				ofs << r.getName() << ",";
			}
			ofs << endl;
		}
		ofs.close();
	}

	//Plan �ҷ�����
	void loadPlan(PlanDB& planDB) {
		PlanDB loadedP;
		ifstream file("plan.txt");
		if (!file.is_open()) {
			cout << "cannot open the file" << endl;
			return;
		}
		string line;
		while (getline(file, line)) {
			if (!line.empty()) {
				istringstream iss(line);
				string token;
				vector<string> Field;
				RecipeDB recipedb;
				loadRecipe(recipedb);  // plan ��ȯ�� ���� meal�� �Է��ؾ��ϴµ� ���Ͽ��� string �� ������ ������ �ʿ���

				while (getline(iss, token, '|')) {
					Field.push_back(token);
				}

				if (Field.size() >= 4) {
					string name = Field[0];
					Meal breakfast, lunch, dinner;
					string a = "";
					string breakfastRecipeNames = Field[1];  // ��ħ �Ļ翡 �ش��ϴ� ������ �̸����� ��ǥ�� �����Ͽ� ����

					istringstream breakfastRecipeStream(breakfastRecipeNames);
					string breakfastRecipeName;

					// ��ħ �Ļ翡 �ش��ϴ� ������ �̸����� ��ǥ�� �и��Ͽ� ������ ���� Meal breakfast�� �߰�
					while (getline(breakfastRecipeStream, breakfastRecipeName, ',')) {
						// RecipeDB���� �ش� ������ �̸��� ���� Recipe�� �����ɴϴ�.
						Recipe breakfastRecipe = recipedb.getRecipe(breakfastRecipeName);


						// ������ �����Ǹ� ��ħ �Ļ�(Meal breakfast)�� �߰��մϴ�.
						breakfast.addRecipes(breakfastRecipe);
					}
					string lunchRecipeNames = Field[2];
					istringstream lunchRecipeStream(lunchRecipeNames);
					string lunchRecipeName;
					while (getline(lunchRecipeStream, lunchRecipeName, ',')) {
						Recipe lunchRecipe = recipedb.getRecipe(lunchRecipeName);
						lunch.addRecipes(lunchRecipe);
					}

					string dinnerRecipeNames = Field[3];
					istringstream dinnerRecipeStream(dinnerRecipeNames);
					string dinnerRecipeName;
					while (getline(dinnerRecipeStream, dinnerRecipeName, ',')) {
						Recipe dinnerRecipe = recipedb.getRecipe(dinnerRecipeName);
						dinner.addRecipes(dinnerRecipe);
					}

					Plan plan(name, breakfast, lunch, dinner);
					loadedP.addPlan(plan);
				}
			}

		}
		planDB = loadedP;
		file.close();
	}

	// Recipe ����
	void saveRecipe(RecipeDB rdb) {
		vector<Recipe> recipes = rdb.getRecipes();
		ofstream ofs;
		ofs.open("recipe.txt", ios::out);
		if (ofs.fail()) {
			cerr << "Error!" << endl;
			return;
		}
		for (Recipe r : recipes) {
			ofs << r.getName() << "|";
			ofs << r.getDescription() << "|" << r.getTime() << "|";
			for (string s : r.getIngredients()) {
				ofs << s << ",";
			}
			ofs << endl;
		}
		ofs.close();
	}

	//Recipe �ҷ�����
	void loadRecipe(RecipeDB& recipeDB) { // �������: �̸�,������,�ð�,���
		RecipeDB loadedR;
		ifstream inputFile("recipe.txt");  // recipe.txt ������ �б� ���� ���ϴ�.

		if (!inputFile.is_open()) {
			cout << "cannot open recipe.txt " << endl;
			return;
		}

		string line;

		while (getline(inputFile, line)) {
			if (!line.empty()) {
				istringstream iss(line);
				string token;
				vector<string> recipeFields;

				// '|'�� �и��� �ʵ带 �����Ͽ� recipeFields ���Ϳ� �����մϴ�.
				while (getline(iss, token, '|')) {
					recipeFields.push_back(token);
				}

				// �ʵ尡 ����� ��쿡�� �����Ǹ� �����ϰ� RecipeDB�� �߰��մϴ�.
				if (recipeFields.size() >= 4) {
					string name = recipeFields[0];
					string description = recipeFields[1];
					int time = stoi(recipeFields[2]);
					vector<string> ingredients;

					// '|'�� �и��� ��� �ʵ带 ingredients ���Ϳ� �߰��մϴ�.
					istringstream ingredientsStream(recipeFields[3]);
					while (getline(ingredientsStream, token, ',')) {
						ingredients.push_back(token);
					}

					// �����Ǹ� �����ϰ� RecipeDB�� �߰��մϴ�.
					loadedR.addRecipe(Recipe(name, description, time, ingredients));
				}
			}
		}
		recipeDB = loadedR;
		inputFile.close();  // ������ �ݽ��ϴ�.
	}


	// Calander ����
	void saveCalender(Calender cdb) {
		vector<Date> dates = cdb.getCalender();
		ofstream ofs;
		ofs.open("calender.txt", ios::out);
		if (ofs.fail()) {
			cerr << "Error!" << endl;
			return;
		}
		for (Date c : dates) {
			ofs << c.getYear() << "|" << c.getMonth() << "|" << c.getDay() << "|" << c.getPlan().getName() << endl;
		}
		ofs.close();
	}

	//Calender �ҷ�����
	void loadCalender(Calender& calender) {
		Calender loadedC;
		ifstream file("calender.txt");
		if (!file.is_open()) {
			cout << "cannot open the file" << endl;
			return;
		}
		string line;
		while (getline(file, line)) {
			if (!line.empty()) {
				istringstream iss(line);
				string token;
				vector<string> Field;
				PlanDB plandb;
				loadPlan(plandb);
				while (getline(iss, token, '|')) {
					Field.push_back(token);
				}
				if (Field.size() >= 4) {
					string y = Field[0];
					int year = stoi(y);
					string m = Field[1];
					int month = stoi(m);
					string d = Field[2];
					int day = stoi(d);
					string planName = Field[3];
					Plan plan = plandb.getPlan(planName);
					Date date(year, month, day, plan);
					loadedC.addDate(date);
				}

			}

		}
		calender = loadedC;
		file.close();
	}
};
