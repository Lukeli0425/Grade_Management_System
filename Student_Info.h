//
//  Student_Info.h
//  Grade_Management_System
//
//  Created by Luke on 2021/7/20.
//

#ifndef Student_Info_h
#define Student_Info_h

#include "Basic.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

class Student_Info: public Basic {
public:
    Student_Info(int ID = 20000000,string name = "None",int year = 2000,int department = 0,int score = 0,int gender = 0): Basic(ID,name,year,department,score),gender(gender){
    }
    ~Student_Info(){}
    
    //返回属性
    virtual float get_score();  //虚函数
    virtual float get_GPA();  //虚函数
    int get_gender();  //性别
    //设置属性
    void set_gender(int gender);

protected:
    int gender;//性别
};

#endif /* Student_Info_h */
