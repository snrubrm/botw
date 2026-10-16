#include "Game/Actor/AI/aiLastBossRoot.h"
#include "Game/Actor/actLastBoss.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/System/Timer.h"
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

namespace uking::ai {

// NON_MATCHING: the guard timer reset stores both 5.0 values with one 64-bit store in the original; stack slot of
// the home position
void LastBossRoot::calc_() {
    const bool prev_as = _b6;
    _b6 = checkAS(1, 0);
    auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
    if (!boss) {
        setFailed();
        return;
    }
    auto* damage_mgr = sub_710072BA90(mActor);
    if (!damage_mgr) {
        setFailed();
        return;
    }
    if (damage_mgr->getField50() == 3)
        boss->_14f0 = 0;
    else
        ksys::Timer::update(&boss->_14f0, 1.0f);

    const auto isDead = [boss] {
        auto* life = boss->getLife();
        return life && *life == 0;
    };
    const auto resetGuardTimer = [this] {
        _c4.reset(5.0f);
        _b5 = false;
    };

    if ((boss->_14e8.getDirect() & 0xc02) == 2 && !isDead()) {
        if (!(_c4.value <= sead::Mathf::epsilon()))
            _c4.update();
        if (sub_710072B7C4()) {
            if (boss->_14f8._30.isOnBit(0)) {
                if (boss->_14e8.isOnBit(2))
                    boss->_14e8.resetBit(2);
                boss->_14f8._30.resetBit(0);
                boss->update();
            } else if (_b5) {
                _b5 = false;
                boss->update();
            } else if (!sub_71005DD798(mActor, 8, nullptr, 0, 0) || !_b5) {
                if (!sub_71005DD798(mActor, 8, nullptr, 0, 0) && _b5)
                    resetGuardTimer();
            }
        } else if (boss->_14f8._30.isOnBit(0)) {
            if (sub_71005DD798(mActor, 8, nullptr, 0, 0) && !_b5) {
                _b5 = true;
                if (boss->_14e8.isOnBit(2))
                    boss->_14e8.resetBit(2);
                boss->_14f8._30.resetBit(0);
                boss->update();
            } else if (!sub_71005DD798(mActor, 8, nullptr, 0, 0) || !_b5) {
                if (!sub_71005DD798(mActor, 8, nullptr, 0, 0) && _b5)
                    resetGuardTimer();
            }
        } else if (!_b5 && _c4.value <= sead::Mathf::epsilon()) {
            if (!boss->_14e8.isOnBit(2))
                boss->_14e8.setBit(2);
            boss->_14f8._30.setBit(0);
            boss->x();
        } else if (!sub_71005DD798(mActor, 8, nullptr, 0, 0) || !_b5) {
            if (!sub_71005DD798(mActor, 8, nullptr, 0, 0) && _b5)
                resetGuardTimer();
        }
    } else if (boss->_14e8.getDirect() & 0xc00) {
        resetGuardTimer();
    }

    boss->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000000);
    if (boss->_14e8.isOnBit(14) && isSlowTimeMaybe())
        boss->sub_71002C5E58(true);

    getCurrentChild();
    if ((isCurrentChild("通常") || isCurrentChild("リアクション")) && !_b4) {
        if (boss->_14f8._30.isOnBit(8) || (boss->_14e4 != 0 && isDead())) {
            changeChild("特殊リアクション");
            return;
        }
    }

    sub_7100479F74(boss, prev_as);

    sead::Vector3f home;
    boss->getHomePos(&home);
    const auto& player = getPlayerPosition();
    boss->_14e8.changeBit(12, home.y + 3.0f < player.y);
    const bool react = sub_710047A374(boss);

    auto* boss2 = sead::DynamicCast<act::LastBoss>(mActor);
    if (boss2 && boss2->transitionToSecondHalf(*mAuraHPRate_s, mAuraDemoName_s, mAuraEntryName_s, mAuraWallEntry_s,
                                               mAuraDemoDownEntry_s)) {
        if (boss->_14f8._30.isOnBit(4))
            return;
        if (!boss->_14e8.isOnBit(14))
            changeChild("リアクション");
        return;
    }
    if (mActor->get1a0())
        return;
    if (auto* obj = mActor->getMapObject()) {
        if (obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000))
            return;
    }
    auto* child = getCurrentChild();
    if (react) {
        changeChild("リアクション");
        return;
    }
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("リアクション"))
            _b5 = false;
        changeChild("通常");
    }
}

