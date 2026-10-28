#include <devenv/seadStackTrace.h>
#include <new>
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/AOC/aocManager.h"
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
// NON_MATCHING: only the parameter registers x22 / x23 (area / size) are swapped; the body and
// constants agree.
void NavMeshLoadMgr::createResources(sead::Heap* heap, const sead::SafeString& path,
                                     const sead::Vector2i& area, const sead::Vector2i& origin,
                                     const sead::Vector2i& size) {
    auto lock = sead::makeScopedLock(_130);
    if (_10)
        return;

    _18 = path;
    _170 = origin;
    _178 = size;
    _180 = sead::Vector2i(area.x / size.x, area.y / size.y);
    _188 = sead::Vector2i(-1, -1);

    auto* handles = new (heap, 8, std::nothrow) TileHandle[10];
    if (handles) {
        _8 = 10;
        _10 = handles;
    }
}

void NavMeshLoadMgr::load(sead::Heap* heap, const sead::SafeString& path) {
    auto lock = sead::makeScopedLock(_130);
    if (_10)
        return;

    _18 = path;
    _170 = sead::Vector2i(0, 0);
    _178 = sead::Vector2i(0, 0);
    _180 = sead::Vector2i(0, 0);
    _188 = sead::Vector2i(0, 0);

    auto* handle = new (heap, 8, std::nothrow) TileHandle[1];
    if (handle) {
        _8 = 1;
        _10 = handle;
    }

    res::LoadRequest request(0x10, 0, false);
    request.mRequester = "NavMeshLoadMgr";
    request._22 = true;

    if (aoc::Manager::instance() != nullptr)
        request.mAocFileDevice = aoc::Manager::instance()->getFileDeviceForNavMesh(_18);

    (_8 ? _10 : nullptr)->mHandle.load(_18, &request, nullptr);
}

// NON_MATCHING: one load pair only: the original reads the tile's two indices with two `ldr`
// instructions, ours merges them into one `ldp` (692 vs 696 bytes); every other instruction agrees.
void NavMeshLoadMgr::a(TileHandle* handle) {
    if (handle->mHandle.requestedLoad()) {
        if (handle->mHandle.isReadyOrNeedsParse())
            handle->mHandle.parseResource(nullptr);
    } else {
        res::LoadRequest request(0x10, 0, false);
        request.mRequester = "NavMeshLoadMgr";
        request._22 = true;

        sead::SafeString path = _18;
        sead::FixedSafeString<256> tile_path;
        if ((_178.x | _178.y) != 0) {
            const s32 x = handle->_50;
            const s32 z = handle->_54;
            tile_path.format("%s/%d-%d.hknm2", _18.cstr(), x, z);
            path = tile_path;
        }

        if (aoc::Manager::instance() != nullptr)
            request.mAocFileDevice = aoc::Manager::instance()->getFileDeviceForNavMesh(path);

        handle->mHandle.requestLoad(path, &request, nullptr);
    }

    if (handle->mHandle.isSuccess() && handle->_58 != 1) {
        auto* entries =
            sead::DynamicCast<Unk_7102519b90>(handle->mHandle.getResource())->getEntries().getBufferPtr();
        const s32 count =
            sead::DynamicCast<Unk_7102519b90>(handle->mHandle.getResource())->getEntries().size();
        for (s32 i = 0; i != count; ++i) {
            if (entries[i]._8 && entries[i]._28)
                HavokAI::instance()->sub_7100F81868(&entries[i]);
        }
        handle->_58 = 1;
    }
}

// NON_MATCHING: register allocation only (the cast type info and the lock spill to the other stack
// slots; the body, both loops and the buffer teardown agree instruction for instruction).
void NavMeshLoadMgr::sub_7100F898E4() {
    auto lock = sead::makeScopedLock(_130);
    if (_10) {
        const u32 count = _8;
        for (u32 i = 0; i != count; ++i) {
            TileHandle& handle = _10[i];
            if (!handle._58)
                continue;
            auto* resource =
                sead::DynamicCast<Unk_7102519b90>(handle.mHandle.getResource());
            for (auto& entry : resource->getEntries()) {
                if (entry._8 && entry._28)
                    HavokAI::instance()->sub_7100F81EE0(&entry, false);
            }
        }
    }
    if (_10) {
        delete[] _10;
        _10 = nullptr;
        _8 = 0;
    }
    _190 = false;
}

// NON_MATCHING: the Buffer bounds compare keeps the size and index in the opposite registers (only
// a commutative cmp residue; every other instruction agrees).
void NavMeshLoadMgr::sub_7100F8AA78(s32 index, const sead::Matrix34f& transform) {
    if (_190)
        return;
    auto lock = sead::makeScopedLock(_130);
    if (!_10 || (_178.x | _178.y) != 0)
        return;
    auto* resource = sead::DynamicCast<Unk_7102519b90>(_10->mHandle.getResource());
    if (index < 0 || !resource)
        return;
    auto& entries = resource->getEntries();
    const s32 i = index + 1;
    if (entries.size() <= i || !entries.getBufferPtr()[i]._8)
        return;
    entries.get(i)->sub_71012A7324(transform);
}

