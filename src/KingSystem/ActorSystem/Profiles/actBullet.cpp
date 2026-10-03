#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {

// NON_MATCHING: the non-virtual thunks (0x7100006964...) do not keep &_bd0._10 in a register
Bullet::~Bullet() = default;

Actor* Bullet::m163() {
    if (!_ba0.hasProc())
        return nullptr;
    return sead::DynamicCast<Actor>(_ba0.getProc(nullptr, nullptr));
}

void Bullet::sub_71000048BC(BaseProc* proc) {
    _b90.acquire(proc, false);
}

void Bullet::sub_71000048C8(const BaseProcLink& link) {
    _b90 = link;
}

void Bullet::sub_710000497C(BaseProc* proc) {
    _ba0.acquire(proc, false);
}

void Bullet::sub_7100004988(const BaseProcLink& link) {
    _ba0 = link;
}

namespace acc {

// inline-only in the original; name is a guess: the 12 setters below construct the parameter name before
// they look up the bullet (11 identical copies: set a map unit parameter of the Bullet's RootAi).
template <bool UseAiTreeParams = false, typename T>
static inline void setBulletParam(const Bullet* self, BaseProc* owner, const sead::SafeString& key,
                                  AIDefParamType type, T value) {
    if (auto* bullet = self->getBulletOwnedByMaybe(owner)) {
        auto* root_ai = bullet->getRootAi();
        auto& params = UseAiTreeParams ? root_ai->getAiTreeParams() : root_ai->getMapUnitParams();
        params.setAITreeVariable(key, type, value);
    }
}

static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

BaseProcLink& Bullet::sub_71000056E4() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    if (sead::IsDerivedFrom<act::Bullet>(actor))
        return static_cast<act::Bullet*>(actor)->_ba0;
    return getDummyBaseProcLink();
}


act::Bullet* Bullet::getBulletOwnedByMaybe(BaseProc* owner) const {
    auto* bullet = sead::DynamicCast<act::Bullet>(static_cast<Actor*>(getProcIfActor(mProc)));
    if (bullet && bullet->isSleep() && bullet->_bd0._0.hasProcById(owner))
        return bullet;
    return nullptr;
}

bool Bullet::sub_71000057DC() const {
    auto* bullet = sead::DynamicCast<act::Bullet>(static_cast<Actor*>(getProcIfActor(mProc)));
    if (!bullet)
        return false;
    return bullet->_cf4 >> 1 & 1;
}

bool Bullet::sub_71000058D4() const {
    auto* bullet = sead::DynamicCast<act::Bullet>(static_cast<Actor*>(getProcIfActor(mProc)));
    if (!bullet)
        return false;
    return bullet->_cf4 >> 8 & 1;
}

f32 Bullet::sub_71000059CC() const {
    auto* bullet = sead::DynamicCast<act::Bullet>(static_cast<Actor*>(getProcIfActor(mProc)));
    if (!bullet)
        return 1.0f;
    return bullet->_cc0;
}

void Bullet::setIsUseAtCollision(bool value, BaseProc* owner) {
    setBulletParam(this, owner, "IsUseAtCollision", AIDefParamType::Bool, value);
}

void Bullet::setAttackPower(s32 value, BaseProc* owner) {
    setBulletParam(this, owner, "AttackPower", AIDefParamType::Int, value);
}

void Bullet::setAttackAttr(s32 value, BaseProc* owner) {
    setBulletParam(this, owner, "AttackAttr", AIDefParamType::Int, value);
}

void Bullet::setAttackType(s32 value, BaseProc* owner) {
    setBulletParam(this, owner, "AttackType", AIDefParamType::Int, value);
}

void Bullet::setCutGrassType(s32 value, BaseProc* owner) {
    setBulletParam(this, owner, "CutGrassType", AIDefParamType::Int, value);
}

void Bullet::setRange(f32 value, BaseProc* owner) {
    setBulletParam(this, owner, "Range", AIDefParamType::Float, value);
}

void Bullet::setScaleTime(f32 value, BaseProc* owner) {
    setBulletParam(this, owner, "ScaleTime", AIDefParamType::Float, value);
}

void Bullet::setAttackTarget(s32 value, BaseProc* owner) {
    setBulletParam(this, owner, "AttackTarget", AIDefParamType::Int, value);
}

void Bullet::setAttackDirType(s32 value, BaseProc* owner) {
    setBulletParam(this, owner, "AttackDirType", AIDefParamType::Int, value);
}

void Bullet::setGolemPartInitialIceMagic(bool value, BaseProc* owner) {
    setBulletParam<true>(this, owner, "GolemPartInitialIceMagic", AIDefParamType::Bool, value);
}

void Bullet::setGolemPartInitialBurn(bool value, BaseProc* owner) {
    setBulletParam<true>(this, owner, "GolemPartInitialBurn", AIDefParamType::Bool, value);
}

void Bullet::setXLinkKey(const sead::SafeString& value, BaseProc* owner) {
    const sead::SafeString key = "XLinkKey";
    if (auto* bullet = getBulletOwnedByMaybe(owner))
        bullet->getRootAi()->getMapUnitParams().setString(value, key);
}

// NON_MATCHING: the original schedules `orr w0, wzr, #1` after the store to *out
bool Bullet::getMapUnitParamF32(f32* out, const sead::SafeString& key, BaseProc* owner) {
    if (auto* bullet = getBulletOwnedByMaybe(owner)) {
        const f32* value = nullptr;
        if (!bullet->getRootAi()->getMapUnitParam(&value, key))
            return false;
        *out = *value;
        return true;
    }
    return false;
}

// NON_MATCHING: the original schedules `orr w0, wzr, #1` after the final 8-byte store
bool Bullet::getMapUnitParamVec3(sead::Vector3f* out, const sead::SafeString& key, BaseProc* owner) {
    if (auto* bullet = getBulletOwnedByMaybe(owner)) {
        const sead::Vector3f* value = nullptr;
        if (!bullet->getRootAi()->getMapUnitParam(&value, key))
            return false;
        out->set(*value);
        return true;
    }
    return false;
}

bool Bullet::isReflectThrownBullet() const {
    auto* bullet = sead::DynamicCast<act::Bullet>(static_cast<Actor*>(getProcIfActor(mProc)));
    if (bullet) {
        bool* value;
        if (bullet->getRootAi()->getAITreeVariable(&value, "IsReflectThrownBullet"))
            return *value;
    }
    return false;
}

void Bullet::sub_710000634C(BaseProc* proc, BaseProc* owner) {
    if (auto* bullet = getBulletOwnedByMaybe(owner))
        bullet->_b90.acquire(proc, false);
}

void Bullet::sub_710000638C(BaseProc* proc, BaseProc* owner) {
    if (auto* bullet = getBulletOwnedByMaybe(owner))
        bullet->_ba0.acquire(proc, false);
}

void Bullet::sub_71000063CC(f32 value, BaseProc* owner) {
    if (auto* bullet = getBulletOwnedByMaybe(owner))
        bullet->_cf8 = value;
}

void Bullet::sub_71000063F4(f32 factor, BaseProc* owner) {
    if (auto* bullet = getBulletOwnedByMaybe(owner)) {
        if (auto* body = bullet->getMainBody())
            body->setGravityFactor(factor);
    }
}

}  // namespace acc

}  // namespace ksys::act
