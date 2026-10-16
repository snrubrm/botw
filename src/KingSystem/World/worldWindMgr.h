#pragma once

#include <math/seadVector.h>
#include <common/aglTextureSampler.h>
#include <common/aglGPUMemAddr.h>
#include <nn/gfx/gfx_ResTextureData.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// Render-wind object: allocated as 0x268 bytes by WindMgr::init_ at 0x71010ee214.
// Its constructor is 0x71012fe90c and its vtable is 0x710251f868; constructor and phase update are implemented below.
struct Unk_710251F868 {
    Unk_710251F868();
    virtual ~Unk_710251F868();
    void sub_71012FEAA8(sead::Heap* heap);
    // Full native 12FEBE4 rebuilds the render-wind texture and its range tables.
    void sub_71012FEBE4();
    void sub_71012FEFF0(f32 delta);
    f32 sub_71012FF2B0(f32 strength);
    f32 sub_71012FF268(f32 strength);
    f32 sub_71012FF01C(const sead::Vector3f* position, const sead::Vector2f* direction,
                          f32 strength, f32 value) const;
    f32 _8;
    f32 _c;
    f32 _10;
    u8 _14[4];
    u32 _18;
    u32 _1c;
    u32 _20;
    u32 _24;
    agl::GPUMemAddrBase _28;
    agl::TextureData* _40;
    agl::TextureSampler _48;
    nn::gfx::ResTextureData _1b8;
    f32 _258;
    f32 _25c;
    f32 _260;
    f32 _264;
};
KSYS_CHECK_SIZE_NX150(Unk_710251F868, 0x268);

// Embedded wind-transition state; vtable 0x710250d258.
// Constructor 10EE15C and update 10EE904 establish these four fields.
class Unk_710250D258 {
public:
    Unk_710250D258() : _8(false), _c(0), _10(1.0f), _14(0.0f) {}
    virtual ~Unk_710250D258();
    void sub_71010EE904(f32 delta, f32 speed);
    bool _8;
    s32 _c;
    f32 _10;
    f32 _14;
};
KSYS_CHECK_SIZE_NX150(Unk_710250D258, 0x18);

class WindMgr : public Job {
    SEAD_RTTI_OVERRIDE(WindMgr, Job)
public:
    WindMgr();
    ~WindMgr() override;

    void init_(sead::Heap* heap) override;
    void calc_() override {}
    void calcType1_() override {}
    void calcType2_() override;
    void drawDebug() override;

    JobType getType() const override { return JobType::Wind; }

    void sub_71010EEBE4(sead::Vector3f* out, const sead::Vector3f* position);
    void sub_71010EEA98(sead::Vector3f* out, const sead::Vector3f* position);
    f32 sub_71010EECE8(const sead::Vector3f* position, f32 value);
    f32 sub_71010EECF8(const sead::Vector3f* position, f32 value);
    f32 sub_71010EEC04();
    agl::TextureSampler* sub_71010EEE94();
    agl::TextureData* sub_71010EEEBC();
    nn::gfx::ResTextureData* sub_71010EEEE8();
    f32 sub_71010EEF48() const;
    f32 sub_71010EEF04() const;
    f32 x_0();
    f32 x_1();

    Unk_710251F868* _20;
    u8 _28;
    u8 _29[3];
    f32 _2c;
    f32 _30;
    sead::Vector3f _34;
    sead::Vector3f _40;
    f32 _4c;
    sead::Vector2f _50;
    sead::Vector2f _58;
    f32 _60;
    f32 _64;
    f32 _68;
    f32 _6c;
    Unk_710250D258 _70;
    sead::Vector3f _88;
    nn::gfx::ResTextureData _98;
};
KSYS_CHECK_SIZE_NX150(WindMgr, 0x138);

}  // namespace ksys::world
