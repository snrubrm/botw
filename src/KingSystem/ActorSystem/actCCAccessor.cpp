#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace ksys::act {

phys::CharacterController* CCAccessor::sub_710072ACF8(Actor* actor) {
    if (!actor)
        return nullptr;
    return actor->getCharacterController();
}

CCAccessor::CCAccessor() = default;

CCAccessor::~CCAccessor() = default;

bool CCAccessor::sub_710072AD1C(phys::CharacterController* cc) {
    if (!cc)
        return false;
    mSavedMotionType = cc->sub_7100F5F0E4();
    return true;
}

void CCAccessor::resetMotionType(phys::CharacterController* cc) {
    if (!cc)
        return;
    const MotionType motion_type = mSavedMotionType;
    const MotionType current = cc->sub_7100F5F0E4();
    if (int(current) != int(motion_type))
        cc->sub_7100F5F458(motion_type);
}

void CCAccessor::resetRigidBodyMotion(Actor* actor) {
    if (auto* physics = actor->getPhysics())
        physics->sub_7100FBADDC();
}

void CCAccessor::saveFlags(phys::CharacterController* cc) {
    if (!cc)
        return;
    if (mSavedFlagMask.isOn(1))
        mSavedFlags.change(1, cc->sub_7100F636EC());
    if (mSavedFlagMask.isOn(2))
        mSavedFlags.change(2, cc->sub_7100F63590());
    if (mSavedFlagMask.isOn(4))
        mSavedFlags.change(4, cc->sub_7100F62D34());
    if (mSavedFlagMask.isOn(8))
        mSavedFlags.change(8, cc->mFlags.isOn(8));
}

void CCAccessor::restoreSavedFlags(phys::CharacterController* cc) {
    if (!cc)
        return;
    if (mSavedFlagMask.isOn(1) && mSavedFlags.isOn(1) != cc->sub_7100F636EC())
        cc->sub_7100F636B0(mSavedFlags.isOn(1));
    if (mSavedFlagMask.isOn(2) && mSavedFlags.isOn(2) != cc->sub_7100F63590())
        cc->sub_7100F63554(mSavedFlags.isOn(2));
    if (mSavedFlagMask.isOn(4) && mSavedFlags.isOn(4) != cc->sub_7100F62D34())
        cc->sub_7100F62CA8(mSavedFlags.isOn(4));
    if (mSavedFlagMask.isOn(8) && mSavedFlags.isOn(8) != cc->mFlags.isOn(8))
        cc->mFlags.setDirect(mSavedFlags.isOn(8) ? (cc->mFlags.getDirect() | 8) :
                                       (cc->mFlags.getDirect() & ~8));
}

}  // namespace ksys::act
