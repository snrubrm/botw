#pragma once

#include "Game/AI/AI/aiEnemyCalledAppear.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinCallSelect : public EnemyCalledAppear {
    SEAD_RTTI_OVERRIDE(AssassinCallSelect, EnemyCalledAppear)
public:
    explicit AssassinCallSelect(const InitArg& arg);
    ~AssassinCallSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m34() override;
    bool m35() override;

protected:
    // Inline-only in the original (name guess; shared by m34 and m35: the event-name temporaries sit above the caller's).
    bool isChangeDemoActive();

    // static_param at offset 0x38
    sead::SafeString mChangeDemoName_s{};
    // static_param at offset 0x48
    sead::SafeString mChangeDemoEPName_s{};
};

}  // namespace uking::ai