// NON_MATCHING: the two flag bit tests of _14e8 are merged into one mask compare in our build
void LastBossRoot::sub_7100479F74(act::LastBoss* boss, bool update_wait) {
    auto* life = boss->getLife();
    if (life && *life == 0 && !_b4) {
        auto* as_list = mActor->getASList();
        if (!as_list)
            return;
        if (as_list->x_1(1, 0) == "Barrier_Off_Damage_Last" || as_list->x_1(1, 0) == "Damage_Last_Material")
            return;
        if (boss->_14e8.isOnBit(17))
            changeAS("Barrier_Off_Damage_Last", true, 1, 0);
        else
            changeAS("Damage_Last_Material", true, 1, 0);
        return;
    }

    if (!boss->_14e8.isOnBit(1) || !boss->_14f8._30.isOnBit(0)) {
        if (auto* as_list = mActor->getASList()) {
            if (as_list->x_1(1, 0) == "Barrier_Off" || as_list->x_1(1, 0) == "Barrier_Off_AtSlow") {
                if (!update_wait)
                    return;
            }
            if (auto* damage_mgr = boss->getDamageMgr()) {
                if (s32(damage_mgr->getDamage()) >= 1)
                    changeAS("Damage", false, 1, 0);
            }
        }
    }

    if (!update_wait)
        return;
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;
    const auto& flags = boss->_14e8;
    if (flags.isOnBit(1)) {
        if (!flags.isOnBit(10) && (boss->_14f8._30.getDirect() & 0x11) == 1 && as_list->x_1(0, 0) != "Miss") {
            auto* boss_life = boss->getLife();
            if (!boss_life || *boss_life != 0) {
                boss->x();
                return;
            }
        }
    }
    if (boss->_14f8._30.isOnBit(4) || boss->_14e8.isOnBit(10) || boss->_14e8.isOnBit(11))
        changeAS("DownWaitMaterial", false, 1, 0);
    else
        changeAS("Wait_Battle_Material", false, 1, 0);
}

bool LastBossRoot::sub_710047A374(act::LastBoss* boss) {
    auto* child = getCurrentChild();
    if (!child)
        return false;
    auto* damage_mgr = sub_710072BA90(mActor);
    if (!damage_mgr)
        return false;

    const auto isDead = [this] {
        auto* life = mActor->getLife();
        return life && *life == 0;
    };

    if (!_b4 && isDead()) {
        if (child->isFinished() || child->isFailed()) {
            _b4 = true;
            return true;
        }
    } else if (_b4 && isDead()) {
        return false;
    }

    if (u32(damage_mgr->getField54() - 9) < 6)
        return false;

    if (child->isChangeable() && sub_71005D6E28(mActor)) {
        bool react = true;
        if (isCurrentChild("リアクション"))
            react = child->isFinished() || child->isFailed();
        const bool dead = isDead() && !_b4;
        const bool result = react | dead | boss->_14f8._30.isOnBit(2);
        if (dead && isSlowTimeMaybe()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&act::PlayerInfo::getSomeProcLink(), &accessor);
            sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000b2), nullptr);
        }
        if (!result)
            return false;
        _b4 |= dead;
        return true;
    }

    if (!isCurrentChild("特殊リアクション") && boss->_14e4 == 0) {
        if (damage_mgr->checkDamageFlags(1) && damage_mgr->getField50() == 3)
            return true;
        if (!_b4 && isDead()) {
            _b4 = true;
            return true;
        }
    }

    if (sub_71005D6E28(mActor) && boss->_14f8._30.isOnBit(7))
        return true;

    if (!boss->getActorPartsActor("ShockWave").hasProcInCalcState())
        return false;
    auto* wave = sead::DynamicCast<ksys::act::Actor>(boss->getActorPartsActor("ShockWave").getProc(nullptr, nullptr));
    if (!wave)
        return false;
    const s32 num = getNumAttackInfoMaybe(wave);
    for (s32 i = 0; i < num; ++i) {
        auto* info = getAttackInfo(wave, i);
        if (info && (info->_18 & 2))
            return true;
    }
    return false;
}

}  // namespace uking::ai
