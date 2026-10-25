#include "Game/gameGraphics.h"
#include <gfx/seadGraphicsContext.h>
#include <math/seadMathCalcCommon.h>
#include <utility/aglDevTools.h>
#include <new>

// Home of the Graphics render-block TUs at 0x710128a000..0x710128cfff (Graphics::Unk_378 and the
// code around it). The shadow settings setter below belongs here: its code sits at 0x710128b084,
// between the Unk_378 helpers 0x710128af04 and 0x710128b08c.

// 0x710128b084 (unnamed in the CSV): sets the quality index of the shadow settings block reached
// through Graphics + 0xa98. Graphics' shadow mode switch (0x7100f2f2c8) calls it with 1..4.
void Graphics::Unk_a98::setQuality(u32 quality) {
    mQuality = quality;
}

// 0x710128babc (unnamed in the CSV): bumps the change counter at +0x7c. Graphics' shadow mode
// path (0x7100f1fdc8) calls it on the shadow settings block after testing a related flag.
void Graphics::Unk_a98::incrementChangeCountMaybe() {
    mChangeCount.increment();
}

// 0x710128ab14: constructs the two banks of debug render textures (each unit is a TextureData and
// the GPUMemBlock that owns its image).
Graphics::Unk_378_18_6b0::Unk_378_18_6b0() {}

// 0x710128aa50: destroys the banks' textures and their GPU memory blocks.
Graphics::Unk_378_18_6b0::~Unk_378_18_6b0() {}

// 0x7101288658: constructs the debug block (Graphics' initializer stores it at Graphics + 0x378).
Graphics::Unk_378::Unk_378()
    : _8(6), mBlocks(), _20(nullptr), mPage(), _268(3), _26c(3), mSamples(), mSampleIndex(0), _284(1),
      _288(4.0f), _28c(1.5f), _290(1.5f), _294(0.15f), _298(1.0f), _29c(0.001f), _2a0(0.4f),
      _2a4(1.0f), _2a8(200.0f), _2ac(1.5f), _2b0(0.7f) {}

// 0x7101288710: releases the sample history, then every block's cell buffer, then the block array.
// The debug texture page and its disposer are destroyed as members.
Graphics::Unk_378::~Unk_378() {
    mSamples.freeBuffer();
    for (auto& block : mBlocks)
        block._12a8.freeBuffer();
    mBlocks.freeBuffer();
}

// 0x710128ca44: constructs the focus controller at Graphics + 0x668 (vtable 0x71025190d0).
Graphics::Unk_668::Unk_668() {}

// 0x710128ca70: releases the parameter block the controller owns.
Graphics::Unk_668::~Unk_668() {
    if (_10) {
        delete[] _10;
        _10 = nullptr;
        _8 = 0;
    }
}

// 0x710128cbcc (placeholder name): stores `value` at _10+0x70 and chases _10+0x74 towards it with
// the rate at +0x1c. The third argument is unused.
// NON_MATCHING: the first multiply's register order is swapped (fmul s0, s0, s3).
void Graphics::Unk_668::chaseValueMaybe(f32 value, f32 delta, bool snap) {
    auto* data = _10;
    const f32 prev = data->_74;
    data->_70 = value;
    data->_74 = prev + _1c * (value - prev) * delta;
}

// 0x710128caec (placeholder name): allocates `count` 0x78-byte records and initializes their two
// identity matrices, the zero vector and the three 1.0 floats.
void Graphics::Unk_668::initMaybe(s32 count, sead::Heap* heap) {
    if (count >= 1) {
        auto* data = new (heap, 8, std::nothrow) Unk_668_10[count];
        if (data) {
            _8 = count;
            _10 = data;
        }
    }

    Unk_668_10* data = _10;
    const u64 num = u32(_8);
    for (u64 i = 0; i < num; ++i) {
        data->mPrevMatrix.makeIdentity();
        data->mMatrix.makeIdentity();
        data->_60 = sead::Vector3f::zero;
        data->_74 = 1.0f;
        data->mValue = 1.0f;
        data->_70 = 1.0f;
        ++data;
    }
}

// 0x710128a988 (placeholder name): draws the block's debug grid in the XZ plane when the enable
// flag is set.
void Graphics::Unk_378::sub_710128A988(agl::DrawContext* context, u8) {
    if (!(_8 & 1))
        return;

    sead::GraphicsContext graphics_context;
    graphics_context.setDepthTestEnable(false);
    graphics_context.setDepthWriteEnable(false);
    graphics_context.apply(context);

    sead::Matrix34f matrix;
    matrix.makeR({sead::Mathf::piHalf(), 0.0f, 0.0f});

    agl::utl::DevTools::beginDrawImm(context, matrix, sead::Matrix44f::ident);
    agl::utl::DevTools::drawGridImm(context, 2.0f, 2.0f, _268, _26c, sead::Color4f::cWhite, 1.0f);
}

// 0x710128aa30 (placeholder name): stores `value` at +0x14f0 of block `view` (the block array is at
// +0x18 with 0x1530-byte elements and falls back to block 0 out of range).
void Graphics::Unk_378::setValueMaybe(f32 value, s32 view) {
    mBlocks[view]._14f0 = value;
}
