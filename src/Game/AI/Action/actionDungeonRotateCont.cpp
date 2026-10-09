#include "Game/AI/Action/actionDungeonRotateCont.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

DungeonRotateCont::DungeonRotateCont(const InitArg& arg) : DungeonRotateBase(arg) {}

DungeonRotateCont::~DungeonRotateCont() = default;

bool DungeonRotateCont::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DungeonRotateCont::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
    const f32 angle = sead::Mathf::deg2rad(*mTiltAngle_m);
    _e0 = _80 + (*mDgnRotDir_m == 0 ? -angle : angle);
}

void DungeonRotateCont::leave_() {
    DungeonRotateBase::leave_();
}

void DungeonRotateCont::loadParams_() {
    DungeonRotateBase::loadParams_();
    getMapUnitParam(&mDgnRotDir_m, "DgnRotDir");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
    getAITreeVariable(&mIsContinueRotateOrMove_a, "IsContinueRotateOrMove");
}

// NON_MATCHING: arrival branch lowering and scalar scheduling differ.
void DungeonRotateCont::calc_() {
    DungeonRotateBase::calc_();
    m35();
    const f32 angle = sead::Mathf::deg2rad(*mTiltAngle_m);
    const f32 step = _84 * ksys::VFR::instance()->getDeltaFrame();
    const f32 current = _80;
    const f32 target = _e0;
    const bool forward = *mDgnRotDir_m != 0;
    bool reached;
    if (forward) {
        const f32 magnitude = step > 0.0f ? step : -step;
        if (current < target) {
            const f32 candidate = current + magnitude;
            reached = candidate < current || candidate >= target;
        } else if (current > target) {
            const f32 candidate = current - magnitude;
            reached = current < candidate || candidate <= target;
        } else {
            reached = true;
        }
        _80 = current + step;
    } else {
        if (current < target) {
            const f32 candidate = current + step;
            reached = candidate < current || candidate >= target;
        } else if (current > target) {
            const f32 candidate = current - step;
            reached = current < candidate || candidate <= target;
        } else {
            reached = true;
        }
        _80 = current - step;
    }
    if (reached) {
        if (*mIsContinueRotateOrMove_a) {
            _e0 = forward ? target + angle : target - angle;
            if (_80 > sead::Mathf::pi() || _80 < -sead::Mathf::pi()) {
                _80 = ksys::util::sub_71011EF0CC(_80);
                _e0 = ksys::util::sub_71011EF0CC(_e0);
            }
        } else {
            _80 = target;
            sub_71000FD51C();
            setFinished();
        }
    }
    if (_90) {
        const auto rotation = _70 * _80;
        sub_71000FCCA4(&rotation, _e0 < _80);
    }
}

}  // namespace uking::action
