#ifndef __WORKPLACE_H__
#define __WORKPLACE_H__
#include "Employee.h"

namespace mtm
{
    typedef void*(*ConditionToCheck)(Condition*);
    class WorkPlace
    {
        private:
            int id;
            std::string name;
            int salary_of_employees;
            int salary_of_managers;

        public:
        Citizen(int id,std::string name,int salary_of_employees,int salary_of_managers);
        int getManagersSalary();
        int getWorkersSalary();
        std::string getName();
        int getId();
        
        template<class HiringCondition>
        void hireEmployee(HiringCondition condition ,Employee* employee,int id_of_manager);
        virtual std::ostream& printShort(std::ostream& stream) const =0;
        virtual std::ostream& printLong(std::ostream& stream) const =0;
        virtual std::shared_ptr<Citizen> clone() const = 0;

        friend bool operator==(const Citizen& Citizen1,const Citizen& Citizen2); // how to make virtual
        friend bool operator<(const Citizen& Citizen1,const Citizen& Citizen2);
        virtual ~Citizen() = default;

        
    };
    bool operator>(const Citizen& Citizen1,const Citizen& Citizen2);
    bool operator>=(const Citizen& Citizen1,const Citizen& Citizen2);
    bool operator<=(const Citizen& Citizen1,const Citizen& Citizen2);
    bool operator!=(const Citizen& Citizen1,const Citizen& Citizen2);
}



#endif  //  __WORKPLACE_H__

