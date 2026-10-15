#include "Game/Actor/AI/aiPreyRoot.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "KingSystem/System/VFR.h"
#include <cmath>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_7100D8C538.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"

namespace uking::ai {

PreyRoot::PreyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyRoot::~PreyRoot() = default;

// NON_MATCHING: position registers and free-fall reset/threshold scheduling differ.
void PreyRoot::sub_71005035A8() {
    auto* nav = mActor->m45();
    auto* controller = mActor->getCharacterController();
    if (!nav || !controller)
        return;
    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    const f32 raw_time = ksys::VFR::instance()->getRawDeltaTime();
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    if (*mIsCheckFreeFall_s && !isCurrentChild("所持") && !controller->sub_7100F5F14C() &&
        !m34() && !sub_7100504D80()) {
        if (std::isnan(_1fc))
            _1fc = position.y;
        _200 = _1fc - position.y;
        if (_200 > 0.0f && !_205 &&
            _200 >= mActor->getParam()->getRes().mDamageParam->mFallDamageStartHeight.ref() - 0.1f)
            _205 = true;
    } else {
        sub_7100504BF0();
    }
    const f32 dx = position.x - _19c.x;
    const f32 dy = *mIsCheckStuckConsiderY_s ? position.y - _19c.y : 0.0f;
    const f32 dz = position.z - _19c.z;
    const f32 distance = sead::Mathf::sqrt((dx * dx + dy * dy) + dz * dz);
    const f32 relative_speed = ((1.0f / raw_time) * distance) /
                               (delta * controller->sub_7100F5EF00());
    *mIsStuckOnTerrain_a = relative_speed < 0.2f;
    if (*mIsStuckOnTerrain_a) {
        *mFramesStuckOnTerrain_a += 1.0f;
    } else {
        *mIsStuckOnTerrain_a = false;
        *mFramesStuckOnTerrain_a = 0.0f;
    }
    _19c = position;
}

bool PreyRoot::sub_7100504D80() {
    auto* controller = mActor->getCharacterController();
    if (!controller || controller->sub_7100F5F14C() || !_188->_1190)
        return false;
    bool result = _188->_e84.isOn(0x400000);
    if (auto* info = controller->sub_7100F635E4()) {
        for (auto point = info->begin(), end = info->end(); point != end; ++point) {
            if ((*point)->separating_normal.dot(sead::Vector3f::ey) != 0.0f)
                result = true;
        }
    }
    return result;
}

// NON_MATCHING: controller-vector stack slots and gear selection scheduling differ.
void PreyRoot::sub_7100503864() {
    auto* actor = mActor;
    auto* list = actor->getASList();
    if (!list)
        return;
    auto* controller = actor->getCharacterController();
    if (controller)
        _190 = controller->get64();
    if (actor->m132()) {
        auto* rideable = actor->m132();
        const act::Rideable::Gear gear(rideable->_18._b ? rideable->_18._b : rideable->_18._9);
        list->x_6(10, 0, static_cast<f32>(int(gear)));
        if (actor->getHorseOptionsMaybe()) {
            const act::Unk_7100e8b2b8::Unk8 type(
                actor->getHorseOptionsMaybe()->act::Unk_7100e8b2b8::_8.load() & 0xff);
            list->x_2(66, 26, int(type) != 0, false);
        }
    } else if (controller) {
        sead::Vector3f direction = sead::Vector3f::zero;
        if ((controller->_116 & 0xc) == 0xc &&
            controller->sub_7100F5F0E4() == ksys::act::MotionType::_1) {
            list->sub_710115F024(sead::Vector3f::ey, 0);
        } else if (controller->sub_7100F5F14C() && controller->sub_7100F5F234(&direction)) {
            list->sub_710115F024(direction, 0);
        }
    } else if (auto* body = actor->getMainBody()) {
        if (body->getMotionType() == ksys::phys::MotionType::Keyframed ||
            body->getMotionType() == ksys::phys::MotionType::Fixed) {
            const sead::Vector3f direction = actor->getMtx().getBase(1);
            list->sub_710115F024(direction, 0);
        }
    }
    f32 distance = 99999.0f;
    if (_188->_c48._8.hasProc()) {
        const f32 dx = actor->getMtx().getTranslation().x - _188->_c48._18.x;
        const f32 dz = actor->getMtx().getTranslation().z - _188->_c48._18.z;
        distance = sead::Mathf::sqrt(dx * dx + dz * dz);
    }
    list->x_6(16, 0, distance);
    _1c0.sub_710071EE38();
}

void PreyRoot::calc_() {
    auto* actor = mActor;
    if (!actor->getLodState()->mFlags8.isOn(0x800))
        m40();
    if (auto* rideable = mActor->getHorseOptionsMaybe()) {
        if (actor->isDeletedOrDeleting() || actor->getFadeOutDeleteType())
            rideable->Unk_7100e8b2b8::_8.store(0x200);
    }
    sub_71005035A8();
    sub_7100503864();
    m41();
    m43();
    sub_7100503A78();
    _1b4.update();
    if (_1b4.value <= sead::Mathf::epsilon() && !ksys::act::attentionStuff(actor)) {
        sub_7100736A84(actor);
        _1b4.reset(30.0f);
    }
}

bool PreyRoot::init_(sead::Heap* heap) {
    _188 = sead::DynamicCast<act::Enemy>(mActor);
    return _188 != nullptr;
}

void PreyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreyRoot::leave_() {
    if (!_188->_1190) {
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F62DD0(1.0f);
    }
    sub_71005DA114(mActor, &_98);
    sub_71005DA114(mActor, &_118);
    sub_71005DA114(mActor, &_c8);
    sub_71005DA114(mActor, &_f0);
}

void PreyRoot::loadParams_() {
    getStaticParam(&mAfterEscapeForceEndState_s, "AfterEscapeForceEndState");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mEscapeForceEndTime_s, "EscapeForceEndTime");
    getStaticParam(&mIsCheckFreeFall_s, "IsCheckFreeFall");
    getStaticParam(&mIsCheckStuckConsiderY_s, "IsCheckStuckConsiderY");
    getStaticParam(&mIsUseWeakForcePushOutside_s, "IsUseWeakForcePushOutside");
    getStaticParam(&mIsEnableEscapeForceEndCheck_s, "IsEnableEscapeForceEndCheck");
    getAITreeVariable(&mCreateDeadConditionType_a, "CreateDeadConditionType");
    getAITreeVariable(&mFramesStuckOnTerrain_a, "FramesStuckOnTerrain");
    getAITreeVariable(&mIsStuckOnTerrain_a, "IsStuckOnTerrain");
    getAITreeVariable(&mIsChangeableStateFreeFall_a, "IsChangeableStateFreeFall");
    getAITreeVariable(&mIsUseTerritory_a, "IsUseTerritory");
}

