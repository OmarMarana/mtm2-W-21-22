#ifndef SKILL_H
#define SKILL_H
#include <string>


namespace mtm
{
    class Skill
    {
        private:
            int id;
            std::string name;
            int required_points;
        
        public:
        Skill(int id, std::string name, int required_points) : id(id), name(name), required_points(required_points){};
        int getId();
        std::string getName();
        int getRequiredPoints();
        Skill& operator++(int); // postfix ++
        Skill& operator+=(const Skill& skill1);
        friend Skill operator+(const Skill& skill1,int points);
        friend std::ostream& operator<<(std::ostream& stream, const Skill& skill);
        friend bool operator==(const Skill& skill1,const Skill& skill2);
        friend bool operator<(const Skill& skill1,const Skill& skill2);
    };
    bool operator>(const Skill& skill1,const Skill& skill2);
    bool operator>=(const Skill& skill1,const Skill& skill2);
    bool operator<=(const Skill& skill1,const Skill& skill2);
    bool operator!=(const Skill& skill1,const Skill& skill2);

}

#endif