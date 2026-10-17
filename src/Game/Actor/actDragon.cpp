#include "Game/Actor/actDragon.h"
#include <math/seadQuat.h>
#include <gsys/gsysModelUnit.h>
#include <gsys/gsysModel.h>
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/gameDragonChallengeMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include <basis/seadNew.h>
#include <math/seadVector.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::act {

namespace {
// File-static names set up by the TU's static initializer (0x7100012a28).
sead::SafeString sBodyName = "Body";
sead::SafeString sTgtName = "Tgt";
sead::SafeString sAtkName = "Atk";
}  // namespace

f32 Dragon::x_0() const {
    return _1e1c.length();
}

void Dragon::m63() {
    Enemy::m63();
    sub_710000D474();
    sub_710000D51C();
}

void Dragon::sub_710000D51C() {
    if (!_1f70.isOn(1 << 28))
        _1ec0.sub_71010F17FC(false);
}

// NON_MATCHING: the two calls are laid out in the other order (the original falls through to sub_710000ECA4)
void Dragon::updatePositionMaybe() {
    Enemy::updatePositionMaybe();
    const sead::Vector3f pos = getMtx().getTranslation();
    const sead::Vector3f center = _1f54;
    const f32 dx = pos.x - center.x;
    const f32 dz = pos.z - center.z;
    if (m139() < 1.0f || dx * dx + dz * dz > 350.0f * 350.0f)
        sub_710000D474();
    else
        sub_710000ECA4();
    _1f70.set(0x40000000);
}

void Dragon::afterModelMatrixUpdate() {
    if (_1e0c != 0)
        return;
    if (!ksys::gdt::getFlag_BalladOfHeroRito_DragonEffect())
        return;
    auto* mgr = DragonChallengeMgr::instance();
    if (!mgr)
        return;
    if ((mgr->_12c == 2) != _1f70.isOn(0x10000000))
        return;
    sead::Matrix34f mtx;
    if (sub_71011D57F8(&mtx, "Head"))
        DragonChallengeMgr::instance()->sub_71006F9E20(mtx);
}

bool Dragon::sub_710000FF60(int idx) {
    return !_1f70.isOn(0x10 << idx) && _1f70.isOn(1 << idx);
}

bool Dragon::sub_710000F70C(int idx) {
    return _1f70.isOn(0x10 << idx);
}

// NON_MATCHING: we merge the two adjacent -1.0f stores into one 64-bit store and schedule the copies' loads differently.
// NON_MATCHING: the original addresses the three names from one base of the TU's merged statics.
void Dragon::sub_710000D474() {
    if (!_1f70.isOnBit(22))
        return;
    _1f70.resetBit(22);
    if (auto* body = getRigidBodyByName(sBodyName.cstr()))
        body->removeFromWorld();
    if (auto* body = getRigidBodyByName(sTgtName.cstr()))
        body->removeFromWorld();
    if (auto* body = getRigidBodyByName(sAtkName.cstr()))
        body->removeFromWorld();
}

ksys::map::Object* Dragon::sub_710000C440() const {
    if (_1f70.isOnBit(28))
        return getMapObject();
    auto* mgr = ksys::map::PlacementMgr::instance();
    if (!mgr)
        return nullptr;
    auto* actors = mgr->mPlacementActors;
    if (!actors)
        return nullptr;
    switch (_1e0c) {
    case 0:
        return actors->mDragonObjects[0];
    case 1:
        return actors->mDragonObjects[1];
    case 2:
        return actors->mDragonObjects[2];
    case 3:
        return getMapObject();
    default:
        return nullptr;
    }
}

