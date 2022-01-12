#include "/home/omarmarana/matam/Winter-21_22/mtm2-W-21-22/solution/Skill.h"
#include "/home/omarmarana/matam/Winter-21_22/mtm2-W-21-22/solution/Employee.h"
#include<iostream>
using namespace mtm;
using std::cout;
using std::endl;


int main(){
    Employee e1(1, "John", "Williams", 2002);
    cout << "Short Print" << endl;
    e1.printShort(cout);
    cout << "Long Print" << endl;
    e1.printLong(cout);
    cout << "----------" << endl;
    Skill s1(1,"C++",0);
    Skill s2(2, "Java", 0);
    e1.learnSkill(s1);
    e1.learnSkill(s2);
    cout << "Short Print" << endl;
    e1.printShort(cout);
    cout << "Long Print" << endl;
    e1.printLong(cout);
    return 0;
}
