#include "Game/Actor/actDragon.h"
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

namespace uking::act {

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
    _5c0 = _400;
    _5bc = _3f0;
    _5cc = _b0;
    _5c4 = _90;
    _5b8 = _3e0;
    _5c8 = _a0;
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

// NON_MATCHING: member types incomplete
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
}  // namespace uking::act
