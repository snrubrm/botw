#pragma once

#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
class Model;
}

namespace ksys::phys {
class Unk_71024f67c8;
}

namespace uking::act {

// Placeholder name: HorseBase +0xb28, allocated as 0x208 bytes by 0x7100e72e18.
// Its four chains drive the horse leg bones; 0x7100e72f0c fills one BoneSet per chain.
// The vtable at 0x71024eb5e0 has only the two destructor slots.
class Unk_71024eb5e0 {
public:
    virtual ~Unk_71024eb5e0();
    // 0x7100e7332c releases the chains before invoking the deleting destructor.
    void destroy();

    struct BoneSet {
        ~BoneSet() {
            mKeys.freeBuffer();
            mMatrices.freeBuffer();
        }

        gsys::Model* mModel;
        sead::Buffer<gsys::BoneAccessKey> mKeys;
        sead::Buffer<sead::Matrix34f> mMatrices;
    };
    KSYS_CHECK_SIZE_NX150(BoneSet, 0x28);

    /* 0x008 */ ksys::phys::Unk_71024f67c8* mChains[4];
    /* 0x028 */ u32 _28[4];
    /* 0x038 */ u32 _38[4];
    /* 0x048 */ sead::Vector3f _48[4];
    /* 0x078 */ f32 _78[4];
    /* 0x088 */ f32 _88[4];
    /* 0x098 */ f32 _98[4];
    /* 0x0a8 */ sead::Vector3f _a8[4];
    /* 0x0d8 */ sead::SafeArray<BoneSet, 4> mBoneSets;
    /* 0x178 */ sead::Vector3f _178[4];
    /* 0x1a8 */ sead::Vector3f _1a8[4];
    /* 0x1d8 */ u32 _1d8[4];
    /* 0x1e8 */ gsys::Model* mModel;
    /* 0x1f0 */ u32 _1f0;
    /* 0x1f4 */ f32 _1f4;
    /* 0x1f8 */ f32 _1f8;
    /* 0x1fc */ f32 _1fc;
    /* 0x200 */ f32 _200;
};
KSYS_CHECK_SIZE_NX150(Unk_71024eb5e0, 0x208);

}  // namespace uking::act
