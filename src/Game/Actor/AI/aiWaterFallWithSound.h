#pragma once

#include <aal/aalShape.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaterFallWithSound : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WaterFallWithSound, ksys::act::ai::Ai)
public:
    explicit WaterFallWithSound(const InitArg& arg);
    ~WaterFallWithSound() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void sub_71005EC090();
    void sub_71005EBEC0();

protected:
    void updateShapeFromModel_();

    aal::ShapeCapsule* _38 = nullptr;  // created in init_
    xlink2::HandleSLink _40;
};
KSYS_CHECK_SIZE_NX150(WaterFallWithSound, 0x50);

}  // namespace uking::ai
