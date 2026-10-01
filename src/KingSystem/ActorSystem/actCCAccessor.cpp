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
    mMotionType = cc->sub_7100F5F0E4();
    return true;
}

// NON_MATCHING: the original passes/returns the motion type as a 4-byte struct (x0/x2, `mov w0, w0`)
// and compares through stack slots - consistent with a SEAD_ENUM (volatile operator int); the enum's
// value names are unknown
bool CCAccessor::changeMotionType(phys::CharacterController* cc, MotionType motion_type) {
    if (!cc)
        return false;
    mMotionType = cc->sub_7100F5F0E4();
    if (cc->sub_7100F5F0E4() != motion_type)
        cc->sub_7100F5F458(motion_type);
    return true;
}

// NON_MATCHING: the original passes/returns the motion type as a 4-byte struct (x0/x2, `mov w0, w0`)
// and compares through stack slots - consistent with a SEAD_ENUM (volatile operator int); the enum's
// value names are unknown
void CCAccessor::resetMotionType(phys::CharacterController* cc) {
    if (!cc)
        return;
    if (cc->sub_7100F5F0E4() != mMotionType)
        cc->sub_7100F5F458(mMotionType);
}

void CCAccessor::resetRigidBodyMotion(Actor* actor) {
    if (auto* physics = actor->getPhysics())
        physics->sub_7100FBADDC();
}

void CCAccessor::sub_710072AE20(phys::CharacterController* cc) {
    if (!cc)
        return;
    if (_4.isOn(1))
        _5.change(1, cc->sub_7100F636EC());
    if (_4.isOn(2))
        _5.change(2, cc->sub_7100F63590());
    if (_4.isOn(4))
        _5.change(4, cc->sub_7100F62D34());
    if (_4.isOn(8))
        _5.change(8, cc->mFlags.isOn(8));
}

// NON_MATCHING: last block - the original selects the new flag word with csel, we branch
void CCAccessor::sub_710072AEEC(phys::CharacterController* cc) {
    if (!cc)
        return;
    if (_4.isOn(1) && _5.isOn(1) != cc->sub_7100F636EC())
        cc->sub_7100F636B0(_5.isOn(1));
    if (_4.isOn(2) && _5.isOn(2) != cc->sub_7100F63590())
        cc->sub_7100F63554(_5.isOn(2));
    if (_4.isOn(4) && _5.isOn(4) != cc->sub_7100F62D34())
        cc->sub_7100F62CA8(_5.isOn(4));
    if (_4.isOn(8) && _5.isOn(8) != cc->mFlags.isOn(8))
        cc->mFlags.change(8, _5.isOn(8));
}

}  // namespace ksys::act
