#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossBlowoffDamageSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossBlowoffDamageSelect, ksys::act::ai::Ai)
public:
    explicit PriestBossBlowoffDamageSelect(const InitArg& arg);
    ~PriestBossBlowoffDamageSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100510a94: grounded stagger without a damage manager, else knocked down on the ground / while floating
    void sub_7100510A94();

    int _38 = -1;
    int _3c = -1;
    sead::SafeString _40 = "none";
};
KSYS_CHECK_SIZE_NX150(PriestBossBlowoffDamageSelect, 0x50);

}  // namespace uking::ai