bool Dragon::shouldUnload(s32* a1) {
    if (!_1f70.isOnBit(28)) {
        const f32 dist_sq = _1f6c * _1f6c;
        if (dist_sq < mDeleteDistanceSq)
            return false;
        if (_1f70.isOnBit(29)) {
            if (auto* obj = sub_710000C440()) {
                if (obj->sub_7100D4C868()) {
                    const f32 lod_dist = obj->sub_7100D4C868()->getTraverseDistForLOD();
                    if (dist_sq > lod_dist * lod_dist)
                        deleteLater(DeleteReason::_0);
                }
            }
            return false;
        }
    }
    if (_1e0c == 2) {
        const auto& pos = getMtx().getTranslation();
        const f32 dx = pos.x + 47.9083f;
        const f32 dz = pos.z - 2505.9648f;
        if (dx * dx + dz * dz < 1000000.0f && _1f6c * _1f6c < mDeleteDistanceSq)
            return false;
    }
    return shouldUnloadBecauseOfDistance(a1);
}

// NON_MATCHING: the bone matrix lives at a different stack offset (regalloc / stack layout).
void Unk_7102357168::m0() {
    for (s32 i = 0; i < numParts; ++i)
        parts[i].handle._68 = sead::Matrix34f::ident;
    _a4 = 0;
    if (!actor)
        return;

    sead::Matrix34f mtx;
    const auto& key = _10[0].getKey();
    actor->getModel()->getUnits()(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
        &mtx, key.bone_index);
    sead::Vector3f x_axis = mtx.getBase(0);
    sead::Vector3f y_axis = mtx.getBase(1);
    sead::Vector3f z_axis = mtx.getBase(2);
    x_axis.normalize();
    y_axis.normalize();
    z_axis.normalize();
    _44 = sead::Vector3f::zero;
    _38 = mtx.getTranslation() + x_axis * 4.0f;
    _5c = sead::Vector3f::zero;
}

// TODO: not decompiled yet (W, 3360 B). Defined so that the vtable (keyed on m0) links.
void Unk_7102357168::m1() {}

// NON_MATCHING: the second bone key / model loads are scheduled differently.
void Unk_7102357188::m0() {
    for (s32 i = 0; i < numParts; ++i)
        parts[i].handle._68 = sead::Matrix34f::ident;

    sead::Matrix34f mtx0;
    sead::Matrix34f mtx1;
    sead::Vector3f scale;
    auto* model = actor->getModel();
    const auto& key0 = _10[0].getKey();
    model->getUnits()(key0.model_unit_index)->mModelUnit->getBoneLocalMatrix(&mtx0, &scale,
                                                                              key0.bone_index);
    const auto& key1 = _10[1].getKey();
    actor->getModel()->getUnits()(key1.model_unit_index)->mModelUnit->getBoneLocalMatrix(
        &mtx1, &scale, key1.bone_index);
    parts[0]._e4 = mtx0;
    parts[1]._e4 = mtx1;
}

// TODO: not decompiled yet (W, 1412 B). Defined so that the vtable (keyed on m0) links.
void Unk_7102357188::m1() {}

bool Dragon::startPreparingForPreDelete_() {
    if (!_1f70.isOn(0x4000000)) {
        if (_14c8._930 & 8)
            _14c8.sub_71006FB8A8();
        for (auto& group : _1fd0)
            group.detachParts();
        _2270.detachParts();
        if (!_1f70.isOn(0x10000000))
            _1ec0.sub_71010F17FC(true);
        _1f70.set(0x4000000);
    }
    return Enemy::startPreparingForPreDelete_();
}

ksys::act::BaseProc::PreDeletePrepareResult Dragon::prepareForPreDelete_() {
    auto* mgr = ksys::map::PlacementMgr::instance();
    if (mgr && mgr->mPlacementActors) {
        ksys::map::Object* obj;
        bool has_obj = true;
        if (_1f70.isOnBit(28)) {
            obj = getMapObject();
        } else {
            switch (_1e0c) {
            case 0:
                obj = mgr->mPlacementActors->mDragonObjects[0];
                break;
            case 1:
                obj = mgr->mPlacementActors->mDragonObjects[1];
                break;
            case 2:
                obj = mgr->mPlacementActors->mDragonObjects[2];
                break;
            case 3:
                obj = getMapObject();
                break;
            default:
                has_obj = false;
                break;
            }
        }
        if (has_obj && obj) {
            if (_1f70.isOnBit(28)) {
                sead::Vector3f pos;
                if (_1e0c == 3) {
                    getHomePos(&pos);
                } else {
                    const auto translate = obj->getTranslate();
                    pos.set(translate.x, -500.0f, translate.z);
                }
                obj->setTranslate(pos);
                if (auto* lod = obj->findPlacementLODLinkObject_0(nullptr))
                    lod->setTranslate(pos);
            } else if (_1f70.isOnBit(29)) {
                if (auto* lod = obj->sub_7100D4C890()) {
                    if (auto* actor = lod->tryGetActor(false))
                        actor->deleteLater(DeleteReason::_0);
                }
            }
        }
    }
    return Actor::prepareForPreDelete_();
}