bool PreyRoot::m34() {
    if (!mActor->get68f().load())
        return false;
    const f32 y = mActor->getMtx().m[1][3];
    return mActor->get6f0() - y > *mInWaterDepth_s;
}

bool PreyRoot::m35() {
    return m34() && !isCurrentChild("水中行動");
}

namespace {
// inline-only in the original; name is a guess. Evidence: the SEAD_ENUM temporary of the Unk8 value shares
// the SafeString's stack slot (by-value parameter, lifetime markers); one call site (PreyRoot::m36).
bool isNonZero(act::Unk_7100e8b2b8::Unk8 type) {
    return int(type) != 0;
}
}  // namespace

bool PreyRoot::m36() {
    if (mActor->getHorseOptionsMaybe())
        return isNonZero(mActor->getHorseOptionsMaybe()->Unk_7100e8b2b8::_8 & 0xff) &&
               !isCurrentChild("騎乗中");
    return false;
}

// NON_MATCHING: the target returns _205 without normalising it (no cmp/cset)
bool PreyRoot::m37() {
    if (*mIsChangeableStateFreeFall_a && !isCurrentChild("落下"))
        return _205;
    return false;
}

bool PreyRoot::m38() {
    if (isCurrentChild("落下")) {
        if (!_205)
            return true;
    }
    return false;
}

// 0x7100504070
bool PreyRoot::sub_7100504070() {
    if (m34()) {
        if (auto* cc = mActor->getCharacterController()) {
            if (cc->_116 & 4) {
                if (cc->_18c == 1)
                    return true;
            }
            if ((cc->_116 & 0x14) == 0x10)
                return true;
        }
    }
    return false;
}

