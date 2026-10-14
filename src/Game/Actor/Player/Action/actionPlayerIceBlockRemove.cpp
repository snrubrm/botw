#include "Game/Actor/Player/Action/actionPlayerIceBlockRemove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"

namespace uking::action {

PlayerIceBlockRemove::PlayerIceBlockRemove(const InitArg& arg) : PlayerAction(arg) {}

PlayerIceBlockRemove::~PlayerIceBlockRemove() = default;

void PlayerIceBlockRemove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20);

    ksys::act::BaseProcMgr::ProcIteratorContext context(
        *ksys::act::BaseProcMgr::instance(),
        ksys::act::BaseProcMgr::ProcFilter::Sleeping |
            ksys::act::BaseProcMgr::ProcFilter::DeletedOrDeleting |
            ksys::act::BaseProcMgr::ProcFilter::Initializing |
            ksys::act::BaseProcMgr::ProcFilter::SkipAccessCheck);
    while (auto* proc = context.next()) {
        if (!sead::DynamicCast<ksys::act::Actor>(proc))
            continue;
        if (proc->getName() == "IceBlock") {
            ksys::act::BaseProcLink link;
            link.acquire(proc, false);
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
    }
}

void PlayerIceBlockRemove::leave_() {}

void PlayerIceBlockRemove::calc_() {
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    setFinished();
}

bool PlayerIceBlockRemove::isChangeable() const {
    return false;
}

}  // namespace uking::action
