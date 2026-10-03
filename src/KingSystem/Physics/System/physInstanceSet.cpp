#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physCharacterControllerParam.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physParamSet.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Resource/Actor/resResourceRagdollBlendWeight.h"

namespace ksys::phys {

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

// NON_MATCHING: the original constructs only the begin iterator (it compares its index with its
// point count); begin() != end() also calls the out-of-line IsEnd constructor
bool InstanceSet::sub_7100FBB4B4() const {
    if (!mRagdollContactPointInfo)
        return false;
    if (mRagdollContactPointInfo->getNumContactPoints() == 0)
        return false;
    return mRagdollContactPointInfo->begin() != mRagdollContactPointInfo->end();
}

s32 InstanceSet::sub_7100FBE7F0(const sead::SafeString& name) const {
    if (auto* param = mParamSet->character_controller)
        return param->findFormIdx(name);
    return -1;
}

void* InstanceSet::sub_7100FBAEDC(s32 idx1, s32 idx2) const {
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

// NON_MATCHING: loop shape (the original increments the index after the end check and re-checks
// the sign of the found index)
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
    s32 idx = 0;
    for (auto& set : mRigidBodySets) {
        if (mRigidBodySets[idx] && name == set.getName())
            break;
        ++idx;
    }
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

}  // namespace ksys::phys
