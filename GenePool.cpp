#include "GenePool.h"
#include "Query.h"
#include <string>
#include <istream>
#include <sstream>
#include <iostream>

GenePool::GenePool(std::istream& stream)
{
    std::string x;
    while (getline(stream, x))
    {
        if (x == "" || x.find("#") == 0)
        {
            continue;
        }
        Person* temp = new Person();
        std::istringstream newstream(x);
        getline(newstream,x,'\t');
        temp->setName(x);
        getline(newstream,x,'\t');
        if (x == "male")
            temp->setGender(Gender::MALE);
        else if (x == "female")
            temp->setGender(Gender::FEMALE);
        else   
            temp->setGender(Gender::ANY);
        getline(newstream,x,'\t');
        if (x == "???")
            temp->setMother(nullptr);
        else
        {
            temp->setMother(this->find(x));
            this->find(x)->addChild(temp);
        }
        getline(newstream,x,'\t');
        if (x == "???")
            temp->setFather(nullptr);
        else  
        {
            temp->setFather(this->find(x));
            this->find(x)->addChild(temp);
        }
        Pool[temp->name()] = temp;
        
        
    }
    



}

Person* GenePool::find(const std::string& name) const
{
    auto temp = Pool.find(name);
    if (temp != Pool.end())
        return temp->second;
    else
        return nullptr;
}

GenePool::~GenePool()
{
    for (auto itr = Pool.begin(); itr != Pool.end(); ++itr)
    {
        delete itr->second;
    }
}