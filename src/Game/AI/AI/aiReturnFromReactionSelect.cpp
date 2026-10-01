#include "Game/AI/AI/aiReturnFromReactionSelect.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

ReturnFromReactionSelect::ReturnFromReactionSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReturnFromReactionSelect::~ReturnFromReactionSelect() = default;

bool ReturnFromReactionSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReturnFromReactionSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsEnableRetFromDamage_s && testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0))
        changeChild("ダメージ復帰", params);
    else if (*mIsEnableRetFromGuard_s && testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1))
        changeChild("ガード復帰", params);
    else if (*mIsEnableRetFromRebound_s && testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4))
        changeChild("弾かれ復帰", params);
    else
        changeChild("通常", params);
}

void ReturnFromReactionSelect::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        child->isChangeable();
        return;
    }

    if (*mIsChangeToNormalByFinish_s && !isCurrentChild("通常"))
        changeChild("通常");
}

void ReturnFromReactionSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReturnFromReactionSelect::loadParams_() {
    getStaticParam(&mIsChangeToNormalByFinish_s, "IsChangeToNormalByFinish");
    getStaticParam(&mIsEnableRetFromDamage_s, "IsEnableRetFromDamage");
    getStaticParam(&mIsEnableRetFromGuard_s, "IsEnableRetFromGuard");
    getStaticParam(&mIsEnableRetFromRebound_s, "IsEnableRetFromRebound");
}

bool ReturnFromReactionSelect::isFinished() const {
    if (!*mIsChangeToNormalByFinish_s)
        return getCurrentChild()->isFinished();
    return isCurrentChild("通常") && getCurrentChild()->isFinished();
}

bool ReturnFromReactionSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

}  // namespace uking::ai
