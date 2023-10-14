#pragma once
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

#include "Recipe.h"

using namespace std;


//recipe�� ����Ŭ����
class Meal { 
private:
	vector<Recipe> recipes; //Meal�� ���Ե� recipe���� �����ϴ� set

public:
	Meal() {}
	// recipe���� ����� set ��ȯ
	vector<Recipe> getRecipes() { return recipes; } 
	// recipes�� ���ο� Recipe �߰� { �ʿ�����: �߰��� Recipe��ü }
	void addRecipes(Recipe data) { recipes.push_back(data); } 
	// target Recipe ���� { �ʿ�����: ������ Recipe��ü }
	void deleteRecipes(Recipe target) {
		for (int i = 0; i < recipes.size(); i++) {
			if (recipes[i].getName() == target.getName()) {
				recipes.erase(recipes.begin() + i);
			}
		}
	}
	// ��� Recipe ���
	void print() {
		cout << endl;
		for (Recipe recipe : recipes) {
			cout << "-" << recipe.getName() << endl;
		}
		cout << endl;
	}
};


//Meal�� ��ħ, ����, �������� ������ �����ϴ� Ŭ����
class Plan {
private:
	Meal breakfast, lunch, dinner;  //��ħ,����,���� Meal
	string name = "NULL"; // Plan �̸�

public:
	//Plan�ʱ⳻�� �����ϴ� Constructor { �ʿ�����: Plan�̸� String, Meal�� 3�� ����� Vector }
	Plan() {}
	Plan(string n, Meal a, Meal b, Meal c) {
		name = n;
		breakfast = a;
		lunch = b;
		dinner = c;
	}
	// Plan �̸� ��ȯ
	string getName() { return name; }
	//��ħ,����,���� ��ȯ
	Meal getBreakfast() { return breakfast; }
	Meal getLunch() { return lunch; }
	Meal getDinner() { return dinner; }

	//Plan �̸� ����
	void setName(string d) { name = d; }
	//��ħ,����,���� ���� { �ʿ�����: Meal ��ü }
	void setBreakfast(Meal data) { breakfast = data; }
	void setLunch(Meal data) { lunch = data; }
	void setDinner(Meal data) { dinner = data; }

	//Plan ���
	void print() {
		cout << endl;
		cout << "Plan name: " << name << endl;
		cout << "-----Breakfast-----";
		breakfast.print();
		cout << "-------Lunch-------";
		lunch.print();
		cout << "-------Dinner------";
		dinner.print();
	}
};

bool comparePlan(Plan a, Plan b) {
	return a.getName() <= b.getName();
}


//Plan���� �����ϴ� DB Ŭ����
class PlanDB {
private:
	vector<Plan> plans;

public:
	//Plan�߰� Plan �̸��� ���ų� ���� �̸��� ������ �ȳ��� ���
	void addPlan(Plan d) { 
		if (d.getName() != "NULL") {
			for (Plan p : plans) {
				if (p.getName() == d.getName()) {
					cout << endl;
					cout << "There is already same Plan";
					return;
				}
			}
			plans.push_back(d);
			return;
		}
		cout << endl;
		cout << "That Plan does not have name";
	}
	//Plan���� ������ �ȳ��� ���
	void deletePlan(string s) {
		for (int i = 0; i < plans.size(); i++) {
			if (plans[i].getName() == s) {
				plans.erase(plans.begin()+i);
				cout << "Delete Success" << endl;
				return;
			}
		}
		cout << endl;
		cout << "Not Exist Plan";
	}
	//���� Plan ��� { �ʿ�����: Plan �̸� }
	void printPlan(string data) {
		for (Plan p : plans) {
			if (data == p.getName()) {
				p.print();
			}
		}
	}

	//Plan ��ȯ ( Plan �̸� �ʿ� )
	Plan getPlan(string data) {
		for (Plan p : plans) {
			if (data == p.getName()) {
				return p;
			}
		}
		Plan p = Plan();
		return p;

	}

	vector<Plan> getPlans() { return plans; }

	void searchPlan(string& s) {
		bool count = false;
		for (Plan p : plans) {
			string data = p.getName();
			if (data.find(s) != string::npos) {
				p.print();
				cout << "---------------------" << endl;
				count = true;
			}
		}
		if (!count) {
			cout << "NO RESULT" << endl;
		}
	}

