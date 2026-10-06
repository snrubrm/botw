#include "KingSystem/Physics/System/physInstanceSet.h"
#include <basis/seadNew.h>
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/Ragdoll/physRagdollController.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/CylinderWater/physCylinderWaterRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySetParam.h"
#include "KingSystem/Physics/System/physCharacterControllerParam.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physParamSet.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Resource/Actor/resResourceRagdollConfigList.h"
#include "KingSystem/Resource/Actor/resResourceRagdollBlendWeight.h"

namespace ksys::phys {

bool InstanceSet::sub_7100FBE184(RigidBody* body) const {
    return body->hasFlag(RigidBody::Flag::_20);
}

void InstanceSet::setFlag2() {
    mFlags.set(Flag::_2);
    if (mClothSet != nullptr) {
        mFlags.set(Flag::_2);
        mFlags.set(Flag::DisableDraw);
    }
}

void InstanceSet::clothVisibleStuff() {
    if (mClothSet != nullptr) {
        mFlags.set(Flag::DisableDraw);
    }
}

void InstanceSet::setInDemo() {
    mFlags.set(Flag::InDemo);
}

void InstanceSet::resetInDemo() {
    mFlags.reset(Flag::InDemo);
}

void InstanceSet::clothVisibleStuff_0(s32 setting) {
    if (mFlags.isOn(Flag::InDemo))
        return;

    switch (setting) {
    case -2:
        mFlags.reset(Flag::Cloth2);
        mFlags.set(Flag::Cloth1);
        break;
    case -1:
        mFlags.reset(Flag::Cloth3);
        mFlags.reset(Flag::Cloth2);
        mFlags.reset(Flag::Cloth1);
        mFlags.set(Flag::Cloth2);
        mFlags.set(Flag::Cloth3);
        break;
    case 0:
        mFlags.reset(Flag::Cloth1);
        mFlags.reset(Flag::Cloth2);
        mFlags.set(Flag::Cloth3);
        break;
    case 1:
        mFlags.reset(Flag::Cloth1);
        mFlags.reset(Flag::Cloth2);
        mFlags.reset(Flag::Cloth3);
        break;
    }
}

void InstanceSet::sub_7100FB9BAC(InstanceSet* other) {
    if (other == nullptr)
        return;

    u32 idx = other->sub_7100FB9C2C();
    clothVisibleStuff_0(idx);
}

u32 InstanceSet::sub_7100FB9C2C() const {
    u32 idx;
    if (mFlags.isOn(Flag::Cloth1)) {
        idx = -2;
    } else if (mFlags.isOn(Flag::Cloth2)) {
        idx = -1;
    } else if (mFlags.isOn(Flag::Cloth3)) {
        idx = 0;
    } else {
        idx = 1;
    }
    return idx;
}

void InstanceSet::sub_7100FBA9BC() {
    for (auto& rb : mRigidBodySets) {
        rb.addToWorld();
    }

    for (auto& body : mList) {
        body->addToWorld();
    }

    if (mCharacterController != nullptr)
        mCharacterController->sub_7100F5EC30();
}

void InstanceSet::sub_7100FB9D24() {
    if (mCharacterController)
        mCharacterController->sub_7100F60794();

    for (auto& rb : mRigidBodySets) {
        rb.resetFrozenState();
    }

    for (auto& body : mList) {
        body->resetFrozenState();
    }

    if (mRagdollInstance)
        mRagdollInstance->resetFrozenState();
}

void InstanceSet::sub_7100FB9E90(bool on) {
    if (mCharacterController)
        mCharacterController->sub_7100F60934(on);

    for (auto& rb : mRigidBodySets) {
        rb.setEntityMotionFlag200(on);
    }

    for (auto& body : mList) {
        body->setEntityMotionFlag200(on);
    }

    if (mRagdollInstance)
        mRagdollInstance->setEntityMotionFlag200(on);
}

void InstanceSet::sub_7100FBAA3C() {
    for (auto& rb : mRigidBodySets) {
        rb.removeFromWorld();
    }

    for (auto& body : mList) {
        body->removeFromWorld();
    }

    if (mCharacterController)
        mCharacterController->sub_7100F5EC44();

    if (mRagdollInstance)
        mRagdollInstance->removeFromWorld();
}

bool InstanceSet::sub_7100FBAAC8() {
    bool ok = true;
    for (auto& rb : mRigidBodySets) {
        ok &= rb.removeFromWorldAndResetLinks();
    }

    for (auto& body : mList) {
        ok &= body->removeFromWorldAndResetLinks();
    }

    if (mCharacterController)
        ok &= mCharacterController->sub_7100F5ECC4();

    if (mRagdollInstance)
        ok &= mRagdollInstance->removeFromWorldAndResetLinks();

    return ok;
}

void InstanceSet::sub_7100FB835C() {
    if (_178[0]) {
        System::instance()->removeSystemGroupHandler(_178[0]);
        _178[0] = nullptr;
        _188[0] = nullptr;
    }
    if (_178[1]) {
        System::instance()->removeSystemGroupHandler(_178[1]);
        _178[1] = nullptr;
        _188[1] = nullptr;
    }
}

void InstanceSet::sub_7100FBAC4C(phys::ContactLayer layer) {
    bool sensor = phys::getContactLayerType(layer) != ContactLayerType::Entity;

    for (auto& rb : mRigidBodySets) {
        rb.enableContactLayer(layer);
    }
    if (sensor)
        return;

    if (mRagdollInstance != nullptr)
        mRagdollInstance->enableContactLayer(layer);

    if (mCharacterController != nullptr)
        mCharacterController->enableContactLayer(layer);
}

void InstanceSet::sub_7100FBACE0(phys::ContactLayer layer) {
    bool sensor = phys::getContactLayerType(layer) != ContactLayerType::Entity;

    for (auto& rb : mRigidBodySets) {
        rb.disableContactLayer(layer);
    }
    if (sensor)
        return;

    if (mRagdollInstance != nullptr)
        mRagdollInstance->disableContactLayer(layer);

    // The original calls enableContactLayer here (0x7100f605e4 forwards to RigidBody::enableContactLayer).
    if (mCharacterController != nullptr)
        mCharacterController->enableContactLayer(layer);
}

void InstanceSet::sub_7100FBAD74() {
    for (auto& rb : mRigidBodySets) {
        rb.disableAllContactLayers();
    }
    if (mRagdollInstance != nullptr) {
        mRagdollInstance->setContactNone();
    }
    if (mCharacterController != nullptr) {
        mCharacterController->sub_7100F60604();
    }
}

bool InstanceSet::sub_7100FBB4B4() const {
    if (!mRagdollContactPointInfo)
        return false;
    if (mRagdollContactPointInfo->getNumContactPoints() == 0)
        return false;
    return !mRagdollContactPointInfo->begin().isEnd();
}

s32 InstanceSet::sub_7100FBE7F0(const sead::SafeString& name) const {
    if (auto* param = mParamSet->character_controller)
        return param->findFormIdx(name);
    return -1;
}

RigidBody* InstanceSet::sub_7100FBAEDC(s32 idx1, s32 idx2) const {
    if (mRigidBodySets.size() <= idx1)
        return nullptr;
    return mRigidBodySets[idx1]->getRigidBody(idx2);
}

void InstanceSet::sub_7100FBB00C(phys::RigidBody* body, phys::RigidBodyParam* param) {
    if (body == nullptr)
        return;

    phys::RigidBodyInstanceParam instance_params;
    param->makeInstanceParam(&instance_params);
    if (instance_params.contact_layer == phys::ContactLayer::SensorCustomReceiver) {
        body->setSensorCustomReceiver(instance_params.receiver_mask, _188[body->isSensor()]);
    } else if (instance_params.groundhit_mask) {
        body->setGroundHitMask(instance_params.contact_layer, instance_params.groundhit_mask);
    } else {
        body->setContactLayerAndGroundHitAndHandler(
            instance_params.contact_layer, instance_params.groundhit, _188[body->isSensor()]);
    }
    body->enableGroundCollision(instance_params.no_hit_ground == 0);
    body->enableWaterCollision(instance_params.no_hit_water == 0);
    body->clearSensorReceiverIgnoredLayer();
}

RigidBody* InstanceSet::findRigidBody(const sead::SafeString& name) const {
    for (auto& rb : mRigidBodySets) {
        RigidBody* p = rb.findBodyByHavokName(name);
        if (p != nullptr)
            return p;
    }
    return nullptr;
}

int InstanceSet::sub_7100FBB668(const sead::SafeString& name) const {
    s32 idx = 0;
    for (auto& set : mRigidBodySets) {
        if (mRigidBodySets[idx] && name == set.getName())
            return idx;
        ++idx;
    }
    return -1;
}

RigidBodySet* InstanceSet::findBodyGroupByName(const sead::SafeString& name) {
    const s32 idx = sub_7100FBB668(name);
    if (idx < 0)
        return nullptr;
    return mRigidBodySets[idx];
}

s32 InstanceSet::findContactPointInfo(const sead::SafeString& name) const {
    s32 idx = 0;
    for (auto& info : mContactPointInfo) {
        if (name == info.getName())
            return idx;
        idx++;
    }
    return -1;
}

s32 InstanceSet::findCollisionInfo(const sead::SafeString& name) const {
    s32 idx = 0;
    for (auto& info : mCollisionInfo) {
        if (name == info.getName())
            return idx;
        idx++;
    }
    return -1;
}

void InstanceSet::sub_7100FBD324(bool a1, bool a2) {
    if (a1) {
        if (a2 && (mFlags.getDirect() & 0x18000) == 0x8000 && mClothSet)
            mClothSet->sub_7101218A90();
        mFlags.setDirect(mFlags.getDirect() & ~0x18000u);
    } else {
        mFlags.set(Flag::_8000);
        mFlags.change(Flag::_10000, a2);
    }
}

void InstanceSet::sub_7100FBD3EC(bool on) {
    if (mClothSet)
        mClothSet->_70 = on ? (mClothSet->_70 | 0x8000) : (mClothSet->_70 & ~0x8000u);
}

void InstanceSet::sub_7100FBD410(const sead::Vector3f* vec) {
    if (mClothSet)
        mClothSet->_64 = *vec;
}

void InstanceSet::sub_7100FBD284(const sead::Matrix34f& mtx) {
    if (mFlags.isOff(Flag::_1))
        return;

    if (mFlags.isOn(Flag::_80000000)) {
        sub_7100FBC890(mtx, true, false);
    } else {
        mFlags.reset(Flag::_8);
        if (mFlags.isOn(Flag::_2))
            setMtxAndScale(mtx, false, false, mScale);
    }
    mFlags.reset(Flag::_80000000);

    if (mRagdollInstance == nullptr)
        return;

    if (mRagdollInstance->getWorldState() == RagdollInstance::WorldState::AddedToWorld)
        sub_7100FBC890(mtx, false, false);
}

s32 InstanceSet::sub_7100FBDA2C(const sead::SafeString& name) const {
    if (mRagdollBlendWt == nullptr)
        return -1;

    s32 idx = mRagdollBlendWt->findStateIdx(name);
    if (idx >= 0)
        return idx + 2;

    if (name == "full_dynamic") {
        return 1;
    }
    if (name == "full_key_framed") {
        return 0;
    }

    return -1;
}

void InstanceSet::sub_7100FBC838(s32 idx) {
    idx = sead::Mathi::max(idx, 0);
    if (idx >= _98.size())
        idx = _98.size() - 1;
    if (_112 != idx)
        _98[idx]->reset();
    _112 = idx;
}

// NON_MATCHING: the original loads the controller index (_112) before the size and clamps with two csel
void InstanceSet::sub_7100FBDB5C() {
    s32 idx = _112 > _98.size() - 1 ? _98.size() - 1 : _112;
    idx = _112 < 0 ? 0 : idx;
    _98[idx]->reset();
}

bool InstanceSet::sub_7100FBDB90(s32 idx, f32 factor) {
    if (idx < 0 || idx >= _98.size())
        return false;
    _98[idx]->setFactor(factor);
    return true;
}

bool InstanceSet::sub_7100FBDBD8(s32 idx, s32 bone, f32 weight) {
    if (idx < 0 || idx >= _98.size())
        return false;
    _98[idx]->setBoneWeight(bone, weight);
    return true;
}

bool InstanceSet::sub_7100FBDC24(s32 idx, const sead::SafeString& bone_name, f32 weight) {
    if (idx < 0 || idx >= _98.size())
        return false;
    _98[idx]->setBoneWeight(bone_name, weight);
    return true;
}

bool InstanceSet::sub_7100FC0234() const {
    for (s32 i = 0; i < _100.size(); ++i) {
        if (_100[i]._98)
            return true;
    }
    return false;
}

bool InstanceSet::sub_7100FBD390() const {
    if (!mClothSet)
        return true;
    const s32 size = mClothSet->_18.size();
    for (s32 i = 0; i < size; ++i) {
        if (mClothSet->_18[i]._18 & 4)
            return true;
    }
    return false;
}

void InstanceSet::sub_7100FBDC70(f32 scale) {
    if (!mRagdollConfigList || !mRagdollInstance)
        return;

    const s32 num = sead::Mathi::min(mRagdollInstance->getRigidBodies_().size(),
                                     mRagdollConfigList->getBodyParams().size());
    for (s32 i = 0; i < num; ++i) {
        if (auto* body = mRagdollInstance->getRigidBodies_()[i])
            body->setFrictionScale(mRagdollConfigList->getBodyParams()[i].friction_scale.ref() *
                                   scale);
    }
}

void InstanceSet::sub_7100FBDD40(bool on) {
    mFlags.change(Flag::_40000000, on);

    const s32 num = mRagdollInstance->getRigidBodies_().size();
    for (s32 i = 0; i < num; ++i) {
        if (auto* body = mRagdollInstance->getRigidBodies_()[i]) {
            body->changeFlag40(on);
            body->setLinearVelocity(sead::Vector3f::zero);
            body->setAngularVelocity(sead::Vector3f::zero);
        }
    }
}

bool InstanceSet::sub_7100FBAF18(RigidBody* body) {
    const s32 num_sets = mRigidBodySets.size();
    for (s32 i = 0; i < num_sets; ++i) {
        auto& set_param = mParamSet->getRigidBodySet(i);
        const s32 num = mRigidBodySets(i)->getRigidBodies().size();
        for (s32 j = 0; j < num; ++j) {
            if (sub_7100FBAEDC(i, j) == body) {
                sub_7100FBB00C(body, &set_param.rigid_bodies[j]);
                return true;
            }
        }
    }
    return false;
}

void InstanceSet::sub_7100FBA174() {
    for (auto& set : mRigidBodySets)
        set.triggerScheduledMotionTypeChange();

    for (auto* body : mList)
        body->triggerScheduledMotionTypeChange();

    if (mCharacterController)
        mCharacterController->sub_7100F5F670();
}

// NON_MATCHING: the original keeps `fixed | bit` unnormalised in w20 and truncates it at each use
// (`and w1, w20, #1` / `tst w20, #1`); we normalise it up front
void InstanceSet::sub_7100FBA010(bool fixed) {
    fixed |= (_26 & 0x20) >> 5;
    const bool fixed_ = fixed;
    const bool preserve_velocities = mFlags.isOff(Flag::_800);

    if (mCharacterController)
        mCharacterController->sub_7100F609E4(Fixed(fixed_), PreserveVelocities(preserve_velocities));

    for (auto& set : mRigidBodySets)
        set.setFixed(Fixed(fixed_), PreserveVelocities(preserve_velocities));

    for (auto* body : mList)
        body->setFixed(Fixed(fixed_), PreserveVelocities(preserve_velocities));

    if (mRagdollInstance)
        mRagdollInstance->setFixed(Fixed(fixed_), PreserveVelocities(preserve_velocities));

    mFlags.change(Flag::_40000, fixed_);
}

void InstanceSet::systemGroupHandlerStuff(SystemGroupHandler* handler, ContactLayerType layer_type) {
    if (handler && handler->getLayerType() != layer_type)
        return;

    for (auto& set : mRigidBodySets)
        set.setSystemGroupHandler(handler, layer_type);

    for (auto* body : mList) {
        if (body->getLayerType() == layer_type)
            body->setSystemGroupHandler(handler);
    }

    if (layer_type == ContactLayerType::Entity) {
        if (mRagdollInstance)
            mRagdollInstance->setSystemGroupHandler(handler);
        if (mCharacterController)
            mCharacterController->sub_7100F5EDB4(handler);
    }

    _188[static_cast<int>(layer_type)] = handler;
}

void InstanceSet::sub_7100FBB29C() {
    const s32 num_sets = mRigidBodySets.size();
    for (s32 i = 0; i < num_sets; ++i) {
        auto& set_param = mParamSet->getRigidBodySet(i);
        const s32 num = mRigidBodySets(i)->getRigidBodies().size();
        for (s32 j = 0; j < num; ++j)
            sub_7100FBB00C(sub_7100FBAEDC(i, j), &set_param.rigid_bodies[j]);
    }
}

void InstanceSet::sub_7100FBADDC() {
    const s32 num_sets = mRigidBodySets.size();
    for (s32 i = 0; i < num_sets; ++i) {
        auto& set_param = mParamSet->getRigidBodySet(i);
        const s32 num = mRigidBodySets(i)->getRigidBodies().size();
        for (s32 j = 0; j < num; ++j) {
            auto& param = set_param.rigid_bodies[j];
            if (auto* body = sub_7100FBAEDC(i, j))
                body->changeMotionType(param.getMotionType());
        }
    }

    if (mRagdollInstance)
        mRagdollInstance->changeWorldState(RagdollInstance::WorldState::NotAddedToWorld);
}

void InstanceSet::sub_7100FC0600(RigidBody* body) {
    for (auto* node = mList.front(); node; node = mList.next(node)) {
        if (node->mData == body) {
            mList.erase(node);
            delete node->mData;
            delete node;
            return;
        }
    }
}

CapsuleRigidBody* InstanceSet::sub_7100FC03A0(RigidBodyInstanceParam* param, sead::Heap* heap) {
    auto* body = CapsuleRigidBody::make(param, heap);
    if (body) {
        if (param->groundhit_mask == 0)
            body->setSystemGroupHandler(_188[body->isSensor()]);
        body->setUserTag(mUserTag);
        auto* node = new (heap, 8) sead::TListNode<RigidBody*>(body);
        mList.pushBack(node);
    }
    return body;
}

BoxRigidBody* InstanceSet::sub_7100FC0440(RigidBodyInstanceParam* param, sead::Heap* heap) {
    auto* body = BoxRigidBody::make(param, heap);
    if (body) {
        if (param->groundhit_mask == 0)
            body->setSystemGroupHandler(_188[body->isSensor()]);
        body->setUserTag(mUserTag);
        auto* node = new (heap, 8) sead::TListNode<RigidBody*>(body);
        mList.pushBack(node);
    }
    return body;
}

CylinderWaterRigidBody* InstanceSet::sub_7100FC04E0(RigidBodyInstanceParam* param, sead::Heap* heap) {
    auto* body = CylinderWaterRigidBody::make(param, heap);
    if (body) {
        if (param->groundhit_mask == 0)
            body->setSystemGroupHandler(_188[body->isSensor()]);
        body->setUserTag(mUserTag);
        auto* node = new (heap, 8) sead::TListNode<RigidBody*>(body);
        mList.pushBack(node);
    }
    return body;
}

RigidBody* InstanceSet::sub_7100FC0580(RigidBodyFromShape* shape, sead::Heap* heap) {
    auto* body = shape->clone(heap, nullptr);
    if (body) {
        body->setUserTag(mUserTag);
        auto* node = new (heap, 8) sead::TListNode<RigidBody*>(body);
        mList.pushBack(node);
    }
    return body;
}

bool InstanceSet::sub_7100FBAB68() const {
    for (auto& set : mRigidBodySets) {
        if (!set.hasNoRigidBodyWithFlag8(true))
            return false;
    }
    for (auto& body : mList) {
        if (body->isAddedToWorld())
            return false;
        if (body->isAddingBodyToWorld())
            return false;
    }
    if (mCharacterController) {
        if (mCharacterController->sub_7100F5E954())
            return false;
        if (mCharacterController->sub_7100F635B4())
            return false;
    }
    if (mRagdollInstance) {
        if (mRagdollInstance->isAddedToWorld())
            return false;
        if (mRagdollInstance->isAddingToWorld())
            return false;
    }
    return true;
}

bool InstanceSet::sub_7100FBB374(RigidBody* body) const {
    for (auto& set : mRigidBodySets) {
        auto& bodies = set.getRigidBodies();
        for (s32 i = 0; i < bodies.size(); ++i) {
            if (bodies[i] == body)
                return true;
        }
    }
    for (auto& listed : mList) {
        if (listed == body)
            return true;
    }
    return false;
}

bool InstanceSet::sub_7100FBB420() const {
    for (auto& set : mRigidBodySets) {
        if (set.hasActiveEntityBody())
            return true;
    }
    for (auto& body : mList) {
        if (!body->isSensor() && body->isActive())
            return true;
    }
    if (mRagdollInstance && mRagdollInstance->isAddedToWorld())
        return true;
    return false;
}

SphereRigidBody* InstanceSet::sub_7100FC0300(SphereParam* param, sead::Heap* heap) {
    auto* body = SphereRigidBody::make(param, heap);
    if (body) {
        if (param->groundhit_mask == 0)
            body->setSystemGroupHandler(_188[body->isSensor()]);
        body->setUserTag(mUserTag);
        auto* node = new (heap, 8) sead::TListNode<RigidBody*>(body);
        mList.pushBack(node);
    }
    return body;
}

// NON_MATCHING: the original null-checks the result of ParamSet::getRigidBodySet (a reference here)
bool InstanceSet::sub_7100FBB18C(RigidBodySet* set) {
    for (s32 i = 0; i < mRigidBodySets.size(); ++i) {
        if (mRigidBodySets[i] != set)
            continue;

        auto& set_param = mParamSet->getRigidBodySet(i);
        const s32 num = mRigidBodySets(i)->getRigidBodies().size();
        for (s32 j = 0; j < num; ++j)
            sub_7100FBB00C(sub_7100FBAEDC(i, j), &set_param.rigid_bodies[j]);
        return true;
    }
    return false;
}

RigidBodySet* InstanceSet::findBodyByName(const sead::SafeString& name) const {
    const s32 idx = sub_7100FBB668(name);
    if (idx < 0)
        return nullptr;
    return mRigidBodySets[idx];
}

RigidBody* InstanceSet::findX(const sead::SafeString& a1, const sead::SafeString& a2) const {
    const s32 idx = sub_7100FBB668(a1);
    if (idx < 0)
        return nullptr;
    auto* set = mRigidBodySets[idx];
    if (!set)
        return nullptr;
    return set->findBodyByHavokName(a2);
}

RigidBody* InstanceSet::sub_7100FBB918(const sead::SafeString& a1, const sead::SafeString& a2) const {
    const s32 idx = sub_7100FBB668(a1);
    if (idx < 0)
        return nullptr;
    const RigidBodySet* set = mRigidBodySets[idx];
    if (!set)
        return nullptr;
    return set->findBodyByHavokName(a2);
}

// NON_MATCHING: the tail after the two handler tests is laid out differently (we keep a flag in
// w21 for `!handler`, the original re-tests the handler register)
void InstanceSet::sub_7100FBDFA4(SystemGroupHandler* handler) {
    for (auto& set : mRigidBodySets)
        set.setSystemGroupHandler(handler);

    for (auto* body : mList) {
        if (!handler || handler->getLayerType() == body->getLayerType())
            body->setSystemGroupHandler(handler);
    }

    if (!handler || handler->getLayerType() == ContactLayerType::Entity) {
        if (mRagdollInstance)
            mRagdollInstance->setSystemGroupHandler(handler);
        if (mCharacterController)
            mCharacterController->sub_7100F5EDB4(handler);
    }

    s32 idx;
    if (handler) {
        idx = static_cast<s32>(handler->getLayerType());
    } else {
        _188[0] = nullptr;
        idx = 1;
    }
    _188[idx] = handler;
}

void InstanceSet::sub_7100FBD918(const void* key, s32 value) {
    for (auto& entry : mLinkMatricesMaybe) {
        if (entry._38 == key) {
            entry._40 = value;
            return;
        }
    }
}

void InstanceSet::sub_7100FBD94C(const void* key, bool value) {
    for (auto& entry : mLinkMatricesMaybe) {
        if (entry._38 == key) {
            entry._44 = value;
            return;
        }
    }
}

void InstanceSet::sub_7100FBD984(bool value) {
    for (auto& entry : mLinkMatricesMaybe)
        entry._44 = value;
}

gsys::BoneAccessKey InstanceSet::sub_7100FBDF54(const void* key) const {
    if (key) {
        for (auto& entry : mLinkMatricesMaybe) {
            if (entry._38 == key)
                return entry._30;
        }
    }
    return {};
}

void InstanceSet::sub_7100FB83B8() {
    while (mContactPointInfo.size() >= 1) {
        auto* info = mContactPointInfo.popBack();
        if (!info)
            break;
        ContactPointInfo::free(info);
    }
    while (mCollisionInfo.size() >= 1) {
        auto* info = mCollisionInfo.popBack();
        if (!info)
            break;
        CollisionInfo::free(info);
    }
    mCollisionInfo.freeBuffer();
    mContactPointInfo.freeBuffer();
    if (mRagdollContactPointInfo) {
        ContactPointInfo::free(mRagdollContactPointInfo);
        mRagdollContactPointInfo = nullptr;
    }
}

void InstanceSet::sub_7100FB9DB0(bool use) {
    if (mCharacterController)
        mCharacterController->sub_7100F607CC(use);
    for (auto& set : mRigidBodySets)
        set.setUseSystemTimeFactor(use);
    for (auto* body : mList)
        body->setUseSystemTimeFactor(use);
    if (mRagdollInstance)
        mRagdollInstance->setUseSystemTimeFactor(use);
}

void InstanceSet::sub_7100FBA0F4() {
    for (auto& set : mRigidBodySets)
        set.updateMotionTypeRelatedFlags();
    for (auto* body : mList)
        body->updateMotionTypeRelatedFlags();
    if (mCharacterController)
        mCharacterController->sub_7100F5F5A0();
}

void InstanceSet::sub_7100FBD434(u8 type) {
    for (auto& set : mRigidBodySets)
        set.callRigidBody_x_7(type);
    for (auto* body : mList)
        body->x_17(type);
}

bool InstanceSet::sub_7100FBDE90(RigidBody* body) const {
    if (!body)
        return false;
    if (body->hasFlag(RigidBody::Flag::IsSensor) && body->getLinkedRigidBody() &&
        !body->isSensorMotionFlag40000Set())
        return true;
    for (auto& entry : mLinkMatricesMaybe) {
        if (entry._38 == body)
            return true;
    }
    return false;
}

bool InstanceSet::sub_7100FBDF08(const void* key) const {
    if (!key)
        return false;
    for (auto& entry : mLinkMatricesMaybe) {
        if (entry._38 == key)
            return true;
    }
    return false;
}

InstanceSet::Unk2* InstanceSet::sub_7100FC00EC(s32 idx) {
    if (idx < 0 || idx >= _100.size())
        return nullptr;
    return &_100[idx];
}

sead::Buffer<InstanceSet::Unk2>* InstanceSet::sub_7100FC0124() {
    return &_100;
}

}  // namespace ksys::phys
