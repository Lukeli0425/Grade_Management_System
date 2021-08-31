# Grade_Mangement_System
## 学生成绩管理系统

### 目  录

1. 系统需求分析 
2. 总体设计 
3. 详细设计 
4. 系统调试 
5. 使用说明&结果分析 
6. 总结 
7. 附录：文件清单

### 一、系统需求分析 
学生成绩管理系统中记录了学生的信息（院系、姓名、年级、学号、性别、绩点、所修课程及成绩）和课程信息（课程名称、课程号、课程学分、学年、学期、选修学生及成绩），并可以根据学生的成绩自动计算绩点和排名。为了应对学生转专业、休学等特殊情况，系统中也专门设计了相应的功能修改学生或课程信息。

具体而言，整个系统主要具有如下的功能：

1. 实现不同身份的登录（学生/教师/管理员），不同身份对应不同的权限；
2. 录入学生课程成绩，自动计算学生的GPA、排名，自动计算课程平均分；
3. 修改信息，包括修改学生课程成绩、添加/删除学生、添加/删除课程、修改学生年级和专业（转专业带来的变动）等；
4. 查询信息，具体包括查询学生的成绩单、批量查询某院系某一届全体同学信息、查询课程信息（包含将成绩单、课程信息下载到txt文件的功能）。

### 二、总体设计
为了满足系统的需求，我设计了诸多功能模块，详细说明如下：
0. 用户登录：根据用户的不同身份（学生、教师、管理员）进行相应的登录操作。学生登录需要输入自己的院系、年级和学号，教师登录需要输入自己的院系和院系密码，管理员登录需要输入管理员密码。不同的登录状态有不同的操作权限。
1. （学生、教师、管理员）查询学生的成绩单：成绩单中既包含学生的学号、院系、年级等全部基本信息，也包含学生所修的全部课程信息（课程号、课程名称、学分、百分制成绩、等级制成绩、绩点）。成绩单既可以在系统中查看，也可以下载到txt文件中。
2. （教师、管理员）查询某一院系某一年级全体同学的信息：输入院系和年级之后，系统按照GPA由高到低的顺序显示所有同学的学号、姓名、GPA和由GPA换算得到的百分置成绩。
3. （教师、管理员）查询某一课程的学生信息：教工输入院系和课程号之后，系统显示课程名称、课程号、课程学分、学年、学期、选课人数、平均分等基本信息，之后按照学号顺序显示全部选课同学的信息（学号、姓名、院系和课程成绩）。课程信息可以下载到txt文件中。
4. （教师、管理员）录入或修改学生的课程成绩：教工输入课程所在院系、课程号，学生院系、学号，以及学生的在该课程中的百分制成绩，系统自动修改学生的课程成绩，并计算绩点。如果输入前系统中没有学生选修这门课的成绩记录，系统自动为学生添加选修课程的成绩记录。
5. （教工）添加学生信息：输入学号、姓名、院系等基本信息，系统检查该学生是否存在。如果不存在，系统自动创建学生信息，学生信息被添加的初始状态不含任何课程成绩；如果学生已经存在，显示提示信息。
6. （教工）删除学生信息：输入学生院系、年级和学号，系统检查该学生是否存在。如果学生存在，系统删除该学生的信息和全部的课程记录；如果学生不存在，显示提示信息。
7. （教工）添加课程信息：输入院系、课程号、课程名称、学期等基本信息，系统检查该课程是否存在。如果不存在，系统自动创建课程信息，课程信息被添加的初始状态不含任何学生成绩；如果课程已经存在，显示提示信息。
8. （教工）删除课程信息：输入课程院系、学期和课程号，系统检查该课程是否存在。如果课程存在，系统删除该课程的信息和全部的课程记录；如果课程不存在，显示提示信息。
9. （管理员）更改学生院系和年级：输入学生原始院系、年级和学号，如果学生不存在，系统显示提示信息；如果学生存在，继续输入转入院系和年级，系统更改学生的年级和院系，并在该学生所修的全部课程记录中修改学生的年级和院系。
 
