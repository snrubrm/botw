#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include <container/seadPtrArray.h>
#include <container/seadOffsetList.h>
#include <container/seadObjArray.h>
#include <aal/aalHandle.h>
#include <thread/seadCriticalSection.h>
#include <container/seadBuffer.h>
#include <prim/seadEnum.h>
#include <aal/aalGroupLimiter.h>
#include <aal/aalListener.h>
#include <aal/aalListenerPoser.h>
#include <container/seadFreeList.h>
#include <aal/aalTimedFader.h>
#include <aal/aalAssetInfo.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/System/DebugMessage.h"

namespace aal {
class Shape;
class Emitter;
class SpeakerBalanceUnifier;
}

namespace xlink2 {
class HandleSLink;
class UserInstanceSLink;
}

namespace ksys::res {
class Handle;
}

namespace ksys::act {
class Actor;
class ActorCreator;
}

namespace uking::act {
class EnvSeEmitPoint;
class SoundProxy;
}

namespace ksys::snd {

f32 sub_710105E3A4();
const char* sub_710105E7B4(bool* flag);
void sub_710105E534(sead::PtrArray<aal::Group>* groups, aal::Group* excluded, aal::Group* root);
void sub_710105E5CC(sead::PtrArray<aal::Group>* groups,
                   const sead::PtrArray<aal::Group>* excluded, aal::Group* root);
void sub_710105E614(sead::PtrArray<aal::Group>* groups,
                   const sead::PtrArray<aal::Group>* excluded, aal::Group* group);
s32 sub_710105E75C(const aal::AssetInfo::LoopInfo* loop, s32 position, s32 offset);

struct Unk_SoundMgr30;

// Only the interface needed by the UI sound wrapper is recovered.
class UiSoundMgr {
public:
    UiSoundMgr();
    virtual ~UiSoundMgr();
    void sub_710105D0E4(sead::Heap* heap);
    void sub_710105D0E8();
    // 0x710105d23c: requests its GetItemSound actor outside the TitleMenu map.
    void sub_710105D23C(sead::Heap* heap, act::ActorCreator* creator);
    void sub_710105D308();
    void sub_710105D9F8(aal::SoundSource* source);
    // 0x710105d5ac: stops the previous HeartUp sound and emits mc_HeartUp (`mode` picks the handle).
    bool sub_710105D5AC(const s32* mode);
    // 0x710105d7b0: mutes _38 and emits mc_ExtraHeartUp (mode 0 only).
    bool sub_710105D7B0(const s32* mode);
    void sub_710105D844(const s32* mode);
    // 0x710105d330: emits the SLink sound `label` through the user instance at +0x20; the handle is copied to
    // `handle` if given. Returns whether the emitted event is alive.
    bool playSound(const sead::SafeString& label, xlink2::HandleSLink* handle);
    // 0x710105d3bc (CSV uiSoundMgr::emitGetItemSound; declared only): emits the "get item" sound `label`.
    bool emitGetItemSound(const sead::SafeString& label);

    /* 0x08 */ act::BaseProcHandle _8;
    /* 0x18 */ act::Actor* _18 = nullptr;
    /* 0x20 */ xlink2::UserInstanceSLink* _20 = nullptr;
    /* 0x28 */ xlink2::HandleSLink _28;
    /* 0x38 */ xlink2::HandleSLink _38;
    /* 0x48 */ aal::Handle _48;
    /* 0x58 */ aal::TimedFader _58{1.0f, aal::FadeCurveType::Square, 1.0f};
    /* 0x80 */ u8 _80 = 0;
    /* 0x84 */ u32 _84 = 0;
    /* 0x88 */ DebugMessage _88;
    void* _118 = nullptr;
    void* _120 = nullptr;
};
KSYS_CHECK_SIZE_NX150(UiSoundMgr, 0x128);

// Placeholder name (SoundMgr::_38::_30). Holds the aal::SpeakerBalanceUnifier objects at +0x68 (count at +0x60,
// guarded by a CriticalSection at +0x20); shapes are registered with the one picked by a size threshold.
class SpeakerBalanceUnifierMgr {
public:
    // 0x7101027d4c: adds `shape` to the unifier chosen by `size` (3 thresholds).
    void sub_7101027D4C(f32 size, aal::Shape* shape);
    // 0x7101027e0c: removes `shape` from every unifier.
    void sub_7101027E0C(aal::Shape* shape);
    // 0x7101027e90 (declared only): emits the SLink sound for `type` (1 or 2) picked by `size` and
    // attaches `shape` to its sound source.
    xlink2::HandleSLink sub_7101027E90(f32 size, int type, aal::Shape* shape);
    void sub_7101027CE8();
    static sead::SafeString sUnk_7102610618[4];
    static sead::SafeString sUnk_7102610658[4];

