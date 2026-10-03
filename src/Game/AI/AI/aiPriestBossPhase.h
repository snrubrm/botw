#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "Game/AI/AI/aiPriestBossMeta.h"
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
