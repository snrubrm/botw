#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HeroSoulGiftRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HeroSoulGiftRoot, ksys::act::ai::Ai)
public:
    explicit HeroSoulGiftRoot(const InitArg& arg);
    ~HeroSoulGiftRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    virtual bool m34(sead::Matrix34f* mtx);
    virtual bool m35(sead::Matrix34f* mtx);
    virtual void m36();
    virtual bool m37() { return true; }

protected:
    // 0x710042eeb4: sleeps the actor if ActorFlag2::_20 is set, otherwise changes to 退場.
    void sub_710042EEB4();

    // static_param at offset 0x38
    const bool* mUseInitMtxForBasePos_s{};
    // static_param at offset 0x40
    const bool* mUseInitMtxForBaseRot_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mPosOffset_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mRotOffset_s{};
    sead::Matrix34f _58 = sead::Matrix34f::ident;
    bool _88{};
};

}  // namespace uking::ai
