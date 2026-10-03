#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/aiUnk_7102450058.h"
#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddCarriedBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AddCarriedBase, ksys::act::ai::Ai)
public:
    explicit AddCarriedBase(const InitArg& arg);
    ~AddCarriedBase() override;

    bool updateForPreDelete() override;
    bool hasUpdateForPreDeleteCb() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x71002f786c: whether the actor is further than FailDistance from its main body's position.
    virtual bool m34();
    virtual ksys::act::ActorBind* m35() = 0;
    virtual void m36() = 0;
    virtual void m37(const sead::Matrix34f& mtx) = 0;
    virtual bool m38();

protected:
    // static_param at offset 0x38
    const float* mFailDistance_s{};
    // static_param at offset 0x40
    const bool* mIsRecoverCharCtrlAxis_s{};
    // static_param at offset 0x48
    const bool* mIsUseConstraint_s{};
    // static_param at offset 0x50
    sead::SafeString mHoldOnXLinkKey_s{};
    u32 _60 = 0;
    Unk_7102450298 _68{mActor};
};
KSYS_CHECK_SIZE_NX150(AddCarriedBase, 0xc0);

}  // namespace uking::ai
