//
//  Department.cpp
//  Grade_Management_System
//
//  Created by Luke on 2021/7/21.
//

#include "Department.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

bool comp_GPA(Student a,Student b){
     return a.get_GPA() > b.get_GPA();
}// 排序时的比较方法，GPA从大到小排序

bool Department::judge_stu(int ID,int year) {  //判断是否有此学生
    if(year >= 2000){
        int y = year-2000;
        stu_num[y] = students[y].size();  //更新一下该年级人数
        for(int i=0;i<stu_num[y];i++) {
            if(students[y][i].get_ID() == ID){
                return true;
            }
        }
    }
    else {
        for(int y=0;y<30;y++){
            stu_num[y] = students[y].size();  //更新一下该年级人数
            for(int i=0;i<stu_num[y];i++) {
                if(students[y][i].get_ID() == ID){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Department::judge_crs(int ID,int year){  //判断是否有此课程
    if(year >= 2000){
        int y = year-2000;
        crs_num[y] = courses[y].size();  //更新一下课程数
        for(int i=0;i<crs_num[y];i++){
            if(courses[y][i].get_ID() == ID){
                return true;
            }
        }
    }
    else{
        for(int y=0;y<30;y++){
            crs_num[y] = courses[y].size();  //更新一下该年级人数
            for(int i=0;i<crs_num[y];i++) {
                if(courses[y][i].get_ID() == ID){
                    return true;
                }
            }
        }
    }
    return false;
}

int Department::get_stu_GPA(int year,int ID){  //查询学生的GPA
    stu_num[year-2000] = students[year-2000].size();  //更新一下该年级人数
    for(int i=0;i<stu_num[year-2000];i++){
        if(students[year-2000][i].get_ID() == ID){
            return students[year-2000][i].get_GPA();
        }
    }
    return -1;  //查无此人，返回-1
}

int Department::get_stu_rank(int year,int ID){ // 查询学生的排名
    stu_num[year-2000] = students[year-2000].size();//更新一下该年级人数
    sort(students[year-2000].begin(),students[year-2000].end(),comp_GPA);
    int last=1;//前一位排名，处理并列情况
    for(int i=0;i<stu_num[year-2000];i++){
        if(i>0 && students[year-2000][i].get_GPA() == students[year-2000][i-1].get_GPA()){ //与上一位成绩相同
            if(students[year-2000][i].get_ID() == ID)
                return last;
        }
        else{ //与上一位成绩不同
            last = i+1;
            if(students[year-2000][i].get_ID() == ID)
                return i+1;
        }
    }
    return -1;  //查无此人，返回-1
}

Student_Info Department::stu_info(int ID){  //返回学生的Student_Info部分
    for(int y=0;y<30;y++){
        stu_num[y] = students[y].size();
        for(int i=0;i<stu_num[y];i++){
            if(students[y][i].get_ID() == ID){
                return students[y][i];
            }
        }
    }
    return Student_Info(00000000,"Error",2000,0,0,0);  //查无此学生
}

Course_Info Department::crs_info(int ID){  //返回课程的Course_Info部分
    for(int y=0;y<30;y++){
        crs_num[y] = courses[y].size();
        for(int i=0;i<crs_num[y];i++){
            if(courses[y][i].get_ID() == ID){
                return courses[y][i];
            }
        }
    }
    return Course_Info(00000000,"Error",2000,0,0,0);  //查无此课程
}

int Department::total_stu(){  //学生总人数
    int total_stu = 0;
    for(int y=0;y<30;y++){
        total_stu += students[y].size();
    }
    return total_stu;
}

int Department::total_crs(){  //总课程数
    int total_crs = 0;
    for(int y=0;y<30;y++){
        total_crs += courses[y].size();
    }
    return total_crs;
}


//修改属性

void Department::set_name(string name){
    this->name = name;
}

void Department::set_number(int num){
    this->number = num;
}

void Department::add_student(int year, Student new_stu){//添加学生
    students[year-2000].push_back(new_stu);
    stu_num[year-2000] ++;
}

Student Department::delete_student(int year,int ID){  //删除学生
    for(vector<Student>::iterator it=students[year-2000].begin(); it!=students[year-2000].end(); ){
        if(it->get_ID() == ID) {
            Student stu = *it;
            it = students[year-2000].erase(it);
            stu_num[year-2000] --;//更新人数
            return stu;
        }
        else{
            ++it;
        }
    }
    return Student(00000000,"Error",2000);
}

void Department::add_course(int year,Course new_course){
    courses[year-2000].push_back(new_course);
    crs_num[year-2000]++;
}// 添加课程

bool Department::delete_course(int year,int ID){
    for(vector<Course>::iterator it=courses[year-2000].begin(); it!=courses[year-2000].end(); ){
        if(it->get_ID() == ID) {
            it = courses[year-2000].erase(it);
            return true;
        }
        else{
            ++it;
        }
    }
    return false;
}// 删除课程

bool Department::change_score_crs(int crs_ID,int stu_ID,float score,Student_Info stu){  //修改某一课程某一学生的成绩
    //修改Course
    for(int y=0;y<30;y++){
        crs_num[y] = courses[y].size();
        for(int i=0;i<crs_num[y];i++){
            if(courses[y][i].get_ID() == crs_ID){
                courses[y][i].change_score(stu_ID,score,stu);
                return true;
            }
        }
    }
    return false;
}

bool Department::change_score_stu(int stu_ID,int crs_ID,float score,Course_Info crs){   //修改某一学生某一课程的成绩
    //修改Student
    for(int y=0;y<30;y++){
        stu_num[y] = students[y].size();
        for(int i=0;i<stu_num[y];i++){
            if(students[y][i].get_ID() == stu_ID){
                students[y][i].change_score(crs_ID,score,crs);
                return true;
            }
        }
    }
    return false;
}

bool Department::change_year(int year,int ID,int des_year){  //更改专业
    Student temp;
    for(vector<Student>::iterator it=students[year-2000].begin(); it!=students[year-2000].end(); ){
        if(it->get_ID() == ID){
            temp = *it;
            it = students[year-2000].erase(it);
            stu_num[year-2000] --;//更新人数
            temp.set_year(des_year);//更新年级
            add_student(des_year,temp);//加入新年级
            return true;
        }
        else{
            ++it;
        }
    }
    return false;
}

bool Department::add_stu_course(int ID, Course_Info new_crs){  //为学生添加课程
    for(int y=0;y<30;y++){
        stu_num[y] = students[y].size();
        for(int i=0;i<stu_num[y];i++){
            if(students[y][i].get_ID() == ID){
                students[y][i].add_course(new_crs);
                return true;
            }
        }
    }
    cout<<"Student not found!";
    return false;
}

void Department::update_rank(){  //更新排名
    for(int y=0;y<30;y++){
        stu_num[y] = students[y].size();//更新一下该年级人数
        sort(students[y].begin(),students[y].end(),comp_GPA);
        int last=1;//前一位排名，处理并列情况
        for(int i=0;i<stu_num[y];i++){
            if(i>0 && students[y][i].get_GPA() == students[y][i-1].get_GPA()){ //与上一位成绩相同
                students[y][i].set_rank(last);
            }
            else{ //与上一位成绩不同
                last = i+1;
                students[y][i].set_rank(i+1);
            }
        }
    }
}

void Department::update_crs_dep(int crs_id,int stu_id,int dep,int year){  //更新某一课程某一学生的院系年级
    for(int y=0;y<30;y++){
        for(int i=0;i<courses[y].size();i++)
        {
            if(courses[y][i].get_ID() == crs_id){
                courses[y][i].update_stu_dep(stu_id,dep,year);
                break;
            }
        }
    }
    return;
}

void Department::show_year_class_info(int year){  //显示某一届学生的全部信息
    cout<<setiosflags(ios::fixed);
    cout<<"\n--------- Student Information ---------\n\n";
    sort(students[year-2000].begin(),students[year-2000].end(),comp_GPA);
    stu_num[year-2000] = students[year-2000].size();//更新一下该年级人数
    cout<<"Department: "<<name<<"\nClass of "<<year<<endl;
    cout<<"Total Students: "<<students[year-2000].size()<<endl;
    int last=1;//前一位排名，处理并列情况
    for(int i=0;i<stu_num[year-2000];i++){
        if(i>0 && students[year-2000][i].get_GPA() == students[year-2000][i-1].get_GPA()){
            cout<<"\n"<<last;
        }
        else{
            cout<<"\n"<<i+1;last = i+1;
        }
        cout<<"  "<<students[year-2000][i].get_ID()<<"  ";
        cout<<students[year-2000][i].get_name()<<"\t";
        cout<<setprecision(3)<<students[year-2000][i].get_GPA()<<"  ";
        cout<<setprecision(2)<<students[year-2000][i].get_score();
    }
    cout<<"\n\n--------- Student Information ---------"<<endl;
}

bool Department::show_course_info(int year,int ID){  //显示某一课程的全部信息
    for(int i=0;i<courses[year-2000].size();i++){
        if(courses[year-2000][i].get_ID() == ID){
            courses[year-2000][i].show_course();
            return true;
        }
    }
    cout<<"Course not found!";
    return false;
}

bool Department::show_stu_report(int ID,int year){ //显示学生成绩单
    if(year >= 2000){
        int y = year-2000;
        for(int i=0;i<students[y].size();i++){
            if(students[y][i].get_ID() == ID){
                students[y][i].show_report_card();
                return true;
            }
        }
    }
    else{
        for(int y=0;y<30;y++){
            for(int i=0;i<students[y].size();i++){
                if(students[y][i].get_ID() == ID){
                    students[y][i].show_report_card();
                    return true;
                }
            }
        }
    }
    cout<<"Student not found!";
    return false;
}

void Department::save(){
    //Student
    stu_file<<name<<endl;
    stu_file<<number<<" "<<password<<"\n";
    stu_file<<total_stu()<<"\n";
    for(int y=0;y<30;y++){  //依次写入全部学生
        for(int i=0;i<students[y].size();i++){
            stu_file<<students[y][i].get_ID()<<" ";
            stu_file<<students[y][i].get_name()<<" ";
            stu_file<<students[y][i].get_year()<<" ";
            stu_file<<students[y][i].get_gender()<<"\n";
        }
    }
    cout<<"Finished Student Information Export: "<<name<<endl;
    //Course
    crs_file<<total_crs()<<"\n\n";
    for(int y=0;y<30;y++){  //依次写入全部课程
        for(int i=0;i<courses[y].size();i++){  //写入课程中的学生及成绩
            courses[y][i].save();
        }
    }
    cout<<"Finished Course Information Export: "<<name<<endl;
}
