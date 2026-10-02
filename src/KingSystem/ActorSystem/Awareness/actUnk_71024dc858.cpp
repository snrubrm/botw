#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace ksys::act {

// NON_MATCHING: store merging (the original merges _1c/_20 and _28-_34 into 64-bit stores)
Unk_71024dc858::Unk_71024dc858() = default;

Unk_71024dc858::~Unk_71024dc858() {
    mLink.reset();
}

bool Unk_71024dc858::m5(int bit) const {
    return _38.isOnBit(bit);
}

sead::BitFlag16* Unk_71024dc858::m6() {
    return &_38;
}

void Unk_71024dc858::m10(int bit, bool on) {
    _38.changeBit(bit, on);
}

bool Unk_71024dc858::m7(sead::Vector3f* pos) {
    ActorConstDataAccess accessor;
    if (!acquireActor(&mLink, &accessor))
        return false;
    pos->set(accessor.getPreviousPos());
    return true;
}

bool Unk_71024dc858::m8(sead::Vector3f* vel) {
    ActorConstDataAccess accessor;
    if (!acquireActor(&mLink, &accessor))
        return false;
    vel->set(accessor.getVelocity());
    return true;
}

void Unk_71024dc858::m9(int idx, f32 value) {
    if (idx == 1 || idx == 2) {
        if (_18[idx] < value)
            _18[idx] = value;
    } else {
        _18[idx] = value;
    }
}


Unk_71024dc858* sub_7100D78E30(const sead::ObjArray<Unk_71024dc858>* array, s32 idx) {
    return array->at(idx);
}

}  // namespace ksys::act
