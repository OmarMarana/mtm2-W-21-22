#include "Employee.h"
#include "exceptions.h"
#include "Skill.h"
#include <set>
#include <iostream>

namespace mtm
{
    int Employee::getSalary()
    {
        return salary;
    }

    int Employee::getScore()
    {
        return score;
    }

    void Employee::learnSkill(Skill skill)
    {
        if( skills.find(skill) != skills.end())
        {
            throw SkillAlreadyLearned();
        }
        if(this->score < skill.getRequiredPoints()) 
        {
            throw CanNotLearnSkill();
        }
        skills.insert(skill);
    }

    void Employee::forgetSkill(int skill_id)
    {
        if(hasSkill(skill_id)==false)
        {
            throw DidNotLearnSkill();
        }

        std::string tmp_name = "shalom";
        int tmp_required_points = 10;
        Skill tmp(skill_id,tmp_name,tmp_required_points);
        skills.erase(tmp);
    }

    bool Employee::hasSkill(int skill_id)
    {
        bool flag = false;
        Skill tmp(skill_id, "s", 10);

        if( skills.find(tmp) != skills.end())
        {
            flag = true;
        }
        return flag;
    }

    void Employee::setSalary(int delta)
    {

        this->salary += delta;
        if(this->salary < 0)
        {
          this->salary = 0;  
        }
    }

    void Employee::setScore(int delta)
    {
        this->score += delta;
        if(this->score < 0)
        {
          this->score = 0;  
        }
    }

    std::ostream& Employee::printShort(std::ostream& stream) const 
    {
        return stream << getFirstName() << " " << getLastName() << std::endl 
        << "Salary: " << salary << " Score: " << score << std::endl;
    }

    std::ostream& Employee::printLong(std::ostream& stream) const
    {
        if(skills.size() != 0)
        {
            stream << getFirstName() << " " << getLastName() << std::endl 
            << "id - " << getId() << " birth_year - " << getBirthYear() << std::endl 
            <<  "Salary: " << salary << " Score: " << score <<" Skills: " << std::endl;
           
        }
        else
        {
            stream << getFirstName() << " " << getLastName() << std::endl 
            << "id - " << getId() << " birth_year - " << getBirthYear() << std::endl 
            <<  "Salary: " << salary << " Score: " << score << std::endl;
        }
        
        

        for(std::set<Skill>::iterator i = skills.begin(); i != skills.end(); ++i)
        {
            stream << (*i).getName()<< std::endl;
        } 
        
        
        return stream;
    }

    Citizen* Employee::clone() const 
    {
        Citizen* ptr(new Employee(*this));
        return ptr;
    }
}