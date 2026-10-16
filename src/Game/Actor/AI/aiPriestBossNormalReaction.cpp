#include "Game/Actor/AI/aiPriestBossNormalReaction.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

// 0x7100528494
void Unk_7102414f60::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          act::DamageCallbackInfo* a6) {
    if (*a5 == -1)
        return;
    auto* enemy = sead::DynamicCast<act::Enemy>(mDamageManager->mActor);
    if (enemy && enemy->_868 && enemy->_868->sub_71006ED9EC()) {
        auto* info = sead::DynamicCast<act::DamageCallbackInfo>(a6);
        if (info)
            info->mFlags |= 0x200000;
    }
}

PriestBossNormalReaction::PriestBossNormalReaction(const InitArg& arg)
    : EnemyDefaultReaction(arg), _a8() {}

PriestBossNormalReaction::~PriestBossNormalReaction() = default;

bool PriestBossNormalReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void PriestBossNormalReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
    if (auto* mgr = mActor->getDamageMgr())
        mgr->addDamageCallback(0, &_80);
    _c9 = false;
    *mPriestBossUrbosasFuryEShock_a = false;
}

// 0x7100527ed0
void PriestBossNormalReaction::calc_() {
    EnemyDefaultReaction::calc_();

    if (!_c8) {
        auto* damage_mgr = sead::DynamicCast<act::DamageManager>(mActor->getDamageMgr());
        if (damage_mgr && s32(damage_mgr->getDamage()) > 0 && damage_mgr->checkDamageFlags(0x16))
            _c8 = true;
    }
    if (_c8 && *mPriestBossUrbosasFuryEShock_a) {
        if (!_a8.sub_7101241B6C())
            xlinkSearchAndEmit(mActor, "ElectricShock", 2, &_a8);
    } else if (_a8.sub_7101241B6C()) {
        _a8.fadeXLink();
    }

    if (sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a))) {
        auto* unit =
            sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
        if (unit->isFlagOn(Unk_7102450fa8::Flag::_16))
            _c9 = true;
    }

    if (!*mIsUseQuickRecover_s || !_c9)
        return;
    if (!isCurrentChild("小ダメージ") && !isCurrentChild("ふっとび"))
        return;

    auto* ragdoll = sead::DynamicCast<act::Enemy>(mActor)->_868;
    if (ragdoll->sub_71006ED9EC()) {
        if (ragdoll->sub_71006EE15C()) {
            _c9 = false;
            ksys::act::ai::InlineParamPack pack;
            pack.addBool(true, "IsFromRagdoll", -1);
            changeChild("クイック復帰", &pack);
        }
        return;
    }

    if (mActor->getASList()->x_1(0, 0) == "LargeDamageLoop") {
        _c9 = false;
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(false, "IsFromRagdoll", -1);
        changeChild("クイック復帰", &pack);
    }
}

void PriestBossNormalReaction::leave_() {
    EnemyDefaultReaction::leave_();
    if (_a8.sub_7101241B6C())
        _a8.fadeXLink();
    if (auto* mgr = mActor->getDamageMgr())
        mgr->removeDamageCallback(&_80);
}

void PriestBossNormalReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mIsUseQuickRecover_s, "IsUseQuickRecover");
    getAITreeVariable(&mPriestBossUrbosasFuryEShock_a, "PriestBossUrbosasFuryEShock");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

bool PriestBossNormalReaction::m34(act::DamageManagerBase* damage_mgr, int damage_type) {
    return false;
}

void PriestBossNormalReaction::m35(act::DamageManagerBase* damage_mgr, int damage_type, bool x,
                                   ksys::act::ai::InlineParamPack* params) {
    if (damage_mgr->checkDamageFlags(22)) {
        _c8 = true;
        changeChild("ウルボザの怒り", params);
        return;
    }
    _c8 = false;
    EnemyDefaultReaction::m35(damage_mgr, damage_type, x, params);
}

bool PriestBossNormalReaction::m45() {
    return false;
}

}  // namespace uking::ai
