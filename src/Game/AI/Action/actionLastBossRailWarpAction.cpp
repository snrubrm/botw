#include "Game/AI/Action/actionLastBossRailWarpAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

LastBossRailWarpAction::LastBossRailWarpAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossRailWarpAction::~LastBossRailWarpAction() = default;

bool LastBossRailWarpAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossRailWarpAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossRailWarpAction::leave_() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    controller->sub_7100F60604();
    controller->sub_7100F5E764(true);
    controller->sub_7100F62CA8(true);
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FBAD74();
    if (auto* body = controller->sub_7100F61A34()) {
        if (auto* physics = mActor->getPhysics())
            body->setContactLayerAndHandler(ksys::phys::ContactLayer::EntityHitOnlyGround,
                                            physics->get188(0));
    }
}

void LastBossRailWarpAction::loadParams_() {
    getStaticParam(&mWarpTime_s, "WarpTime");
    getStaticParam(&mYOffset_s, "YOffset");
    getStaticParam(&mIsUpdateHomePos_s, "IsUpdateHomePos");
    getStaticParam(&mIsTurnToPlayer_s, "IsTurnToPlayer");
    getDynamicParam(&mRailIndex_d, "RailIndex");
    getDynamicParam(&mIsPartsActorTgOn_d, "IsPartsActorTgOn");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LastBossRailWarpAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
