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
            std::set<Skill> skills; // may have to define a cmpFunc like citizenCmp

        public:
            Employee(int id,std::string first_name,std::string last_name,int year_of_birth, int salary = 0,int score = 0):
            Citizen(id,first_name,last_name,year_of_birth), salary(salary),score(score){}
            int getSalary();
            int getScore();
            void learnSkill(Skill skill);
            void forgetSkill(int skill_id);
            bool hasSkill(int skill_id);
            void setSalary(int delta);
            void setScore(int delta);
            ~Employee() override = default;
            std::ostream& printShort(std::ostream& stream) const override;
            std::ostream& printLong(std::ostream& stream) const override;
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