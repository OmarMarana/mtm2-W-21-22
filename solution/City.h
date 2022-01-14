#ifndef __CITY_H__
#define __CITY_H__
#include <set>
#include <memory>
#include "Citizen.h"
#include "Faculty.h"
#include "Workplace.h"

namespace mtm 

{

    template<class Condition>
    class CompareFaculties
        {
        public:
            bool operator()( Faculty<Condition> faculty1,  Faculty<Condition> faculty2)
            {
                return faculty1.getId() < faculty2.getId(); 
            }
        };
    
    class City
    {
        private:
            std::string name;
            std::set<Citizen* , CompareCitizens> citizens;
            
            std::set<Faculty<Condition>, CompareFaculties<Condition>> faculties; 
            std::set<std::shared_ptr<Workplace>, CompareWorkplaces> workplaces;
        
        public:
            //constructor
            City(std::string name) : name(name) {}
            //destructor
            ~City();
            
            //add an employee to the city
            void addEmployee(int id,std::string first_name,std::string last_name,int year_of_birth);
            //add a manager to the city
            void addManager(int id,std::string first_name,std::string last_name,int year_of_birth);
            //add a faculty to the city
            void addFaculty(int id,  Skill skill, int acquired_points, Condition* condition);
            //add a Workplace to the city
            void createWorkplace(int id,std::string name,int salary_of_employees,int salary_of_managers);
            //teach an imployee at the faculty
            void teachAtFaculty(int employee_id, int faculty_id);
            //hire an employee if the condition is satisfied
            template<class HiringCondition>
            void hireEmployeeAtWorkplace(HiringCondition condition,int employee_id, int manager_id, int workplace_id);
            //hire a manager at a Workplace
            void hireManagerAtWorkplace(int manager_id, int workplace_id);
            //fire an employee
            void fireEmployeeAtWorkplace(int employee_id, int manager_id, int workplace_id);
            //fire a manager
            void fireManagerAtWorkplace(int manager_id, int workplace_id);
            //print all citizens that earn more or equal to salary and return their amount
            int getAllAboveSalary(std::ostream& stream, int salary);
            //check if two employees are working in the same place
            bool isWorkingInTheSameWorkplace(int employee_id1,int employee_id2);
            //print all employees the have the skill 
            void printAllEmployeesWithSkill(std::ostream& stream, int skill_id);
            //static function that checks if the employee exists in the set of citizens 
            static Employee* doesEmployeeExist(std::set<Citizen* , CompareCitizens>& citizens, int employee_id);
            bool doesExist(int employee_id);
            //static function that checks if the manager exists in the set of citizens 
            static Manager* doesManagerExist(std::set<Citizen* , CompareCitizens>& citizens, int manager_id);
    };

    template<class HiringCondition>
    void City::hireEmployeeAtWorkplace(HiringCondition Condition,int employee_id, int manager_id, int workplace_id)
    {
        
        Employee * employee = doesEmployeeExist(this->citizens, employee_id);

        doesManagerExist(this->citizens, manager_id);
        
        std::shared_ptr<Workplace> work_place(new Workplace(workplace_id,"F",0,0));
        if(workplaces.find(work_place) == workplaces.end())
        {
            throw WorkplaceDoesNotExist();
        }
        
        (*(workplaces.find(work_place)))->hireEmployee(Condition ,employee ,manager_id);
        
    }
    
}



#endif  //  __CITY_H__

