#include "Game/AI/Action/actionEquipedRod.h"
#include <cmath>
#include "KingSystem/Utils/MathUtil.h"
#include <math/seadMatrixCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectMasterSword.h"

#include "Game/AI/aiUnk_7102407678.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectRod.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::action {

EquipedRod::EquipedRod(const InitArg& arg) : EquipedAction(arg) {}

EquipedRod::~EquipedRod() = default;

// NON_MATCHING: the timer's zero and rate stores are paired differently.
void EquipedRod::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedAction::enter_(params);
    _7c.reset(0.0f);
    _88.value = 0.0f;
    _88.previous_value = 0.0f;
    auto* actor = mActor;
    _88.rate = -1.0f;
    _94 = 0;
    _98 = false;
    _99 = false;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(actor);
    if (weapon) {
        if (auto* rod = weapon->getParam()->getRes().mGParamList->getRod()) {
            _9c = rod->mChargeMagicInterval.ref();
            _a0 = rod->mChargeMagicNum.ref();
            _78 = rod->mMagicRange.ref();
        }
    }
}

// NON_MATCHING: rotation arithmetic, vector loads and register allocation differ.
bool EquipedRod::sub_7100110900(sead::Matrix34f* out) {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!weapon)
        return false;
    const sead::Vector3f global_up = sead::Vector3f::ey;
    if (sub_7100111EB8()) {
        const sead::Vector3f position = *weapon->getAttackPosMaybe();
        sead::Vector3f direction = *weapon->sub_71002EE46C() - position;
        direction.normalize();
        ksys::util::sub_71011F0260(out, direction, global_up, position, false);
        if (weapon->isMasterSword()) {
            sead::Matrix33f rotation;
            rotation.makeR(sead::Vector3f::ez * *mAxisYAngle_s);
            sead::Matrix34CalcCommon<f32>::multiply(*out, *out, rotation);
        }
        return true;
    }
    auto* parent = weapon->getParentActor();
    if (!parent)
        return false;
    sead::Vector3f position = parent->getMtx().getTranslation();
    sead::Vector3f direction = parent->getMtx().getBase(2);
    if (_98) {
        direction = -parent->getMtx().getBase(0);
        f32 step = sead::Mathf::pi2();
        f32 offset = 0.0f;
        if (_a0 >= 1) {
            step /= f32(_a0);
            offset = sead::Mathf::piHalf() - step;
            if (_99) {
                offset = sead::Mathf::pi() - offset;
                step = -step;
            }
        }
        sead::Matrix33f rotation;
        rotation.makeR(sead::Vector3f::ey * (offset + step * f32(_94)));
        direction.rotate(rotation);
    }
    position.x += direction.x;
    position.z += direction.z;
    position.y = weapon->getMtx()(1, 3) + *mMagicCreateYOffset_s;
    if (*mIsCreateWeaponPosOffset_s)
        weapon->getMtx().getTranslation(position);
    if (ksys::act::isEnemyProfile(parent) && weapon->_d38 &&
        s32(weapon->_d38->sub_71002EF74C()) > 0) {
        const sead::Vector3f& target = sub_71005D93CC(parent);
        const f32 distance = std::sqrt((target.x - position.x) * (target.x - position.x) +
                                       (target.z - position.z) * (target.z - position.z));
        direction = sead::Vector3f(position.x + distance * direction.x, target.y,
                                  position.z + distance * direction.z) - position;
        direction.normalize();
    }
    if (!_98 && weapon->isParentPlayer() && weapon->_d38 &&
        s32(weapon->_d38->sub_71002EF74C()) > 0) {
        auto* player = sead::DynamicCast<ksys::act::PlayerBase>(parent);
        sead::Vector3f target;
        if (player && player->m352(&target)) {
            target.y += 1.0f;
            direction = target - position;
            direction.normalize();
        }
    }
    if (*mIsAxisYTop_s) {
        ksys::util::sub_71011F0260(out, direction, global_up, position, false);
        return true;
    }
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&weapon->getParentLink(), &accessor);
    const auto& parent_matrix = accessor.getActorMtx();
    sead::Vector3f up = weapon->getMtx().getBase(1);
    const u8 flags = weapon->_c4c ? weapon->_c20._14 : weapon->_cfc;
    if (flags & 0x20) {
        const u32 state = weapon->_af8._0 == 9 ? weapon->_af8._38 : weapon->_c20._10;
        if (state - 2 < 2)
            up.set(-parent_matrix(2, 1), parent_matrix(1, 1), parent_matrix(0, 1));
        else if (state < 2)
            parent_matrix.getBase(up, 1);
    }
    ksys::util::sub_71011F0260(out, direction, up, position, false);
    return true;
}

