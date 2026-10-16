#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/Damage/dmgStruct20.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiUnk_7100736460.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actImpulseBaseProcLink.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"

namespace uking::act {

DamageManager::DamageManager(ksys::act::Actor* actor)
    : DamageManagerBase(actor), _84(actor->getMtx()(1, 3)), _d8(actor, 0x800003e), _128(actor, 0x800003f),
      _178(actor, 0x800006e), _1f8(actor, 0x80000b5) {
    _216.set(9);
}

void DamageManager::sub_71006D276C() {
    // NON_MATCHING: identical instruction multiset and registers, but different store
    // scheduling (ours: _7c/_218/_6c/_88, and+strh216, _c0, _5c; original: _6c/_7c/_88/_218,
    // and, _c0, _5c, strh216). Tried _216.reset() first / between _218 and _c0 / last.
    DamageManagerBase::resetStuff();
    _6c = -1;
    _7c = 0;
    _88 = -1;
    _8c = 0;
    _218 = 0;
    _219 = false;
    // Clears bits 1, 5, 7 and 8 (single and with ~0x1a2).
    _216.reset(0x1a2);
    _c0 = {0, 0, 0};
    mDamageType = -1;
}

// NON_MATCHING: store scheduling (_5c / _68 pair, _218), and the original stores _216 twice (after the 0x10 update and
// after clearing 0x1a0) where ours merges them.
void DamageManager::resetDamage() {
    DamageManagerBase::resetDamage();
    sub_71006D276C();
    _68 = 0;
    _70 = 0;
    _84 = mActor->getMtx()(1, 3);
    _f0.x();
    _140.x();
    _1a8.x();
    _212 = 0;
    _214 = 0;
    if (!sub_71007A40A8(mActor) || isBgGroundHit(mActor, false))
        _216.set(0x10);
    else
        _216.reset(0x10);
    _216.reset(0x1a0);
    _218 = 0;
    sub_71006D27BC();
    _88 = -1;
    mFlags2 = 0;
    _228 = 0;
}

void DamageManager::sub_71006D32F8() {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return;
    _84 = actor->m148();
    if (!sub_71007A40A8(actor))
        return;
    bool ragdoll_grounded = false;
    if (actor->_868 && actor->_868->sub_71006ED9EC()) {
        if (auto* physics = mActor->getPhysics())
            ragdoll_grounded = physics->sub_7100FBB4B4();
    }
    const bool grounded = isBgGroundHit(actor, false);
    if (ragdoll_grounded || grounded)
        _216.set(0x10);
    else
        _216.reset(0x10);
}

ksys::phys::RigidBody* DamageManager::sub_71006D69F8() {
    switch (getDamageType()) {
    case 2:
        if (_6c >= 0) {
            if (auto* info = ::sub_71007A255C(mActor, _6c))
                return info->_c0;
        }
        return nullptr;
    case 4:
        if (auto* impulse = mActor->getImpulseBaseProcLink())
            return impulse->_10.mBody;
        return nullptr;
    case 6:
        if (_216.isOn(0x100) && _88 >= 0) {
            if (auto* info = ::sub_71007A255C(mActor, _88))
                return info->_c0;
        }
        return nullptr;
    default:
        return nullptr;
    }
}

// NON_MATCHING: inlining the existing body getter merges the two attack-info calls.
bool DamageManager::isDamageSourceObjectMaybe(ksys::phys::RigidBody* body) {
    auto* damage_body = sub_71006D69F8();
    return damage_body && damage_body == body;
}

// NON_MATCHING: the original duplicates accessor cleanup in its true / false return paths.
bool DamageManager::m51(const ksys::act::BaseProcLink* link) {
    const auto* param = getActorDamageParam();
    if (!(_78 >= 1.0f)) {
        if (!param || param->mLightningAffect.ref())
            return false;
    }
    ksys::act::ActorLinkConstDataAccess accessor;
    // The original deliberately discards acquireActor's bool before the name lookup.
    ksys::act::acquireActor(link, &accessor);
    if (accessor.getName() == "Explode")
        return true;
    return false;
}

// The out-of-line copy of the constructor lives in this TU (DamageManager::allocStruct20 inlines it).
Struct20_2::Struct20_2() = default;

bool DamageManager::allocStruct20(sead::Heap* heap) {
    mStruct20_a = new (heap, 8) Struct20_2;
    if (!mStruct20_a)
        return false;

    mStruct20_b = new (heap, 8) Struct20_2;
    return mStruct20_b != nullptr;
}

// NON_MATCHING (also sub_71006D9B30): the original keeps a flag for "no speed limit scaling" (`w19`) across the accessor
// destructor and applies the default 1.0 afterwards; ours materialises 1.0f in a register up front.
DamageManagerUnk220::DamageManagerUnk220() = default;

// NON_MATCHING: the original clears 0x27a-0x291 like a 0x18-byte memset with 2-byte alignment (three unaligned 8-byte
// stores) between the stores of _278 / _294 / _292; the fields there are not known well enough to reproduce it.
void DamageManagerUnk220::sub_71006D99F4() {
    mHits.clear();
    _278 = 0;
    _279 = 0;
    _27a = false;
    _27b = 0;
    _27c = {0, 0, 0};
    _288 = {0, 0, 0};
    _294 = -1.0f;
}

f32 DamageManagerUnk220::sub_71006D9A24(ksys::act::Actor* actor) const {
    f32 value = actor->m38();
    f32 ratio;
    if (!_27a) {
        ratio = f32(mHits.size()) / f32(mHits.capacity());
    } else {
        if (auto* info = uking::act::PlayerInfo::instance()) {
            ksys::act::acc::PlayerBase accessor;
            ksys::act::acquireActor(&info->getPlayerLink(), &accessor);
            if (value > 0.0f)
                ratio = _27c.length() / (value * (accessor.getStopTimerBlowSpeedLimit() * 30.0f));
            else
                ratio = 1.0f;
        } else {
            ratio = 1.0f;
        }
        ratio = sead::Mathf::min(ratio, 1.0f);
    }
    return sead::Mathf::max(ratio, 0.01f);
}

f32 DamageManagerUnk220::sub_71006D9B30(const ksys::act::ActorLinkConstDataAccess& accessor_) const {
    f32 value = accessor_.sub_7100D14114();
    f32 ratio;
    if (!_27a) {
        ratio = f32(mHits.size()) / f32(mHits.capacity());
    } else {
        if (auto* info = uking::act::PlayerInfo::instance()) {
            ksys::act::acc::PlayerBase accessor;
            ksys::act::acquireActor(&info->getPlayerLink(), &accessor);
            if (value > 0.0f)
                ratio = _27c.length() / (value * (accessor.getStopTimerBlowSpeedLimit() * 30.0f));
            else
                ratio = 1.0f;
        } else {
            ratio = 1.0f;
        }
        ratio = sead::Mathf::min(ratio, 1.0f);
    }
    return sead::Mathf::max(ratio, 0.01f);
}

f32 DamageManager::getStasisBlowPowerRatio() {
    if (_220)
        return _220->sub_71006D9A24(mActor);
    return 0.0f;
}

bool DamageManager::m14(sead::Vector3f* out) {
    if (_220 && _220->_27a) {
        *out = _220->_27c;
        return true;
    }
    return false;
}

void DamageManager::preDelete1() {
    if (mStruct20_a) {
        delete mStruct20_a;
        mStruct20_a = nullptr;
    }
    if (mStruct20_b) {
        delete mStruct20_b;
        mStruct20_b = nullptr;
    }
}

f32 DamageManager::sub_71006D8DE8() {
    auto* link = m37();
    if (link->hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (ksys::act::getWeaponCommonIsPikohan(accessor) ||
            dlc::isOneHitObliteratorActorAccessor(accessor, true))
            return 2.0f;
    }
    return 1.0f;
}

s32 DamageManager::sub_71006D8534() const {
    return _220 ? _220->mHits.size() : 0;
}

ksys::act::ActorAtk::Unk_710079e64c::Unk1* DamageManager::getAttackInfo_() {
    s32 index;
    switch (getDamageType()) {
    case 2:
        index = _6c;
        if (index < 0)
            return nullptr;
        break;
    case 6:
        if (!_216.isOn(0x100))
            return nullptr;
        index = _88;
        if (index < 0)
            return nullptr;
        break;
    default:
        return nullptr;
    }
    return ::sub_71007A255C(mActor, index);
}

// Inline-only in the original (name is a guess; its body is repeated for the character controller and the rigid body path
// of sub_71006D27BC): the first non-negative impulse threshold, or -1.
static inline f32 getImpulseThreshold(const ksys::res::DamageParam* param) {
    f32 threshold = param->mImpulseThresholdLv0.ref();
    if (!(threshold >= 0.0f)) {
        threshold = param->mImpulseThresholdLv1.ref();
        if (!(threshold >= 0.0f)) {
            threshold = param->mImpulseThresholdLv2.ref();
            if (!(threshold >= 0.0f)) {
                threshold = param->mImpulseThresholdLv3.ref();
                if (!(threshold >= 0.0f)) {
                    threshold = param->mImpulseThresholdLv4.ref();
                    if (!(threshold >= 0.0f))
                        threshold = -1.0f;
                }
            }
        }
    }
    return threshold;
}

void DamageManager::sub_71006D27BC() {
    auto* param = getActorDamageParam();
    if (!param || param->mIsCommonCalcImpuleDamage.ref())
        return;

    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62C14(getImpulseThreshold(param) * _80);
    else if (auto* body = mActor->getMainBody())
        body->setMaxImpulse(getImpulseThreshold(param) * _80);
}

void DamageManager::sub_71006D81D8(f32 value) {
    auto* param = getActorDamageParam();
    if (param && !param->mIsCommonCalcImpuleDamage.ref()) {
        _80 = value;
        sub_71006D27BC();
    }
}

// NON_MATCHING: the original keeps the element state compares in source order (1, 6, 2); ours turns them into a switch
// (6, 2, 1) and lays the blocks out differently
s32 DamageManager::sub_71006D7FB0(ksys::act::ActorAtk::Unk_710079e64c::Unk1* info) {
    ksys::act::ActorLinkConstDataAccess attacker;
    ksys::act::acquireActor(&info->_e8, &attacker);
    auto* chemical = mActor->getChemicalStuff();
    if (!chemical)
        return -1;
    auto* param = mActor->getParam();
    if (!param)
        return -1;
    auto* damage_param = param->getRes().mDamageParam;
    if (!damage_param)
        return -1;

    const s32 state = attacker.sub_7100D131D0(-1);
    if (state == 1 || state == 6) {
        auto* player_or_enemy = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
        if (player_or_enemy && player_or_enemy->m151(3))
            return -1;
        return damage_param->mIceable.ref() ? 10 : -1;
    }
    if (state == 2)
        return damage_param->mBurnable.ref() ? 9 : -1;
    if (!damage_param->mElectricable.ref() || attacker.sub_7100D13080() <= chemical->_1b8)
        return 6;
    return 11;
}

s32 DamageManager::sub_71006D8130() {
    switch (getDamageType()) {
    case 2:
    case 10:
        if (_6c < 0)
            return -1;
        if (auto* info = ::sub_71007A255C(mActor, _6c))
            return info->_f8;
        return -1;
    case 6:
        if (!_216.isOn(0x100))
            return -1;
        if (_6c < 0)
            return -1;
        if (auto* info = ::sub_71007A255C(mActor, _6c))
            return info->_f8;
        return -1;
    default:
        return -1;
    }
}

s32 DamageManager::getNumCallbacks() {
    return 7;
}

bool DamageManager::checkDamageFlags(s32 bit) {
    return (1 << bit) & _8c;
}

bool DamageManager::isDamageItemFlagCheckDisabled() {
    return checkDamageFlags(14);
}

bool DamageManager::isSlowTime() {
    if (DamageManagerBase::isSlowTime())
        return true;
    auto* info = getAttackInfo_();
    return info && info->sub_71007A1F78(0x4000000);
}

bool DamageManager::getAttackDirType(s32* out) {
    *out = -1;
    if (auto* info = getAttackInfo_()) {
        *out = info->_bc;
        return true;
    }
    return false;
}

// NON_MATCHING: the original sets up its stack frame at the top (no shrink wrapping around the call)
// NON_MATCHING: the original ends the failure paths with a tail call of getDummyBaseProcLink() (the call is not a tail
// call in ours: its result joins the other returns)
ksys::act::BaseProcLink* DamageManager::getAttacker() {
    switch (getDamageType()) {
    case 2:
    case 10:
        if (_6c < 0)
            return &ksys::act::getDummyBaseProcLink();
        if (auto* info = ::sub_71007A255C(mActor, _6c))
            return &info->_d8;
        return &ksys::act::getDummyBaseProcLink();
    case 3:
        if (!::hasAttackInfo(mActor))
            return &ksys::act::getDummyBaseProcLink();
        if (auto* info = ::getAttackInfo(mActor, 0))
            return &info->_50;
        return &ksys::act::getDummyBaseProcLink();
    case 4:
    case 11:
        if (auto* link = mActor->getImpulseBaseProcLink())
            return &link->mLink;
        return &ksys::act::getDummyBaseProcLink();
    case 6:
        if (!_216.isOn(0x100) || _88 < 0)
            return &ksys::act::getDummyBaseProcLink();
        if (auto* info = ::sub_71007A255C(mActor, _88))
            return &info->_d8;
        return &ksys::act::getDummyBaseProcLink();
    default:
        return &ksys::act::getDummyBaseProcLink();
    }
}

// NON_MATCHING: same tail call difference as getAttacker
ksys::act::BaseProcLink* DamageManager::m37() {
    switch (getDamageType()) {
    case 2:
    case 10:
        if (_6c < 0)
            return &ksys::act::getDummyBaseProcLink();
        if (auto* info = ::sub_71007A255C(mActor, _6c))
            return &info->_e8;
        return &ksys::act::getDummyBaseProcLink();
    case 3:
        if (!::hasAttackInfo(mActor))
            return &ksys::act::getDummyBaseProcLink();
        if (auto* info = ::getAttackInfo(mActor, 0))
            return &info->_50;
        return &ksys::act::getDummyBaseProcLink();
    case 4:
    case 11:
        if (auto* link = mActor->getImpulseBaseProcLink())
            return &link->mLink;
        return &ksys::act::getDummyBaseProcLink();
    case 6:
        if (!_216.isOn(0x100) || _88 < 0)
            return &ksys::act::getDummyBaseProcLink();
        if (auto* info = ::sub_71007A255C(mActor, _88))
            return &info->_e8;
        return &ksys::act::getDummyBaseProcLink();
    default:
        return &ksys::act::getDummyBaseProcLink();
    }
}

// NON_MATCHING: register allocation / store scheduling of the damage kind 1 and 3 paths (the original stores x first,
// then y and z one at a time; it fmovs the copied position in another order)
bool DamageManager::getPosition(sead::Vector3f* out) {
    mActor->getMtx().getTranslation(*out);

    s32 index;
    switch (getDamageType()) {
    case 1:
        mActor->getMtx().getTranslation(*out);
        if (_c0.x * _c0.x + _c0.y * _c0.y + _c0.z * _c0.z > 0.0f) {
            const sead::Vector3f offset(_c0.x * 0.4f, _c0.y * 0.4f, _c0.z * 0.4f);
            out->x = out->x - offset.x;
            out->y = out->y - offset.y;
            out->z = out->z - offset.z;
        }
        return true;
    case 2:
    case 10:
        index = _6c;
        if (index < 0)
            return false;
        break;
    case 3: {
        if (::hasAttackInfo(mActor)) {
            auto* info = ::getAttackInfo(mActor, 0);
            if (!info)
                return false;
            *out = info->_0;
            return true;
        }
        if (!(_218 & 0x30))
            return false;
        mActor->getMtx().getTranslation(*out);
        const auto& velocity = mActor->getVelocity();
        out->x = out->x - velocity.x;
        out->y = out->y - velocity.y;
        out->z = out->z - velocity.z;
        return true;
    }
    case 4:
    case 11: {
        auto* impulse = mActor->getImpulseBaseProcLink();
        const sead::Vector3f* position;
        if (!impulse)
            position = &sead::Vector3f::zero;
        else
            position = &impulse->_10._4c;
        *out = *position;
        return true;
    }
    case 6:
        if (!_216.isOn(0x100))
            return false;
        index = _88;
        if (index < 0)
            return false;
        break;
    case 9:
        *out = _90;
        return true;
    default:
        return false;
    }

    auto* info = ::sub_71007A255C(mActor, index);
    if (!info)
        return false;
    *out = info->_0;
    return true;
}

// NON_MATCHING: same logic and damage-kind structure, but the original keeps no float register across the switch (the
// impulse direction is copied first and scaled afterwards; our scheduling / csel polarity differ in several kinds)
bool DamageManager::getDamageImpulse(sead::Vector3f* out) {
    s32 index;
    switch (getDamageType()) {
    case 1:
        if (getField54() == 20) {
            const f32 scale = 2400.0f;
            out->x = _c0.x * scale;
            out->y = _c0.y * scale;
            out->z = _c0.z * scale;
            return true;
        }
        *out = sead::Vector3f::zero;
        return true;
    case 2:
    case 10:
        index = _6c;
        if (index < 0)
            return false;
        break;
    case 3: {
        if (::hasAttackInfo(mActor)) {
            auto* info = ::getAttackInfo(mActor, 0);
            if (!info)
                return false;
            f32 scale;
            if (info->_18 & 2) {
                scale = 1800.0f;
            } else if (info->_18 & 1) {
                scale = 600.0f;
            } else {
                return false;
            }
            out->x = info->_c.x * scale;
            out->y = info->_c.y * scale;
            out->z = info->_c.z * scale;
            return true;
        }
        f32 scale;
        if (_218 & 0x20) {
            scale = 1800.0f;
        } else if (_218 & 0x10) {
            scale = 600.0f;
        } else {
            return false;
        }
        const auto& velocity = mActor->getVelocity();
        out->set(-velocity.x, -velocity.y, -velocity.z);
        out->normalize();
        out->x *= scale;
        out->y *= scale;
        out->z *= scale;
        return true;
    }
    case 4:
    case 11: {
        auto* impulse = mActor->getImpulseBaseProcLink();
        const sead::Vector3f* direction;
        if (!impulse)
            direction = &sead::Vector3f::ez;
        else
            direction = &impulse->_10._10;
        *out = *direction;
        const f32 scale = impulse ? impulse->_10._8 : 0.0f;
        out->x *= scale;
        out->y *= scale;
        out->z *= scale;
        return true;
    }
    case 6:
        if (!_216.isOn(0x100))
            return false;
        index = _88;
        if (index < 0)
            return false;
        break;
    case 7:
        if (!_216.isOn(0x40))
            return false;
        *out = _cc;
        return true;
    case 9:
        *out = _b4;
        return true;
    default:
        return false;
    }

    auto* info = ::sub_71007A255C(mActor, index);
    if (!info)
        return false;
    *out = info->_a0;
    return true;
}

bool DamageManager::getHitDirection(sead::Vector3f* out) {
    s32 index;
    switch (getDamageType()) {
    case 1:
        if (_c0.x * _c0.x + _c0.y * _c0.y + _c0.z * _c0.z > 0.0f) {
            *out = _c0;
            return true;
        }
        {
            const auto& mtx = mActor->getMtx();
            const sead::Vector3f z_axis(-mtx(0, 2), -mtx(1, 2), -mtx(2, 2));
            out->x = z_axis.x;
            out->y = z_axis.y;
            out->z = z_axis.z;
            return true;
        }
    case 2:
    case 10:
        index = _6c;
        if (index < 0)
            return false;
        break;
    case 3: {
        if (::hasAttackInfo(mActor)) {
            auto* info = ::getAttackInfo(mActor, 0);
            if (!info)
                return false;
            *out = info->_c;
            out->normalize();
            return true;
        }
        if (!(_218 & 0x30))
            return false;
        const auto& velocity = mActor->getVelocity();
        out->set(-velocity.x, -velocity.y, -velocity.z);
        out->normalize();
        return true;
    }
    case 4:
    case 11: {
        auto* impulse = mActor->getImpulseBaseProcLink();
        const sead::Vector3f* direction;
        if (!impulse)
            direction = &sead::Vector3f::ez;
        else
            direction = &impulse->_10._10;
        *out = *direction;
        return true;
    }
    case 6:
        if (!_216.isOn(0x100))
            return false;
        index = _88;
        if (index < 0)
            return false;
        break;
    case 9:
        *out = _a8;
        return true;
    default:
        return false;
    }

    auto* info = ::sub_71007A255C(mActor, index);
    if (!info)
        return false;
    *out = info->_94;
    return true;
}

bool DamageManager::getDamageDir(sead::Vector3f* out) {
    s32 index;
    switch (getDamageType()) {
    case 1:
        if (_c0.x * _c0.x + _c0.y * _c0.y + _c0.z * _c0.z > 0.0f) {
            *out = _c0;
            return true;
        }
        {
            const auto& mtx = mActor->getMtx();
            mtx.getBase(*out, 2);
            out->normalize();
            out->negate();
            return true;
        }
    case 2:
    case 10:
        index = _6c;
        if (index < 0)
            return false;
        break;
    case 3: {
        if (::hasAttackInfo(mActor)) {
            auto* info = ::getAttackInfo(mActor, 0);
            if (!info)
                return false;
            *out = info->_c;
            return true;
        }
        if (!(_218 & 0x30))
            return false;
        const auto& velocity = mActor->getVelocity();
        out->set(-velocity.x, -velocity.y, -velocity.z);
        out->normalize();
        return true;
    }
    case 4:
    case 11: {
        auto* impulse = mActor->getImpulseBaseProcLink();
        const sead::Vector3f* direction;
        if (!impulse)
            direction = &sead::Vector3f::ez;
        else
            direction = &impulse->_10._10;
        *out = *direction;
        return true;
    }
    case 6:
        if (!_216.isOn(0x100))
            return false;
        index = _88;
        if (index < 0)
            return false;
        break;
    case 7:
        if (!_216.isOn(0x40))
            return false;
        *out = _cc;
        out->normalize();
        return true;
    case 9:
        *out = _9c;
        return true;
    default:
        return false;
    }

    auto* info = ::sub_71007A255C(mActor, index);
    if (!info)
        return false;
    *out = info->_c;
    return true;
}

bool DamageManager::getAttackSourceMtx(sead::Matrix34f* out) {
    s32 index;
    switch (getDamageType()) {
    case 2:
        index = _6c;
        if (index < 0)
            return false;
        break;
    case 3: {
        if (!::hasAttackInfo(mActor))
            return false;
        auto* info = ::getAttackInfo(mActor, 0);
        if (!info)
            return false;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&info->_50, &accessor);
        *out = accessor.getActorMtx();
        return true;
    }
    case 4: {
        auto* impulse = mActor->getImpulseBaseProcLink();
        const sead::Matrix34f* mtx;
        if (!impulse)
            mtx = &sead::Matrix34f::ident;
        else
            mtx = &impulse->_10._1c;
        *out = *mtx;
        return true;
    }
    case 6:
        if (!_216.isOn(0x100))
            return false;
        index = _88;
        if (index < 0)
            return false;
        break;
    default:
        *out = sead::Matrix34f::ident;
        return false;
    }

