#include "Game/AI/AI/aiRailMove.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

RailMove::RailMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RailMove::~RailMove() = default;

bool RailMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710032BCAC(0.0f);
    m38();
}

// NON_MATCHING: the original keeps the direction in registers through normalize() and stores it
// once afterwards
void RailMove::calc_() {
    if (isFinished() || isFailed())
        return;

    if (!_40.sub_7100EEBB74()) {
        setFailed();
        return;
    }

    if (isCurrentChild("移動")) {
        m37();
        const sead::Vector3f cur_pos = _40._8.sub_7100EEB370();
        sead::Vector3f dir = cur_pos - _40._30.sub_7100EEB370();
        dir.normalize();
        const auto& target_pos = _40._30.sub_7100EEB370();
        getCurrentChild()->setDynamicParam(target_pos, "TargetPos");
        getCurrentChild()->setDynamicParam(target_pos, "DynTargetPos");
        getCurrentChild()->setDynamicParam(dir, "FrontDir");
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("停止")) {
            sub_710032C088();
        } else if (isCurrentChild("移動")) {
            if (s32(_40._30.progress) != s32(_40._8.progress) || _40.m3())
                m39();
            else
                sub_710032C0D4();
        } else if (isCurrentChild("停止点移動")) {
            m39();
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("移動")) {
            if (s32(_40._30.progress) == s32(_40._8.progress) && !_40.m3())
                return;
            if (sub_7100EEF078(_40._8.rail, _40._30.progress) > 0.0f)
                sub_710032C2B0();
        } else if (isCurrentChild("停止")) {
        }
    }
}

void RailMove::sub_710032BCAC(f32 progress) {
    _40.sub_7100EEBAE0(m36(), progress);
    _40.sub_7100EEBE9C(1);
}

void RailMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RailMove::loadParams_() {
    getStaticParam(&mIsIgnoreNoWaitStopPoint_s, "IsIgnoreNoWaitStopPoint");
}

void RailMove::sub_710032C088() {
    m37();
    sub_710032C56C();
}

// NON_MATCHING: the original keeps the direction in registers through normalize() and stores it
// once afterwards; regalloc
void RailMove::sub_710032C0D4() {
    const sead::Vector3f cur_pos = _40._8.sub_7100EEB370();
    sead::Vector3f dir = cur_pos - _40._30.sub_7100EEB370();
    dir.normalize();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(_40._30.sub_7100EEB370(), "TargetPos", -1);
    params.addVec3(_40._30.sub_7100EEB370(), "DynTargetPos", -1);
    params.addVec3(_40._8.sub_7100EEB370(), "DynStartPos", -1);
    params.addVec3(dir, "FrontDir", -1);
    changeChild("移動", &params);
}

// NON_MATCHING: the original keeps the direction in registers through normalize() and stores it
// once afterwards; regalloc
void RailMove::sub_710032C2B0() {
    sead::Vector3f start_pos;
    start_pos = _40._8.sub_7100EEB370();
    sead::Vector3f target_pos;
    if (auto* rail = _40._8.rail) {
        s32 idx;
        if (rail->isBezier()) {
            idx = _40._58 < 0 ? sead::Mathf::ceil(_40._30.progress) :
                                sead::Mathf::floor(_40._30.progress);
        } else {
            idx = _40._30.progress;
        }
        rail->calcTranslate(&target_pos, idx);
    } else {
        target_pos = _40._8.sub_7100EEB370();
    }

    const sead::Vector3f cur_pos = _40._8.sub_7100EEB370();
    sead::Vector3f dir = cur_pos - _40._30.sub_7100EEB370();
    dir.normalize();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(target_pos, "TargetPos", -1);
    params.addVec3(target_pos, "DynTargetPos", -1);
    params.addVec3(start_pos, "DynStartPos", -1);
    params.addVec3(dir, "FrontDir", -1);
    changeChild("停止点移動", &params);
}

void RailMove::sub_710032C56C() {
    if (sub_710032C5AC())
        sub_710032C0D4();
    else
        sub_710032C2B0();
}

bool RailMove::sub_710032C5AC() const {
    return _40._8.rail && _40._8.rail->isBezier();
}

void RailMove::sub_710032C5BC(sead::Vector3f* pos) const {
    *pos = _40._8.sub_7100EEB370();
}

void RailMove::m34() {}

ksys::map::Rail* RailMove::m36() {
    return sub_7100EEF264(mActor, 0);
}

void RailMove::m37() {
    if (!_40.sub_7100EEBB74())
        return;

    if (!_40.sub_7100EEBE88() && _40.m3() && m40())
        _40.sub_7100EEBE9C(-_40._58);

    if (sub_710032C5AC())
        _40.x(m35() * ksys::VFR::instance()->getDeltaFrame());
    else
        _40.x(-1.0f);
}

// NON_MATCHING: the original keeps the direction in registers through normalize() and stores it
// once afterwards; regalloc
void RailMove::sub_710032C5F8(f32 wait_frame) {
    sead::Vector3f stop_pos;
    if (auto* rail = _40._8.rail) {
        s32 idx;
        if (rail->isBezier()) {
            idx = _40._58 < 0 ? sead::Mathf::ceil(_40._30.progress) :
                                sead::Mathf::floor(_40._30.progress);
        } else {
            idx = _40._30.progress;
        }
        rail->calcTranslate(&stop_pos, idx);
    } else {
        stop_pos = _40._8.sub_7100EEB370();
    }

    const sead::Vector3f cur_pos = _40._8.sub_7100EEB370();
    sead::Vector3f dir = cur_pos - _40._30.sub_7100EEB370();
    dir.normalize();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(stop_pos, "DynStopPos", -1);
    params.addFloat(wait_frame, "DynStopTime", -1);
    params.addVec3(stop_pos, "TargetPos", -1);
    params.addVec3(dir, "FrontDir", -1);
    changeChild("停止", &params);
}

f32 RailMove::sub_710032C97C() const {
    return _40._30.progress;
}

bool RailMove::sub_710032C984(f32* progress, sead::Vector3f* pos,
                              const sead::Vector3f& target) const {
    auto* rail = _40._8.rail;
    if (!rail)
        return false;

    const f32 p = sub_7100EEF7AC(rail, target, false, 0.2f, -0.0f);
    if (progress)
        *progress = p;
    if (pos)
        rail->calcTranslate(pos, p);
    return true;
}

void RailMove::sub_710032CA64() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "DynStopPos", -1);
    params.addFloat(9999.0f, "DynStopTime", -1);
    changeChild("停止", &params);
    setFailed();
}

void RailMove::m38() {
    if (_40.sub_7100EEBB74())
        sub_710032C088();
    else
        sub_710032CA64();
}

void RailMove::m39() {
    const f32 wait_frame = sub_7100EEF078(_40._8.rail, sub_710032C97C());
    if (*mIsIgnoreNoWaitStopPoint_s && wait_frame <= 0.0f)
        sub_710032C088();
    else
        sub_710032C5F8(wait_frame);
}

bool RailMove::m40() {
    return true;
}

}  // namespace uking::ai
