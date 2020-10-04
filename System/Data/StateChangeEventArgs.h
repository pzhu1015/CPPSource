///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_STATECHANGEEVENTARGS_H
#define SYSTEM_DATA_STATECHANGEEVENTARGS_H
#define _WIN32_WINNT 0x0502
#include <afxdb.h>
#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF") rename("BOF","adoBOF")
#include "System/Base/EventArgs.h"
#include <functional>
namespace System
{
	namespace Data
	{
		class SYSTEM_API StateChangeEventArgs : EventArgs
		{
		public:
			StateChangeEventArgs() = default;
			virtual ~StateChangeEventArgs() = default;

			ObjectStateEnum GetOriginalState();
			ObjectStateEnum GetCurrentState();
		private:
			ObjectStateEnum m_original_state;
			ObjectStateEnum m_current_state;
		};
		typedef std::function<void(StateChangeEventArgs&)> StateChangeEventHandler;
	}
}
#endif // !SYSTEM_DATA_STATECHANGEEVENTARGS_H
