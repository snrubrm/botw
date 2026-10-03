#include "Game/AI/AI/aiDragonRootBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

DragonRootBase::DragonRootBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DragonRootBase::~DragonRootBase() = default;

bool DragonRootBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DragonRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_7100EEF034(mActor, 0))
        sub_7100356764(m35(), 0.0f);
    m37();
}

void DragonRootBase::sub_7100356764(ksys::map::Rail* rail, f32 progress) {
    _38.sub_7100EEBAE0(rail ? rail : m35(), progress);
    _38.sub_7100EEBE9C(1);
}

bool DragonRootBase::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ksys::act::ai::ActionBase::reenter_(other, true))
        return false;
    auto* root = sead::DynamicCast<DragonRootBase>(other);
    if (!root)
        return false;
    _38.sub_7100EEBAE0(root->_38._8.rail, root->_38._30.progress);
    return true;
}

void DragonRootBase::calc_() {
    if (isFinished() || isFailed())
        return;

    if (!_38.sub_7100EEBB74()) {
        setFailed();
        return;
    }

    if (isCurrentChild("移動"))
        sub_7100356A7C();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("停止")) {
            sub_7100356CFC();
        } else if (isCurrentChild("移動")) {
            if (s32(_38._30.progress) != s32(_38._8.progress))
                m38();
            changeToMove();
        } else if (isCurrentChild("停止点移動")) {
            m38();
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("移動")) {
            if (s32(_38._30.progress) == s32(_38._8.progress))
                return;
            if (sub_7100EEF078(_38._8.rail, _38._30.progress) > 0.0f)
                sub_7100356F30();
        } else if (isCurrentChild("停止")) {
        }
    }
}

// NON_MATCHING: stack slots of the target vector and the core id / key temporaries swapped
void DragonRootBase::sub_7100356A7C() {
    const f32 speed = m34();
    if ((_38._30.sub_7100EEB370() - mActor->getMtx().getTranslation()).length() < speed)
        m36();

    sead::Vector3f dir = _38._30.sub_7100EEB370() - mActor->getMtx().getTranslation();
    dir.normalize();
    const sead::Vector3f target = mActor->getMtx().getTranslation() +
                                  dir * speed * ksys::VFR::instance()->getDeltaFrame();
    getCurrentChild()->setDynamicParam(target, "TargetPos");
    getCurrentChild()->setDynamicParam(target, "DynTargetPos");
    getCurrentChild()->setDynamicParam(-dir, "FrontDir");
}

void DragonRootBase::sub_7100356CFC() {
    m36();
    if (_38._8.rail && _38._8.rail->isBezier())
        changeToMove();
    else
        sub_7100356F30();
}

// NON_MATCHING: the original keeps the normalized direction in registers and stores it once
// afterwards (same as RailMove::sub_710032C0D4)
void DragonRootBase::changeToMove() {
    sead::Vector3f dir = mActor->getMtx().getTranslation() - _38._30.sub_7100EEB370();
    dir.normalize();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(_38._30.sub_7100EEB370(), "TargetPos", -1);
    params.addVec3(_38._30.sub_7100EEB370(), "DynTargetPos", -1);
    params.addVec3(mActor->getMtx().getTranslation(), "DynStartPos", -1);
    params.addVec3(dir, "FrontDir", -1);
    changeChild("移動", &params);
}

// NON_MATCHING: the original keeps the normalized direction in registers and stores it once
// afterwards (same as RailMove::sub_710032C0D4)
void DragonRootBase::sub_7100356F30() {
    sead::Vector3f start_pos;
    start_pos = _38._8.sub_7100EEB370();
    sead::Vector3f target_pos;
    if (auto* rail = _38._8.rail)
        rail->calcTranslate(&target_pos, s32(_38._30.progress));
    else
        target_pos = _38._8.sub_7100EEB370();

    sead::Vector3f dir = mActor->getMtx().getTranslation() - _38._30.sub_7100EEB370();
    dir.normalize();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(target_pos, "TargetPos", -1);
    params.addVec3(target_pos, "DynTargetPos", -1);
    params.addVec3(start_pos, "DynStartPos", -1);
    params.addVec3(dir, "FrontDir", -1);
    changeChild("停止点移動", &params);
}

void DragonRootBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DragonRootBase::loadParams_() {}

bool DragonRootBase::sub_7100357414(f32 progress) {
    if (!_38._8.rail)
        return false;
    _38.sub_7100EEBAE0(_38._8.rail, progress);
    return true;
}

// NON_MATCHING: the original keeps the normalized direction in registers and stores it once
// afterwards (same as RailMove::sub_710032C0D4)
void DragonRootBase::sub_7100357440(f32 wait_frame) {
    sead::Vector3f stop_pos;
    if (auto* rail = _38._8.rail)
        rail->calcTranslate(&stop_pos, s32(_38._30.progress));
    else
        stop_pos = _38._8.sub_7100EEB370();

    sead::Vector3f dir = mActor->getMtx().getTranslation() - _38._30.sub_7100EEB370();
    dir.normalize();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(stop_pos, "DynStopPos", -1);
    params.addFloat(wait_frame, "DynStopTime", -1);
    params.addVec3(stop_pos, "TargetPos", -1);
    params.addVec3(dir, "FrontDir", -1);
    changeChild("停止", &params);
}

ksys::map::Rail* DragonRootBase::m35() {
    return sub_7100EEF264(mActor, 0);
}

bool DragonRootBase::sub_710035797C(f32* out_progress, sead::Vector3f* out_pos,
                                    const sead::Vector3f& pos) {
    auto* rail = _38._8.rail;
    if (!rail)
        return false;
    const f32 progress = sub_7100EEF7AC(rail, pos, false, 0.2f, -0.0f);
    if (out_progress)
        *out_progress = progress;
    if (out_pos)
        rail->calcTranslate(out_pos, progress);
    return true;
}

void DragonRootBase::m37() {
    if (_38.sub_7100EEBB74()) {
        m36();
        if (_38._8.rail && _38._8.rail->isBezier())
            changeToMove();
        else
            sub_7100356F30();
    } else {
        sub_7100357A5C();
    }
}

void DragonRootBase::sub_7100357A5C() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "DynStopPos", -1);
    params.addFloat(9999.0f, "DynStopTime", -1);
    changeChild("停止", &params);
    setFailed();
}

void DragonRootBase::m38() {
    sub_7100357440(sub_7100EEF078(_38._8.rail, _38._30.progress));
}

bool DragonRootBase::m39() {
    return false;
}

}  // namespace uking::ai
