#include "Game/AI/Action/actionMagneGearGrabbed.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

MagneGearGrabbed::MagneGearGrabbed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MagneGearGrabbed::~MagneGearGrabbed() = default;

bool MagneGearGrabbed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original loads _1c first and stores the two 60.0f floats as one 64-bit constant (ours: stp w8, w8)
void MagneGearGrabbed::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = ksys::Timer(60.0f, 60.0f);
    _34 = false;
    if (_1c) {
        if (auto* body = mActor->getMainBody())
            body->changeMotionType(ksys::phys::MotionType::Dynamic);
        _1c = 0;
    }
    mFlags.set(Flag::Changeable);
}

void MagneGearGrabbed::leave_() {
    ksys::act::ai::Action::leave_();
}

void MagneGearGrabbed::loadParams_() {
    getStaticParam(&mConnectDistance_s, "ConnectDistance");
}

void MagneGearGrabbed::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
