#include "Skill.h"
#include "exceptions.h"
#include <iostream>

namespace mtm
{
    int Skill::getId() const{
        return id;
    }

    std::string Skill::getName() const{
        return name;
    }

    int Skill::getRequiredPoints() const{
        return required_points;
    }

    Skill Skill::operator++(int) 
    {
        
        Skill result = *this;
        this->required_points++;
        return result;

    }

    Skill& Skill::operator+=(int delta)
    {
        if(delta<0)
        {
          throw NegativePoints();
        }
       this->required_points +=delta; 
       return *this;
    }

    Skill operator+(Skill skill,int points)
    {   
        if(points<0)
        {
          throw NegativePoints();
        }
        // skill.id += points;////may add sum from the other side.
        Skill new_skill(skill);
        new_skill.required_points += points;
        return new_skill;
    }
    
    Skill operator+(int points,Skill skill)
    {
        if(points<0)
        {
          throw NegativePoints();
        }
        // skill.id += points;////mey add sum from the other side.
        Skill new_skill(skill);
        new_skill.required_points += points;
        return new_skill;
    }

    std::ostream& operator<<(std::ostream& stream, const Skill& skill)
    {
        stream << skill.getName() << std::endl;
        return stream;
    }

    bool operator==(const Skill& skill1,const Skill& skill2)
    {
        return skill1.id == skill2.id;
    }
    
    bool operator<(const Skill& skill1,const Skill& skill2)
    {
        return skill1.id < skill2.id;
    }

    bool operator>(const Skill& skill1,const Skill& skill2)
    {
        return skill1.getId() > skill2.getId();
    }

    bool operator>=(const Skill& skill1,const Skill& skill2)
    {
        return skill1.getId() >= skill2.getId();
    }

    bool operator<=(const Skill& skill1,const Skill& skill2)
    {
        return skill1.getId() <= skill2.getId();
    }
    bool operator!=(const Skill& skill1,const Skill& skill2)
    {
        return skill1.getId() != skill2.getId();
    }
}