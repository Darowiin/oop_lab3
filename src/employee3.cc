#pragma warning(disable:6386)
#include <employee3/employee3.h>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

//setters and getters
void Employee::set_full_name(string full_name) { this->full_name = full_name; }
void Employee::set_year_of_hiring(int year_of_hiring) { this->year_of_hiring = year_of_hiring; }
void Staff::set_current_year(int current_year) { this->current_year = current_year; }
void Staff::set_basic_rate_for_month(int basic_rate_for_month) { this->basic_rate_for_month = basic_rate_for_month; }
void Freelance::set_basic_rate_for_hour(int basic_rate_for_hour) { this->basic_rate_for_hour = basic_rate_for_hour; }
void Freelance::set_percent_of_individual_allowance(double percent_of_individual_allowance) { this->percent_of_individual_allowance = percent_of_individual_allowance; }
void Freelance::set_number_of_hours_in_month(int number_of_hours_in_month) { this->number_of_hours_in_month = number_of_hours_in_month; }
string Employee::get_full_name() const { return full_name; }
int Employee::get_year_of_hiring() const { return year_of_hiring; }
int Staff::get_current_year() const { return current_year; }
int Staff::get_basic_rate_for_month() const { return basic_rate_for_month; }
int Freelance::get_basic_rate_for_hour() const { return basic_rate_for_hour; }
double Freelance::get_percent_of_individual_allowance() const { return percent_of_individual_allowance; }
int Freelance::get_number_of_hours_in_month() const { return number_of_hours_in_month;}
//c-tors and d-tors
Staff::Staff() {
	full_name = "default";
	year_of_hiring = 0;
	current_year = 0;
	basic_rate_for_month = 0;
}
Freelance::Freelance() {
	full_name = "default";
	year_of_hiring = 0;
	basic_rate_for_hour = 0;
	percent_of_individual_allowance = 0;
	number_of_hours_in_month = 0;
}
Staff::Staff(string full_name, int year_of_hiring, int current_year, int basic_rate_for_month) {
	this->full_name = full_name;
	this->year_of_hiring = year_of_hiring;
	this->current_year = current_year;
	this->basic_rate_for_month = basic_rate_for_month;
}
Freelance::Freelance(string full_name, int year_of_hiring, int basic_rate_for_hour, double percent_of_individual_allowance, int number_of_hours_in_month) {
	this->full_name = full_name;
	this->year_of_hiring = year_of_hiring;
	this->basic_rate_for_hour = basic_rate_for_hour;
	this->percent_of_individual_allowance = percent_of_individual_allowance;
	this->number_of_hours_in_month = number_of_hours_in_month;
}
EmployeeList::EmployeeList() {
	for (int i = 0; i < 5; ++i) {
		_employee.push_back(make_shared<Staff>());
	}
}
EmployeeList::EmployeeList(vector<ItemPtr> employees) {
	_employee = vector<ItemPtr>(employees.size());
	for (int i = 0; i < _employee.size(); ++i) {
		this->_employee[i] = make_shared<Staff>();
	}
}
EmployeeList::EmployeeList(vector<ItemPtr> employees,int) {
	_employee = vector<ItemPtr>(employees.size());
	for (int i = 0; i < _employee.size(); ++i) {
		this->_employee[i] = make_shared<Freelance>();
	}
}
EmployeeList::EmployeeList(const EmployeeList& other) {
	this->_employee = other._employee;
}
//methods
int Staff::compute_salary() const {
    int salary = basic_rate_for_month + ((current_year - year_of_hiring) * 0.005) * basic_rate_for_month;
    return salary;
}
int Freelance::compute_salary() const {
	int salary = ((1 + (0.01 * percent_of_individual_allowance)) * basic_rate_for_hour) * number_of_hours_in_month;
	return salary;
}
unique_ptr<Employee> Staff::clone() const {
	return make_unique<Staff>(full_name, year_of_hiring, current_year, basic_rate_for_month);
}
unique_ptr<Employee> Freelance::clone() const {
	return make_unique<Freelance>(full_name, year_of_hiring, basic_rate_for_hour, percent_of_individual_allowance, number_of_hours_in_month);
}
void Staff::print(ostream& out) const {
	out << "Staff(" << full_name << ',' << year_of_hiring << ',' << basic_rate_for_month << ',' << current_year << ')';
}
void Freelance::print(ostream& out) const {
	out << "Freelance(" << full_name << ',' << year_of_hiring << ',' << basic_rate_for_hour << ',' << percent_of_individual_allowance << ',' << number_of_hours_in_month << ')';
}
int EmployeeList::find_with_max_salary() {
	int index = 0;
	double max_salary = _employee[0]->compute_salary();
	for (int i = 1; i <= _employee.size() - 1; ++i)
	{
		double cur_salary = _employee[i]->compute_salary();
		if (cur_salary > max_salary)
		{
			index = i;
			max_salary = cur_salary;
		}
	}
	return index;
}
//swaps and operators
void EmployeeList::Swap(EmployeeList& other) noexcept{
	swap(_employee, other._employee);
}
bool Staff::equals(shared_ptr<Employee> other) const {
	const auto d_other = dynamic_pointer_cast<Staff>(other);
	if (d_other == nullptr) {
		return false;
	}
	return (full_name == d_other->full_name && year_of_hiring == d_other->year_of_hiring && 
		basic_rate_for_month == d_other->basic_rate_for_month && current_year == d_other->current_year);
}
bool Freelance::equals(shared_ptr<Employee> other) const {
	const auto d_other = dynamic_pointer_cast<Freelance>(other);
	if (d_other == nullptr) {
		return false;
	}
	return (full_name == d_other->full_name && year_of_hiring == d_other->year_of_hiring &&
		basic_rate_for_hour == d_other->basic_rate_for_hour && percent_of_individual_allowance == d_other->percent_of_individual_allowance && 
		number_of_hours_in_month == d_other->number_of_hours_in_month);
}
bool operator==(const EmployeeList& lhs, const EmployeeList& rhs) {
	return ((lhs._employee) == (rhs._employee));
}
bool operator!=(const EmployeeList& lhs, const EmployeeList& rhs) {
	return !(lhs == rhs);
}
EmployeeList& EmployeeList::operator=(EmployeeList other) {
	Swap(other);
	return *this;
}
ItemPtr EmployeeList::operator[](int index) const {
	if (index < 0 || index >= _employee.size())
	{
		throw runtime_error("Index out of range.");
	}
	return _employee[index];
}
ItemPtr& EmployeeList::operator[](int index)
{
	if (index < 0 || index >= _employee.size())
	{
		throw runtime_error("Index out of range.");
	}
	return _employee[index];
}
//getters for list
ItemPtr EmployeeList::get_employee_by_index(int index) { 
	return _employee[index]; 
}
int EmployeeList::size() { 
	return static_cast<int>(_employee.size());
}
//to change the array
void EmployeeList::insert(int index, ItemPtr employer) {
	if (index < 0 || index > _employee.size()) {
		throw runtime_error("Index out of range.");
	}
	_employee.insert(_employee.begin() + index, employer);
}
void EmployeeList::erase(int index) {
	if (index < 0 || index > _employee.size()) {
		throw runtime_error("List is empty.");
	}
	_employee.erase(_employee.begin() + index);
}
void EmployeeList::clear() {
	_employee.clear();
}
//for console
istream& operator>>(istream& in, shared_ptr<Staff>& item) {
	cout << "Enter name:\n ";
	in >> item->full_name;
	cout << "Enter year of hiring:\n ";
	in >> item->year_of_hiring;
	cout << "Enter basic rate for month:\n ";
	in >> item->basic_rate_for_month;
	cout << "Enter current year:\n ";
	in >> item->current_year;
	return in;
}
istream& operator>>(istream& in, shared_ptr<Freelance>& item) {
	cout << "Enter name:\n ";
	in >> item->full_name;
	cout << "Enter year of hiring:\n ";
	in >> item->year_of_hiring;
	cout << "Enter basic rate for hour:\n ";
	in >> item->basic_rate_for_hour;
	cout << "Enter percent of individual allowance(0-5):\n ";
	in >> item->percent_of_individual_allowance;
	cout << "Enter number of hours in month:\n";
	in >> item->number_of_hours_in_month;
	return in;
}
void EmployeeList::print_current(int index) {
	_employee[index]->print(cout);
}
void EmployeeList::show_all() {
	cout << "Текущий список:\n";
	for (int i = 0; i < _employee.size(); ++i) {
		cout << i << ':';
		print_current(i);
		cout << endl;
	}
}