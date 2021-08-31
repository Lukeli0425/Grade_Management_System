//
//  main.cpp
//  Grade_Management_System
//
//  Created by Luke on 2021/7/19.
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

int main() {
    cout<<"Welcome to Grade Management System!\n\n";
    
    inialization();
    login();
    operation();
//    save_changes();
//    
//    cout<<"\nThank you for using Grade Management System!\n\n";
    return 0;
}
