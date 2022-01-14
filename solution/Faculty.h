#ifndef __FACULTY_H__
#define __FACULTY_H__
#include "Skill.h"
#include "Employee.h"
#include <string>
#include <cstdbool>
#include <memory>
#include "exceptions.h"

namespace mtm
{
    
    template<class Condition>
    class Faculty                            
    {
        class CompareFaculties
        {
        public:
            bool operator()( Faculty<Condition> faculty1,  Faculty<Condition> faculty2)
            {
                return faculty1.getId() < faculty2.getId(); 
            }
        };

        private:
            
            int id;
            Skill skill;
            int added_points;
    	    Condition* condition;            

        
    	public:
            //constructor
            Faculty(int id,  Skill skill, int added_points, Condition* condition) : 
                id(id),  skill(skill), added_points(added_points) ,condition(condition){};
            //return added_points
            int getAddedPoints();
            //return id
            int getId();
            //return the skill that the faculty teaches
            Skill getSkill();
            //teack the employee the skill
            void teach(Employee* employee)const;
    };
    class Condition{
        public:
            virtual bool operator()(Employee* employee) = 0;
    };


    template<class Condition>
    int Faculty<Condition>::getAddedPoints()
    {
        return added_points;
    }

    template<class Condition>
    int Faculty<Condition>::getId()
    {
        return id;
    }

    template<class Condition>
    Skill Faculty<Condition>::getSkill()
    {
        return skill;
    }

    template<class Condition>
    void Faculty<Condition>::teach(Employee* employee) const
    {
        if((*condition)(employee))
        {
            employee->learnSkill(skill);
            employee->setScore(added_points); 
        }

        else
        {
            throw EmployeeNotAccepted();
        }
    }
    

}


#endif  //  __FACULTY_H__

