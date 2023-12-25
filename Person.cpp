#include "Person.h"
#include "Enums.h"

Person::Person()
{
    myName = "";
    myMother = nullptr;
    myFather = nullptr;
    myGender = Gender::ANY;
}

const std::string& Person::name() const
{
    return myName;
}

Gender Person::gender() const
{
    return myGender;
}

Person* Person::mother()
{
    return myMother;
}

Person* Person::father()
{
    return myFather;
}

void Person::setFather(Person* x)
{
    myFather = x;
}

void Person::setMother(Person* x)
{
    myMother = x;
}

void Person::setGender(Gender x)
{
    myGender = x;
}

void Person::setName(std::string x)
{
    myName = x;
}

void Person::addChild(Person* x)
{
    myChildren.insert(x);
}

std::set<Person*> Person::ancestors(PMod pmod)
{
    
    std::set<Person*> temp;
    if (myFather != nullptr && (pmod == PMod::ANY || pmod == PMod::PATERNAL))
        temp.insert(myFather);
    if (myMother != nullptr && (pmod == PMod::ANY || pmod == PMod::MATERNAL))
        temp.insert(myMother);
    std::set<Person*> temp2;
    std::set<Person*> temp3;
    if (pmod == PMod::PATERNAL || pmod == PMod::ANY)
    {
        if ( myFather != nullptr)
        {
            temp2 = myFather->ancestors(PMod::ANY);
            for (auto itr = temp2.begin(); itr != temp2.end(); ++itr)
            {
               temp.insert(*itr);
            }
        }
    }
    if (myMother != nullptr && (pmod == PMod::MATERNAL || pmod == PMod::ANY))
    {
        temp3 = myMother->ancestors(PMod::ANY);
         for (auto itr = temp3.begin(); itr != temp3.end(); ++itr)
        {
        temp.insert(*itr);
        }
    }
    
   
    return temp;

}
std::set<Person*> Person::aunts(PMod pmod, SMod smod)
{
    std::set<Person*> temp;
    std::set<Person*> temp2;
    std::set<Person*> temp3;
    if ((pmod == PMod::ANY || pmod == PMod::PATERNAL) && myFather != nullptr)
    {
        temp2 = myFather->sisters(pmod,smod);
    }
    if ((pmod == PMod::ANY || pmod == PMod::MATERNAL) && myMother != nullptr)
    {
        temp3 = myMother->sisters(pmod,smod);
    }
    if (pmod == PMod::ANY)
    {
        for(Person* p:temp2)
        {
            temp.insert(p);
        }
        for(Person* p:temp3)
        {
            temp.insert(p);
        }
    }
    if (pmod == PMod::PATERNAL)
    {
        for (Person* p:temp2)
        {
            temp.insert(p);
        }
    }
    if (pmod == PMod::MATERNAL)
    {
        for (Person* p:temp3)
        {
            temp.insert(p);
        }
        if (smod == SMod::HALF && myMother != nullptr)
        {
            std::set<Person*> temp4 = myMother->sisters(PMod::PATERNAL,smod);
            for (Person* p:temp4)
            {
                if (temp.count(p))
                {
                    continue;
                }
                else
                    temp.insert(p);
            }
        }
    }
    return temp;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod)
{
    std::set<Person*> temp;
    std::set<Person*> temp2 = siblings(pmod, smod);
    for (Person* p:temp2)
    {
        if (p->gender() == Gender::MALE)
            temp.insert(p);
    }
    return temp;
}
std::set<Person*> Person::children()
{
    return myChildren;
}
std::set<Person*> Person::cousins(PMod pmod, SMod smod)
{
    std::set<Person*> temp;
    std::set<Person*> temp2;
    std::set<Person*> temp3;
    if (myFather != nullptr && (pmod == PMod::ANY || pmod == PMod::PATERNAL)) 
        temp2 = myFather->siblings(pmod,smod);
    if (myMother != nullptr && (pmod == PMod::ANY || pmod == PMod::MATERNAL)) 
        temp3 = myMother->siblings(pmod,smod);
    for (Person* p:temp2)
    {
        std::set<Person*> temp4 = p->children();
        for (Person* x:temp4)
        {
            if (temp.count(x))
            {
                continue;
            }
            else
            {
                temp.insert(x);
            }
        }
    }
    for (Person* p:temp3)
    {
        std::set<Person*> temp4 = p->children();
        for (Person* x:temp4)
        {
            if (temp.count(x))
            {
                continue;
            }
            else
            {
                temp.insert(x);
            }
        }
    }
    return temp;
}
std::set<Person*> Person::daughters()
{
    std::set<Person*> temp;
    if (!myChildren.empty())
        for (Person* p:myChildren)
        {
            if (p->gender() == Gender::FEMALE)
                temp.insert(p);
        }
    return temp;

        
}
std::set<Person*> Person::descendants()
{
    std::set<Person*> temp;
    for (Person* p:myChildren)
    {
        temp.insert(p);
        std::set<Person*> temp2 = p->descendants();
        for (Person* x:temp2)
        {
            temp.insert(x);
        }
    }
    return temp;
}
std::set<Person*> Person::grandchildren()
{
    std::set<Person*> temp;
    for (Person* p:myChildren)
    {
        for (Person* x:p->children())
        {
            temp.insert(x);
        }
    }
    return temp;
}
std::set<Person*> Person::granddaughters()
{
    std::set<Person*> temp2 = grandchildren();
    std::set<Person*> temp;
    for (Person* p:temp2)
    {
        if (p->gender() == Gender::FEMALE)
            temp.insert(p);
    }

    return temp;
}
std::set<Person*> Person::grandfathers(PMod pmod)
{
    std::set<Person*> temp;
    if ((pmod == PMod::ANY || pmod == PMod::PATERNAL) && myFather != nullptr && myFather->father() != nullptr) 
    {
        temp.insert(myFather->father());
    }
    if ((pmod == PMod::ANY || pmod == PMod::MATERNAL) && myMother != nullptr && myMother->father() != nullptr) 
    {
        temp.insert(myMother->father());
    }
    return temp;
}
std::set<Person*> Person::grandmothers(PMod pmod)
{
    std::set<Person*> temp;
    if ((pmod == PMod::ANY || pmod == PMod::PATERNAL) && myFather != nullptr && myFather->mother() != nullptr) 
    {
        temp.insert(myFather->mother());
    }
    if ((pmod == PMod::ANY || pmod == PMod::MATERNAL) && myMother != nullptr && myMother->mother() != nullptr) 
    {
        temp.insert(myMother->mother());
    }
    return temp;
}
std::set<Person*> Person::grandparents(PMod pmod)
{
    std::set<Person*> temp;
    if (myFather != nullptr)
    {
        std::set<Person*> temp2 = myFather->parents();
        if (pmod == PMod::ANY || pmod == PMod::PATERNAL)
        {
            for (Person* p:temp2)
            {
                temp.insert(p);
            }
        }
    }
    if (myMother != nullptr)
    {
        std::set<Person*> temp3 = myMother->parents();
    
        if (pmod == PMod::ANY || pmod == PMod::MATERNAL)
        {
            for (Person* p:temp3)
            {
                temp.insert(p);
            }
        }

    }
    return temp;
}
std::set<Person*> Person::grandsons()
{
    std::set<Person*> temp2 = grandchildren();
    std::set<Person*> temp;
    for (Person* p:temp2)
    {
        if (p->gender() == Gender::MALE)
            temp.insert(p);
    }
    return temp;
}
std::set<Person*> Person::nephews(PMod pmod, SMod smod)
{
    std::set<Person*> temp;
    std::set<Person*> temp2 = siblings(pmod,smod);
    std::set<Person*> temp3;
    for (Person* p:temp2)
    {
        temp3 = p->sons();
        for (Person* x:temp3)
        {
            if (temp.count(x))
            {
                continue;
            }
            else
            {
                temp.insert(x);
            }
        }
    }
    return temp;
}
std::set<Person*> Person::nieces(PMod pmod, SMod smod)
{
    std::set<Person*> temp;
    std::set<Person*> temp2 = siblings(pmod,smod);
    std::set<Person*> temp3;
    for (Person* p:temp2)
    {
        temp3 = p->daughters();
        for (Person* x:temp3)
        {
            if (temp.count(x))
            {
                continue;
            }
            else
            {
                temp.insert(x);
            }
        }
    }
    return temp;
}
std::set<Person*> Person::parents(PMod pmod)
{
    std::set<Person*> temp;
    if ((pmod == PMod::ANY || pmod == PMod::PATERNAL) && myFather != nullptr)
        temp.insert(myFather);
    if ((pmod == PMod::ANY || pmod == PMod::MATERNAL) && myMother != nullptr)
        temp.insert(myMother);
    return temp;
}
std::set<Person*> Person::siblings(PMod pmod, SMod smod)
{
    std::set<Person*> temp;
    std::set<Person*> temp2;
    std::set<Person*> temp3;
    if ((pmod == PMod::PATERNAL || pmod == PMod::ANY) && myFather != nullptr)
    {
        temp2 = myFather->children();
    }
    if ((pmod == PMod::MATERNAL || pmod == PMod::ANY) && myMother != nullptr)
    {
        temp3 = myMother->children();
    }
    if (smod == SMod::ANY)
    {
        for (Person* p:temp2)
        {
            if (p != this)
                temp.insert(p);
        }
        for (Person* p:temp3)
        {
            if (temp.count(p))
            {
                continue;
            }
            else
            {
                if (p != this)
                    temp.insert(p);
            }
        }
    }
    if (smod == SMod::FULL)
    {
        for (Person* p:temp2)
        {
            if (p->father() != nullptr && p->mother() != nullptr)
                if ((p->father() == myFather && p->mother() == myMother) && p != this)
                {
                    temp.insert(p);
                }
        }
        for (Person* p:temp3)
        {
            if (p->father() != nullptr && p->mother() != nullptr)
                if ((p->father() == myFather && p->mother() == myMother) && p != this)
                {
                    if (temp.count(p))
                    {
                        continue;
                    }
                    else
                        temp.insert(p);
                }
        }
    }
    if (smod == SMod::HALF)
    {

        for (Person* p:temp2)
        {
            if ((p->father() != myFather && p->mother() == myMother) || (p->father() == myFather && p->mother() != myMother))
            {
                temp.insert(p);
            }
        }
        for (Person* p:temp3)
        {
            if ((p->father() != myFather && p->mother() == myMother) || (p->father() == myFather && p->mother() != myMother))
            {
                if (temp.count(p))
                {
                    continue;
                }
                else
                    temp.insert(p);
            }
        }
        
    }

    return temp;
}
std::set<Person*> Person::sisters(PMod pmod, SMod smod)
{
    std::set<Person*> temp;
    std::set<Person*> temp2 = siblings(pmod,smod);
    for (Person* p:temp2)
    {
        if (p->gender() == Gender::FEMALE)
        {
            temp.insert(p);
        }
    }
    return temp;
}
std::set<Person*> Person::sons()
{
    std::set<Person*> temp;
    if (!myChildren.empty())
        for (Person* p:myChildren)
        {
            if (p->gender() == Gender::MALE)
                temp.insert(p);
        }
    return temp;
}
std::set<Person*> Person::uncles(PMod pmod, SMod smod)
{
    std::set<Person*> temp;
    std::set<Person*> temp2;
    std::set<Person*> temp3;
    if ((pmod == PMod::ANY || pmod == PMod::PATERNAL) && myFather != nullptr)
    {
        temp2 = myFather->brothers(pmod,smod);
    }
    if ((pmod == PMod::ANY || pmod == PMod::MATERNAL) && myMother != nullptr)
    {
        temp3 = myMother->brothers(pmod,smod);
    }
    if (pmod == PMod::ANY)
    {
        for(Person* p:temp2)
        {
            temp.insert(p);
        }
        for(Person* p:temp3)
        {
            temp.insert(p);
        }
    }
    if (pmod == PMod::PATERNAL)
    {
        for (Person* p:temp2)
        {
            temp.insert(p);
        }
    }
    if (pmod == PMod::MATERNAL)
    {
        for (Person* p:temp3)
        {
            temp.insert(p);
        }
        if (smod == SMod::HALF && myMother != nullptr)
        {
            std::set<Person*> temp4 = myMother->brothers(PMod::PATERNAL,smod);
            for (Person* p:temp4)
            {
                if (temp.count(p))
                {
                    continue;
                }
                else
                    temp.insert(p);
            }
        }
    }
    return temp;
    
}