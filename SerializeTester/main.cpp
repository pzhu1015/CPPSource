///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Serializers/JsonSerialize.h"
#include "System/DateTimes/DateTime.h"
#include <iostream>
using namespace System::Serializers;
using namespace System::DateTimes;
struct TesterObj;
typedef std::shared_ptr<TesterObj> TesterObjPtr;
struct TesterObj : public JsonSerialize
{
	TesterObj() = default;
	TesterObj(
		__int8								int8_,
		__int16								int16_,
		__int32								int32_,
		__int64								int64_,
		unsigned __int8						uint8_,
		unsigned __int16					uint16_,
		unsigned __int32					uint32_,
		unsigned __int64					uint64_,
		bool								bool_,
		float								float_,
		double								double_,
		std::string							&string_,
											
		std::vector<__int8>					&v_int8_,
		std::vector<__int16>				&v_int16_,
		std::vector<__int32>				&v_int32_,
		std::vector<__int64>				&v_int64_,
		std::vector<unsigned __int8>		&v_uint8_,
		std::vector<unsigned __int16>		&v_uint16_,
		std::vector<unsigned __int32>		&v_uint32_,
		std::vector<unsigned __int64>		&v_uint64_,
		std::vector<bool>					&v_bool_,
		std::vector<float>					&v_float_,
		std::vector<double>					&v_double_,
		const std::vector<std::string>		&v_string_,
		 									
		const std::list<__int8>				&l_int8_,
		const std::list<__int16>			&l_int16_,
		const std::list<__int32>			&l_int32_,
		const std::list<__int64>			&l_int64_,
		const std::list<unsigned __int8>	&l_uint8_,
		const std::list<unsigned __int16>	&l_uint16_,
		const std::list<unsigned __int32>	&l_uint32_,
		const std::list<unsigned __int64>	&l_uint64_,
		const std::list<bool>				&l_bool_,
		const std::list<float>				&l_float_,
		const std::list<double>				&l_double_,
		const std::list<std::string>		&l_string_,
		 									
		const std::set<__int8>				&s_int8_,
		const std::set<__int16>				&s_int16_,
		const std::set<__int32>				&s_int32_,
		const std::set<__int64>				&s_int64_,
		const std::set<unsigned __int8>		&s_uint8_,
		const std::set<unsigned __int16>	&s_uint16_,
		const std::set<unsigned __int32>	&s_uint32_,
		const std::set<unsigned __int64>	&s_uint64_,
		const std::set<bool>				&s_bool_,
		const std::set<float>				&s_float_,
		const std::set<double>				&s_double_,
		const std::set<std::string>			&s_string_
	)
	{
		this->int8_			= int8_;
		this->int16_		= int16_;
		this->int32_		= int32_;
		this->int64_		= int64_;
		this->uint8_		= uint8_;
		this->uint16_		= uint16_;
		this->uint32_		= uint32_;
		this->uint64_		= uint64_;
		this->bool_			= bool_;
		this->float_		= float_;
		this->double_		= double_;
		this->string_		= string_;
							
		this->v_int8_		= v_int8_;
		this->v_int16_		= v_int16_;
		this->v_int32_		= v_int32_;
		this->v_int64_		= v_int64_;
		this->v_uint8_		= v_uint8_;
		this->v_uint16_		= v_uint16_;
		this->v_uint32_		= v_uint32_;
		this->v_uint64_		= v_uint64_;
		this->v_bool_		= v_bool_;
		this->v_float_		= v_float_;
		this->v_double_		= v_double_;
		this->v_string_		= v_string_;
							
		this->l_int8_		= l_int8_;
		this->l_int16_		= l_int16_;
		this->l_int32_		= l_int32_;
		this->l_int64_		= l_int64_;
		this->l_uint8_		= l_uint8_;
		this->l_uint16_		= l_uint16_;
		this->l_uint32_		= l_uint32_;
		this->l_uint64_		= l_uint64_;
		this->l_bool_		= l_bool_;
		this->l_float_		= l_float_;
		this->l_double_		= l_double_;
		this->l_string_		= l_string_;
							
		this->s_int8_		= s_int8_;
		this->s_int16_		= s_int16_;
		this->s_int32_		= s_int32_;
		this->s_int64_		= s_int64_;
		this->s_uint8_		= s_uint8_;
		this->s_uint16_		= s_uint16_;
		this->s_uint32_		= s_uint32_;
		this->s_uint64_		= s_uint64_;
		this->s_bool_		= s_bool_;
		this->s_float_		= s_float_;
		this->s_double_		= s_double_;
		this->s_string_		= s_string_;
	}
	virtual ~TesterObj() = default;
	virtual void SerializeTo(CJsonObject &json) override
	{
		SERIALIZE_TO(json, int8_);
		SERIALIZE_TO(json, int16_);
		SERIALIZE_TO(json, int32_);
		SERIALIZE_TO(json, int64_);
		SERIALIZE_TO(json, uint8_);
		SERIALIZE_TO(json, uint16_);
		SERIALIZE_TO(json, uint32_);
		SERIALIZE_TO(json, uint64_);
		SERIALIZE_TO(json, bool_);
		SERIALIZE_TO(json, float_);
		SERIALIZE_TO(json, double_);
		SERIALIZE_TO(json, string_);

		SERIALIZE_TO(json, v_int8_);
		SERIALIZE_TO(json, v_int16_);
		SERIALIZE_TO(json, v_int32_);
		SERIALIZE_TO(json, v_int64_);
		SERIALIZE_TO(json, v_uint8_);
		SERIALIZE_TO(json, v_uint16_);
		SERIALIZE_TO(json, v_uint32_);
		SERIALIZE_TO(json, v_uint64_);
		SERIALIZE_TO(json, v_bool_);
		SERIALIZE_TO(json, v_float_);
		SERIALIZE_TO(json, v_double_);
		SERIALIZE_TO(json, v_string_);

		SERIALIZE_TO(json, l_int8_);
		SERIALIZE_TO(json, l_int16_);
		SERIALIZE_TO(json, l_int32_);
		SERIALIZE_TO(json, l_int64_);
		SERIALIZE_TO(json, l_uint8_);
		SERIALIZE_TO(json, l_uint16_);
		SERIALIZE_TO(json, l_uint32_);
		SERIALIZE_TO(json, l_uint64_);
		SERIALIZE_TO(json, l_bool_);
		SERIALIZE_TO(json, l_float_);
		SERIALIZE_TO(json, l_double_);
		SERIALIZE_TO(json, l_string_);

		SERIALIZE_TO(json, s_int8_);
		SERIALIZE_TO(json, s_int16_);
		SERIALIZE_TO(json, s_int32_);
		SERIALIZE_TO(json, s_int64_);
		SERIALIZE_TO(json, s_uint8_);
		SERIALIZE_TO(json, s_uint16_);
		SERIALIZE_TO(json, s_uint32_);
		SERIALIZE_TO(json, s_uint64_);
		SERIALIZE_TO(json, s_bool_);
		SERIALIZE_TO(json, s_float_);
		SERIALIZE_TO(json, s_double_);
		SERIALIZE_TO(json, s_string_);
	}

