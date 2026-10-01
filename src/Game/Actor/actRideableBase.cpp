#include <basis/seadNew.h>
#include "Game/Actor/actRideable.h"

namespace uking::act {

RideableBase* RideableBase::make(sead::Heap* heap) {
    return new (heap, std::nothrow) RideableBase;
}

RideableBase::RideableBase() = default;

RideableBase::~RideableBase() = default;

}  // namespace uking::act
