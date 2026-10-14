#include "Game/Actor/Action/actionForbidComeback.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForbidComeback::ForbidComeback(const InitArg& arg) : AreaActionBase(arg) {}

ForbidComeback::~ForbidComeback() = default;

bool ForbidComeback::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void ForbidComeback::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void ForbidComeback::leave_() {
    AreaActionBase::leave_();
}

void ForbidComeback::loadParams_() {}

void ForbidComeback::calc_() {
    AreaActionBase::calc_();
}

// NON_MATCHING: the original loads mActor before the forbidComebackMaybe() call
bool ForbidComeback::m15(const ksys::act::ActorLinkConstDataAccess& accessor) {
    ksys::act::acc::PlayerBase player;
    player.acquireActor(accessor);
    if (!player.isPlayerProfile())
        return false;

    player.forbidComebackMaybe();
    mActor->m107();
    return true;
}

}  // namespace uking::action
