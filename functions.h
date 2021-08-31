//
//  function.h
//  Grade_Management_System
//
//  Created by Luke on 2021/8/9.
//

#ifndef functions_h
#define functions_h

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

//全局变量声明
extern vector<Department> school;  //使用vector定义各个院系学生的集合
extern string password;  //教工登录密码
extern int state;  //登录状态
extern int dep;  //学生/教工院系
extern int user_id;  //学生/教工ID
extern int year;  //学生年级

//函数声明
void inialization();  //读入文件，初始化院系（名称、编号、学生、课程）
int get_dep();  //读入院系（含异常处理）
int get_ID();  //读入ID（含异常处理）
int get_year();  //读入年级（含异常处理）
int get_gd();  //读入性别（含异常处理）
int get_sem();  //读入学期（含异常处理）
int get_cre();  //读入学分（含异常处理）
float get_score();  //读入成绩（含异常处理）

void stu_login();  //学生登录（含检查信息是否正确）
void staff_login();  //教工登录（含检查信息是否正确）
void login();  //登录
void operation();  //完成 查询信息/录入信息/导出信息 等操作
    
void stu_info_query();  //（教工）查询学生信息
void stu_report_query();  //（教工）查询学生成绩单
void crs_info_query();  //（教工）查询课程信息
void enter_stu_score();  //录入学生成绩
void add_stu();  //添加学生
void delete_stu();  //删除学生
void add_crs();  //添加课程
void delete_crs();  //删除课程
void change_stu_dep();  //学生转专业
void save_changes();  //保存修改到两个文件
    
#endif /* functions_h */
