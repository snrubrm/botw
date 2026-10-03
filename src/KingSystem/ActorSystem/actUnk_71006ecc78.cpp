#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/physDefines.h"

namespace ksys::act {

void Unk_71006ecc78::sub_71006ED484() {
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    auto* ragdoll = physics->getRagdollInstance();
    if (!ragdoll)
        return;

    if (!mActor->sub_71011CEA90())
        mActor->sub_71011D7E24();
    if (_d2.isOnBit(6))
        sub_71006ECD6C(false);
    physics->sub_7100FBC838(1);
    ragdoll->x_22(-1, 0.0f);
    ragdoll->disableContactLayer(phys::ContactLayer::EntityRagdoll);
    _c0 = 0;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EEE0(0.0f);
    if (!_d2.isOnBit(0))
        mActor->getRagdollInstance()->disableContactLayer(phys::ContactLayer::EntityPlayer);
    _d2.resetBit(7);
    _cc = -1;
}

// NON_MATCHING: the two comparisons against _cc are combined with the operands of `and` swapped
bool Unk_71006ecc78::sub_71006ED9EC() const {
    if (!mActor->sub_71011CEA90())
        return false;
    if (_c8 < 0)
        return true;
    const s8 current = mActor->getPhysics()->get112();
    if (current == _c8)
        return false;
    return current != _cc && _c8 != _cc;
}

void Unk_71006ecc78::sub_71006EDCB8() {
    if (!_8)
        return;

    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EEE0(1.0f);
    mActor->sub_71011D7E68();
    if (auto* bone_control = mActor->getBoneControl())
        bone_control->sub_7100D82FC4();
    mActor->getRagdollInstance()->x_22(-1, 1.0f);
    mActor->getRagdollInstance()->disableContactLayer(phys::ContactLayer::EntityRagdoll);
    if (!_d2.isOnBit(0))
        mActor->getRagdollInstance()->disableContactLayer(phys::ContactLayer::EntityPlayer);
    _d2.resetBit(7);
    _c0 = 2;
}

void Unk_71006ecc78::sub_71006EE280(const sead::SafeString& name) {
    if (auto* physics = mActor->getPhysics())
        _c8 = physics->sub_7100FBDA2C(name);
}

// NON_MATCHING: the original loads the actor before _c8 (scheduling of the inlined sub_71006ED9EC)
void Unk_71006ecc78::sub_71006EDD5C() {
    if (!sub_71006ED9EC())
        return;

    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EEE0(1.0f);
    _c0 = 1;
    _c4 = 5;
    _b8 = 5.0f;
}

// NON_MATCHING: as sub_71006ED9EC (operand order of `and`)
bool Unk_71006ecc78::sub_71006EDDD4() const {
    if (!_8)
        return false;
    if (!mActor->sub_71011CEA90())
        return false;
    return sub_71006ED9EC();
}

bool Unk_71006ecc78::sub_71006EDF9C() const {
    if (!_8)
        return false;
    auto* physics = mActor->getPhysics();
    if (!physics)
        return false;
    return physics->sub_7100FBB4B4();
}

void Unk_71006ecc78::sub_71006EDFBC() {
    if (_d2.isOnBit(0))
        return;
    mActor->getPhysics()->sub_7100FBDD40(true);
    if (mActor->getRagdollInstance())
        mActor->getRagdollInstance()->enableContactLayer(phys::ContactLayer::EntityPlayer);
    _d2.setBit(0);
}

void Unk_71006ecc78::sub_71006EE018() {
    if (!_d2.isOnBit(0))
        return;
    mActor->getPhysics()->sub_7100FBDD40(false);
    if (!_d2.isOnBit(7) && mActor->getRagdollInstance())
        mActor->getRagdollInstance()->disableContactLayer(phys::ContactLayer::EntityPlayer);
    _d2.resetBit(0);
}

bool Unk_71006ecc78::sub_71006EE15C() const {
    auto* ragdoll = mActor->getRagdollInstance();
    if (!ragdoll)
        return true;
    if (_d1)
        return false;
    return ragdoll->sub_7101221D24();
}

bool Unk_71006ecc78::sub_71006EE1A4() const {
    auto* ragdoll = mActor->getRagdollInstance();
    if (!ragdoll)
        return false;
    if (_d1)
        return false;
    if (ragdoll->sub_7101221D24())
        return false;
    return _88 <= 0.0f;
}

void Unk_71006ecc78::sub_71006EE128(sead::Vector3f* out) const {
    *out = _8->_c4;
}

void Unk_71006ecc78::sub_71006EE2E8(f32 scale) {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FBDC70(scale);
}

void Unk_71006ecc78::sub_71006EE2FC() {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FBDC70(1.0f);
}

}  // namespace ksys::act
