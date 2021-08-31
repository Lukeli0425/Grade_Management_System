//
//  function.cpp
//  Grade_Management_System
//
//  Created by Luke on 2021/8/9.
//

#include "functions.h"
#include "Department.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

vector<Department> school;
string password;  //教工登录密码
int state = 0;  //登录状态
int user_id = 0;  //学生/教工ID
int year = 0;  //学生年级
int dep = 0;  //学生/教工院系

void inialization(){  //读入文件，初始化院系（名称、编号、学生、课程）
    string stu_file_path = path + "Student.txt";
    stu_file.open(stu_file_path);
    if(!stu_file.is_open()){  //文件打开不成功则退出程序
        cout<<"Student File Error!\n\n";exit(0);
    }
    //读入Student文件
    string dep_name,stu_name,dep_pw;
    int total_stu=0,dep_code=0,yr=0,id=0,gd=0;
    stu_file>>total_dep;  //总院系数
    stu_file>>password;  //密码
    for(int i=0;i<total_dep;i++){  //依次读取院系信息
        getline(stu_file,dep_name);
        getline(stu_file,dep_name);
        stu_file>>dep_code>>dep_pw>>total_stu;
        department_name.push_back(dep_name);  //存储院系名称
        dep_password.push_back(dep_pw);  //存储密码
        Department temp(i,dep_name);  //构建院系对象
        temp.set_password(dep_pw);
        for(int j=0;j<total_stu;j++){  //依次读取全部学生
            stu_file>>id>>stu_name>>yr>>gd;
            temp.add_student(yr,Student(id,stu_name,yr,i,0,gd));
        }
        school.push_back(temp);
        cout<<"Finished Student Import: "<<dep_name<<endl;
    }
    stu_file.close();
    cout<<endl;
    //读入Course文件
    string crs_file_path = path +"Course.txt";
    crs_file.open(crs_file_path);
    if(!crs_file.is_open()){  //文件打开不成功则退出程序
        cout<<"\nCourse File Error!\n\n";exit(0);
    }
    int total_crs=0,crs_id=0,sem=0,cre=0,stu_num=0,stu_dep=0,score=0;
    string crs_name;
    for(int i=0;i<total_dep;i++){
        crs_file>>total_crs;
        for(int j=0;j<total_crs;j++){  //依次读取全部课程
            crs_file>>crs_id>>crs_name>>yr>>sem>>cre>>stu_num;
            Course crs(crs_id,crs_name,yr,i,0,cre,sem);
            for(int k=0;k<stu_num;k++){  //读取课程中的学生及成绩
                crs_file>>stu_dep>>id>>score;
                crs.add_student(school[stu_dep].stu_info(id));
                crs.change_score(id,score,Student());
                Course_Info crs_info(crs_id,crs_name,yr,i,score,cre,sem);
                school[stu_dep].add_stu_course(id,crs_info);
            }
            crs.get_score();  //更新课程均分
            school[i].add_course(yr,crs);
            cout<<"Finished Course Information Import: "<<crs_name<<endl;
        }
        cout<<"Finished Course Import: "<<department_name[i]<<endl;
    }
    crs_file.close();
    cout<<"\nInitialization Success!\n\n";
}

bool judge_stu(int id){  //判断学生是否已经存在
    for(int i=0;i<total_dep;i++){
        for(int y=2000;y<2030;y++){
            if(school[i].judge_stu(id,y)){
                return true;
            }
        }
    }
    return false;
}

bool judge_crs(int id) {  //判断课程是否已经存在
    for(int i=0;i<total_dep;i++){
        for(int j=2000;j<2030;j++){
            if(school[i].judge_crs(id,j)){
                return true;
            }
        }
    }
    return false;
}

int get_dep() {  //读入院系（含异常处理）
    int dep_num;
    string str;
    
    getline(cin, str);
    try {
        if (str.size() != 1 && str.size() != 2)  //处理dep位数不对
            throw 1;
        for (int i = 0; i < str.size(); i++){  //处理含有非数字输入
            if(str[i] < 48 || str[i] > 57)
                throw 2;
        }
        dep_num = atoi(str.c_str());  //输入正确，返回该整数
        if(dep_num < 0 || dep_num >= total_dep) //处理0开头的非0输入
            throw 3;
    }
    catch (int) {
        cout<<"\nInput error!\n";
        for(int i=0;i<total_dep;i++){  //显示全部院系号
            cout<<i<<" - "<<department_name[i]<<"\n";
        }
        cout<<"Please enter a correct department code: ";
        dep_num = get_dep();
    }
    return dep_num;
}

