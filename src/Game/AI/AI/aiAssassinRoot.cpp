#include "Game/AI/AI/aiAssassinRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"

namespace uking::ai {

AssassinRoot::AssassinRoot(const InitArg& arg) : NPCRoot(arg) {}

AssassinRoot::~AssassinRoot() = default;

bool AssassinRoot::init_(sead::Heap* heap) {
    return NPCRoot::init_(heap);
}

void AssassinRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void AssassinRoot::calc_() {
    NPCRoot::calc_();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (auto* mgr = ksys::map::AutoPlacementMgr::instance()) {
        if (mgr->isNonAutoPlacement(pos, true) && mgr->auto0(pos, 0))
            mActor->deleteEx(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool AssassinRoot::hasPreDeleteCb() {
    return true;
}

void AssassinRoot::leave_() {
    NPCRoot::leave_();
}

void AssassinRoot::loadParams_() {
    NPCRoot::loadParams_();
    getStaticParam(&mChangeDistance_s, "ChangeDistance");
    getMapUnitParam(&mEquipItem1_m, "EquipItem1");
    getMapUnitParam(&mEquipItem2_m, "EquipItem2");
    getMapUnitParam(&mEquipItem3_m, "EquipItem3");
    getMapUnitParam(&mEquipItem4_m, "EquipItem4");
    getMapUnitParam(&mRideHorseName_m, "RideHorseName");
}

}  // namespace uking::ai
