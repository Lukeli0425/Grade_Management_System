//
//  Course_Info.cpp
//  Grade_Management_System
//
//  Created by Luke on 2021/7/20.
//

#include "Course_Info.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

float Course_Info::get_score(){
    return this->score;
}

float Course_Info::get_GPA(){
    return this->GPA;
}

int Course_Info::get_credit(){
    return credit;
}

int Course_Info::get_semester(){
    return semester;
}
