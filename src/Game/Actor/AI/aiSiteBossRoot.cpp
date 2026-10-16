#include "Game/Actor/AI/aiSiteBossRoot.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ai {

// 0x71025bc6e0 (.bss, after the SiteBossRecognizeRoot RTTI statics): when set, SiteBossRoot::enter_ sets bit 10 of
// SiteBoss::_1558 (cleared otherwise). Only read there; no writer found.
// Hidden visibility: read with adrp + ldrb (no GOT), as gdtCommonFlags.h and the worldWindMgr.cpp constants.
KSYS_VISIBILITY_HIDDEN bool sUnk_71025BC6E0 = false;

SiteBossRoot::SiteBossRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossRoot::~SiteBossRoot() {
    x();
    if (ksys::act::hasTag(mActor, ksys::act::tags::EnemySiteBoss_R) &&
        !mIsPlayed_DemoFlagName_s.isEmpty()) {
        ksys::gdt::setBoolByKey(false, mIsPlayed_DemoFlagName_s);
    }
}

void SiteBossRoot::x() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    auto& link = enemy->getActorPartsActor("WeakPoint");
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    enemy->sub_7100D3CFEC("WeakPoint");
}

bool SiteBossRoot::init_(sead::Heap* heap) {
    if (!sead::IsDerivedFrom<act::Enemy>(mActor))
        return false;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->m51(true);
        if (auto* chemical = boss->sub_71011D8A54("WeaponChemical")) {
            chemical->sub_7100D90F60(true);
            if (((chemical->mMaterial->attribute.ref() & 0x108) == 0x108 &&
                 !(chemical->_be & 4)) || chemical->_1b8 > 0.0f) {
                chemical->sub_7100D90AF4(false);
            }
        }
        if (auto* chemical = boss->sub_71011D8A54("ShieldChemical")) {
            chemical->sub_7100D90F60(true);
            if (((chemical->mMaterial->attribute.ref() & 0x108) == 0x108 &&
                 !(chemical->_be & 4)) || chemical->_1b8 > 0.0f) {
                chemical->sub_7100D90AF4(false);
            }
        }
        boss->_1514 = *mWeakPointDamageRate_s;
        boss->_151c = *mBlownOffAtWeakPointHitNum_s;
        if (!mIsPlayed_DemoFlagName_s.isEmpty() && mActor->getMapObject() &&
            ksys::gdt::getBoolByKey(mIsPlayed_DemoFlagName_s, false)) {
            boss->_1540 = 1;
        }
    }
    if (auto* effects = Unk_710260af28::instance())
        effects->sub_7100F1ECE8(mActor->getModel());
    _d9 = false;
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115BAF8("Root");
    return true;
}

// NON_MATCHING: the original keeps the position copy at sp + 0x10 and stores _e8 after _f0
void SiteBossRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    if (!_d9) {
        mActor->emitBasicSigOff();
        mActor->emitSignalAxisY_0();
        _d9 = true;
    }
    ui::sub_7100A9B5B0(true);
    {
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        ui::sub_7100A9B584(&pos);
    }

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (!boss->get1a0() &&
            !(boss->getMapObject() && boss->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
            boss->sub_71002D39D8();
        }
        boss->_e90 = 1;
        if (checkHpRate(boss, 0.5f) && !boss->get1a0() &&
            !(boss->getMapObject() && boss->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000)) &&
            boss->_1558.isOnBit(8)) {
            boss->_1558.resetBit(7);
            boss->_1558.setBit(9);
        }
        boss->_1558.resetBit(26);
        if (auto* damage_mgr = boss->getDamageMgr()) {
            if (!boss->_14c8.mDamageManager)
                damage_mgr->addDamageCallback(4, &boss->_14c8);
        }
        if (*mOffFlagIndexAtClipping_s != -1)
            boss->_1544 = *mOffFlagIndexAtClipping_s;
        boss->_1558.changeBit(10, sUnk_71025BC6E0);
    }

    _dc.value = 30.0f;
    _dc.previous_value = 30.0f;
    _dc.rate = -1.0f;
    _f0 = 1.0f;
    _f4 = 0;
    _d8 = false;
    _e8 = 0;
    _ec = 0;
    _da = true;

    if (!mIsPlayed_DemoFlagName_s.isEmpty() && mActor->getMapObject() &&
        !ksys::gdt::getBoolByKey(mIsPlayed_DemoFlagName_s, false)) {
        changeChild("出現デモ待ち");
        return;
    }

    if (testRootAiFlag(ksys::act::ai::RootAiFlag::_7))
        sub_71007A3540(mActor);
    if (testRootAiFlag(ksys::act::ai::RootAiFlag::_7) && !checkHpRate(mActor, 0.5f)) {
        if (auto* as_list = mActor->getASList())
            as_list->sub_710115BAF8("Root");
        changeChild("出現デモ終了直後");
        sub_7100739918(mActor);
        return;
    }

    auto* actor = mActor;
    if (!actor->get1a0() &&
        !(actor->getMapObject() && actor->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
        if (auto* as_list = actor->getASList())
            as_list->sub_710115CD0C();
    }
    const s32* life = mActor->getLife();
    if (life && *life <= 0)
        changeChild("リアクション");
    else
        changeChild("通常");
}

