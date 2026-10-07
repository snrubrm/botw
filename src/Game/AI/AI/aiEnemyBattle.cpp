#include "Game/AI/AI/aiEnemyBattle.h"
#include <random/seadGlobalRandom.h>
#include "Game/Damage/dmgInfoManager.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "Game/AI/aiUnk_7100D8C538.h"
#include <limits>

namespace uking::ai {

EnemyBattle::EnemyBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsUpdateNoticeState_s) {
        auto* actor = mActor;
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    }
    _88 = testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1);
    m34(params);
}

bool EnemyBattle::m39() {
    if (!m40())
        return false;
    return sub_7100382558();
}

bool EnemyBattle::m40() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy || !(enemy->_e68.value <= std::numeric_limits<f32>::epsilon()))
        return false;
    sead::Vector3f target;
    // The original uses a signed comparison of the nearest-enemy count at DamageInfoMgr +0x5c0.
    if (dmg::DamageInfoMgr::instance() &&
        static_cast<s32>(dmg::DamageInfoMgr::instance()->get4f8()._c8) > 1 &&
        ksys::act::Attention::instance() &&
        !ksys::act::Attention::instance()->sub_7100D74114()) {
        mActor->getMtx().getTranslation(target);
        const f32 radius = *mDisplayCheckRadius_s;
        target.y += radius;
        if (!visibilityCheckMaybe(target, radius))
            return false;
    }
    m36(&target);
    return sub_710072DDB8(target, mActor->getMtx(), *mAttackAngle_s);
}

bool EnemyBattle::sub_7100382558() {
    const f32 base = *mGlobalNoAtkTime_s;
    const s32 random = *mGlobalNoAtkTimeRnd_s;
    const f32 extra = random >= 1 ? f32(sead::GlobalRandom::instance()->getS32Range(0, random)) : 0.0f;
    const s32 time = base + extra;
    if (time < 0)
        return true;
    if (!ksys::act::isPlayerProfile(&m35()))
        return true;
    return dmg::DamageInfoMgr::instance()->get4f8().sub_7100671A40(mActor, time);
}

bool EnemyBattle::sub_7100381D68() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    bool result;
    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->_e08._0, &accessor);
        if (accessor.sub_7100D1463C()) {
            result = true;
        } else {
            ksys::act::acquireActor(&m35(), &accessor);
            result = accessor.sub_7100D1463C();
        }
    }
    return result;
}

void EnemyBattle::calc_() {
    if (_88) {
        if (sub_7100381D68()) {
            const s32 time = sead::GlobalRandom::instance()->getU32(5) + 10;
            if (auto* enemy = static_cast<act::Enemy*>(mActor))
                enemy->_e68 = ksys::Timer(time, time);
        } else {
            _88 = false;
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("戦闘準備")) {
            if (child->isFailed()) {
                setFailed();
                return;
            }
            if (*mIsCheckLineReachable_s) {
                const sead::Vector3f target = sub_71005D9330(mActor);
                auto* nav = mActor->m45();
                const f32 tolerance = nav ? nav->_2a8 * nav->_2ac : 0.0f;
                sead::Vector3f out;
                if (!sub_710072F944(mActor, target, &out, tolerance, 3.0f)) {
                    setFailed();
                    return;
                }
            }
            if (!m42()) {
                bool x;
                {
                    ksys::act::acc::PlayerBase player;
                    ksys::act::acquireActor(&m35(), &player);
                    x = player.x_13();
                }
                if (!x) {
                    m38();
                    return;
                }
            }
            m37();
            return;
        }
        if (isCurrentChild("戦闘攻撃")) {
            const bool failed = child->isFailed();
            if (auto* enemy = static_cast<act::Enemy*>(mActor))
                enemy->startAttackInterval(*mAttackIntervalIntensity_s);
            if (failed) {
                setFailed();
                return;
            }
            if (*mIsCheckLineReachable_s) {
                const sead::Vector3f target = sub_71005D9330(mActor);
                auto* nav = mActor->m45();
                const f32 tolerance = nav ? nav->_2a8 * nav->_2ac : 0.0f;
                sead::Vector3f out;
                if (!sub_710072F944(mActor, target, &out, tolerance, 3.0f)) {
                    setFailed();
                    return;
                }
            }
            m37();
        }
        return;
    }

    if (child->isChangeable() && isCurrentChild("戦闘準備")) {
        if (!mActor) {
            setFailed();
            return;
        }
        if (m41() && m39()) {
            m38();
            return;
        }
    }
    sead::Vector3f pos;
    m36(&pos);
    child->setDynamicParam(pos, "TargetPos");
}

bool EnemyBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyBattle::leave_() {
    auto* actor = mActor;
    if (sead::IsDerivedFrom<act::Enemy>(actor) && static_cast<act::Enemy*>(actor)->_e84.isOnBit(0))
        sub_7100381ED4();
}

void EnemyBattle::loadParams_() {
    getStaticParam(&mRetFrmGrdAtkTimer_s, "RetFrmGrdAtkTimer");
    getStaticParam(&mRetFrmGrdAtkPrcTimer_s, "RetFrmGrdAtkPrcTimer");
    getStaticParam(&mRetFrmDmgAtkTimer_s, "RetFrmDmgAtkTimer");
    getStaticParam(&mGlobalNoAtkTime_s, "GlobalNoAtkTime");
    getStaticParam(&mGlobalNoAtkTimeRnd_s, "GlobalNoAtkTimeRnd");
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
    getStaticParam(&mDisplayCheckRadius_s, "DisplayCheckRadius");
    getStaticParam(&mIsUpdateNoticeState_s, "IsUpdateNoticeState");
    getStaticParam(&mIsCheckLineReachable_s, "IsCheckLineReachable");
}

void EnemyBattle::m36(sead::Vector3f* pos) {
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(&m35(), &acc);
    acc.getActorMtx().getTranslation(*pos);
}

void EnemyBattle::m37() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    m36(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("戦闘準備", &pack);
}

void EnemyBattle::m38() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    m36(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    m43(&pack);
    changeChild("戦闘攻撃", &pack);
}

ksys::act::BaseProcLink& EnemyBattle::m35() {
    auto* link = sub_71005D9050(mActor);
    if (link != nullptr)
        return *link;
    return ksys::act::getDummyBaseProcLink();
}

bool EnemyBattle::sub_7100381E7C() {
    ksys::act::acc::PlayerBase player;
    ksys::act::acquireActor(&m35(), &player);
    return player.x_13();
}

void EnemyBattle::sub_7100381E58(s32 time) {
    if (time < 0)
        return;
    auto* enemy = static_cast<act::Enemy*>(mActor);
    if (enemy)
        enemy->_e68 = ksys::Timer(time, time);
}

void EnemyBattle::sub_7100381ED4() {
    auto* enemy = static_cast<act::Enemy*>(mActor);
    if (enemy)
        enemy->startAttackInterval(*mAttackIntervalIntensity_s);
}

}  // namespace uking::ai
