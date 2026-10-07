#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include <container/seadPtrArray.h>
#include <aal/aalHandle.h>
#include <thread/seadCriticalSection.h>

namespace aal {
class Shape;
}

namespace xlink2 {
class HandleSLink;
class UserInstanceSLink;
}

namespace ksys::act {
class Actor;
}

namespace ksys::snd {

struct Unk_SoundMgr30;

// Only the interface needed by the UI sound wrapper is recovered.
class UiSoundMgr {
public:
    // 0x710105d330: emits the SLink sound `label` through the user instance at +0x20; the handle is copied to
    // `handle` if given. Returns whether the emitted event is alive.
    bool playSound(const sead::SafeString& label, xlink2::HandleSLink* handle);

    u8 _0[0x20];
    /* 0x20 */ xlink2::UserInstanceSLink* _20;
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
    // 0x7101037f7c: stores `value` in the byte at +0x39c.
    void sub_7101037F7C(bool value);

    u8 _0[0x328];
    /* 0x328 */ bool _328;
    /* 0x32c */ sead::Vector3f mBoxMin;
    /* 0x338 */ sead::Vector3f mBoxMax;
    /* 0x344 */ u8 _344;
    u8 _345[0x398 - 0x345];
    /* 0x398 */ f32 _398;
    /* 0x39c */ bool _39c;
    u8 _39d[0x3c0 - 0x39d];
    /* 0x3c0 */ void* _3c0;
    /* 0x3c8 */ void* _3c8;
    u8 _3d0[0x3d8 - 0x3d0];
    /* 0x3d8 */ sead::Vector3f mBoxCenter;
    /* 0x3e4 */ sead::Vector3f mBoxSize;
};

// Placeholder name (SoundMgr::_38).
struct Unk_SoundMgr38 {
    // 0x710102c104: returns `_28`.
    Unk_SoundMgr38_28* sub_710102C104() const;

    u8 _0[0x28];
    /* 0x28 */ Unk_SoundMgr38_28* _28;
    /* 0x30 */ SpeakerBalanceUnifierMgr* _30;
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
    // 0x7101042d6c (declared only): clears bit 0 of the ducker `idx`'s flags byte (+0xc8) and suspends its
    // aal::GroupDucker if `suspend`.
    void sub_7101042D6C(int idx, bool suspend);
};

// Placeholder name (SoundMgr::_48; the object has an aal::Handle at +0x18). Used by the UI message screens.
class Unk_SoundMgr48 {
public:
    // 0x7101055b44 (CSV unnamed): stops the handle with a short fade if it is enabled.
    void sub_7101055B44();
    // 0x7101055e3c: returns 0.2f.
    f32 sub_7101055E3C() const;

    u8 _0[0x18];
    /* 0x18 */ aal::Handle _18;
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
    // 0x710103d418: starts the ducker 0x1f.
    void sub_710103D418();

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
    // The singleton (instance pointer 0x7102614cb0, size 0x2a8, disposer at +8; SoundMgr::_90 points to it as well;
    // it was a separate placeholder `Unk_7102614cb0` before). Defined by the symbol map only.
    static Unk_710104e5b4* instance() { return sInstance; }

    // 0x710104f86c: starts the dialogue ducker (SoundMgr::_80 ducker 0x10) while an event is active.
    void sub_710104F86C();
    // 0x710104f8c4: `suspend` the dialogue ducker (SoundMgr::_80 ducker 0x10).
    void sub_710104F8C4(bool suspend);
    // 0x710104f8e0: starts the ducker 0xf unless ducking is not allowed (bit 2 of `_2a0`).
    void sub_710104F8E0();
    // 0x710104f904: stops the ducker 0xf without suspending it.
    void sub_710104F904();
    // 0x710104f920: with `on`: stops the duckers 0x10 and 0xf and disables ducking (sets bit 2 of `_2a0`); else clears it.
    void sub_710104F920(bool on);
    // 0x710104fd38 (not done; copies a 12-byte value (4 bytes at +8 first) to `_278`; sead::Vector3f's operator=
    // copies element-wise).