// NON_MATCHING: matrix copying and rotation arithmetic have different code generation.
void EquipedRod::sub_7100111320(const sead::Matrix34f* matrix,
                              const sead::Vector3f* velocity, s32 index) {
    auto* unit = sead::DynamicCast<ai::Unk_7102407678>(*mMagicCreateUnit_a);
    if (!unit || u32(index) >= 8)
        return;
    auto& handle = unit->_18[index];
    auto* actor = sead::DynamicCast<ksys::act::Actor>(handle.getProc());
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!actor || !weapon)
        return;
    auto* parent = weapon->getParentActor();
    if (!parent)
        return;
    sead::Vector3f position = matrix->getTranslation();
    sead::Matrix34f adjusted;
    const sead::Matrix34f* initial_matrix = matrix;
    if (sub_7100112A90(&position, &position, &sead::Vector3f::zero)) {
        adjusted = *matrix;
        adjusted.setTranslation(position);
        initial_matrix = &adjusted;
    }
    actor->setMatrix(*initial_matrix, nullptr);
    actor->setVelocity(velocity, nullptr);
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor)) {
        bullet->sub_71000048BC(parent);
        bullet->sub_710000497C(parent);
        if (auto* body = actor->getMainBody()) {
            f32 gravity = weapon->getParam()->getRes().mGParamList->getRod()->mMagicGravity.ref();
            if (weapon->m142())
                gravity = weapon->getParam()->getRes().mGParamList->getRod()->mMagicGravityByEnemy.ref();
            body->setGravityFactor(gravity);
        }
        if (*mIsCreateWeaponPosOffset_s) {
            adjusted = *matrix;
            adjusted.setTranslation(weapon->getMtx().getTranslation());
            sead::Matrix34f offset;
            offset.makeRT(sead::Vector3f::zero, *mCreatePosOffset_s);
            adjusted *= offset;
            position = adjusted.getTranslation();
            if (_98) {
                position = parent->getMtx().getTranslation();
                position.y = weapon->getMtx()(1, 3);
            }
            position += *velocity;
            sead::Vector3f direction = *velocity;
            const f32 speed = direction.normalize();
            direction = sead::Vector3f(parent->getMtx()(0, 3) + _78 * direction.x,
                                       position.y + _78 * direction.y,
                                       parent->getMtx()(2, 3) + _78 * direction.z) - position;
            direction.normalize();
            direction *= speed;
            sub_7100112A90(&position, &position, &direction);
            adjusted.setTranslation(position);
            actor->setMatrix(adjusted, nullptr);
            actor->setVelocity(&direction, nullptr);
        }
        bullet->_cf4 &= ~8;
        actor->setFlag(ksys::act::Actor::ActorFlag::_2c, true);
        handle.releaseAndWakeProc();
        actor->getRootAi()->getAiTreeParams().setAITreeVariable("AttackLevel", ksys::AIDefParamType::Int, _a4);
    } else {
        handle.releaseAndWakeProc();
    }
    if (!weapon->isMasterSword() && weapon->isParentPlayer()) {
        f32 charge = weapon->_d38 ? f32(s32(weapon->_d38->sub_71002EF74C())) : 0.0f;
        if (_a0 > 0)
            charge /= f32(_a0);
        if (weapon->_d38)
            weapon->_d38->sub_71002EF828(charge);
        if (_94 == 1)
            weapon->setDamage(1);
        else if (_a0 <= _94)
            _a4 = 1;
        if (weapon->_d38)
            weapon->_d38->_18 |= 4;
    }
}