void SiteBossRoot::leave_() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss)
        return;

    if (mActor->getRootAi()->isActorGoingBackToRootAi()) {
        if (!checkHpRate(mActor, 0.5f)) {
            if (auto* as_list = mActor->getASList())
                as_list->sub_710115BAF8("Root");
            sub_71007398E4(mActor, true);
        }
        if (auto* controller = mActor->getCharacterController()) {
            controller->sub_7100F5F6FC(sead::Vector3f::zero);
            controller->sub_7100F5FB24(sead::Vector3f::zero);
        }
        if (checkHpRate(mActor, 0.5f)) {
            if (boss->_1558.isOnBit(7))
                boss->_1558.resetBit(7);
            boss->x_0();
        }
    } else if (mActor->getRootAi()->isActorDeletedOrDeleting()) {
        if (auto* damage_mgr = boss->getDamageMgr())
            damage_mgr->removeDamageCallback(&boss->_14c8);
        boss->x_0();
    }
    boss->sub_71002D28BC();
    boss->sub_71002D3944();
    ui::sub_7100A9B5B0(false);
}

void SiteBossRoot::onPreDelete() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->x_0();
}

void SiteBossRoot::m34(act::SiteBoss* boss) {}

// NON_MATCHING: shared return tails and callback flag test scheduling.
bool SiteBossRoot::m35(act::SiteBoss* boss) {
    auto* child = getCurrentChild();
    if (!child)
        return false;
    auto* life = boss->getLife();
    if (life && *life <= 0 && !boss->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::Alive)) {
        auto* current_life = mActor->getLife();
        if (!current_life || *current_life != 0 || _d8 || !isSlowTimeMaybe())
            return true;
    } else {
        if (boss->_1558.isOn(0x4000000))
            return true;
        if (!boss->_14c8._30.isOn(0x200) &&
            ((child->isChangeable() && sub_71005D6E28(mActor)) || boss->_14c8._30.isOn(0x100))) {
            const bool child_done = !isCurrentChild("リアクション") || child->isFinished() || child->isFailed();
            auto* current_life = mActor->getLife();
            const bool first_zero = current_life && *current_life == 0 && !_d8;
            const u16 flags = boss->_14c8._30.getDirect();
            boss->_14c8._30.reset(0x100);
            if (!child_done && !first_zero && !(flags & 0x101))
                return false;
            _d8 |= first_zero;
            if (!first_zero || !isSlowTimeMaybe())
                return true;
        } else {
            if (boss->_14c8._30.isOn(0x200) || boss->_1558.isOn(0x10000))
                return false;
            auto* damage = sub_710072BA90(mActor);
            if (!damage)
                return false;
            if (damage->checkDamageFlags(1) || damage->checkDamageFlags(0)) {
                if (damage->getField50() == 3 || damage->getField50() == 16)
                    return true;
            }
            if (boss->_14c8._30.isOn(0x2000))
                return true;
            if (damage->getField54() == 6)
                return true;
            return damage->getField54() == 7;
        }
    }

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&act::PlayerInfo::getSomeProcLink(), &accessor);
    sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000b2), nullptr);
    return true;
}

void SiteBossRoot::loadParams_() {
    getStaticParam(&mOffFlagIndexAtClipping_s, "OffFlagIndexAtClipping");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mForceRecoverHitMax_s, "ForceRecoverHitMax");
    getStaticParam(&mForceRecoverDamageMax_s, "ForceRecoverDamageMax");
    getStaticParam(&mAddForceRecoverHitNum_s, "AddForceRecoverHitNum");
    getStaticParam(&mAddForceRecoverDamage_s, "AddForceRecoverDamage");
    getStaticParam(&mBlownOffAtWeakPointHitNum_s, "BlownOffAtWeakPointHitNum");
    getStaticParam(&mDemoPlayHPRate_s, "DemoPlayHPRate");
    getStaticParam(&mWeakPointDamageRate_s, "WeakPointDamageRate");
    getStaticParam(&mIsRemainBoss_s, "IsRemainBoss");
    getStaticParam(&mDemoName_s, "DemoName");
    getStaticParam(&mNormalEntryName_s, "NormalEntryName");
    getStaticParam(&mAtDownEntryName_s, "AtDownEntryName");
    getStaticParam(&mIsPlayed_DemoFlagName_s, "IsPlayed_DemoFlagName");
    getMapUnitParam(&mUniqueNameMessageLabel_m, "UniqueNameMessageLabel");
}

bool SiteBossRoot::handleMessage_(const ksys::Message* message) {
    return message->getType() == 0x3000007;
}

}  // namespace uking::ai
