#pragma once

#include <basis/seadTypes.h>

// Partial declaration: name from the CSV Graphics::createInstance (0x7100f2a1d0).
// Source namespace remains unknown; global spelling follows the existing scene placeholders.
// No instance layout or construction is modeled here.
class Graphics {
public:
    // Placeholder name: the block at Graphics + 0xa98 (shadow settings; lane3 s35, only the fields
    // EventChangeShadowNearAndFar::calc_ writes are modeled).
    struct Unk_a98 {
        u8 _0[0x12];
        /* 0x12 */ u16 mFlags;  // bit 8: near distance set manually, bit 9: far distance set manually
        u8 _14[0x540 - 0x14];
        /* 0x540 */ f32 mShadowNear;
        /* 0x544 */ f32 mShadowFar;
    };

    // Original instance pointer 0x710260b060 (GOT 0x7102579d58).
    static Graphics* instance() { return sInstance; }
    static Graphics* sInstance;

    // 0x7100f2ddf0: declaration only; selects a lens-flare preset, negative disables it.
    void sub_7100F2DDF0(s32 preset);

    // Only a pointer to the (separately allocated) shadow settings is modeled.
    Unk_a98* getUnk_a98() const { return _a98; }

private:
    u8 _0[0xa98];
    Unk_a98* _a98;
};
