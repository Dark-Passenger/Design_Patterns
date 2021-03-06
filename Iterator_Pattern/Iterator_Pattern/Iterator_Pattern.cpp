// Iterator_Pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>
#include <type_traits>

using namespace std::string_literals;

template<typename T>
class mylist
{
private:
  class Node
  {
  private:
    T data;
    Node* pNext;
    friend class mylist;

  public:
    Node(T _data) : data(std::move(_data)), pNext(nullptr) {}
    ~Node() = default;
  };

  Node* m_spRoot;

  Node* GetNode(T data)
  {
    return new Node(std::move(data));
  }

  Node*& GetRootNode()
  {
    return m_spRoot;
  }

public:
  mylist() : m_spRoot(nullptr) {}

  class iterator
  {
  private:
    const Node* m_pCurrentNode;

  public:
    iterator() : m_pCurrentNode(m_spRoot) {}
    iterator(const Node* pnode) : m_pCurrentNode(pnode) {}
    iterator& operator=(Node* pnode)
    {
      m_pCurrentNode = pNode;
      return *this;
    }

    iterator& operator++()
    {
      if (m_pCurrentNode)
      {
        m_pCurrentNode = m_pCurrentNode->pNext;
      }

      return *this;
    }

    iterator& operator++(int)
    {
      iterator* tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator!=(const iterator& itr)
    {
      return (m_pCurrentNode != itr.m_pCurrentNode);
    }

    T operator*()
    {
      return m_pCurrentNode->data;
    }

    T* operator->()
    {
      return &m_pCurrentNode->data;
    }
  };

  iterator begin()
  {
    return iterator(m_spRoot);
  }

  iterator end()
  {
    return iterator(nullptr);
  }

  void push_back(T data)
  {
    Node* pTemp = GetNode(data);
    if (!GetRootNode())
    {
      GetRootNode() = pTemp;
    }
    else
    {
      Node* pNode = GetRootNode();
      while (pNode->pNext)
      {
        pNode = pNode->pNext;
      }

      pNode->pNext = pTemp;
    }
  }

  void traverse()
  {
    Node* pNode = GetRootNode();
    while (pNode->pNext)
    {
      std::cout << pNode->data << " " << std::endl;
      pNode = pNode->pNext;
    }
  }

  ~mylist()
  {
    Node* pNode = GetRootNode();
    Node* tmp = pNode;
    while (pNode->pNext)
    {
      tmp = pNode;
      pNode = pNode->pNext;
      delete tmp;
    }
  }
};

int main()
{
  mylist<std::string> list;
  list.push_back("something string"s);
  list.push_back("something string version 2"s);

  for (auto&& i : list)
  {
    std::cout << i << std::endl;
  }

  return 0;
}