    auto* info = ::sub_71007A255C(mActor, index);
    if (!info)
        return false;
    *out = info->_58;
    return true;
}

// NON_MATCHING: the original duplicates the `info ? &info->_20 : nullptr` tail in both arms of the damage kind switch
ksys::phys::MaterialMask* DamageManager::getAttackOtherMaterialMask() {
    auto* info = getAttackInfo_();
    return info ? &info->_20 : nullptr;
}

// NON_MATCHING: same tail duplication as getAttackOtherMaterialMask
ksys::phys::MaterialMask* DamageManager::tgSensorMaterialOnHitMaybe() {
    auto* info = getAttackInfo_();
    return info ? &info->_38 : nullptr;
}

bool DamageManager::m29(sead::Vector3f* out) {
    if (getDamageType() == 7 && _216.isOn(0x40)) {
        *out = _cc;
        out->normalize();
        return true;
    }
    return DamageManagerBase::m29(out);
}

bool DamageManager::m30(sead::Vector3f* out) {
    if (getDamageType() == 7 && _216.isOn(0x40)) {
        *out = _cc;
        out->normalize();
        return true;
    }
    return DamageManagerBase::m30(out);
}

bool DamageManager::getAttackInfoFlagFC() {
    if (auto* info = getAttackInfo_())
        return info->_fc & 1;
    return false;
}