    // 0x7102501140: the sizes that separate the four unifiers.
    static f32 sSizeThresholds[3];

    u8 _0[8];
    // 0x710102780c obtains this actor through the handle; 0x7101027ce8 clears both.
    act::BaseProcHandle mHandle;
    act::Actor* mActor;
    /* 0x20 */ sead::CriticalSection mCS;
    /* 0x60 */ sead::PtrArray<aal::SpeakerBalanceUnifier> mUnifiers;
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

// Placeholder name (SoundMgr::_38::_20; ctor 0x7101029864, init 0x7101029958): the registry of the
// environment sound emit points (uking::act::EnvSeEmitPoint actors). Its two lists (0x18 bytes per entry, guarded by
// the CriticalSection at +0x38) are indexed by the `_83c` kind of the emit point (0 or 1).
class Unk_SoundMgr38_20 {
public:
    Unk_SoundMgr38_20();
    virtual ~Unk_SoundMgr38_20();
    void sub_7101029958(sead::Heap* heap);
    void sub_7101029970();
    void sub_71010299AC();
    void sub_7101029AA0();
    void sub_7101029B94();
    void sub_7101029BA0();
    void sub_7101029BA8();
    // 0x7101029bb0 (declared only; lane1 s47): registers `point` in the list of its kind (the kind is picked by the
    // actor's name); false if the name matches no kind.
    bool sub_7101029BB0(uking::act::EnvSeEmitPoint* point);
    // 0x7101029c98 (declared only; lane1 s47): removes `point` from the list of its kind.
    void sub_7101029C98(uking::act::EnvSeEmitPoint* point);

    /* 0x08 */ sead::OffsetList<uking::act::EnvSeEmitPoint> _8[2];
    /* 0x38 */ sead::CriticalSection mCS;
    bool _78 = false;
    bool _79 = false;
    bool _7a[2] = {};
    f32 _7c = 400.0f;
    f32 _80 = 600.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgr38_20, 0x88);

// Placeholder name (SoundMgr::_38::_48; lane1 s47): a registry of actors (list at +0x1aa8, guarded by the CriticalSection
// at +0x1d58) used by the GrudgeEyeball AI.
class Unk_SoundMgr38_48 {
public:
    // 0x7101035b50 (declared only): adds `actor` to the list (if it has room).
    void sub_7101035B50(ksys::act::Actor* actor);
    // 0x7101035c50 (declared only): removes the entry of the actor with id `id` / hash id `hash_id`.
    void sub_7101035C50(u32 id, u32 hash_id);
};

// Placeholder name (SoundMgr::_38).
struct Unk_SoundMgr38 {
    // 0x710102c104: returns `_28`.
    Unk_SoundMgr38_28* sub_710102C104() const;
    // 0x710102c10c: unavailable while the manager's mode byte is set.
    Unk_SoundMgr38_28* sub_710102C10C() const;
    // 0x710102b11c: forwards to the cleanup operation.
    void sub_710102B11C();
    void sub_710102AF84();

