#include "Game/AI/Action/actionFreeMoveRandom.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

FreeMoveRandom::FreeMoveRandom(const InitArg& arg) : FreeMove(arg) {}

FreeMoveRandom::~FreeMoveRandom() = default;

bool FreeMoveRandom::init_(sead::Heap* heap) {
    return FreeMove::init_(heap);
}

void FreeMoveRandom::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMove::enter_(params);
    mFlags.set(Flag::Changeable);
}

void FreeMoveRandom::leave_() {
    FreeMove::leave_();
}

void FreeMoveRandom::loadParams_() {
    FreeMove::loadParams_();
    getStaticParam(&mRandVertical_s, "RandVertical");
    getStaticParam(&mRandHorizontal_s, "RandHorizontal");
    getStaticParam(&mRandSpeedMax_s, "RandSpeedMax");
    getStaticParam(&mRandSpeedMin_s, "RandSpeedMin");
    getStaticParam(&mTargetDistance_s, "TargetDistance");
    getStaticParam(&mHeightMax_s, "HeightMax");
    getStaticParam(&mHeightMin_s, "HeightMin");
    getStaticParam(&mMoveAreaRadius_s, "MoveAreaRadius");
}

void FreeMoveRandom::calc_() {
    FreeMove::calc_();
}

bool FreeMoveRandom::m34() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f target = _1c;
    _10c.update();
    if (_10c.value <= sead::Mathf::epsilon()) {
        sead::Vector3f hit_pos;
        const sead::Vector3f start = pos + sead::Vector3f(0, 3, 0);
        somePositionCalc(&hit_pos, start, -sead::Vector3f::ey, 10.0f);
        const f32 height = pos.y - hit_pos.y;
        if (height >= *mHeightMax_s - 0.2f)
            return true;
        if (height <= *mHeightMin_s + 0.2f)
            return true;
        _10c = ksys::Timer(6.0f, 6.0f);
    }
    return (pos - target).length() > _108;
}

}  // namespace uking::action
