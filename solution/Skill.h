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
        //return the id of skill
        int getId() const;
        //return the name of skill
        std::string getName() const;
        //return the required points to learn the skill
        int getRequiredPoints() const;
        //Increment the skill required_points by 1
        Skill operator++(int); 
        //Increment the skill required_points by delta
        Skill& operator+=(int delta);
        //opertaor plus to the left side
        friend Skill operator+(Skill skill,int points);
        //opertaor plus to the rigth side
        friend Skill operator+(int points,Skill skill);
        //print format for Skill
        friend std::ostream& operator<<(std::ostream& stream, const Skill& skill);
        // == for skill via ids
        friend bool operator==(const Skill& skill1,const Skill& skill2);
        //operator < via ids
        friend bool operator<(const Skill& skill1,const Skill& skill2);
    };
    //operator > via ids
    bool operator>(const Skill& skill1,const Skill& skill2);
    //operator >= via ids
    bool operator>=(const Skill& skill1,const Skill& skill2);
    //operator <= via ids
    bool operator<=(const Skill& skill1,const Skill& skill2);
    //operator != via ids
    bool operator!=(const Skill& skill1,const Skill& skill2);
}

#endif