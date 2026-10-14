#include "Game/AI/AI/aiGanonReaction.h"
#include "Game/AI/aiUnk_71002C52DC.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actLastBoss.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ai {

GanonReaction::GanonReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

GanonReaction::~GanonReaction() = default;

bool GanonReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

// NON_MATCHING: the damage switch uses one bit mask instead of a mask and a separate range check.
void GanonReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool default_reaction = EnemyDefaultReaction::m45();
    auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
    if (default_reaction) {
        if (boss) {
            boss->sub_71002C5E58(false);
            boss->update();
            boss->sub_71002C6930();
            boss->stunEnd();
            sub_71007A36BC(mActor);
        }
    } else {
        if (!boss) {
            setFailed();
            return;
        }
        if ((mActor->get1a0() ||
             (mActor->getMapObject() &&
              mActor->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000)) ||
             (sub_71002C52DC(boss, 0.5f) && boss->_14e8.isOffBit(5))) &&
            boss->_14f8._30.isOffBit(4) && boss->_14e8.isOffBit(10) && boss->_14e4 == 0) {
            boss->_14e8.setBit(14);
            boss->sub_71006DD92C(true);
            changeChild("デモ待ち大ダメージ");
            return;
        }
        if (auto* damage_mgr = sub_710072BA90(mActor)) {
            switch (damage_mgr->getField54()) {
            case 9:
            case 10:
            case 11:
            case 12:
            case 14:
            case 21:
            case 22:
                EnemyDefaultReaction::m44();
                changeChild("小ダメージ");
                return;
            default:
                break;
            }
        }
        if (boss->getActorPartsActor("ShockWave").hasProcInCalcState()) {
            auto* shock = sead::DynamicCast<ksys::act::Actor>(
                boss->getActorPartsActor("ShockWave").getProc(nullptr, nullptr));
            if (shock) {
                const s32 num = getNumAttackInfoMaybe(shock);
                for (s32 i = 0; i < num; ++i) {
                    auto* info = getAttackInfo(shock, i);
                    if (info && (info->_18 & 2)) {
                        changeChild("ショック");
                        return;
                    }
                }
            }
        }
    }
    EnemyDefaultReaction::enter_(params);
}

void GanonReaction::leave_() {
    EnemyDefaultReaction::leave_();
    _63 = false;
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor))
        boss->_14f8._30.resetBit(7);
    sub_7100739918(mActor);
}

void GanonReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
}

void GanonReaction::calc_() {
    if (!getCurrentChild())
        return;
    if (isCurrentChild("デモ待ち大ダメージ"))
        return;

    sub_7100739900(mActor);
    if (auto* damage_mgr = sub_710072BA90(mActor)) {
        switch (damage_mgr->getField54()) {
        case 9:
        case 10:
        case 11:
        case 12:
        case 14:
            EnemyDefaultReaction::m44();
            changeChild("小ダメージ");
            return;
        case 13:
            return;
        default:
            break;
        }
    }
    EnemyDefaultReaction::calc_();
}

bool GanonReaction::m34(act::DamageManagerBase* damage_mgr, int damage_type) {
    if (_63)
        return false;
    return EnemyDefaultReaction::m34(damage_mgr, damage_type);
}

bool GanonReaction::m36(int damage_type) {
    _63 = true;
    return false;
}

void GanonReaction::m40(ksys::act::ai::InlineParamPack* params) {
    changeChild("小ダメージ");
}

}  // namespace uking::ai
