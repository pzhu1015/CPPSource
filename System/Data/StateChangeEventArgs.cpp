///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/StateChangeEventArgs.h"
namespace System
{
	namespace Data
	{
		ObjectStateEnum StateChangeEventArgs::GetOriginalState()
		{
			return m_original_state;
		}
		ObjectStateEnum StateChangeEventArgs::GetCurrentState()
		{
			return m_current_state;
		}
	}
}