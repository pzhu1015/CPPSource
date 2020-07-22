///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_MSG_H
#define SYSTEM_HCN_MSG_H
#include "System/DllExport.h"
namespace System
{
	namespace HCN
	{
		class SYSTEM_API Msg
		{
		public:
			Msg()
			{

			}
			~Msg()
			{

			}
			int GetLength() const
			{
				return m_length;
			}
		protected:
			int m_length = 0;
		};

		class SYSTEM_API TestMsg : public Msg
		{
		public:
			TestMsg()
			{
				m_length = sizeof(TestMsg);
			}

		private:
			char m_buff[996];
		};
	}
}
#endif // !SYSTEM_HCN_MSG_H