// NON_MATCHING: block layout only; the original places the shared `return true` block right after the
// first four m151 checks (mine puts it at the end); every instruction is otherwise identical
bool PreyRoot::m39() {
    if (_188->m151(3) || _188->m151(4) || _188->m151(0xb) || _188->m151(0xa))
        return true;

    if (sub_71005D6E28(mActor)) {
        auto* life = mActor->getLife();
        if (life && *life <= 0 && !mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::Alive))
            return true;
    }

    if (auto* damage_mgr = sub_710072BA90(_188)) {
        const s32 type = damage_mgr->getField54();
        if (damage_mgr->_216.isOn(2))
            return true;
        switch (type) {
        case 15:
        case 17:
        case 18:
        case 20:
        case 21:
        case 22:
        case 23:
        case 27:
        case 30:
        case 31:
        case 33:
        case 34:
            return true;
        default:
            break;
        }

        if (sub_7100736BD8(damage_mgr->getField54())) {
            const s32 damage = damage_mgr->getDamage();
            if (damage > 0)
                return true;
        }
    }
    return false;
}

void PreyRoot::m40() {
    auto* actor = mActor;
    auto* unk = actor->m100();
    if (unk && !isCurrentChild("所持") && !unk->sub_7100E502B8())
        ksys::act::enableAttClient(actor, "Grab");
    else
        ksys::act::disableAttClient(actor, "Grab");
}

void PreyRoot::sub_71005047A8() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("通常行動", &pack);
}

// NON_MATCHING: the original's jump table starts at case 0 (entry 0 = default; ours starts at 1 with a subtract)
// 0x7100503a78
void PreyRoot::sub_7100503A78() {
    if (!*mIsEnableEscapeForceEndCheck_s)
        return;
    if (isCurrentChild("リアクション"))
        return;
    if (!mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_8000000) ||
        *mIsUseTerritory_a) {
        _1f0 = ksys::Timer(*mEscapeForceEndTime_s, *mEscapeForceEndTime_s);
        return;
    }
    _1f0.update();
    if (_1f0.value <= sead::Mathf::epsilon()) {
        _1f0 = ksys::Timer(*mEscapeForceEndTime_s, *mEscapeForceEndTime_s);
        switch (*mAfterEscapeForceEndState_s) {
        case 1:
            if (mActor->getMapObject() &&
                mActor->becomePreActor(ksys::act::Actor::DeleteType::_1,
                                       ksys::act::BaseProc::DeleteReason::_0))
                return;
            break;
        case 2:
            sub_71005047A8();
            return;
        case 3:
            mActor->deleteEx(ksys::act::Actor::DeleteType::_5,
                             ksys::act::BaseProc::DeleteReason::_0);
            return;
        case 9:
            m47();
            return;
        }
        sub_7100504ED0();
    }
}

void PreyRoot::sub_7100504A9C(u32 mask, bool on) {
    if (on)
        _188->_e84.set(mask);
    else
        _188->_e84.reset(mask);
}

bool PreyRoot::sub_7100504EBC(u32 mask) const {
    return _188->_e84.isOn(mask);
}

void PreyRoot::sub_7100504BF0() {
    _205 = false;
    _1fc = std::numeric_limits<f32>::quiet_NaN();
    _200 = 0;
}

void PreyRoot::sub_71005044C8() {
    sub_7100504BF0();
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("水中行動", &pack);
}

void PreyRoot::m41() {
    if (isCurrentChild("リアクション"))
        return;
    if (m39()) {
        m45();
        return;
    }
    if (m37()) {
        m46();
        return;
    }
    if (m36()) {
        ksys::act::disableAttClient(mActor, "LockOn");
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
        _188->_e84.setBit(4);
        changeChild("騎乗中");
        mActor->getHorseOptionsMaybe()->_18._52 |= 2;
        return;
    }
    if (_148._30) {
        if (sub_71005DC444(mActor)) {
            _148.x();
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
            changeChild("所持");
        } else if (!mActor->getConnectedCalcParent()) {
            _148.x();
        }
        return;
    }
    if (m35()) {
        sub_71005044C8();
        return;
    }
    if (isChangeable())
        m42();
}

void PreyRoot::m42() {
    if (isCurrentChild("水中行動") && !m34()) {
        sub_71005047A8();
        return;
    }
    if (m38()) {
        sub_71005047A8();
    }
}

void PreyRoot::m45() {
    auto* damage_mgr = sub_710072BA90(mActor);
    if (damage_mgr && !sub_7100736BD8(damage_mgr->getField54()) && damage_mgr->getField50() != 15) {
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
        _1f0 = ksys::Timer(*mEscapeForceEndTime_s, *mEscapeForceEndTime_s);
    }
    changeChild("リアクション");
}