学生成绩管理系统功能模块图：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/Module_Grade_Management-System.jpg)

程序开始后先读入文件中存储的信息，读入成功后进入登录界面，登录成功后进入菜单界面选择需要进行的操作，退出程序前可选择保存修改或不保存修改。

### 三、详细设计 

学生成绩管理系统中包含6个类，它们的层次结构如下图所示：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/Class_Grade_Management-System.jpg)

其中Basic类为模板类，含有纯虚函数，这些纯虚函数在不同的派生类中又不同的实现。Student_Info类和Course_Info类是Basic类的派生类，它们中的成员存储了学生/课程的基本信息，如名称、学号/课程号、年级/学期、所属院系等。Student类和Course类分别是Student_Info类和Course_Info类的派生类，分别存储了某一学生或课程的全部信息。Student类继承了Student_Info类，含有Student_Info类中存储学生基本信息的成员，也含有一个由Course_Info对象组成的vector容器作为成员，其中每一个Course_Info对象记录了该学生所修的一个课程的信息（包括成绩）；类似地，Course类继承了Course_Info类，含有Course_Info类中存储课程基本信息的成员，也含有一个由Student_Info对象组成的vector容器作为成员，其中每一个Student_Info对象记录了选修该课程的一个学生的信息（包括成绩）。最后，Department类代表一个院系，成员中包括一个由Student对象组成的vector容器，容器中的每一个Student对象都是该院系中的学生，还包括一个由Course对象组成的vector容器，容器中的每一个Course对象都是该院系开设的课程。
	各功能模块的实现：

#### 0. 用户登录

进入登录界面后，用户根据提示输入0/1/2/3，它们分别代表退出系统（0）、学生登录（1）、教师登录（2）和管理员登录（3）。之后用户需根据提示信息输入登录所需的院系等信息以及密码，如果信息或密码正确，登录成功，进入菜单界面，否则系统跳回登录页面。用户登录的功能模块图如下：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/login.jpg)

#### 1. 查询学生的成绩单

在成绩单查询模块中任何身份的用户都可以查询成绩单：学生进入后直接显示该学生的成绩单；教师可以查询本院系学生的成绩单，根据提示输入学号，如果学号正确则显示成绩单，否则询问是否重新输入；管理员可以查询任何学生的成绩单，根据提示输入学生的院系和学号，如果学生存在则显示成绩单，否则询问是否重新输入。在显示成绩单后，系统自动询问是否下载成绩单，如果选择是，则系统将成绩单下载为一个txt文件内，之后返回菜单界面，如果选择否则直接返回菜单界面。学生成绩单查询功能模块图如下：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/stu_report_query.jpg)

#### 2. 查询某一院系某一年级全体同学的信息

只有教师和管理员有权限批量查询学生信息。学生进入后显示无权限的提示信息，自动跳回菜单界面；教师登录后可根据提示输入所要查询的年级，之后系统显示教师所在院系该年级学生的姓名、学号、GPA、排名等（顺序按照GPA由高至低排名）；管理员登录后可根据提示输入所要查询的院系和年级，之后系统显示所选院系年级学生的姓名、学号、GPA、排名等（顺序按照GPA由高至低排名）。功能模块图如下：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/stu_info_query.jpg)

#### 3. 查询某一课程的学生信息

教师和管理员有权限查询课程信息。学生进入后显示无权限的提示信息，自动跳回菜单界面。教师登录后可根据提示输入所要查询课程的学年和课程号（只能查询本院系开设的课程），如果课程号正确，则显示该课程的基本信息（课程名称、课程号、学年、学期、学分、平均分等）和选修课程的学生信息（学号、姓名、院系、百分制成绩、等机制成绩、绩点等按照学号排序），如果课程号错误，系统询问时都重试，选择不重试则返回菜单界面。管理员登录后需在最开始选择开设课程的院系，其余与教师登录无异。显示课程信息后系统询问是否下载，选择是则将课程信息下载到txt文件中，之后返回菜单界面；选择否则直接返回菜单界面。功能模块图如下：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/crs_info_query.jpg)

