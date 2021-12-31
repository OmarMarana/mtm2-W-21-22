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
            Citizen(int id,std::string first_name,std::string last_name,int year_of_birth ): id(id), first_name(first_name),
            last_name(last_name), year_of_birth(year_of_birth) {}
            int getId() const;
            std::string getFirstName()const;
            std::string getLastName()const;
            int getYearOfBirth()const;
    
            virtual std::ostream& printShort(std::ostream& stream) const =0;
            virtual std::ostream& printLong(std::ostream& stream) const =0;
            virtual std::shared_ptr<Citizen> clone() const = 0;
    
            friend bool operator==(const Citizen& Citizen1,const Citizen& Citizen2); 
            friend bool operator<(const Citizen& Citizen1,const Citizen& Citizen2);
            virtual ~Citizen() = default;

        
    };
    bool operator>(const Citizen& Citizen1,const Citizen& Citizen2);
    bool operator>=(const Citizen& Citizen1,const Citizen& Citizen2);
    bool operator<=(const Citizen& Citizen1,const Citizen& Citizen2);
    bool operator!=(const Citizen& Citizen1,const Citizen& Citizen2);


    // class CompareCitizens 
    // {
    //     public:
    //         bool operator()(Citizen* citizen1, Citizen* citizen2)
    //         {
    //             return citizen1->getId() < citizen2->getId(); 
    //         }
    // };

    class CompareCitizens 
    {
        public:
            bool operator()(std::shared_ptr<Citizen> citizen1, std::shared_ptr<Citizen> citizen2)
            {
                return citizen1->getId() < citizen2->getId(); 
            }
    };
}

#endif 