// Placeholder name: switches the horn animation (AS slot 5) to `name` when it changes, then sub_710000D474.
void Dragon::sub_710000EA88(const sead::SafeString& name) {
    if (name.isEmpty())
        return;
    if (_1f18 == name)
        return;
    _1f18.copy(name);
    mASList->startAnimationMaybe(-1.0f, -1.0f, _1f18, 5, 0, true);
    sub_710000D474();
}

// Placeholder name: plays the "Appear" animation in AS slot 5, bank 2.
void Dragon::sub_710000EC50() {
    mASList->startAnimationMaybe(-1.0f, -1.0f, "Appear", 5, 2, true);
}

void Dragon::Unk_710000b710::sub_71006FB3FC(const sead::Matrix34f& matrix) {
    _20 = matrix;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (sead::Mathf::isNan(_20.m[i][j])) {
                _20.makeIdentity();
                return;
            }
        }
    }
}

void Dragon::Unk_710000b710::sub_71006FB7F8() {
    if (!(_930 & 4))
        return;
    if (_930 & 8)
        sub_71006FB8A8();
    _850.freeBuffer();
    _8.freeBuffer();
    _930 &= ~4;
}

void Dragon::Unk_710000b710::sub_71006FB8A8() {
    if ((_930 & 0xc) != 0xc)
        return;
    mActor->sub_71011DA868(&_5d0.handle);
    mActor->sub_71011DA868(&_338.handle);
    mActor->sub_71011DA868(&_b8.handle);
    for (s32 i = 0, n = _850.size(); i < n; ++i) {
        auto& part = _850[i];
        if (part._170.isValid() && !part._170.getName().isEmpty())
            mActor->sub_71011DA868(&part.handle);
    }
    _930 &= ~8;
}

// NON_MATCHING: the bit 3 test uses the flags before bit 0 was cleared (register choice only).
void Dragon::Unk_710000b710::sub_71006FBAD4() {
    _930 &= ~1;
    _860.setTranslation(sead::Vector3f::zero);
    if (!(_930 & 0x800)) {
        if (_930 & 8)
            sub_71006FB8A8();
        sub_71006FABC8();
    }
    if (!(_930 & 0x20))
        sub_71006FB51C();
    if (!(_930 & 0x10))
        _8.clear();
    if (!(_930 & 0x80))
        sub_71006FBB64();
}

void Dragon::Unk_710000b710::sub_71006FD830(f32 start_frame, f32 end_frame) {
    if (start_frame < 0.0f) {
        if (_930 & 0x100) {
            _8a4 = -1.0f;
            _8a8 = -1.0f;
            _8ac = 0.0f;
            _930 &= ~0x100;
        }
        return;
    }
    _8ac = 1.0f;
    _5c0 = _338.handle._9c.m[2][3];
    _5bc = _338.handle._9c.m[1][3];
    _5cc = _84.m[2][3];
    _5c4 = _84.m[0][3];
    _5b8 = _338.handle._9c.m[0][3];
    _5c8 = _84.m[1][3];
    _8a4 = start_frame;
    _8a8 = end_frame;
    _930 |= 0x100;
}

ksys::act::BaseProc* Dragon::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Dragon(arg);
}

const sead::Matrix34f& Dragon::sub_710001014C() const {
    return *_14c8.sub_71006FC514();
}

