//
//  Department.h
//  Grade_Management_System
//
//  Created by Luke on 2021/7/21.
//

#ifndef Department_h
#define Department_h


#include "Student.h"
#include "Course.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

class Department{
public:
    Department(int number = 0,string name = "\0"):number(number),name(name){
        students.clear();
        courses.clear();
        stu_num.clear();
        crs_num.clear();
        vector<Student> empty_year;
        for(int i=0;i<30;i++){
            stu_num.push_back(0);
            students.push_back(empty_year);
        }
        vector<Course> empty_year_crs;
        for(int i=0;i<30;i++){
            crs_num.push_back(0);
            courses.push_back(empty_year_crs);
        }
        password = "12345678";
    }
    ~Department(){  //防止内存泄漏
        vector<Student> S;
        vector<vector<Student>> SS;
        vector<Course> C;
        vector<vector<Course>> CC;
        vector<unsigned long> I,J;
        for(int i=0;i<students.size();i++){
            students[i].swap(S);
        }
        students.swap(SS);
        stu_num.swap(J);
        for(int i=0;i<courses.size();i++){
            courses[i].swap(C);
        }
        courses.swap(CC);
        crs_num.swap(I);
    }
    
    //返回属性
    bool judge_stu(int ID,int year = -1);  //判断是否有此学生
    bool judge_crs(int ID,int year = -1);  //判断是否有此课程
    int get_stu_GPA(int year,int ID);  //查询学生的GPA
    int get_stu_rank(int year,int ID);  //查询学生的排名
    Student_Info stu_info(int ID);  //返回学生的Student_Info部分
    Course_Info crs_info(int ID);  //返回课程的Course_Info部分
    int total_stu();  //学生总人数
    int total_crs();  //总课程数
    string get_password(){  //返回密码
        return this->password;
    }
    
    //修改属性
    void set_name(string name);
    void set_number(int num);
    void set_password(string password){  //设置密码
        this->password = password;
    }
    void add_student(int year, Student student);  // 添加学生
    Student delete_student(int year,int ID);  // 删除学生
    void add_course(int year,Course course);  // 添加课程
    bool delete_course(int year,int ID);  // 删除课程
    bool change_score_crs(int crs_ID,int stu_ID,float score,Student_Info stu);  //修改某一课程某一学生的成绩
    bool change_score_stu(int stu_ID,int crs_ID,float score,Course_Info crs);  //修改某一学生某一课程的成绩
    bool change_year(int year,int ID,int des_dep);  //更改专业
    bool add_stu_course(int Id,Course_Info new_crs);  //为学生添加课程
    void update_rank();  //更新全部学生排名
    void update_crs_dep(int crs_id,int stu_id,int dep,int year);  //更新某一课程某一学生的院系年级
    
    //显示信息
    void show_year_class_info(int year);// 显示某一届学生的全部信息
    bool show_course_info(int year,int ID);  //显示课程信息
    bool show_stu_report(int ID,int year = -1);  //显示学生成绩单
    void save();  //保存到文件
    
protected:
    vector<vector<Student>> students;
    vector<unsigned long> stu_num;
    vector<vector<Course>> courses;
    vector<unsigned long> crs_num;
    
    string name;  //院系名称
    int number;  //院系编号，即school中索引
    string password;  //教工登录密码
};

#endif /* Department_h */
