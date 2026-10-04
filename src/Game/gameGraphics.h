#pragma once

#include <basis/seadTypes.h>

// Partial declaration: name from the CSV Graphics::createInstance (0x7100f2a1d0).
// Source namespace remains unknown; global spelling follows the existing scene placeholders.
// No instance layout or construction is modeled here.
class Graphics {
public:
    // Original instance pointer 0x710260b060 (GOT 0x7102579d58).
    static Graphics* instance() { return sInstance; }
    static Graphics* sInstance;

    // 0x7100f2ddf0: declaration only; selects a lens-flare preset, negative disables it.
    void sub_7100F2DDF0(s32 preset);
};
