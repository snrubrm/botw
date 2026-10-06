#include "Game/AI/AI/aiSimpleWildlifeRoot.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace uking::ai {

// NON_MATCHING: the original addresses everything from `this` (we keep this+0x38 in a register)
SimpleWildlifeRoot::SimpleWildlifeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleWildlifeRoot::~SimpleWildlifeRoot() = default;

void SimpleWildlifeRoot::m9() {
    auto* root_ai = mActor->getRootAi();
    _f4 = (root_ai && root_ai->getI() == 4) || *mIsLocatorCreate_m;
    if (mActor->hasPlacementLinkWithTypeFreeze())
        _f5 = true;

    bool* is_amiibo = nullptr;
    if (mActor->getRootAi()->getAITreeVariable(&is_amiibo, "IsAmiibo"))
        _f6 = *is_amiibo;
}

bool SimpleWildlifeRoot::init_(sead::Heap* heap) {
    m9();
    return true;
}

void SimpleWildlifeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SimpleWildlifeRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleWildlifeRoot::calc_() {
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

void SimpleWildlifeRoot::loadParams_() {
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
bool SimpleWildlifeRoot::m34() {
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
bool SimpleWildlifeRoot::m35() {
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

void SimpleWildlifeRoot::m37() {
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

void SimpleWildlifeRoot::m38() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(home_pos, "TargetPos", -1);
    changeChild("通常行動", &params);
}

void SimpleWildlifeRoot::m39() {
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

bool SimpleWildlifeRoot::sub_710034342C() {
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

void SimpleWildlifeRoot::sub_7100343510() {
    if (m36()) {
        _dc = _e0 == _e4 ? _e0 : sead::GlobalRandom::instance()->getS32Range(_e0, _e4);
        mActor->getLodState()->mFlags10.reset(0x40);
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000);
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000);
    }
    m38();
}

void SimpleWildlifeRoot::m40() {
    if (isCurrentChild("死亡"))
        return;

    if (*mIsDeleteWhenDead_s)
        ksys::act::disableAllAttClients(mActor);
    else
        ksys::act::enableAttClient(mActor, "NoticeDo");
    changeChild("死亡");
}

void SimpleWildlifeRoot::m41() {
    m38();
}

void SimpleWildlifeRoot::m42() {
    if (*mIsDeadWhenPut_s || *mIsCreateDead_m) {
        m40();
    } else if (*mIsEscapeWhenPut_s) {
        _c4 = ksys::Timer(-1.0f, -1.0f);
        m39();
    } else {
        m38();
    }
}

void SimpleWildlifeRoot::m43() {
    if (*mIsDeadWhenDrop_s || *mIsCreateDead_m)
        m40();
    else
        m38();
}

void SimpleWildlifeRoot::m44() {
    m38();
    _c4 = ksys::Timer(150.0f, 150.0f);
    _d0 = ksys::Timer(*mInvalidTgtTimerVal_s, *mInvalidTgtTimerVal_s);
    _f5 = false;
}

bool Unk_71023dcc38::m0() {
    return _28;
}

}  // namespace uking::ai
