#pragma once
#include <string>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

// Recipe 정보 반환
class Recipe {
private:
	// 멤버 변수

	// 레시피 이름
	string name="NULL";
	// 레시피 설명
	string description;
	// 레시피 재료: 재료의 집합
	set<string> ingredients;
	// 레시피를 요리하는 데 걸리는 시간
	int time;
	// 재료 표시를 위한 카운트
	int ct = 0;

public:
	// 메소드

	// 생성자(Recipe 초기내용 설정) : name(str), description(str), time(int), ingredients(Vector)
	Recipe() {}
	Recipe(string& n, string& d, int t, vector<string> i) :
		name(n), description(d), time(t), ingredients() {
		for (string s : i)
			ingredients.insert(s);
	};

	// 레시피 이름, 과정, 재료, 시간 받아오기
	const string& getName() const { return name; }
	const string& getDescription() const { return description; }
	const set<string>& getIngredients() const { return ingredients; }
	int getTime() const { return time; }

	// 레시피 이름, 과정, 시간 설정
	void setName(string& n) { name = n; }
	void setDescription(string& d) { description = d; }
	void setTime(int t) { time = t; }

	// 함수
	// 레시피 재료를 재료 세트에 삽입하고 저장값을 반환
	bool addIngredient(string& n) { return ingredients.insert(n).second; }
	// 레시피 재료를 재료 세트에서 제거하고 저장값을 반환
	bool removeIngredient(string& n) { return ingredients.erase(n) == 1; }
	// 재료를 찾는다.
	bool searchIngredient(string& n) { return ingredients.find(n) != ingredients.end(); }

	// 레시피 출력
	void print() {
		cout << " >> Recipe Name : " << name << endl;
		cout << " >> Ingredients : " << endl;
		for (string s : ingredients)
			cout << "  " << ++ct << ". " << s << endl;
		cout << " >> Time : " << time << "min" << endl;
		cout << " >> Direction" << endl << "  -> " << description << endl;
		cout << "---------------------" << endl;

	}
};

bool compareRecipe(Recipe a, Recipe b) {
	return a.getName() <= b.getName();
}


// 레시피 DataBase 
class RecipeDB {
private:
	vector<Recipe> Recipes;

public:
	RecipeDB() {};

	//레시피 추가
	void addRecipe(Recipe r) {
		for (Recipe s : Recipes) {
			if (s.getName() == r.getName()) {
				cout << "Already exist" << endl;
				return;
			}
		}
		Recipes.push_back(r);
	}

	//레시피 삭제
	void deleteRecipe(string& s) {
		for (int i = 0; i < Recipes.size(); i++) {
			if (s == Recipes[i].getName()) {
				Recipes.erase(Recipes.begin() + i);
				cout << "Delete Success" << endl;
				return;
			}
		}
		cout << "NO exist" << endl;
	}

	//레시피 반환
	Recipe getRecipe(string& s) {
		for (Recipe r : Recipes) {
			if (s == r.getName()) {
				return r;
			}
		}
		Recipe n = Recipe();
		return n;
	}

	vector<Recipe> getRecipes() { return Recipes; }

	//레시피 검색
	void searchRecipe(string& s) {
		bool count = false;
		for (Recipe r : Recipes) {
			string data = r.getName();
			set<string> inge = r.getIngredients();
			if (data.find(s) != string::npos) {
				r.print();
				count = true;
			}
			else{
				for (string ing : r.getIngredients()) {
					if (ing.find(s) != string::npos) {
						r.print();
						count = true;
						break;
					}
				}
			}
		}
		if (!count) {
			cout << "NO RESULT" << endl;
		}
	}

	//레시피 출력
	void printRecipe(string& s) {
		for (Recipe r : Recipes) {
			if (s == r.getName()) {
				r.print();
				return;
			}
		}
		cout << "No exist" << endl;
	}

	//레시피 전체 출력
	void printAll() {
		for (Recipe r : Recipes) {
			r.print();
		}
	}

	void sortRecipe() {
		sort(Recipes.begin(), Recipes.end(), compareRecipe);
	}

};