	virtual void SerializeFrom(CJsonObject &json) override
	{
		SERIALIZE_FROM(json, int8_);
		SERIALIZE_FROM(json, int16_);
		SERIALIZE_FROM(json, int32_);
		SERIALIZE_FROM(json, int64_);
		SERIALIZE_FROM(json, uint8_);
		SERIALIZE_FROM(json, uint16_);
		SERIALIZE_FROM(json, uint32_);
		SERIALIZE_FROM(json, uint64_);
		SERIALIZE_FROM(json, bool_);
		SERIALIZE_FROM(json, float_);
		SERIALIZE_FROM(json, double_);
		SERIALIZE_FROM(json, string_);
				  
		SERIALIZE_FROM(json, v_int8_);
		SERIALIZE_FROM(json, v_int16_);
		SERIALIZE_FROM(json, v_int32_);
		SERIALIZE_FROM(json, v_int64_);
		SERIALIZE_FROM(json, v_uint8_);
		SERIALIZE_FROM(json, v_uint16_);
		SERIALIZE_FROM(json, v_uint32_);
		SERIALIZE_FROM(json, v_uint64_);
		SERIALIZE_FROM(json, v_bool_);
		SERIALIZE_FROM(json, v_float_);
		SERIALIZE_FROM(json, v_double_);
		SERIALIZE_FROM(json, v_string_);
				  
		SERIALIZE_FROM(json, l_int8_);
		SERIALIZE_FROM(json, l_int16_);
		SERIALIZE_FROM(json, l_int32_);
		SERIALIZE_FROM(json, l_int64_);
		SERIALIZE_FROM(json, l_uint8_);
		SERIALIZE_FROM(json, l_uint16_);
		SERIALIZE_FROM(json, l_uint32_);
		SERIALIZE_FROM(json, l_uint64_);
		SERIALIZE_FROM(json, l_bool_);
		SERIALIZE_FROM(json, l_float_);
		SERIALIZE_FROM(json, l_double_);
		SERIALIZE_FROM(json, l_string_);
				  
		SERIALIZE_FROM(json, s_int8_);
		SERIALIZE_FROM(json, s_int16_);
		SERIALIZE_FROM(json, s_int32_);
		SERIALIZE_FROM(json, s_int64_);
		SERIALIZE_FROM(json, s_uint8_);
		SERIALIZE_FROM(json, s_uint16_);
		SERIALIZE_FROM(json, s_uint32_);
		SERIALIZE_FROM(json, s_uint64_);
		SERIALIZE_FROM(json, s_bool_);
		SERIALIZE_FROM(json, s_float_);
		SERIALIZE_FROM(json, s_double_);
		SERIALIZE_FROM(json, s_string_);
	}

