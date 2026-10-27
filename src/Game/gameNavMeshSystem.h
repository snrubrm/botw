#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <limits>
#include <math/seadVector.h>
#include "KingSystem/Physics/System/physCharacterControllerParam.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Utils/Types.h"

namespace uking {

// Stage-local navigation obstacles. Factory 0x7100e8e850 allocates 0x30 bytes;
// its singleton disposer starts at +0, followed by the 0x260-byte obstacle buffer.
class NavMeshSystem {
    SEAD_SINGLETON_DISPOSER(NavMeshSystem)
    NavMeshSystem() = default;
    ~NavMeshSystem();

public:
    void init(sead::Heap* heap);
    // 0x7100e8f1c0 (declaration only; placeholder name): called by Unk_710251cbf0's destructor with the
    // fire position, its obstacle id and 1.5f.
    void sub_7100E8F1C0(const sead::Vector3f* position, s32 id, f32 radius);

private:
    struct Entry;
    sead::Buffer<Entry> mEntries;
};
KSYS_CHECK_SIZE_NX150(NavMeshSystem, 0x30);

}  // namespace uking

namespace uking::ai {

// Placeholder name (vtable 0x71024ed6a0): the navmesh position query that WolfLinkAmiibo's
// sub_7100600A6C allocates (0x50 bytes) and submits. m0 runs the nearest-face query at _18 with
// the radius in _30, keeps the reference position it was handed as the hit position and stops the
// search once the accumulated face area reaches _3c.
class Unk_71024ed6a0 : public ksys::phys::Unk_7102372790 {
public:
    // 0x7100e8e67c
    bool m0(const ksys::phys::Unk_7100f7e9f0& face, const sead::Vector3f& ref_pos) override;

    /* 0x34 */ ksys::phys::NavMeshCharacterType _34 = ksys::phys::NavMeshCharacterType::Horse;
    /* 0x38 */ f32 _38 = 0;  // accumulated face area
    /* 0x3c */ f32 _3c = 0;  // area limit
    /* 0x40 */ sead::Vector3f _40{std::numeric_limits<f32>::quiet_NaN(),
                                  std::numeric_limits<f32>::quiet_NaN(),
                                  std::numeric_limits<f32>::quiet_NaN()};
    /* 0x4c */ u8 _4c[4];
};
KSYS_CHECK_SIZE_NX150(Unk_71024ed6a0, 0x50);

}  // namespace uking::ai
