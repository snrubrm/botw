#include "Game/AI/AI/aiNPCGerudoQueenRoot.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::ai {

// 0x710240b650
static const sead::SafeString sUnk_710240b650[] = {
    "Gerudo_Ch_Helmet_Finish",
    "Npc_oasis003_IntoFrontThrone",
    "Npc_oasis003_IntoThrone",
};

NPCGerudoQueenRoot::NPCGerudoQueenRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCGerudoQueenRoot::~NPCGerudoQueenRoot() = default;

bool NPCGerudoQueenRoot::init_(sead::Heap* heap) {
    return NPCRoot::init_(heap);
}

void NPCGerudoQueenRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NPCGerudoQueenRoot::leave_() {
    ksys::gdt::setBoolByKey(false, sUnk_710240b650[1]);
    ksys::gdt::setBoolByKey(false, sUnk_710240b650[2]);
    _248 = false;
    NPCRoot::leave_();
}

void NPCGerudoQueenRoot::loadParams_() {
    NPCRoot::loadParams_();
    getMapUnitParam(&mIsOnHelmet_m, "IsOnHelmet");
}

}  // namespace uking::ai
