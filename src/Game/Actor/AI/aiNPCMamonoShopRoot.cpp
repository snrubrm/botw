#include "Game/Actor/AI/aiNPCMamonoShopRoot.h"
#include "Game/gameGraphics.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

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

    if (auto* physics = mActor->getPhysics()) {
        if (auto* cloth_set = physics->getClothSet())
            cloth_set->_70 |= 0x20000;
    }

    if (mActor->isCalc())
        return;

    auto* schedule = mActor->getSchedule();
    if ((schedule && schedule->_68 == "Action1") || sub_71004CD42C()) {
        _248 = true;
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
        ksys::act::setEnabledTalkAndLockOn(mActor, false);
        if (auto* controller = mActor->getCharacterController()) {
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityObject);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntitySmallObject);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityHitOnlyWater);
        }
        if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "Body"))
            body->removeFromWorld();
        if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
            npc->_fe8 |= 0x20000000;
    } else {
        _248 = false;
        mActor->emitBasicSigOn();
        ksys::gdt::setBoolByKey(true, "MamonoShop_Start");
    }
}

void NPCMamonoShopRoot::leave_() {
    NPCRoot::leave_();
}

void NPCMamonoShopRoot::calc_() {
    NPCRoot::calc_();
    auto* schedule = mActor->getSchedule();
    if (!schedule)
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::findLinkedActor(&accessor, mActor, "TwnObj_MamonoShop_A_01");
    if (_248 && schedule->_88 == "Action2" && accessor.hasProc() && !accessor.sub_7100D10E6C(5)) {
        _248 = false;
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        ksys::act::x_6(mActor);
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F60604();
        if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "Body"))
            body->addToWorld();
        if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
            npc->_fe8 &= ~0x20000000;
        ksys::act::setEnabledTalkAndLockOn(mActor, true);
        mActor->emitBasicSigOn();
        ksys::gdt::setBoolByKey(true, "MamonoShop_Start");
    }
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
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::findLinkedActor(&accessor, mActor, "TwnObj_MamonoShop_A_01");
    if (accessor.hasProc()) {
        const sead::Vector3f shop_pos = accessor.getActorMtx().getTranslation();
        f32 radius = 30.0f;
        if (!mActor->isCalc())
            radius = 5.0f;
        const auto& player_pos = uking::act::PlayerInfo::instance()->getPlayerPos();
        const f32 dx = shop_pos.x - player_pos.x;
        const f32 dz = shop_pos.z - player_pos.z;
        if (std::sqrt(dx * dx + dz * dz) < radius)
            return true;
    }
    return false;
}

}  // namespace uking::ai
