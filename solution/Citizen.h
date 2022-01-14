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
            //constructor
            Citizen(int id,std::string first_name,std::string last_name,int year_of_birth ): id(id), first_name(first_name),
            last_name(last_name), year_of_birth(year_of_birth) {}
            // return id
            int getId() const;
            //return first_name
            std::string getFirstName()const;
            //return //return first_name
            std::string getLastName()const;
            //return year_of_birth
            int getBirthYear()const;
            //print short desciption of citizen
            virtual std::ostream& printShort(std::ostream& stream) const =0;
            //print long desciption of citizen
            virtual std::ostream& printLong(std::ostream& stream) const =0;
            //clone the citizen
            virtual Citizen* clone() const = 0;
            //compare via ids
            friend bool operator==(const Citizen& Citizen1,const Citizen& Citizen2); 
            friend bool operator<(const Citizen& Citizen1,const Citizen& Citizen2);
            //destructor
            virtual ~Citizen() = default;

        
    };
    //compare Citizen operators via ids
    bool operator>(const Citizen& Citizen1,const Citizen& Citizen2);
    bool operator>=(const Citizen& Citizen1,const Citizen& Citizen2);
    bool operator<=(const Citizen& Citizen1,const Citizen& Citizen2);
    bool operator!=(const Citizen& Citizen1,const Citizen& Citizen2);


    class CompareCitizens 
    {
        public:
            bool operator()(Citizen* citizen1, Citizen* citizen2)
            {
                return citizen1->getId() < citizen2->getId(); 
            }
    };
}

#endif 