#pragma once

#include "Game/AI/AI/aiGolemRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class MiniGolemRoot : public GolemRootBase {
    SEAD_RTTI_OVERRIDE(MiniGolemRoot, GolemRootBase)
public:
    explicit MiniGolemRoot(const InitArg& arg);
    ~MiniGolemRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m36() override;
    void m37() override;
    void m38() override;
    void m40() override;
    bool m44() override;

protected:
    // aitree_variable at offset 0x310
    bool* mIsAllowReactionLift_a{};
    // static_param at offset 0x318
    const int* mLiftDeadTime_s{};
    bool _320 = false;
    ksys::Timer _324;
};
KSYS_CHECK_SIZE_NX150(MiniGolemRoot, 0x330);

}  // namespace uking::ai
