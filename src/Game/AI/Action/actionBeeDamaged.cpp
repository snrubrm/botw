#include "Game/AI/Action/actionBeeDamaged.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actSwarm.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710072A944.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

BeeDamaged::BeeDamaged(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BeeDamaged::~BeeDamaged() = default;

bool BeeDamaged::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BeeDamaged::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BeeDamaged::leave_() {
    if (auto* swarm = sead::DynamicCast<act::Swarm>(mActor))
        swarm->_162c = 0;
    sub_710072ABB4(mActor);
}

void BeeDamaged::loadParams_() {
    getStaticParam(&mParams.mTime_s, "Time");
    getStaticParam(&mParams.mSubActorSpeed_s, "SubActorSpeed");
    getStaticParam(&mParams.mAddYSpeed_s, "AddYSpeed");
}

// NON_MATCHING: the original loads the target x / z before the actor translation and stores dir.y first
// (scheduling of the loads / stores of `dir` only).
void BeeDamaged::calc_() {
    if (*mParams.mTime_s >= 1) {
        mTimer.update();
        if (mTimer.value <= sead::Mathf::epsilon())
            setFinished();
    }
    if (auto* swarm = sead::DynamicCast<act::Swarm>(mActor)) {
        swarm->_1628 = 0;
        swarm->_162c = 2;
    }
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    const sead::Vector3f velocity{0, *mParams.mAddYSpeed_s * 30, 0};
    controller->sub_7100F5F6FC(velocity);
    const sead::Vector3f& target = sub_71005D8F28(mActor) ? sub_71005D9330(mActor) : mTargetPos;
    sead::Vector3f dir(target.x - mActor->getMtx()(0, 3), 0, target.z - mActor->getMtx()(2, 3));
    dir.normalize();
    if (dir.x == 0 && dir.z == 0) {
        sub_7100738660(controller, 0.9f);
        return;
    }
    sub_710073FA94(&_38, mActor);
    sub_71007407F0(&_38, dir, sead::Vector3f::ey, true, sead::Mathf::pi() / 6);
    sub_7100740E04(_38, controller);
}

}  // namespace uking::action