s32 DamageManager::getDamageFromTypeIndex(s32 damageTypeMaybe) {
    if (_8c & 0x10)
        return 1;
    return DamageManagerBase::getDamageFromTypeIndex(damageTypeMaybe);
}

bool DamageManager::sub_71006EE2B0() const {
    switch (getDamageType()) {
    case 1:
    case 4:
    case 5:
    case 6:
        return true;
    default:
        return (_218 & 0x30) != 0;
    }
}

bool DamageManager::sub_71006D82D4() const {
    if (!_219)
        return false;
    return _220 && _220->mHits.size() > 0;
}

bool DamageManager::sub_71006D83B8(s32 bit) const {
    return _220->mHits.back()._18 & (1 << bit);
}

s32 DamageManager::sub_71006D8304() const {
    return _220->mHits.back()._0;
}

s32 DamageManager::sub_71006D8340() const {
    return _220->mHits.back()._14;
}

s32 DamageManager::sub_71006D837C() const {
    return _220->mHits.back()._10;
}

bool DamageManager::m56() {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (actor && !actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40) && actor->m151(3))
        return actor->m154();
    return false;
}

bool DamageManager::sub_71006D33FC(s32* damage, s32* df48, u32* minDmg, u32* f50, s32* f54, s32* f40) {
    auto* actor = mActor;
    auto* param = getActorDamageParam();
    if (!param)
        return false;

    if (_78 < 1.0f && param->mLightningAffect.ref() && actor->m50()) {
        *damage = s32(static_cast<f32>(param->mLightningDamage.ref()) * (1.0f - _78));
        *df48 = 0;
        *f50 = 11;
        *f54 = 22;
        *f40 = 4;
        *minDmg = 0;
        _216.set(0x20);
        return true;
    }

    if (m50(damage, df48, minDmg, f50, f54, f40))
        return true;

    if (param->mGustAffect.ref()) {
        auto* chemical = mActor->getChemicalStuff();
        if (!chemical)
            return false;
        if (chemical->_bc & 0x2000) {
            _c0 = chemical->_12c;
            *damage = 0;
            *df48 = 0;
            *f50 = 12;
            *f54 = 20;
            *f40 = 2;
            *minDmg = 0;
            return true;
        }
    }
    return false;
}

