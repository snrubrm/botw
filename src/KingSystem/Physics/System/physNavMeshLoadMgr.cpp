#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/System/physHavokAI.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Physics/Ragdoll/physUnk_7102519b90.h"

namespace ksys::phys {

void NavMeshObj2Maybe::sub_7100F8B518(HavokAI* fallback) {
    if (_70)
        _70->sub_7100F8363C(this);
    else
        fallback->sub_7100F83580(this);
}

void NavMeshObj2Maybe::sub_7100F8B538() {
    // The pending pointer carries two request tag bits in F8B538 and the queue consumers.
    auto* pending = reinterpret_cast<HavokAI*>(reinterpret_cast<uintptr_t>(_78.load()) & ~uintptr_t(3));
    if (pending)
        pending->sub_7100F83790(this, false);
    if (_70)
        _70->sub_7100F83790(this, false);
    // The original also performs this discarded atomic load after removing both owners.
    _78.load();
}

void NavMeshObj2Maybe::sub_7100F8B584(hkaiStreamingCollection* collection) {
    mPairs.clear();
    sub_7100F8B59C(nullptr, collection, -1);
}

// NON_MATCHING: register allocation (entry index and count swap registers)
void NavMeshLoadMgr::sub_7100F8AA78(s32 index, const sead::Matrix34f& transform) {
    if (_190)
        return;
    auto lock = sead::makeScopedLock(_130);
    if (!_10 || (_178.x | _178.y) != 0)
        return;
    auto* resource = sead::DynamicCast<Unk_7102519b90>(_10->getResource());
    if (index < 0 || !resource)
        return;
    auto& entries = resource->getEntries();
    const s32 i = index + 1;
    if (entries.size() <= i || !entries.getBufferPtr()[i]._8)
        return;
    entries.get(i)->sub_71012A7324(transform);
}

// NON_MATCHING: boolean return materialization, tile-size loads and saved registers differ.
bool NavMeshLoadMgr::x_0(const sead::Vector3f* pos) {
    if (_190)
        return false;
    auto lock = sead::makeScopedLock(_130);
    if (!_10)
        return false;
    if (_178.x == 0 && _178.y == 0)
        return true;
    const s32 x = sead::Mathi::clamp((s32(pos->x) - _170.x) / _178.x, 0, _180.x - 1);
    if (sead::Mathi::abs(x - _188.x) > 1)
        return false;
    const s32 z = sead::Mathi::clamp((s32(pos->z) - _170.y) / _178.y, 0, _180.y - 1);
    return sead::Mathi::abs(z - _188.y) < 2;
}

// NON_MATCHING: register allocation / instruction scheduling only (the original ors the tile sizes in the other operand order
// and clamps the z tile before converting the z position)
// NON_MATCHING: register allocation / instruction scheduling only (same as x_1)
void NavMeshLoadMgr::sub_7100F8B334(const sead::Vector3f* pos) {
    if (_190)
        return;

    auto lock = sead::makeScopedLock(_130);
    if (!_10)
        return;
    if ((_180.x | _180.y) == 0)
        return;

    const s32 x = sead::Mathi::clamp((s32(pos->x) - _170.x) / _178.x, 0, _180.x - 1);
    const s32 z = sead::Mathi::clamp((s32(pos->z) - _170.y) / _178.y, 0, _180.y - 1);
    TileHandle* handle = _8 > 9 ? &_10[9] : nullptr;
    if (handle->requestedLoad()) {
        if (x != handle->_50 || z != handle->_54)
            return;
    }
    handle->_50 = x;
    handle->_54 = z;
    a(handle);
}

bool NavMeshLoadMgr::x_1(const sead::Vector3f* pos) {
    if (_190)
        return false;

    auto lock = sead::makeScopedLock(_130);
    if (!_10)
        return false;
    if (_178.x == 0 && _178.y == 0)
        return false;

    const s32 x = sead::Mathi::clamp((s32(pos->x) - _170.x) / _178.x, 0, _180.x - 1);
    const s32 z = sead::Mathi::clamp((s32(pos->z) - _170.y) / _178.y, 0, _180.y - 1);
    const s32 dx = sead::Mathi::abs(x - _188.x);
    const s32 dz = sead::Mathi::abs(z - _188.y);
    if (dx < 2 && dz < 2)
        return false;
    if (dx == 2 && dz == 2)
        return false;
    return dx < 3 && dz < 3;
}

// NON_MATCHING: coordinate conversion scheduling and saved values differ.
bool NavMeshLoadMgr::sub_7100F8ADC4(const sead::Vector3f* pos) {
    if (_190 || !_10)
        return false;
    if ((_178.x | _178.y) != 0) {
        const s32 x = sead::Mathi::clamp((s32(pos->x) - _170.x) / _178.x, 0, _180.x - 1);
        const s32 z = sead::Mathi::clamp((s32(pos->z) - _170.y) / _178.y, 0, _180.y - 1);
        auto lock = sead::makeScopedLock(_130);
        u32 count = _8;
        for (auto* handle = _10; count != 0; --count, ++handle) {
            if (handle->requestedLoad() && handle->_50 == x && handle->_54 == z)
                return handle->sub_7100F8AF0C();
        }
        return false;
    }
    auto lock = sead::makeScopedLock(_130);
    TileHandle* handle = _8 ? &_10[0] : nullptr;
    return handle->sub_7100F8AF0C();
}

bool NavMeshLoadMgr::TileHandle::sub_7100F8AF0C() {
    if (!requestedLoad() || _58 != 1)
        return false;

    const auto* entries =
        sead::DynamicCast<Unk_7102519b90>(getResource())->getEntries().getBufferPtr();
    const s32 count = sead::DynamicCast<Unk_7102519b90>(getResource())->getEntries().size();
    for (s32 i = 0; i != count; ++i) {
        if (entries[i]._8 && !(entries[i]._60.load() & 0x400))
            return false;
    }
    return true;
}

void NavMeshLoadMgr::x_2() {
    if (_190)
        return;

    auto lock = sead::makeScopedLock(_130);
    if (!_10)
        return;
    if ((_180.x | _180.y) == 0)
        return;

    TileHandle* handle = _8 > 9 ? &_10[9] : nullptr;
    if (handle->requestedLoad())
        x_3(handle, handle);
}

}  // namespace ksys::phys

// NON_MATCHING: placeholder destructor; the original (0x7100f8bba8) also destroys members or bases
// this class does not declare yet.
Unk_71024f7180::~Unk_71024f7180() = default;

// Placeholder: a load record with a state word at 0x48.
struct Unk_7100F894D0Maybe {
    u8 _0[0x48];
    s32 _48;
};

s32 sub_7100F894D0(const Unk_7100F894D0Maybe* obj) {
    return obj->_48;
}

void sub_7100F894D8(Unk_7100F894D0Maybe* obj) {
    obj->_48 = 0;
}

bool sub_7100F89504(const Unk_7100F894D0Maybe* obj) {
    return obj->_48 > 7;
}
