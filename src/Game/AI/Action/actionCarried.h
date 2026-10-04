#pragma once

#include "Game/AI/aiUnk_7102450058.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::action {

class Carried : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Carried, ksys::act::ai::Action)
public:
    explicit Carried(const InitArg& arg);
    ~Carried() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool hasUpdateForPreDeleteCb() override;
    bool updateForPreDelete() override;

protected:
    void calc_() override;
    virtual bool m32();
    // 0x71000d4fb4 / 0x71000d5da4 / 0x71000d50d0 / 0x71000d5dac / 0x71000d5dc8 (m33 / m35 declared only).
    virtual bool m33(sead::Matrix34f* out, const sead::Vector3f* a2);
    virtual ksys::act::ModelBindInfo* m34() { return &_70; }
    virtual void m35();
    virtual void m36(const sead::Matrix34f* mtx) { _70._68 = *mtx; }
    virtual bool m37() { return true; }

    // static_param at offset 0x20
    const int* mBindType_s{};
    // static_param at offset 0x28
    const float* mFailDistance_s{};
    // static_param at offset 0x30
    const bool* mIsCreateItem_s{};
    // static_param at offset 0x38
    const bool* mIsRecoverCharCtrlAxis_s{};
    // static_param at offset 0x40
    const bool* mIsUseConstraint_s{};
    // static_param at offset 0x48
    const bool* mIsOnBaseLink_s{};
    // static_param at offset 0x50
    const bool* mIsChangeable_s{};
    // static_param at offset 0x58
    sead::SafeString mHoldOnXLinkKey_s{};
    s32 _68 = 0;
    ksys::act::ModelBindInfo _70;
    Unk_7102450298 _110{mActor};
};
KSYS_CHECK_SIZE_NX150(Carried, 0x168);

}  // namespace uking::action
