#include <iostream>


class Person 
{ 
public: 
  Person() 
    : name_("?????"),
      age_(-1)
  { 
    std::cout<< "constructor\n" ;
  } 

  Person(std::string name, int age)
  { 
    name_ = name; 
    age_ = age; 
  } 

  void* operator new(size_t size) 
  { 
    std::cout<< "I'm created, size=" << size << std::endl;
    void * p = malloc(size);
    return p;
  } 
  
  void operator delete(void * p) 
  { 
    std::cout<< "I'm deleted!" << std::endl;
    free(p); 
  } 

private:
  std::string name_; 
  int age_; 
}; 

