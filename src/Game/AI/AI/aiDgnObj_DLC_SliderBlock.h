#pragma once

#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// Besides Ai it has a plain ActorBind subobject at 0x38 (its ctor calls ActorBind::ActorBind; the
// actor's mModelBindInfo is set to it in enter_). m4/m5 override ActorBind's slots (their Ai
// vtable entries are the CSV's m34/m35).
class DgnObj_DLC_SliderBlock : public ksys::act::ai::Ai, public ksys::act::ActorBind {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_SliderBlock, ksys::act::ai::Ai)
public:
    explicit DgnObj_DLC_SliderBlock(const InitArg& arg);
    ~DgnObj_DLC_SliderBlock() override;

    bool updateForPreDelete() override;

    bool hasUpdateForPreDeleteCb() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    bool m4(ksys::act::BaseProc* proc) override;
    bool m5(ksys::act::BaseProc* proc) override;

protected:
    f32 _60 = 0;
};

}  // namespace uking::ai
