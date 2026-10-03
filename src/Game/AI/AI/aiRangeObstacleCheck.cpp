#include "Game/AI/AI/aiRangeObstacleCheck.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

RangeObstacleCheck::RangeObstacleCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RangeObstacleCheck::~RangeObstacleCheck() = default;

bool RangeObstacleCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RangeObstacleCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* actor = mActor) {
        if (!inlineIsTargetInReach(*mTargetPos_d,
                                   *mRangeDist_s + sub_71007320F0(actor, *mWeaponIdx_s),
                                   *mHeightMin_s, *mHeightMax_s, actor->getMtx(),
                                   sead::Mathf::pi(), sead::Mathf::maxNumber(), 0.8f)) {
            _64 = 10;
            _68 = 15;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("レンジ外", &pack);
            return;
        }
    }
    _64 = 10;
    _68 = 15;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("レンジ内", &pack);
}

// NON_MATCHING: regalloc only (the original computes `this + 0x60` once before the branch and keeps it in x20)
void RangeObstacleCheck::calc_() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (!getCurrentChild()->isChangeable())
        return;
    const bool is_out = isCurrentChild("レンジ外");
    bool out_of_range = false;
    if (auto* actor = mActor) {
        out_of_range = !inlineIsTargetInReach(
            *mTargetPos_d, *mRangeDist_s + sub_71007320F0(actor, *mWeaponIdx_s), *mHeightMin_s,
            *mHeightMax_s, actor->getMtx(), sead::Mathf::pi(), sead::Mathf::maxNumber(), 0.8f);
    }
    if (is_out) {
        if (out_of_range)
            _60 = _64 == _68 ? _64 : sead::GlobalRandom::instance()->getS32Range(_64, _68);
        else
            ksys::Timer::update(&_60, -1.0f);
        if (_60 <= 0.0f) {
            _64 = 10;
            _68 = 15;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("レンジ内", &pack);
        }
    } else {
        if (out_of_range)
            ksys::Timer::update(&_60, -1.0f);
        else
            _60 = _64 == _68 ? _64 : sead::GlobalRandom::instance()->getS32Range(_64, _68);
        if (_60 <= 0.0f) {
            _64 = 10;
            _68 = 15;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("レンジ外", &pack);
        }
    }
}

void RangeObstacleCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RangeObstacleCheck::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRangeDist_s, "RangeDist");
    getStaticParam(&mHeightMin_s, "HeightMin");
    getStaticParam(&mHeightMax_s, "HeightMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool RangeObstacleCheck::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool RangeObstacleCheck::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

}  // namespace uking::ai
