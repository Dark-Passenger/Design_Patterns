// Strategy_Pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <memory>

class SortBehaviour
{
public:
  virtual void sort() const = 0;
};

class MergeSort : public SortBehaviour
{
public:
  virtual void sort() const override
  {
    std::cout << "Merge sort" << std::endl;
  }
};

class QuickSort : public SortBehaviour
{
public:
  virtual void sort() const override
  {
    std::cout << "Quick sort" << std::endl;
  }
};

class HeapSort : public SortBehaviour
{
public:
  virtual void sort() const override
  {
    std::cout << "Heap sort" << std::endl;
  }
};

class SearchBehaviour
{
public:
  virtual void search() const = 0;
};

class SeqSearch : public SearchBehaviour
{
public:
  virtual void search() const override
  {
    std::cout << "Sequential search" << std::endl;
  }
};

class BinarySearch : public SearchBehaviour
{
public:
  virtual void search() const override
  {
    std::cout << "Binary tree search" << std::endl;
  }
};

class HashSearch : public SearchBehaviour
{
public:
  virtual void search() const override
  {
    std::cout << "Hash table search" << std::endl;
  }
};

template<typename SortPolicy, typename SearchPolicy>
class Static_Collection
{
private:
  SortPolicy m_sort;
  SearchPolicy m_search;

public:
  void sort() const
  {
    m_sort.sort();
  }

  void search() const
  {
    m_search.search();
  }
};

class Collection
{
private:
  std::unique_ptr<SortBehaviour> m_sort;
  std::unique_ptr<SearchBehaviour> m_search;

public:
  void set_sort(SortBehaviour* s)
  {
    m_sort.reset(s);
  }

  void set_search(SearchBehaviour* s)
  {
    m_search.reset(s);
  }

  void sort() const
  {
    m_sort->sort();
  }

  void search() const
  {
    m_search->search();
  }
};

int main()
{
  Collection coll;

  //select a search strategy
  coll.set_sort(new HeapSort());

  //select a sort strategy
  coll.set_search(new BinarySearch());

  coll.search();
  coll.sort();

  //strategy can also be selected at compile time, this is called 
  //policy based design pattern.
  Static_Collection<QuickSort, HashSearch> coll_2;

  coll_2.search();
  coll_2.sort();

  return 0;
}