// NON_MATCHING: matrix copying and rotation arithmetic have different code generation.
void EquipedRod::sub_7100111FF0(const sead::Matrix34f* matrix,
                              const sead::Vector3f* velocity) {
    auto* unit = sead::DynamicCast<ai::Unk_7102407678>(*mMagicCreateUnit_a);
    if (!unit)
        return;
    auto& handle = unit->_8;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(handle.getProc());
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!actor || !weapon)
        return;
    auto* parent = weapon->getParentActor();
    if (!parent)
        return;
    sead::Vector3f position = matrix->getTranslation();
    sead::Matrix34f adjusted;
    const sead::Matrix34f* initial_matrix = matrix;
    if (sub_7100112A90(&position, &position, &sead::Vector3f::zero)) {
        adjusted = *matrix;
        adjusted.setTranslation(position);
        initial_matrix = &adjusted;
    }
    actor->setMatrix(*initial_matrix, nullptr);
    actor->setVelocity(velocity, nullptr);
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor)) {
        bullet->sub_71000048BC(parent);
        bullet->sub_710000497C(parent);
        if (auto* body = actor->getMainBody()) {
            f32 gravity = weapon->getParam()->getRes().mGParamList->getRod()->mMagicGravity.ref();
            if (weapon->m142())
                gravity = weapon->getParam()->getRes().mGParamList->getRod()->mMagicGravityByEnemy.ref();
            body->setGravityFactor(gravity);
        }
        if (*mIsCreateWeaponPosOffset_s && !sub_7100111EB8()) {
            adjusted = *matrix;
            adjusted.setTranslation(weapon->getMtx().getTranslation());
            sead::Matrix34f offset;
            offset.makeRT(sead::Vector3f::zero, *mCreatePosOffset_s);
            adjusted *= offset;
            position = adjusted.getTranslation();
            if (_98) {
                position = parent->getMtx().getTranslation();
                position.y = weapon->getMtx()(1, 3);
            }
            position += *velocity;
            sead::Vector3f direction = *velocity;
            const f32 speed = direction.normalize();
            direction = sead::Vector3f(parent->getMtx()(0, 3) + _78 * direction.x,
                                       position.y + _78 * direction.y,
                                       parent->getMtx()(2, 3) + _78 * direction.z) - position;
            direction.normalize();
            direction *= speed;
            sub_7100112A90(&position, &position, &direction);
            adjusted.setTranslation(position);
            actor->setMatrix(adjusted, nullptr);
            actor->setVelocity(&direction, nullptr);
        }
        if (weapon->isMasterSword()) {
            if (!weapon->sub_71002ED934())
                return;
            const f32 scale = weapon->sub_71002ED9B0();
            f32 power;
            const bool true_form = weapon->isTrueFormMasterSword();
            auto* params = weapon->getParam()->getRes().mGParamList;
            if (true_form) {
                power = params->getMasterSword()->mTrueFormMagicPower.ref();
                if (params->getMasterSword()->mTrueFormMagicPower.ref() < 0) {
                    auto* rod = params->getRod();
                    power = rod ? f32(rod->mMagicPower.ref() +
                                      ksys::gdt::getFlag_MasterSword_Add_BeamPower(false)) : 0.0f;
                }
            } else {
                auto* rod = params->getRod();
                power = rod ? f32(rod->mMagicPower.ref() +
                                  ksys::gdt::getFlag_MasterSword_Add_BeamPower(false)) : 0.0f;
            }
            bullet->_ca8 = scale;
            bullet->_cac = power * weapon->_af8._30;
        }
        bullet->_cf4 |= 8;
        const s32 attack_direction = weapon->_af8._0 == 9 ? weapon->_af8._38 : weapon->_c20._10;
        actor->getRootAi()->getAiTreeParams().setAITreeVariable("AttackDirType", ksys::AIDefParamType::Int, attack_direction);
        actor->setFlag(ksys::act::Actor::ActorFlag::_2c, true);
        handle.releaseAndWakeProc();
        actor->getRootAi()->getAiTreeParams().setAITreeVariable("AttackLevel", ksys::AIDefParamType::Int, _a4);
    } else {
        handle.releaseAndWakeProc();
    }
    if (weapon->isParentPlayer()) {
        if (!weapon->isMasterSword()) {
            weapon->setDamage(1);
            if (weapon->_d38)
                weapon->_d38->sub_71002EF75C();
            _a4 = 1;
            if (weapon->_d38)
                weapon->_d38->_18 |= 4;
        } else if (!weapon->isTrueFormMasterSword()) {
            weapon->setDamage(1);
        }
    }
}

