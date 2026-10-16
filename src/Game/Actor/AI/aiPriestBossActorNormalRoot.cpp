#include "Game/Actor/AI/aiPriestBossActorNormalRoot.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::ai {

PriestBossActorNormalRoot::PriestBossActorNormalRoot(const InitArg& arg)
    : PriestBossActorRoot(arg) {}

PriestBossActorNormalRoot::~PriestBossActorNormalRoot() = default;

bool PriestBossActorNormalRoot::init_(sead::Heap* heap) {
    if (!PriestBossActorRoot::init_(heap))
        return false;
    _80.makeAllZero();
    return true;
}

// NON_MATCHING: getter arguments are evaluated in a different order and enum bit-index temporaries are absent.
void PriestBossActorNormalRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorRoot::enter_(params);
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->_c48.sub_71002DBC8C(uking::act::PlayerInfo::getSomeProcLink(),
                                  &player.getActorMtx(), &player.getPreviousPos());
        enemy->_c48._7c = 5;
    }
    if (!_80.isOn(1)) {
        *mEquipWeaponBufIndex_a = -1;
        _80.set(1);
    }
    sub_710050DC18(false);
}

// NON_MATCHING: temporary string storage and the sync-mode branch layout differ.
void PriestBossActorNormalRoot::calc_() {
    PriestBossActorRoot::calc_();
    if (!sub_7100505BE4()) {
        if (!isCurrentChild("通常モード")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addBool(false, "FromSyncMode", -1);
            changeChild("通常モード", &pack);
        }
        return;
    }
    if (m36())
        return;
    if (isCurrentChild("攻撃変更の間")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            sub_710050DC18(true);
        return;
    }
    if (sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_0) &&
        !isCurrentChild("シンクロモード")) {
        changeChild("攻撃変更の間");
        return;
    }
    if (!sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_0) &&
        !isCurrentChild("通常モード"))
        changeChild("攻撃変更の間");
}

void PriestBossActorNormalRoot::leave_() {
    PriestBossActorRoot::leave_();
}

void PriestBossActorNormalRoot::loadParams_() {
    PriestBossActorRoot::loadParams_();
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
}

// NON_MATCHING: the original skips the null test of mActor before the Enemy cast and passes the flag bit through a
// stack slot
// 0x710050e284: drops the boss's two equipped weapons and equips a new bow and sword
void PriestBossActorNormalRoot::m35() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    for (s32 i = 0; i < 2; ++i) {
        if (enemy->getWeapons()->getEquippedWeapon(i)) {
            enemy->getWeapons()->getEquippedWeapon(i)->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            enemy->dropWeapon(i, sead::Vector3f::zero, false, false, nullptr, false);
            _80.setBit(i + 1);
        }
    }

    const sead::SafeString names[] = {"Weapon_Bow_029", "Weapon_Sword_015"};
    ksys::act::InstParamPack params;
    params->addPosition(sUnk_71025c8d04);
    params->add(-1, "Life");
    params->add(false, "IsPlayerPut");
    for (s32 i = 0; i < 2; ++i) {
        auto* actor = ksys::act::ActorCreator::instance()->createActor(
            names[i].cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &params, true, false);
        if (auto* weapon = sead::DynamicCast<act::Weapon>(actor))
            enemy->sub_7100015438(i, weapon);
        else
            actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    *mEquipWeaponBufIndex_a = -1;
}

// NON_MATCHING: the return value of the last isFailed() test is folded into `!x` (mvn / and) where
// the original branches to the shared `return false` / `return true` blocks
bool PriestBossActorNormalRoot::m36() {
    if (isCurrentChild("バナナモード")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            return false;
        return true;
    }

    if (sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_10))
        return false;

    if (isChangeable() || isFinished() || isFailed()) {
        if (!sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_7))
            return false;
        changeChild("バナナモード");
        return true;
    }
    return false;
}

// 0x710050dc18
void PriestBossActorNormalRoot::sub_710050DC18(bool from_sync) {
    if (!sub_7100505BE4())
        return;
    if (sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_0) && !isCurrentChild("シンクロモード")) {
        changeChild("シンクロモード", nullptr);
        sub_710050DDBC(2);
        return;
    }
    if (!sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_0) && !isCurrentChild("通常モード")) {
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(from_sync, "FromSyncMode", -1);
        changeChild("通常モード", &pack);
        sub_710050DDBC(1);
    }
}

// 0x710050ddbc
// NON_MATCHING: actor load and accessor-destructor branch scheduling differ.
void PriestBossActorNormalRoot::sub_710050DDBC(u32 value) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (sub_7100505BE4()->sub_71007194CC(&accessor)) {
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_48._30);
            _48._18 = value;
            _48._20.acquire(mActor, false);
        }
        _48.sub_710070DBB0(*accessor.getMessageTransceiverId(), false);
    }
}

}  // namespace uking::ai