int get_ID(){ //读入ID（含异常处理）
    int id;
    string str;
    getline(cin, str);
    try {
        if (str.size() != 8) //处理ID位数不对
            throw 1;
        for (int i = 0; i < str.size(); i++){ // 处理含有非数字输入
            if((str[i] < 48 || str[i] > 57) && !(i == 0 && str[i] == '-'))
                throw 2;
        }
        if(str[0] == '0' && str.size() != 1) //处理0开头的非0输入
            throw 3;
        id = atoi(str.c_str());  // 输入正确，返回该整数
    }
    catch (int) {
        cout << "\nInput error! Please enter a correct ID: ";
        id = get_ID();
    }
    return id;
}

int get_year(){ //读入年级（含异常处理）
    int yr;
    string str;
    getline(cin, str);
    try {
        if (str.size() != 4) //处理ID位数不对
            throw 1;
        for (int i = 0; i < str.size(); i++){ // 处理含有非数字输入
            if(str[i] < 48 || str[i] > 57)
                throw 2;
        }
        yr = atoi(str.c_str());  // 输入正确，返回该整数
        if(yr<2000 || yr > 2030)  //不合理年级
            throw 3;
    }
    catch (int) {
        cout << "\nInput error! Please enter a correct year: ";
        yr = get_year();
    }
    return yr;
}

int get_gd(){  //读入性别，含异常处理
    int gd = -1;
    string str;
    getline(cin, str);
    try {
        if (str.size() != 1)  //处理gd位数不对
            throw 1;
        if(str[0] != '0' && str[0] != '1')
            throw 2;
        gd = atoi(str.c_str());  // 输入正确，返回该整数
    }
    catch (int) {
        cout<<"\nInput error! Please enter 0/1: ";
        gd = get_gd();
    }
    return gd;
}

int get_sem(){  //读入学期，含异常处理
    int sem = -1;
    string str;
    getline(cin, str);
    try {
        if (str.size() != 1)  //位数不对
            throw 1;
        if(str[0] != '1' && str[0] != '2' && str[0] != '3')
            throw 2;
        sem = atoi(str.c_str());// 输入正确，返回该整数
    }
    catch (int) {
        cout<<"\nInput error! Please enter 1/2/3: ";
        sem = get_sem();
    }
    return sem;
}

int get_cre(){  //读入学分，含异常处理
    int cre = -1;
    string str;
    getline(cin, str);
    try {
        if (str.size() != 1)  //位数不对
            throw 1;
        if(str[0] != '0' && str[0] != '1' && str[0] != '2' && str[0] != '3' && str[0] != '4' && str[0] != '4')
            throw 2;
        cre = atoi(str.c_str());  //输入正确，返回该整数
    }
    catch (int) {
        cout<<"\nInput error! Please enter a correct credit: ";
        cre = get_cre();
    }
    return cre;
}

float get_score(){  //读入成绩
    int score = -1;
    string str;
    getline(cin, str);
    try {
        if (str.size() != 2 && str.size() != 3)  //位数不对
            throw 1;
        for (int i = 0; i < str.size(); i++){  //处理含有非数字输入
            if(str[i] < 48 || str[i] > 57)
                throw 2;
        }
        score = atoi(str.c_str());  //输入正确，返回该整数
        if(score<0 || score>100)  //成绩在范围之外
            throw 3;
    }
    catch (int) {
        cout<<"\nInput error! Please enter a correct score: ";
        score = get_score();
    }
    return float(score);
}

void stu_login(){  //学生登录（含检查信息是否正确）
    cout<<"\nPlease enter your department code: ";
    dep = get_dep();  //读入学生院系
    cout<<"\nPlease enter your year: ";  //登录时保留输入年级
    year = get_year();  //读入学生年级
    cout<<"\nPlease enter your ID: ";
    user_id = get_ID();  //读入学生ID
    if(! school[dep].judge_stu(user_id,year)){
        cout<<"\nStudent not found!\n\n";
        cout<<"------ Login Failed! ------\n";
        login();
    }
}

