#include "Game/AI/Action/actionFixedMagneStick.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

FixedMagneStick::FixedMagneStick(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FixedMagneStick::~FixedMagneStick() = default;

bool FixedMagneStick::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FixedMagneStick::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.reset(Flag::Changeable);
    _58 = 0;
}

void FixedMagneStick::leave_() {
    mActor->emitBasicSigOff();
    if (_38)
        _38->sub_7100F6A074();
    if (mActor) {
        if (auto* body = mActor->getMainBody())
            body->changeMotionType(ksys::phys::MotionType::Dynamic);
    }
}

void FixedMagneStick::loadParams_() {
    getMapUnitParam(&mGrabbedMagneReleaseTime_m, "GrabbedMagneReleaseTime");
    getAITreeVariable(&mMagneStickLength_a, "MagneStickLength");
    getAITreeVariable(&mIsTargetFixedAcceptor_a, "IsTargetFixedAcceptor");
}

void FixedMagneStick::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
