#include "Game/AI/Action/actionSetComebackPosition.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetComebackPosition::SetComebackPosition(const InitArg& arg) : AreaTagAction(arg) {}

SetComebackPosition::~SetComebackPosition() = default;

bool SetComebackPosition::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void SetComebackPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void SetComebackPosition::leave_() {
    AreaTagAction::leave_();
}

void SetComebackPosition::loadParams_() {
    getMapUnitParam(&mAngleY_m, "AngleY");
}

void SetComebackPosition::calc_() {
    AreaTagAction::calc_();
}

bool SetComebackPosition::m15(const ksys::act::ActorConstDataAccess& accessor) {
    if (!accessor.isPlayerProfile())
        return false;

    ksys::act::acc::PlayerBase player;
    player.acquireActor(accessor);
    auto* actor = mActor;
    sead::Vector3f pos;
    actor->getHomePos(&pos);
    player.setRestartBuf(pos, *mAngleY_m);
    actor->m107();
    return true;
}

}  // namespace uking::action
