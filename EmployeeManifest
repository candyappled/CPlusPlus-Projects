#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
//#include <bits/stdc++.h>
using namespace std;

class Employee {
protected:
	string firstName;
	string lastName;
	int employeeID;
	string employmentType;
	double earned;
public:
	virtual void output(){
		cout << "employee name: " << getfirstName() << " " << getlastName() << endl;
		cout << "employee ID: " << getemployeeID() << endl;
	}

	virtual void earnings(){
		earned = 0.0;
	}

	virtual void applyRaise(){
		earned = 0.0;
	}

	virtual double getGS(){
		return 0.0;
	}
	
	string getfirstName(){ return firstName; };
	string getlastName(){ return lastName; };
	int getemployeeID(){ return employeeID; };
	void setfirstName(string s){ firstName = s;};
	void setlastName(string s){ lastName = s;};
	void setemployeeID(int n){ employeeID = n;};
	string getEmploymentType(){ return employmentType; };
	void setEmploymentType(string s){ employmentType = s; };
	double getEarned(){ return earned; };
};

class HourlyEmployee: public Employee {
protected:
	double hours, wage;
public:
	void setHours(double h){ hours = h; }
	double getHours(){ return hours; }

	void setWage(double s){ wage = s; }
	double getWage(){ return wage; }

	void applyRaise() {
		earned = earned + 1.5*getHours(); 
		wage += 1.5;
	}
	
	void earnings() {
		int hours = getHours();
		if(hours <= 40.0){
			earned = hours * getWage();
		} else {
			earned = getWage() * 40.0 + (hours-40.0)*1.5*getWage();
		}
	}

	double getGS(){
		return 0.0;
	}

	void output(){
		cout << "employee name: " << getfirstName() << " " << getlastName() << endl;
		cout << "employment type: " << getEmploymentType() << endl;
		cout << "employee ID: " << getemployeeID() << endl;
		cout << fixed << setprecision(2) << "   hourly wage: $" << getWage() << endl;
		cout << fixed << setprecision(2) << "   hours worked: " << getHours() << endl;
		cout << fixed << setprecision(2) << "earned $" << getEarned() << endl;
	}
};

class CommissionEmployee: public Employee {
protected:
	double grossSales, rate;
public:
	void setGS(double f){ grossSales = f; } // gross sales
	double getGS() { return grossSales; }

	void setRate(double s) { rate = s; } // commission rate 
	double getRate() { return rate; }

	void earnings(){
		earned = getGS() * getRate();
	}

	void applyRaise(){
		rate += 0.02;
		earned = earned + earned*0.02;
	}

	void output(){
		cout << "employee name: " << getfirstName() << " " << getlastName() << endl;
		cout << "employment type: " << getEmploymentType() << endl;
		cout << "employee ID: " << getemployeeID() << endl;
		cout << fixed << setprecision(2) << "   gross sales: $" << getGS() << endl;
		cout << fixed << setprecision(2) << "   commission rate: " << getRate()*100 << "%\n";
		cout << fixed << setprecision(2) << "earned $" << getEarned() << endl;
	}
};

class SalariedEmployee: public Employee {
protected:
	double salary;
public:
	double getSalary(){ return salary; };
	void setSalary(double s){ salary = s; };
	void earnings() {
		earned = getSalary();
	}

	void applyRaise(){
		earned = earned + earned*0.1;
	}

	double getGS(){
		return 0.0;
	}

	void output(){
		cout << "employee name: " << getfirstName() << " " << getlastName() << endl;
		cout << "employment type: " << getEmploymentType() << endl;
		cout << "employee ID: " << getemployeeID() << endl;
		cout << fixed << setprecision(2) << "   weekly salary: $" << getSalary() << endl;
		cout << fixed << setprecision(2) << "earned $" << getEarned();
	}
};

class BasePlusCommissionEmployee: public CommissionEmployee{
protected: 
	double baseSalary;
public:
	void setbaseSalary(double s){ baseSalary = s; }
	double getbaseSalary() { return baseSalary; }

	void earnings(){
		earned = getGS() * getRate() + getbaseSalary();
	}

	void applyRaise(){
		baseSalary *=1.05;
		rate += 0.01;
		earned = earned + earned*0.05 + getGS()*0.01;
	}

	void output(){
		cout << "employee name: " << getfirstName() << " " << getlastName() << endl;
		cout << "employment type: " << getEmploymentType() << endl;
		cout << "employee ID: " << getemployeeID() << endl;
		cout << fixed << setprecision(2) << "   gross sales: $" << getGS() << endl;
		cout << fixed << setprecision(2) << "   commission rate: " << (getRate()+0.01)*100 << "%\n";
		cout << fixed << setprecision(2) << "   base salary: $" << getbaseSalary()*1.05 << endl;
		cout << fixed << setprecision(2) << "earned $" << getEarned() << endl;
	}
};

int num, emp; // number of employees, employee type

