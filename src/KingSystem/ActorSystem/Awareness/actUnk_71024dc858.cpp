#include "KingSystem/ActorSystem/Awareness/actAITerror.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace ksys::act {

// NON_MATCHING: store merging (the original merges _1c/_20 and _28-_34 into 64-bit stores)
Unk_71024dc858::Unk_71024dc858() = default;

// NON_MATCHING: store merging (as the default ctor)
Unk_71024dc858::Unk_71024dc858(Actor* actor) {
    mLink.acquire(actor, false);
}

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

void Unk_71024dc858::sub_7100D77518(int idx, f32 value) {
    _18[idx] = value;
}

Unk_71024dca28::~Unk_71024dca28() {
    for (auto* terror = _8; terror;) {
        auto* next = terror->_a8;
        terror->sub_7100D78970();
        terror = next;
    }
    _8 = nullptr;
}

void Unk_71024dca28::sub_7100D783E4(AITerror* terror) {
    if (_8) {
        auto* last = _8;
        while (last->_a8)
            last = last->_a8;
        terror->sub_7100D78814(this, last);
        return;
    }
    if (terror->sub_7100D78814(this, nullptr))
        _8 = terror;
}

void Unk_71024dca28::sub_7100D78444(AITerror* terror) {
    if (_8 && _8 == terror)
        _8 = terror->_a8;
    terror->sub_7100D78970();
}

Unk_7100d78e50* sub_7100D78E30(const sead::ObjArray<Unk_7100d78e50>* array, s32 idx) {
    return array->at(idx);
}

}  // namespace ksys::act