#### 4. 录入或修改学生的课程成绩

教师和管理员可以录入或修改学生的课程成绩。学生进入后显示无权限的提示信息，自动跳回菜单界面。教师可录入学生在本院系课程中获得的成绩，进入后可根据提示输入课程号，如果课程号正确，继续输入学生所在院系和学号，如果学号正确，则可输入学生的百分制成绩。如果系统之前有学生选修这门课的记录，则会更新学生的成绩，如果没有则会创建选修的记录，并记录成绩。管理员登录后需在最开始选择开设课程的院系，其余与教师登录无异。如果输入学号或课程号有误，则系统询问是否重试。录入或修改学生的课程成绩功能模块如下图所示：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/enter_stu_score.jpg)

#### 5. 添加学生信息

教师或管理员可以添加学生信息。类似前述模块，学生无权限，教师和管理员均有权限，差别在于教师只能添加学生到本院系，管理员可以向任何院系添加学生，因此首先需要输入院系。此后输入学号，如果学号已被使用，则系统询问是否重试；如果输入的学号未被占用，则可继续输入年级、姓名、性别等信息，系统自动创建学生，并完成后显示提示信息，返回菜单界面。添加学生的功能模块图如下：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/add_stu.jpg)

#### 6. 删除学生信息

教师或管理员可以删除学生信息。类似前述模块，学生无权限，教师和管理员均有权限，差别在于教师只能删除本院系学生，管理员可以删除任何院系的学生，因此首先需要输入院系。此后输入学号，如果学号不存在，则系统询问是否重试；如果输入的学号存在，则删除该学号对应的学生，并完成后显示提示信息，返回菜单界面。删除学生的功能模块图如下：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/delete_stu.jpg)

#### 7. 添加课程信息

教师或管理员可以添加课程。类似前述模块，学生无权限，教师和管理员均有权限，差别在于教师只能添加本院系的课程，管理员可以向任何院系添加课程，因此首先需要输入院系。此后输入课程号，如果课程号已被使用，则系统询问是否重试；如果输入的学号未被占用，则可继续输入课程名称、学年、学期、学分等信息，系统自动创建课程，并完成后显示提示信息，返回菜单界面。添加课程的功能模块图如下：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/add_crs.jpg)

#### 8. 删除课程信息

教师或管理员可以删除课程。类似前述模块，学生无权限，教师和管理员均有权限，差别在于教师只能删除本院系课程，管理员可以删除任何院系的课程，因此首先需要输入院系。此后输入课程号，如果课程号不存在，则系统询问是否重试；如果输入的课程号存在，则删除对应课程，并完成后显示提示信息，返回菜单界面。删除课程的功能模块图如下：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/delete_crs.jpg)

#### 9. 更改学生院系和年级

只有管理员可以进行此操作。学生和教师进入该模块后显示无权限的提示信息后返回菜单界面。管理员进入后首先输入学生原来的院系、年级和学号，信息无误后继续输入变更后的年纪和院系，系统对学生信息进行修改，显示提示信息，返回菜单界面。如果学生信息有误，则系统询问是否重试。该模块功能模块图如下：
 
![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/change_stu_dep.jpg)

学生成绩管理系统中6个类的UML图：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/UML_Grade_Management-System.jpg)

### 四、系统调试 

