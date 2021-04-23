#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

#include "myDlList.hpp"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

template <typename HashedObj>
class myHashTable
{
  public:
    explicit myHashTable(int size = 101)
    {
      currentSize = size;
      theLists.resize(size);
    }

    bool contains(const HashedObj & x)
    {
      const int index = myhash(x);
      auto & whichList = theLists[index];
      return whichList.find(getiteratorbegin(index), getiteratorend(index), x) != getiteratorend(index);
    }

    void makeEmpty()
    {
      for(auto & thisList : theLists)
      {
        thisList.clear();
      }
    }

    bool insert(const HashedObj & x)
    {
      const int index = myhash(x);
      auto & whichList = theLists[index];
      // auto itr = whichList.find(getiteratorbegin(index), getiteratorend(index), x);
      if(whichList.find(getiteratorbegin(index), getiteratorend(index), x) != getiteratorend(index)) // x already exists in the hash table
      {
        return false;
      }
      whichList.push_back(x);
      if(++currentSize > theLists.size())
      {
        rehash();
      }
      return true;
    }

    bool insert(HashedObj && x)
    {
      const int index = myhash(x);
      auto & whichList = theLists[index];
      auto itr = whichList.find(getiteratorbegin(index), getiteratorend(index), x);
      if(itr != getiteratorend(index)) //x does not exist in whichList already
      {
        return false;
      }
      whichList.push_back(std::move(x));
      if(++currentSize > theLists.size())
      {
        rehash();
      }
      return true;
    }

    bool remove(const HashedObj & x)
    {
      const int index = myhash(x);
      auto & whichList = theLists[index];
      auto itr = whichList.find(getiteratorbegin(index), getiteratorend(index), x);
      if(itr == getiteratorend(index))
      {
        return false;
      }
      else
      {
        whichList.erase(itr);
        --currentSize;
        return true;
      }
    }

    int nextPrime(int n)
    {
      if(n <= 1)
      {
        return 2;
      }
      while(true)
      {
        n++;
        if(isPrime(n))
        {
          return n;
        }
      }
    }

    typename myDlList<HashedObj>::iterator getiteratorbegin(int index)
    {
      return theLists[index].begin();
    }

    typename myDlList<HashedObj>::iterator getiteratorend(int index)
    {
      return theLists[index].end();
    }

    int hashsize()
    {
      return theLists.size();
    }

  private:
    std::vector<myDlList<HashedObj>> theLists;
    int currentSize;

    void rehash()
    {
      std::vector<myDlList<HashedObj>> oldLists = theLists;
      theLists.resize(nextPrime(2 * theLists.size()));
      for(auto & thisList : theLists)
      {
        thisList.clear();
      }
      currentSize = 0;
      for(auto & thisList : oldLists)
      {
        for(auto & x : thisList)
        {
          insert(std::move(x));
        }
      }
    }

    bool isPrime(int n)
    {
      if(n <= 1)
      {
        return false;
      }
      for(int i = 2; i < n; ++i)
      {
        if(n % i == 0)
        {
          return false;
        }
      }
      return true;
    }

    size_t myhash(const HashedObj & x) const
    {
      static hash<HashedObj> hf;
      return hf(x) % theLists.size();
    }
};

template <typename hashitem>
class hash
{
  public:
    size_t operator()(const hashitem & key) const
    {
      size_t hashVal = 0;
      for(char ch : key)
      {
        hashVal = 37 * hashVal + ch;
      }
      return hashVal;
    }
};

#endif
