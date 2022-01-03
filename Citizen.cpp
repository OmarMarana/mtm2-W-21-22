#include "Citizen.h"



namespace mtm
{
    int Citizen::getId()const
    {
        return id;
    }
    std::string Citizen::getFirstName()const
    {
        return first_name;
    }
    std::string Citizen::getLastName()const
    {
        return last_name;
    }
    int Citizen::getBirthYear() const
    {
        return year_of_birth;
    }
    
    bool operator==(const Citizen& Citizen1,const Citizen& Citizen2)
    {
        return Citizen1.id == Citizen2.id;
    } 
    bool operator<(const Citizen& Citizen1,const Citizen& Citizen2)
    {
        return Citizen1.id < Citizen2.id;
    }
    bool operator>(const Citizen& Citizen1,const Citizen& Citizen2)
    {
        return ( (Citizen1 == Citizen2)==false && (Citizen1 < Citizen2)==false );
    }
    bool operator>=(const Citizen& Citizen1,const Citizen& Citizen2)
    {
        return (Citizen1 < Citizen2)==false;
    }
    bool operator<=(const Citizen& Citizen1,const Citizen& Citizen2)
    {
        return (Citizen1 > Citizen2)==false;
    }
    bool operator!=(const Citizen& Citizen1,const Citizen& Citizen2)
    {
        return (Citizen1 == Citizen2)==false;
    }
}