inline float sqXYZDistance(const sead::Vector3f& a, const sead::Vector3f& b) {
    sead::Vector3f diff = a;
    diff -= b;
    return diff.squaredLength();
}

// Name from the CSV (dragon::isWithin1kmOfHyruleCastle). Despite the name, false when the player is in the open
// world within 1000 (XZ) of Hyrule Castle (-244.9891, -945.029); true otherwise.
bool isWithin1kmOfHyruleCastle() {
    auto* world = ksys::world::Manager::instance();
    if (world && world->getStageType() == ksys::StageType::OpenWorld) {
        const auto& pos = getPlayerPosition();
        const f32 dx = -244.9891f - pos.x;
        const f32 dz = -945.029f - pos.z;
        if (dx * dx + dz * dz < 1000000.0f)
            return false;
    }
    return true;
}

// NON_MATCHING: Swapped arguments in fadd for distance calcuation
bool getDragonItemDropPosition(sead::Vector3f* target_pos, const sead::Vector3f& current_pos) {
    auto* mgr = ksys::map::PlacementMgr::instance();
    const auto& results = mgr->mTraverseResults[1 - mgr->mTraverseResultIdx];

    sead::SafeArray<sead::Vector3f, 3> pos;
    pos.fill(sead::Vector3f::zero);

    bool ok = false;
    for (const auto& obj : results.dragon_item_drop_targets) {
        const sead::Vector3f& obj_pos = obj.getTranslate();
        if (!(obj_pos.y < current_pos.y)) {
            continue;
        }

        // Looks like an Insertion Sort
        for (int i = 0; i < pos.size(); i++) {
            bool closer = sqXYZDistance(obj_pos, current_pos) < sqXYZDistance(pos[i], current_pos);
            if (closer || pos[i] == sead::Vector3f(0, 0, 0)) {
                if (i > 0) {
                    pos[i - 1] = pos[i];
                }
                pos[i] = obj_pos;
                ok = true;
            }
        }
    }
    if (!ok) {
        return false;
    }
    int index = sead::GlobalRandom::instance()->getS32Range(0, 3);
    target_pos->e = pos[index].e;
    return true;
}

}  // namespace uking::act

namespace uking::act {

Dragon::~Dragon() = default;

void Dragon::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    Enemy::m76(setter);
}

void Dragon::m115() {}

bool Dragon::sub_710000FDFC() const {
    return _1f70.isOn(0xf0);
}

// NON_MATCHING: the final boolean branch is folded into a normalized return instead of sharing the earlier true return.
bool Dragon::sub_710000FE10() {
    if (getGameDataFlagGrudgeAlive(0) || getGameDataFlagGrudgeAlive(1) ||
        getGameDataFlagGrudgeAlive(2) || getGameDataFlagGrudgeAlive(3))
        return true;
    return false;
}

bool Dragon::getGameDataFlagGrudgeAlive(int idx) {
    if (_1e0c != 3)
        return false;
    return getGameDataFlag("GrudgeAlive", idx);
}

void Dragon::m110(f32* a1, s32* a2) {
    // tag hash 0xa4c7ba34 (no name known)
    if (ksys::act::hasTag(this, 0xA4C7BA34u)) {
        *a1 = 0.4f;
        *a2 = 0;
    } else {
        Actor::m110(a1, a2);
    }
}

void Dragon::m111(f32* a1, s32* a2) {
    // tag hash 0xa4c7ba34 (no name known)
    if (ksys::act::hasTag(this, 0xA4C7BA34u)) {
        *a1 = 0.4f;
        *a2 = 2;
    } else {
        Actor::m111(a1, a2);
    }
}

void Dragon::m112(f32* a1, s32* a2) {
    // tag hash 0xa4c7ba34 (no name known)
    if (ksys::act::hasTag(this, 0xA4C7BA34u)) {
        *a1 = 0.4f;
        *a2 = 0;
    } else {
        Actor::m112(a1, a2);
    }
}