bool EquipedRod::sub_7100111184(sead::Vector3f* out, const sead::Matrix34f* matrix) {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!weapon)
        return false;
    matrix->getBase(*out, 2);
    const bool thrown = sub_7100111EB8();
    auto* rod = weapon->getParam()->getRes().mGParamList->getRod();
    if (thrown) {
        *out *= rod->mMagicSpeedByThrow.ref() / 30.0f;
    } else {
        f32 speed = rod->mMagicSpeed.ref();
        if (weapon->m142())
            speed = weapon->getParam()->getRes().mGParamList->getRod()->mMagicSpeedByEnemy.ref();
        *out *= speed / 30.0f;
        *out += *mMagicShootVelOffset_s;
    }
    return true;
}

// NON_MATCHING: vector load pairing and cleanup branches differ.
bool EquipedRod::sub_7100112A90(sead::Vector3f* out, const sead::Vector3f* a,
                              const sead::Vector3f* b) {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!weapon)
        return false;
    auto* parent = weapon->getParentActor();
    if (!parent)
        return false;
    sead::Vector3f start;
    parent->getMtx().getTranslation(start);
    start.y = weapon->getMtx()(1, 3);
    const sead::Vector3f end = *a + *b;
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.setStartAndEnd(start, end);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;
    *out = start;
    return true;
}

bool EquipedRod::sub_7100111C48() {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!weapon)
        return false;
    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(weapon->getParentActor());
    return player && player->m296() == 1;
}

bool EquipedRod::sub_7100111AC4() {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!weapon || weapon->isMasterSword())
        return false;
    if (!weapon->_c4c)
        return false;
    if (!(weapon->_c20._14 & 8))
        return false;
    if (weapon->_d09)
        return false;
    if (weapon->_c20._0 == 2)
        return false;
    auto* unit = sead::DynamicCast<ai::Unk_7102407678>(*mMagicCreateUnit_a);
    if (!unit)
        return false;
    for (s32 i = 0; i < _a0; ++i) {
        if (i >= 8)
            return false;
        if (!unit->_18[i].isProcReady())
            return false;
    }
    return true;
}

bool EquipedRod::sub_7100111D60() {
    auto* unit = sead::DynamicCast<ai::Unk_7102407678>(*mMagicCreateUnit_a);
    if (!unit)
        return false;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!weapon || weapon->isMasterSword())
        return false;
    if (!unit->_8.isProcReady())
        return false;
    if (!weapon->_c4c)
        return false;
    if ((weapon->_c20._0 | 2) != 2)
        return false;
    if (!weapon->m214())
        return false;
    if (weapon->_d09)
        return false;
    return weapon->_c20._0 != 2;
}

bool EquipedRod::sub_7100111EB8() {
    auto* unit = sead::DynamicCast<ai::Unk_7102407678>(*mMagicCreateUnit_a);
    if (!unit)
        return false;
    auto& handle = unit->_8;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    return handle.isProcReady() && weapon && weapon->_af8._0 == 9 && weapon->m214();
}

bool EquipedRod::sub_7100112850() {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!weapon)
        return false;
    if (weapon->_d38 && (weapon->_d38->_18 & 1))
        return false;
    auto* weapon2 = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (weapon2 && weapon2->_c4c && (weapon2->_c20._0 | 2) == 2 && !weapon2->m214())
        return true;
    return sub_7100112C20();
}

bool EquipedRod::sub_7100112C20() {
    auto* unit = sead::DynamicCast<ai::Unk_7102407678>(*mMagicCreateUnit_a);
    if (!unit)
        return false;
    auto& handle = unit->_8;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    return handle.isProcReady() && weapon && weapon->_af8._0 == 9 && !weapon->m214();
}

void EquipedRod::leave_() {
    EquipedAction::leave_();
}

