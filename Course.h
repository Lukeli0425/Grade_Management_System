//
//  Course.h
//  Grade_Management_System
//
//  Created by Luke on 2021/7/20.
//

#ifndef Course_h
#define Course_h

#include "Course_Info.h"
#include "Student_Info.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

bool comp_ID(Student_Info a,Student_Info b);

class Course: public Course_Info {
public:
    Course(int ID = 20000000,string name = "None",int year = 0, int department = 0,int score = 0,int credit = 0,int semester = 1): Course_Info(ID,name,year,department,score,credit,semester){
        students.clear();
        student_num = 0;
    }
    ~Course(){
        vector <Student_Info> SI;
        students.swap(SI);
    }
    
    void add_student(Student_Info student_info);
    bool delete_student(int ID);
    bool change_score(int ID,float score,Student_Info stu);  //修改某一学生的成绩
    void update_stu_dep(int id,int dep,int yr);  //更新学生院系年级
    
    float get_score();  //计算平均分,加入求平均过程，因此要重新写
    unsigned long get_stu_num();  //返回学生人数
    
    void show_course();
    void save();  //保存课程
    
protected:
    vector<Student_Info> students;
    unsigned long student_num;  //选课学生人数
};

#endif /* Course_h */
