#include "Game/AI/AI/aiKorokRailMove.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapRail.h"

namespace uking::ai {

KorokRailMove::KorokRailMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokRailMove::~KorokRailMove() = default;

bool KorokRailMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _58.sub_7100EEBAE0(m36(), 0.0f);
    _58.sub_7100EEBE9C(1);
    m39();
    _b8 = 0;
}

// NON_MATCHING: the original keeps the normalized direction in registers and stores it once
// afterwards (same as RailMove::calc_)
void KorokRailMove::calc_() {
    if (isFinished() || isFailed())
        return;

    if (!_58.sub_7100EEBB74()) {
        setFailed();
        return;
    }

    if (isCurrentChild("移動")) {
        m37();
        const sead::Vector3f cur_pos = _58._8.sub_7100EEB370();
        sead::Vector3f dir = cur_pos - _58._30.sub_7100EEB370();
        dir.normalize();
        const auto& target_pos = _58._30.sub_7100EEB370();
        getCurrentChild()->setDynamicParam(target_pos, "TargetPos");
        getCurrentChild()->setDynamicParam(target_pos, "DynTargetPos");
        getCurrentChild()->setDynamicParam(dir, "FrontDir");
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("停止")) {
            m37();
            if (sub_710045BD08())
                sub_710045B800();
            else
                sub_710045BA20();
            return;
        }
        if (isCurrentChild("移動")) {
            const s32 idx = _58._8.progress;
            if (_b8 != idx) {
                _b8 = idx;
                m40();
            } else {
                sub_710045B800();
            }
            return;
        }
        if (isCurrentChild("停止点移動"))
            m40();
    } else if (child->isChangeable()) {
        if (isCurrentChild("移動")) {
            if (s32(_58._30.progress) != s32(_58._8.progress) &&
                sub_7100EEF078(_58._8.rail, _58._30.progress) > 0.0f) {
                sub_710045BA20();
            }
        } else if (isCurrentChild("停止")) {
        }
    }

    child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("レールに向かう")) {
            if (getCurrentChild()->isFinished()) {
                m37();
                if (sub_710045BD08())
                    sub_710045B800();
                else
                    sub_710045BA20();
            } else {
                setFailed();
            }
        }
    }
}

void KorokRailMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokRailMove::loadParams_() {
    getStaticParam(&mOnRailDistance_s, "OnRailDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mIsIgnoreNoWaitStopPoint_s, "IsIgnoreNoWaitStopPoint");
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
}

void KorokRailMove::sub_710045B800() {
    const sead::Vector3f cur_pos = _58._8.sub_7100EEB370();
    sead::Vector3f dir = cur_pos - _58._30.sub_7100EEB370();
    dir.normalize();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(_58._30.sub_7100EEB370(), "TargetPos", -1);
    params.addVec3(_58._30.sub_7100EEB370(), "DynTargetPos", -1);
    params.addFloat(*mRailMoveSpeed_m, "Speed", -1);
    params.addFloat(*mRailMoveSpeed_m, "DynSpeed", -1);
    params.addBool(sub_710045BD08(), "IsBezier", -1);
    params.addBool(sub_710045BD08(), "DynIsBezier", -1);
    changeChild("移動", &params);
}

f32 KorokRailMove::sub_710045BA10() {
    return sub_7100EEF078(_58._8.rail, _58._30.progress);
}

void KorokRailMove::sub_710045BA20() {
    sead::Vector3f start_pos;
    start_pos = _58._8.sub_7100EEB370();
    sead::Vector3f target_pos;
    if (auto* rail = _58._8.rail)
        rail->calcTranslate(&target_pos, s32(_58._30.progress));
    else
        target_pos = _58._8.sub_7100EEB370();

    const sead::Vector3f cur_pos = _58._8.sub_7100EEB370();
    sead::Vector3f dir = cur_pos - _58._30.sub_7100EEB370();
    dir.normalize();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(target_pos, "TargetPos", -1);
    params.addVec3(target_pos, "DynTargetPos", -1);
    params.addFloat(*mRailMoveSpeed_m, "Speed", -1);
    params.addFloat(*mRailMoveSpeed_m, "DynSpeed", -1);
    params.addBool(sub_710045BD08(), "IsBezier", -1);
    params.addBool(sub_710045BD08(), "DynIsBezier", -1);
    changeChild("停止点移動", &params);
}

bool KorokRailMove::sub_710045BD08() {
    return _58._8.rail && _58._8.rail->isBezier();
}

// NON_MATCHING: placement of &_58._8 (computed in both branches in the original)
void KorokRailMove::sub_710045BD18(f32 wait_frame) {
    sead::Vector3f stop_pos;
    if (auto* rail = _58._8.rail)
        rail->calcTranslate(&stop_pos, s32(_58._30.progress));
    else
        stop_pos = _58._8.sub_7100EEB370();

    const sead::Vector3f cur_pos = _58._8.sub_7100EEB370();
    sead::Vector3f dir = cur_pos - _58._30.sub_7100EEB370();
    dir.normalize();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(stop_pos, "DynStopPos", -1);
    params.addFloat(wait_frame, "DynStopTime", -1);
    changeChild("停止", &params);
}

void KorokRailMove::sub_710045BEB4(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    params.addVec3(pos, "DynTargetPos", -1);
    params.addFloat(*mRailMoveSpeed_m, "Speed", -1);
    params.addFloat(*mRailMoveSpeed_m, "DynSpeed", -1);
    params.addBool(sub_710045BD08(), "IsBezier", -1);
    params.addBool(sub_710045BD08(), "DynIsBezier", -1);
    changeChild("レールに向かう", &params);
}

void KorokRailMove::m34() {}

ksys::map::Rail* KorokRailMove::m36() {
    return sub_7100EEF264(mActor, 0);
}

void KorokRailMove::m37() {
    if (!_58.sub_7100EEBB74())
        return;

    if (!_58.sub_7100EEBE88() && _58.m3() && m41())
        _58.sub_7100EEBE9C(-_58._58);

    if (sub_710045BD08()) {
        const f32 speed = m35();
        sead::Vector3f diff = sead::Vector3f::zero;
        sead::Vector3f target = _58._30.sub_7100EEB370();
        m38(&diff, &target);
        if (diff.length() < speed)
            _58.x(speed - diff.length());
    } else {
        _58.x(-1.0f);
    }
}

// NON_MATCHING: placement of &_58 (the original computes it in both branches)
void KorokRailMove::m39() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f rail_pos;
    if (auto* rail = _58._8.rail) {
        const f32 progress = sub_7100EEF7AC(rail, pos, false, 0.2f, -0.0f);
        rail->calcTranslate(&rail_pos, progress);
        _58.sub_7100EEBAE0(m36(), progress);
        _58.sub_7100EEBE9C(1);
    }

    if (!_58.sub_7100EEBB74()) {
        sub_710045C3A8();
    } else if ((rail_pos - pos).length() > *mOnRailDistance_s) {
        sub_710045BEB4(rail_pos);
    } else {
        m37();
        if (sub_710045BD08())
            sub_710045B800();
        else
            sub_710045BA20();
    }
}

void KorokRailMove::sub_710045C3A8() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "DynStopPos", -1);
    params.addFloat(9999.0f, "DynStopTime", -1);
    changeChild("停止", &params);
    setFailed();
}

void KorokRailMove::m40() {
    const f32 wait_frame = sub_7100EEF078(_58._8.rail, _58._30.progress);
    if (*mIsIgnoreNoWaitStopPoint_s && wait_frame <= 0.0f) {
        m37();
        if (sub_710045BD08())
            sub_710045B800();
        else
            sub_710045BA20();
    } else {
        sub_710045BD18(wait_frame);
    }
}

// NON_MATCHING: regalloc (s1 vs s2 for the second 1.0f)
f32 KorokRailMove::m35() {
    const sead::Vector3f rail_pos = _58._8.sub_7100EEB370();
    const f32 dist = (mActor->getMtx().getTranslation() - rail_pos).length();
    const f32 t = sead::Mathf::clamp((dist - *mOnRailDistance_s) / (*mFarDistance_s - *mOnRailDistance_s),
                                     0.0f, 1.0f);
    return (1.0f - t) * *mRailMoveSpeed_m;
}

bool KorokRailMove::m41() {
    return true;
}

}  // namespace uking::ai
