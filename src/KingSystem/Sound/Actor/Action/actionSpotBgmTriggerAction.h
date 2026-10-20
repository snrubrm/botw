#pragma once

#include <aal/aalShape.h>
#include <aal/aalTimedFader.h>
#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Sound/sndBgmMgr.h"

// Placeholder for the small primary base of Unk_SpotBgmInstance: a virtual destructor and the two
// virtuals the instance overrides (vtable 0x7102500cb0, no RTTI). The second base
// Unk_71024fc7f8 sits at +8 with its own vtable (0x7102500cf0, offset to top -8).
class Unk_SpotBgmInstanceBase {
public:
    virtual ~Unk_SpotBgmInstanceBase();
    virtual void sub_7101024358() = 0;
    virtual void sub_71010246CC() = 0;
};

// The spot BGM instance a SpotBgmTriggerAction creates in init_ (size 0x3c0).
class Unk_SpotBgmInstance : public Unk_SpotBgmInstanceBase, public ksys::snd::Unk_71024fc7f8 {
public:
    // The two sub-tracks of a spot BGM (the faders at 0x2d8 and the distance tables). The
    // original loops over this enum with a SEAD_ENUM iterator in sub_7101024808.
    SEAD_ENUM(SubTrack, _0, _1)
    // 0x7101023050
    explicit Unk_SpotBgmInstance(bool a);
    ~Unk_SpotBgmInstance() override;
    // 0x710102413c / 0x710102418c (declared only): fade in / fade out (Unk_710260f1a8::m12 / m13).
    void sub_710102413C(f32 fade_sec);
    void sub_710102418C(f32 fade_sec);
    void sub_7101023EC8();
    void sub_71010239A8();
    void sub_7101023F68(f32 volume);
    void sub_71010241D0(bool allow, bool fade_in);
    // 0x71010242c8 (placeholder name): if flag 4 is set, clears flags 0xc and stores 1.0 in `_260` when flag
    // 0x8000 is set (0.0 otherwise).
    void sub_71010242C8();
    // 0x71010242f0: SpotBgmTriggerAction::init_ calls it for a box area with
    // IsStopWithoutReductionY.
    void sub_71010242F0();
    // 0x7101024280: stops the handle (with the info's fade out time) when it is playing, then clears
    // the started / stopping flags.
    void sub_7101024280();
    // 0x71010233cc (declared only; 1500 B): `name` is the sound name parameter; `a3` is 1 for a box area, 0 otherwise.
    void sub_71010233CC(sead::Heap* heap, const sead::SafeString* name, u64 a3, ksys::act::Actor* actor);

    // The class's own virtuals (primary vtable slots 2 / 3).
    void sub_7101024358() override;
    void sub_71010246CC() override;
    void hm14() override;
    void hm15() override;

    // Set to an invalid value by the constructor and destructor (0xbac435ef / 0xca110000).
    /* 0x188 */ u32 _188 = 0xca11bac4;
    u32 _18c;
    /* 0x190 */ ksys::snd::SpotBgmInfo* mInfo = nullptr;
    /* 0x198 */ sead::FixedSafeString<128> mName;
    /* 0x230 */ aal::Shape* mShape = nullptr;
    /* 0x238 */ s32 _238 = 2;
    /* 0x23c */ u32 _23c = 0;
    /* 0x240 */ u32 _240 = 0;
    /* 0x244 */ u32 _244 = 0;
    /* 0x248 */ f32 _248 = 0.0f;
    /* 0x24c */ f32 _24c = 0.0f;
    /* 0x250 */ f32 _250 = 0.0f;
    /* 0x254 */ f32 _254 = 0.0f;
    /* 0x258 */ f32 _258 = 0.0f;
    /* 0x25c */ f32 _25c = 0.0f;
    /* 0x260 */ f32 _260 = 0.0f;
    /* 0x264 */ f32 _264 = 9999.0f;
    /* 0x268 */ f32 _268 = 0.0f;
    u32 _26c = 0;
    /* 0x270 */ void* _270 = nullptr;
    /* 0x278 */ aal::SimpleTimedFader _278{1.0f};
    // The playing entry the sub-track volumes (entry volume slots 1 / 2) are written to.
    /* 0x290 */ ksys::snd::Unk_710260f248Entry* mEntry = nullptr;
    /* 0x298 */ s32 _298 = 0;
    u32 _29c = 0;
    /* 0x2a0 */ aal::SimpleTimedFader _2a0{0.0f};
    /* 0x2b8 */ aal::SimpleTimedFader _2b8{0.0f};
    /* 0x2d0 */ u32 _2d0 = 0;
    /* 0x2d4 */ s32 _2d4 = -1;
    /* 0x2d8 */ sead::SafeArray<aal::SimpleTimedFader, 2> mSubTrackFaders{
        {aal::SimpleTimedFader(1.0f), aal::SimpleTimedFader(1.0f)}};
    /* 0x308 */ s32 _308 = 0;
    u32 _30c = 0;
    /* 0x310 */ aal::TimedFader _310{1.0f, aal::FadeCurveType(1), 1.0f};
    /* 0x338 */ s32 _338 = 2;
    u32 _33c = 0;
    /* 0x340 */ aal::TimedFader _340{1.0f, aal::FadeCurveType(0), 1.0f};
    /* 0x368 */ u32 _368 = 0;  // MusicianSpotBgmTriggerAction::enter_ sets bit 0x400
    /* 0x36c */ bool _36c = true;
    u8 _36d[3]{};
    u8 _370[5]{};
    u8 _375[8]{};
    u8 _37d[3]{};
    /* 0x380 */ f32 _380 = 1.0f;
    u32 _384 = 0;
    /* 0x388 */ sead::FixedSafeString<32> mCategory;
};
KSYS_CHECK_SIZE_NX150(Unk_SpotBgmInstance, 0x3c0);

void setSubTrack0DistanceMaybe(f32 distance);
void setSubTrack1DistanceMaybe(f32 distance);
void clearSubTrackDistancesMaybe();

// 0x7101024374 (declared only; 824 B): re-emits the spot BGM handle when it has no entry.
void sub_7101024374(Unk_SpotBgmInstance* instance);
// 0x7101024808 (declared only): applies the instance's filter / volume state.
void sub_7101024808(Unk_SpotBgmInstance* instance);

// The spot BGM manager the actions talk to is ksys::snd::Unk_710260f198 (ksys::snd::sub_7100FFD7CC).

namespace ksys::act {
class Actor;
}

namespace ksys::snd {

class SpotBgmTriggerAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SpotBgmTriggerAction, ksys::act::ai::Action)
public:
    explicit SpotBgmTriggerAction(const InitArg& arg);
    ~SpotBgmTriggerAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mSound_d{};
    // map_unit_param at offset 0x30
    const bool* mIsStopWithoutReductionY_m{};
    // map_unit_param at offset 0x38
    sead::SafeString mSound_m{};
    Unk_SpotBgmInstance* _48 = nullptr;
};
KSYS_CHECK_SIZE_NX150(SpotBgmTriggerAction, 0x50);

}  // namespace ksys::snd