vector<int> pn; // 68906 elements
bool isPrime(int num){ // check if number supplied is prime
	if(num <= 1) return false;
	int sqrtNum = sqrt(num);
	for(int i = 2; i <= sqrtNum; i++){
		if(num % i == 0) return false;
	}

	return true;
}

void SixPrime(){ // fill pn
	int lower = 100'000;
	int upper = 999'999;
	pn.push_back(0); // put a 0 into pn since indexing starts with 1
	for(int i = lower; i <= upper; i++){
		if(isPrime(i)) pn.push_back(i);
	}
}

string fn, ln; 
double weekly_sales, commission_rate, base_salary;
double hours, wage, sal;

int main() {
	SixPrime(); // fill pn vector with all viable prime numbers
	// ios::sync_with_stdio(0); cin.tie(0);
	cout << "Employee input\n";
	cout << "==============\n";
	cout << "How many employees? "; 
	cin >> num;
	if(num < 0 || num > 68906){ // specified number of employees is out of bounds
		cout << "Invalid number of employees specified.\n";
		return 0;
	}
	
	Employee *employees[num+1]; // array creation
	
	for(int i = 1; i <= num; i++){
		cout << "Employee # " << i << " input:\n";
		cout << "   (1 = Hourly, 2 = Commission, 3 = Base+Commission, 4 = Salaried)\n";
		cout << "   Employee type? ";
		cin >> emp;
		if(emp == 1){	 // hourly
			HourlyEmployee* he = new HourlyEmployee();
			he->setEmploymentType("hourly"); // facilitates output
			cout << "   First name? "; cin >> fn; he->setfirstName(fn);
			cout << "   Last name? "; cin >> ln;  he->setlastName(ln);
			cout << "   Hourly wage? "; cin >> wage; he->setWage(wage);
			cout << "   Hours worked? "; cin >> hours; he->setHours(hours);
			he->setemployeeID(pn[i]);
			he->applyRaise();
			he->earnings();
			employees[i] = he;
		} else if(emp == 2){ // commission
			CommissionEmployee *ce = new CommissionEmployee();
			ce->setEmploymentType("commission"); // facilitates output
			cout << "   First name? "; cin >> fn; ce->setfirstName(fn);
			cout << "   Last name? "; cin >> ln;  ce->setlastName(ln);
			cout << "   Gross sales (in $)? "; cin >> weekly_sales; ce->setGS(weekly_sales);
			cout << "   Commission rate (as a decimal)? "; cin >> commission_rate; ce->setRate(commission_rate);
			ce->setemployeeID(pn[i]);
			ce->applyRaise();
			ce->earnings();
			employees[i] = ce;
		} else if(emp == 3){ // commission + salary
			BasePlusCommissionEmployee* bp = new BasePlusCommissionEmployee();
			bp->setEmploymentType("base-salaried commission"); // facilitates output
			cout << "   First name? "; cin >> fn; bp->setfirstName(fn);
			cout << "   Last name? "; cin >> ln;  bp->setlastName(ln);
			cout << "   Gross sales (in $)? "; cin >> weekly_sales; bp->setGS(weekly_sales);
			cout << "   Commission rate (as a decimal)? "; cin >> commission_rate; bp->setRate(commission_rate);
			cout << "   Base salary? "; cin >> base_salary; bp->setbaseSalary(base_salary);
			bp-> setemployeeID(pn[i]);
			bp->applyRaise();
			bp->earnings();
			employees[i] = bp;
		} else if(emp == 4) { // salaried
			SalariedEmployee *se = new SalariedEmployee();
			se->setEmploymentType("salaried"); // facilitates output
			cout << "   First name? "; cin >> fn; se->setfirstName(fn);
			cout << "   Last name? "; cin >> ln;  se->setlastName(ln);
			cout << "   Salary? "; cin >> sal; se->setSalary(sal);
			se->setemployeeID(pn[i]);
			se->earnings();
			se->applyRaise();
			employees[i] = se;
		} else { // if none of the above print error message 
			cout << "Invalid employee type specified.\n";
			return 0;
		}
	} 

	cout << endl << "Employee input complete.\n\n";
	cout << "Applying pay changes.\n";
	cout << endl;
	double totalSales = 0.0;
	double totalPayroll = 0.0;

	// output employee summary
	cout << "Employee Summary\n";
	cout << "================\n";
	for(int i = 1; i <= num; i++){
		totalPayroll += employees[i]->getEarned(); // calculate payroll
		totalSales += employees[i]->getGS(); // calculate sales
		employees[i]->output(); cout << endl;
	}

	cout << endl;

	// output company summary
	cout << "Company Summary\n";
	cout << "===============\n";
	cout << fixed << setprecision(2) << "Total sales: $" << totalSales << endl;
	cout << fixed << setprecision(2) << "Total payroll: $" << totalPayroll << endl;
	
	return 0;
} 
