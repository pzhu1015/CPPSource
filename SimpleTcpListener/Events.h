///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SIMPLETCPLISTENER_EVENTS_H
#define SIMPLETCPLISTENER_EVENTS_H
#include <functional>
class ProcessStartEventArgs;
class OnLineEventArgs;
class OffLineEventArgs;

class TcpStartEventArgs;
class TcpStopEventArgs;
class TcpAcceptEventArgs;
class TcpReceiveEventArgs;
class TcpSendEventArgs;
class TcpSelectErrorEventArgs;
class ProcessStartEventArgs;

typedef std::function<void(ProcessStartEventArgs*)> ProcessStartEventHandler;
typedef std::function<void(OnLineEventArgs*)> OnLineEventHandler;
typedef std::function<void(OffLineEventArgs*)> OffLineEventHandler;

typedef std::function<void(TcpStartEventArgs*)> TcpStartEventHandler;
typedef std::function<void(TcpStopEventArgs*)> TcpSTopEventHandler;
typedef std::function<void(TcpAcceptEventArgs*)> TcpAccetpEventHandler;
typedef std::function<void(TcpReceiveEventArgs*)> TcpReceiveEventHandler;
typedef std::function<void(TcpSendEventArgs*)> TcpSendEventHandler;
typedef std::function<void(TcpSelectErrorEventArgs*)> TcpSelectErrorEventHandler;

#endif // !SIMPLETCPLISTENER_EVENTS_H