	virtual bool operator<(const TesterObj &obj) const
	{
		return int8_ < obj.int8_;
	}

	virtual bool operator==(const TesterObj &obj) const
	{
		return int8_ == obj.int8_;
	}

	__int8								int8_;
	__int16								int16_;
	__int32								int32_;
	__int64								int64_;
	unsigned __int8						uint8_;
	unsigned __int16					uint16_;
	unsigned __int32					uint32_;
	unsigned __int64					uint64_;
	bool								bool_;
	float								float_;
	double								double_;
	std::string							string_;

	std::vector<__int8>					v_int8_;
	std::vector<__int16>				v_int16_;
	std::vector<__int32>				v_int32_;
	std::vector<__int64>				v_int64_;
	std::vector<unsigned __int8>		v_uint8_;
	std::vector<unsigned __int16>		v_uint16_;
	std::vector<unsigned __int32>		v_uint32_;
	std::vector<unsigned __int64>		v_uint64_;
	std::vector<bool>					v_bool_;
	std::vector<float>					v_float_;
	std::vector<double>					v_double_;
	std::vector<std::string>			v_string_;

	std::list<__int8>					l_int8_;
	std::list<__int16>					l_int16_;
	std::list<__int32>					l_int32_;
	std::list<__int64>					l_int64_;
	std::list<unsigned __int8>			l_uint8_;
	std::list<unsigned __int16>			l_uint16_;
	std::list<unsigned __int32>			l_uint32_;
	std::list<unsigned __int64>			l_uint64_;
	std::list<bool>						l_bool_;
	std::list<float>					l_float_;
	std::list<double>					l_double_;
	std::list<std::string>				l_string_;

