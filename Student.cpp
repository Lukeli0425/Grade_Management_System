//
//  Student.cpp
//  Grade_Management_System
//
//  Created by Luke on 2021/7/20.
//

#include "Student.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

//工具函数定义
float grade2score(string grade){  //等级对应百分置成绩
    if(grade == "A+")
       return 100;
    else if(grade == "A ")
        return 95;
    else if(grade == "A-")
        return 92;
    else if(grade == "B+")
        return 87;
    else if(grade == "B ")
        return 82;
    else if(grade == "B-")
        return 78;
    else if(grade == "C+")
        return 75;
    else if(grade == "C ")
        return 71;
    else if(grade == "C-")
        return 68;
    else if(grade == "D+")
        return 65;
    else if(grade == "D ")
        return 61;
    else
        return 0;
}

//获得属性
float Student::get_GPA(){
    int total_credit = 0;
    GPA = 0;
    if (!courses.empty()){
        unsigned long course_number = this->courses.size();
        for(int i=0; i<course_number; i++){
            total_credit += courses[i].get_credit();
            GPA += courses[i].get_credit() * courses[i].get_GPA();
        }
        GPA = GPA/float(total_credit);
    }
    return GPA;
}

float Student::get_score(){
    int total_credit = 0;
    score = 0;
    if (!courses.empty()){
        unsigned long course_number = this->courses.size();
        for(int i=0; i<course_number; i++){
            total_credit += courses[i].get_credit();
            score += courses[i].get_credit() * grade2score(courses[i].get_grade());
        }
        score = score/float(total_credit);
    }
    return score;
}

int Student::get_rank(){
    return this->rank;
}

int Student::total_credit(){  //总学分
    int total_credit = 0;
    if (!courses.empty()){
        unsigned long course_number = courses.size();
        for(int i=0; i<course_number; i++){
            total_credit += courses[i].get_credit();
        }
    }
    return total_credit;
}

int Student::total_course(){  //总课程
    int total_crs = 0;
    unsigned long course_number = courses.size();
    for(int i=0; i<course_number; i++){
        total_crs += 1;
    }
    return total_crs;
}

//修改属性
void Student::set_rank(int rank){
    this->rank = rank;
}

void Student::add_course(Course_Info course_info){ //添加课程
    courses.push_back(course_info);
}

bool Student::delete_course(int ID){ //删除课程
    for(vector<Course_Info>::iterator it=courses.begin(); it!=courses.end(); ){
        if(it->get_ID() == ID) {
            it = courses.erase(it);
            return true;
        }
        else{
            ++it;
        }
    }
    return false;
}

bool Student::change_score(int ID,int score,Course_Info crs){//修改某一课程的成绩
    unsigned long crs_num = courses.size();
    for(int i=0;i<crs_num;i++){
        if(courses[i].get_ID() == ID){
            courses[i].set_score(score);
            return true;
        }
    }
    //如果不存在课程则添加
    crs.set_score(score);
    courses.push_back(crs);
    return false;
}



void Student::show_student_info(){ //显示学生个人信息
    cout<<"\n--------- Student Information ---------\n\n";
    cout<<setiosflags(ios::fixed);
    cout<<"Department:\t"<<department_name[department]<<"\n";
    cout<<"ID:\t"<<ID<<endl;
    cout<<"Name:\t"<<name<<""<<endl;
    cout<<"Year:\t"<<year<<endl;
    cout<<"GPA:\t"<<setprecision(3)<<get_GPA()<<endl;
    cout<<"Score:\t"<<setprecision(2)<<get_score()<<endl;
    cout<<"Rank:\t"<<rank<<endl;
    cout<<"\n--------- Student Information ---------\n";
}

void Student::show_report_card(){  //显示学生课程信息（成绩单）
    cout<<"\n--------- Student Report Card ---------\n\n";
    //基本信息
    cout<<setiosflags(ios::fixed);
    cout<<"Department:\t\t"<<department_name[department]<<""<<endl;
    cout<<"ID:\t\t\t\t"<<ID<<endl;
    cout<<"Name:\t\t\t"<<name<<endl;
    cout<<"Year:\t\t\t"<<year<<endl;
    cout<<"GPA:\t\t\t"<<setprecision(3)<<get_GPA()<<endl;
    cout<<"Score:\t\t\t"<<setprecision(2)<<get_score()<<endl;
    cout<<"Total Credit:\t"<<setprecision(0)<<total_credit()<<endl;
    cout<<"Rank:\t\t\t"<<rank<<endl;
    unsigned long course_number = this->courses.size();
    for(int i=0; i<course_number; i++){
        cout<<"\n"<<i+1<<"  "<<courses[i].get_ID()<<"  ";
        cout<<courses[i].get_year()<<"-"<<courses[i].get_year()+1<<"-"<<courses[i].get_semester()<<"  ";
        cout<<setprecision(0)<<courses[i].get_credit()<<"  ";
        cout<<setprecision(0)<<courses[i].get_score()<<"\t";
        cout<<courses[i].get_grade()<<"  ";
        cout<<setprecision(1)<<courses[i].get_GPA()<<"  ";
        cout<<left<<courses[i].get_name();
    }
    cout<<"\n\n--------- Student Report Card ---------\n";
    
    
    string cmd = "\n";
    cout<<"\nDownload report card? Enter 'yes' to download:\n";
    getline(cin,cmd);
    if(cmd == "yes"){  //将成绩单写在一个文件内
        string filepath = path + "stu_" + to_string(ID);  //文件路经
        filepath += ".txt";
        ofstream rc(filepath);
        
        rc<<"--------- Student Report Card ---------\n\n";
        //基本信息
        rc<<setiosflags(ios::fixed);
        rc<<"Department:\t"<<department_name[department]<<""<<endl;
        rc<<"ID:\t\t"<<ID<<endl;
        rc<<"Name:\t\t"<<name<<endl;
        rc<<"Year:\t\t"<<year<<endl;
        rc<<"GPA:\t\t"<<setprecision(3)<<get_GPA()<<endl;
        rc<<"Score:\t\t"<<setprecision(2)<<get_score()<<endl;
        rc<<"Total Credit:\t"<<setprecision(0)<<total_credit()<<endl;
        rc<<"Rank:\t\t"<<rank<<endl;
        unsigned long course_number = this->courses.size();
        for(int i=0; i<course_number; i++){
            rc<<"\n"<<i+1<<"  "<<courses[i].get_ID()<<"  ";
            rc<<courses[i].get_year()<<"-"<<courses[i].get_year()+1<<"-"<<courses[i].get_semester()<<"  ";
            rc<<setprecision(0)<<courses[i].get_credit()<<"  ";
            rc<<setprecision(0)<<courses[i].get_score()<<"\t";
            rc<<courses[i].get_grade()<<"  ";
            rc<<setprecision(1)<<courses[i].get_GPA()<<"  ";
            rc<<left<<courses[i].get_name();
        }
        rc<<"\n\n--------- Student Report Card ---------\n";
        cout<<"\nReport Card exported to file: stu_"<<ID<<".txt\n";
    }
    return;
}
