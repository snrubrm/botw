#include "Game/AI/Action/actionForkASTrgTurnGround.h"
#include "Game/AI/aiUnk_7102384718.h"
#include "KingSystem/ActorSystem/actActor.h"
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
    ksys::act::ai::Action::enter_(params);
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

void ForkASTrgTurnGround::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
