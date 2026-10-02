#pragma once

#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class KorokStartStandRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokStartStandRoot, ksys::act::ai::Ai)
public:
    explicit KorokStartStandRoot(const InitArg& arg);
    ~KorokStartStandRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool _38 = false;
    Unk_71012419b4 _40;
};
KSYS_CHECK_SIZE_NX150(KorokStartStandRoot, 0x60);

}  // namespace uking::ai
