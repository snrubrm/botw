#include "Game/AI/AI/aiLastBossShieldBash.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LastBossShieldBash::LastBossShieldBash(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossShieldBash::~LastBossShieldBash() = default;

bool LastBossShieldBash::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossShieldBash::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsAttackPatternFixed_d) {
        ksys::act::ai::InlineParamPack pack;
        const sead::Vector3f pos = *mTargetPos_d;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("ジャンプ斬り", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("盾突き攻撃", &pack);
    }
}

void LastBossShieldBash::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossShieldBash::loadParams_() {
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool LastBossShieldBash::isChangeable() const {
    auto* child = getCurrentChild();
    if (!child)
        return false;
    return child->isChangeable();
}

}  // namespace uking::ai
