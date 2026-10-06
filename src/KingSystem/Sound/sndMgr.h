#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace aal {
class Shape;
}

namespace xlink2 {
class HandleSLink;
}

namespace ksys::act {
class Actor;
}

namespace ksys::snd {

// Only the interface needed by the UI sound wrapper is recovered.
class UiSoundMgr {
public:
    bool playSound(const sead::SafeString& label, xlink2::HandleSLink* handle);
};

// Placeholder name (SoundMgr::_38::_30). Holds the aal::SpeakerBalanceUnifier objects at +0x68 (count at +0x60,
// guarded by a CriticalSection at +0x20); shapes are registered with the one picked by a size threshold.
class SpeakerBalanceUnifierMgr {
public:
    // 0x7101027d4c (declared only): adds `shape` to the unifier chosen by `size` (3 thresholds).
    void sub_7101027D4C(f32 size, aal::Shape* shape);
    // 0x7101027e0c (declared only): removes `shape` from every unifier.
    void sub_7101027E0C(aal::Shape* shape);
    // 0x7101027e90 (declared only): emits the SLink sound for `type` (1 or 2) picked by `size` and
    // attaches `shape` to its sound source.
    xlink2::HandleSLink sub_7101027E90(f32 size, int type, aal::Shape* shape);
};

// Placeholder name (SoundMgr::_38::_28; lane5 s6): the occlusion volume state of the sound manager, used by the
// SoundOcclusionTag* actions (the sound is occluded while the player is inside the box set by sub_7101037ED8).
class Unk_SoundMgr38_28 {
public:
    // 0x7101037ed8 (declared only; 132 B): sets the box (centre `pos`, size `size`) and stores both vectors.
    void sub_7101037ED8(const sead::Vector3f* pos, const sead::Vector3f* size);
    // 0x7101037f5c: stores `value` in the byte at +0x344.
    void sub_7101037F5C(u8 value);
    // 0x7101037f64: sets the enabled flag at +0x328 (clears the pointers at +0x3c0 / +0x3c8 when disabled).
    void sub_7101037F64(bool enabled);

    u8 _0[0x398];
    /* 0x398 */ f32 _398;
};

// Placeholder name (SoundMgr::_38).
struct Unk_SoundMgr38 {
    // 0x710102c104 (declared only; 8 B): returns `_28`.
    Unk_SoundMgr38_28* sub_710102C104() const;

    u8 _0[0x30];
    SpeakerBalanceUnifierMgr* _30;
};

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

// Placeholder name (SoundMgr::_48; the object has an aal::Handle at +0x18). Used by the UI message screens.
class Unk_SoundMgr48 {
public:
    // 0x7101055b44 (declared only; CSV unnamed)
    void sub_7101055B44();
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

    // 0x710103bb00 (declared only; CSV unnamed): applies the scene sound controls (bgm type, se type) now.
    void sub_710103BB00(int bgm_type, int se_type);
    // 0x710103cfe8: stores the two types in _5d0 / _5d4 for later (used while _5cc is set).
    void sub_710103CFE8(int bgm_type, int se_type);

    u8 _0[0x5cc];
    /* 0x5cc */ bool _5cc;
    u8 _5cd[0x5d0 - 0x5cd];
    /* 0x5d0 */ int _5d0;
    /* 0x5d4 */ int _5d4;
    // Set by SceneSoundSetEndProcAction ("SkipAll"); name unknown.
    /* 0x5d8 */ bool _5d8;
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

// Placeholder name (SoundMgr::_60): `_28` is the address of the xlink2 SLink resource list the UI screens
// (uking::ui::ScreenBase::getSlink2ResourceList_) hand to their sound link users.
struct Unk_SoundMgr60 {
    u8 _0[0x28];
    u8 mSlinkResources[8];
};

// Placeholder name: the sound instances the AreaTagAction family (Shielding / Occlusion / Reverb) get from
// SoundMgr::_a8.
struct Unk_SoundInstance {
    // 0x710104acb4 (declared only; 68 B).
    bool sub_710104ACB4();

    u8 _0[0x440];
    /* 0x440 */ f32 _440;
    u8 _444[0x490 - 0x444];
    /* 0x490 */ bool _490;
    /* 0x491 */ bool _491;
};

// Placeholder name (SoundMgr::_a8): the manager of the sound instances the AreaTagAction family hold at +0xa0.
class Unk_SoundMgra8 {
public:
    // 0x710104b554 (CSV nullsub_4415; declared only): releases `instance`.
    void sub_710104B554(Unk_SoundInstance* instance);
    // 0x710104b558 (declared only; 132 B): the volume the sound instance list gives `actor` (the first
    // non-negative value of the instances' 0x710104ac00 query, else -1).
    f32 sub_710104B558(ksys::act::Actor* actor);
};

// FIXME: incomplete
struct SoundMgr {
    SEAD_SINGLETON_DISPOSER(SoundMgr)

    virtual ~SoundMgr();

    // 0x71011fc29c (lane2 request, s49; placeholder name): starts the ducker 0x23 of the DuckingMgr and sets bit 1 of
    // `_238`.
    void sub_71011FC29C();

public:
    u8 _28[0x38 - 0x28];
    Unk_SoundMgr38* _38;
    /* 0x40 */ UiSoundMgr* mUiSoundMgr;
    /* 0x48 */ Unk_SoundMgr48* _48;
    u8 _50[0x58 - 0x50];
    ListenerPoser* _58;
    /* 0x60 */ Unk_SoundMgr60* _60;
    u8 _68[0x80 - 0x68];
    /* 0x80 */ DuckingMgr* mDuckingMgr;
    u8 _88[8];
    /* 0x90 */ Unk_710104e5b4* _90;
    /* 0x98 */ Unk_710103b704* _98;
    u8 _a0[0xa8 - 0xa0];
    /* 0xa8 */ Unk_SoundMgra8* _a8;
    u8 _b0[0x238 - 0xb0];
    u8 _238;
    u8 _239[0x270 - 0x239];
    AudioChannelType mAudioChannelType;
};

}  // namespace ksys::snd
