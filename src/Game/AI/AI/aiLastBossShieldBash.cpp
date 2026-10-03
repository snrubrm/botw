#include "Game/AI/AI/aiLastBossShieldBash.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
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

// inline-only in the original (the same sequence appears twice in calc_ and in enter_); name is a guess.
inline void LastBossShieldBash::changeToJumpSlash() {
    ksys::act::ai::InlineParamPack pack;
    const sead::Vector3f pos = *mTargetPos_d;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("ジャンプ斬り", &pack);
}

// inline-only in the original (calc_ has two copies); name is a guess.
static bool isPlayerX31() {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    return player.x_31();
}

void LastBossShieldBash::calc_() {
    auto* child = getCurrentChild();
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (child->isFailed()) {
        setFailed();
    } else if (child->isFinished()) {
        if (isCurrentChild("盾突き攻撃")) {
            if (isPlayerX31() || child->isFinished()) {
                child->isFinished();
                changeToJumpSlash();
                return;
            }
        }
        setFinished();
    } else if (child->isChangeable()) {
        if (isCurrentChild("盾突き攻撃")) {
            if (isPlayerX31())
                changeToJumpSlash();
        }
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
