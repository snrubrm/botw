#include "Game/Actor/aiUnk_710073BB28.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/UI/uiUtils.h"
#include "Game/gamePlayReport.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"

void sub_710073BB28(bool a, bool b) {
    uking::ui::sub_7100A94AC8();
    uking::ui::sub_7100A94C74(a, b);
}

bool sub_710073BB54() {
    if (uking::ui::sub_7100A94AC8())
        return true;
    return !uking::ui::sub_7100A94E08();
}

bool sub_710073BB80(ksys::act::Actor* actor) {
    return actorHasTagCanGetPouch(actor->getName());
}

void sub_710073BADC() {
    uking::ui::playSound("mc_DoUnable", nullptr);
}

void weaponBroken(ksys::act::Actor* actor) {
    uking::ui::PauseMenuDataMgr::instance()->removeWeaponIfEquipped(actor->getName());
    uking::ui::mainScreen3DStuff();
}

void uking::removeFromInventory(const sead::SafeString& name) {
    uking::ui::PauseMenuDataMgr::instance()->removeWeaponIfEquipped(name);
    uking::ui::mainScreen3DStuff();
}

void masterSwordBroken() {
    uking::ui::PauseMenuDataMgr::instance()->breakMasterSword();
    uking::ui::mainScreen3DStuff();
}

// Declaration-only: full native 620-byte item handler and 332-byte event tail
// establish the side-effect-only return and these two inputs. Source namespace is unknown.
void doGetItem(const sead::SafeString& name, const uking::act::WeaponModifierInfo* modifier);

void setItemDataToPouch(const sead::SafeString& name,
                       const uking::act::WeaponModifierInfo* modifier) {
    if (ksys::act::hasTag(name, ksys::act::tags::ZukanWeapon) &&
        !uking::ui::PauseMenuDataMgr::instance()->cannotGetItem(name, 1)) {
        auto* info = uking::act::PlayerInfo::instance();
        uking::reportGetItem(info ? info->getPlayerPos() : sead::Vector3f::zero, name);
    }
    doGetItem(name, modifier);
}

// NON_MATCHING: the native bool argument uses branch normalization instead of a mask.
void getDemoGetAnotherActor(ksys::act::Actor* actor, const sead::SafeString& actor_name,
                           bool can_get_pouch, bool option, uking::act::WeaponModifierInfo* modifier) {
    if (auto* manager = ksys::evt::Manager::instance()) {
        ksys::evt::Metadata metadata;
        callGetAnotherItemDemo(&metadata, actor_name, can_get_pouch,
                               ksys::act::hasTag(actor, ksys::act::tags::GetAnotherActor), option,
                               modifier);
        manager->callEvent(metadata, actor, nullptr);
    }
}
