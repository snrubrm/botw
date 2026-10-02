#include "Game/AI/AI/aiWaitNearTarget.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WaitNearTarget::WaitNearTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaitNearTarget::~WaitNearTarget() = default;

bool WaitNearTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaitNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    const auto& pos = mActor->getMtx().getTranslation();
    const sead::Vector2f diff(pos.x - mTargetPos_d->x, pos.z - mTargetPos_d->z);
    const f32 dist = diff.length();
    if (*mBaseDist_s + *mStartCloseDistOffset_s + sub_71007320F0(mActor, *mWeaponIdx_s) <= dist &&
        (!*mIsCheckLineReachableForClose_s ||
         sub_710072CB78(mActor, *mTargetPos_d, nullptr,
                        *mBaseDist_s + *mStartCloseDistOffset_s +
                            sub_71007320F0(mActor, *mWeaponIdx_s),
                        -1))) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("近づき", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("待機", &pack);
    }
}

void WaitNearTarget::calc_() {
    const auto& pos = mActor->getMtx().getTranslation();
    const sead::Vector2f diff(pos.x - mTargetPos_d->x, pos.z - mTargetPos_d->z);
    const f32 dist = diff.length();
    auto* child = getCurrentChild();
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (child->isFinished() || child->isFailed()) {
        if (*mBaseDist_s + *mOutDistOffset_s + sub_71007320F0(mActor, *mWeaponIdx_s) <= dist) {
            setFailed();
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("待機", &pack);
        }
    } else if (child->isChangeable()) {
        if (*mBaseDist_s + *mOutDistOffset_s + sub_71007320F0(mActor, *mWeaponIdx_s) <= dist) {
            setFailed();
        } else if (isCurrentChild("待機")) {
            if (*mBaseDist_s + *mStartCloseDistOffset_s + sub_71007320F0(mActor, *mWeaponIdx_s) <=
                    dist &&
                (!*mIsCheckLineReachableForClose_s ||
                 sub_710072CB78(mActor, *mTargetPos_d, nullptr,
                                *mBaseDist_s + *mStartCloseDistOffset_s +
                                    sub_71007320F0(mActor, *mWeaponIdx_s),
                                -1))) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("近づき", &pack);
            }
        }
    }
}

void WaitNearTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaitNearTarget::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mStartCloseDistOffset_s, "StartCloseDistOffset");
    getStaticParam(&mOutDistOffset_s, "OutDistOffset");
    getStaticParam(&mIsCheckLineReachableForClose_s, "IsCheckLineReachableForClose");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
