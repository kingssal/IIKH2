#pragma once
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

#include "Recipe.h"

using namespace std;


//recipe의 집합클래스
class Meal { 
private:
	vector<Recipe> recipes; //Meal에 포함된 recipe들을 저장하는 set

public:
	Meal() {}
	// recipe들이 저장된 set 반환
	vector<Recipe> getRecipes() { return recipes; } 
	// recipes에 새로운 Recipe 추가 { 필요인자: 추가할 Recipe객체 }
	void addRecipes(Recipe data) { recipes.push_back(data); } 
	// target Recipe 제거 { 필요인자: 제거할 Recipe객체 }
	void deleteRecipes(Recipe target) {
		for (int i = 0; i < recipes.size(); i++) {
			if (recipes[i].getName() == target.getName()) {
				recipes.erase(recipes.begin() + i);
			}
		}
	}
	// 모든 Recipe 출력
	void print() {
		cout << endl;
		for (Recipe recipe : recipes) {
			cout << "-" << recipe.getName() << endl;
		}
		cout << endl;
	}
};


//Meal을 아침, 점심, 저녁으로 나누어 저장하는 클래스
class Plan {
private:
	Meal breakfast, lunch, dinner;  //아침,점심,저녁 Meal
	string name = "NULL"; // Plan 이름

public:
	//Plan초기내용 설정하는 Constructor { 필요인자: Plan이름 String, Meal이 3개 저장된 Vector }
	Plan() {}
	Plan(string n, Meal a, Meal b, Meal c) {
		name = n;
		breakfast = a;
		lunch = b;
		dinner = c;
	}
	// Plan 이름 반환
	string getName() { return name; }
	//아침,점심,저녁 반환
	Meal getBreakfast() { return breakfast; }
	Meal getLunch() { return lunch; }
	Meal getDinner() { return dinner; }

	//Plan 이름 설정
	void setName(string d) { name = d; }
	//아침,점심,저녁 설정 { 필요인자: Meal 객체 }
	void setBreakfast(Meal data) { breakfast = data; }
	void setLunch(Meal data) { lunch = data; }
	void setDinner(Meal data) { dinner = data; }

	//Plan 출력
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


//Plan들을 관리하는 DB 클래스
class PlanDB {
private:
	vector<Plan> plans;

public:
	//Plan추가 Plan 이름이 없거나 같은 이름이 있으면 안내문 출력
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
	//Plan제거 없으면 안내문 출력
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
	//개별 Plan 출력 { 필요인자: Plan 이름 }
	void printPlan(string data) {
		for (Plan p : plans) {
			if (data == p.getName()) {
				p.print();
			}
		}
	}

	//Plan 반환 ( Plan 이름 필요 )
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

	//전체 Plan 출력
	void printAll() {
		for (Plan p : plans) {
			p.print();
			cout << "---------------------";
			cout << endl;
		}
	}
};

//날짜에 Plan을 설정한 class
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
	//년,월,일, 전체날짜 설정
	void setYear(int data) { year = data; }
	void setMonth(int data) { month = data; }
	void setDay(int data) { day = data; }
	void setDate(int y, int m, int d) { year = y; month = m; day = d; }
	//년,월,일 전체날짜 반환
	int getYear() { return year; }
	int getMonth() { return month; }
	int getDay() { return day; }
	//년,월,일을 int배열형식으로 반환
	int *getDate() {
		int arr[] = {year,month,day};
		return arr;
	}
	//Plan 설정
	void setPlan(Plan d) { plan = d; }
	//Plan 반환
	Plan getPlan() { return plan; }

	void print() {
		cout << "---------------------" << endl;
		cout << "Date: " << year << "-" << month << "-" << day;
		plan.print();
	}

};

//date정렬에 필요한 compare함수
bool compareDate(Date a, Date b) {
	if (a.getYear() < b.getYear()) { return 1; }
	else if (a.getYear() > b.getYear()) { return 0; }
	else if (a.getMonth() < b.getMonth()) { return 1; }
	else if (a.getMonth() > b.getMonth()) { return 0; }
	else if (a.getDay() < b.getDay()) { return 1; }
	else if (a.getDay() > b.getDay()) { return 0; }
	return 1;
}

// Date들을 관리하는 class
class Calender {
private:
	vector<Date> dates;
public:
	Calender() {}

	//Date 추가 같은 날짜 Date가 이미 존재할 경우 안내문 출력
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
	//해당하는 날짜의 Date삭제 없으면 안내문 출력
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
	//Date들을 날짜순으로 정렬
	void sortDate() {
		sort(dates.begin(), dates.end(), compareDate);
	}

	//전체 출력
	void printAll() {
		for (Date kk : dates) {
			kk.print();
		}
	}

	//해당 날짜의 Date출력
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

	//해당 날짜의 Date반환
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

