#pragma once
#include <string>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

// Recipe ���� ��ȯ
class Recipe {
private:
	// ��� ����

	// ������ �̸�
	string name="NULL";
	// ������ ����
	string description;
	// ������ ���: ����� ����
	set<string> ingredients;
	// �����Ǹ� �丮�ϴ� �� �ɸ��� �ð�
	int time;
	// ��� ǥ�ø� ���� ī��Ʈ
	int ct = 0;

public:
	// �޼ҵ�

	// ������(Recipe �ʱ⳻�� ����) : name(str), description(str), time(int), ingredients(Vector)
	Recipe() {}
	Recipe(string& n, string& d, int t, vector<string> i) :
		name(n), description(d), time(t), ingredients() {
		for (string s : i)
			ingredients.insert(s);
	};

	// ������ �̸�, ����, ���, �ð� �޾ƿ���
	const string& getName() const { return name; }
	const string& getDescription() const { return description; }
	const set<string>& getIngredients() const { return ingredients; }
	int getTime() const { return time; }

	// ������ �̸�, ����, �ð� ����
	void setName(string& n) { name = n; }
	void setDescription(string& d) { description = d; }
	void setTime(int t) { time = t; }

	// �Լ�
	// ������ ��Ḧ ��� ��Ʈ�� �����ϰ� ���尪�� ��ȯ
	bool addIngredient(string& n) { return ingredients.insert(n).second; }
	// ������ ��Ḧ ��� ��Ʈ���� �����ϰ� ���尪�� ��ȯ
	bool removeIngredient(string& n) { return ingredients.erase(n) == 1; }
	// ��Ḧ ã�´�.
	bool searchIngredient(string& n) { return ingredients.find(n) != ingredients.end(); }

	// ������ ���
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


// ������ DataBase 
class RecipeDB {
private:
	vector<Recipe> Recipes;

public:
	RecipeDB() {};

	//������ �߰�
	void addRecipe(Recipe r) {
		for (Recipe s : Recipes) {
			if (s.getName() == r.getName()) {
				cout << "Already exist" << endl;
				return;
			}
		}
		Recipes.push_back(r);
	}

	//������ ����
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

	//������ ��ȯ
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

	//������ �˻�
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

	//������ ���
	void printRecipe(string& s) {
		for (Recipe r : Recipes) {
			if (s == r.getName()) {
				r.print();
				return;
			}
		}
		cout << "No exist" << endl;
	}

	//������ ��ü ���
	void printAll() {
		for (Recipe r : Recipes) {
			r.print();
		}
	}

	void sortRecipe() {
		sort(Recipes.begin(), Recipes.end(), compareRecipe);
	}

};