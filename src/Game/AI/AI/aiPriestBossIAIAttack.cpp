#include "Game/AI/AI/aiPriestBossIAIAttack.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

PriestBossIAIAttack::PriestBossIAIAttack(const InitArg& arg) : IAIAttack(arg) {}

PriestBossIAIAttack::~PriestBossIAIAttack() = default;

bool PriestBossIAIAttack::init_(sead::Heap* heap) {
    return IAIAttack::init_(heap);
}

void PriestBossIAIAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    IAIAttack::enter_(params);
}

void PriestBossIAIAttack::leave_() {
    IAIAttack::leave_();
}

void PriestBossIAIAttack::loadParams_() {
    IAIAttack::loadParams_();
}

void PriestBossIAIAttack::m34(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    params.addVec3(pos, "MoveTargetPos", -1);
    changeChild("駆け寄り", &params);
}

}  // namespace uking::ai
