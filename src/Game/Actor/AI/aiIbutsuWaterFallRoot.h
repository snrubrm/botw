#pragma once

#include <aal/aalShape.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class IbutsuWaterFallRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(IbutsuWaterFallRoot, ksys::act::ai::Ai)
public:
    explicit IbutsuWaterFallRoot(const InitArg& arg);
    ~IbutsuWaterFallRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool sub_7100445394(sead::Heap* heap);

    void sub_7100445AA0();

protected:
    void sub_710044584C();
    void sub_7100445510();

    bool _38{};
    // created in sub_7100445394
    aal::ShapeCylinder* _40{};
    aal::ShapeCylinder* _48{};
    aal::ShapeSphere* _50{};
    xlink2::HandleSLink _58;
    xlink2::HandleSLink _68;
    xlink2::HandleSLink _78;
};

}  // namespace uking::ai
