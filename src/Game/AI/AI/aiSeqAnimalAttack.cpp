#include "Game/AI/AI/aiSeqAnimalAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007398C0.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

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
    _54 = false;
    sub_71005DB3EC(mActor);
    if (auto* control = sub_71007398C0(mActor))
        control->_90[3] = control->_90[2];
}

void SeqAnimalAttack::loadParams_() {
    getStaticParam(&mIsUseAfterAttackState_s, "IsUseAfterAttackState");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool SeqAnimalAttack::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool SeqAnimalAttack::isFinished() const {
    if (ksys::act::ai::Ai::isFinished())
        return true;
    if (!getCurrentChild()->isFinished())
        return false;
    if (!*mIsUseAfterAttackState_s)
        return isCurrentChild("攻撃");
    return isCurrentChild("攻撃ヒット後") || isCurrentChild("攻撃ハズレ後");
}

}  // namespace uking::ai
