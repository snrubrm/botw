#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace ksys::act {

// NON_MATCHING: most member types are still unknown (placeholders)
PlayerBase::~PlayerBase() = default;

sead::Vector3f& PlayerBase::getPlayerPosForPostCalc() {
    return PlayerInfo::instance()->getPlayerPosForPostCalc();
}

PlayerBase* PlayerBase::getPlayer() {
    BaseProcMgr::instance()->isAccessingProcSafe(this, nullptr);
    return this;
}

bool PlayerBase::getActorViaAccessor(ActorLinkConstDataAccess* accessor) {
    return accessor->acquire(this);
}

}  // namespace ksys::act
