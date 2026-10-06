#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

class PlayASForDemo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayASForDemo, ksys::act::ai::Action)
public:
    explicit PlayASForDemo(const InitArg& arg);
    ~PlayASForDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual float m32();
    virtual bool m33();
    virtual const sead::SafeString& m34();
    virtual const sead::SafeString& m35() { return mASName_d; }
    // 0x710021be00 (declared only): plays the AS (playAS or the ASList at 0x710115bc28).
    virtual void m36();

    // Out-of-line copies of inline helpers (names are placeholders): 0x710021ba28 / 0x710021bdc4 /
    // 0x710021bdd8.
    int sub_710021BA28();
    int sub_710021BDC4();
    f32 sub_710021BDD8();

    // static_param at offset 0x20
    const int* mAnimeDrivenSettings_s{};
    // dynamic_param at offset 0x28
    int* mTargetIndex_d{};
    // dynamic_param at offset 0x30
    int* mSeqBank_d{};
    // dynamic_param at offset 0x38
    int* mIsEnabledAnimeDriven_d{};
    // dynamic_param at offset 0x40
    int* mClothWarpMode_d{};
    // dynamic_param at offset 0x48
    float* mMorphingFrame_d{};
    // dynamic_param at offset 0x50
    bool* mIsIgnoreSame_d{};
    // dynamic_param at offset 0x58
    sead::SafeString mASName_d{};
    ksys::act::CCAccessor mCCAccessor;
    bool _70 = false;
    bool _71 = false;
    // not touched by the ctor/enter_/calc_/leave_
    u8 _72[0xa4 - 0x72];
    u32 _a4 = 0;
    bool _a8 = false;
};

KSYS_CHECK_SIZE_NX150(PlayASForDemo, 0xb0);

}  // namespace uking::action
