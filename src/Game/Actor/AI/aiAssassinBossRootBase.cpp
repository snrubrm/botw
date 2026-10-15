#include "Game/Actor/AI/aiAssassinBossRootBase.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

bool Unk_71023d7eb0::m2(const ksys::Message& message) {
    if (message.getType() != 0x800007d)
        return false;

    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023d7ee0::m2(const ksys::Message& message) {
    if (message.getType() != 0x800007e)
        return false;

    _30 = true;
    _18 = message.getSource();
    return true;
}

void Unk_71023d7e40::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          act::DamageCallbackInfo* a6) {
    if (*a1 < 1)
        return;

    auto* damage_manager = sead::DynamicCast<act::DamageManager>(mDamageManager);
    if (!damage_manager)
        return;
    auto* enemy = sead::DynamicCast<act::Enemy>(damage_manager->mActor);
    if (!enemy || enemy->_e84.isOnBit(3))
        return;

    const s32* life_ptr = mDamageManager->mActor->getLife();
    s32 life = life_ptr ? *life_ptr : 1;
    if (enemy->getLifeRecoverInfo()) {
        auto* info = enemy->getLifeRecoverInfo();
        life += info->mExtraHp1;
        info->onApplyDamage_0();
    }

    if (life - *a1 <= _24)
        *a1 = sead::Mathi::max(life - 1 - _24, 0);
}

void Unk_71023d7e78::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          act::DamageCallbackInfo* a6) {
    if (*a1 < 1)
        return;

    auto* damage_manager = sead::DynamicCast<act::DamageManager>(mDamageManager);
    if (!damage_manager)
        return;

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(damage_manager->m37(), &accessor);
    if (accessor.getName() == "AssassinRockBall") {
        *a1 = _24;
        *a5 = 22;
    }
}

AssassinBossRootBase::AssassinBossRootBase(const InitArg& arg) : EnemyRoot(arg) {}

AssassinBossRootBase::~AssassinBossRootBase() = default;

bool AssassinBossRootBase::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void AssassinBossRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
    if (isRootAiParamINot5()) {
        _1e8.x();
        _220.x();
    }

    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    player.runeMgrCheckCanUseSquareBomb();
    sub_71005D8DE8(mActor, uking::act::PlayerInfo::getSomeProcLink(), &player.getActorMtx(),
                   &player.getPreviousPos());

    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e90 = 4;

    _1e8.x();
    _220.x();
    _258 = 10.0f;
    if (!_288.mDamageManager) {
        _288._24 = *mParams.mRockBallDamage_s;
        setDamageCallbackTiming(mActor, 2, &_288);
    }
    if (auto* controller = mActor->getCharacterController())
        controller->mFlags.set(0xc00);
}

void AssassinBossRootBase::calc_() {
    sub_71003B5644();

    if (isCurrentChild("撤退")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            if (_220._30) {
                m47();
                _1e8.x();
                _258 = 10.0f;
            } else {
                xlinkSearchAndEmit(mActor, "Doron", 2, nullptr);
                mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
            }
            _220.x();
        }
        return;
    }

    if (_220._30) {
        _1e8.x();
        _220.x();
    }

    if (_1e8._30)
        ksys::Timer::update(&_258, -1.0f);
    else
        _258 = 10.0f;

    if (isCurrentChild("強制ワープ回避")) {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        sead::Vector3f pos;
        player.getActorMtx().getTranslation(pos);
        getCurrentChild()->setDynamicParam(pos, "TargetPos");
        if (_1c8) {
            m42();
            return;
        }
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            changeChild("通常");
        else
            EnemyRoot::calc_();
        return;
    }

    if (isCurrentChild("リアクション")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            changeChild("リアクション復帰");
        else
            EnemyRoot::calc_();
        return;
    }

    const bool is_recovering = isCurrentChild("リアクション復帰");
    auto* child = getCurrentChild();
    if (is_recovering) {
        if (child->isFinished() || child->isFailed()) {
            m38();
            return;
        }
        if (_258 <= 0) {
            changeChild("撤退");
            _1e8.x();
            return;
        }
        if (m45())
            m46();
        return;
    }

    if (child->isChangeable() && _258 <= 0) {
        changeChild("撤退");
        _1e8.x();
        return;
    }
    if (m45())
        m46();
    else
        EnemyRoot::calc_();
}

// NON_MATCHING: parameter-pack and temporary-string lifetimes use different scheduling.
void AssassinBossRootBase::sub_710031BBC4(const sead::SafeString& part_name,
                                         const sead::SafeString& actor_name, s32 idx,
                                         sead::Heap* heap) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;
    sead::FixedSafeString<32> key;
    key.format("%s%d", part_name.cstr(), idx);
    auto& parts = enemy->_1128;
    parts.sub_7100D3CED8(key, heap);
    auto& link = parts.getActorPartsActor(key);
    if (link.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        const auto& name = accessor.getName();
        name.cstr();
        name.cstr();
        actor_name.cstr();
        return;
    }
    ksys::act::InstParamPack pack;
    pack.getBuffer().addPosition(mActor->getMtx().getTranslation());
    pack.getBuffer().addRotation(mActor->getMtx().getRotation());
    pack.getBuffer().add(9999, "Count");
    auto* created = ksys::act::ActorCreator::instance()->createActor(
        actor_name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, true, false);
    if (!created)
        return;
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(created))
        bullet->sub_710000497C(enemy);
    parts.sub_7100D3D108(key, created);
}

void AssassinBossRootBase::sub_710031C2C8(s32 threshold) {
    _260._24 = threshold;
    setDamageCallbackTiming(mActor, 4, &_260);
}

void AssassinBossRootBase::sub_710031BB3C() {
    sub_71005DA114(mActor, &_260);
}

void AssassinBossRootBase::leave_() {
    EnemyRoot::leave_();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e90 = 1;

    sub_71005DA114(mActor, &_260);
    if (auto* controller = mActor->getCharacterController()) {
        sub_71007377D4(controller, 0.0f);
        sub_7100738660(controller, 0.0f);
    } else if (auto* body = mActor->getMainBody()) {
        sub_71007379FC(body, 0.0f);
        sub_7100738898(body, 0.0f);
    }
    if (_288.mDamageManager)
        sub_71005DA114(mActor, &_288);
}

bool AssassinBossRootBase::handleMessage_(const ksys::Message* message) {
    if (EnemyRoot::handleMessage_(message))
        return true;
    if (_1e8.m2(*message))
        return true;
    return _220.m2(*message);
}

bool AssassinBossRootBase::m45() {
    return false;
}

void AssassinBossRootBase::m46() {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    sead::Vector3f pos;
    player.getActorMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("強制ワープ回避", &params);
}

void AssassinBossRootBase::m47() {
    changeChild("呼ばれ");
}

void AssassinBossRootBase::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mParams.mChangeModeLifeRatio_s, "ChangeModeLifeRatio");
    getStaticParam(&mParams.mRockBallDamage_s, "RockBallDamage");
}

}  // namespace uking::ai
