#ifndef __CITY_H__
#define __CITY_H__
#include <set>
#include <memory>
#include "Citizen.h"
#include "Faculty.h"
#include "Workplace.h"

namespace mtm 

{
    // class HiringCondition;

    template<class Condition>
    class CompareFaculties
        {
        public:
            bool operator()( Faculty<Condition> faculty1,  Faculty<Condition> faculty2)
            {
                return faculty1.getId() < faculty2.getId(); 
            }
        };
    // class Condition
    // {
    //     public:
    //         bool operator()(Employee* employee)
    //         {
    //             return true;
    //         }
    // };
    // template<class Condition>
    class City
    {

        private:
            std::string name;
            std::set<Citizen* , CompareCitizens> citizens;
            
            std::set<Faculty<Condition>, CompareFaculties<Condition>> faculties; // maybe change set to vector here
            std::set<WorkPlace, CompareWorkplaces> workplaces;
        
        public:
            City(std::string name) : name(name) {}
            void addEmployee(int id,std::string first_name,std::string last_name,int year_of_birth);
            void addManager(int id,std::string first_name,std::string last_name,int year_of_birth);
            
            void addFaculty(int id,  Skill skill, int acquired_points, Condition* condition);
            void createWorkplace(int id,std::string name,int salary_of_employees,int salary_of_managers);
            void teachAtFaculty(int employee_id, int faculty_id);
            
            template<class HiringCondition>
            void hireEmployeeAtWorkplace(HiringCondition condition,int employee_id, int manager_id, int workplace_id);
            
            void hireManagerAtWorkplace(int manager_id, int workplace_id);
            void fireEmployeeAtWorkplace(int employee_id, int manager_id, int workplace_id);
            void fireManagerAtWorkplace(int manager_id, int workplace_id);
            int getAllAboveSalary(std::ostream& stream, int salary);
            bool isWorkingInTheSameWorkplace(int employee_id1,int employee_id2);
            void printAllEmployeesWithSkill(std::ostream& stream, int skill_id);
            static Employee* doesEmployeeExist(std::set<Citizen* , CompareCitizens>& citizens, int employee_id);
            static Manager* doesManagerExist(std::set<Citizen* , CompareCitizens>& citizens, int manager_id);
    };

    template<class HiringCondition>
    void City::hireEmployeeAtWorkplace(HiringCondition Condition,int employee_id, int manager_id, int workplace_id)
    {
        
        Employee * employee = doesEmployeeExist(this->citizens, employee_id);

        Manager * manager = doesManagerExist(this->citizens, manager_id);

        
        WorkPlace work_place(workplace_id,"F",0,0);
        if(workplaces.find(work_place) == workplaces.end())
        {
            throw WorkplaceDoesNotExist();
        }
        
        WorkPlace wp = (*(workplaces.find(work_place)));
        wp.hireEmployee(Condition ,employee ,manager_id);
        workplaces.erase((*(workplaces.find(work_place))));
        workplaces.insert(wp);
    }
    
}



#endif  //  __CITY_H__