    u8 _0[0x20];
    /* 0x20 */ Unk_SoundMgr38_20* _20;
    /* 0x28 */ Unk_SoundMgr38_28* _28;
    /* 0x30 */ SpeakerBalanceUnifierMgr* _30;
    u8 _38[0x48 - 0x38];
    /* 0x48 */ Unk_SoundMgr38_48* _48;
    u8 _50[0x70 - 0x50];
    // Read by 0x710102c10c and the cleanup operation 0x710102af84.
    /* 0x70 */ bool _70;
};

// Name from the CSV (snd::DuckingMgr::startDucking 0x7101042078; ctor 0x710103e404, init 0x710103e58c).
// SoundMgr::_80. A buffer (size at +8, data at +0x10) of 50 duckers (0xd0 bytes each: aal::GroupDucker at +0x68,
// `_c0` / `_c8` state) indexed by a SEAD_ENUM of ducker names (the enum's text function is 0x7101042f30);
// entries 0x30 / 0x31 are the "custom" duckers used by Unk_710103b704.
// TODO: incomplete.
class DuckingMgr {
public:
    // The names are the strings at 0x7101e26516 (the SEAD_ENUM text; text function 0x7101042f30).
    // clang-format off
    // (the original text has a space before each comma: `text_all` is 737 bytes)
    SEAD_ENUM(DuckerType,
              cSlowBgm , cSlowSe , cFocus , cSquat , cPauseIngame , cPauseEvent , cBattleEnv , cGrudgeEnv ,
              cGrudgeEnvBoost , cBloody , cBossDialogHero , cBossDialogZelda , cFieldRemainsFire ,
              cFieldRemainsOrGanon , cRaceAudience , cTalk , cDialog , cScreenFadeS , cScreenFadeM ,
              cScreenFadeL , cScreenFadeLogo , cScreenFadeForce , cHomeMenu , cEvtBgmReduce , cEvtBgmMute ,
              cEvtEnvReduce , cEvtWorldMute , cTmlnWorldMute , cTmlnThruShake , cTmlnThruShakeWeather ,
              cTmlnMovie , cTmlnLoading , cTitleMute , cEventSkip , cEventSkipBeam , cPlayTimeOver ,
              cExplosion , cImpact , cLocationUI , cWaveShockL , cParasailOpen , cDive , cHorseJump ,
              cFairyRecover , cLightningNear , cExplosionRemote , cEnemyWeaponSwing , cEnemyImpact ,
              cCustomEvt , cCustomEvt2)
    // clang-format on

    struct Ducker {
        virtual void v0();
        virtual void v1();
        // 0x7101042f18
        virtual bool isActive() const;

        u8 _8[0x60];
        /* 0x68 */ aal::GroupDucker mDucker;
        /* 0xb0 */ void* _b0;
        u8 _b8[8];
        /* 0xc0 */ f32 _c0;
        u8 _c4[4];
        /* 0xc8 */ u8 _c8;  // bit 0: active
    };

    // 0x7101042078: starts the ducker called `type` (looked up by name); null when there is none.
    Ducker* startDucking(const sead::SafeString& type);
    // 0x7101042db4: stops the ducker called `type` (`suspend`: also suspends its aal::GroupDucker).
    void sub_7101042DB4(const sead::SafeString& type, bool suspend);
    // 0x7101042024: starts the ducker `type`.
    Ducker* sub_7101042024(DuckerType type);
    // 0x7101042d6c: clears bit 0 of the ducker `type`'s flags byte (+0xc8) and suspends its aal::GroupDucker if
    // `suspend`.
    void sub_7101042D6C(DuckerType type, bool suspend);

    void* _0;  // vtable
    /* 0x08 */ sead::Buffer<Ducker> mDuckers;
};

// Actual sound-owned B8 allocation in 0x710105590C and embedded stream-path callback.
class Unk_710105fe78 {
public:
    Unk_710105fe78();
    virtual ~Unk_710105fe78();
    // Lookup 0x7101060C04 proves the hash/handle pair and sixteen-byte stride.
    struct Entry {
        u32 mHash;
        res::Handle* mHandle;
    };
    static_assert(sizeof(Entry) == 0x10);
    class Callback : public aal::Unk_7100BA1AEC {
    public:
        bool sub_7100BA1AEC(sead::BufferedSafeStringBase<char>* path, aal::AssetInfo* info) override;
        sead::FixedSafeString<128> mString;
    };
    static_assert(sizeof(Callback) == 0xa0);
    /* 0x08 */ sead::Buffer<Entry>* _8 = nullptr;
    /* 0x10 */ s32 _10 = 0;
    u8 _14[4];
    /* 0x18 */ Callback mCallback;
};
KSYS_CHECK_SIZE_NX150(Unk_710105fe78, 0xb8);

// Placeholder name (SoundMgr::_48), used by the UI message screens.
class Unk_SoundMgr48 {
public:
    Unk_SoundMgr48();
    virtual ~Unk_SoundMgr48();
    void sub_710105590C(sead::Heap* heap);
    void sub_7101055B44();
    f32 sub_7101055E3C() const;

