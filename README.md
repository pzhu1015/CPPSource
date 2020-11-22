# CPPSource

##### *. ini配置文件的读取封装。

```C++
std::string GetValue(const std::string &section, const std::string &key, const std::string &dft_value);
int GetValue(const std::string &section, const std::string &key, int dft_value);
int64_t GetValue(const std::string &section, const std::string &key, int64_t dft_value);
double GetValue(const std::string &section, const std::string &key, double dft_value);
std::vector<ConfigOption> GetAllKeyValues(const std::string &section);
```



##### *. Data数据库操作，使用了ADO com组件的模式封,目前支持测试的有Mysql, Sqlserverl。

```C++
SqlConnection: 
virtual std::string GetConnectionString() override;
virtual void SetConnectionString(const std::string &str) override;
virtual int GetConnectionTimeout() override;
virtual std::string GetDatabase() override;
virtual void ChangeDatabase(const std::string &database) override;
virtual ObjectStateEnum GetState() override;
virtual bool Close() override;
virtual bool Open() override;
virtual DbTransactionPtr BeginTransaction() override;
virtual DbTransactionPtr BeginTransaction(IsolationLevelEnum level) override;
virtual DbCommandPtr CreateCommand() override;
template <class T>
typename std::enable_if<std::is_same<T, SqlCommandPtr>::value, T>::type CreateCommand();
const _ConnectionPtr& GetConnection() const;

SqlCommand:
virtual DbConnectionPtr GetConnection() override;
virtual void SetConnection(const DbConnectionPtr &connection) override;
virtual DbTransactionPtr GetTransaction() override;
virtual void SetTransaction(const DbTransactionPtr &transaction) override;
virtual std::string GetCommandText() override;
virtual void SetCommandText(const std::string &command) override;
virtual int GetTimeout() override;
virtual void SetTimeout(int timeout) override;
virtual CommandTypeEnum GetCommandType() override;
virtual void SetCommandType(CommandTypeEnum type) override;
virtual bool Prepare() override;
virtual bool Cancel() override;
virtual int ExecuteNoQuery() override;
virtual _variant_t ExecuteScalar() override;
virtual DbDataReaderPtr ExecuteReader() override;
virtual DbDataParameterPtr CreateParameter() override;
virtual std::vector<DbDataParameterPtr>& GetParameters() override;
virtual void SetParameters(const std::vector<DbDataParameterPtr> &params) override;
template <class T>
typename std::enable_if<std::is_same<T, SqlDataReaderPtr>::value, T>::type ExecuteReader();

SqlDataReader:
virtual bool HasRows() override;
virtual int FieldCount() override;
virtual bool IsClosed() override;
virtual int RecordsAffected() override;
virtual void Close() override;
virtual bool Read() override;
virtual bool NextResult() overrid
virtual byte GetByte(const _variant_t &ordinal) override;
virtual bool GetBool(const _variant_t &ordinal) override;
virtual DECIMAL GetDecimal(const _variant_t &ordinal) override;
virtual double GetDouble(const _variant_t &ordinal) override;
virtual float GetFloat(const _variant_t &ordinal) override;
virtual __int8 GetInt8(const _variant_t &ordinal) override;
virtual __int16 GetInt16(const _variant_t &ordinal) override;
virtual __int32 GetInt32(const _variant_t &ordinal) override;
virtual __int64 GetInt64(const _variant_t &ordinal) override;
virtual unsigned __int8 GetUInt8(const _variant_t &ordinal) override;
virtual unsigned __int16 GetUInt16(const _variant_t &ordinal) override;
virtual unsigned __int32 GetUInt32(const _variant_t &ordinal) override;
virtual unsigned __int64 GetUInt64(const _variant_t &ordinal) override;
virtual std::string GetString(const _variant_t &ordinal) override;
virtual COleDateTime GetDateTime(const _variant_t &ordinal) override;
virtual bool IsDBNull(const _variant_t &ordinal) override;
SqlParameter: 
virtual DataTypeEnum GetDbType() override;
virtual void SetDbType(DataTypeEnum type) override;
virtual bool IsNullable() override;
virtual std::string GetParameterName() override;
virtual void SetParameterName(const std::string &name) override;
virtual std::string GetSourceColumn() override;
virtual void SetSourceColumn() override;
virtual __int8 GetPrecision() override;
virtual void SetPrecision(char precision) override;
virtual __int8 GetScale() override;
virtual void SetScale(char scale) override;
virtual _variant_t GetValue() override;
virtual void SetValue(const _variant_t & value) override;
virtual ParameterDirectionEnum GetDirection() override;
virtual void SetDirection(ParameterDirectionEnum direction) override;
const _ParameterPtr &GetParameter() const;
static _ParameterPtr CreateParameter(const std::string & name, DataTypeEnum type, _variant_t & value, ParameterDirectionEnum direction);

SqlTransaction:
virtual DbConnectionPtr GetConnection() override;
virtual IsolationLevelEnum GetIsolationLevel() override;
virtual bool Commit() override;
virtual bool Rollback() override;
```



