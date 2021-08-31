//
//  Student_Info.cpp
//  Grade_Management_System
//
//  Created by Luke on 2021/7/20.
//

#include "Student_Info.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

float Student_Info::get_score(){
    return this->score;
}

float Student_Info::get_GPA(){
    return this->GPA;
}

int Student_Info::get_gender(){//返回性别
    return this->gender;
}

void Student_Info::set_gender(int gender){//设置性别
    this->gender = gender;
}