bool DamageManager::sub_71006D357C(s32 type, s32 eventId, bool flag, s32 damage, s32 df48, u32 minDmg,
                                   u32 f50, s32 f54, s32 f40) {
    callDamageCallbacks_(type, eventId, &damage, &df48, &minDmg, &f50, &f54);

    if (type == 2 && sub_71007A2604(mActor)) {
        const s32 reaction = getDamageFromTypeIndex(f50);
        if (sub_71006E0F24(reaction)) {
            const bool guard = sub_71006E0BD4(reaction) || ksys::act::isPlayerProfile(mActor);
            if ((!guard || (f54 >= 9 && f54 <= 14)) && damage <= 0 && _6c >= 0) {
                if (auto* attack = sub_71007A255C(mActor, _6c)) {
                    if (attack->_e8.hasProcInCalcState())
                        _1f8.sub_710070DCC0(&attack->_e8, true);
                }
            }
        }
    }

    if (!addDamage(type, damage, df48, minDmg, f50, f54, f40))
        return false;

    mDamageType = type;
    _216.change(2, flag);
    auto* ride_info = mActor->getPlayerRideInfo();
    if (ride_info && ride_info->_30 & 1)
        _8c |= 0x20000;
    return true;
}

bool sub_71006D7038(ksys::act::Actor* actor, ksys::act::ActorAtk::Unk_710079e64c::Unk1* info) {
    if (!ksys::act::isAttClientEnabled(actor, "SleepSilentKill") &&
        !ksys::act::isAttClientEnabled(actor, "AwakeSilentKill")) {
        return false;
    }
    if (!info->sub_71007A1F78(0x80000))
        return false;
    if (sub_7100735BA8(&info->_d8, actor))
        return true;
    return sub_7100735D2C(&info->_d8, actor);
}

