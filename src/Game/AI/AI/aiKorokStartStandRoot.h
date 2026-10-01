#pragma once

#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokStartStandRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokStartStandRoot, ksys::act::ai::Ai)
public:
    explicit KorokStartStandRoot(const InitArg& arg);
    ~KorokStartStandRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool _38 = false;
    xlink2::HandleELink _40;
    xlink2::HandleSLink _50;
};
KSYS_CHECK_SIZE_NX150(KorokStartStandRoot, 0x60);

}  // namespace uking::ai
