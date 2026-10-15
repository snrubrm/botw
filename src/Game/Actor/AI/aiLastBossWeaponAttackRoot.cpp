#include "Game/Actor/AI/aiLastBossWeaponAttackRoot.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_7100FFDFDC.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Map/mapObject.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LastBossWeaponAttackRoot::LastBossWeaponAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossWeaponAttackRoot::~LastBossWeaponAttackRoot() = default;

bool LastBossWeaponAttackRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossWeaponAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7EBE0(1.0f);
        awareness->enable();
    }
    auto* target = sub_71005D9050(mActor);
    if ((target && target->hasProc() && ksys::act::isPlayerProfile(target)) ||
        mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000)) {
        sub_710047EA10();
        return;
    }
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_2) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4)) {
        sub_710047ED84();
        return;
    }
    auto* damage = sub_710072BA90(mActor);
    if (damage && s32(damage->getDamage()) >= 1)
        sub_710047ED84();
    else
        changeToWait();
}

// NON_MATCHING: branch layout and string/awareness register allocation differ.
void LastBossWeaponAttackRoot::calc_() {
    auto* child = getCurrentChild();
    child->setDynamicParam(*mIsAttackPatternFixed_d, "IsAttackPatternFixed");
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("発見中")) {
            sub_71005D8E9C(mActor);
            changeToWait();
        } else if (isCurrentChild("ダメージ反応")) {
            if (sub_710047F2B8())
                sub_710047EA10();
            else
                changeToWait();
        }
    } else if (child->isChangeable() && isCurrentChild("ダメージ反応")) {
        auto* target = sub_71005D9050(mActor);
        if (!target || !target->hasProc()) {
            if (auto* awareness = mActor->getAwareness()) {
                Unk_7102451678 filter;
                auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter);
                const auto& link = entry ? entry->_0.mLink : uking::act::PlayerInfo::getSomeProcLink();
                sub_71005D8DE8(mActor, link, entry ? &entry->_58 : nullptr, nullptr);
            }
        }
        sub_710047EA10();
    }
    if (isCurrentChild("待機") && sub_710047F2B8())
        sub_710047EA10();
}

void LastBossWeaponAttackRoot::leave_() {
    if (auto* awareness = mActor->getAwareness())
        awareness->disable();
}

// NON_MATCHING: kind selection becomes a jump table instead of membership-test branches.
void LastBossWeaponAttackRoot::sub_710047EA10() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EBE0(1.0f);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->_e90 != 4) {
            enemy->_e90 = 4;
            bool start_bgm = *mIsStartBossBgm_s;
            if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
                const s32 kind = boss->_1534;
                if ((kind & ~3) == 4) {
                    if (kind == 0 || kind == 4 || kind == 8)
                        start_bgm &= ksys::gdt::getFlag_IsPlayed_Demo141_0(false);
                    else if (kind == 3 || kind == 7 || kind == 11)
                        start_bgm &= ksys::gdt::getFlag_IsPlayed_Demo141_3(false);
                    else if (kind == 1 || kind == 5 || kind == 9)
                        start_bgm &= ksys::gdt::getFlag_IsPlayed_Demo141_1(false);
                    else if (kind == 2 || kind == 6 || kind == 10)
                        start_bgm &= ksys::gdt::getFlag_IsPlayed_Demo141_2(false);
                }
            }
            if (start_bgm) {
                Unk_71024fd448* bgm;
                if (*mEnemyType_s == -1) {
                    bgm = sub_7100FFE5EC();
                } else {
                    const ksys::snd::RemainsBossBgmType type = *mEnemyType_s;
                    bgm = sub_7100FFE520(&type);
                }
                if (bgm)
                    bgm->sub_71010003A4();
            }
        }
    }
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (!boss->get1a0() &&
            !(boss->getMapObject() &&
              boss->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
            if (boss->_1540) {
                boss->_2390.sub_7100723418(30.0f);
                boss->_1540 = 0;
            } else {
                boss->_2390._8 = true;
            }
        }
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(*mIsAttackPatternFixed_d, "IsAttackPatternFixed", -1);
    changeChild("発見中", &pack);
}

void LastBossWeaponAttackRoot::sub_710047ED84() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EBE0(1.5f);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->_e90 != 4) {
            enemy->_e90 = 4;
            if (*mIsStartBossBgm_s) {
                Unk_71024fd448* bgm;
                if (*mEnemyType_s == -1) {
                    bgm = sub_7100FFE5EC();
                } else {
                    const ksys::snd::RemainsBossBgmType type = *mEnemyType_s;
                    bgm = sub_7100FFE520(&type);
                }
                if (bgm)
                    bgm->sub_71010003A4();
            }
        }
    }
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (!boss->get1a0() &&
            !(boss->getMapObject() &&
              boss->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
            if (boss->_1540) {
                boss->_2390.sub_7100723418(30.0f);
                boss->_1540 = 0;
            } else {
                boss->_2390._8 = true;
            }
        }
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("ダメージ反応", &pack);
}

// NON_MATCHING: range-parameter selection uses conditional selects; registers and cleanup branches differ.
bool LastBossWeaponAttackRoot::sub_710047F2B8() {
    auto* awareness = mActor->getAwareness();
    if (!awareness || awareness->_300 == 0)
        return false;
    Unk_7102451678 filter;
    auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter);
    if (!entry || entry->_a0 == 0)
        return false;

    sead::Vector3f target;
    entry->_58.getTranslation(target);
    sead::Vector3f home;
    bool special = false;
    bool reappearance = false;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        home = boss->_2318;
        special = (boss->_1534 & ~3) == 4;
        reappearance = boss->_1558.isOnBit(15);
    } else {
        mActor->getHomePos(&home);
    }
    const auto* distance = reappearance ? mReappearanceDist_s : mChaseDist_s;
    const auto* offset = reappearance ? mReappearanceDistOffset_s : mChaseDistOffset_s;
    if (!sub_71002D17D4(mActor, &home, &target, distance, offset, special))
        return false;
    sub_71005D8DE8(mActor, entry->_0.mLink, &entry->_58, nullptr);
    return true;
}

void LastBossWeaponAttackRoot::loadParams_() {
    getStaticParam(&mEnemyType_s, "EnemyType");
    getStaticParam(&mIsStartBossBgm_s, "IsStartBossBgm");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
    getStaticParam(&mReappearanceDist_s, "ReappearanceDist");
    getStaticParam(&mReappearanceDistOffset_s, "ReappearanceDistOffset");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
}

void LastBossWeaponAttackRoot::changeToWait() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EBE0(1.0f);

    ksys::act::ai::InlineParamPack pack;
    pack.addBool(true, "IsResetEndTime", -1);
    changeChild("待機", &pack);
}

}  // namespace uking::ai
