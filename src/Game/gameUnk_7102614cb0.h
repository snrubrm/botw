#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
class UserInstanceSLink;
}

// Placeholder name: an unnamed singleton (instance pointer 0x7102614cb0) whose member at +0x28 is the
// SLink user instance the sound triggers (SoundTriggerFadeAction / SoundTrigger) fall back to. Declaration
// only (lane5 s5); the class is otherwise unknown.
class Unk_7102614cb0 {
public:
    static Unk_7102614cb0* instance() { return sInstance; }

    /* 0x00 */ u8 _0[0x28];
    /* 0x28 */ xlink2::UserInstanceSLink* _28;

private:
    static Unk_7102614cb0* sInstance;
};
