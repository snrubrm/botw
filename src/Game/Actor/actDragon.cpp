#include "Game/Actor/actDragon.h"
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
