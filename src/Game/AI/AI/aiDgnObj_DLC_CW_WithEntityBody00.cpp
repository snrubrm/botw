#include "Game/AI/AI/aiDgnObj_DLC_CW_WithEntityBody00.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physFixedCs.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

DgnObj_DLC_CW_WithEntityBody00::DgnObj_DLC_CW_WithEntityBody00(const InitArg& arg)
    : DgnObj_DLC_CogWheel2(arg) {}

DgnObj_DLC_CW_WithEntityBody00::~DgnObj_DLC_CW_WithEntityBody00() {
    if (_a0) {
        ksys::phys::Constraint::destroy(_a0);
        _a0 = nullptr;
    }
}

bool DgnObj_DLC_CW_WithEntityBody00::init_(sead::Heap* heap) {
    if (!DgnObj_DLC_CogWheel2::init_(heap))
        return false;
    auto* actor = mActor;
    if (!actor)
        return true;
    auto* body = actor->findPhysicsBodyByName("BodyParts_00", "RigidBody_0");
    if (!body)
        return true;
    auto* main_body = actor->getMainBody();
    if (!main_body)
        return true;
    ksys::phys::FixedCs::Param param;
    param.body_a = main_body;
    param.body_b = body;
    _a0 = ksys::phys::FixedCs::make(param, heap);
    return true;
}

void DgnObj_DLC_CW_WithEntityBody00::enter_(ksys::act::ai::InlineParamPack* params) {
    DgnObj_DLC_CogWheel2::enter_(params);
    if (mActor) {
        if (auto* body = mActor->findPhysicsBodyByName("BodyParts_00", "RigidBody_0"))
            body->addToWorld();
    }
    if (auto* fixed = sead::DynamicCast<ksys::phys::FixedCs>(_a0)) {
        sead::Matrix34f mtx;
        mtx.makeIdentity();
        fixed->sub_7100F6D6D8(mtx, mtx);
        fixed->sub_7100F69FF0();
    }
}

void DgnObj_DLC_CW_WithEntityBody00::calc_() {
    DgnObj_DLC_CogWheel2::calc_();
}

void DgnObj_DLC_CW_WithEntityBody00::leave_() {
    DgnObj_DLC_CogWheel2::leave_();
    if (_a0 && (_a0->_50 & 1))
        _a0->sub_7100F6A074();
    if (mActor) {
        if (auto* body = mActor->findPhysicsBodyByName("BodyParts_00", "RigidBody_0"))
            body->removeFromWorld();
    }
}

void DgnObj_DLC_CW_WithEntityBody00::loadParams_() {
    DgnObj_DLC_CogWheel2::loadParams_();
}

}  // namespace uking::ai
