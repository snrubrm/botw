#pragma once

#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class GanonNormalRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonNormalRoot, ksys::act::ai::Ai)
public:
    explicit GanonNormalRoot(const InitArg& arg);
    ~GanonNormalRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    void sub_71003ED718(int idx);
    bool sub_71003ED9B0();

protected:
    sead::SafeArray<ksys::act::BaseProcHandle, 4> _38;
    sead::SafeArray<ksys::act::BaseProcLink, 4> _78;
};
KSYS_CHECK_SIZE_NX150(GanonNormalRoot, 0xb8);

}  // namespace uking::ai
