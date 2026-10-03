#include "Game/AI/AI/aiKeeseRoam.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

KeeseRoam::KeeseRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KeeseRoam::~KeeseRoam() = default;

bool KeeseRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

inline void KeeseRoam::changeToMove(const sead::Vector3f& target) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("移動", &pack);
}

void KeeseRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    _70 = false;
    _74 = 8;
    sead::Vector3f target;
    if (sub_7100453F6C(&target)) {
        changeToMove(target);
    } else {
        changeChild("待機");
    }
}

// NON_MATCHING: the original computes `max - min` of the y offset range in each branch (before the join) and
// schedules the length sum slightly differently
bool KeeseRoam::sub_7100453F6C(sead::Vector3f* out) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    const sead::Vector3f& center = *mCentralPos_d;

    sead::Vector3f diff = pos - center;
    const f32 dy = diff.y;
    diff.normalize();
    f32 angle = sead::Mathf::atan2(diff.x, diff.z);
    angle += sead::GlobalRandom::instance()->getF32Range(sead::Mathf::piHalf(),
                                                         sead::Mathf::piHalf() * 3);
    angle = ksys::util::sub_71011EF0CC(angle);

    f32 min_y, max_y;
    if (sead::GlobalRandom::instance()->getF32Range(*mMinOffsetY_s, *mMaxOffsetY_s) < dy) {
        min_y = *mMinOffsetY_s;
        max_y = 0;
    } else {
        min_y = 0;
        max_y = *mMaxOffsetY_s;
    }
    const f32 y_offset = sead::GlobalRandom::instance()->getF32Range(min_y, max_y);

    sead::Vector3f target{0, 0, *mRoamRadius_s};
    ksys::util::sub_71011EF010(&target, angle);
    target.y += y_offset;
    target += center;

    sead::Vector3f dir = target - pos;
    const f32 dist = dir.normalize();
    if (dist > *mMaxMoveDist_s)
        target = pos + dir * *mMaxMoveDist_s;
    else if (dist < *mMinMoveDist_s)
        return false;

    sead::Vector3f hit;
    if (sub_710072E500(pos, target, &hit, nullptr, nullptr, 0.0f)) {
        const sead::Vector3f hit_diff = hit - pos;
        if (hit_diff.squaredLength() <= *mMinMoveDist_s * *mMinMoveDist_s)
            return false;
        target = hit;
    }
    out->set(target);
    return true;
}

bool KeeseRoam::sub_7100454410(s32 tries) {
    for (s32 i = 0; i < tries; ++i) {
        sead::Vector3f target;
        if (sub_7100453F6C(&target)) {
            changeToMove(target);
            return true;
        }
    }
    return false;
}

void KeeseRoam::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("待機")) {
            if (sub_7100454410(2))
                return;
            _70 = true;
            _74 = 8;
        } else {
            if (sead::GlobalRandom::instance()->getF32Range(0.0f, 1.0f) < *mNoWaitRatio_s) {
                if (sub_7100454410(2))
                    return;
            }
            _70 = false;
        }
        changeChild("待機");
    } else if (child->isChangeable()) {
        if (_70 && isCurrentChild("待機")) {
            if (_74 <= 0)
                sub_7100454410(1);
            else
                --_74;
        }
    }
}

void KeeseRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KeeseRoam::loadParams_() {
    getStaticParam(&mMinOffsetY_s, "MinOffsetY");
    getStaticParam(&mMaxOffsetY_s, "MaxOffsetY");
    getStaticParam(&mRoamRadius_s, "RoamRadius");
    getStaticParam(&mMinMoveDist_s, "MinMoveDist");
    getStaticParam(&mMaxMoveDist_s, "MaxMoveDist");
    getStaticParam(&mNoWaitRatio_s, "NoWaitRatio");
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

}  // namespace uking::ai
