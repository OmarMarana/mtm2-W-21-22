#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

namespace mtm
{
	class Exception : public std::exception
	{
	};

    //Skill
    class NegativePoints : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A Skill related error has occurred: NegativePoints";
        }
    };

    //Employee
	class SkillAlreadyLearned : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "An Employee related error has occurred: SkillAlreadyLearned";
        }
    };
    class CanNotLearnSkill : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "An Employee related error has occurred: CanNotLearnSkill";
        }
    };
    class DidNotLearnSkill : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "An Employee related error has occurred: DidNotLearnSkill";
        }
    };

    //Manager
    class EmployeeAlreadyHired : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A Manager related error has occurred: EmployeeAlreadyHired";
        }
    };
    class EmployeeIsNotHired : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A Manager related error has occurred: EmployeeIsNotHired";
        }
    };

    //Workplace
    class EmployeeNotSelected : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A Workshop related error has occurred: EmployeeNotSelected";
        }
    };
    class ManagerIsNotHired : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A Workshop related error has occurred: ManagerIsNotHired";
        }
    };
    class ManagerAlreadyHired : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A Workshop related error has occurred: ManagerAlreadyHired";
        }
    };
    class CanNotHireManager : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A Workshop related error has occurred: CanNotHireManager";
        }
    };

    //Faculty
    class EmployeeNotAccepted : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A Faculty related error has occurred: EmployeeNotAccepted";
        }
    };

    //City

    class EmployeeAlreadyExists : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A City related error has occurred: EmployeeAlreadyExists";
        }
    };
    class ManagerAlreadyExists : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A City related error has occurred: ManagerAlreadyExists";
        }
    };
    class FacultyAlreadyExists : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A City related error has occurred: FacultyAlreadyExists";
        }
    };
    class WorkplaceAlreadyExists : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A City related error has occurred: WorkplaceAlreadyExists";
        }
    };
    class FacultyDoesNotExist : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A City related error has occurred: FacultyDoesNotExist";
        }
    };
    class EmployeeDoesNotExist : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A City related error has occurred: EmployeeDoesNotExist";
        }
    }; 
    class ManagerDoesNotExist : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A City related error has occurred: ManagerDoesNotExist";
        }
    };
    class WorkplaceDoesNotExist : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A City related error has occurred: WorkplaceDoesNotExist";
        }
    };
    class CitizenAlreadyExists : public Exception
    {
        public: const char * what() const noexcept override
        {
            return "A City related error has occurred: CitizenAlreadyExists";
        }
    };


    
}



#endif