    /* 0x08 */ Unk_710105fe78* _8 = nullptr;
    /* 0x10 */ aal::Emitter* _10 = nullptr;
    /* 0x18 */ aal::Handle _18;
    /* 0x28 */ aal::Handle _28;
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgr48, 0x38);

// Root subobject at 0x5e0 of Unk_710103b704, constructed at 0x710105abc0.
// Its original vtable has only the two destructor slots.
class Unk_710105abc0 {
public:
    explicit Unk_710105abc0(sead::Heap* heap);
    virtual ~Unk_710105abc0();
    bool sub_710105B090();

    aal::Emitter* _8;
    aal::Handle _10;
    aal::SimpleTimedFader _20{1.0f};
    sead::BitFlag8 _38;
    // 0x710105abc0 clears this byte alongside _38.
    bool _39;
    u8 _3a[2];
    f32 _3c;
};
KSYS_CHECK_SIZE_NX150(Unk_710105abc0, 0x40);

// Placeholder (lane2 s46): the sound kind (0..5) the UI hands to SoundMgr (a 4-byte class: passed in a full register).
struct UiSoundKind {
    s32 value;
};

// Placeholder name (ctor 0x710103b704; SoundMgr::_98): starts / stops the two custom duckers (indices 0x30 / 0x31
// of the DuckingMgr). Used by CustomDuckingStartAction / CustomDuckingEndAction.
class Unk_710103b704 {
public:
    explicit Unk_710103b704(sead::Heap* heap);
    virtual ~Unk_710103b704();
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
    // 0x710103d0d8 / 0x710103d324 (declared only): the UI sound kind handed over by SoundMgr (see sub_71011FC0C0).
    void sub_710103D0D8(UiSoundKind kind);
    void sub_710103D324(UiSoundKind kind);
    // 0x710103d418: starts the ducker 0x1f.
    void sub_710103D418();

    // 0x710103bb00 (declared only; CSV unnamed): applies the scene sound controls (bgm type, se type) now.
    void sub_710103BB00(int bgm_type, int se_type);
    // 0x710103cfe8: stores the two types in _5d0 / _5d4 for later (used while _5cc is set).
    void sub_710103CFE8(int bgm_type, int se_type);

    u8 _8[0x5cc - 8];
    /* 0x5cc */ bool _5cc;
    u8 _5cd[0x5d0 - 0x5cd];
    /* 0x5d0 */ int _5d0;
    /* 0x5d4 */ int _5d4;
    // Set by SceneSoundSetEndProcAction ("SkipAll"); name unknown.
    /* 0x5d8 */ bool _5d8;
    u8 _5d9[0x5e0 - 0x5d9];
    /* 0x5e0 */ Unk_710105abc0 _5e0;
    /* 0x620 */ u32 _620;
};
KSYS_CHECK_SIZE_NX150(Unk_710103b704, 0x628);

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
    void sub_710104FD4C();
    void sub_710104FD38(const xlink2::HandleSLink& handle);
    void sub_710104EA7C();

    u8 _0[0x28];
    // The SLink user instance the sound triggers (SoundTrigger / SoundTriggerFadeAction) fall back to.
    /* 0x28 */ xlink2::UserInstanceSLink* _28;
    u8 _30[0x250 - 0x30];
    /* 0x250 */ u32 _250;
    u8 _254[4];
    /* 0x258 */ aal::SimpleTimedFader _258;
    /* 0x270 */ f32 _270;
    u8 _274[4];
    /* 0x278 */ xlink2::HandleSLink _278;
    u8 _288[0x2a0 - 0x288];
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
// in SoundMgr's init (CSV Sound::init) and stored in SoundMgr::_58. It owns an aal::Listener and the aal::ListenerPoser
// that positions it (named "snd::ListenerPoser"; the listener is the default listener).
// TODO: incomplete.
class ListenerPoser {
public:
    // 0x71010549d8
    ListenerPoser();
    // 0x7101054a88 (D1) / 0x7101054adc (D0)
    virtual ~ListenerPoser();

    // 0x7101055538 (CSV unnamed): if `_70` is clear, sets it and stores `value` in `_74`.
    void sub_7101055538(s32 value);
    // 0x7101054b30 (declaration only): creates the poser (in `heap`) and the default listener.
    void init(sead::Heap* heap);

