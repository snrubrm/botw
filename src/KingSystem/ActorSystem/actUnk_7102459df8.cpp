#include "KingSystem/ActorSystem/actUnk_7102459df8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace ksys::act {

Unk_7102459df8::~Unk_7102459df8() = default;

void Unk_7102459df8::m5() {
    if (_10)
        _10->sub_71007A5318();
    if (_18)
        _18->sub_710079FE9C();
    if (_20)
        _20->sub_710079F600();
}

void Unk_7102459df8::m6() {
    if (_18) {
        delete _18;
        _18 = nullptr;
    }
    if (_10) {
        delete _10;
        _10 = nullptr;
    }
    if (_20) {
        delete _20;
        _20 = nullptr;
    }
    _38.freeBuffer();
    _28.freeBuffer();
}

bool Unk_7102459df8::m9() {
    if (_20)
        _20->sub_710079F600();
    return true;
}

void Unk_7102459df8::m10() {
    if (_20)
        _20->sub_710079F600();
}

bool Unk_7102459df8::sub_710079CE78() const {
    if (!_10)
        return false;
    return _10->mNum > 0;
}

s32 Unk_7102459df8::sub_710079CE98() const {
    if (!_10)
        return 0;
    return _10->mNum;
}

bool Unk_7102459df8::sub_710079CEB0() const {
    if (!_18)
        return false;
    return _18->mNum > 0;
}

s32 Unk_7102459df8::sub_710079CED0() const {
    if (!_18)
        return 0;
    return _18->mNum;
}

bool Unk_7102459df8::sub_710079CEE8() const {
    if (!_20)
        return false;
    return _20->mNum > 0;
}

s32 Unk_7102459df8::sub_710079CF08() const {
    if (!_20)
        return 0;
    return _20->mNum;
}

bool Unk_7102459df8::sub_710079CF20() const {
    if (!_20)
        return false;
    return _20->_582 != 0;
}

Unk_7102459df8::Unk_7102459e60::Unk1* Unk_7102459df8::sub_710079CF40(int idx) const {
    if (!_10)
        return nullptr;
    return &_10->mEntries[idx];
}

Unk_7102459df8::Unk_7102459e88::Unk1* Unk_7102459df8::sub_710079CF6C(int idx) const {
    if (!_18)
        return nullptr;
    return &_18->mEntries[idx];
}

Unk_7102459df8::Unk_710079d5a0::Unk1* Unk_7102459df8::sub_710079CF98(int idx) const {
    if (!_20)
        return nullptr;
    return &_20->mEntries[idx];
}

}  // namespace ksys::act

namespace ksys::act {

Unk_710245a0b8::~Unk_710245a0b8() = default;
Unk_710245a0e0::~Unk_710245a0e0() = default;

void Unk_7102459df8::Unk_7102459e60::Unk1::sub_710079F508(
    const sead::Vector3f& position, const sead::Vector3f& normal,
    const ActorConstDataAccess* actor, const phys::MaterialMask& material1,
    const phys::MaterialMask& material2) {
    _28 = material2;
    _40 = material1;
    if (actor)
        actor->linkAcquire(&_18);
    else
        _18.reset();
    _0 = position;
    _c = normal;
}

// NON_MATCHING: the same-source record update is inlined instead of retaining its native call.
void Unk_710245a0e0::m2(Actor* actor) {
    auto* controller = actor->getCharacterController();
    if (!controller || !controller->sub_7100F5F128())
        return;
    ++mNum;
    sead::Vector3f position;
    controller->sub_7100F5F234(&position);
    const phys::MaterialMask material2(18u);
    const phys::MaterialMask material1(2u);
    mEntries[0].sub_710079F508(controller->sub_7100F5F134(), controller->sub_7100F5F140(),
                             nullptr, material1, material2);
}

}  // namespace ksys::act
