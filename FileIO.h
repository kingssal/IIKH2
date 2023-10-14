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

class FileIO { //파일 입출력에 관한 동작을 하는 클래스
private:

public:
	FileIO() {};

	// Plan 저장
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

	//Plan 불러오기
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
				loadRecipe(recipedb);  // plan 반환을 위해 meal을 입력해야하는데 파일에선 string 만 나오기 때문에 필요함

				while (getline(iss, token, '|')) {
					Field.push_back(token);
				}

				if (Field.size() >= 4) {
					string name = Field[0];
					Meal breakfast, lunch, dinner;
					string a = "";
					string breakfastRecipeNames = Field[1];  // 아침 식사에 해당하는 레시피 이름들을 쉼표로 구분하여 저장

					istringstream breakfastRecipeStream(breakfastRecipeNames);
					string breakfastRecipeName;

					// 아침 식사에 해당하는 레시피 이름들을 쉼표로 분리하여 각각에 대해 Meal breakfast에 추가
					while (getline(breakfastRecipeStream, breakfastRecipeName, ',')) {
						// RecipeDB에서 해당 레시피 이름을 가진 Recipe를 가져옵니다.
						Recipe breakfastRecipe = recipedb.getRecipe(breakfastRecipeName);


						// 가져온 레시피를 아침 식사(Meal breakfast)에 추가합니다.
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

	// Recipe 저장
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

	//Recipe 불러오기
	void loadRecipe(RecipeDB& recipeDB) { // 저장순서: 이름,조리법,시간,재료
		RecipeDB loadedR;
		ifstream inputFile("recipe.txt");  // recipe.txt 파일을 읽기 모드로 엽니다.

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

				// '|'로 분리된 필드를 추출하여 recipeFields 벡터에 저장합니다.
				while (getline(iss, token, '|')) {
					recipeFields.push_back(token);
				}

				// 필드가 충분한 경우에만 레시피를 생성하고 RecipeDB에 추가합니다.
				if (recipeFields.size() >= 4) {
					string name = recipeFields[0];
					string description = recipeFields[1];
					int time = stoi(recipeFields[2]);
					vector<string> ingredients;

					// '|'로 분리된 재료 필드를 ingredients 벡터에 추가합니다.
					istringstream ingredientsStream(recipeFields[3]);
					while (getline(ingredientsStream, token, ',')) {
						ingredients.push_back(token);
					}

					// 레시피를 생성하고 RecipeDB에 추가합니다.
					loadedR.addRecipe(Recipe(name, description, time, ingredients));
				}
			}
		}
		recipeDB = loadedR;
		inputFile.close();  // 파일을 닫습니다.
	}


	// Calander 저장
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

	//Calender 불러오기
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