学生成绩管理系统的代码完成主要分为两个部分。第一部分我完成了6个类的声明以及类的成员函数的实现。我首先设计了类的UML图，确定每个类内的成员后，就可以首先完成类的声明，接下来根据系统的需要添加成员函数。在完成成员函数之后，我写了一些小的测试程序来验证这些类的定义及成员函数的正确性。这个过程中主要的错误出现在删除某个类的vector成员中的某一项上。例如删除学生的课程时，需要根据课程号在Student类的courses成员（类型为vector<Course_Info>）中找到对应的一项并将其删除。我在一开始采用的删除方法并不能达到这一效果，并且没有对找不到删除对象的情况进行异常处理。因此我使用了iterator迭代器来实现删除效果，并针对找不到删除对象的情况作了处理，将函数的返回值类型由void修改为bool，用于标记是否删除成功，这就解决了这一问题。其余类中类似的查找或删除问题用相同的方法全部迎刃而解。

在完成6个类的全部代码并验证无误后，我开始针对具体的功能编写相应的函数（登录、菜单及9个主要功能）。在完成的过程中，我也对之前完成的类的成员函数进行了修改或添加以满足特定功能的需要（例如Student类的show_report_card()函数和Course类的show_course()函数添加了导出功能，加入密码功能后向Department类中加入了set_password()函数等等）。随后我便对整个系统开始进行测试。这时我才发现，我并没有实现系统存储录入的信息的功能，程序运行结束后录入的成绩将会丢失，因此我采取了这样一种方式：进入系统时读取文件，导入上一次存储的信息，操作结束后，退出系统前将当前的信息存入文件，这样就是initialization()和save_changes()函数所实现的内容。此后我利用文件对系统进行初始化，进行各种功能的测试就方便了很多，这期间出现了一些小问题，例如：输出的内容有误或函数形参写错等，一一修改后系统就可以正确的运行了。

在测试过程中，我意识到输入异常时如果不进行处理，程序容易出致命的错误（例如数组越界），于是我针对每一种输入专门编写了含有异常处理功能的函数应对这种情况：
```c++
int get_dep();  //读入院系（含异常处理）
int get_ID();  //读入ID（含异常处理）
int get_year();  //读入年级（含异常处理）
int get_gd();  //读入性别（含异常处理）
int get_sem();  //读入学期（含异常处理）
int get_cre();  //读入学分（含异常处理）
float get_score();  //读入成绩（含异常处理）
```

### 五、使用说明&结果分析

在测试的过程中，我利用初始化文件（Student.txt和Course.txt）对系统功能进行验证。Student.txt中记录了院系的学生信息，Course.txt记录了课程信息。为了方便起见，我在测试时只设置了10个院系，并在两个院系中各设置了10名学生，在另一个院系设置了1名学生（用来模拟转专业），总共设置了4门课程。

Student.txt的内容：

```
10 65712949
电子工程系
0 0000
10
20180001 ABA 2018 0
20180002 ABB 2018 0
20180005 ABE 2018 1
20180003 ABC 2018 0
20180004 ABD 2018 1
20190001 AAA 2019 0
20190004 AAD 2019 1
20190005 AAE 2019 0
20190002 AAB 2019 0
20190003 AAC 2019 1
计算机系  
1 1111
10
20181001 BBA 2018 0
20181002 BBB 2018 0
20181003 BBC 2018 0
20181004 BBD 2018 1
20181005 BBE 2018 1
20191001 BAA 2019 0
20191002 BAB 2019 0
20191003 BAC 2019 1
20191004 BAD 2019 0
20191005 BAE 2019 1
自动化系  
2 2222
0
软件学院  
3 333
0
数学科学系
4 4444
0
物理系   
5 5555
0
天文系   
6 6666
0
化学系   
7 7777
0
生命学院  
8 8888
0
航天航空学院
9 9999
1
20192392 LTA 2019 0
```

其中第一行的10表示总共有10个院系，65712949是管理员登录密码。每个院系名之后的一行中的两个数字分别是院系代码和院系密码（如电子系院系代码为0，密码为0000），下一行为院系总学生数（如电子系总学生为10），之后的每一行为院系内一位学生的信息，依次为学号、姓名、年级和性别（0表示男，1表示女）。

