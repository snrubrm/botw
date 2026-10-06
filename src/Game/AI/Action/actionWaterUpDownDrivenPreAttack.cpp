#include "Game/AI/Action/actionWaterUpDownDrivenPreAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

WaterUpDownDrivenPreAttack::WaterUpDownDrivenPreAttack(const InitArg& arg)
    : WaterUpDownAnmDrivenMove(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
WaterUpDownDrivenPreAttack::~WaterUpDownDrivenPreAttack() {
    ;
}

bool WaterUpDownDrivenPreAttack::init_(sead::Heap* heap) {
    return WaterUpDownAnmDrivenMove::init_(heap);
}

void WaterUpDownDrivenPreAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterUpDownAnmDrivenMove::enter_(params);
}

void WaterUpDownDrivenPreAttack::leave_() {
    WaterUpDownAnmDrivenMove::leave_();
}

void WaterUpDownDrivenPreAttack::loadParams_() {
    WaterUpDownAnmDrivenMove::loadParams_();
    getStaticParam(&mTurnSpeed_s, "TurnSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void WaterUpDownDrivenPreAttack::calc_() {
    WaterUpDownAnmDrivenMove::calc_();
}

void WaterUpDownDrivenPreAttack::m32(ksys::phys::CharacterController* controller) {
    if (!sub_71005DD798(mActor, 0x29, nullptr, 0, 0)) {
        sub_7100738660(controller, *mRotReduceRatio_s);
        return;
    }

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir = *mTargetPos_d - pos;
    const sead::Vector3f up = getUpDir(mActor);
    ksys::util::sub_71011EFA00(&dir, dir, up);
    dir.normalize();
    sub_710073FA94(&_78, mActor);
    sub_71007407F0(&_78, dir, up, true, *mTurnSpeed_s);
    sub_7100740E04(_78, controller);
}

}  // namespace uking::action
