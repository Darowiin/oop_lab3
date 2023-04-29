#include <gtest/gtest.h>
#include <employee3/employee3.h>


TEST(EmployeeTests, EmployeetConstructorTest) {
    Staff person1 = Staff("Vladimir Petrov", 2020, 2023, 45000);
    EXPECT_EQ(person1.get_full_name(), "Vladimir Petrov");
}
TEST(EmployeeTests, EmployeetConstructorTest2) {
    Staff person1 = Staff("Vladimir Petrov", 2020, 2023, 45000);
    EXPECT_EQ(person1.get_current_year(), 2023);
}
TEST(EmployeeTests, EmployeetConstructorTest3) {
    Freelance person1 = Freelance("Sergey Smirnov", 2020, 200, 2.5, 150);
    EXPECT_EQ(person1.get_basic_rate_for_hour(), 200);
}
TEST(EmployeeTests, EmployeetConstructorTest4) {
    Freelance person1 = Freelance("Sergey Smirnov", 2020, 200, 2.5, 150);
    EXPECT_EQ(person1.get_percent_of_individual_allowance(), 2.5);
}
TEST(EmployeeTests, EmployeeSetterTest2) {
    Staff person1;
    person1.set_year_of_hiring(2019);
    EXPECT_EQ(person1.get_year_of_hiring(), 2019);
}
TEST(EmployeeTests, EmployeeSetterTest3) {
    Staff person1;
    person1.set_basic_rate_for_month(37500);
    EXPECT_EQ(person1.get_basic_rate_for_month(), 37500);
}
TEST(EmployeeTests, EmployeeSetterTest4) {
    Freelance person1;
    person1.set_full_name("Vitaliy Ivanov");
    EXPECT_EQ(person1.get_full_name(), "Vitaliy Ivanov");
}
TEST(EmployeeTests, EmployeeComputeSalaryTest) {
    Staff person1("Konstantin Jukov", 2021, 2023, 30000);
    EXPECT_EQ(person1.compute_salary(), 30300);
}
TEST(EmployeeTests, EmployeeComputeSalaryTest2) {
    Freelance person1("Ivan Krilov", 2021, 150, 2.7, 140);
    EXPECT_EQ(person1.compute_salary(), 21566);
}
TEST(EmployeeListTests, EmployeeListDefaultConstructorTest) {
    EmployeeList EL = EmployeeList();
    EXPECT_EQ(EL.size(), 5);
}
TEST(EmployeeListTests, EmployeeListDefaultConstructorTest2) {
    EmployeeList EL = EmployeeList();
    EXPECT_EQ(EL[0]->get_full_name(), "default");
}
TEST(EmployeeListTests, EmployeeListAddEmployerTest) {
    EmployeeList EL = EmployeeList();
    ItemPtr employer = make_shared<Staff>("Konstantin Jukov", 2021, 2023, 30000);
    EL.insert(2, employer);
    EXPECT_EQ(EL.size(), 6);
    EXPECT_EQ(EL[2]->get_full_name(), "Konstantin Jukov");
    EXPECT_EQ(EL[0]->compute_salary(), 0);
    EXPECT_EQ(EL[2]->compute_salary(), 30300);
}
TEST(EmployeeListTests, EmployeeListDelEmployerTest) {
    EmployeeList EL = EmployeeList();
    EL.erase(0);
    EXPECT_EQ(EL.size(), 4);
    EXPECT_EQ(EL[0]->compute_salary(), 0);
}
TEST(EmployeeListTests, EmployeeListClearTest) {
    EmployeeList EL = EmployeeList();
    EL.clear();
    EXPECT_EQ(EL.size(), 0);
}
TEST(EmployeeListTests, EmployeeListMaxSalaryTest) {
    EmployeeList EL;
    EL.insert(0, make_shared<Staff>("John Manning", 2021, 2023, 30000));
    EL.insert(1, make_shared<Freelance>("Leroy Williams", 2018, 400, 2.5,250));
    EL.insert(2, make_shared<Staff>("Matthew Cooper", 2015, 2023, 40000));
    EL.insert(3, make_shared<Freelance>("Anthony Miller", 2017, 350, 3.5, 200));
    EL.insert(4, make_shared<Staff>("Peter Manning", 2019, 2023, 50000));
    EXPECT_EQ(EL.find_with_max_salary(), 1);
}
TEST(EmployeeListTests, EmployeeListCtorAndOPCpyTest) {
    EmployeeList EL = EmployeeList();
    EmployeeList EL2(EL);
    EmployeeList EL3 = EL;
    EXPECT_EQ(EL, EL2);
    EXPECT_EQ(EL, EL3);
}
TEST(ExceptionTests, ExeptionIndexOutTest) {
    EmployeeList EL = EmployeeList();
    EXPECT_THROW(EL[-1]->compute_salary(), std::runtime_error);
    EXPECT_THROW(EL[10]->compute_salary(), std::runtime_error);
}
TEST(ExceptionTests, ExeptionEmptyTest) {
    EmployeeList EL = EmployeeList();
    for (int i = 0; i < 5; ++i) {
        EL.erase(0);
    }
    EXPECT_THROW(EL.erase(1), std::runtime_error);
}
