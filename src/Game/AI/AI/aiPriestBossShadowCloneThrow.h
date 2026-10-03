#pragma once

#include <container/seadSafeArray.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PriestBossShadowCloneThrow : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossShadowCloneThrow, ksys::act::ai::Ai)
public:
    explicit PriestBossShadowCloneThrow(const InitArg& arg);
    ~PriestBossShadowCloneThrow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // Signatures of the virtuals other than m37 are not known yet (declared for the vtable layout).
    virtual void m34();
    virtual void m35();
    virtual bool m36();
    virtual bool m37();
    virtual void m38(sead::Vector3f* out, s32 which);
    virtual void m39();

protected:
    // static_param at offset 0x38
    const float* mShadowCloneOffsetY_s{};
    // static_param at offset 0x40
    const float* mShadowCloneRadius_s{};
    // static_param at offset 0x48
    const float* mShadowCloneAngleOffset_s{};
    // static_param at offset 0x50
    const float* mPrepareTimer_s{};
    // static_param at offset 0x58
    sead::SafeString mShadowCloneLefeBoneName_s{};
    // static_param at offset 0x68
    sead::SafeString mShadowCloneRightBoneName_s{};
    // aitree_variable at offset 0x78
    void* mPriestBossMetaAIUnit_a{};
    ksys::Timer _80;
    s32 _8c = 0;
    u32 _90 = 0;
    sead::SafeArray<s32, 8> _94;
    sead::SafeArray<Unk_7102415df0, 8> _b8;
    Unk_71023b1860 _378{mActor, 0x80000d5};
    Unk_71023b1860 _3b0{mActor, 0x80000d5};
    bool _3e8 = false;
    bool _3e9 = false;
    bool _3ea = false;
};
KSYS_CHECK_SIZE_NX150(PriestBossShadowCloneThrow, 0x3f0);

}  // namespace uking::ai