Course.txt内容如下：

```
3

20192002 电子电路与系统基础（1） 2019 2 2 8
0 20190001 95
0 20190002 86
0 20190003 83
0 20190004 93
0 20190005 91
0 20180004 81
0 20180005 89
9 20192392 90

20202003 计算机程序设计基础（2） 2020 2 3 7
0 20190001 89
0 20190002 91
0 20190003 90
0 20190004 87
0 20190005 80
0 20180003 89
9 20192392 90

20202004 信号与系统 2020 2 4 10
0 20190001 95
0 20190002 86
0 20190003 83
0 20190004 93
0 20190005 91
0 20180001 93
0 20180002 95
0 20180003 85
9 20192392 92
1 20181002 88


1

20201104 数据结构 2020 1 4 8
1 20191001 92
1 20191002 95
1 20191003 82
1 20191004 81
1 20191005 100
1 20181002 89
1 20181003 85
0 20180002 90


0


0


0


0


0


0


0


0
```

其中每一个独占一行的数字代表某一院系的总课程数，顺序按照院系代码排列（例如电子系有3门课），之后每一段信息代表一个课程。第一行分别是课程号、课程名称、学年、学期、学分和选课人数，余下的每一行记录了每一位选课学生的信息（以此是所属院系代码、学号和百分制成绩）。

编写好测试文件之后，我开始测试全部的功能：

#### 0. 读入文件初始化

程序开始运行后显示如下信息证明Student.txt和Course.txt文件内容无误初始化成功：
```
Welcome to Grade Management System!

Finished Student Import: 电子工程系
Finished Student Import: 计算机系  
Finished Student Import: 自动化系  
Finished Student Import: 软件学院  
Finished Student Import: 数学科学系
Finished Student Import: 物理系   
Finished Student Import: 天文系   
Finished Student Import: 化学系   
Finished Student Import: 生命学院  
Finished Student Import: 航天航空学院

Finished Course Information Import: 电子电路与系统基础（1）
Finished Course Information Import: 计算机程序设计基础（2）
Finished Course Information Import: 信号与系统
Finished Course Import: 电子工程系
Finished Course Information Import: 数据结构
Finished Course Import: 计算机系  
Finished Course Import: 自动化系  
Finished Course Import: 软件学院  
Finished Course Import: 数学科学系
Finished Course Import: 物理系   
Finished Course Import: 天文系   
Finished Course Import: 化学系   
Finished Course Import: 生命学院  
Finished Course Import: 航天航空学院

Initialization Success!
```

#### 1. 学生登录

选择以电子系学号为20190001的学生登录，信息正确，登录成功：
```
------- Login -------
0 - exit
1 - login as student
2 - login as school staff
3 - login as administrator

Please enter 0/1/2/3: 1

------ Login as student ------

Please enter your department code: 0

Please enter your year: 2019

Please enter your ID: 20190001

------ Login success! ------
```

同时弹出菜单界面：
```
0 - Exit
1 - Student report card
2 - Student information query (staff only)
3 - Course information query (staff only)
4 - Enter student's score (staff only)
5 - Add student information (staff only)
6 - Delete student (staff only)
7 - Add course information (staff only)
8 - Delete course (staff only)
9 - Change Student Department (administrator only)

Please enter the operation you wish to perform: 
```

验证成绩单查询功能，并下载成绩单：
```
Please enter the operation you wish to perform: 1

--------- Student Report Card ---------

Department:		电子工程系
ID:				20190001
Name:				AAA
Year:				2019
GPA:				3.867
Score:			92.33
Total Credit:		9
Rank:				1

1  20192002  2019-2020-2  2  95	A   4.0  电子电路与系统基础（1）
2  20202003  2020-2021-2  3  89	B+  3.6  计算机程序设计基础（2）
3  20202004  2020-2021-2  4  95	A   4.0  信号与系统

--------- Student Report Card ---------

Download report card? Enter 'yes' to download:
yes

Report Card exported to file: stu_20190001.txt

--------- Student Report Card Query Done ————
```