	void sortPlan() {
		sort(plans.begin(), plans.end(), comparePlan);
	}

	//��ü Plan ���
	void printAll() {
		for (Plan p : plans) {
			p.print();
			cout << "---------------------";
			cout << endl;
		}
	}
};

//��¥�� Plan�� ������ class
class Date {
private:
	int year, month, day;
	Plan plan;
public:
	Date(){
		year = 0;
		month = 0;
		day = 0;
	}
	Date(int y, int m, int d, Plan p) { year = y; month = m; day = d; plan = p; }
	//��,��,��, ��ü��¥ ����
	void setYear(int data) { year = data; }
	void setMonth(int data) { month = data; }
	void setDay(int data) { day = data; }
	void setDate(int y, int m, int d) { year = y; month = m; day = d; }
	//��,��,�� ��ü��¥ ��ȯ
	int getYear() { return year; }
	int getMonth() { return month; }
	int getDay() { return day; }
	//��,��,���� int�迭�������� ��ȯ
	int *getDate() {
		int arr[] = {year,month,day};
		return arr;
	}
	//Plan ����
	void setPlan(Plan d) { plan = d; }
	//Plan ��ȯ
	Plan getPlan() { return plan; }

	void print() {
		cout << "---------------------" << endl;
		cout << "Date: " << year << "-" << month << "-" << day;
		plan.print();
	}

};

//date���Ŀ� �ʿ��� compare�Լ�
bool compareDate(Date a, Date b) {
	if (a.getYear() < b.getYear()) { return 1; }
	else if (a.getYear() > b.getYear()) { return 0; }
	else if (a.getMonth() < b.getMonth()) { return 1; }
	else if (a.getMonth() > b.getMonth()) { return 0; }
	else if (a.getDay() < b.getDay()) { return 1; }
	else if (a.getDay() > b.getDay()) { return 0; }
	return 1;
}

// Date���� �����ϴ� class
class Calender {
private:
	vector<Date> dates;
public:
	Calender() {}

	//Date �߰� ���� ��¥ Date�� �̹� ������ ��� �ȳ��� ���
	void addDate(Date d) {
		int y = d.getYear();
		int m = d.getMonth();
		int dd = d.getDay();
		for (int i = 0; i < (int)dates.size(); i++) {
			if (dates[i].getYear() == y && dates[i].getMonth() == m && dates[i].getDay() == dd) {
				cout << endl;
				cout << "there is already same Date";
				return;
			}
		}
		dates.push_back(d);
	}
	//�ش��ϴ� ��¥�� Date���� ������ �ȳ��� ���
	void deleteDate(int y, int m, int d) {
		for (int i = 0; i < (int)dates.size(); i++) {
			if (dates[i].getYear() == y && dates[i].getMonth() == m && dates[i].getDay() == d) {
				dates.erase(dates.begin() + i);
				cout << "Delete Success" << endl;
				return;
			}
		}
		cout << endl;
		cout << "Not Exist Plan at the date";
	}
	//Date���� ��¥������ ����
	void sortDate() {
		sort(dates.begin(), dates.end(), compareDate);
	}

	//��ü ���
	void printAll() {
		for (Date kk : dates) {
			kk.print();
		}
	}

	//�ش� ��¥�� Date���
	void printDate(int y) {
		bool count = false;
		for (Date kk : dates) {
			if (kk.getYear() == y) {
				kk.print();
				count = true;
			}
		}
		if (!count) {
			cout << "NO RESULT" << endl;
		}
	}
	void printDate(int y, int m) {
		bool count = false;
		for (Date kk : dates) {
			if (kk.getYear() == y && kk.getMonth() == m) {
				kk.print();
				count = true;
			}
		}
		if (!count) {
			cout << "NO RESULT" << endl;
		}
	}
	void printDate(int y, int m, int d) {
		bool count = false;
		for (Date kk : dates) {
			if (kk.getYear() == y && kk.getMonth() == m && kk.getDay() == d) {
				kk.print();
				count = true;
			}
		}
		if (!count) {
			cout << "NO RESULT" << endl;
		}
	}

	//�ش� ��¥�� Date��ȯ
	Date getDate(int y, int m, int d) {
		for (Date kk : dates) {
			if (kk.getYear() == y && kk.getMonth() == m && kk.getDay() == d) {
				return kk;
			}
		}
	}
	
	vector<Date> getCalender() {
		return dates;
	}
};

