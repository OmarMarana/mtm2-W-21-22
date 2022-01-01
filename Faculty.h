#ifndef __FACULTY_H__
#define __FACULTY_H__
#include "Skill.h"
#include "Employee.h"
#include <string>
#include <cstdbool>
#include <memory>


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
            Condition condition;
            Skill skill;
            int acquired_points;
            int id;
        
    	public:
            Faculty(int id,  Skill skill, int acquired_points, Condition condition) : 
                id(id),  skill(skill), acquired_points(acquired_points) ,condition(condition){};
            int getAddedPoints();
            int getId();
            Skill getSkill();
            void teach(Employee& employee)const;
    };

    // template<class Condition>
    
    

}


#endif  //  __FACULTY_H__

