#pragma once
#include <memory>
#include <iostream>
#include <vector>
#define ItemPtr shared_ptr<Employee>
using namespace std;

class Employee {
public:
	void set_full_name(string full_name);
	void set_year_of_hiring(int year_of_hiring);
	string get_full_name() const;
	int get_year_of_hiring() const;

	virtual int compute_salary() const = 0;

	virtual unique_ptr<Employee> clone() const = 0;
	virtual bool equals(shared_ptr<Employee> other) const = 0;
	virtual void print(ostream& stream) const = 0;

	virtual ~Employee() = default;
protected:	
	string full_name;
	int year_of_hiring;
	Employee() = default;
	Employee(const Employee& employer) = default;
	Employee& operator=(const Employee& other) = default;
};

class Staff : public Employee {
	int current_year;
	int basic_rate_for_month;
public:
	void set_current_year(int current_year);
	void set_basic_rate_for_month(int basic_rate_for_month); 
	int get_current_year() const;
	int get_basic_rate_for_month() const;

	Staff();
	Staff(string full_name, int year_of_hiring, int current_year, int basic_rate_for_month);
	~Staff() = default;

	unique_ptr<Employee> clone() const override;
	bool equals(shared_ptr<Employee> other) const override;
	void print(ostream& out) const override;
	friend istream& operator>>(istream& in, shared_ptr<Staff>& item);
	int compute_salary() const override;
};

class Freelance : public Employee {
	int basic_rate_for_hour;
	double percent_of_individual_allowance;
	int number_of_hours_in_month;
public:
	void set_basic_rate_for_hour(int basic_rate_for_hour);
	void set_percent_of_individual_allowance(double percent_of_individual_allowance);
	void set_number_of_hours_in_month(int number_of_hours_in_month);
	int get_basic_rate_for_hour() const;
	double get_percent_of_individual_allowance() const;
	int get_number_of_hours_in_month() const;

	Freelance();
	Freelance(string full_name, int year_of_hiring, int basic_rate_for_hour, double percent_of_individual_allowance, int number_of_hours_in_month);
	~Freelance() = default;

	unique_ptr<Employee> clone() const override;
	bool equals(shared_ptr<Employee> other) const override;
	void print(ostream& out) const override;
	friend istream& operator>>(istream& in, shared_ptr<Freelance>& item);
	int compute_salary() const override;
};

class EmployeeList {
	vector<ItemPtr> _employee;

public:
	EmployeeList();
	EmployeeList(vector<ItemPtr> employees);
	EmployeeList(vector<ItemPtr> employees, int);
	EmployeeList(const EmployeeList& pther);

	ItemPtr get_employee_by_index(int i);
	int size();

	ItemPtr operator[](int index) const;
	ItemPtr& operator[](int index);
	EmployeeList& operator=(EmployeeList other);

	void insert(int index, ItemPtr employer);
	void erase(int index);
	void clear();
	void print_current(int index);
	void show_all();
	void Swap(EmployeeList& other) noexcept;
	friend bool operator==(const EmployeeList& lhs, const EmployeeList& rhs);
	friend bool operator!=(const EmployeeList& lhs, const EmployeeList& rhs);
	int find_with_max_salary();
};