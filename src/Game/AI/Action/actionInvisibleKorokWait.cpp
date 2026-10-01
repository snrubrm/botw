#include "Game/AI/Action/actionInvisibleKorokWait.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

InvisibleKorokWait::InvisibleKorokWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

InvisibleKorokWait::~InvisibleKorokWait() = default;

bool InvisibleKorokWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void InvisibleKorokWait::enter_(ksys::act::ai::InlineParamPack* params) {
    _30 = 0.0f;
}

void InvisibleKorokWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void InvisibleKorokWait::loadParams_() {
    getStaticParam(&mSpeedDecreRate_s, "SpeedDecreRate");
    getDynamicParam(&mDynStopTime_d, "DynStopTime");
}

void InvisibleKorokWait::calc_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
    if (_30 >= *mDynStopTime_d) {
        mFlags.set(Flag::Changeable);
        setFinished();
    } else {
        _30 += 1.0f;
    }
}

}  // namespace uking::action
