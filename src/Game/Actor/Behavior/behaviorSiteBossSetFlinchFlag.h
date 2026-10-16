#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SiteBossSetFlinchFlag : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SiteBossSetFlinchFlag, ksys::act::ai::Behavior)
public:
    explicit SiteBossSetFlinchFlag(const InitArg& arg);
    ~SiteBossSetFlinchFlag() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(SiteBossSetFlinchFlag, 0x28);

}  // namespace uking::behavior
