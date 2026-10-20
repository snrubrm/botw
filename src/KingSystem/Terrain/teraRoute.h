#pragma once

#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <common/aglTextureSampler.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::tera {

// Terrain's renderable rail curve. Constructor 0x710110e390; PlacementMapMgr::parseRoute
// allocates 0x488 bytes and passes its 0x38-byte control points to sub_710110E4A8.
class Unk_710110e390 {
public:
    struct Point {
        sead::Vector3f translate;
        sead::Vector3f control_points[2];
        f32 scale;
        u8 _28[0x38 - 0x28];
    };
    KSYS_CHECK_SIZE_NX150(Point, 0x38);
    struct InitArg {
        sead::Heap* heap;
        u32 _8;
        sead::SafeString name;
        const Point* points;
        u32 num_points;
        bool _2c;
    };
    struct Segment;
    struct Node;

    Unk_710110e390();
    // Builds segment lengths, the subdivision tree and the two texture samplers.
    bool sub_710110E4A8(const InitArg& arg);
    void sub_710110E408();

private:
    void* _0 = nullptr;
    void* _8 = nullptr;
    u32 _10 = 0;
    sead::SafeString mName = sead::SafeString::cEmptyString;
    sead::Buffer<Segment> mSegments;
    f32 mLength = 0;
    // 0x710110f03c computes the arc-length sampling step here.
    f32 mSampleStep = 0;
    sead::Buffer<Node> mNodes;
    u64 _50 = 0;
    s32 mTreeDepth = 0;
    agl::TextureSampler mSamplers[2];
    // Bit 3 of mFlags marks the image pointers as owned; sub_710110E408 clears it.
    struct Unk_340 {
        u8 _0[0x140];
        u32 mFlags;
    };
    KSYS_CHECK_SIZE_NX150(Unk_340, 0x144);
    /* 0x340 */ Unk_340 _340{};
};
KSYS_CHECK_SIZE_NX150(Unk_710110e390, 0x488);

}  // namespace ksys::tera
