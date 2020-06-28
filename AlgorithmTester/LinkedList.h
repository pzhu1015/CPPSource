///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef ALGORITHMTESTER_LINKLIST_H
#define ALGORITHMTESTER_LINKLIST_H

#include <assert.h>
#include <iostream>
#include <stdlib.h>

//[head]->[node1]->[node2]-> ... ->[noden]
struct Node
{
	Node* m_next;
	int m_data;
};

//Delete all elements with value in the linked list
void DeleteFromList(Node* head, int value)
{
	Node* prev = head;
	Node* next = head->m_next;
	while (nullptr != next)
	{
		if (next->m_data != value)
		{
			prev = next;
			next = next->m_next;
		}
		else
		{
			prev->m_next = next->m_next;
			delete next;
			next = prev->m_next;
		}
	}
}

//Insert a new value element in the index position of the linked list
void InsertFromList(Node* head, int index, int value)
{
	Node* itr = head;
	for (int i = 0; i < index && nullptr != itr; ++i, itr = itr->m_next);
	assert(nullptr != itr);
	Node* node = new Node;
	node->m_data = value;
	node->m_next = itr->m_next;
	itr->m_next = node;
}

Node* ReverseLinkedList(Node* head) 
{
	//A->B->C
	Node* prev = head;
	Node* next = head->m_next;
	Node* next_next = nullptr;
	while (nullptr != next)
	{
		next_next = next->m_next;
		next->m_next = prev;

		prev = next;
		next = next_next;
	}
	head->m_next = nullptr;
	return prev;
}

bool IsLoop(Node* head)
{
	assert(nullptr != head);
	Node* next = head->m_next;
	Node* next_next = head->m_next;
	while (nullptr != next && nullptr != next_next->m_next)
	{
		next = next->m_next;
		next_next = next_next->m_next->m_next;
		if (next == next_next)
		{
			return true;
		}
	}
	return false;
}

bool DeleteBack(Node* ptr, int k)
{
	if (ptr == nullptr) return false;
	Node* p1 = ptr;
	Node* p2 = ptr;
	k--;
	while (k && p2 != nullptr)
	{
		k--;
		p2 = p2->m_next;
	}
	if (k != 0) return false;
	Node* prev = p1;
	while (p2->m_next != nullptr)
	{
		prev = p1;
		p1 = p1->m_next;
		p2 = p2->m_next;
	}

	prev->m_next = p1->m_next;
	delete p1;
	return true;
}

void Display(Node *head)// 打印链表
{
	if (head == NULL)
	{
		std::cout << "the list is empty" << std::endl;
		return;
	}
	else
	{
		Node *p = head;
		while (p)
		{
			std::cout << p->m_data << " ";
			p = p->m_next;
		}
	}
	std::cout << std::endl;
}

Node* Init(int num) // 创建链表
{
	if (num <= 0)
		return NULL;
	Node* cur = NULL;
	Node* head = NULL;
	Node* node = (Node*)malloc(sizeof(Node));
	node->m_data = 1;
	head = cur = node;
	for (int i = 1; i < num; i++)
	{
		Node* node = (Node*)malloc(sizeof(Node));
		node->m_data = i + 1;
		cur->m_next = node;
		cur = node;
	}
	cur->m_next = NULL;
	return head;
}

#endif // !ALGORITHMTESTER_LINKLIST_H