s32 DamageManager::sub_71006D6D88(ksys::act::ActorAtk::Unk_710079e64c::Unk1* info) {
    if (info->sub_71007A1F68(1))
        return 0;
    if (info->sub_71007A1F68(2))
        return 1;
    if (info->sub_71007A1F68(4))
        return 2;
    if (info->sub_71007A1F68(8))
        return 3;
    if (info->sub_71007A1F68(0x2000))
        return 5;
    if (info->sub_71007A1F68(0x10))
        return 4;
    if (info->sub_71007A1F68(0x400))
        return 14;
    if (info->sub_71007A1F68(0x1000))
        return 16;
    if (info->sub_71007A1F68(0x8000))
        return 7;
    if (info->sub_71007A1F68(0x10000))
        return 17;
    if (info->sub_71007A1F68(0x800))
        return sub_71006D7FB0(info);
    return -1;
}

bool DamageManager::sub_71006D6EC0(ksys::act::ActorAtk::Unk_710079e64c::Unk1* info) {
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (actor->m151(3) || actor->m151(4))
            return false;
    }
    if (info->sub_71007A1F78(0x80000000)) {
        auto* player = sead::DynamicCast<uking::act::PlayerBase>(mActor);
        if (!player || !player->isDarukProtectionEnabled())
            return false;
    }
    if (info->sub_71007A1F78(8))
        return false;
    if (info->_18 & 1)
        return true;
    return info->_18 & 2;
}

