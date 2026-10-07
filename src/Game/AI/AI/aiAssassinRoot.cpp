#include "Game/AI/AI/aiAssassinRoot.h"
#include "Game/Actor/actNPCBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"

namespace uking::ai {

AssassinRoot::AssassinRoot(const InitArg& arg) : NPCRoot(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
AssassinRoot::~AssassinRoot() {
    ;
}

bool AssassinRoot::init_(sead::Heap* heap) {
    NPCRoot::init_(heap);
    if (auto* npc = sead::DynamicCast<act::NPCBase>(mActor)) {
        const sead::Vector3f position = mActor->getMtx().getTranslation();
        if (_290.sub_7100EEDDA4(position))
            npc->_840 = &_290;
    }
    return true;
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

void AssassinRoot::onPreDelete() {
    if (auto* npc = sead::DynamicCast<act::NPCBase>(mActor)) {
        if (npc->_840 == &_290)
            npc->_840 = nullptr;
    }
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

void AssassinRoot::m35() {}

}  // namespace uking::ai
