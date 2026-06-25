#include "HangarCollection.h"
#include "MyException.h"
std::vector<std::unique_ptr<Hangar>> HangarCollection::hangars;

const std::unique_ptr<Hangar>& HangarCollection::getHangarById(std::string _id)
{
    for (const auto& i : hangars) {
        if (i->getId() == _id) {
            return i;
        }
    }
    throw MyException("HangarNotFound");
}

const std::vector<std::unique_ptr<Hangar>>& HangarCollection::getAllHangars()
{
    return hangars;
}

void HangarCollection::addHangar(std::unique_ptr<Hangar> hangar)
{
    for (const auto& i : hangars) {
        if (i->getId() == hangar->getId()) {
            throw MyException("HangarAlreadyExists");
        }
    }
    hangars.push_back(std::move(hangar));
}

void HangarCollection::printAllHangars(std::ostream& os)
{
    for (const auto& i : hangars) {
        os << *i;
    }
}

bool HangarCollection::hangarId(std::string id)
{
    for (const auto& i : hangars) {
        if (i->getId() == id) {
            return true;
        }
    }
    return false;
}