// NON_MATCHING: the original builds the mask 0xb01f0000 with mov + movk (ours: one movn); probably an OR of named
// attack flags.
void DamageManager::sub_71006D7628(s32 type, s32* damage, s32*, u32*, u32*, s32* f54) {
    if (type == 1 || *f54 == -1)
        return;
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return;
    if (actor->m151(4) && actor->m155())
        actor->m149(4);
    if (type == 2) {
        if (_6c < 0)
            return;
        auto* info = ::sub_71007A255C(mActor, _6c);
        if (!info || !info->sub_71007A1F68(0xb01f0000))
            return;
    }
    if (!m56())
        return;
    *damage = s32(actor->m153() * static_cast<f32>(*damage));
    if (*f54 <= 22)
        *f54 = 23;
    actor->m149(3);
}

// NON_MATCHING: register use for the listener addresses and the block order of the no-attack-info paths.
bool DamageManager::sub_71006D5668(s32* damage, s32*, u32* minDmg, u32* f50, s32* f54, s32* f40) {
    auto* actor = mActor;
    if (_f0._30) {
        *f50 = 8;
        *f54 = 7;
        *damage = 0;
        *minDmg = 0;
        *f40 = 4;
        _f0.x();
        _140.x();
        if (!::hasAttackInfo(actor))
            _218 |= 0x20;
        return true;
    }

    if (::hasAttackInfo(actor)) {
        auto* info = ::getAttackInfo(actor, 0);
        if (info) {
            if (_1a8._30 && _1a8._38.mLink == info->_50)
                return false;
            if (info->_18 & 2) {
                if (_140._30) {
                    _140.x();
                    *f50 = 8;
                    *f54 = 8;
                } else {
                    *f50 = 8;
                    *f54 = 7;
                }
                *damage = 0;
                *minDmg = 0;
                *f40 = 0;
                return true;
            }
            if (!_140._30)
                return false;
            _140.x();
            if (!(info->_18 & 1))
                return false;
            *f50 = 8;
            *f54 = 6;
            *damage = 0;
            *minDmg = 0;
            *f40 = 0;
            return true;
        }
    }

    if (!_140._30)
        return false;
    _140.x();
    *f50 = 8;
    *f54 = 6;
    *damage = 0;
    *minDmg = 0;
    *f40 = 1;
    _218 |= 0x10;
    return true;
}

