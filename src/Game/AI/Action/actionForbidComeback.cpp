#include "Game/AI/Action/actionForbidComeback.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForbidComeback::ForbidComeback(const InitArg& arg) : AreaTagAction(arg) {}

ForbidComeback::~ForbidComeback() = default;

bool ForbidComeback::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void ForbidComeback::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void ForbidComeback::leave_() {
    AreaTagAction::leave_();
}

void ForbidComeback::loadParams_() {}

void ForbidComeback::calc_() {
    AreaTagAction::calc_();
}

// NON_MATCHING: the original loads mActor before the forbidComebackMaybe() call
bool ForbidComeback::m15(const ksys::act::ActorConstDataAccess& accessor) {
    ksys::act::acc::PlayerBase player;
    player.acquireActor(accessor);
    if (!player.isPlayerProfile())
        return false;

    player.forbidComebackMaybe();
    mActor->m107();
    return true;
}

}  // namespace uking::action
