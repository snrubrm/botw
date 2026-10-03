#include "Game/AI/AI/aiGuardianWait.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardianWait::GuardianWait(const InitArg& arg) : GuardianAI(arg) {}

GuardianWait::~GuardianWait() = default;

bool GuardianWait::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianWait::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
    if (sub_7100EEF034(mActor, 0)) {
        changeChild("レール移動");
        return;
    }

    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(home_pos, "CentralPos", -1);
    changeChild("ランダム移動", &pack);
}

void GuardianWait::calc_() {
    GuardianAI::calc_();
}

void GuardianWait::leave_() {
    GuardianAI::leave_();
}

void GuardianWait::loadParams_() {
    GuardianAI::loadParams_();
}

}  // namespace uking::ai
