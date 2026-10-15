#include "Game/Actor/Action/actionForkASTrgTurnGround.h"
#include "Game/Actor/aiUnk_7102384718.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

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

}  // namespace uking::action
