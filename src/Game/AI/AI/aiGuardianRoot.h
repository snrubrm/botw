#pragma once

#include "Game/AI/AI/aiGuardianAI.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianRoot : public GuardianAI {
    SEAD_RTTI_OVERRIDE(GuardianRoot, GuardianAI)
public:
    explicit GuardianRoot(const InitArg& arg);
    ~GuardianRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void loadParams_() override;
    // 0x710042b8b4 (placeholder name)
    void changeToReactToSight();
    // 0x710042b7c4 (placeholder name)
    void changeToReactToSound();

protected:
    // map_unit_param at offset 0x38
    const bool* mIsSuspended_m{};
    // aitree_variable at offset 0x40
    sead::Vector3f* mForceSetDropPos_a{};
    u32 _48 = 0;
    Unk_71023f9b08 _50;
};

}  // namespace uking::ai
