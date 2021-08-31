//
//  Basic.cpp
//  Grade_Management_System
//
//  Created by Luke on 2021/8/3.
//

#include "Basic.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int total_dep = 0;
vector<string> department_name;
vector<string> dep_password;  //各个院系密码
string path = "/Users/Luke/Desktop/Grade_Management_System/";  //文件路径
fstream stu_file,crs_file;

void Basic::caculate_GPA_grade(){  // 根据百分制成绩计算等机制成绩和绩点
    if(score >= 90){
        GPA = 4.0;
        if(score == 100)
            grade = "A+";
        else if(score >= 95)
            grade = "A ";
        else
            grade = "A-";
    }
    else if(score >= 85){
        GPA = 3.6;
        grade = "B+";
    }
    else if(score >= 80){
        GPA = 3.3;
        grade = "B ";
    }
    else if(score >= 77){
        GPA = 3.0;
        grade = "B-";
    }
    else if(score >= 73){
        GPA = 2.6;
        grade = "C+";
    }
    else if(score >= 70){
        GPA = 2.3;
        grade = "C ";
    }
    else if(score >= 67){
        GPA = 2.0;
        grade = "C-";
    }
    else if(score >= 63){
        GPA = 1.6;
        grade = "D+";
    }
    else if(score >= 60){
        GPA = 1.3;
        grade = "D ";
    }
    else{
        GPA = 0;
        grade = "F ";
    }
    return;
}

int Basic::get_ID(){
    return this->ID;
}

string Basic::get_name(){
    return this->name;
}

int Basic::get_year(){
    return this->year;
}

int Basic::get_department(){
    return this->department;
}

string Basic::get_grade(){
    return this->grade;
}

void Basic::set_score(float score){
    this->score = score;
    this->caculate_GPA_grade();
}

void Basic::set_ID(int ID){
    this->ID = ID;
}

void Basic::set_name(string name){
    this->name = name;
}

void Basic::set_year(int year){
    this->year = year;
}

void Basic::set_department(int department){
    this->department = department;
}