void staff_login(){  //教工登录（含检查密码是否正确）
    string pw,cmd="yes";
    cout<<"\nPlease enter your department code: ";
    dep = get_dep();  //读入教工院系
    cout<<"\nPlease enter department password: ";
    //user_id = get_ID();  //读入教工ID
    getline(cin,pw);
    if(pw != dep_password[dep]){
        cout<<"\nWrong password!\n\n";
        cout<<"------ Login Failed! ------\n";
        login();
    }
}

void ad_login(){  //管理员登录（含检查密码是否正确）
    string pw,cmd="yes";
    cout<<"\nPlease enter administrator password: ";
    getline(cin,pw);
    if(pw != password){
        cout<<"\nWrong password!\n\n";
        cout<<"------ Login Failed! ------\n";
        login();
    }
}

void login(){  //登录
    string str = "\0";
    state = -1;
    cout<<"\n------- Login -------\n";
    cout<<"0 - exit\n";
    cout<<"1 - login as student\n";
    cout<<"2 - login as school staff\n";
    cout<<"3 - login as administrator\n";
    cout<<"\nPlease enter 0/1/2/3: ";
    do{
        getline(cin, str);
        try {
            if(str != "0" && str != "1" && str != "2" && str != "3")
                throw 1;
            else
                state = atoi(str.c_str());
        }
        catch(int) {
            cout<<"\nInput error! Please enter 0/1/2/3: ";
        }
    } while(state == -1);
    
    switch (state) {
        case 1:
            cout<<"\n------ Login as student ------\n";
            stu_login();
            break;
        case 2:
            cout<<"\n------ Login as school staff ------\n";
            staff_login();
            break;
        case 3:
            cout<<"\n------ Login as administrator ------\n";
            ad_login();
            break;
        default:
            cout<<"\n------ Exit ------\n";
            save_changes();
            cout<<"\nThank you for using Grade Management System!\n\n";
            exit(0);
            break;
    }
}

void operation(){  //完成 查询信息/录入信息/导出信息 等操作
    int op = -1;
    string str;
    cout<<"\n------ Login success! ------\n";
    while (op != 0){
        cout<<"\n0 - Exit\n";
        cout<<"1 - Student report card\n";
        cout<<"2 - Student information query (staff only)\n";
        cout<<"3 - Course information query (staff only)\n";
        cout<<"4 - Enter student's score (staff only)\n";
        cout<<"5 - Add student information (staff only)\n";
        cout<<"6 - Delete student (staff only)\n";
        cout<<"7 - Add course information (staff only)\n";
        cout<<"8 - Delete course (staff only)\n";
        cout<<"9 - Change Student Department (administrator only)\n";
        cout<<"\nPlease enter the operation you wish to perform: ";
        do{  //读入操作op
            op = -1;  //读入前需要归零
            getline(cin, str);
            try {
                if(str != "0" && str != "1" && str != "2" && str != "3"&& str != "4" && str != "5"&& str != "6" && str != "7" && str != "8" && str != "9")
                    throw 1;
                else
                    op = atoi(str.c_str());
            }
            catch(int) {
                cout<<"\nInput error! Please enter 0/1/2/3/4/5/6/7/8/9: ";
            }
        } while(op == -1);
        
        switch (op) {
            case 1:  //学生成绩单
                if(state == 1){  //学生登陆时只显示自己的信息
                    school[dep].update_rank();  //更新排名
                    school[dep].show_stu_report(user_id);
                }
                else  //教工登录时输入需要查询的学生
                    stu_report_query();
                break;
            case 2:  //学生信息查询
                if(state != 1){
                    stu_info_query();
                }
                else { //学生无权限
                    cout<<"\nSorry,you have no access to student information.\n";
                }
                break;
            case 3: //课程信息查询
                if(state != 1)
                    crs_info_query();
                else {
                    cout<<"\nSorry,you have no access to course information.\n";
                }
                break;
            case 4:  //录入学生课程成绩
                if(state != 1)
                    enter_stu_score();
                else {
                    cout<<"\nSorry,you have no authority to enter student's score.\n";
                }
                break;
            case 5:  //添加学生信息
                if(state != 1)
                    add_stu();
                else {
                    cout<<"\nSorry,you have no authority to add student information.\n";
                }
                break;
            case 6:  //删除学生信息
                if(state != 1)
                    delete_stu();
                else {
                    cout<<"\nSorry,you have no authority to delete student information.\n";
                }
                break;
            case 7:  //添加课程信息
                if(state != 1)
                    add_crs();
                else {
                    cout<<"\nSorry,you have no authority to add course information.\n";
                }
                break;
            case 8:  //删除课程信息
                if(state != 1)
                    delete_crs();
                else {
                    cout<<"\nSorry,you have no authority to delete course information.\n";
                }
                break;
            case 9:  //学生院系变化
                if(state == 3)
                    change_stu_dep();
                else {
                    cout<<"\nSorry,you have no authority to change student department.\n";
                }
                break;
            default:  //回到登录页面
                login();
                operation();
                break;
        }
    }
    return;
}

