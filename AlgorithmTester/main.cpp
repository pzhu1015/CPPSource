///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "AlgorithmTester/Serialize.h"
#include <iostream>
#include <string>
using namespace std;

int main(int args, char** argv)
{
	/*{
		Employee emp;
		emp.set_id(110);
		emp.set_name("彭志虎");
		emp.set_salary(20000.0);
		emp.set_no(1000000000);
		emp.set_id_vector(std::vector<int>(4, 1000));
		emp.set_id_list(std::list<int>(4, 1000));
		emp.set_id_set(std::set<int>{1000, 1200, 1300});
		Department dept;
		dept.set_id(100);
		dept.set_name("研发部");
		emp.set_dept(dept);
		emp.set_dept_vector(std::vector<Department>(3, dept));
		emp.set_dept_list(std::list<Department>(3, dept));
		emp.set_dept_set(std::set<Department>{dept});
		CJsonObject json;
		emp.SerializeTo(json);
		std::string str = json.ToFormattedString();
		std::cout << str << std::endl;

		CJsonObject root(str);
		Employee emp1;
		emp1.SerializeFrom(root);
		str = root.ToFormattedString();
		std::cout << str << std::endl;
	}*/
	SimpleStruct simple_struct;
	simple_struct.bool_ = true;
	simple_struct.int_ = 101;
	simple_struct.double_ = 10.9;
	simple_struct.string_ = "hello";
	CJsonObject json;
	adl_serializer<SimpleStruct>::to_json(json, simple_struct);
	std::string str = json.ToString();
	std::cout << str << std::endl;
	::system("pause");
	return 1;
}