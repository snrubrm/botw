#include "Game/AI/AI/aiSeqAnimalAttack.h"

namespace uking::ai {

SeqAnimalAttack::SeqAnimalAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqAnimalAttack::~SeqAnimalAttack() = default;

bool SeqAnimalAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqAnimalAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqAnimalAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqAnimalAttack::loadParams_() {
    getStaticParam(&mIsUseAfterAttackState_s, "IsUseAfterAttackState");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool SeqAnimalAttack::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

// NON_MATCHING: scheduling of the SafeString argument setup before the shared isCurrentChild call
bool SeqAnimalAttack::isFinished() const {
    if (ksys::act::ai::Ai::isFinished())
        return true;
    if (!getCurrentChild()->isFinished())
        return false;
    if (*mIsUseAfterAttackState_s)
        return isCurrentChild("攻撃ヒット後") || isCurrentChild("攻撃ハズレ後");
    return isCurrentChild("攻撃");
}

}  // namespace uking::ai