    /* 0x08 */ aal::Listener* mListener = nullptr;
    /* 0x10 */ aal::ListenerPoser* mPoser = nullptr;
    /* 0x18 */ f32 _18 = 22.5f;
    /* 0x1c */ f32 _1c = 45.0f;
    /* 0x20 */ f32 _20 = 1.0f;
    /* 0x24 */ f32 _24 = 5.0f;
    /* 0x28 */ f32 _28 = 0.25f;
    /* 0x2c */ f32 _2c = 1.0f;
    /* 0x30 */ u64 _30[4] = {};
    u8 _50[8];
    /* 0x58 */ aal::SimpleTimedFader _58{0.0f};
    /* 0x70 */ bool _70 = true;
    /* 0x74 */ s32 _74 = 0;
    /* 0x78 */ s32 _78 = 0;  // mode: 0 Normal, 5 Gyro, 6 EvtBack (ListenerSetModeAction)
    /* 0x7c */ u32 _7c = 0;
    // set to 1 / 0 by uking::action::CameraAction enter_ / leave_
    /* 0x80 */ u32 _80 = 0;
    /* 0x84 */ u16 _84 = 0;
    /* 0x88 */ u32 _88 = 1;
    /* 0x90 */ aal::SimpleTimedFader _90{1.0f};
    /* 0xa8 */ aal::SimpleTimedFader _a8{0.0f};
    /* 0xc0 */ f32 _c0 = 1.0f;
    /* 0xc4 */ u32 _c4 = 0;
    /* 0xc8 */ u32 _c8 = 0;
    /* 0xcc */ u32 _cc = 0;
    /* 0xd0 */ u32 _d0 = 0;
    /* 0xd4 */ u32 _d4 = 0;
    /* 0xd8 */ u32 _d8 = 0;
    u8 _dc[4];
};
static_assert(sizeof(ListenerPoser) == 0xe0);

// Placeholder name (SoundMgr::_60): `_28` is the address of the xlink2 SLink resource list the UI screens
// (uking::ui::ScreenBase::getSlink2ResourceList_) hand to their sound link users.
struct Unk_SoundMgr60 {
    u8 _0[0x28];
    u8 mSlinkResources[8];
};

// Placeholder name: the sound instances the AreaTagAction family (Shielding / Occlusion / Reverb) get from
// SoundMgr::_a8.
struct Unk_SoundInstance {
    explicit Unk_SoundInstance(s32 id);
    ~Unk_SoundInstance();
    bool sub_710104ACB4();
    void sub_710104ABE8();
    // Placeholder names; the callers are the Unk_SoundMgra8 list queries:
    bool sub_710104AFBC(int a);    // 0x710104afbc
    bool sub_710104AFC0(act::Actor* a);  // 0x710104afc0
    bool sub_710104B10C(act::Actor* a);
    bool sub_710104B1D8(act::Actor* a);  // 0x710104b1d8
    bool sub_710104ADB8(int a);
    bool sub_710104ACF8(map::Object* object);
    bool sub_710104AE6C(int id);
    // 0x710104ac00: the volume this instance gives `actor` (negative: none).
    f32 sub_710104AC00(ksys::act::Actor* actor);

    // 0x710104A9A0 initializes two pools; 0x710104AC00 compares map hashes and actor IDs.
    sead::FixedObjArray<u32, 32> _0;
    sead::FixedObjArray<u32, 32> _220;
    /* 0x440 */ f32 _440 = 0.0f;
    /* 0x448 */ sead::CriticalSection mCS;
    /* 0x488 */ s32 _488 = 0;
    /* 0x48c */ s32 _48c;
    /* 0x490 */ bool _490 = false;
    /* 0x491 */ bool _491 = false;
    /* 0x494 */ s32 _494 = 0;
};
static_assert(sizeof(Unk_SoundInstance) == 0x498);

// Placeholder name (SoundMgr::_a8): the manager of the sound instances the AreaTagAction family hold at +0xa0.
class Unk_SoundMgra8 {
public:
    Unk_SoundMgra8();
    virtual ~Unk_SoundMgra8();
    void sub_710104B404(sead::Heap* heap);
    void sub_710104B408();
    Unk_SoundInstance* sub_710104B480(s32 id);
    // 0x710104b554 (CSV nullsub_4415): releases `instance`.
    void sub_710104B554(Unk_SoundInstance* instance);
    // 0x710104b558 (132 B): the volume the sound instance list gives `actor` (the first non-negative value of the
    // instances' 0x710104ac00 query, else -1).
    f32 sub_710104B558(ksys::act::Actor* actor);
    // 0x710104b5dc: `idx` is below the count at +0x4a70.
    bool sub_710104B5DC(u32 idx) const;
    // 0x710104b68c: the first instance for which sub_710104B1D8(a) holds, passed on to sub_710104ADB8(b); false if none.
    bool sub_710104B5F0(act::Actor* actor);
    bool sub_710104B68C(act::Actor* a, int b);
    // 0x710104b708 / 0x710104b76c: whether any instance answers sub_710104AFBC(a) / sub_710104AFC0(a).
    bool sub_710104B708(int a);
    bool sub_710104B76C(act::Actor* a);
    // 0x710104b7d0: increments (under the critical section) and returns the counter at +0x4a70.
    int sub_710104B7D0();

