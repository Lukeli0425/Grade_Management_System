//
//  Course.cpp
//  Grade_Management_System
//
//  Created by Luke on 2021/7/20.
//

#include "Course.h"
#include "Student_Info.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool comp_ID(Student_Info a,Student_Info b){
     return a.get_ID() < b.get_ID();
}// 排序时的比较方法，ID从小到大排序

float Course::get_score(){ //计算平均分,加入求平均过程，因此要重新写
    score = 0;
    student_num = students.size();
    for(int i=0;i<student_num;i++)
        score += students[i].get_score();
    score = score/student_num;
    return score;
}

bool Course::delete_student(int ID){
    for(vector<Student_Info>::iterator it=students.begin(); it!=students.end(); ){
        if(it->get_ID() == ID) {
            it = students.erase(it);
            student_num --;//更新选课人数
            return true;
        }
        else{
            ++it;
        }
    }
    return false;
}

void Course::add_student(Student_Info student_info){
    students.push_back(student_info);
    student_num ++;
}

bool Course::change_score(int ID,float score,Student_Info stu){
    student_num = students.size();
    for(int i=0;i<student_num;i++){
        if(students[i].get_ID() == ID){
            students[i].set_score(score);
            return true;
        }
    }
    //若没有此学生则添加
    stu.set_score(score);
    students.push_back(stu);
    return true;
}

void Course::update_stu_dep(int id,int dep,int yr){  //更新学生院系年级
    student_num = students.size();
    for(int i=0;i<student_num;i++){
        if(students[i].get_ID() == id){
            students[i].set_department(dep);
            students[i].set_year(yr);
            break;
        }
    }
    return;
}

void Course::show_course(){
    cout<<"\n--------- Course Information ---------\n\n";
    cout<<setiosflags(ios::fixed);
    sort(students.begin(),students.end(),comp_ID);
    student_num = students.size();
    cout<<"Department:\t\t"<<department_name[department]<<endl;
    cout<<"ID:\t\t\t\t"<<ID<<endl;
    cout<<"Semester:\t\t"<<year<<"-"<<year+1<<"-"<<semester<<endl;
    cout<<"Course Name:\t"<<name<<endl;
    cout<<"Total students:\t"<<student_num<<endl;
    cout<<"Average Score:\t"<<setprecision(1)<<get_score()<<endl;
    for(int i=0;i<student_num;i++){
        cout<<"\n"<<i+1<<"\t"<<students[i].get_ID()<<"  ";
        cout<<setprecision(0)<<students[i].get_score()<<"\t";
        cout<<students[i].get_grade()<<"  ";
        cout<<setprecision(1)<<students[i].get_GPA()<<"  ";
        cout<<department_name[students[i].get_department()]<<"\t";
        cout<<students[i].get_name();
    }
    cout<<"\n\n--------- Course Information ---------\n";
    
    string cmd = "\n";
    cout<<"\nDownload course information? Enter 'yes' to download:\n";
    getline(cin,cmd);
    if(cmd == "yes"){  //将课程信息写在一个文件内
        string filepath = path + "crs_" + to_string(ID);  //文件路经
        filepath += ".txt";
        ofstream ci(filepath);
        
        ci<<"--------- Course Information ---------\n\n";
        ci<<setiosflags(ios::fixed);
        sort(students.begin(),students.end(),comp_ID);
        student_num = students.size();
        ci<<"Department:\t"<<department_name[department]<<endl;
        ci<<"ID:\t\t"<<ID<<endl;
        ci<<"Semester:\t"<<year<<"-"<<year+1<<"-"<<semester<<endl;
        ci<<"Course Name:\t"<<name<<endl;
        ci<<"Total students:\t"<<student_num<<endl;
        ci<<"Average Score:\t"<<setprecision(1)<<get_score()<<endl;
        for(int i=0;i<student_num;i++){
            ci<<"\n"<<i+1<<"\t"<<students[i].get_ID()<<"  ";
            ci<<setprecision(0)<<students[i].get_score()<<"\t";
            ci<<students[i].get_grade()<<"  ";
            ci<<setprecision(1)<<students[i].get_GPA()<<"  ";
            ci<<department_name[students[i].get_department()]<<"\t";
            ci<<students[i].get_name();
        }
        ci<<"\n\n--------- Course Information ---------\n";
        cout<<"\nCourse information exported to file: crs_"<<ID<<".txt\n";
    }
    return;
    
}


unsigned long Course::get_stu_num(){  //返回学生人数
    student_num = students.size();
    return student_num;
}

void Course::save(){  //保存课程
    student_num = students.size();
    crs_file<<ID<<" "<<name<<" "<<year<<" ";
    crs_file<<semester<<" "<<credit<<" "<<student_num<<"\n";
    for(int i=0;i<student_num;i++){
        crs_file<<students[i].get_department()<<" ";
        crs_file<<students[i].get_ID()<<" ";
        crs_file<<students[i].get_score()<<"\n";
    }
    crs_file<<endl;
}
