#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

namespace ksys::snd {

// Name from the CSV (snd::DuckingMgr::startDucking 0x7101042078; ctor 0x710103e404, init 0x710103e58c).
// SoundMgr::_80. A buffer (size at +8, data at +0x10) of 50 duckers (0xd0 bytes each: aal::GroupDucker at +0x68,
// `_c0` / `_c8` state) indexed by a SEAD_ENUM of ducker names (the enum's text function is 0x7101042f30);
// entries 0x30 / 0x31 are the "custom" duckers used by Unk_710103b704.
// TODO: incomplete.
class DuckingMgr {
public:
    struct Ducker;

    // 0x7101042078: starts the ducker called `type` (looked up by name); null when there is none.
    Ducker* startDucking(const sead::SafeString& type);
    // 0x7101042db4 (declared only): stops the ducker called `type` (`suspend`: also suspends its aal::GroupDucker).
    void sub_7101042DB4(const sead::SafeString& type, bool suspend);
    // 0x7101042024 (declared only): starts the ducker with index `idx`.
    Ducker* sub_7101042024(int idx);
};

// Placeholder name (ctor 0x710103b704; SoundMgr::_98): starts / stops the two custom duckers (indices 0x30 / 0x31
// of the DuckingMgr). Used by CustomDuckingStartAction / CustomDuckingEndAction.
class Unk_710103b704 {
public:
    struct StartParam {
        sead::SafeString _0;
        sead::SafeString _10;
        f32 _20;
        f32 _24;
        f32 _28;
        f32 _2c;
    };

    // 0x710103cff4 (declared only)
    void sub_710103CFF4(StartParam& param);
    // 0x710103d094 (declared only)
    void sub_710103D094();
};

// Placeholder name (ctor 0x710104e5b4; SoundMgr::_90; the object has a byte at +0x2a0 whose bit 2 means "ducking
// is allowed"). Used by the message-dialog / talk actions (NPCTalk, OpenMessageDialog*, SimpleUniqueTalk).
class Unk_710104e5b4 {
public:
    // 0x710104f86c (declared only): starts the dialogue ducker (SoundMgr::_80 ducker 0x10) while an event is active.
    void sub_710104F86C();
};

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
    u8 _60[0x80 - 0x60];
    /* 0x80 */ DuckingMgr* mDuckingMgr;
    u8 _88[8];
    /* 0x90 */ Unk_710104e5b4* _90;
    /* 0x98 */ Unk_710103b704* _98;
    u8 _a0[0x270 - 0xa0];
    AudioChannelType mAudioChannelType;
};

}  // namespace ksys::snd
