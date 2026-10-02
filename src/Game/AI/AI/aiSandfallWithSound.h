#pragma once

#include <math/seadVector.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandfallWithSound : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandfallWithSound, ksys::act::ai::Ai)
public:
    explicit SandfallWithSound(const InitArg& arg);
    ~SandfallWithSound() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void sub_71005565D8();

protected:
    void sub_7100556370();
    void sub_710055646C();

    // aal::ShapeSegment* (created in init_ with aal::ShapeSegment::create)
    void* _38{};
    xlink2::HandleSLink _40;
    xlink2::HandleSLink _50;
    sead::Vector3f _60 = sead::Vector3f::zero;
};

}  // namespace uking::ai
