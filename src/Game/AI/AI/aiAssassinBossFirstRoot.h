#pragma once

#include "Game/AI/AI/aiAssassinBossRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// vtable 0x71023d7798: damage callback without RTTI of its own (functions in the
// AssassinBossFirstRoot TU). Placeholder name.
class Unk_71023d7798 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    bool _24 = false;
    bool _25 = false;
};

class AssassinBossFirstRoot : public AssassinBossRootBase {
    SEAD_RTTI_OVERRIDE(AssassinBossFirstRoot, AssassinBossRootBase)
public:
    explicit AssassinBossFirstRoot(const InitArg& arg);
    ~AssassinBossFirstRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m35() override;
    bool m45() override;
    void m46() override;

protected:
    Unk_71023d7798 _2b0;
    bool _2d8 = false;
};
KSYS_CHECK_SIZE_NX150(AssassinBossFirstRoot, 0x2e0);

}  // namespace uking::ai
