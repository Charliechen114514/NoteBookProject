#pragma once
#include <string>
#include <sstream>


struct Person
{
    std::string work_space, work_number, work_professions;
    std::string live_space, id_card, name, gender;

    std::string introduce_self() const{
        std::ostringstream oss;
        oss << name << "'s id is " << id_card << ", who lives in " << live_space;
        oss << ". he works as a " << work_professions << 
                "with work number " << work_number << " at " << work_space;
        return oss.str();
    }
};

struct PersonAddressBuilder;
struct PersonLivingBuilder;

struct PersonBuilderBase
{
    operator Person(){
        return std::move(who);
    }
    PersonAddressBuilder work();
    PersonLivingBuilder live();
protected:
    PersonBuilderBase(Person& p):who(p){}
    Person& who;
};

struct PersonLivingBuilder : public PersonBuilderBase
{
    explicit PersonLivingBuilder(Person& p): PersonBuilderBase(p){}
    PersonLivingBuilder& live_in(const std::string living_at){
        this->who.live_space = living_at;
        return *this;
    }

    PersonLivingBuilder& with_id(const std::string id_num){
        this->who.id_card = id_num;
        return *this;
    }

    PersonLivingBuilder& with_name(const std::string name){
        this->who.name = name;
        return *this;
    }
};

struct PersonAddressBuilder : PersonBuilderBase
{
    explicit PersonAddressBuilder(Person& p):PersonBuilderBase(p){}
    PersonAddressBuilder& work_as(const std::string work_professions)
    {
        
        this->who.work_professions = work_professions;
        return *this;
    }

    PersonAddressBuilder& work_in(const std::string work_at)
    {
        this->who.work_space = work_at;
        return *this;
    }

    PersonAddressBuilder& with_work_number(const std::string work_number)
    {
        this->who.work_number = work_number;
        return *this;
    }
};



class PersonBuilder : public PersonBuilderBase
{
    Person creating_person;
public:
    PersonBuilder():PersonBuilderBase(creating_person){}
};

struct PersonCreator
{
    static PersonBuilder create(){
        return PersonBuilder();
    }
};