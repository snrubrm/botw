#include "Game/AI/Action/actionPriestBossAimBeam.h"
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::action {

PriestBossAimBeam::PriestBossAimBeam(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PriestBossAimBeam::~PriestBossAimBeam() = default;

bool PriestBossAimBeam::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PriestBossAimBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    m32("");
    _188 = false;
}

void PriestBossAimBeam::leave_() {
    m34();
}

void PriestBossAimBeam::loadParams_() {
    getStaticParam(&mAimLockFrame_s, "AimLockFrame");
    getStaticParam(&mTargetOffset_s, "TargetOffset");
    getStaticParam(&mTargetOffsetY_s, "TargetOffsetY");
    getStaticParam(&mFluctuationRange_s, "FluctuationRange");
    getStaticParam(&mFluctuationTime_s, "FluctuationTime");
    getStaticParam(&mFluctuationSpan_s, "FluctuationSpan");
    getStaticParam(&mAimMaxLength_s, "AimMaxLength");
    getStaticParam(&mAimOffToTarget_s, "AimOffToTarget");
    getStaticParam(&mNodeName_s, "NodeName");
    getStaticParam(&mNodeOffset_s, "NodeOffset");
    getDynamicParam(&mAimTargetPos_d, "AimTargetPos");
}

void PriestBossAimBeam::calc_() {
    if (_80._f4 <= _80._d8) {
        _80.end("Target_End");
        setFinished();
        return;
    }
    m35();
}

void PriestBossAimBeam::m32(const char* name) {
    _80.init(mActor, "Target", "Laser", name, "BeamSightSearch", "BeamSightLocking",
             "BeamSightLocked", *mFluctuationRange_s, *mFluctuationSpan_s, *mFluctuationTime_s,
             *mTargetOffsetY_s, *mAimTargetPos_d, mNodeName_s, *mNodeOffset_s);
    _80._f4 = *mAimLockFrame_s;
    _178 = true;
}

void PriestBossAimBeam::m33(const sead::Vector3f& target_pos) {
    if (_178)
        _80.update(target_pos);
}

void PriestBossAimBeam::m34() {
    if (_178) {
        _80.sub_71006F2D08();
        _178 = false;
    }
}

// NON_MATCHING: the original keeps the head matrix in registers across the sqrtf call (as if it
// were a non-escaping copy) and reuses its stack slot for the second matrix
void PriestBossAimBeam::m35() {
    sead::Matrix34f head_mtx = sead::Matrix34f::ident;
    mActor->sub_71011D57F8(&head_mtx, "Head");
    sead::Vector3f head_pos;
    head_mtx.getTranslation(head_pos);

    sead::Matrix34f inv_mtx;
    inv_mtx.setInverse(head_mtx);
    sead::Vector3f dir;
    dir.setMul(inv_mtx, *mAimTargetPos_d);
    dir.normalize();

    sead::Vector3f end;
    end.setMul(head_mtx, dir * *mAimMaxLength_s);

    sead::Vector3f target;
    if (!m36(head_pos, end, &target))
        target = end;

    if (*mAimOffToTarget_s) {
        if ((target - getPlayerPosition()).length() < 5.0f) {
            _188 = true;
        } else if (!_188) {
            sead::Vector3f pos = sead::Vector3f::zero;
            sead::Matrix34f mtx = sead::Matrix34f::ident;
            if (mActor->sub_71011D57F8(&mtx, "Head"))
                mtx.getTranslation(pos);
            target = pos;
        }
    }

    m33(target);
}

bool PriestBossAimBeam::m36(const sead::Vector3f& start, const sead::Vector3f& end,
                            sead::Vector3f* hit_pos) {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityPlayer);
    query.enableLayer(ksys::phys::ContactLayer::EntitySmallObject);
    query.setStartAndEnd(start, end);
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;
    if (hit_pos)
        query.getHitPosition(hit_pos);
    return true;
}

}  // namespace uking::action
