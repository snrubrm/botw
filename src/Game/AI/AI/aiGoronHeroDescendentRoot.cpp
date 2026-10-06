#include "Game/AI/AI/aiGoronHeroDescendentRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GoronHeroDescendentRoot::GoronHeroDescendentRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GoronHeroDescendentRoot::~GoronHeroDescendentRoot() {
    sub_7100A9A6AC(false);
}

bool GoronHeroDescendentRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GoronHeroDescendentRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GoronHeroDescendentRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GoronHeroDescendentRoot::loadParams_() {
    getStaticParam(&mGuardEndDelayTime_s, "GuardEndDelayTime");
    getStaticParam(&mWhistleReactTimeGo_s, "WhistleReactTimeGo");
    getStaticParam(&mWhistleReactTimeStop_s, "WhistleReactTimeStop");
    getStaticParam(&mAppearWaitTime_s, "AppearWaitTime");
    getStaticParam(&mPlayerNearDist_s, "PlayerNearDist");
    getStaticParam(&mPlayerLeaveDist_s, "PlayerLeaveDist");
    getStaticParam(&mPlayerSeparateDist_s, "PlayerSeparateDist");
    getStaticParam(&mFollowModeFlagName_s, "FollowModeFlagName");
    getStaticParam(&mPlayerFollowOffset_s, "PlayerFollowOffset");
}

bool GoronHeroDescendentRoot::sub_71004090D4() {
    if (isCurrentChild("ジャンプ準備") || isCurrentChild("ジャンプ") || isCurrentChild("砲台内") ||
        isCurrentChild("着地") || isCurrentChild("帰還")) {
        return true;
    }
    return false;
}

bool GoronHeroDescendentRoot::sub_71004095E4() {
    if (isCurrentChild("プレイヤー追従") || isCurrentChild("プレイヤー接近待機") ||
        isCurrentChild("停止命令") || isCurrentChild("減速") || isCurrentChild("待機")) {
        return true;
    }
    return false;
}

void GoronHeroDescendentRoot::changeToStopCommand() {
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "TerrorOccurring", -1);
    pack.addVec3(mActor->getMtx().getTranslation(), "TargetPos", -1);
    changeChild("停止命令", &pack);
}

void GoronHeroDescendentRoot::changeToWaitForPlayerApproach() {
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "TerrorOccurring", -1);
    pack.addVec3(mActor->getMtx().getTranslation(), "TargetPos", -1);
    changeChild("プレイヤー接近待機", &pack);
}

}  // namespace uking::ai
