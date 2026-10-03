#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

// NON_MATCHING: instruction scheduling / register allocation around the second sender (_198)
EnemyRoot::EnemyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRoot::~EnemyRoot() {
    if (_38) {
        delete _38;
        _38 = nullptr;
    }
}

bool EnemyRoot::init_(sead::Heap* heap) {
    const float* fall_height{};
    getStaticParam(&fall_height, "FallHeight");
    if (*fall_height >= 0.0f) {
        _38 = new (heap) Unk_7100702370(mActor, fall_height);
        if (!_38)
            return false;
    }
    return true;
}

void EnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_38)
        _38->sub_7100702370();
    *mIsTrgChangeUnderWaterState_a = false;
    m34(params);
}

void EnemyRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRoot::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOutOfWaterOffset_s, "OutOfWaterOffset");
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mSmallSpreadDist_s, "SmallSpreadDist");
    getStaticParam(&mFortressTag_s, "FortressTag");
    getStaticParam(&mIgnoreHell_s, "IgnoreHell");
    getMapUnitParam(&mIsNearCreate_m, "IsNearCreate");
    getMapUnitParam(&mEquipItem1_m, "EquipItem1");
    getMapUnitParam(&mEquipItem2_m, "EquipItem2");
    getMapUnitParam(&mEquipItem3_m, "EquipItem3");
    getMapUnitParam(&mEquipItem4_m, "EquipItem4");
    getMapUnitParam(&mRideHorseName_m, "RideHorseName");
    getAITreeVariable(&mCreateDeadConditionType_a, "CreateDeadConditionType");
    getAITreeVariable(&mForceSealSilentKillCount_a, "ForceSealSilentKillCount");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

void EnemyRoot::m37() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.resetBit(13);
    changeChild("リアクション");
}

void EnemyRoot::m39() {
    if (isCurrentChild("通常"))
        *mIsTrgChangeUnderWaterState_a = true;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.resetBit(13);
    changeChild("水中");
}

void EnemyRoot::m40() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.resetBit(13);
    changeChild("所持");
}

void EnemyRoot::m43() {
    auto* actor = mActor;
    if (isCurrentChild("騎乗") || isCurrentChild("リアクション") || isCurrentChild("近接湧出")) {
        ksys::act::disableAttClient(actor, "SleepSilentKill");
        ksys::act::disableAttClient(actor, "AwakeSilentKill");
        return;
    }

    auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor);
    if (!enemy)
        return;

    if (enemy->_e84.isOnBit(8)) {
        ksys::act::enableAttClient(actor, "SleepSilentKill");
        ksys::act::disableAttClient(actor, "AwakeSilentKill");
        return;
    }

    ksys::act::disableAttClient(actor, "SleepSilentKill");
    auto& target = sub_71005D94AC(actor);
    if (*mForceSealSilentKillCount_a > 0 ||
        actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_1000000) ||
        (target == ksys::act::PlayerInfo::getSomeProcLink() &&
         (!enemyTeamStuff(mActor, &target) || enemy->_e84.isOnBit(1)))) {
        ksys::act::disableAttClient(actor, "AwakeSilentKill");
    } else {
        ksys::act::enableAttClient(actor, "AwakeSilentKill");
    }
}

void EnemyRoot::m42() {
    _1c8 = false;
    changeChild("奈落");
}

bool EnemyRoot::m35() {
    return sub_71005D6E28(mActor);
}

void EnemyRoot::sub_71003B5644() {
    *mIsTrgChangeUnderWaterState_a = false;
    if (auto* awareness = mActor->getAwareness()) {
        const u32 flags = awareness->_318;
        const bool castle = ksys::gdt::getFlag_IsInHyruleCastleArea();
        if (flags & 8) {
            if (castle)
                awareness->_318 &= ~8u;
        } else if (!castle) {
            awareness->_318 |= 8;
        }
    }
}

bool EnemyRoot::sub_71003B5804(bool a1) {
    if (_e8._30) {
        if (sub_71005DC444(mActor)) {
            _e8.x();
            m40();
            return true;
        }
        if (!mActor->getConnectedCalcParent())
            _e8.x();
    } else if (a1) {
        ksys::act::enableAttClient(mActor, "Grab");
    }
    return false;
}

}  // namespace uking::ai
