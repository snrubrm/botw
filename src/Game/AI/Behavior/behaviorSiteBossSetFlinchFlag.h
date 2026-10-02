#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SiteBossSetFlinchFlag : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SiteBossSetFlinchFlag, ksys::act::ai::Behavior)
public:
    explicit SiteBossSetFlinchFlag(const InitArg& arg);
    ~SiteBossSetFlinchFlag() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(SiteBossSetFlinchFlag, 0x28);

}  // namespace uking::behavior
