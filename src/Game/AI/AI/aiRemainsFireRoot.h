#pragma once

#include "Game/AI/AI/aiRemainsRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsFireRoot : public RemainsRoot {
    SEAD_RTTI_OVERRIDE(RemainsFireRoot, RemainsRoot)
public:
    explicit RemainsFireRoot(const InitArg& arg);
    ~RemainsFireRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;
    void handlePendingChildChange_() override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m34() override;
    void m35(bool x) override;
    void m36() override;

protected:
    // static_param at offset 0x50
    sead::SafeString mTargetBoneName_s{};
    f32 _60;
    u32 _64;
    f32 _68;
    s32 _6c = 0;
};
KSYS_CHECK_SIZE_NX150(RemainsFireRoot, 0x70);

}  // namespace uking::ai
