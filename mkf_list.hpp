#ifndef MKF_LIST_HPP_INCLUDED
#define MKF_LIST_HPP_INCLUDED


#include<cstddef>


namespace mkf{


template<typename  T>
class
List
{
  struct ListElement{
    T  data;

    ListElement*  next;

    ListElement(const T&   dat): data(         (dat)), next(nullptr){}
    ListElement(      T&&  dat): data(std::move(dat)), next(nullptr){}
  };


  ListElement*  first;
  ListElement*   last;

public:
   List(           ): first(nullptr){}
   List(List&&  rhs): first(nullptr){}

  virtual ~List(){clear();}


  List&  operator=(List&&  rhs)
  {
    clear();

    first = rhs.first;
            rhs.first = nullptr;

    last = rhs.last;

    return *this;
  }


  int  size() const
  {
    int  n = 0;

    auto  now = first;

      while(now)
      {
        now = now->next;

        ++n;
      }


    return n;
  }


  bool  empty() const{return !first;}

  void  clear()
  {
    auto  now = first;

      while(now)
      {
        auto  next = now->next;

        delete now       ;
               now = next;
      }


    first = nullptr;
     last = nullptr;
  }


  T&  push(const T&  t)
  {
    auto  e = new ListElement(t);

      if(!first)
      {
        first = e;
      }

    else
      {
        last->next = e;
      }


    last = e;

    return e->data;
  }


  T&  push(T&&  t)
  {
    auto  e = new ListElement(std::move(t));

      if(!first)
      {
        first = e;
      }

    else
      {
        last->next = e;
      }


    last = e;

    return e->data;
  }


  T&  front() const{return first->data;}
  T&   back() const{return  last->data;}

  void  merge(List&  rhs)
  {
      if(rhs.first)
      {
          if(first)
          {
            last->next = rhs.first          ;
                         rhs.first = nullptr;

            last = last->next;
          }

        else
          {
                   first = rhs.first;
            last = first            ;
          }
      }
  }


  class Iterator{
    ListElement*  ptr;

  public:
    Iterator(ListElement*  ptr_=nullptr): ptr(ptr_){}

    operator bool() const{return ptr;}

    Iterator&  operator++(){ptr = ptr->next;}

    T&  operator*()  const{return  ptr->data;}
    T*  operator->() const{return &ptr->data;}

    bool  operator!=(const Iterator&  rhs) const{return(ptr != rhs.ptr);}

  };


  Iterator  begin() const
  {
    return Iterator(first);
  }


  Iterator  end() const
  {
    return Iterator(nullptr);
  }

};


}


#endif