    /* 0x8 */ sead::CriticalSection mCS;
    /* 0x48 */ bool _48;
    /* 0x49 */ bool _49;
    u8 _4a[0x50 - 0x4a];
    /* 0x50 */ sead::PtrArray<Unk_SoundInstance> _50;
    /* 0x60 */ sead::FreeList mFreeList;
    /* 0x70 */ u8 mPoolStorage[16 * sizeof(Unk_SoundInstance)];
    /* 0x49f0 */ Unk_SoundInstance* mPointerStorage[16];
    /* 0x4a70 */ u16 _4a70;
    /* 0x4a72 */ u16 _4a72;
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgra8, 0x4a78);

// 2026-10-07: constructor 0x710105a6f0 and node-offset setup 0x710105a718 identify
// the SoundMgr +0xa0 proxy list manager. Bodies remain owned by the sound subsystem.
class Unk_710105a6f0 {
public:
    Unk_710105a6f0();
    ~Unk_710105a6f0();
    void sub_710105A718();
    void sub_710105A734(uking::act::SoundProxy* proxy);
    void sub_710105A7B4(uking::act::SoundProxy* proxy);
    uking::act::SoundProxy* sub_710105A830(map::Object* object);

    bool _0 = false;
    sead::OffsetList<uking::act::SoundProxy> mProxies;
    sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(Unk_710105a6f0, 0x60);

// FIXME: incomplete
struct SoundMgr {
    SEAD_SINGLETON_DISPOSER(SoundMgr)

    virtual ~SoundMgr();

    f32 sub_71011FC31C();
    f32 sub_71011FC310();
    bool sub_71011FC2DC();

public:
    // 0x71011fc29c (lane2 request, s49; placeholder name): starts the ducker 0x23 of the DuckingMgr and sets bit 1 of
    // `_238`. (Public: called by uking::ui::sub_7100A9F8B0.)
    void sub_71011FC29C();
    // 0x71011fbecc: cleanup forwarding to the spatial and UI sound managers.
    void sub_71011FBECC();
    aal::Listener* sub_71011FC2D0();
    f32 sub_71011FC338();
    f32 sub_71011FC340();
    // 0x71011fc288 (declared only; lane2 s46): called by ScreenFadeDemo's slot 101 (nothing happens while the byte at 0xf8 is set)
    void sub_71011FC288();
    // 0x71011fc0c0 / 0x71011fc17c (CSV Sound::__auto4 / __auto5; declared only): `kind` 0..5, `bit` the bit set in the byte at 0xf8
    void sub_71011FC0C0(UiSoundKind kind, s32 bit);
    void sub_71011FC17C(UiSoundKind kind, s32 bit);
    // 0x71011fb5ac (CSV Sound::calc2; declaration only): called by MCMgr::invoked4.
    void sub_71011FB5AC();

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
    /* 0xa0 */ Unk_710105a6f0* _a0;
    /* 0xa8 */ Unk_SoundMgra8* _a8;
    u8 _b0[0xd8 - 0xb0];
    // Created by 0x71011fab7c and queried through the Heap virtual interface.
    sead::Heap* mSLinkUserCreateHeap;
    u8 _e0[0xec - 0xe0];
    u32 _ec;
    u8 _f0[8];
    sead::BitFlag8 _f8;
    u8 _f9[0x238 - 0xf9];
    u8 _238;
    u8 _239[0x270 - 0x239];
    AudioChannelType mAudioChannelType;
};

}  // namespace ksys::snd
