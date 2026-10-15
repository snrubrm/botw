#include "Game/Actor/AI/aiCapturedActorRoot.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace uking::ai {

// NON_MATCHING: the original addresses everything from `this` (we keep this+0x38 in a register)
CapturedActorRoot::CapturedActorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void CapturedActorRoot::applyParams() {
    auto* root_ai = mActor->getRootAi();
    _f4 = (root_ai && root_ai->getI() == 4) || *mIsLocatorCreate_m;
    if (mActor->hasPlacementLinkWithTypeFreeze())
        _f5 = true;

    bool* is_amiibo = nullptr;
    if (mActor->getRootAi()->getAITreeVariable(&is_amiibo, "IsAmiibo"))
        _f6 = *is_amiibo;
}

bool CapturedActorRoot::init_(sead::Heap* heap) {
    applyParams();
    return true;
}

// NON_MATCHING: timer/string temporaries and initial-state dispatch use different scheduling.
void CapturedActorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* awareness = actor->getAwareness())
        awareness->enable();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F63700(false);
    ksys::act::enableAttClient(actor, "NameBalloon");
    ksys::act::disableAttClient(actor, "NoticeDo");
    _c4.reset(f32(*mInvalidTgtTimerVal_s));
    _d0.reset(f32(*mInvalidTgtTimerVal_s));
    _38._28 = *mInvalidTgtTimerVal_s > 0;
    if (auto* atk = sead::DynamicCast<ksys::act::ActorAtk>(mActor->getAtk()))
        atk->sub_710079E344(&_38);
    _dc = 45.0f;
    _e0 = 45;
    _e4 = 45;
    f32 duration = 60.0f;
    f32 random_duration = 240.0f;
    if (!*mIsPlayerPut_m && !*mIsDrop_a && !*mIsCreateDead_m && mActor->sub_7100EE1E94()) {
        duration = 15.0f;
        random_duration = 30.0f;
    }
    _e8.reset(duration + random_duration * sead::GlobalRandom::instance()->getF32());
    const auto& mtx = mActor->getMtx();
    sead::Vector3f forward;
    mtx.getBase(forward, 2);
    _b8 = mtx.getTranslation() - forward * 5.0f;
    actor->sub_71011C8B04(actor->getMtx());
    if (actor->getModel())
        actor->getASList()->sub_710115BAF8("Root");
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->_e84.isOnBit(3)) {
        m40();
    } else if (_f6) {
        m41();
    } else if (*mIsPlayerPut_m) {
        m42();
    } else if (*mIsDrop_a) {
        m43();
    } else if (*mIsCreateDead_m) {
        m40();
    } else if (_f4) {
        m37();
    } else if (_f5) {
        m44();
    } else {
        m38();
    }
}

void CapturedActorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CapturedActorRoot::calc_() {
    _c4.update();
    _d0.update();
    _38._28 = !(_d0.value <= sead::Mathf::epsilon());
    if (isCurrentChild("死亡"))
        return;

    if (m35()) {
        m40();
        return;
    }

    if (isChangeable()) {
        if (m34()) {
            m39();
            return;
        }
        if (!*mIsPlayerPut_m && !*mIsDrop_a && !*mIsCreateDead_m && mActor->sub_7100EE1E94()) {
            _e8.update();
            auto* actor = mActor;
            if (auto* lod = actor->getLodState())
                _e8.value += lod->_40 * _e8.rate;
            if (_e8.value <= sead::Mathf::epsilon())
                actor->deleteEx(ksys::act::Actor::DeleteType::_1,
                                ksys::act::BaseProc::DeleteReason::_0, nullptr);
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("ロケーターわき出し")) {
            m38();
        } else if (isCurrentChild("逃走") && m36()) {
            mActor->deleteEx(ksys::act::Actor::DeleteType::_1,
                            ksys::act::BaseProc::DeleteReason::_0, nullptr);
        }
    }
}

void CapturedActorRoot::loadParams_() {
    getStaticParam(&mInvalidTgtTimerVal_s, "InvalidTgtTimerVal");
    getStaticParam(&mInvalidEscapeTimerVal_s, "InvalidEscapeTimerVal");
    getStaticParam(&mIsDeleteWhenDead_s, "IsDeleteWhenDead");
    getStaticParam(&mIsDeadWhenPut_s, "IsDeadWhenPut");
    getStaticParam(&mIsEscapeWhenPut_s, "IsEscapeWhenPut");
    getStaticParam(&mIsDeadWhenDrop_s, "IsDeadWhenDrop");
    getMapUnitParam(&mIsPlayerPut_m, "IsPlayerPut");
    getMapUnitParam(&mIsLocatorCreate_m, "IsLocatorCreate");
    getMapUnitParam(&mIsCreateDead_m, "IsCreateDead");
    mActor->getRootAi()->getAITreeVariable2(&mIsDrop_a, "IsDrop");
}

