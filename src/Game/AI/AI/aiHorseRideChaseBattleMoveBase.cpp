#include "Game/AI/AI/aiHorseRideChaseBattleMoveBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

HorseRideChaseBattleMoveBase::HorseRideChaseBattleMoveBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

HorseRideChaseBattleMoveBase::~HorseRideChaseBattleMoveBase() = default;

bool HorseRideChaseBattleMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideChaseBattleMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _58.x();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D93CC(mActor), "TargetPos", -1);
    changeChild("追跡指令", &pack);
}

void HorseRideChaseBattleMoveBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideChaseBattleMoveBase::loadParams_() {
    getStaticParam(&mSlowDownDist_s, "SlowDownDist");
    getStaticParam(&mSpeedUpDist_s, "SpeedUpDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
}

bool HorseRideChaseBattleMoveBase::handleMessage_(const ksys::Message& message) {
    if (!_58.m2(message))
        return false;
    setFailed();
    return true;
}

}  // namespace uking::ai
