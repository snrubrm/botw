#include "Game/AI/Action/actionCollaboShootingStarAreaTag.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldShootingStarMgrEx.h"

namespace uking::action {

CollaboShootingStarAreaTag::CollaboShootingStarAreaTag(const InitArg& arg) : AreaTagAction(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
CollaboShootingStarAreaTag::~CollaboShootingStarAreaTag() {
    ;
}

bool CollaboShootingStarAreaTag::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void CollaboShootingStarAreaTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void CollaboShootingStarAreaTag::leave_() {
    AreaTagAction::leave_();
}

void CollaboShootingStarAreaTag::loadParams_() {
    getMapUnitParam(&mcollaboSSFalloutFlagName_m, "collaboSSFalloutFlagName");
}

void CollaboShootingStarAreaTag::calc_() {
    AreaTagAction::calc_();
}

bool CollaboShootingStarAreaTag::m15(const ksys::act::ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;

    auto* world = ksys::world::Manager::instance();
    if (!world)
        return false;

    auto* mgr = static_cast<ksys::world::ShootingStarMgrEx*>(world->getShootingStarMgr());
    if (!sead::IsDerivedFrom<ksys::world::ShootingStarMgr>(mgr) || !ksys::act::isPlayerProfile(accessor))
        return false;

    mgr->sub_71010D06C4(mcollaboSSFalloutFlagName_m);
    return true;
}

}  // namespace uking::action
