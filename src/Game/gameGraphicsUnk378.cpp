#include "Game/gameGraphics.h"
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
// NON_MATCHING: clang pairs the identity stores (the original keeps six 16-byte stores off a
// +0x74-based pointer) and tests the record count with an index instead of a countdown.
void Graphics::Unk_668::initMaybe(s32 count, sead::Heap* heap) {
    if (count >= 1) {
        auto* data = new (heap, 8, std::nothrow) Unk_668_10[count];
        if (data) {
            _8 = count;
            _10 = data;
        }
    }

    Unk_668_10* data = _10;
    for (s32 i = 0; i < _8; ++i) {
        data->mMatrix.makeIdentity();
        data->mPrevMatrix.makeIdentity();
        data->_60 = sead::Vector3f::zero;
        data->mValue = 1.0f;
        data->_70 = 1.0f;
        data->_74 = 1.0f;
        ++data;
    }
}