void Dragon::m113(f32* a1, s32* a2) {
    // tag hash 0xa4c7ba34 (no name known)
    if (ksys::act::hasTag(this, 0xA4C7BA34u)) {
        *a1 = 0.4f;
        *a2 = 2;
    } else {
        Actor::m113(a1, a2);
    }
}

}  // namespace uking::act

namespace uking::act {
// Placeholder name: with _1f70 bit 19, reopens eye `idx` (clears its closed bit and plays GrudgeEye_Open in AS slot
// idx + 1) unless it is already open or blocked (bit 11 + idx).
void Dragon::sub_710000F36C(s32 idx) {
    if (!_1f70.isOnBit(19) || !_1f70.isOn(0x8000u << idx) || _1f70.isOn(0x800u << idx))
        return;
    _1f70.reset(0x8000u << idx);
    switch (idx) {
    case 0:
        if (mASList->x_1(1, 0).findIndex("GrudgeEye_Open") != -1)
            return;
        mASList->startAnimationMaybe(-1.0f, -1.0f, "GrudgeEye_Open", 1, 0, true);
        break;
    case 1:
        if (mASList->x_1(2, 0).findIndex("GrudgeEye_Open") != -1)
            return;
        mASList->startAnimationMaybe(-1.0f, -1.0f, "GrudgeEye_Open", 2, 0, true);
        break;
    case 2:
        if (mASList->x_1(3, 0).findIndex("GrudgeEye_Open") != -1)
            return;
        mASList->startAnimationMaybe(-1.0f, -1.0f, "GrudgeEye_Open", 3, 0, true);
        break;
    case 3:
        if (mASList->x_1(4, 0).findIndex("GrudgeEye_Open") != -1)
            return;
        mASList->startAnimationMaybe(-1.0f, -1.0f, "GrudgeEye_Open", 4, 0, true);
        break;
    }
}

void Dragon::sub_710000F52C(s32 idx) {
    if (_1f70.isOn(0x8000u << idx) || _1f70.isOn(0x800u << idx))
        return;
    _1f70.set(0x8000u << idx);
    switch (idx) {
    case 0:
        mASList->startAnimationMaybe(-1.0f, -1.0f, "GrudgeEye_Close", 1, 0, true);
        break;
    case 1:
        mASList->startAnimationMaybe(-1.0f, -1.0f, "GrudgeEye_Close", 2, 0, true);
        break;
    case 2:
        mASList->startAnimationMaybe(-1.0f, -1.0f, "GrudgeEye_Close", 3, 0, true);
        break;
    case 3:
        mASList->startAnimationMaybe(-1.0f, -1.0f, "GrudgeEye_Close", 4, 0, true);
        break;
    }
}

void Dragon::sub_710000F654(s32 idx) {
    const u32 bit = 0x10u << idx;
    if (_1e0c != 3 || _1f70.isOn(bit))
        return;
    if (!getGameDataFlag("GrudgeAlive", idx))
        return;
    _1e0c = 3;
    _1f70.set(bit);
    _1f70.reset(0x8800u << idx);
    sub_710000F52C(idx);
    _1f70.set(0x100000u);
}

// NON_MATCHING: compiler merges the common animation-call tail and flag update; scheduling differs.
void Dragon::sub_710000FC70(s32 idx, bool start, bool secondary) {
    if (!_1f70.isOn(0x10u << idx) || _1f70.isOn(0x800u << idx))
        return;
    if (start) {
        _1f70.set(0x8000000u);
        _1f4c = 60.0f;
        _1f50 = 0.0f;
        mASList->startAnimationMaybe(-1.0f, -1.0f, "Damage_Grudge_Body", 0, 0, true);
        _1f70.set(0x400u);
        mASList->startAnimationMaybe(-1.0f, -1.0f, "Damage_Grudge", idx + 1, 0, true);
    } else {
        _1f70.set(0x200u);
        mASList->startAnimationMaybe(-1.0f, -1.0f, "Damage_Grudge_Skip", idx + 1, 0, true);
        if (secondary)
            mASList->startAnimationMaybe(-1.0f, -1.0f, "Damage_Grudge", idx + 1, 0, true);
    }
    _1f70.set(0x800u << idx);
}
}  // namespace uking::act

