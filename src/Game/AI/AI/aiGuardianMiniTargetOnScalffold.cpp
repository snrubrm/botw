#include "Game/AI/AI/aiGuardianMiniTargetOnScalffold.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardianMiniTargetOnScalffold::GuardianMiniTargetOnScalffold(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMiniTargetOnScalffold::~GuardianMiniTargetOnScalffold() = default;

void GuardianMiniTargetOnScalffold::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710042902C(true);
}

void GuardianMiniTargetOnScalffold::sub_710042902C(bool flag) {
    const sead::Vector2f target(mParams.mTargetPos_d->x, mParams.mTargetPos_d->z);
    const sead::Vector2f actor_pos(mActor->getMtx().m[0][3], mActor->getMtx().m[2][3]);
    const sead::Vector2f diff = target - actor_pos;
    const f32 dist = diff.length();
    if (flag) {
        if (dist >= *mParams.mFarDist_s) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
            changeChild("遠距離行動", &pack);
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
            changeChild("行動", &pack);
        }
        return;
    }
    if (isCurrentChild("行動")) {
        if (!(dist >= *mParams.mFarDist_s))
            return;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
        changeChild("遠距離行動", &pack);
        return;
    }
    if (isCurrentChild("遠距離行動")) {
        if (!(dist <= *mParams.mNearDist_s))
            return;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
        changeChild("行動", &pack);
    }
}

void GuardianMiniTargetOnScalffold::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniTargetOnScalffold::loadParams_() {
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mFarDist_s, "FarDist");
    getStaticParam(&mParams.mNearDist_s, "NearDist");
}

void GuardianMiniTargetOnScalffold::calc_() {
    sub_71005DB1D8(mActor, *mParams.mTargetPos_d);
    getCurrentChild()->setDynamicParam(*mParams.mTargetPos_d, "TargetPos");
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
    else if (getCurrentChild()->isChangeable())
        sub_710042902C(false);
}

}  // namespace uking::ai