下载的成绩单stu_20190001.txt中内容准确无误：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/stu_20190001.jpg)

最后验证学生进行其他操作时无权限（这里以查询课程信息为例）：
```
Please enter the operation you wish to perform: 2

Sorry,you have no access to student information.
```

#### 2. 教师登录

教师登录也可查询学生成绩单，只是需要额外输入学号（这里也顺便验证一下学号错误时的异常处理）：
```
------- Login -------
0 - exit
1 - login as student
2 - login as school staff
3 - login as administrator

Please enter 0/1/2/3: 2

------ Login as school staff ------

Please enter your department code: 0

Please enter department password: 0000

------ Login success! ------

0 - Exit
1 - Student report card
2 - Student information query (staff only)
3 - Course information query (staff only)
4 - Enter student's score (staff only)
5 - Add student information (staff only)
6 - Delete student (staff only)
7 - Add course information (staff only)
8 - Delete course (staff only)
9 - Change Student Department (administrator only)

Please enter the operation you wish to perform: 1


--------- Student Report Card Query ---------

You can only access students in your own department(0).

Please enter student's ID: 20190000
Student not found! Enter 'yes' to try again:yes

You can only access students in your own department(0).

Please enter student's ID: 20190002

--------- Student Report Card ---------

Department:		    电子工程系
ID:				    20190002
Name:				AAB
Year:				2019
GPA:				3.733
Score:			    88.67
Total Credit:		9
Rank:				4

1  20192002  2019-2020-2  2  86	B+  3.6  电子电路与系统基础（1）
2  20202003  2020-2021-2  3  91	A-  4.0  计算机程序设计基础（2）
3  20202004  2020-2021-2  4  86	B+  3.6  信号与系统

--------- Student Report Card ---------

Download report card? Enter 'yes' to download:
no

--------- Student Report Card Query Done ---------
```

验证教师查询院系中某一届全体同学的信息（按照绩点排名）：
```
Please enter the operation you wish to perform: 2


--------- Student Information Query ---------

You can only access students in your own department(0).

Please enter student's year: 2019

--------- Student Information ---------

Department: 电子工程系
Class of 2019
Total Students: 5

1  20190001  AAA	3.867  92.33
1  20190004  AAD	3.867  90.33
3  20190005  AAE	3.767  88.67
4  20190002  AAB	3.733  88.67
5  20190003  AAC	3.533  85.33

--------- Student Information ---------

--------- Student Information Query Done ————
```

验证查询课程信息并下载的功能（顺便验证一下课程号错误时的异常处理）：
```
Please enter the operation you wish to perform: 3

--------- Course Information Query ---------

You can only access courses in your own department(0).

Please enter semester: 2020

Please enter course's ID: 20202000
Course not found! Enter 'yes' to try again:yes

You can only access courses in your own department(0).

Please enter semester: 2020

Please enter course's ID: 20202004

--------- Course Information ---------

Department:		    电子工程系
ID:				    20202004
Semester:			2020-2021-2
Course Name:		信号与系统
Total students:		10
Average Score:		90.1

1	20180001  93	A-  4.0  电子工程系	ABA
2	20180002  95	A   4.0  电子工程系	ABB
3	20180003  85	B+  3.6  电子工程系	ABC
4	20181002  88	B+  3.6  计算机系  	BBB
5	20190001  95	A   4.0  电子工程系	AAA
6	20190002  86	B+  3.6  电子工程系	AAB
7	20190003  83	B   3.3  电子工程系	AAC
8	20190004  93	A-  4.0  电子工程系	AAD
9	20190005  91	A-  4.0  电子工程系	AAE
10	20192392  92	A-  4.0  航天航空学院	LTA

--------- Course Information ---------

Download course information? Enter 'yes' to download:
yes

Course information exported to file: crs_20202004.txt


--------- Course Information Query Done ---------
```