void DamageManager::applyAttackInfoStateChangeDamage() {
    s32 damage = 0;
    u32 minDmg = 0;
    u32 f50 = -1;
    s32 f54 = -1;
    s32 f40 = 0;
    if (!sub_71006D5668(&damage, nullptr, &minDmg, &f50, &f54, &f40)) {
        damage = 0;
        minDmg = 0;
        f50 = -1;
        f54 = -1;
        f40 = 0;
    }
    sub_71006D357C(3, 1, true, damage, 0, minDmg, f50, f54, f40);
    _1a8.x();
}

void DamageManager::handleDamageForPlayer(u32* a2, u32* a3, u32* a4, u32* a5, u32* a6) {
    DamageManagerBase::handleDamageForPlayer(a2, a3, a4, a5, a6);
    auto* info = sead::DynamicCast<Struct20_2>(mStruct20_b);
    if (!info)
        return;
    _8c |= info->mField_1C;
    _216.change(0x40, info->mField_30);
    _cc = info->mField_20 * info->mField_2C;
}

bool DamageManager::handleMessage(const ksys::Message& message) {
    if (_f0.m2(message))
        return true;
    if (_140.m2(message))
        return true;
    if (message.getType() != 0x800006e)
        return false;
    auto* payload = static_cast<Unk_7102358dc0_Payload*>(message.getUserData());
    if (!payload)
        return false;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _1a8._38.mLink = payload->mLink;
    }
    _1a8._30 = true;
    _1a8._18 = message.getSource();
    return true;
}

void DamageManager::applyRequestedDamage(const ConditionDamageInfo& info) {
    if ((_212 & 0x40) && !(info.mFlags & 1))
        return;
    if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::Alive) && !(info.mFlags & 0x20))
        return;
    if (info._8 & 0x40)
        _8c |= 4;
    if (info.mFlags & 0x100)
        _8c |= 0x400000;

    s32 f50;
    s32 f54;
    switch (info.mKind) {
    case 2:
        m54(info);
        return;
    case 3:
        sub_71006D888C(info);
        return;
    case 4:
        m55(info);
        return;
    case 6: {
        if (info.mFlags & 2)
            f54 = 29;
        else
            f54 = (info.mFlags & 0x20) ? 28 : 1;
        s32 damage = info.mDamage;
        if (_214 & 0x40)
            damage = (info.mFlags & 1) ? damage : 0;
        if (!sub_71006D357C(6, 5, info.mFlags & 8, damage, 0, 0, 22, f54, 0))
            return;
        _216.change(0x100, info.mFlags & 8);
        if (info.mFlags & 8)
            _88 = info._10;
        return;
    }
    default:
        break;
    }

    // Kinds 7 to 10.
    if ((1 << info.mKind) & 0x780) {
        if (info.mFlags & 2) {
            switch (info.mKind) {
            case 7:
                f50 = 13;
                break;
            case 8:
                f50 = 20;
                break;
            case 9:
                f50 = 19;
                break;
            default:
                f50 = 22;
                break;
            }
            _8c |= 0x1000;
            f54 = 31;
        } else if (info.mKind == 10) {
            f50 = (info.mFlags & 4) ? 21 : 9;
            f54 = (info.mFlags & 4) ? 33 : 0;
        } else if (info.mFlags & 4) {
            f54 = 30;
            f50 = 21;
        } else {
            f54 = (info.mFlags & 0x20) ? 28 : 0;
            switch (info.mKind) {
            case 7:
                f50 = 13;
                break;
            case 8:
                f50 = 20;
                break;
            case 9:
                f50 = 19;
                break;
            default:
                f50 = 22;
                break;
            }
        }
        s32 damage = info.mDamage;
        if (_214 & 0x40)
            damage = (info.mFlags & 1) ? damage : 0;
        sub_71006D357C(6, 5, false, damage, 0, 0, f50, f54, 0);
    } else if (info.mKind == 0 || info.mKind == 1) {
        f54 = (info.mFlags & 0x20) ? 28 : 0;
        f50 = info.mKind == 1 ? 20 : 19;
        s32 damage = info.mDamage;
        if (_214 & 0x40)
            damage = (info.mFlags & 1) ? damage : 0;
        sub_71006D357C(6, 5, false, damage, 0, 0, f50, f54, 0);
    } else if (info.mKind == 11) {
        s32 damage = info.mDamage;
        f54 = (info.mFlags & 0x20) ? 28 : 0;
        if (_214 & 0x40)
            damage = (info.mFlags & 1) ? damage : 0;
        sub_71006D357C(6, 5, false, damage, 0, 0, 17, f54, 0);
    }
}