	std::set<__int8>					s_int8_;
	std::set<__int16>					s_int16_;
	std::set<__int32>					s_int32_;
	std::set<__int64>					s_int64_;
	std::set<unsigned __int8>			s_uint8_;
	std::set<unsigned __int16>			s_uint16_;
	std::set<unsigned __int32>			s_uint32_;
	std::set<unsigned __int64>			s_uint64_;
	std::set<bool>						s_bool_;
	std::set<float>						s_float_;
	std::set<double>					s_double_;
	std::set<std::string>				s_string_;
};
struct Tester : public JsonSerialize
{
public:
	Tester() = default;
	virtual ~Tester() = default;
	virtual void SerializeTo(CJsonObject &json) override
	{
		SERIALIZE_TO(json, int8_);
		SERIALIZE_TO(json, int16_);
		SERIALIZE_TO(json, int32_);
		SERIALIZE_TO(json, int64_);
		SERIALIZE_TO(json, uint8_);
		SERIALIZE_TO(json, uint16_);
		SERIALIZE_TO(json, uint32_);
		SERIALIZE_TO(json, uint64_);
		SERIALIZE_TO(json, bool_);
		SERIALIZE_TO(json, float_);
		SERIALIZE_TO(json, double_);
		SERIALIZE_TO(json, string_);
		SERIALIZE_TO(json, obj_);
		SERIALIZE_TO(json, obj_ptr_);

		SERIALIZE_TO(json, v_int8_);
		SERIALIZE_TO(json, v_int16_);
		SERIALIZE_TO(json, v_int32_);
		SERIALIZE_TO(json, v_int64_);
		SERIALIZE_TO(json, v_uint8_);
		SERIALIZE_TO(json, v_uint16_);
		SERIALIZE_TO(json, v_uint32_);
		SERIALIZE_TO(json, v_uint64_);
		SERIALIZE_TO(json, v_bool_);
		SERIALIZE_TO(json, v_float_);
		SERIALIZE_TO(json, v_double_);
		SERIALIZE_TO(json, v_string_);
		SERIALIZE_TO(json, v_obj_);
		SERIALIZE_TO(json, v_obj_ptr_);

		SERIALIZE_TO(json, l_int8_);
		SERIALIZE_TO(json, l_int16_);
		SERIALIZE_TO(json, l_int32_);
		SERIALIZE_TO(json, l_int64_);
		SERIALIZE_TO(json, l_uint8_);
		SERIALIZE_TO(json, l_uint16_);
		SERIALIZE_TO(json, l_uint32_);
		SERIALIZE_TO(json, l_uint64_);
		SERIALIZE_TO(json, l_bool_);
		SERIALIZE_TO(json, l_float_);
		SERIALIZE_TO(json, l_double_);
		SERIALIZE_TO(json, l_string_);
		SERIALIZE_TO(json, l_obj_);
		SERIALIZE_TO(json, l_obj_ptr_);

		SERIALIZE_TO(json, s_int8_);
		SERIALIZE_TO(json, s_int16_);
		SERIALIZE_TO(json, s_int32_);
		SERIALIZE_TO(json, s_int64_);
		SERIALIZE_TO(json, s_uint8_);
		SERIALIZE_TO(json, s_uint16_);
		SERIALIZE_TO(json, s_uint32_);
		SERIALIZE_TO(json, s_uint64_);
		SERIALIZE_TO(json, s_bool_);
		SERIALIZE_TO(json, s_float_);
		SERIALIZE_TO(json, s_double_);
		SERIALIZE_TO(json, s_string_);
		SERIALIZE_TO(json, s_obj_);
		SERIALIZE_TO(json, s_obj_ptr_);
	}

