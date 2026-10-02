#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace ksys::snd {

enum class AudioChannelType {
    Mono = 1,
    Stereo = 2,
    _5_1ch = 6,
    Other = -1  // TODO: does Other have a definite value?
};

// Name from the CSV (snd::ListenerPoser::ctor 0x71010549d8, init 0x7101054b30): size 0xe0, created
// in SoundMgr's init (CSV Sound::init) and stored in SoundMgr::_58. Probably derived from
// aal::ListenerPoser (not in the repo).
// TODO: incomplete.
class ListenerPoser {
public:
    virtual ~ListenerPoser();

    u8 _8[0x80 - 0x8];
    u32 _80;  // set to 1 / 0 by uking::action::CameraAction enter_ / leave_
    u8 _84[0xe0 - 0x84];
};

// FIXME: incomplete
struct SoundMgr {
    SEAD_SINGLETON_DISPOSER(SoundMgr)

    virtual ~SoundMgr();

public:
    u8 _28[0x58 - 0x28];
    ListenerPoser* _58;
    u8 _60[0x270 - 0x60];
    AudioChannelType mAudioChannelType;
};

}  // namespace ksys::snd