void stu_report_query(){  //（教工）查询学生成绩单:1
    cout<<"\n\n--------- Student Report Card Query ---------\n";
    int dep_num=0,id=0;
    string cmd = "yes",str;
    while(cmd == "yes"){
        if(state == 3){  //管理员能查询任何院系的学生
            cout<<"\nPlease enter student's department code: ";
            dep_num = get_dep();
        }
        else{  //教师登录只能查询本院系的学生
            cout<<"\nYou can only access students in your own department("<<dep<<").\n";
            dep_num = dep;
        }
        school[dep_num].update_rank();  //更新排名
        cout<<"\nPlease enter student's ID: ";
        id = get_ID();
        if(school[dep_num].show_stu_report(id)){
            break;
        }
        cout<<" Enter 'yes' to try again:";
        getline(cin, cmd);
    }
    cout<<"\n--------- Student Report Card Query Done ---------\n\n";
    return;
}

void stu_info_query(){  //（教工）查询学生信息:2
    cout<<"\n\n--------- Student Information Query ---------\n";
    int dep_num=0,yr=0;
    string cmd = "yes",str;
    school[dep_num].update_rank();  //更新排名
    if(state == 3){  //管理员能查询任何院系的学生
        cout<<"\nPlease enter student's department code: ";
        dep_num = get_dep();
    }
    else{  //教师登录只能查询本院系的学生
        cout<<"\nYou can only access students in your own department("<<dep<<").\n";
        dep_num = dep;
    }
    cout<<"\nPlease enter student's year: ";
    yr = get_year();
    school[dep_num].show_year_class_info(yr);
    cout<<"\n--------- Student Information Query Done ---------\n\n";
    return;
}

void crs_info_query(){  //（教工）查询课程信息:3
    cout<<"\n--------- Course Information Query ---------\n";
    int dep_num=0,yr=0,id=0;
    string cmd = "yes";
    while(cmd == "yes"){
        if(state == 3){  //管理员能查询任何的课程成绩
            cout<<"\nPlease enter course's department code: ";
            dep_num = get_dep();
        }
        else{  //教师登录只能查询本院系的课程成绩
            cout<<"\nYou can only access courses in your own department("<<dep<<").\n";
            dep_num = dep;
        }
        cout<<"\nPlease enter semester: ";
        yr = get_year();
        cout<<"\nPlease enter course's ID: ";
        id = get_ID();
        if(school[dep_num].show_course_info(yr,id)){
            break;
        }
        cout<<" Enter 'yes' to try again:";
        getline(cin,cmd);
    }
    cout<<"\n\n--------- Course Information Query Done ---------\n\n";
    return;
}

