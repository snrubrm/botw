#include "Game/Actor/actMapConst.h"
#include <basis/seadNew.h>

namespace uking::act {

MapConstPassive::MapConstPassive(const CreateArg& arg) : MapConstPassiveBase(arg) {}

MapConstPassive::~MapConstPassive() = default;

ksys::act::BaseProc* MapConstPassive::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) MapConstPassive(arg);
}

void MapConstPassive::m63() {
    MapConstPassiveBase::m63();
}

void MapConstPassive::initMaybe() {
    MapConstPassiveBase::initMaybe();
}

}  // namespace uking::act
