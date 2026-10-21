#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "Game/Actor/AI/aiPriestBossMeta.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PriestBossPhase : public PriestBossMeta {
    SEAD_RTTI_OVERRIDE(PriestBossPhase, PriestBossMeta)
public:
    // The phase index (Unk_7102450fa8::Phase): enter_ stores m38() into the unit's `_3c` and uses it
    // as the bit index of `_60`.
    using Flag = Unk_7102450fa8::Phase;

    explicit PriestBossPhase(const InitArg& arg);
    ~PriestBossPhase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34() {}
    virtual void m35() {}
    virtual bool m36();
    virtual bool m37(f32* x) { return false; }
    virtual Flag m38() { return Flag::_4; }
    virtual void m39() {}
    virtual void m40();

protected:
    void sub_7100528B5C();
    // 0x7100528f10 (placeholder name): marks the phase as started once m36 holds (after m35), or sets flag 2 while
    // the phase's flags are _0 and _1 without _2
    void sub_7100528F10();
    // 0x71005289c4 (placeholder name): whether one of the Demo644_0 .. Demo644_3 events is the active one
    bool sub_71005289C4();
    // 0x7100528854 (placeholder name): calls the event `name` / `entry`; in phases 0 and 1 only after the player
    // has stood on level ground (|y| <= 0.25) for the _70 timer
    bool sub_7100528854(const sead::SafeString& name, const sead::SafeString& entry);
    bool sub_7100528C48();
    // static_param at offset 0x50
    const float* mPercentLifeTransition_s{};
    // static_param at offset 0x58
    const float* mPercentLifePrevious_s{};
    sead::BitFlag16 _60;
    ksys::Timer _64{30.0f, 30.0f};
    ksys::Timer _70{5.0f, 5.0f};
};
KSYS_CHECK_SIZE_NX150(PriestBossPhase, 0x80);

}  // namespace uking::ai
