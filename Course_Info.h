//
//  Course_Info.h
//  Grade_Management_System
//
//  Created by Luke on 2021/7/20.
//

#ifndef Course_Info_h
#define Course_Info_h

#include "Basic.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

class Course_Info: public Basic {
public:
    Course_Info(int ID = 20000000,string name = "None",int year = 0, int department = 0,int score = 0,int credit = 0,int semester = 1): Basic(ID,name,year,department,score),credit(credit),semester(semester){
        this->caculate_GPA_grade();
    }
    ~Course_Info(){}
    //返回属性
    virtual float get_score();
    virtual float get_GPA();
    int get_credit();
    int get_semester();
    //设置属性
protected:
    int credit;// 课程学分
    int semester;// 课程学期（1/2/3）
};

#endif /* Course_Info_h */
