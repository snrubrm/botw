#include "Game/Actor/Action/actionForkASTrgTurnGround.h"
#include "Game/Actor/aiUnk_7102384718.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
#include <math/seadBoundBox.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ForkASTrgTurnGround::ForkASTrgTurnGround(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgTurnGround::~ForkASTrgTurnGround() = default;

bool ForkASTrgTurnGround::init_(sead::Heap* heap) {
    _58.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    setupCRBOffsetUnit(_58);
    return true;
}

void ForkASTrgTurnGround::enter_(ksys::act::ai::InlineParamPack* params) {
    _60.makeRT(*mCtrlAngleOffset_s, *mCtrlOffset_s);
    _94 = false;
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_58._0))
        unit->_8.sub_attach(mActor);
    if (auto* controller = mActor->getCharacterController())
        _98 = controller->get110();
}

void ForkASTrgTurnGround::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->mFlags.reset(2);
        controller->sub_7100F5EEB8(_98);
    }
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_58._0))
        unit->_8.sub_detach(mActor);
}

void ForkASTrgTurnGround::loadParams_() {
    getStaticParam(&mSpeedBasePosRatio_s, "SpeedBasePosRatio");
    getStaticParam(&mOnAfterGroundRotAngle_s, "OnAfterGroundRotAngle");
    getStaticParam(&mAxis_s, "Axis");
    getStaticParam(&mCtrlOffset_s, "CtrlOffset");
    getStaticParam(&mCtrlAngleOffset_s, "CtrlAngleOffset");
    getStaticParam(&mActMoveVec_s, "ActMoveVec");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

// NON_MATCHING: vector rotation and scaling stores are scheduled differently.
void ForkASTrgTurnGround::calc_() {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    if (!as_list)
        return;
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(actor, 41, &query, 0, 0)) {
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F5EEB8(0.0f);
        mFlags.reset(Flag::Changeable);
        sub_7100145FCC(query._10);
        _94 = true;
    } else if (as_list->x(41, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        mFlags.reset(Flag::Changeable);
        sub_7100146268();
    } else {
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F5EEB8(_98);
        mFlags.set(Flag::Changeable);
        if (_94) {
            auto* controller = mActor->getCharacterController();
            if (!controller)
                return;
            if (!controller->sub_7100F63370()) {
                sead::Vector3f velocity;
                velocity.setRotated(mActor->getMtx(), *mAxis_s);
                velocity *= *mOnAfterGroundRotAngle_s;
                ksys::act::sub_7100EE5A14(mActor, velocity);
                return;
            }
        }
        sub_7100738AA8(actor, 0.99f);
    }
}

void ForkASTrgTurnGround::sub_7100146268() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    sead::Matrix34f transform = mActor->getMtx();
    transform.setTranslation(transform.getTranslation() +
                             _9c * ksys::VFR::instance()->getDeltaFrame());
    mActor->setMtx(transform, false, false);
    if (controller->sub_7100F63370()) {
        controller->sub_7100F5EEB8(_98);
        sub_7100738AA8(mActor, 0.01f);
        _9c = sead::Vector3f::zero;
    }
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_58._0)) {
        sub_71007448C0(&unit->_8.mHandle, _60,
                       _90 > 0.0f ? 1.0f / sead::Mathf::clampMin(_90, 1.0f) : 0.5f);
    }
}

// NON_MATCHING: rotated-axis component loads and scalar multiplication scheduling differ.
void ForkASTrgTurnGround::sub_7100145FCC(f32 frames) {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    controller->mFlags.set(2);
    controller->_240 = *mAxis_s;
    sead::BoundBox3f bounds;
    controller->sub_7100F61A34()->getAabbInLocal(&bounds);
    const f32 radius = bounds.getMax().y * *mSpeedBasePosRatio_s;
    sead::Vector3f axis;
    axis.setRotated(mActor->getMtx(), *mAxis_s);
    const sead::Vector3f actor_position = mActor->getMtx().getTranslation();
    sead::Vector3f position{actor_position.x - radius * axis.z,
                          actor_position.y + radius * axis.y,
                          actor_position.z + radius * axis.x};
    f32 angle = sead::Mathf::piHalf();
    if (somePositionCalc(&position, position, -sead::Vector3f::ey, 10.0f)) {
        position -= actor_position;
        angle -= std::atan2(position.y, radius);
    }
    axis.setRotated(mActor->getMtx(), *mAxis_s);
    ksys::act::sub_7100EE5A14(mActor, axis * (angle / frames));
    _90 = frames;
    _9c = *mActMoveVec_s * (1.0f / frames);
}

}  // namespace uking::action
