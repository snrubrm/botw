#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AttackGrave : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AttackGrave, ksys::act::ai::Ai)
public:
    explicit AttackGrave(const InitArg& arg);
    ~AttackGrave() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    // 0x7100323f00 (not decompiled yet; declared for PriestBossAttackGrave::calc_)
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    Unk_71024506d8 _38;
    Unk_7102450588 _70;
};
KSYS_CHECK_SIZE_NX150(AttackGrave, 0xc0);

}  // namespace uking::ai