##### *. DateTime时间类型的封装使用(性能不是最佳的，后期有时间再优化)。

```C++
void AddYears(const time_t &years);
void AddMonths(const time_t &months);
void AddDays(const time_t &days);
void AddHours(const time_t &hours);
void AddMinutes(const time_t &minutes);
void AddSeconds(const time_t &seconds);
void AddWeeks(const time_t &weeks);
int CompareTo(const DateTime *datetime)  const;
bool Equals(const DateTime* datetime)  cons
std::string ToString(const std::string &format) const;
std::string ToString() cons
int GetYear() const;
int GetMonth() const;
int GetDay() const;
int GetHour() const;
int GetMinute() const;
int GetSecond() const;
int DayOfWeek() const;
int DayOfYear() cons
bool operator == (const DateTime &datetime) const;
bool operator > (const DateTime &datetime) const;
bool operator < (const DateTime &datetime) const;
bool operator >= (const DateTime &datetime) const;
bool operator <= (const DateTime &datetime) const;
bool operator != (const DateTime &datetime) cons
static DateTime GetNow();
static int Comare(const DateTime& value1, const DateTime& value2);
static bool Equals(const DateTime& value1, const DateTime& value2);
static DateTime Parse(const std::string &str);
static DateTime Parse(const std::string &str, const std::string &format);
```



##### *. Exceptions, 内部的一些异常封。

```C++
#include "System/Exceptions/Exception.h"
#include "System/Exceptions/ArgumentException.h"
#include "System/Exceptions/ArgumentNullException.h"
#include "System/Exceptions/ArgumentOutOfRangeException.h"
#include "System/Exceptions/ArrayTypeMismatchException.h"
#include "System/Exceptions/IndexOutOfRangeException.h"
#include "System/Exceptions/InvalidOperationException.h"
#include "System/Exceptions/IOException.h"
#include "System/Exceptions/NotSupportedException.h"
#include "System/Exceptions/NullReferenceException.h"
#include "System/Exceptions/OverflowException.h"
#include "System/Exceptions/RedisException.h"
#include "System/Exceptions/SocketException.h"
#include "System/Exceptions/SqlException.h"

using namespace System::Exceptions;
void TestArgumentException()
{
	throw ArgumentException("arg error");
}

void TestArgumentNullException()
{
	throw ArgumentNullException("arg is nullptr");
}

void TestArgumentOutOfRangeException()
{
	throw ArgumentOutOfRangeException("arg out of range");
}

void TestArrayTypeMismatchException()
{
	throw ArrayTypeMismatchException("array type miss match");
}

void TestException()
{
	throw Exception("Exception");
}

void TestIndexOutOfRangeException()
{
	throw IndexOutOfRangeException("index out of range");
}

void TestInvalidOperationException()
{
	throw InvalidOperationException("invalid operation");
}

void TestIOException()
{
	throw IOException("io error");
}

void TestNotSupportedException()
{
	throw NotSupportedException(__func__);
}

void TestNullReferenceException()
{
	throw NullReferenceException("is nullptr");
}

void TestOverflowException()
{
	throw OverflowException("over flow");
}

void TestRedisException()
{
	throw RedisException("redis error");
}

void TestSocketException()
{
	throw SocketException("socket error");
}

void TestSqlException()
{
	throw SqlException("sql error");
}
int main(int argc, char** argv)
{
	try
	{
		TestArgumentException();
	}
	catch (ArgumentException &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		TestArgumentNullException();
	}
	catch (ArgumentNullException &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		TestArgumentOutOfRangeException();
	}
	catch (ArgumentOutOfRangeException &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		TestArrayTypeMismatchException();
	}
	catch (ArrayTypeMismatchException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestIndexOutOfRangeException();
	}
	catch (IndexOutOfRangeException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestInvalidOperationException();
	}
	catch (InvalidOperationException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestIOException();
	}
	catch (IOException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestNotSupportedException();
	}
	catch (NotSupportedException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestNullReferenceException();
	}
	catch (NullReferenceException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestOverflowException();
	}
	catch (OverflowException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestRedisException();
	}
	catch (RedisException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestSocketException();
	}
	catch (SocketException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestSqlException();
	}
	catch (SqlException &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		TestException();
	}
	catch (Exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	getchar();
	return 1;
}
```



##### *. Net, HCN, 高并发网络通信，装装了原生的Socket, TcpServer, TcpClient。

##### *. Json序列化，包括数组(vector，list，set)，或自定义对象。

##### *. Redis使用了cpp_redis开源库，封了连接池，基本哲作，外部提供c++11的接口。

##### *. Threading, 使用C++11封装，包括Semphore。

##### *. IO使用C++11 iostream封装了文件操作。
