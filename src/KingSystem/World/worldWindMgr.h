#pragma once

#include <math/seadVector.h>
#include <nn/gfx/gfx_ResTextureData.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// Render-wind object: allocated as 0x268 bytes by WindMgr::init_ at 0x71010ee214.
// Its constructor is 0x71012fe90c and its vtable is 0x710251f868; implementation remains declared-only.
struct Unk_710251F868 {
    f32 sub_71012FF2B0(f32 strength);
    f32 sub_71012FF268(f32 strength);
    u8 _0[8];
    f32 _8;
    u8 _c[0x1b8 - 0xc];
    nn::gfx::ResTextureData _1b8;
    u8 _258[0x268 - 0x258];
};
KSYS_CHECK_SIZE_NX150(Unk_710251F868, 0x268);

class WindMgr : public Job {
public:
    WindMgr();

    JobType getType() const override { return JobType::Wind; }

    void sub_71010EEBE4(sead::Vector3f* out, const sead::Vector3f* position);
    void sub_71010EEA98(sead::Vector3f* out, const sead::Vector3f* position);
    nn::gfx::ResTextureData* sub_71010EEEE8();
    f32 sub_71010EEF48() const;
    f32 sub_71010EEF04() const;
    f32 x_0();
    f32 x_1();

    Unk_710251F868* _20;
    u8 _28;
    u8 _29[0x34 - 0x29];
    sead::Vector3f _34;
    u8 _40[0x68 - 0x40];
    f32 _68;
    u8 _6c[0x80 - 0x6c];
    f32 _80;
    u8 _84[0x98 - 0x84];
    nn::gfx::ResTextureData _98;
};
KSYS_CHECK_SIZE_NX150(WindMgr, 0x138);

}  // namespace ksys::world
