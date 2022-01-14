#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "Skill.h"
#include "Citizen.h"
#include <set>

namespace mtm
{
    class Employee : public Citizen
    {
        private:
            int salary;
            int score;
            std::set<Skill> skills; 

        public:
            Employee(int id,std::string first_name,std::string last_name,int year_of_birth, int salary = 0,int score = 0):
            Citizen(id,first_name,last_name,year_of_birth), salary(salary),score(score){}
            Employee(const Employee& other) = default;
            Employee& operator=(const Employee& other) = default;
            //return the salary of employee
            int getSalary();
            //return the score of employee
            int getScore();
            //give skill to employee
            void learnSkill(Skill skill);
            //remove skill from employee
            void forgetSkill(int skill_id);
            //check if the employee has the skill
            bool hasSkill(int skill_id);
            //change the salary of the employee
            void setSalary(int delta);
            //change the score of the employee
            void setScore(int delta);
            //destructor of employee
            ~Employee() override = default;
            //print short of employee
            std::ostream& printShort(std::ostream& stream) const override;
            //print long of employee
            std::ostream& printLong(std::ostream& stream) const override;
            //clone of employee
            Citizen* clone() const override;
    };
    class CompareEmployee 
    {
        public:
            bool operator()(Employee* employee1, Employee* employee2)
            {
                return employee1->getId() < employee2->getId(); 
            }
    };
}

#endif