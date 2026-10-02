#include "Game/AI/AI/aiNPCMamonoShopRoot.h"

namespace uking::ai {

NPCMamonoShopRoot::NPCMamonoShopRoot(const InitArg& arg) : NPCRoot(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NPCMamonoShopRoot::~NPCMamonoShopRoot() {
    ;
}

bool NPCMamonoShopRoot::init_(sead::Heap* heap) {
    return NPCRoot::init_(heap);
}

void NPCMamonoShopRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NPCMamonoShopRoot::leave_() {
    NPCRoot::leave_();
}

void NPCMamonoShopRoot::loadParams_() {
    NPCRoot::loadParams_();
    getMapUnitParam(&mMamonoShopPlacement_m, "MamonoShopPlacement");
}

}  // namespace uking::ai
