#include "Game/AI/AI/aiNPCMamonoShopRoot.h"
#include "Game/gameGraphics.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

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

// 0x71004cd790
void NPCMamonoShopRoot::onPreDelete() {
    if (auto* graphics = Graphics::instance()) {
        if (auto* block = graphics->getUnk_ab0())
            block->_e48 |= 0x80000000;
    }
    mActor->emitBasicSigOff();
    ksys::gdt::setBoolByKey(false, "MamonoShop_Start");
    ksys::gdt::setBoolByKey(false, "MamonoShop_OpenStop");
    ksys::gdt::setBoolByKey(false, "MamonoShop_Forward");
}

void NPCMamonoShopRoot::loadParams_() {
    NPCRoot::loadParams_();
    getMapUnitParam(&mMamonoShopPlacement_m, "MamonoShopPlacement");
}

// 0x71004cd42c
bool NPCMamonoShopRoot::sub_71004CD42C() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::findLinkedActor(&accessor, mActor, "TwnObj_MamonoShop_A_01");
    if (accessor.hasProc()) {
        const sead::Vector3f shop_pos = accessor.getActorMtx().getTranslation();
        f32 radius = 30.0f;
        if (!mActor->isCalc())
            radius = 5.0f;
        const auto& player_pos = ksys::act::PlayerInfo::instance()->getPlayerPos();
        const f32 dx = shop_pos.x - player_pos.x;
        const f32 dz = shop_pos.z - player_pos.z;
        if (std::sqrt(dx * dx + dz * dz) < radius)
            return true;
    }
    return false;
}

}  // namespace uking::ai
