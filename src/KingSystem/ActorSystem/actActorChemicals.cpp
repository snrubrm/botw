#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace ksys::act {

// The body keeps the vtable store of the original, as in upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; }
// (commit 96101229).
Unk_71024e6560::~Unk_71024e6560() {
    ;
}

const sead::Vector3f& Unk_71024e6428::m5() const {
    return _2a4;
}

const sead::Vector3f& Unk_71024e6428::m6() const {
    return _2b0;
}

const sead::SafeString& Unk_71024e6428::getName() const {
    return mActor ? mActor->getName() : sead::SafeString::cEmptyString;
}

bool Unk_71024e6428::m15(u32 a1) const {
    return _30 & 0x100;
}

bool Unk_71024e6428::m16() const {
    return _30 & 0x2;
}

bool Unk_71024e6428::m17() const {
    return mActor && mActor->getActorFlags2().isOn(Actor::ActorFlag2::_40);
}

// NON_MATCHING: the original guards the loop with a signed `count >= 1` test (`cmp w20, #1; b.lt`), ours with `cbz`
bool Unk_71024e6428::m18() const {
    for (auto& entry : _278) {
        if (auto* body = entry.body) {
            if (!body->isAddedToWorld() && !body->isAddingBodyToWorld())
                return false;
        }
    }
    return true;
}

bool Unk_71024e6428::m19() const {
    return mActor && mActor->isSleep();
}

bool Unk_71024e6428::m21() const {
    return false;
}

f32 Unk_71024e6428::m23() const {
    return _28c;
}

f32 Unk_71024e6428::m24() const {
    return _290;
}

f32 Unk_71024e6428::m26() const {
    return _294;
}

void Unk_71024e6428::m27(f32 value) {
    _28c = value;
}

bool Unk_71024e6428::m22(u32 a1) const {
    return !(_30 & 0x30);
}

f32 Unk_71024e6428::m25() const {
    if (mActor) {
        if (auto* body = mActor->getMainBody())
            return body->getMass();
    }
    return 1.0f;
}

// NON_MATCHING: the original loads `mActor` before the virtual m5() call (the null test comes after it) and reloads it
// inside the branch
bool Unk_71024e6428::m28() {
    return sub_7100E41470(m5(), mActor ? mActor->getPhysics()->get188(0) : nullptr);
}

f32 Unk_71024e6428::m30(const void* a1) {
    f32 sum = 0;
    for (auto& entry : _278)
        sum += sub_7100E40B7C(entry.body, a1, entry._24);
    return sum;
}

bool Unk_71024e6428::m31() {
    return !_18->isRigidAttribute16Set(_288);
}

bool Unk_71024e6428::m33() {
    if (mChemical._c0 == 2 && mActor) {
        if (mActor->getName() == "FireWoodFromBundle") {
            mChemical.sub_7100D90B78();
            return true;
        }
    }
    return false;
}

// NON_MATCHING: the original loads `_288` before the slot of the virtual call (scheduling only)
bool Unk_71024e6428::m36() {
    if ((_30 & 0x10000) || !(_3c & 0x1))
        return true;
    if (!_18->isRigidAttribute6Or14Set(_288) && !(_3c & 0x100000))
        return true;
    return _30 & 0x8000;
}

ActorChemicals::ActorChemicals() = default;

Unk_71024e6428* ActorChemicals::sub_7100E3718C(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    if (_58.size() + _80 < 1)
        return nullptr;
    if (idx < _58.size())
        return &_58[idx];
    return &_70[idx - _58.size()];
}

Unk_71024e6428* ActorChemicals::sub_7100E37FA8(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    if (_58.size() + _80 < 1)
        return nullptr;
    if (idx < _58.size())
        return &_58[idx];
    return &_70[idx - _58.size()];
}

// NON_MATCHING: the original's null path skips the conversion (branch target only)
Chemical* ActorChemicals::sub_7100E37788(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    auto* element = getElement_(idx);
    if (!element)
        return nullptr;
    return &element->mChemical;
}

// NON_MATCHING: the original's null path skips the conversion (branch target only)
Chemical* ActorChemicals::getStuff(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    auto* element = getElement_(idx);
    if (!element)
        return nullptr;
    return &element->mChemical;
}

Chemical* ActorChemicals::sub_7100E380FC(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    if (idx < 0 || idx >= _70.size())
        return nullptr;
    return &_70[idx].mChemical;
}

Chemical* ActorChemicals::sub_7100E3816C(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    if (idx < 0 || idx >= _70.size())
        return nullptr;
    return &_70[idx].mChemical;
}

// NON_MATCHING: same as getStuff (the null path of the inlined element lookup branches to a different unlock)
Chemical* ActorChemicals::sub_7100E381DC(const sead::SafeString& name) {
    const auto lock = sead::makeScopedLock(mCS);
    const s32 idx = sub_7100E382C4(name);
    if (idx == -1)
        return nullptr;
    return getStuff(idx);
}

// NON_MATCHING: the original keeps the null check of the element and loads the body count without sign extension
bool ActorChemicals::sub_7100E384C4(const phys::RigidBody* body, int idx) {
    if (idx < 0 || idx >= _58.size() + _80)
        return false;
    Unk_71024e6428* element;
    if (idx < _58.size())
        element = &_58[idx];
    else
        element = &_70[idx - _58.size()];
    if (!element)
        return false;
    for (s32 i = 0; i < element->_278.size(); ++i) {
        if (element->_278[i].body == body)
            return true;
    }
    return false;
}

// NON_MATCHING: same as getStuff (the original's null path of the inlined element lookup unlocks once and shares the
// outer unlock; the loop counters also use other registers)
void ActorChemicals::sub_7100E39614(bool on) {
    const auto lock = sead::makeScopedLock(mCS);
    for (s32 i = 0; i < _58.size() + _80; ++i) {
        if (auto* chemical = getStuff(i))
            chemical->sub_7100D91098(on);
    }
}

}  // namespace ksys::act