	virtual void SerializeFrom(CJsonObject &json) override
	{
		SERIALIZE_FROM(json, int8_);
		SERIALIZE_FROM(json, int16_);
		SERIALIZE_FROM(json, int32_);
		SERIALIZE_FROM(json, int64_);
		SERIALIZE_FROM(json, uint8_);
		SERIALIZE_FROM(json, uint16_);
		SERIALIZE_FROM(json, uint32_);
		SERIALIZE_FROM(json, uint64_);
		SERIALIZE_FROM(json, bool_);
		SERIALIZE_FROM(json, float_);
		SERIALIZE_FROM(json, double_);
		SERIALIZE_FROM(json, string_);
		SERIALIZE_FROM(json, obj_);
		SERIALIZE_FROM(json, obj_ptr_);

		SERIALIZE_FROM(json, v_int8_);
		SERIALIZE_FROM(json, v_int16_);
		SERIALIZE_FROM(json, v_int32_);
		SERIALIZE_FROM(json, v_int64_);
		SERIALIZE_FROM(json, v_uint8_);
		SERIALIZE_FROM(json, v_uint16_);
		SERIALIZE_FROM(json, v_uint32_);
		SERIALIZE_FROM(json, v_uint64_);
		SERIALIZE_FROM(json, v_bool_);
		SERIALIZE_FROM(json, v_float_);
		SERIALIZE_FROM(json, v_double_);
		SERIALIZE_FROM(json, v_string_);
		SERIALIZE_FROM(json, v_obj_);
		SERIALIZE_FROM(json, v_obj_ptr_);

		SERIALIZE_FROM(json, l_int8_);
		SERIALIZE_FROM(json, l_int16_);
		SERIALIZE_FROM(json, l_int32_);
		SERIALIZE_FROM(json, l_int64_);
		SERIALIZE_FROM(json, l_uint8_);
		SERIALIZE_FROM(json, l_uint16_);
		SERIALIZE_FROM(json, l_uint32_);
		SERIALIZE_FROM(json, l_uint64_);
		SERIALIZE_FROM(json, l_bool_);
		SERIALIZE_FROM(json, l_float_);
		SERIALIZE_FROM(json, l_double_);
		SERIALIZE_FROM(json, l_string_);
		SERIALIZE_FROM(json, l_obj_);
		SERIALIZE_FROM(json, l_obj_ptr_);

		SERIALIZE_FROM(json, s_int8_);
		SERIALIZE_FROM(json, s_int16_);
		SERIALIZE_FROM(json, s_int32_);
		SERIALIZE_FROM(json, s_int64_);
		SERIALIZE_FROM(json, s_uint8_);
		SERIALIZE_FROM(json, s_uint16_);
		SERIALIZE_FROM(json, s_uint32_);
		SERIALIZE_FROM(json, s_uint64_);
		SERIALIZE_FROM(json, s_bool_);
		SERIALIZE_FROM(json, s_float_);
		SERIALIZE_FROM(json, s_double_);
		SERIALIZE_FROM(json, s_string_);
		SERIALIZE_FROM(json, s_obj_);
		SERIALIZE_FROM(json, s_obj_ptr_);
	}

	__int8								int8_;
	__int16								int16_;
	__int32								int32_;
	__int64								int64_;
	unsigned __int8						uint8_;
	unsigned __int16					uint16_;
	unsigned __int32					uint32_;
	unsigned __int64					uint64_;
	bool								bool_;
	float								float_;
	double								double_;
	std::string							string_;
	TesterObj							obj_;
	TesterObjPtr						obj_ptr_;

	std::vector<__int8>					v_int8_;
	std::vector<__int16>				v_int16_;
	std::vector<__int32>				v_int32_;
	std::vector<__int64>				v_int64_;
	std::vector<unsigned __int8>		v_uint8_;
	std::vector<unsigned __int16>		v_uint16_;
	std::vector<unsigned __int32>		v_uint32_;
	std::vector<unsigned __int64>		v_uint64_;
	std::vector<bool>					v_bool_;
	std::vector<float>					v_float_;
	std::vector<double>					v_double_;
	std::vector<std::string>			v_string_;
	std::vector<TesterObj>				v_obj_;
	std::vector<TesterObjPtr>			v_obj_ptr_;

	std::list<__int8>					l_int8_;
	std::list<__int16>					l_int16_;
	std::list<__int32>					l_int32_;
	std::list<__int64>					l_int64_;
	std::list<unsigned __int8>			l_uint8_;
	std::list<unsigned __int16>			l_uint16_;
	std::list<unsigned __int32>			l_uint32_;
	std::list<unsigned __int64>			l_uint64_;
	std::list<bool>						l_bool_;
	std::list<float>					l_float_;
	std::list<double>					l_double_;
	std::list<std::string>				l_string_;
	std::list<TesterObj>				l_obj_;
	std::list<TesterObjPtr>				l_obj_ptr_;

