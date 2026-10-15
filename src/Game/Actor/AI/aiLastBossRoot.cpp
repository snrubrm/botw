#include "Game/Actor/AI/aiLastBossRoot.h"
#include "Game/Actor/actLastBoss.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_71007398C0.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldChemicalMgr.h"
#include "Game/gameLastBossMgr.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LastBossRoot::LastBossRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossRoot::~LastBossRoot() = default;

bool LastBossRoot::init_(sead::Heap* heap) {
    if (auto* mgr = LastBossMgr::instance())
        mgr->sub_7100677FFC(mActor);
    _b4 = false;
    _b5 = false;
    return true;
}

// NON_MATCHING: home vector copy and timer stores are grouped differently.
void LastBossRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("通常");
    if (auto* world = ksys::world::Manager::instance()) {
        if (auto* chemical = world->getChemicalMgr())
            chemical->_b14.reset(8);
    }
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        sead::Vector3f home;
        boss->getHomePos(&home);
        boss->_14d8 = home;
        boss->sub_71002C6220(true);
        boss->sub_71002C69CC();
        boss->sub_71002C6A78();
        const s32 cleared = getNumberOfClearedRemains();
        boss->_1538 = *mForceRecoverHitMax_s + *mAddForceRecoverHitNum_s * cleared;
        boss->_1540 = *mForceRecoverDamageMax_s + *mAddForceRecoverDamage_s * cleared;
        if (checkHpRate(boss, 0.5f) && !boss->get1a0() &&
            (!boss->getMapObject() ||
             !boss->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000)) &&
            boss->_14e8.isOn(1)) {
            boss->_14e8.set(0x20);
        }
    }
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E764(false);
        controller->sub_7100F62CA8(false);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityObject);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
        controller->mFlags.set(0xc00);
    }
    _b8 = ksys::Timer(30.0f, 30.0f);
    _c4 = ksys::Timer(0.0f, 0.0f);
    _d0 = ksys::Timer(30.0f, 30.0f);
    _b5 = false;
    _dc = 0;
    if (testRootAiFlag(ksys::act::ai::RootAiFlag::_7)) {
        sub_71007A3540(mActor);
        sub_7100739918(mActor);
        sub_71005D74E8(mActor);
        if (auto* list = mActor->getASList()) {
            if (list->x_1(1, 0) == "ResetMaterial")
                changeAS("Wait_Battle_Material", false, 1, 0);
        }
    }
}

bool LastBossRoot::hasPreDeleteCb() {
    return true;
}

void LastBossRoot::onPreDelete() {
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        boss->sub_71002C5A14();
        boss->sub_71002C5DB4();
    }
}

// NON_MATCHING: boss-pointer lifetime and parts-loop/cleanup branch layout differ.
void LastBossRoot::leave_() {
    auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
    if (boss) {
        boss->sub_71002C5E58(false);
        boss->sub_71002C6A24();
        boss->stunEnd();
        boss->sub_71002C5B3C();
    }
    if (mActor->getRootAi()->isActorGoingBackToRootAi()) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            for (auto* part : enemy->_1128.mList) {
                if (part->mLink.hasProcInCalcState()) {
                    ksys::act::ActorLinkConstDataAccess accessor;
                    ksys::act::acquireActor(&part->mLink, &accessor);
                    if (accessor.hasTag(0u))
                        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
                }
            }
        }
        sub_71005D74E8(mActor);
        sub_71005DB3EC(mActor);
        sub_7100739900(mActor);
        if (auto* control = sub_71007398C0(mActor))
            control->sub_7100D86C90();
        if (boss) {
            if (boss->_14e8.isOn(1))
                boss->sub_71002C5A14();
            if (auto* life = boss->getLife(); life && *life == 0)
                boss->sub_71002C5DB4();
        }
    } else if (mActor->getRootAi()->isActorDeletedOrDeleting() && boss) {
        boss->sub_71002C5A14();
        boss->sub_71002C5DB4();
    }
    if (auto* world = ksys::world::Manager::instance()) {
        if (auto* chemical = world->getChemicalMgr())
            chemical->_b14.set(8);
    }
}

void LastBossRoot::loadParams_() {
    getStaticParam(&mForceRecoverHitMax_s, "ForceRecoverHitMax");
    getStaticParam(&mForceRecoverDamageMax_s, "ForceRecoverDamageMax");
    getStaticParam(&mAddForceRecoverHitNum_s, "AddForceRecoverHitNum");
    getStaticParam(&mAddForceRecoverDamage_s, "AddForceRecoverDamage");
    getStaticParam(&mAuraHPRate_s, "AuraHPRate");
    getStaticParam(&mAuraDemoName_s, "AuraDemoName");
    getStaticParam(&mAuraEntryName_s, "AuraEntryName");
    getStaticParam(&mAuraWallEntry_s, "AuraWallEntry");
    getStaticParam(&mAuraDemoDownEntry_s, "AuraDemoDownEntry");
}

}  // namespace uking::ai
