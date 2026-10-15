#include "Game/Actor/Action/actionDungeonRotate2Target.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

DungeonRotate2Target::DungeonRotate2Target(const InitArg& arg) : DungeonRotateBase(arg) {}

DungeonRotate2Target::~DungeonRotate2Target() = default;

bool DungeonRotate2Target::init_(sead::Heap* heap) {
    if (!DungeonRotateBase::init_(heap))
        return false;
    *mTargetRad_a = 0.0f;
    *mTargetRadMax_a = 0.0f;
    *mTargetRadMin_a = 0.0f;
    return true;
}

void DungeonRotate2Target::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
    const f32 rad = *mDgnRotDir_s == 0 ? -*mTargetRad_a : *mTargetRad_a;
    _110 = rad;
    _114 = rad;
    m34(*mRotSpAccel_s);
    _118 = _80;
    mFlags.set(Flag::Changeable);
}

void DungeonRotate2Target::leave_() {
    DungeonRotateBase::leave_();
}

void DungeonRotate2Target::loadParams_() {
    DungeonRotateBase::loadParams_();
    getStaticParam(&mDgnRotDir_s, "DgnRotDir");
    getStaticParam(&mRotSpAccel_s, "RotSpAccel");
    getStaticParam(&mRotSpSlowDown_s, "RotSpSlowDown");
    getStaticParam(&mRotSpSlowDownTh_s, "RotSpSlowDownTh");
    getStaticParam(&mMinRotSp_s, "MinRotSp");
    getStaticParam(&mRotReverseSlowDown_s, "RotReverseSlowDown");
    getAITreeVariable(&mTargetRad_a, "TargetRad");
    getAITreeVariable(&mTargetRadMax_a, "TargetRadMax");
    getAITreeVariable(&mTargetRadMin_a, "TargetRadMin");
}

// NON_MATCHING: target-crossing branch layout and operand scheduling.
void DungeonRotate2Target::calc_() {
    DungeonRotateBase::calc_();
    _110 = *mDgnRotDir_s == 0 ? -*mTargetRad_a : *mTargetRad_a;
    if (!sead::Mathf::equalsEpsilon(_114, _110))
        _118 = _80;
    _114 = _110;
    m35();
    ksys::VFR::add(&_80, _84);
    bool finished = false;
    if (_110 > _118) {
        if (_110 <= _80)
            finished = true;
    } else if (_110 >= _80 && _110 < _118) {
        finished = true;
    }
    if (finished) {
        _80 = _110;
        _84 = 0.0f;
    }
    if (*mDgnRotDir_s != 0) {
        if (_80 <= *mTargetRadMin_a) {
            _80 = *mTargetRadMin_a;
            _84 = 0.0f;
        } else if (_80 >= *mTargetRadMax_a) {
            _80 = *mTargetRadMax_a;
            _84 = 0.0f;
        }
    } else {
        if (_80 >= *mTargetRadMin_a) {
            _80 = *mTargetRadMin_a;
            _84 = 0.0f;
        } else if (_80 <= -*mTargetRadMax_a) {
            _80 = -*mTargetRadMax_a;
            _84 = 0.0f;
        }
    }
    if (_90) {
        ui::sub_7100A9D244(_80);
        sead::Vector3f rotation = _70 * _80;
        sub_71000FCCA4(&rotation, _110 < _80);
    }
    if (finished) {
        sub_71000FD51C();
        setFinished();
    }
}

void DungeonRotate2Target::m33() {
    _84 = 0;
}

void DungeonRotate2Target::m35() {
    f32 speed = _88;
    f32 min_speed = *mMinRotSp_s;
    if (mActor->checkVelocityControlSignal())
        speed *= *mVelocityControlRate_m;
    if (_110 - _118 < 0.0f) {
        speed = -speed;
        min_speed = -min_speed;
    }
    if (sead::Mathf::abs(_110 - _80) <= *mRotSpSlowDownTh_s) {
        m34(*mRotSpSlowDown_s);
        ksys::VFR::chase(&_84, min_speed, _8c);
    } else {
        m34(*mRotSpAccel_s);
        ksys::VFR::chase(&_84, speed, _8c);
    }
}

}  // namespace uking::action
