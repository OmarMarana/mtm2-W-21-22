#include "Faculty.h"
#include "exceptions.h"
#include "Employee.h"

namespace mtm
{
    template<class Condition>
    int Faculty<Condition>::getAddedPoints()
    {
        return acquired_points;
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
    void Faculty<Condition>::teach(Employee& employee) const
    {
        if(condition(&employee))
        {
            employee.learnSkill(skill);
            employee.setScore(acquired_points);
        }

        else
        {
            throw EmployeeNotAccepted();
        }
    }
}
