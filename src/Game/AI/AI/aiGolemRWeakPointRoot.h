#pragma once

#include "Game/AI/AI/aiGolemWeakPointRoot.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemRWeakPointRoot : public GolemWeakPointRoot {
    SEAD_RTTI_OVERRIDE(GolemRWeakPointRoot, GolemWeakPointRoot)
public:
    explicit GolemRWeakPointRoot(const InitArg& arg);
    ~GolemRWeakPointRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    bool handleMessage_(const ksys::Message& message) override;
    void leave_() override;
    void loadParams_() override;

    bool m36() override;
    void m37() override;
    void m38(s32 idx, const sead::Matrix34f& mtx) override;

protected:
    Unk_71023f57c8 _220;
};

}  // namespace uking::ai
