#pragma once

#include <aal/aalTimedFader.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Sound/sndBgmMgr.h"

// The spot BGM instance a SpotBgmTriggerAction creates in init_ (size 0x3c0; its deleting destructor is vtable slot 1).
class Unk_SpotBgmInstance {
public:
    // 0x7101023050 (declared only; 532 B)
    explicit Unk_SpotBgmInstance(bool a);
    // 0x710102413c / 0x710102418c (declared only): fade in / fade out (Unk_710260f1a8::m12 / m13).
    void sub_710102413C(f32 fade_sec);
    void sub_710102418C(f32 fade_sec);
    // 0x71010242c8 (placeholder name): if flag 4 is set, clears flags 0xc and stores 1.0 in `_260` when flag
    // 0x8000 is set (0.0 otherwise).
    void sub_71010242C8();
    // 0x71010242f0: SpotBgmTriggerAction::init_ calls it for a box area with
    // IsStopWithoutReductionY.
    void sub_71010242F0();
    virtual ~Unk_SpotBgmInstance();
    // 0x71010233cc (declared only; 1500 B): `name` is the sound name parameter; `a3` is 1 for a box area, 0 otherwise.
    void sub_71010233CC(sead::Heap* heap, const sead::SafeString* name, u64 a3, ksys::act::Actor* actor);

    // A base in the original (its vtable 0x7102500cb0 has the handle's slots at +0x40, plus Unk_71024fc7f8's three);
    // declared as a member until the instance is decompiled.
    Unk_SpotBgmHandle _8;
    u8 _188[0x260 - 0x188];
    /* 0x260 */ f32 _260;
    u8 _264[0x308 - 0x264];
    /* 0x308 */ s32 _308;
    u8 _30c[4];
    /* 0x310 */ aal::TimedFader _310;
    u8 _338[0x368 - 0x338];
    /* 0x368 */ u32 _368;  // MusicianSpotBgmTriggerAction::enter_ sets bit 0x400
    u8 _36c[0x3c0 - 0x36c];
};

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
