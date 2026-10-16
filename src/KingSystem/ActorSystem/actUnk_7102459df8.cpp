#include "KingSystem/ActorSystem/actUnk_7102459df8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physSystem.h"
#include <math/seadMathCalcCommon.h>
#include <heap/seadHeap.h>

namespace ksys::act {

Unk_7102459df8::~Unk_7102459df8() = default;

// NON_MATCHING: the original combines two flags for the result of the non-player branches and stores mNum
// before the derived vtable.
bool Unk_7102459df8::m4(sead::Heap* heap, const Unk_71025ca5f8* arg) {
    if (sead::IsDerivedFrom<Unk_71025ca5f8>(arg) && arg->_8 == 1) {
        _10 = new (heap, 8) Unk_710245a0e0;
        if (!_10)
            return false;
        _18 = new (heap, 8) Unk_710245a028;
        if (_18 && sub_710079C9A0(heap)) {
            if (!_38.getBufferPtr())
                return true;
            _20 = new (heap, 8) Unk_710079d5a0;
            if (_20)
                return true;
        }
        m6();
        return false;
    }

    if (mActor->getCharacterController()) {
        _10 = new (heap, 8) Unk_710245a0e0;
        if (!_10)
            return false;
        _18 = new (heap, 8) Unk_710245a000;
    } else {
        if (!mActor->getMainBody())
            return false;
        _10 = new (heap, 8) Unk_710245a0b8;
        if (!_10)
            return false;
        _18 = new (heap, 8) Unk_7102459fd8;
    }
    if (_18 && sub_710079C9A0(heap)) {
        if (!_38.getBufferPtr())
            return true;
        _20 = new (heap, 8) Unk_710079d5a0;
        if (_20)
            return true;
    }
    m6();
    return false;
}

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

void Unk_7102459df8::m8() {
    if (_18) {
        _18->sub_710079FE9C();
        _18->m2(mActor);
    }
    if (_10) {
        _10->sub_71007A5318();
        _10->m2(mActor);
    }
    if (_20) {
        _20->sub_710079F600();
        _20->sub_710079F9C0(&_38, mActor);
        _20->sub_710079F66C(&_28, mActor);
    }
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

void Unk_7102459df8::Unk_7102459e60::Unk1::sub_710079F508(
    const sead::Vector3f& position, const sead::Vector3f& normal,
    const ActorLinkConstDataAccess* actor, const phys::MaterialMask& material1,
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

// The initialized word at 0x7102459fd0 is the contact-layer selection mask.
KSYS_VISIBILITY_HIDDEN u32 sUnk_7102459fd0 = 0x1504;

// NON_MATCHING: global mask address and load scheduling.
bool sub_710079F598(phys::RigidBody* body) {
    if (!body || body->getContactLayer() > phys::ContactLayer::EntityForbidden30)
        return false;
    return (sUnk_7102459fd0 & (1 << body->getContactLayer())) != 0;
}

}  // namespace ksys::act

