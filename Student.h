//
//  Student.hpp
//  Grade_Management_System
//
//  Created by Luke on 2021/7/20.
//

#ifndef Student_hpp
#define Student_hpp

#include "Course_Info.h"
#include "Student_Info.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

float grade2score(string grade);  //等级对应百分置成绩

class Student: public Student_Info {
public:
    Student(int ID = 20000000,string name = "None",int year = 2000,int department = 0,int score = 0,int gender = 0): Student_Info(ID,name,year,department,score,gender){
        courses.clear();
        rank = 0;
    }
    ~Student(){
        vector <Course_Info> CI;
        courses.swap(CI);
    }
    
    //返回属性
    virtual float get_GPA();//虚函数：计算学生总绩点，需要加权平均的过程
    virtual float get_score();//虚函数：计算学生总成绩，需要加权平均的过程
    int get_rank(); //获取排名
    int total_credit();  //总学分
    int total_course();  //总课程
    
    //修改属性
    void set_rank(int rank); //更新排名，由外部实时更新
    void add_course(Course_Info course_info);// 添加课程
    bool delete_course(int ID); // 删除课程
    bool change_score(int ID,int score,Course_Info crs);//修改某一课程的成绩
    void update_crs_dep();  //更新所修课程中所存储的院系
        
    //显示信息
    void show_student_info(); // 显示学生成绩信息
    void show_report_card(); // 显示学生所修课程信息（成绩单）
    
protected:
    vector<Course_Info> courses;// 所有课程
    int rank;
};

#endif /* Student_hpp */
