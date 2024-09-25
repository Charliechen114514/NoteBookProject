#include "PersonCreator.h"

PersonAddressBuilder PersonBuilderBase::work()
{
    return PersonAddressBuilder(who);
}

PersonLivingBuilder PersonBuilderBase::live()
{
    return PersonLivingBuilder(who);
}

