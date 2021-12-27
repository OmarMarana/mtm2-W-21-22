#ifndef CITIZEN_H
#define CITIZEN_H
#include <string>
#include <memory>

namespace mtm
{
    class Citizen
    {
        private:
            int id;
            std::string first_name;
            std::string last_name;
            int year_of_birth;
        
        public:
        Citizen(int id,std::string first_name,std::string last_name,int year_of_birth );
        int getId();
        std::string getFirstName();
        std::string getLastName();
        int getYearOfBirth();

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

#endif 