// NON_MATCHING: the final `abs(z - _188.y) >= 2` compare is if-converted to `cset` where the original
// branches through the shared false block; the return value also lives in w20 there and w22 here.
bool NavMeshLoadMgr::x_0(const sead::Vector3f* pos) {
    if (_190)
        return false;
    auto lock = sead::makeScopedLock(_130);
    if (!_10)
        return false;
    if ((_178.x | _178.y) == 0)
        return true;
    const s32 x = sead::Mathi::clamp((s32(pos->x) - _170.x) / _178.x, 0, _180.x - 1);
    if (sead::Mathi::abs(x - _188.x) > 1)
        return false;
    const s32 z = sead::Mathi::clamp((s32(pos->z) - _170.y) / _178.y, 0, _180.y - 1);
    if (sead::Mathi::abs(z - _188.y) >= 2)
        return false;
    return true;
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
    if (handle->mHandle.requestedLoad()) {
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
            if (handle->mHandle.requestedLoad() && handle->_50 == x && handle->_54 == z)
                return handle->sub_7100F8AF0C();
        }
        return false;
    }
    auto lock = sead::makeScopedLock(_130);
    TileHandle* handle = _8 ? &_10[0] : nullptr;
    return handle->sub_7100F8AF0C();
}

bool NavMeshLoadMgr::TileHandle::sub_7100F8AF0C() {
    if (!mHandle.requestedLoad() || _58 != 1)
        return false;

    const auto* entries =
        sead::DynamicCast<Unk_7102519b90>(mHandle.getResource())->getEntries().getBufferPtr();
    const s32 count = sead::DynamicCast<Unk_7102519b90>(mHandle.getResource())->getEntries().size();
    for (s32 i = 0; i != count; ++i) {
        if (entries[i]._8 && !(entries[i]._60.load() & 0x400))
            return false;
    }
    return true;
}

void NavMeshLoadMgr::x_3(TileHandle* handle, TileHandle* other) {
    if (handle->mHandle.isReadyOrNeedsParse())
        handle->mHandle.parseResource(nullptr);
    if (!handle->mHandle.requestedLoad())
        return;

    bool matched = false;
    if (handle == other) {
        const u32 count = sead::Mathu::min(_8, 9u);
        sead::Buffer<TileHandle> tiles(count, _10);
        for (TileHandle& tile : tiles) {
            if (tile.mHandle.requestedLoad() && handle->_50 == tile._50 &&
                handle->_54 == tile._54) {
                matched = true;
                break;
            }
        }
    } else if (other && other->mHandle.requestedLoad() && handle->_50 == other->_50 &&
               handle->_54 == other->_54) {
        matched = true;
    }

    if (!matched) {
        switch (handle->_58) {
        case 0: {
            auto* resource =
                sead::DynamicCast<Unk_7102519b90>(handle->mHandle.getResource());
            if (resource) {
                for (auto& entry : resource->getEntries()) {
                    if (entry._58 || (entry._60.load() & 0x3c00)) {
                        handle->_58 = 1;
                        break;
                    }
                }
            }
            if (handle->_58 == 0) {
                handle->mHandle.requestUnload();
                return;
            }
            [[fallthrough]];
        }
        case 1: {
            auto* entries = sead::DynamicCast<Unk_7102519b90>(handle->mHandle.getResource())
                                ->getEntries().getBufferPtr();
            const s32 count = sead::DynamicCast<Unk_7102519b90>(handle->mHandle.getResource())
                                  ->getEntries().size();
            for (s32 i = 0; i != count; ++i) {
                if (entries[i]._8 || entries[i]._28)
                    HavokAI::instance()->sub_7100F81930(&entries[i]);
            }
            handle->_58 = 2;
            return;
        }
        case 2: {
            auto* entries = sead::DynamicCast<Unk_7102519b90>(handle->mHandle.getResource())
                                ->getEntries().getBufferPtr();
            const s32 count = sead::DynamicCast<Unk_7102519b90>(handle->mHandle.getResource())
                                  ->getEntries().size();
            bool found = false;
            for (s32 i = 0; i != count; ++i) {
                if (entries[i]._58) {
                    found = true;
                    continue;
                }
                if (entries[i]._60.load() & 0x3c00) {
                    HavokAI::instance()->sub_7100F81930(&entries[i]);
                    found = true;
                }
            }
            if (found)
                return;
            break;
        }
        default:
            return;
        }
    }

    handle->_58 = 0;
    handle->mHandle.requestUnload();
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
    if (handle->mHandle.requestedLoad())
        x_3(handle, handle);
}

}  // namespace ksys::phys

// The original emits sead::StackTrace<8> in this TU (vtable 0x71024f7060).
template class sead::StackTrace<8>;
