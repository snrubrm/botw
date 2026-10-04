#include "Game/AI/AI/aiLynelThreeBreathAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LynelThreeBreathAttack::LynelThreeBreathAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelThreeBreathAttack::~LynelThreeBreathAttack() = default;

bool LynelThreeBreathAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelThreeBreathAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("先行動", &pack);
}

void LynelThreeBreathAttack::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        const bool is_xz = *mIsCheckXZ_s;
        const sead::Vector3f& target = *mTargetPos_d;
        const sead::Matrix34f& mtx = mActor->getMtx();
        f32 dist;
        if (is_xz)
            dist = sead::Vector2f(mtx(0, 3) - target.x, mtx(2, 3) - target.z).length();
        else
            dist = (mtx.getTranslation() - target).length();
        if (*mNearRange_s >= dist) {
            setFinished();
            return;
        }
        if (*mFarRange_s > 0 && *mFarRange_s <= dist) {
            setFailed();
            return;
        }

        if (sub_71005D8FBC(mActor)) {
            bool seen;
            {
                ksys::act::acc::PlayerBase player;
                ksys::act::acquireActor(&sub_71005D94AC(mActor), &player);
                seen = player.x_13();
            }
            if (seen) {
                setFinished();
                return;
            }
        }

        if (isCurrentChild("先行動")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("中行動", &pack);
        } else if (isCurrentChild("中行動")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("後行動", &pack);
        } else if (child->isFailed()) {
            setFailed();
        } else {
            setFinished();
        }
    } else {
        child->isChangeable();
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    }
}

void LynelThreeBreathAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelThreeBreathAttack::loadParams_() {
    getStaticParam(&mNearRange_s, "NearRange");
    getStaticParam(&mFarRange_s, "FarRange");
    getStaticParam(&mIsCheckXZ_s, "IsCheckXZ");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool LynelThreeBreathAttack::isFinished() const {
    if (ksys::act::ai::Ai::isFinished())
        return true;

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;

    const bool is_xz = *mIsCheckXZ_s;
    const sead::Vector3f& target = *mTargetPos_d;
    const sead::Matrix34f& mtx = mActor->getMtx();
    f32 dist;
    if (is_xz)
        dist = sead::Vector2f(mtx(0, 3) - target.x, mtx(2, 3) - target.z).length();
    else
        dist = (mtx.getTranslation() - target).length();
    if (*mNearRange_s >= dist)
        return true;

    if (!sub_71005D8FBC(mActor))
        return false;
    ksys::act::acc::PlayerBase player;
    ksys::act::acquireActor(&sub_71005D94AC(mActor), &player);
    return player.x_13();
}

bool LynelThreeBreathAttack::isFailed() const {
    if (ksys::act::ai::Ai::isFailed())
        return true;

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;

    const bool is_xz = *mIsCheckXZ_s;
    const sead::Vector3f& target = *mTargetPos_d;
    const sead::Matrix34f& mtx = mActor->getMtx();
    f32 dist;
    if (is_xz)
        dist = sead::Vector2f(mtx(0, 3) - target.x, mtx(2, 3) - target.z).length();
    else
        dist = (mtx.getTranslation() - target).length();
    return *mFarRange_s > 0 && *mFarRange_s <= dist;
}

}  // namespace uking::ai
