#include "Game/AI/AI/aiGuardianMiniBattleStateSelect.h"
#include "Game/AI/AI/aiGuardianMiniRoot.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianMiniBattleStateSelect::GuardianMiniBattleStateSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMiniBattleStateSelect::~GuardianMiniBattleStateSelect() = default;

bool GuardianMiniBattleStateSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool GuardianMiniBattleStateSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool GuardianMiniBattleStateSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void GuardianMiniBattleStateSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100416744(params, true);
}

void GuardianMiniBattleStateSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniBattleStateSelect::loadParams_() {
    getStaticParam(&mSecondLifeRatio_s, "SecondLifeRatio");
    getStaticParam(&mFinalLifeRatio_s, "FinalLifeRatio");
    getStaticParam(&mIsEnterOnly_s, "IsEnterOnly");
}

void GuardianMiniBattleStateSelect::calc_() {
    if (getCurrentChild()->isChangeable() && !*mIsEnterOnly_s)
        sub_7100416744(nullptr, false);
}

void GuardianMiniBattleStateSelect::sub_7100416744(ksys::act::ai::InlineParamPack* params,
                                                   bool force) {
    if (!sub_71004282EC(mActor)) {
        if (force || !isCurrentChild("第一段階"))
            changeChild("第一段階", params);
        return;
    }
    auto* life_ptr = mActor->getLife();
    const f32 life = life_ptr ? f32(*life_ptr) : 1.0f;
    const f32 max_life = mActor->getMaxLife();
    if (life <= max_life * *mFinalLifeRatio_s) {
        if (force || !isCurrentChild("最終段階"))
            changeChild("最終段階", params);
    } else if (life <= max_life * *mSecondLifeRatio_s) {
        if (force || !isCurrentChild("第二段階"))
            changeChild("第二段階", params);
    } else {
        if (force || !isCurrentChild("第一段階"))
            changeChild("第一段階", params);
    }
}

}  // namespace uking::ai
