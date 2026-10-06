#pragma once

#include "Game/AI/Action/actionSiteBossLswordAtkWithChemical.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossLswordWhirlSlash : public SiteBossLswordAtkWithChemical {
    SEAD_RTTI_OVERRIDE(SiteBossLswordWhirlSlash, SiteBossLswordAtkWithChemical)
public:
    explicit SiteBossLswordWhirlSlash(const InitArg& arg);
    ~SiteBossLswordWhirlSlash() override;

    void loadParams_() override;

protected:
    void calc_() override;

    int m34() override;
    void m37(sead::Vector3f* pos) override;
    f32 m38() override;
    int m39() override;

    // 0x7100260b10 (name is a guess): finds the first rail point within EmitChangeDist (in xz).
    bool sub_7100260B10(sead::Vector3f* out);

    // static_param at offset 0x1e8
    const float* mEmitChangeDist_s{};
    // static_param at offset 0x1f0
    const float* mCircleEmitOffset_s{};
    bool _1f8 = false;
};

}  // namespace uking::action
