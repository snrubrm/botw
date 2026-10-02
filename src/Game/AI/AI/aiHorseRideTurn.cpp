#include "Game/AI/AI/aiHorseRideTurn.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

HorseRideTurn::HorseRideTurn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideTurn::~HorseRideTurn() = default;

bool HorseRideTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    _80.x();
    _48.x();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("指令", &pack);
}

void HorseRideTurn::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideTurn::loadParams_() {
    getStaticParam(&mFinAngle_s, "FinAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool HorseRideTurn::handleMessage_(const ksys::Message& message) {
    return _48.m2(message) || _80.m2(message);
}

}  // namespace uking::ai
