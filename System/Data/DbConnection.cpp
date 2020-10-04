///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/DbConnection.h"
namespace System
{
	namespace Data
	{
		void DbConnection::OnStateChange(StateChangeEventArgs e)
		{
			if (StateChange != nullptr)
			{
				this->StateChange(e);
			}
		}
	}
}