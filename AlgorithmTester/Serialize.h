///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef ALGORITHMTESTER_SERIALIZE_H
#define ALGORITHMTESTER_SERIALIZE_H
#include "System/Serializers/JsonSerialize.h"
#include "System/Reflections/Property.h"
#include <vector>
#include <list>
#include <set>
using namespace System::Serializers;
using namespace System::Reflections;

class Department : public JsonSerialize
{
public:
	Department()
	{

	}
	virtual ~Department()
	{

	}
	virtual void SerializeTo(CJsonObject &json)
	{
		SERIALIZE_TO(json, id);
		SERIALIZE_TO(json, name);
	}

	virtual void SerializeFrom(CJsonObject &json)
	{
		SERIALIZE_FROM(json, id);
		SERIALIZE_FROM(json, name);
	}

	bool operator < (const Department& rhs) const
	{
		return false;
	}

	bool operator == (const Department& rhs) const
	{
		return false;
	}

private:
	int id;
	std::string name;

public:
	PROPERTY(id)
	PROPERTY(name)
};

class Employee : public JsonSerialize
{
public:
	Employee()
	{

	}
	virtual ~Employee()
	{

	}

	virtual void SerializeTo(CJsonObject &json)
	{
		SERIALIZE_TO(json, id);
		SERIALIZE_TO(json, name);
		SERIALIZE_TO(json, salary);
		SERIALIZE_TO(json, no);
		SERIALIZE_TO(json, id_vector);
		SERIALIZE_TO(json, id_list);
		SERIALIZE_TO(json, id_set);
		SERIALIZE_TO(json, dept);
		SERIALIZE_TO(json, dept_vector);
		SERIALIZE_TO(json, dept_list);
		SERIALIZE_TO(json, dept_set);
	}

	virtual void SerializeFrom(CJsonObject &json)
	{
		SERIALIZE_FROM(json, id);
		SERIALIZE_FROM(json, name);
		SERIALIZE_FROM(json, salary);
		SERIALIZE_FROM(json, no);
		SERIALIZE_FROM(json, id_vector);
		SERIALIZE_FROM(json, id_list);
		SERIALIZE_FROM(json, id_set);
		SERIALIZE_FROM(json, dept);
		SERIALIZE_FROM_VECTOR(json, dept_vector);
		SERIALIZE_FROM_LIST(json, dept_list);
		SERIALIZE_FROM_SET(json, dept_set);
	}
private:
	int id;
	std::string name;
	double salary;
	int64_t no;
	std::vector<int> id_vector;
	std::list<int> id_list;
	std::set<int> id_set;
	Department dept;
	std::vector<Department> dept_vector;
	std::list<Department> dept_list;
	std::set<Department> dept_set;
public:
	PROPERTY(id)
	PROPERTY(name)
	PROPERTY(salary)
	PROPERTY(no)
	PROPERTY(id_vector)
	PROPERTY(id_list)
	PROPERTY(id_set)
	PROPERTY(dept)
	PROPERTY(dept_vector)
	PROPERTY(dept_list)
	PROPERTY(dept_set)
};
#endif;