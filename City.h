#ifndef __CITY_H__
#define __CITY_H__
#include <set>
#include <memory>
#include "Citizen.h"
#include "Faculty.h"
#include "Workplace.h"

namespace mtm 
{
    class City
    {
        private:
            std::string name;
            std::set<std::shared_ptr<Citizen> , CompareCitizens> citizens;
            std::set<Faculty, CompareFaculties> faculties;
            std::set<WorkPlace, CompareWorkplaces> workplaces;
        
        public:
            City(std::string name) : name(name) {}
            void addEmployee(int id,std::string first_name,std::string last_name,int year_of_birth);
            void addManager(int id,std::string first_name,std::string last_name,int year_of_birth);
            void addFaculty(int id,  Skill skill, int acquired_points, mtm::Condition condition);
            void createWorkplace(int id,std::string name,int salary_of_employees,int salary_of_managers);
            void teachAtFaculty(int employee_id, int faculty_id );
            
            template<class HiringCondition>
            void hireEmployeeAtWorkPlace(HiringCondition Condition,int employee_id, int manager_id, int workplace_id);
            
            void hireManagerAtWorkPlace( int manager_id, int workplace_id);
            void fireEmployeeAtWorkPlace(int employee_id, int manager_id, int workplace_id);
            void fireManagerAtWorkPlace( int manager_id, int workplace_id);
            int getAllAboveSalary(std::ostream& stream, int salary);
            bool isWorkingInTheSameWorkplace(int employee_id1,int employee_id2);
            void printAllEmployeesWithSkill(std::ostream& stream);

    };
}



#endif  //  __CITY_H__

