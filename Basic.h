//
//  Basic.h
//  Grade_Management_System
//
//  Created by Luke on 2021/7/20.
//

#ifndef Basic_h
#define Basic_h

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

extern int total_dep;
extern vector<string> department_name;
extern vector<string> dep_password;  //各个院系密码
extern string path;  //文件路径
extern fstream stu_file,crs_file;

class Basic{
public:
    Basic(int ID = 20000000,string name = "Alice",int year = 2000,int department = 0,int score = 0){
        this->ID = ID;
        this->name = name;
        this->year = year;
        this->department = department;
        this->score = score;
        this->caculate_GPA_grade();
        this->grade = "N/A";
    }
    ~Basic(){}
    
    //返回属性
    int get_ID();
    string get_name();
    int get_year();
    int get_department();
    virtual float get_score() = 0;  //虚函数
    virtual float get_GPA() = 0;  //虚函数
    string get_grade();
    
    //设置属性
    void set_ID(int ID);
    void set_name(string name);
    void set_year(int year);
    void set_department(int department);
    void set_score(float score);
    void caculate_GPA_grade();  // 根据百分制成绩计算等机制成绩和绩点
    
protected:
    int ID;             //学生/课程ID
    string name;        //学生/课程名称
    int year;           //学生年级/课程学年
    int department;     //学生/教师/课程所属院系编号
    float score;        //百分制成绩
    float GPA;          //绩点
    string grade;       //等级
};

#endif /* Basic_h */