void enter_stu_score(){  //录入学生成绩:4
    Student_Info stu;
    Course_Info crs;
    cout<<"\n--------- Enter Student Score ---------\n";
    int stu_dep=0,crs_dep=0,stu_id=0,crs_id=0;
    float score = 0;
    string cmd = "yes";
    while(cmd == "yes"){  //crs
        if(state == 3){  //管理员能录入任何的课程成绩
            cout<<"\nPlease enter course's department code: ";
            crs_dep = get_dep();
        }
        else{  //教师只能录入本院系的课程成绩
            cout<<"\nYou can only access courses in your own department("<<dep<<").\n";
            crs_dep = dep;
        }
        cout<<"\nPlease enter course's ID: ";
        crs_id = get_ID();
        if(school[crs_dep].judge_crs(crs_id)){
            crs = school[crs_dep].crs_info(crs_id);
            break;
        }
        cout<<"\nCourse not found! Enter 'yes' to try again:";
        getline(cin,cmd);
    }
    while(cmd == "yes"){  //stu
        cout<<"\nPlease enter student's department code: ";
        stu_dep = get_dep();
        cout<<"\nPlease enter student's ID: ";
        stu_id = get_ID();
        if(school[stu_dep].judge_stu(stu_id)){
            stu = school[stu_dep].stu_info(stu_id);
            break;
        }
        cout<<"\nStudent not found! Enter 'yes' to try again:";
        getline(cin,cmd);
    }
    
    if(cmd == "yes"){
        cout<<"\nPlease enter score: ";
        score = get_score();
        school[stu_dep].change_score_stu(stu_id,crs_id,score,crs);
        school[stu_dep].change_score_crs(crs_id,stu_id,score,stu);
    }
    
    cout<<"\n--------- Enter Student Score Done ---------\n";
    return;
}

void add_stu(){  //（教工）添加学生:5
    cout<<"\n--------- Add Student ---------\n";
    int dep_num=0,yr=0,id=0,gd=0;
    string name;
    string cmd = "yes",str;
    if(state == 3){  //管理员能向任何院系添加学生
        cout<<"\nPlease enter student's department code: ";
        dep_num = get_dep();
    }
    else{  //教师只能向本院系添加学生
        cout<<"\nYou can only add student to your own department("<<dep<<").\n";
        dep_num = dep;
    }
    while(cmd == "yes"){
        cout<<"\nPlease enter student's ID: ";
        id = get_ID();
        if(!judge_stu(id)){
            break;
        }
        cout<<"\nStudent already exists!\n";
        cout<<"\nEnter 'yes' to try again:";
        getline(cin, cmd);
    }
    if(cmd == "yes"){
        cout<<"\nPlease enter student's year: ";  //添加学生时保留年级输入
        yr = get_year();
        cout<<"\nPlease enter student's name: ";
        getline(cin,name);
        cout<<"\nPlease enter student's gender(male/0,female/1): ";
        gd = get_gd();
        Student stu(id,name,yr,dep_num,0,gd);
        school[dep_num].add_student(yr,stu);
        cout<<"\nSuceessfully added student("<<id<<","<<name<<") to "<<department_name[dep_num]<<"("<<yr<<").\n";
    }
    cout<<"\n--------- Add Student Done ---------\n\n";
    return;
}

void delete_stu(){  //（教工）删除学生:6
    cout<<"\n--------- Delete Student ---------\n";
    int dep_num=0,yr=0,id=0;
    string cmd = "yes";
    while(cmd == "yes"){
        if(state == 3){  //管理员能删除任何院系学生
            cout<<"\nPlease enter student's department code: ";
            dep_num = get_dep();
        }
        else{  //教师只能删除本院系学生
            cout<<"\nYou can only delete student of your own department("<<dep<<").\n";
            dep_num = dep;
        }
        cout<<"\nPlease enter student's year: ";  //删除时确认年级后删除
        yr = get_year();
        cout<<"\nPlease enter student's ID: ";
        id = get_ID();
        if(school[dep_num].judge_stu(id)){
            school[dep_num].delete_student(yr,id);
            break;
        }
        cout<<"\nStudent not found! Enter 'yes' to try again:";
        getline(cin,cmd);
    }
    cout<<"\n--------- Delete Student Done ---------\n\n";
    return;
}

void add_crs(){  //（教工）添加课程:7
    cout<<"\n--------- Add Course ---------\n";
    int dep_num=0,yr=0,id=0,sem=0,cre=0;
    string name;
    string cmd = "yes",str;
    if(state == 3){  //管理员能向任何院系添加课程
        cout<<"\nPlease enter course's department code: ";
        dep_num = get_dep();
    }
    else{  //教师只能向本院系添加课程
        cout<<"\nYou can only add course to your own department("<<dep<<").\n";
        dep_num = dep;
    }
    while(cmd == "yes"){
        cout<<"\nPlease enter course's ID: ";
        id = get_ID();
        if(!judge_crs(id)){
            break;
        }
        cout<<"Course already exists!\n";
        cout<<"Enter 'yes' to try again:";
        getline(cin, cmd);
    }
    if(cmd == "yes"){
        cout<<"\nPlease enter course's year: ";  //创建课程需要输入年级
        yr = get_year();
        cout<<"\nPlease enter course's semester:";
        sem = get_sem();
        cout<<"\nPlease enter course's credit:";
        sem = get_cre();
        cout<<"\nPlease enter course name: ";
        getline(cin,name);
        Course stu(id,name,yr,dep_num,0,cre,sem);
        school[dep_num].add_course(yr,stu);
        cout<<"\nSuceessfully added course("<<id<<","<<name<<","<<yr<<") to "<<department_name[dep_num]<<"\n";
    }
    cout<<"\n--------- Add Course Done ---------\n\n";
    return;
}

