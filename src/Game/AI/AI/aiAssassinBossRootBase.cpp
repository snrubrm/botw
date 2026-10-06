#include "Game/AI/AI/aiAssassinBossRootBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
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
                          dmg::DamageCallbackInfo* a6) {
    if (*a1 < 1)
        return;

    auto* damage_manager = sead::DynamicCast<dmg::DamageManager>(mDamageManager);
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
                          dmg::DamageCallbackInfo* a6) {
    if (*a1 < 1)
        return;

    auto* damage_manager = sead::DynamicCast<dmg::DamageManager>(mDamageManager);
    if (!damage_manager)
        return;

    ksys::act::ActorConstDataAccess accessor;
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
    sub_71005D8DE8(mActor, ksys::act::PlayerInfo::getSomeProcLink(), &player.getActorMtx(),
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
