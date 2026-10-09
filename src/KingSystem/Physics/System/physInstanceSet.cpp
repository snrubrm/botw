#include "KingSystem/Physics/System/physInstanceSet.h"
#include <basis/seadNew.h>
#include <resource/seadArchiveRes.h>
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/Cloth/physClothParam.h"
#include "KingSystem/Physics/Ragdoll/physRagdollController.h"
#include "KingSystem/Physics/Rig/physModelBoneAccessor.h"
#include "KingSystem/Physics/Ragdoll/physRagdollParam.h"
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
#include "KingSystem/Physics/System/physContactInfoParam.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physParamSet.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include "KingSystem/Physics/Cloth/physClothResource.h"
#include "KingSystem/Physics/Ragdoll/physRagdollResource.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyResource.h"
#include "KingSystem/Physics/SupportBone/physSupportBoneParam.h"
#include "KingSystem/Physics/SupportBone/physSupportBoneResource.h"
#include "KingSystem/Resource/Actor/resResourceRagdollConfigList.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/Actor/resResourceRagdollBlendWeight.h"

namespace ksys::phys {

// Loads a physics resource from the RomFS or, failing that, from the actor pack.
// Placeholder name: the original has four copies of this function (RigidBodyResource, RagdollResource,
// ClothResource, SupportBoneResource; the last three have no RTTI of their own).
// NON_MATCHING: the original combines `in_pack` and `res == nullptr` of the retry condition with a single `and`
// (`in_pack & (res == nullptr)` matches; not applied)
template <typename T>
T* loadFromRomOrActorPack(res::Handle* handle, const sead::SafeString& path, res::Handle* pack_handle,
                          const sead::SafeString& actor_name, bool) {
    if (!handle)
        return nullptr;

    T* res;
    {
        res::SimpleLoadRequest req;
        req._8 = true;
        req.mRequester = actor_name;
        req.mPath = path;
        req.mLaneId = 2;
        res = sead::DynamicCast<T>(handle->load(path, &req));
    }
    if (res)
        return res;

    if (!pack_handle->isSuccess())
        act::ActorParamMgr::instance()->loadActorPack(pack_handle, actor_name, 1);

    bool in_pack = false;
    if (pack_handle && !act::ActorParamMgr::instance()->checkPath(path)) {
        auto* pack = sead::DynamicCast<sead::ArchiveRes>(pack_handle->getResource());
        if (pack)
            in_pack = pack->getFile(path) != nullptr;
    }

    res::LoadRequest req;
    req.mLoadDataAlignment = 0x10;
    req.mRequester = "physInstanceSet";
    req.mPackHandle = in_pack ? pack_handle : nullptr;
    res::Handle::Status status = res::Handle::Status::NoFile;
    res = sead::DynamicCast<T>(handle->load(path, &req, &status));
    if (!res && in_pack) {
        req.mPackHandle = nullptr;
        res = sead::DynamicCast<T>(handle->load(path, &req, &status));
    }
    return res;
}

template RigidBodyResource* loadFromRomOrActorPack<RigidBodyResource>(
    res::Handle*, const sead::SafeString&, res::Handle*, const sead::SafeString&, bool);
template RagdollResource* loadFromRomOrActorPack<RagdollResource>(
    res::Handle*, const sead::SafeString&, res::Handle*, const sead::SafeString&, bool);
template ClothResource* loadFromRomOrActorPack<ClothResource>(
    res::Handle*, const sead::SafeString&, res::Handle*, const sead::SafeString&, bool);
template SupportBoneResource* loadFromRomOrActorPack<SupportBoneResource>(
    res::Handle*, const sead::SafeString&, res::Handle*, const sead::SafeString&, bool);

// NON_MATCHING: the original keeps the ragdoll param pointer in the register that becomes the string `this`
// (`ldr x8, [x21, #0x98]!`); ours computes the +0x98 address up front and needs one more saved register
bool InstanceSet::sub_7100FBE808(sead::Heap* heap, res::Handle* pack_handle) {
    auto* ragdoll = mParamSet->ragdoll;
    if (!ragdoll || ragdoll->ragdoll_setup_file_path.ref().isEmpty())
        return false;

    mRagdollInstance = new (heap) RagdollInstance(_178[0]);
    mRagdollResHandle = new (heap) res::Handle;
    const sead::SafeString& file = ragdoll->ragdoll_setup_file_path.ref();
    sead::FormatFixedSafeString<128> path("Physics/Ragdoll/%s", file.cstr());
    loadFromRomOrActorPack<RagdollResource>(mRagdollResHandle, path, pack_handle, mName, true);
    return true;
}

bool InstanceSet::sub_7100FBF368(sead::Heap* heap, Unk_7102519a10* arg, res::Handle* pack_handle) {
    auto* cloth_set = mParamSet->cloth_set;
    if (!arg && !cloth_set)
        return false;

    const sead::SafeString name = arg ? arg->getClothFileName() : cloth_set->cloth_setup_file_path.ref();
    if (name.isEmpty())
        return false;

    mClothResHandle = new (heap) res::Handle;
    sead::FormatFixedSafeString<128> path("Physics/Cloth/%s", name.cstr());
    mClothRes = loadFromRomOrActorPack<ClothResource>(mClothResHandle, path, pack_handle, mName, true);
    if (!mClothRes)
        return false;
    if (mClothRes->sub_710121CEA0() != 1)
        return false;

    mClothRes->getPath().copy(path);
    mFlags.reset(Flag::Cloth1);
    mFlags.reset(Flag::Cloth2);
    mFlags.set(Flag::Cloth1);
    return true;
}

bool InstanceSet::sub_7100FBF87C(sead::Heap* heap, Unk_7102519a10* arg, res::Handle* pack_handle) {
    if (_e8) {
        delete _e8;
        _e8 = nullptr;
    }
    if (mSupportBoneResHandle) {
        delete mSupportBoneResHandle;
        mSupportBoneResHandle = nullptr;
    }

    auto* support_bone = mParamSet->support_bone;
    if (!arg && !support_bone)
        return false;

    const sead::SafeString& name =
        arg ? arg->getSupportBoneFileName() : support_bone->support_bone_setup_file_path.ref();
    if (name.isEmpty()) {
        if (_e8) {
            delete _e8;
            _e8 = nullptr;
        }
        if (mSupportBoneResHandle) {
            delete mSupportBoneResHandle;
            mSupportBoneResHandle = nullptr;
        }
        return false;
    }

    mSupportBoneResHandle = new (heap) res::Handle;
    sead::FormatFixedSafeString<128> path("Physics/SupportBone/%s", name.cstr());
    if (loadFromRomOrActorPack<SupportBoneResource>(mSupportBoneResHandle, path, pack_handle, mName,
                                                    true))
        return true;

    if (_e8) {
        delete _e8;
        _e8 = nullptr;
    }
    if (mSupportBoneResHandle) {
        delete mSupportBoneResHandle;
        mSupportBoneResHandle = nullptr;
    }
    return false;
}

void InstanceSet::sub_7100FB8F10(sead::Heap* heap, res::Handle* pack_handle) {
    if (mRagdollInstance)
        deleteRagdoll_();
    if (_f0 && mFlags.isOn(Flag::_40)) {
        delete _f0;
        _f0 = nullptr;
        mFlags.reset(Flag::_40);
    }
    if (!sub_7100FBE808(heap, pack_handle))
        deleteRagdoll_();
}

// NON_MATCHING: scheduling only: the original loads the param's `num` field before it builds the name / type
// temporaries and interleaves the temporaries' stores differently
// (discarded call in the original: `mName.cstr()` after initLayerMasks)
bool InstanceSet::initContactInfo(sead::Heap* heap) {
    auto* param = mParamSet->contact_info;
    if (!param)
        return false;

    auto* contact_mgr = System::instance()->getContactMgr();
    const s32 num_contact_point_info = param->contact_point_info_num.ref();
    if (num_contact_point_info > 0) {
        mContactPointInfo.allocBuffer(num_contact_point_info, heap);
        for (s32 i = 0; i < num_contact_point_info; ++i) {
            auto& info_param = param->contact_point_info[i];
            const sead::SafeString name = info_param.name.ref();
            const sead::SafeString type = info_param.type.ref();
            auto* info = ContactPointInfo::make(heap, info_param.num.ref(), name, 0, 0, 0);
            contact_mgr->initLayerMasks(info, type);
            mName.cstr();
            mContactPointInfo.pushBack(info);
        }
    }

    const s32 num_collision_info = param->collision_info_num.ref();
    if (num_collision_info > 0) {
        mCollisionInfo.allocBuffer(num_collision_info, heap);
        for (s32 i = 0; i < num_collision_info; ++i) {
            auto& info_param = param->collision_info[i];
            const sead::SafeString name = info_param.name.ref();
            const sead::SafeString type = info_param.type.ref();
            auto* info = CollisionInfo::make(heap, name);
            contact_mgr->initLayerMasks(info, type);
            mName.cstr();
            mCollisionInfo.pushBack(info);
        }
    }
    return true;
}

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

void InstanceSet::sub_7100FB9F30(bool clear) {
    if (mCharacterController)
        mCharacterController->sub_7100F60850(clear);

    for (auto& rb : mRigidBodySets)
        rb.clearFlag400000(clear);

    for (auto* body : mList)
        body->clearFlag400000(clear);

    if (mRagdollInstance)
        mRagdollInstance->clearFlag400000(clear);
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

NavMeshObjMaybe* InstanceSet::sub_7100FC00EC(s32 idx) {
    if (idx < 0 || idx >= _100.size())
        return nullptr;
    return &_100[idx];
}

sead::Buffer<NavMeshObjMaybe>* InstanceSet::sub_7100FC0124() {
    return &_100;
}

}  // namespace ksys::phys

namespace ksys::phys {

void InstanceSet::sub_7100FBBEC0() {}

void InstanceSet::sub_7100FBDA08(const sead::Vector3f& translation) {
    if (_f0)
        _f0->mTranslate = translation;
}

void InstanceSet::sub_7100FC012C(HavokAI* havok_ai) {
    if (!havok_ai)
        havok_ai = HavokAI::instance();
    for (int i = 0; i < _100.size(); ++i) {
        if (!_100[i]._98)
            havok_ai->sub_7100F8305C(&_100[i]);
    }
}

void InstanceSet::sub_7100FC0288(RigidBody* body) {
    if (!body || body->isSensor())
        return;
    for (int i = 0; i < _100.size(); ++i)
        _100[i].sub_7100F7F430(body->getHkBody());
}

void InstanceSet::sub_7100FC01B0() {
    for (int i = 0; i < _100.size(); ++i) {
        auto& obj = _100[i];
        // The request pointer carries low-bit tags, also tested by HavokAI's queue operations.
        auto* pending = reinterpret_cast<HavokAI*>(uintptr_t(obj._a0.load()) & ~uintptr_t(3));
        if (pending)
            pending->sub_7100F833A8(&obj);
        if (obj._98)
            obj._98->sub_7100F833A8(&obj);
    }
}

// NON_MATCHING: support-bone pointer load order and branch/register allocation.
void InstanceSet::sub_7100FBA508() {
    const bool ragdoll_active = mRagdollInstance &&
        mRagdollInstance->getWorldState() == RagdollInstance::WorldState::AddedToWorld;
    if ((_e8 || ragdoll_active) && _f0) {
        _f0->copyModelPoseToHavok(ragdoll_active ? ModelBoneAccessor::EnableScale::No :
                                                ModelBoneAccessor::EnableScale::Yes);
    }
}

}  // namespace ksys::phys
