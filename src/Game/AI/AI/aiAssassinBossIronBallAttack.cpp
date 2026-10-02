#include "Game/AI/AI/aiAssassinBossIronBallAttack.h"

namespace uking::ai {

AssassinBossIronBallAttack::AssassinBossIronBallAttack(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AssassinBossIronBallAttack::~AssassinBossIronBallAttack() = default;

bool AssassinBossIronBallAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AssassinBossIronBallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71003189D4())
        changeChild("攻撃", params);
    else
        changeChild("準備完了待ち", params);
}

void AssassinBossIronBallAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinBossIronBallAttack::loadParams_() {
    getStaticParam(&mIronBallNum_s, "IronBallNum");
    getStaticParam(&mIronBallPartsName_s, "IronBallPartsName");
}

void AssassinBossIronBallAttack::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("準備完了待ち"))
            setFailed();
        else
            setFinished();
        return;
    }
    if (child->isChangeable() && sub_71003189D4() && !isCurrentChild("攻撃"))
        changeChild("攻撃");
}

}  // namespace uking::ai