void EquipedRod::loadParams_() {
    EquipedAction::loadParams_();
    getStaticParam(&mMagicCreateYOffset_s, "MagicCreateYOffset");
    getStaticParam(&mMagicShootVelOffset_s, "MagicShootVelOffset");
    getStaticParam(&mIsAxisYTop_s, "IsAxisYTop");
    getStaticParam(&mIsCreateWeaponPosOffset_s, "IsCreateWeaponPosOffset");
    getStaticParam(&mCreatePosOffset_s, "CreatePosOffset");
    getStaticParam(&mAxisYAngle_s, "AxisYAngle");
    getAITreeVariable(&mMagicCreateUnit_a, "MagicCreateUnit");
}

// NON_MATCHING: timer stores, comparisons and register allocation differ.
void EquipedRod::calc_() {
    EquipedAction::calc_();
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!weapon)
        return;

    sead::Matrix34f matrix;
    sead::Vector3f velocity;
    if (!_98) {
        if (sub_7100111AC4()) {
            _99 = sub_7100111C48();
            _98 = true;
            if (sub_7100110900(&matrix) && sub_7100111184(&velocity, &matrix)) {
                _a4 = weapon->_c4c ? weapon->_c20._24 : weapon->_d14;
                _88.reset(f32(_9c));
                _94 = 1;
                s32 index = 0;
                if (auto* charge = weapon->_d38) {
                    if (charge->_18 & 1) {
                        charge->_18 |= 4;
                        return;
                    }
                    charge->_14 = charge->sub_71002EF74C();
                    charge->_18 &= ~1;
                    index = _94 - 1;
                }
                sub_7100111320(&matrix, &velocity, index);
            }
        } else {
            if ((!sub_7100111D60() && !sub_7100111EB8()) || !sub_7100110900(&matrix) ||
                !sub_7100111184(&velocity, &matrix)) {
                if (_7c.value <= sead::Mathf::epsilon()) {
                    if (sub_7100112850()) {
                        if (weapon->_d38)
                            weapon->_d38->sub_71002EF850();
                        return;
                    }
                    if (!weapon->_d38 || !(weapon->_d38->_18 & 1))
                        return;
                    auto* current_weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
                    if (!current_weapon)
                        return;
                    if ((!current_weapon->_c4c || (current_weapon->_c20._0 | 2) != 2) &&
                        current_weapon->_af8._0 != 9)
                        return;
                    if (weapon->_d38)
                        weapon->_d38->_18 |= 4;
                    return;
                }
                _7c.update();
                if (!(_7c.value <= sead::Mathf::epsilon()))
                    return;
                if (!sub_7100110900(&matrix) || !sub_7100111184(&velocity, &matrix))
                    return;
            } else {
                _a4 = weapon->_c4c ? weapon->_c20._24 : weapon->_d14;
                if (sub_7100111D60()) {
                    auto* current_weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
                    const f32 time = current_weapon ? f32(current_weapon->_c20._20) : 0.0f;
                    _7c.reset(time);
                }
                if (!(_7c.value <= sead::Mathf::epsilon()))
                    return;
            }
            sub_7100111FF0(&matrix, &velocity);
        }
    } else {
        _88.update();
        auto* current_weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
        if (!current_weapon || current_weapon->isMasterSword() || _a0 <= _94 ||
            !(_88.value <= sead::Mathf::epsilon())) {
            if (_a0 <= _94 && weapon->_d38 && !(weapon->_d38->_18 & 1))
                weapon->_d38->sub_71002EF850();
        } else if (sub_7100110900(&matrix) && sub_7100111184(&velocity, &matrix)) {
            const s32 index = _94++;
            _88.reset(f32(_9c));
            if (!weapon->_d38 || !(weapon->_d38->_18 & 1))
                sub_7100111320(&matrix, &velocity, index);
        }
        if (weapon->m184()) {
            if (_94 < _a0 && sub_7100110900(&matrix) && sub_7100111184(&velocity, &matrix)) {
                const s32 index = _94++;
                _88.reset(f32(_9c));
                if (!weapon->_d38 || !(weapon->_d38->_18 & 1)) {
                    sub_7100111320(&matrix, &velocity, index);
                    if (weapon->_d38)
                        weapon->_d38->sub_71002EF850();
                }
            }
            _98 = false;
            _99 = false;
            _94 = 0;
        }
    }
}

}  // namespace uking::action
