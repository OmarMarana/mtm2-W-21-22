#ifndef __FACULTY_H__
#define __FACULTY_H__
#include "Skill.h"
#include "Employee.h"
#include <string>
#include <cstdbool>
#include <memory>


namespace mtm
{
    class CompareFaculties
    {
        public:
            bool operator()( Faculty& faculty1,  Faculty& faculty2)
            {
                return faculty1.getId() < faculty2.getId(); 
            }
    };                                             //******************************************
    typedef bool(*Condition)(Employee*);      // check if this is okay with the Staff reqs, specifically with add faculty
    class Faculty                             //******************************************
    {
        private:
            Condition condition ;
            Skill skill;
            int acquired_points;
            int id;
        
    	public:
            Faculty(int id,  Skill skill, int acquired_points, mtm::Condition condition) : 
                id(id),  skill(skill), acquired_points(acquired_points) ,condition(condition){};
            int getAddedPoints();
            int getId();
            Skill getSkill();
            std::string getName();
            int getRequiredPoints();
            void teach(Employee& employee);
    };

}


#endif  //  __FACULTY_H__

