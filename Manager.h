#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "Citizen.h"
#include "Employee.h"
#include <memory>
#include <set>

namespace mtm
{   
	class Manager : public Citizen
	{
        private:
            int salary;
            bool hired;
            std::set<std::shared_ptr<Employee>, mtm::CompareEmployee> employees; 

        public:
            
            Manager(int id,std::string first_name,std::string last_name,int year_of_birth,
            int salary = 0, bool hired = false):Citizen(id, first_name, last_name,year_of_birth), salary(salary), hired(hired) {}
            //check if chould define defaluts
            //
            int getSalary()const;
            void addEmployee(std::shared_ptr<Employee> employee);
            void removeEmployee(int employee_id);
            void setSalary(int salary_to_add);
            bool getHired() const;
            void setHired(bool hired);
            std::ostream& printShort(std::ostream& stream) const override;
            std::ostream& printLong(std::ostream& stream) const override;
            std::shared_ptr<Citizen> clone() const override;
            ~Manager() override = default;
            bool isEmployeeIn(int employee_id);
            Manager(const Manager& other) = default;
    };
    class CompareManager 
    {
        public:
            bool operator()(std::shared_ptr<Manager> manager1, std::shared_ptr<Manager> manager2)
            {
                return manager1->getId() < manager2->getId(); 
            }
    };
}


#endif  //  __MANAGER_H__