void DamageManager::m54(const ConditionDamageInfo& info) {
    bool update_type;
    s32 f54;
    if (info.mFlags & 2) {
        _8c |= 0x1000;
        update_type = true;
        f54 = 31;
    } else if (info.mFlags & 0x20) {
        update_type = true;
        f54 = 28;
    } else if (info.mFlags & 0x10) {
        auto* param = getActorDamageParam();
        if (param && param->mProofBurnAtSmallDamage.ref()) {
            update_type = true;
            f54 = 15;
        } else {
            update_type = true;
            f54 = -1;
        }
    } else if (info._8 & 4) {
        update_type = true;
        f54 = 22;
    } else if (info._8 & 2) {
        update_type = true;
        f54 = 21;
    } else if (info._8 & 1) {
        update_type = true;
        f54 = 17;
    } else if (info.mFlags & 1) {
        f54 = 0;
        update_type = true;
    } else {
        update_type = mDamageType == -1;
        f54 = (info.mFlags & 0x40) ? -1 : 18;
    }

    s32 damage = info.mDamage;
    if (_214 & 0x40)
        damage = (info.mFlags & 1) ? damage : 0;
    const u32 prev_f50 = mField_50;
    const s32 prev_type = update_type ? -1 : mDamageType;
    const bool applied = sub_71006D357C(6, 5, info.mFlags & 8, damage, 0, 0, 9, f54, 0);
    if (!update_type) {
        mField_50 = prev_f50;
        mDamageType = prev_type;
        return;
    }
    if (!applied)
        return;
    _216.change(0x100, info.mFlags & 8);
    if (info.mFlags & 8)
        _88 = info._10;
}

void DamageManager::m55(const ConditionDamageInfo& info) {
    s32 f54;
    if (info.mFlags & 2) {
        _8c |= 0x1000;
        f54 = 31;
    } else if (info.mFlags & 0x20) {
        f54 = 28;
    } else if (info.mFlags & 0x10) {
        auto* param = getActorDamageParam();
        if (!param || !param->mProofElecAtSmallDamage.ref())
            return;
        f54 = 15;
    } else if (info.mFlags & 1) {
        f54 = 0;
    } else if (info.mFlags & 0x80) {
        if (info._8 & 4)
            f54 = 22;
        else if (info._8 & 2)
            f54 = 21;
        else
            f54 = (info._8 & 1) ? 17 : -1;
        if (f54 == -1)
            f54 = 4;
    } else {
        f54 = 4;
    }

    if (f54 == -1)
        return;

    if (f54 != 4) {
        s32 damage = info.mDamage;
        if (_214 & 0x40)
            damage = (info.mFlags & 1) ? damage : 0;
        if (!sub_71006D357C(6, 5, info.mFlags & 8, damage, 0, 0, 11, f54, 0))
            return;
        _216.change(0x100, info.mFlags & 8);
        if (info.mFlags & 8)
            _88 = info._10;
        return;
    }

    s32 damage = info.mDamage;
    u32 f50 = 11;
    mField_54 = f54;
    s32 f54_ = f54;
    u32 minDmg = 0;
    s32 df48 = 0;
    callDamageCallbacks_(6, 5, &damage, &df48, &minDmg, &f50, &f54_);
    mDamage += damage;
    if (mDamageType == -1) {
        mField_50 = f50;
        mDamageType = 6;
    }
    mField_54 = f54_;
    _216.change(0x100, info.mFlags & 8);
}

void DamageManager::sub_71006D888C(const ConditionDamageInfo& info) {
    s32 f54;
    if (info.mFlags & 2) {
        _8c |= 0x1000;
        f54 = 31;
    } else if (info.mFlags & 0x20) {
        f54 = 28;
    } else if (info.mFlags & 0x10) {
        auto* param = getActorDamageParam();
        if (!param || !param->mProofIceAtSmallDamage.ref())
            return;
        f54 = 15;
    } else {
        f54 = s32(info.mFlags & 1) - 1;
    }

    s32 damage = info.mDamage;
    if ((_214 & 0x40) && !(info.mFlags & 1))
        damage = 0;

    if (f54 != -1) {
        if (!sub_71006D357C(6, 5, info.mFlags & 8, damage, 0, 0, 10, f54, 0))
            return;
        if (info.mFlags & 8)
            _216.set(0x100);
        else
            _216.reset(0x100);
        return;
    }

    u32 f50 = 10;
    s32 f54_ = 3;
    u32 minDmg = 0;
    s32 df48 = 0;
    callDamageCallbacks_(6, 5, &damage, &df48, &minDmg, &f50, &f54_);
    mDamage += damage;
    if (mDamageType == -1) {
        mField_50 = f50;
        mDamageType = 6;
    }
    mField_54 = f54_;
    _216.change(0x100, info.mFlags & 8);
    if (info.mFlags & 8)
        _88 = info._10;
}

}  // namespace uking::act

// Existing global damage callback cleanup (also called by DynamicActor and Rope).
void sub_7100D2D424(uking::act::DamageManagerBase* manager);

uking::act::DamageManager* gameObjectInitField(ksys::act::Actor* actor, sead::Heap* heap) {
    auto* manager = new (heap, 8) uking::act::DamageManager(actor);
    if (!manager)
        return nullptr;

    const s32 num_callbacks = manager->getNumCallbacks();
    if (num_callbacks != 0) {
        manager->mCallbacks.allocBufferAssert(num_callbacks, heap);
        manager->mCallbacks.fill(nullptr);
    }
    if ((num_callbacks == 0 || manager->mCallbacks.getBufferPtr()) && manager->allocStruct20(heap) &&
        manager->initCallbacks(heap)) {
        return manager;
    }

    sub_7100D2D424(manager);
    manager->preDelete1();
    manager->preDelete2();
    delete manager;
    return nullptr;
}
