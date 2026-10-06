#pragma once

#include <basis/seadTypes.h>

namespace aal {

class SoundSource;

/// Tracks the markers of the asset of a sound (and calls the marker callback). TODO: incomplete; the members that
/// the constructor / setup / reset initialise are modeled (names of the unknown ones start with an underscore).
class MarkerController {
public:
    MarkerController();

    void setup(SoundSource* sound_source);
    void reset();

private:
    SoundSource* mSoundSource;
    void* _8;
    void* _10;
    s32 _18;
    u64 _20;
    s32 _28;
    s32 _2c;
};
static_assert(sizeof(MarkerController) == 0x30, "aal::MarkerController size mismatch");

}  // namespace aal
