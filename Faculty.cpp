#include "Faculty.h"
#include "exceptions.h"
#include "Employee.h"

namespace mtm
{
    int Faculty::getAddedPoints()
    {
        return acquired_points;
    }

    int Faculty::getId()
    {
        return id;
    }

    Skill Faculty::getSkill()
    {
        return skill;
    }

    void Faculty::teach(Employee& employee)
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