void delete_crs(){  //（教工）删除课程:8
    cout<<"\n--------- Delete Course ---------\n";
    int dep_num=0,yr=0,id=0;
    string cmd = "yes";
    while(cmd == "yes"){
        if(state == 3){  //管理员能删除任何院系课程
            cout<<"\nPlease enter course's department code: ";
            dep_num = get_dep();
        }
        else{  //教师只能删除本院系课程
            cout<<"\nYou can only delete course of your own department("<<dep<<").\n";
            dep_num = dep;
        }
        cout<<"\nPlease enter semester: ";
        yr = get_year();
        cout<<"\nPlease enter course's ID: ";
        id = get_ID();
        if(school[dep_num].delete_course(yr,id)){
            break;
        }
        cout<<"\nCourse not found! Enter 'yes' to try again:";
        getline(cin,cmd);
    }
    cout<<"\n--------- Delete Course Done ---------\n\n";
    return;
}

void Student::update_crs_dep(){  //更新所修课程中所存储的院系
    unsigned long course_number = courses.size();
    int crs_dep=-1,crs_id=0;
    for(int i=0; i<course_number; i++){
        crs_dep = courses[i].get_department();
        crs_id = courses[i].get_ID();
        school[crs_dep].update_crs_dep(crs_id,ID,department,year);
    }
    return;
}

void change_stu_dep(){  //学生转专业
    cout<<"\n--------- Change Student Department ---------\n";
    int dep=0,yr=0,id=0,n_dep=0,n_yr=0;
    string cmd = "yes";
    while(cmd == "yes"){
        cout<<"\nPlease enter student's department code: ";
        dep = get_dep();
        cout<<"\nPlease enter student's year: ";  //转专业需要确认年级
        yr = get_year();
        cout<<"\nPlease enter student's ID: ";
        id = get_ID();
        if(school[dep].judge_stu(id,yr)){
            break;
        }
        cout<<"\nStudent not found! Enter 'yes' to try again:";
        getline(cin,cmd);
    }
    if(cmd == "yes"){
        cout<<"\nPlease enter student's new department code: ";
        n_dep = get_dep();
        cout<<"\nPlease enter student's new year: ";  //转专业需要确认年级
        n_yr = get_year();
        Student stu = school[dep].delete_student(yr, id);
        stu.set_year(n_yr);
        stu.set_department(n_dep);
        stu.update_crs_dep();  //更新所修课程中所存储的院系
        school[n_dep].add_student(n_yr, stu);
        cout<<"\nStudent("<<id<<") ";
        cout<<"has been successfully transfered to "<<department_name[n_dep]<<"("<<n_yr<<") from ";
        cout<<department_name[dep]<<"("<<yr<<").\n";
    }
    cout<<"\n--------- Change Student Department Done ---------\n\n";
    return;
}

void save_changes(){  //保存修改到两个文件
    string cmd = "\n";
    cout<<"\nSave changes? Enter 'yes' to save changes:";
    getline(cin,cmd);
    if(cmd == "yes"){
        string stu_file_path = path + "Student.txt";
        string crs_file_path = path +"Course.txt";
        stu_file.open(stu_file_path);
        crs_file.open(crs_file_path);
        //Student + Course
        stu_file<<total_dep<<" "<<password<<endl;  //总院系数
        for(int i=0;i<total_dep;i++){  //依次保存院系信息
            school[i].save();
            crs_file<<endl;
        }
        stu_file.close();
        crs_file.close();
        cout<<"\nSave Changes Success!\n";
    }
}
