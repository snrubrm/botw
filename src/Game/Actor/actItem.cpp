#include "Game/Actor/actItem.h"
#include <basis/seadNew.h>

namespace uking::act {

Item::Item(const CreateArg& arg) : DynamicActor(arg) {}

ksys::act::BaseProc* Item::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Item(arg);
}

}  // namespace uking::act