    u8 _0[0x28];
    // The SLink user instance the sound triggers (SoundTrigger / SoundTriggerFadeAction) fall back to.
    /* 0x28 */ xlink2::UserInstanceSLink* _28;
    u8 _30[0x278 - 0x30];
    /* 0x278 */ sead::Vector3f _278;
    u8 _284[0x2a0 - 0x284];
    /* 0x2a0 */ sead::BitFlag8 _2a0;

private:
    static Unk_710104e5b4* sInstance;
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
    // Declared only (placeholder names; the callers are the Unk_SoundMgra8 list queries):
    bool sub_710104AFBC(int a);    // 0x710104afbc
    bool sub_710104AFC0(void* a);  // 0x710104afc0
    bool sub_710104B1D8(void* a);  // 0x710104b1d8
    bool sub_710104ADB8(int a);    // 0x710104adb8
    // 0x710104ac00 (declared only): the volume this instance gives `actor` (negative: none).
    f32 sub_710104AC00(ksys::act::Actor* actor);

    u8 _0[0x440];
    /* 0x440 */ f32 _440;
    u8 _444[0x490 - 0x444];
    /* 0x490 */ bool _490;
    /* 0x491 */ bool _491;
};

// Placeholder name (SoundMgr::_a8): the manager of the sound instances the AreaTagAction family hold at +0xa0.
class Unk_SoundMgra8 {
public:
    // 0x710104b554 (CSV nullsub_4415): releases `instance`.
    void sub_710104B554(Unk_SoundInstance* instance);
    // 0x710104b558 (132 B): the volume the sound instance list gives `actor` (the first non-negative value of the
    // instances' 0x710104ac00 query, else -1).
    f32 sub_710104B558(ksys::act::Actor* actor);
    // 0x710104b5dc: `idx` is below the count at +0x4a70.
    bool sub_710104B5DC(u32 idx) const;
    // 0x710104b68c: the first instance for which sub_710104B1D8(a) holds, passed on to sub_710104ADB8(b); false if none.
    bool sub_710104B68C(void* a, int b);
    // 0x710104b708 / 0x710104b76c: whether any instance answers sub_710104AFBC(a) / sub_710104AFC0(a).
    bool sub_710104B708(int a);
    bool sub_710104B76C(void* a);
    // 0x710104b7d0: increments (under the critical section) and returns the counter at +0x4a70.
    int sub_710104B7D0();

    u8 _0[8];
    /* 0x8 */ sead::CriticalSection mCS;
    /* 0x48 */ bool _48;
    /* 0x49 */ bool _49;
    u8 _4a[0x50 - 0x4a];
    /* 0x50 */ sead::PtrArray<Unk_SoundInstance> _50;
    u8 _60[0x4a70 - 0x60];
    /* 0x4a70 */ u16 _4a70;
};

// Placeholder (lane2 s46): the sound kind (0..5) the UI hands to SoundMgr (a 4-byte class: passed in a full register).
struct UiSoundKind {
    s32 value;
};

// FIXME: incomplete
struct SoundMgr {
    SEAD_SINGLETON_DISPOSER(SoundMgr)

    virtual ~SoundMgr();

    // 0x71011fc29c (lane2 request, s49; placeholder name): starts the ducker 0x23 of the DuckingMgr and sets bit 1 of
    // `_238`.
    void sub_71011FC29C();

public:
    // 0x71011fc288 (declared only; lane2 s46): called by ScreenFadeDemo's slot 101 (nothing happens while the byte at 0xf8 is set)
    void sub_71011FC288();
    // 0x71011fc0c0 / 0x71011fc17c (CSV Sound::__auto4 / __auto5; declared only): `kind` 0..5, `bit` the bit set in the byte at 0xf8
    void sub_71011FC0C0(UiSoundKind kind, s32 bit);
    void sub_71011FC17C(UiSoundKind kind, s32 bit);

    u8 _28[0x30 - 0x28];
    /* 0x30 */ Unk_SoundMgr30* _30;
    /* 0x38 */ Unk_SoundMgr38* _38;
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
