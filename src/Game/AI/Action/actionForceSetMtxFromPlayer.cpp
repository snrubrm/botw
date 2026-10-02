#include "Game/AI/Action/actionForceSetMtxFromPlayer.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForceSetMtxFromPlayer::ForceSetMtxFromPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceSetMtxFromPlayer::~ForceSetMtxFromPlayer() = default;

bool ForceSetMtxFromPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceSetMtxFromPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForceSetMtxFromPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceSetMtxFromPlayer::loadParams_() {}

// NON_MATCHING: regalloc (the original rematerialises the accessor address for the destructor)
void ForceSetMtxFromPlayer::calc_() {
    auto* info = ksys::act::PlayerInfo::instance();
    if (!info)
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&info->getPlayerLink(), &accessor);
    if (!accessor.hasProc())
        return;
    sead::Matrix34f mtx = accessor.getActorMtx();
    mActor->setMtx(mtx, false, true);
}

}  // namespace uking::action