// NON_MATCHING: the original keeps the sensor pointer in a register and takes &_8 afterwards (we pre-index the size load); register allocation of the result
// 0x7100342ebc
bool CapturedActorRoot::m34() {
    auto* actor = mActor;
    if (sub_71007A2604(actor)) {
        const s32 count = sub_71007A26AC(actor);
        for (s32 i = 0; i < count; ++i) {
            if (auto* info = sub_71007A255C(actor, i)) {
                info->_58.getTranslation(_b8);
                return true;
            }
        }
    }
    if (auto* awareness = actor->getAwareness()) {
        ksys::act::Unk_7100d78e50* entry = nullptr;
        auto* sensor1 = awareness->_260[1];
        if ((sensor1 && sensor1->_8.size() > 0 &&
             (entry = ksys::act::sub_7100D78E30(&sensor1->_8, 0)) && entry->_a0 == 2) ||
            (awareness->_260[2] && awareness->_260[2]->_8.size() > 0 &&
             (entry = ksys::act::sub_7100D78E30(&awareness->_260[2]->_8, 0)))) {
            entry->_58.getTranslation(_b8);
            return true;
        }
        if (auto* sensor3 = awareness->_260[3]) {
            if (sensor3->_8.size() != 0) {
                Unk_71023dcc20 filter;
                if (auto* found = ksys::act::sub_7100D7EEE8(&sensor3->_8, &filter)) {
                    found->_58.getTranslation(_b8);
                    return true;
                }
            }
        }
    }
    return false;
}

// NON_MATCHING: the original tests the damage type as a 30..34 range minus 32 (ccmp) instead of a
// bit mask
bool CapturedActorRoot::m35() {
    if (isCurrentChild("死亡"))
        return false;

    auto* damage_mgr = sub_710072BA90(mActor);
    if (!damage_mgr)
        return false;

    const s32 damage_type = damage_mgr->getField54();
    const s32* life = mActor->getLife();
    if (life && *life <= 0)
        return true;

    switch (damage_type) {
    case 30:
    case 31:
    case 33:
    case 34:
        return true;
    default:
        return false;
    }
}

void CapturedActorRoot::m37() {
    if (auto* awareness = mActor->getAwareness()) {
        if (auto* sensor = awareness->_260[1])
            sensor->_48 = 0;
    }
    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(home_pos, "TargetPos", -1);
    changeChild("ロケーターわき出し", &params);
}

void CapturedActorRoot::m38() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(home_pos, "TargetPos", -1);
    changeChild("通常行動", &params);
}

void CapturedActorRoot::m39() {
    if (!(_c4.value <= sead::Mathf::epsilon()))
        return;

    if (m36()) {
        _dc = _e0 == _e4 ? _e0 : sead::GlobalRandom::instance()->getS32Range(_e0, _e4);
        mActor->getLodState()->mFlags10.set(0x40);
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_8000);
    }
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_8000000);

    ksys::act::ai::InlineParamPack params;
    params.addVec3(_b8, "TargetPos", -1);
    changeChild("逃走", &params);
    _c4 = ksys::Timer(*mInvalidEscapeTimerVal_s, *mInvalidEscapeTimerVal_s);
}

bool CapturedActorRoot::sub_710034342C() {
    if (!(_c4.value <= sead::Mathf::epsilon()))
        return false;

    if (m36()) {
        _dc = _e0 == _e4 ? _e0 : sead::GlobalRandom::instance()->getS32Range(_e0, _e4);
        mActor->getLodState()->mFlags10.set(0x40);
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_8000);
    }
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_8000000);
    _c4 = ksys::Timer(*mInvalidEscapeTimerVal_s, *mInvalidEscapeTimerVal_s);
    return true;
}

void CapturedActorRoot::sub_7100343510() {
    if (m36()) {
        _dc = _e0 == _e4 ? _e0 : sead::GlobalRandom::instance()->getS32Range(_e0, _e4);
        mActor->getLodState()->mFlags10.reset(0x40);
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000);
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000);
    }
    m38();
}

void CapturedActorRoot::m40() {
    if (isCurrentChild("死亡"))
        return;

    if (*mIsDeleteWhenDead_s)
        ksys::act::disableAllAttClients(mActor);
    else
        ksys::act::enableAttClient(mActor, "NoticeDo");
    changeChild("死亡");
}

void CapturedActorRoot::m41() {
    m38();
}

void CapturedActorRoot::m42() {
    if (*mIsDeadWhenPut_s || *mIsCreateDead_m) {
        m40();
    } else if (*mIsEscapeWhenPut_s) {
        _c4 = ksys::Timer(-1.0f, -1.0f);
        m39();
    } else {
        m38();
    }
}

void CapturedActorRoot::m43() {
    if (*mIsDeadWhenDrop_s || *mIsCreateDead_m)
        m40();
    else
        m38();
}

void CapturedActorRoot::m44() {
    m38();
    _c4 = ksys::Timer(150.0f, 150.0f);
    _d0 = ksys::Timer(*mInvalidTgtTimerVal_s, *mInvalidTgtTimerVal_s);
    _f5 = false;
}

bool Unk_71023dcc38::m0(void*, void*, void*, void*, void*, void*,
                        const ksys::act::Struct8Base*, const ksys::act::PhysicsUserTag*) {
    return _28;
}

// 0x7100343738
bool Unk_71023dcc20::m2(ksys::act::Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<ksys::act::Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    accessor.getProfile();
    return ksys::act::isPlayerProfile(accessor) || ksys::act::isEnemyProfile(accessor) ||
           ksys::act::isNPCProfile(accessor) || ksys::act::isPreyOrSwarm(accessor) ||
           ksys::act::isHorseProfile(accessor);
}

}  // namespace uking::ai
