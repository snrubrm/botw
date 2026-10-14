#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::ai {

class LastBossThunderRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastBossThunderRoot, ksys::act::ai::Ai)
public:
    explicit LastBossThunderRoot(const InitArg& arg);
    ~LastBossThunderRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool _38 = false;
    ksys::act::ModelBindInfo _40;
    ksys::act::BaseProcLink _e0;
};
KSYS_CHECK_SIZE_NX150(LastBossThunderRoot, 0xf0);

}  // namespace uking::ai
