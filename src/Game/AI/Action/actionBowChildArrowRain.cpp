#include "Game/AI/Action/actionBowChildArrowRain.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

namespace {
struct Unk_8000054_Payload {
    u8 _0[0x20];
    s32 _20;
};
}  // namespace

// NON_MATCHING: the original emits the zero stores of _d4/_100/_108/_110 before both memsets (0x20..0xd3 and
// the 0x408-byte block at 0x12c); here they end up between / after the memsets.
BowChildArrowRain::BowChildArrowRain(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildArrowRain::~BowChildArrowRain() = default;

bool BowChildArrowRain::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildArrowRain::enter_(ksys::act::ai::InlineParamPack* params) {
    _b8 = 0;
    _bc = 0;
    const s32 id = *mID_d;
    _110 = 0;
    _100 = 0;
    _108 = 0;
    _c0 = f32(id) * (sead::Mathf::pi() / 2);
    for (auto& v : _12c._3d8)
        v = {0, 0};
    _12c._3cc.set(*mToTargetTime_s, *mToTargetTime_s, -1);
    _d0 = false;
    _d1 = false;
    _d2 = false;
    _d8 = *mID_d;
    _c8 = sead::GlobalRandom::instance()->getF32();
    _cc = sead::GlobalRandom::instance()->getF32Range(-5, 5);
}

void BowChildArrowRain::leave_() {
    ksys::act::ai::Action::leave_();
}

void BowChildArrowRain::loadParams_() {
    getStaticParam(&mRainMax_s, "RainMax");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mMoveHeight_s, "MoveHeight");
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mMoveCountNum_s, "MoveCountNum");
    getStaticParam(&mMoveRange_s, "MoveRange");
    getStaticParam(&mMoveOffsetBase_s, "MoveOffsetBase");
    getStaticParam(&mRotateRate_s, "RotateRate");
    getStaticParam(&mRotateStepMax_s, "RotateStepMax");
    getStaticParam(&mAngleToTarget_s, "AngleToTarget");
    getStaticParam(&mTargetOffsetBase_s, "TargetOffsetBase");
    getStaticParam(&mRainScale_s, "RainScale");
    getStaticParam(&mToTargetTime_s, "ToTargetTime");
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mXRotateAngle_d, "XRotateAngle");
    getDynamicParam(&mIsIgnoreHightOffset_d, "IsIgnoreHightOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveTargetPos_d, "MoveTargetPos");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

bool BowChildArrowRain::handleMessage_(const ksys::Message* message) {
    if (!message || message->getBrokerId() != u32(-1))
        return false;
    if (message->getType() != 0x8000054)
        return false;
    if (!message->getUserData())
        return true;

    const auto* data = static_cast<const Unk_8000054_Payload*>(message->getUserData());
    if (!data)
        return true;

    if (data->_20 == 1) {
        _d1 = true;
        return true;
    }

    _b8 = 1;
    _12c._3c0.set(45.0f, 45.0f, -1.0f);
    playAS("Open", false, 0, 0, -1.0f);
    return true;
}

bool BowChildArrowRain::isChangeable() const {
    return _b8 != 1 && _b8 != 2;
}

void BowChildArrowRain::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