	std::set<__int8>					s_int8_;
	std::set<__int16>					s_int16_;
	std::set<__int32>					s_int32_;
	std::set<__int64>					s_int64_;
	std::set<unsigned __int8>			s_uint8_;
	std::set<unsigned __int16>			s_uint16_;
	std::set<unsigned __int32>			s_uint32_;
	std::set<unsigned __int64>			s_uint64_;
	std::set<bool>						s_bool_;
	std::set<float>						s_float_;
	std::set<double>					s_double_;
	std::set<std::string>				s_string_;
	std::set<TesterObj>					s_obj_;
	std::set<TesterObjPtr>				s_obj_ptr_;
};

int main(int argc, char** argv)
{
	TesterObj testerobj;
	testerobj.int8_ = (-127i8 - 1);
	testerobj.int16_ = (-32767i16 - 1);
	testerobj.int32_ = (-2147483647i32 - 1);
	testerobj.int64_ = (-9223372036854775807i64 - 1);
	testerobj.uint8_ = 0xffui8;
	testerobj.uint16_ = 0xffffui16;
	testerobj.uint32_ = 0xffffffffui32;
	testerobj.uint64_ = 0xffffffffffffffffui64;
	testerobj.bool_ = false;
	testerobj.float_ = 100000.09F;
	testerobj.double_ = 100000.00009;
	testerobj.string_ = "string";

	testerobj.v_int8_ = { (-127i8 - 1), 127i8 };
	testerobj.v_int16_ = { (-32767i16 - 1), 32767i16 };
	testerobj.v_int32_ = { (-2147483647i32 - 1), 2147483647i32 };
	testerobj.v_int64_ = { (-9223372036854775807i64 - 1), 9223372036854775807i64 };
	testerobj.v_uint8_ = { 0i8, 0xffui8 };
	testerobj.v_uint16_ = { 0ui16, 0xffffui16 };
	testerobj.v_uint32_ = { 0ui32, 0xffffffffui32 };
	testerobj.v_uint64_ = { 0ui64, 0xffffffffffffffffui64 };
	testerobj.v_bool_ = { false, true };
	testerobj.v_float_ = { 100000.09F, 100000.29F };
	testerobj.v_double_ = { 100000.00009, 100000.10009 };
	testerobj.v_string_ = { "string", "string" };

	testerobj.l_int8_ = { (-127i8 - 1), 127i8 };
	testerobj.l_int16_ = { (-32767i16 - 1), 32767i16 };
	testerobj.l_int32_ = { (-2147483647i32 - 1), 2147483647i32 };
	testerobj.l_int64_ = { (-9223372036854775807i64 - 1), 9223372036854775807i64 };
	testerobj.l_uint8_ = { 0ui8, 0xffui8 };
	testerobj.l_uint16_ = { 0ui16, 0xffffui16 };
	testerobj.l_uint32_ = { 0ui32, 0xffffffffui32 };
	testerobj.l_uint64_ = { 0ui64, 0xffffffffffffffffui64 };
	testerobj.l_bool_ = { false, true };
	testerobj.l_float_ = { 100000.09F, 100000.19F };
	testerobj.l_double_ = { 100000.00009, 100000.20009 };
	testerobj.l_string_ = { "string", "string" };

	testerobj.s_int8_ = { (-127i8 - 1), 127i8 };
	testerobj.s_int16_ = { (-32767i16 - 1), 32767i16 };
	testerobj.s_int32_ = { (-2147483647i32 - 1), 2147483647i32 };
	testerobj.s_int64_ = { (-9223372036854775807i64 - 1), 9223372036854775807i64 };
	testerobj.s_uint8_ = { 0ui8, 0xffui8 };
	testerobj.s_uint16_ = { 0ui16, 0xffffui16 };
	testerobj.s_uint32_ = { 0ui32, 0xffffffffui32 };
	testerobj.s_uint64_ = { 0ui64, 0xffffffffffffffffui64 };
	testerobj.s_bool_ = { false, true };
	testerobj.s_float_ = { 100000.09F, 100000.09F };
	testerobj.s_double_ = { 100000.00009, 100000.00009 };
	testerobj.s_string_ = { "string", "string" };


	TesterObjPtr testerobjptr = std::make_shared<TesterObj>();
	testerobjptr->int8_ = (-127i8 - 1);
	testerobjptr->int16_ = (-32767i16 - 1);
	testerobjptr->int32_ = (-2147483647i32 - 1);
	testerobjptr->int64_ = (-9223372036854775807i64 - 1);
	testerobjptr->uint8_ = 0xffui8;
	testerobjptr->uint16_ = 0xffffui16;
	testerobjptr->uint32_ = 0xffffffffui32;
	testerobjptr->uint64_ = 0xffffffffffffffffui64;
	testerobjptr->bool_ = false;
	testerobjptr->float_ = 100000.09F;
	testerobjptr->double_ = 100000.00009;
	testerobjptr->string_ = "string";
			
	testerobjptr->v_int8_ = { (-127i8 - 1), 127i8 };
	testerobjptr->v_int16_ = { (-32767i16 - 1), 32767i16 };
	testerobjptr->v_int32_ = { (-2147483647i32 - 1), 2147483647i32 };
	testerobjptr->v_int64_ = { (-9223372036854775807i64 - 1), 9223372036854775807i64 };
	testerobjptr->v_uint8_ = { 0i8, 0xffui8 };
	testerobjptr->v_uint16_ = { 0ui16, 0xffffui16 };
	testerobjptr->v_uint32_ = { 0ui32, 0xffffffffui32 };
	testerobjptr->v_uint64_ = { 0ui64, 0xffffffffffffffffui64 };
	testerobjptr->v_bool_ = { false, true };
	testerobjptr->v_float_ = { 100000.09F, 100000.29F };
	testerobjptr->v_double_ = { 100000.00009, 100000.10009 };
	testerobjptr->v_string_ = { "string", "string" };
			 
	testerobjptr->l_int8_ = { (-127i8 - 1), 127i8 };
	testerobjptr->l_int16_ = { (-32767i16 - 1), 32767i16 };
	testerobjptr->l_int32_ = { (-2147483647i32 - 1), 2147483647i32 };
	testerobjptr->l_int64_ = { (-9223372036854775807i64 - 1), 9223372036854775807i64 };
	testerobjptr->l_uint8_ = { 0ui8, 0xffui8 };
	testerobjptr->l_uint16_ = { 0ui16, 0xffffui16 };
	testerobjptr->l_uint32_ = { 0ui32, 0xffffffffui32 };
	testerobjptr->l_uint64_ = { 0ui64, 0xffffffffffffffffui64 };
	testerobjptr->l_bool_ = { false, true };
	testerobjptr->l_float_ = { 100000.09F, 100000.19F };
	testerobjptr->l_double_ = { 100000.00009, 100000.20009 };
	testerobjptr->l_string_ = { "string", "string" };
			 
	testerobjptr->s_int8_ = { (-127i8 - 1), 127i8 };
	testerobjptr->s_int16_ = { (-32767i16 - 1), 32767i16 };
	testerobjptr->s_int32_ = { (-2147483647i32 - 1), 2147483647i32 };
	testerobjptr->s_int64_ = { (-9223372036854775807i64 - 1), 9223372036854775807i64 };
	testerobjptr->s_uint8_ = { 0ui8, 0xffui8 };
	testerobjptr->s_uint16_ = { 0ui16, 0xffffui16 };
	testerobjptr->s_uint32_ = { 0ui32, 0xffffffffui32 };
	testerobjptr->s_uint64_ = { 0ui64, 0xffffffffffffffffui64 };
	testerobjptr->s_bool_ = { false, true };
	testerobjptr->s_float_ = { 100000.09F, 100000.09F };
	testerobjptr->s_double_ = { 100000.00009, 100000.00009 };
	testerobjptr->s_string_ = { "string", "string" };

	Tester tester;
	tester.int8_ = (-127i8 - 1);
	tester.int16_ = (-32767i16 - 1);
	tester.int32_ = (-2147483647i32 - 1);
	tester.int64_ = (-9223372036854775807i64 - 1);
	tester.uint8_ = 0xffui8;
	tester.uint16_ = 0xffffui16;
	tester.uint32_ = 0xffffffffui32;
	tester.uint64_ = 0xffffffffffffffffui64;
	tester.bool_ = false;
	tester.float_ = 100000.09F;
	tester.double_ = 100000.00009;
	tester.string_ = "string";
	tester.obj_ = testerobj;
	tester.obj_ptr_ = testerobjptr;

	tester.v_int8_ = { (-127i8 - 1), 127i8 };
	tester.v_int16_ = { (-32767i16 - 1), 32767i16 };
	tester.v_int32_ = { (-2147483647i32 - 1), 2147483647i32 };
	tester.v_int64_ = { (-9223372036854775807i64 - 1), 9223372036854775807i64 };
	tester.v_uint8_ = { 0i8, 0xffui8 };
	tester.v_uint16_ = { 0ui16, 0xffffui16 };
	tester.v_uint32_ = { 0ui32, 0xffffffffui32 };
	tester.v_uint64_ = { 0ui64, 0xffffffffffffffffui64 };
	tester.v_bool_ = { false, true };
	tester.v_float_ = { 100000.09F, 100000.29F };
	tester.v_double_ = { 100000.00009, 100000.10009 };
	tester.v_string_ = { "string", "string" };
	tester.v_obj_ = { testerobj, testerobj };
	tester.v_obj_ptr_ = { testerobjptr, testerobjptr };

	tester.l_int8_ = { (-127i8 - 1), 127i8 };
	tester.l_int16_ = { (-32767i16 - 1), 32767i16 };
	tester.l_int32_ = { (-2147483647i32 - 1), 2147483647i32 };
	tester.l_int64_ = { (-9223372036854775807i64 - 1), 9223372036854775807i64 };
	tester.l_uint8_ = { 0i8, 0xffui8 };
	tester.l_uint16_ = { 0ui16, 0xffffui16 };
	tester.l_uint32_ = { 0ui32, 0xffffffffui32 };
	tester.l_uint64_ = { 0ui64, 0xffffffffffffffffui64 };
	tester.l_bool_ = { false, true };
	tester.l_float_ = { 100000.09F, 100000.29F };
	tester.l_double_ = { 100000.00009, 100000.10009 };
	tester.l_string_ = { "string", "string" };
	tester.l_obj_ = { testerobj, testerobj };
	tester.l_obj_ptr_ = { testerobjptr, testerobjptr };

	tester.s_int8_ = { (-127i8 - 1), 127i8 };
	tester.s_int16_ = { (-32767i16 - 1), 32767i16 };
	tester.s_int32_ = { (-2147483647i32 - 1), 2147483647i32 };
	tester.s_int64_ = { (-9223372036854775807i64 - 1), 9223372036854775807i64 };
	tester.s_uint8_ = { 0i8, 0xffui8 };
	tester.s_uint16_ = { 0ui16, 0xffffui16 };
	tester.s_uint32_ = { 0ui32, 0xffffffffui32 };
	tester.s_uint64_ = { 0ui64, 0xffffffffffffffffui64 };
	tester.s_bool_ = { false, true };
	tester.s_float_ = { 100000.09F, 100000.29F };
	tester.s_double_ = { 100000.00009, 100000.10009 };
	tester.s_string_ = { "string", "string" };
	tester.s_obj_ = { testerobj, testerobj };
	tester.s_obj_ptr_ = { testerobjptr, testerobjptr };

	__int64 t1 = GetTimestamp();
	int total = 10000;
	CJsonObject json;
	while (total--)
	{
		json.Clear();
		tester.SerializeTo(json);
	}
	__int64 t2 = GetTimestamp();
	std::cout << json.ToFormattedString() << std::endl;
	std::cout << "cost: " << (t2 - t1) / 1000.0 << std::endl;

	system("pause");
}