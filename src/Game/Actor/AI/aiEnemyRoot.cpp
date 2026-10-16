#include "Game/Actor/AI/aiEnemyRoot.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Utils/Thread/Message.h"

bool sub_71005E19F8(ksys::act::Actor* actor, Unk_7102357d20* sender, const char* fortress_tag);

namespace uking::ai {

// NON_MATCHING: load scheduling and register allocation in the home-position distance calculation.
bool EnemyRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003) {
        sead::Vector3f home;
        mActor->getHomePos(&home);
        if (sead::Vector2f(home.x - mActor->getMtx().m[0][3],
                          home.z - mActor->getMtx().m[2][3]).length() < *mSpreadDist_s) {
            auto* actor = mActor;
            sub_71005E19F8(actor, &_198, mFortressTag_s.cstr());
        }
        return false;
    }
    if (message->getType() == 0x80000ca) {
        _1cc.sub_7100700844(message);
        return false;
    }
    if (m44()) {
        auto* actor = mActor;
        if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) || _e8._30)
            return false;
        if (_e8.m2(*message)) {
            _e8.sub_710070B5A0(actor);
            return true;
        }
    }
    if (!*mIgnoreHell_s && message->getType() == 0x3000007) {
        _1c8 = true;
        return true;
    }
    return false;
}

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

// NON_MATCHING: initial-state branches and water-height operand loads are reordered.
void EnemyRoot::m34(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* ride_info = actor->getPlayerRideInfo();
    const u32 initial_state = actor->getRootAi()->getI();
    actor = mActor;
    if (actor->getRootAi()->getI() != 5 && *mIsNearCreate_m) {
        sub_71005D8DE8(actor, uking::act::PlayerInfo::getSomeProcLink(), nullptr, nullptr);
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
        changeChild("近接湧出");
    } else if (ride_info && (ride_info->_30 & 1)) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(actor))
            enemy->_e84.setBit(13);
        changeToRide();
    } else if (*mInWaterDepth_s > 0.0f && actor->get68f() &&
               actor->get6f0() - actor->getMtx().m[1][3] > *mInWaterDepth_s) {
        m39();
    } else if (initial_state == 10) {
        sub_710073DCB4(actor, *mCreateDeadConditionType_a);
        changeChild("死亡生成");
    } else if (initial_state == 6) {
        changeChild("呼ばれ");
    } else {
        m38();
    }
}

// NON_MATCHING: block layout; the original jumps from the dead-enemy test (life < 1) straight to the child
// checks, ours keeps a flag and places the spread code after the child checks.
void EnemyRoot::calc_() {
    sub_71003B5644();
    _1cc.sub_71007008E0(mActor);

    if (isCurrentChild("奈落")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            _1c8 = false;
            m38();
            return;
        }
    } else if (_1c8) {
        m42();
        return;
    }

    if (_38) {
        if (isCurrentChild("所持"))
            _38->_14 |= 4;
        else
            _38->_14 &= ~4;
        _38->sub_7100702384();
    }

    auto* actor = mActor;
    m43();

    if (auto* damage_mgr = sub_710072BA90(mActor); damage_mgr && damage_mgr->_216.isOnBit(1)) {
        bool spread = true;
        const float* spread_dist;
        if (damage_mgr->checkDamageFlags(10)) {
            auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor);
            if (enemy && enemy->_e84.isOnBit(8)) {
                auto* life = actor->getLife();
                if (life && *life < 1)
                    spread = false;
            }
            spread_dist = mSmallSpreadDist_s;
        } else if (damage_mgr->checkDamageFlags(0)) {
            spread_dist = mSmallSpreadDist_s;
        } else {
            spread_dist = mSpreadDist_s;
        }

        const f32 dist = *spread_dist;
        if (spread && dist > 0.0f) {
            sead::Matrix34f mtx;
            damage_mgr->m35(&mtx);
            if (damage_mgr->getAttacker()->hasProc()) {
                auto* self = mActor;
                auto* attacker = damage_mgr->getAttacker();
                {
                    sead::ScopedLock<sead::JobQueueLock> lock(&_128._18.mLock);
                    _128._18._0.acquire(self, false);
                    _128._18._10 = *attacker;
                    _128._18._20 = mtx;
                }

                if (auto* awareness = mActor->getAwareness()) {
                    const sead::Vector3f pos = mActor->getMtx().getTranslation();
                    Unk_7102451448 filter;
                    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
                        if ((entry->_58.getTranslation() - pos).squaredLength() < dist * dist) {
                            ksys::act::ActorLinkConstDataAccess accessor;
                            ksys::act::acquireActor(&entry->_0.mLink, &accessor);
                            _128.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
                        }
                    }
                }

                sead::Vector3f home;
                mActor->getHomePos(&home);
                if (sead::Vector2f(home.x - mActor->getMtx().m[0][3],
                                   home.z - mActor->getMtx().m[2][3])
                        .length() < dist) {
                    sub_71005E1884(mActor, &_128, mFortressTag_s.cstr());
                }
            }
        }
    }

    auto* child = getCurrentChild();
    const bool done = child->isFinished() || child->isFailed();
    if (done || !m36()) {
        const bool in_water = m41();
        const bool changeable = done || isChangeable();
        if (m35()) {
            m37();
            return;
        }
        if (isCurrentChild("所持")) {
            ksys::act::disableAttClient(mActor, "Grab");
        } else {
            if (in_water && changeable &&
                !(*mInWaterDepth_s > 0.0f && mActor->get68f() &&
                  mActor->get6f0() - mActor->getMtx().m[1][3] >
                      *mInWaterDepth_s - *mOutOfWaterOffset_s)) {
                if (_38 && (_38->_14 & 2))
                    changeChild("落下");
                else
                    m38();
                return;
            }
            if (!in_water && changeable && *mInWaterDepth_s > 0.0f && mActor->get68f() &&
                mActor->get6f0() - mActor->getMtx().m[1][3] > *mInWaterDepth_s) {
                m39();
                return;
            }
            if (isCurrentChild("通常") && _38 && (_38->_14 & 2)) {
                changeChild("落下");
                return;
            }
            auto* ride_info = actor->getPlayerRideInfo();
            if (ride_info && (ride_info->_30 & 1)) {
                ksys::act::disableAttClient(mActor, "Grab");
                if (!isCurrentChild("騎乗") &&
                    (child->isChangeable() || child->isFinished() || child->isFailed())) {
                    changeToRide();
                    return;
                }
            }
            if (sub_71003B5804(true))
                return;
        }
    }

    if (child->isFinished() || child->isFailed())
        m38();
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
        (target == uking::act::PlayerInfo::getSomeProcLink() &&
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

void EnemyRoot::changeToRide() {
    ksys::act::ai::InlineParamPack pack;
    if (auto* info = mActor->getPlayerRideInfo()) {
        auto* horse = sead::DynamicCast<ksys::act::Actor>(info->_18.getProc(nullptr, info->mActor));
        pack.acquireActor(horse, "Horse", -1);
    }
    changeChild("騎乗", &pack);
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

const sead::SafeString& EnemyRoot::sub_71003B5E54(int index) const {
    switch (index) {
    case 0:
        return mEquipItem1_m;
    case 1:
        return mEquipItem2_m;
    case 2:
        return mEquipItem3_m;
    case 3:
        return mEquipItem4_m;
    default:
        return mEquipItem1_m;
    }
}

}  // namespace uking::ai
