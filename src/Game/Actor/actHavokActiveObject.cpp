#include "Game/Actor/actHavokActiveObject.h"
#include <basis/seadNew.h>

namespace uking::act {

HavokActiveObject::HavokActiveObject(const CreateArg& arg) : Actor(arg) {
    _1c0 = 3;
}

ksys::act::BaseProc* HavokActiveObject::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) HavokActiveObject(arg);
}

}  // namespace uking::act
