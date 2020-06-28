///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include <hiredis/hiredis.h>
#define NO_QFORKIMPL
#include <Win32_interop/win32fixes.h>



int main(int args, char** argv)
{
	unsigned int j;
	redisContext *c;
	redisReply *reply;

	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	c = redisConnectWithTimeout((char*)"127.0.0.1", 6379, timeout);
	if (c->err) {
		printf("Connection error: %s\n", c->errstr);
		exit(1);
	}

	/* PING server */
	reply = (redisReply *)redisCommand(c, "PING");
	if (reply)
	{
		printf("PING: %s\n", reply->str);
		freeReplyObject(reply);
	}

	/* Set a key */
	reply = (redisReply *)redisCommand(c, "SET %s %s", "foo", "hello world");
	if (reply)
	{
		printf("SET: %s\n", reply->str);
		freeReplyObject(reply);
	}

	/* Set a key using binary safe API */
	reply = (redisReply *)redisCommand(c, "SET bar %b", "hello", 5);
	if (reply)
	{
		printf("SET (binary API): %s\n", reply->str);
		freeReplyObject(reply);
	}

	/* Try a GET and two INCR */
	reply = (redisReply *)redisCommand(c, "GET foo");
	if (reply)
	{
		printf("GET foo: %s\n", reply->str);
		freeReplyObject(reply);
	}

	reply = (redisReply *)redisCommand(c, "INCR counter");
	if (reply)
	{
		printf("INCR counter: %lld\n", reply->integer);
		freeReplyObject(reply);
	}

	/* again ... */
	reply = (redisReply *)redisCommand(c, "INCR counter");
	if (reply)
	{
		printf("INCR counter: %lld\n", reply->integer);
		freeReplyObject(reply);
	}

	/* Create a list of numbers, from 0 to 9 */
	reply = (redisReply *)redisCommand(c, "DEL mylist");
	if (reply)
	{
		freeReplyObject(reply);
	}

	for (j = 0; j < 10; j++) 
	{
		char buf[64];
		sprintf_s(buf, 64, "%d", j);
		reply = (redisReply *)redisCommand(c, "LPUSH mylist element-%s", buf);
		if (reply)
		{
			freeReplyObject(reply);
		}
	}

	/* Let's check what we have inside the list */
	reply = (redisReply *)redisCommand(c, "LRANGE mylist 0 -1");
	if (reply)
	{
		if (reply->type == REDIS_REPLY_ARRAY) {
			for (j = 0; j < reply->elements; j++) {
				printf("%u) %s\n", j, reply->element[j]->str);
				getchar();
			}
		}
		freeReplyObject(reply);
	}
	system("pause");
	return 0;
}