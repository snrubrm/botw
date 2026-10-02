#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

class Unk_7102450fa8;

namespace uking::ai {

class PriestBossFormation : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossFormation, ksys::act::ai::Ai)
public:
    explicit PriestBossFormation(const InitArg& arg);
    ~PriestBossFormation() override;
    bool isChangeable() const override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34(Unk_7102450fa8* unit);
    virtual void m35(Unk_7102450fa8* unit);
    virtual bool m36();
    virtual bool m37();
    virtual void m38(sead::Vector3f* out);
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();

protected:
    // aitree_variable at offset 0x38
    void* mPriestBossMetaAIUnit_a{};
    s32 _40 = -1;
    s32 _44 = 0;
    Unk_7102413398 _48{mActor, 0x80000d3};
};
KSYS_CHECK_SIZE_NX150(PriestBossFormation, 0x80);

}  // namespace uking::ai