namespace uking::act {
// NON_MATCHING: matrix temporaries use different register and stack placement.
void Dragon::x(const sead::Matrix34f& mtx) {
    auto* controller = getCharacterController();
    if (!controller)
        return;
    sead::Matrix34f matrix = mtx;
    auto x_axis = matrix.getBase(0);
    auto y_axis = matrix.getBase(1);
    auto z_axis = matrix.getBase(2);
    x_axis.normalize();
    y_axis.normalize();
    z_axis.normalize();
    matrix.setBase(0, x_axis);
    matrix.setBase(1, y_axis);
    matrix.setBase(2, z_axis);
    _14c8.sub_71006FB3FC(matrix);
    controller->sub_7100F5FBE0(matrix.getTranslation());
}
// NON_MATCHING: same flow; the quaternion-to-matrix products and the translation lerps are scheduled differently.
// Reads the bone's local matrix and scale, then (while the blend timer _16c runs from 0 to 1 at rate 1 / _168)
// blends _20 from _108 to _138 with a smoothstep: translation lerp and a partial rotation about the relative axis.
void Unk_7102450330::m2(gsys::Model* model) {
    const auto& key = _60.getKey();
    if (!key.isValid())
        return;
    model->getUnits()(key.model_unit_index)->mModelUnit->getBoneLocalMatrix(&_9c, &_cc, key.bone_index);

    if (_16c < 1.0f) {
        ksys::Timer::update(&_16c, 1.0f / _168);
        const f32 t = _16c;
        const f32 rate = t * t * (3.0f - 2.0f * t);

        sead::Vector3f pos;
        pos.x = _108.m[0][3] + rate * (_138.m[0][3] - _108.m[0][3]);
        pos.y = _108.m[1][3] + rate * (_138.m[1][3] - _108.m[1][3]);
        pos.z = _108.m[2][3] + rate * (_138.m[2][3] - _108.m[2][3]);

        sead::Vector3f axis;
        f32 angle;
        ksys::util::sub_71011EF51C(&axis, &angle, _108, _138, sead::Vector3f::ey);
        sead::Quatf quat;
        quat.setAxisRadian(axis, rate * angle);
        sead::Matrix34f rotation;
        rotation.fromQuat(quat);
        sead::Matrix34f mtx;
        mtx.setMul(rotation, _108);
        mtx.setTranslation(pos);

        const f32 rest = sead::Mathf::max(1.0f - _16c, 0.0f);
        pos.x += rest * (_138.m[0][3] - pos.x);
        pos.y += rest * (_138.m[1][3] - pos.y);
        pos.z += rest * (_138.m[2][3] - pos.z);
        ksys::util::sub_71011EF51C(&axis, &angle, mtx, _138, sead::Vector3f::ey);
        quat.setAxisRadian(axis, rest * angle);
        rotation.fromQuat(quat);
        mtx.setMul(rotation, mtx);
        mtx.setTranslation(pos);
        _20 = mtx;
    }
    Unk_71024512e8::m2(model);
}

void Dragon::preDelete2_(const PreDeleteArg& arg) {
    Enemy::preDelete2_(arg);
    _14c8.sub_71006FB7F8();
    for (auto& group : _1fd0)
        group.destroy();
    _2270.destroy();
}

// NON_MATCHING: the original's element type has no destructible member at +0xa8, so its array
// teardown does not call ~BoneAccessKeyEx for the part's key; our Unk_71007237d0Part does (the
// Sandworm's parts use that key). Everything else matches.
void DragonBonePartGroup::destroy() {
    detachParts();
    if (_10.getBufferPtr()) {
        delete[] _10.getBufferPtr();
        _10 = sead::Buffer<gsys::BoneAccessKeyEx>();
    }
    if (parts.getBufferPtr()) {
        delete[] parts.getBufferPtr();
        parts = sead::Buffer<Unk_71007237d0Part>();
    }
}

}  // namespace uking::act