void PreyRoot::m46() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("落下", &pack);
}

void PreyRoot::m43() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("騎乗中"))
        mActor->getHorseOptionsMaybe()->sub_7100E63424();

    auto* controller = _188->getCharacterController();
    if (controller && isCurrentChild("所持") && !controller->sub_7100F5F14C()) {
        _1fc = mActor->getMtx().m[1][3] + 100.0f;
        _200 = 100.0f;
        _205 = true;
        m46();
    } else {
        sub_71005047A8();
    }
    _188->_e84.resetBit(4);
    ksys::act::enableAttClient(mActor, "LockOn");
    sub_7100736A84(mActor);
}

void PreyRoot::m44() {
    auto* life = mActor->getLife();
    if (life && *life <= 0) {
        m45();
        return;
    }
    sub_71005047A8();
}

void PreyRoot::sub_7100504ED0() {
    if (auto* info = mActor->m135())
        info->_4 = 0;
    mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
}

bool PreyRoot::handleMessage_(const ksys::Message* message) {
    if (!isCurrentChild("所持")) {
        auto* actor = mActor;
        if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) && !_148._30 &&
            _148.m2(*message)) {
            _148.sub_710070B5A0(actor);
            return true;
        }
    }
    return false;
}

// 0x7100505144
void Unk_7102410b48::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          act::DamageCallbackInfo* a6) {
    if (*a5 == -1)
        return;
    auto* manager = sead::DynamicCast<act::DamageManagerBase>(mDamageManager);
    if (!manager)
        return;
    auto* attacker = manager->getAttacker();
    if (!attacker->hasProc())
        return;
    if (!(ksys::act::isPreyOrSwarm(attacker) && !ksys::act::isWolfOrBear(attacker))) {
        if (!ksys::act::isWolfOrBear(mActor))
            return;
        if (!ksys::act::isWolfOrBear(attacker))
            return;
    }
    *a1 = 0;
    *a5 = -1;
    auto* info = sead::DynamicCast<act::DamageCallbackInfo>(a6);
    if (info)
        info->mFlags = 0;
}

// 0x71005052b0
void Unk_7102410b80::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          act::DamageCallbackInfo* a6) {
    if (*a5 == -1)
        return;
    auto* manager = sead::DynamicCast<act::DamageManagerBase>(mDamageManager);
    if (!manager)
        return;
    if (!manager->getAttacker()->hasProc())
        return;
    if (*a5 != 6)
        return;
    *a1 = 0;
    *a5 = -1;
    auto* info = sead::DynamicCast<act::DamageCallbackInfo>(a6);
    if (info)
        info->mFlags = 0;
}

// 0x71005053e8
void Unk_7102410bb8::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          act::DamageCallbackInfo* a6) {
    if (*a4 - 9 < 3) {
        *a1 = 0;
        *a2 = 0;
        *a3 = 0;
        *a5 = 0xf;
        auto* info = sead::DynamicCast<act::DamageCallbackInfo>(a6);
        if (info)
            info->mFlags = 0;
    }
}

// 0x7100504fac
void Unk_7102410b10::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) {
    if (*a1 <= 0)
        return;
    auto* manager = sead::DynamicCast<act::DamageManager>(mDamageManager);
    if (manager && manager->_6c >= 0) {
        const auto* info = sub_71007A255C(mActor, manager->_6c);
        if (info && info->_d0 != 0x28)
            return;
    }

    const auto* lod = mActor->getLodState();
    const s32 lod_value = lod ? lod->_1c : 0;
    const s32* life = mActor->getLife();
    const f32 life_value = life ? f32(*life) : 1.0f;
    if (f32(*a1) >= life_value) {
        if (lod_value < 2)
            return;
    } else {
        auto* global = ksys::act::GlobalParameter::instance();
        if (!global)
            return;
        auto* param = global->getGlobalParam();
        if (!param)
            return;
        sead::Vector3f camera_pos;
        cam::getCameraPositionMaybe(&camera_pos);
        const sead::Vector3f diff = camera_pos - mActor->getMtx().getTranslation();
        if (!(diff.length() > param->mEnemyAnimalNoDamageDist.ref()))
            return;
    }
    *a1 = 0;
}

}  // namespace uking::ai