课程内部的学生按照学号排序。查看下载的课程信息crs_20202004.txt中内容准确无误：

![](https://github.com/Lukeli0425/Grade_Management_System/raw/main/crs_20202004.jpg)

验证录入成绩的功能。这里将学号为20190001的学生在信号与系统这门课中的成绩修改为85：	
```
Please enter the operation you wish to perform: 4

--------- Enter Student Score ---------

You can only access courses in your own department(0).

Please enter course's ID: 20202004

Please enter student's department code: 0

Please enter student's ID: 20190001

Please enter score: 85

--------- Enter Student Score Done ---------
```

再次查看学生20190001的成绩单，发现成绩已经修改成功：
```
Please enter the operation you wish to perform: 1


--------- Student Report Card Query ---------

You can only access students in your own department(0).

Please enter student's ID: 20190001

--------- Student Report Card ---------

Department:		    电子工程系
ID:				    20190001
Name:				AAA
Year:				2019
GPA:				3.689
Score:			    88.78
Total Credit:		9
Rank:				4

1  20192002  2019-2020-2  2  95	A   4.0  电子电路与系统基础（1）
2  20202003  2020-2021-2  3  89	B+  3.6  计算机程序设计基础（2）
3  20202004  2020-2021-2  4  85	B+  3.6  信号与系统

--------- Student Report Card ---------

Download report card? Enter 'yes' to download:
no

--------- Student Report Card Query Done ---------
```

验证教师添加/删除学生或课程，这里以添加。删除学生为例。向电子系2019届添加学生20190006：

```
	Please enter the operation you wish to perform: 5

--------- Add Student ---------

You can only add student to your own department(0).

Please enter student's ID: 20190006

Please enter student's year: 2019

Please enter student's name: AAF

Please enter student's gender(male/0,female/1): 0

Suceessfully added student(20190006,AAF) to 电子工程系(2019).

--------- Add Student Done ---------
```

验证添加学生成功：
```
Please enter the operation you wish to perform: 2


--------- Student Information Query ---------

You can only access students in your own department(0).

Please enter student's year: 2019

--------- Student Information ---------

Department: 电子工程系
Class of 2019
Total Students: 6

1  20190004  AAD	 3.867  90.33
2  20190005  AAE	 3.767  88.67
3  20190002  AAB	 3.733  88.67
4  20190001  AAA	 3.689  88.78
5  20190003  AAC	 3.533  85.33
6  20190006  AAF	 0.000  0.00

--------- Student Information ---------

--------- Student Information Query Done ————
```

再删去添加的学生：
```
Please enter the operation you wish to perform: 6

--------- Delete Student ---------

You can only delete student of your own department(0).

Please enter student's year: 2019

Please enter student's ID: 20190006

--------- Delete Student Done ————
```

验证删除成功：
```
Please enter the operation you wish to perform: 2


--------- Student Information Query ---------

You can only access students in your own department(0).

Please enter student's year: 2019

--------- Student Information ---------

Department: 电子工程系
Class of 2019
Total Students: 5

1  20190004  AAD	 3.867  90.33
2  20190005  AAE	 3.767  88.67
3  20190002  AAB	 3.733  88.67
4  20190001  AAA	 3.689  88.78
5  20190003  AAC	 3.533  85.33

--------- Student Information ---------

--------- Student Information Query Done ---------
```

验证教师无权限进行转专业操作：
```
Please enter the operation you wish to perform: 9

Sorry,you have no authority to change student department.
```

#### 3. 管理员登录

教师登录的1-8功能出需要额外输入院系之外与之前教师登录无区别，此处不再重复。着重验证学生转专业的功能，这里将学生20192392从航天航空学院转到电子工程系：
```
------- Login -------
0 - exit
1 - login as student
2 - login as school staff
3 - login as administrator

Please enter 0/1/2/3: 3

------ Login as administrator ------

Please enter administrator password: 65712949

------ Login success! ------

0 - Exit
1 - Student report card
2 - Student information query (staff only)
3 - Course information query (staff only)
4 - Enter student's score (staff only)
5 - Add student information (staff only)
6 - Delete student (staff only)
7 - Add course information (staff only)
8 - Delete course (staff only)
9 - Change Student Department (administrator only)

Please enter the operation you wish to perform: 9

--------- Change Student Department ---------

Please enter student's department code: 9

Please enter student's year: 209

Input error! Please enter a correct year: 2019

Please enter student's ID: 20192392

Please enter student's new department code: 0

Please enter student's new year: 2019

Student(20192392) has been successfully transfered to 电子工程系(2019) from 航天航空学院(2019).

--------- Change Student Department Done ---------
```

验证转专业成功：
```
Please enter the operation you wish to perform: 2


--------- Student Information Query ---------

Please enter student's department code: 0

Please enter student's year: 2019

--------- Student Information ---------

Department: 电子工程系
Class of 2019
Total Students: 6

1  20192392  LTA	 4.000  92.00
2  20190004  AAD	 3.867  90.33
3  20190005  AAE	 3.767  88.67
4  20190002  AAB	 3.733  88.67
5  20190001  AAA	 3.689  88.78
6  20190003  AAC	 3.533  85.33

--------- Student Information ---------

--------- Student Information Query Done ---------
```

### 六、总结 

本次作业我所搭建的成绩管理系统总共用到了6个类，其中的好处在于利用继承的方式很多类的成员和方法无需重复完成，问题在于类的层次结构过于复杂，实现某一个功能需要多重函数的调用。在考虑到要求使用类的继承后，我考虑到学生中需要存储该学生所修的课程，课程中也要存储选修这门课的学生信息，如果学生类和课程类互为成员就回出现无穷递归定义的错误。因此我设计了两个成员较少、较为基本的类：Student_Info和Course_Info，其中只存储学生或课程的基本信息（不涉及学生的课程和课程中的学生），供Student和Course类存储学生的课或课程中的学生时作为成员使用。此外，Student类继承Student_Info类，Course类继承Course_Info，也给Student和Course的实现带来了便利。这样虽然用了更多的类，但也使得信息的存储方式更加清晰，便于维护。

本次作业我的另一个不足之处在于没有仔细考虑复杂的的问题。例如根据学号或课程号搜索学生或课程时，我使用的是复杂度为O(n)的遍历法，这在系统中数据量较大时会使得系统运行缓慢。这对于系统的实用性影响较大，是一个值得进一步优化的地方。

在完成本次作业的过程中，我体会到了使用多文件变成的方式完成一个较大的工程的过程，也形成了自己完成代码的规范（例如函数和变量的声明、添加注释等）。本次作业耗时较长，开始我在逐渐寻找适合自己的coding方式，因此开始完成代码等效率不是很高，找到节奏后效率就提升了许多。总的来说这次作业对于我的代码能力和完成一项较大工程的能力是一次很大的提升。

### 七、   附录：文件清单

    README.md				说明文档
    README.txt              说明文档pdf版
    Student.txt				学生初始化文件
    Course.txt				课程初始化文件
    Basic.h				    Basic类头文件
    Basic.cpp				Basic类cpp文件
    Student_Info.h			Student_Info类头文件
    Student_Info.cpp		Student_Info类cpp文件
    Course_Info.h			Course_Info类头文件
    Course_Info.cpp			Course_Info类cpp文件
    Student.h				Student类头文件
    Student.cpp			    Student类cpp文件
    Course.h				Course类头文件
    Course.cpp				Course类cpp文件
    Department.h			Department类头文件
    Department.cpp			Department类cpp文件
    functions.h				功能函数头文件
    functions.cpp			功能函数cpp文件
    main.cpp				主函数文件

---
#### Contact me:    lukeli@sina.cn