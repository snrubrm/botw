#include <basis/seadNew.h>
#include "Game/Actor/actRideable.h"

namespace uking::act {

RideableBase* RideableBase::make(sead::Heap* heap) {
    return new (heap, std::nothrow) RideableBase;
}

RideableBase::RideableBase() = default;

RideableBase::~RideableBase() = default;

void RideableBase::sub_7100E63900() {
    if (_8 & 0x20)
        _8 |= 0x80;
}

void RideableBase::sub_7100E6314C(Rank rank, f32 value, u32 id) {
    f32* ranked;
    u32* ids;
    switch (rank) {
    case 1:
        ranked = &_138;
        ids = &_140;
        break;
    case 2:
        ranked = &_13c;
        ids = &_144;
        break;
    default:
        return;
    }
    if (*ranked < value) {
        *ranked = value;
        *ids = id;
    }
}

}  // namespace uking::act
