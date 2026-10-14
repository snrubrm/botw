#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TerrainHideCenter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TerrainHideCenter, ksys::act::ai::Action)
public:
    explicit TerrainHideCenter(const InitArg& arg);
    ~TerrainHideCenter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100e179a4 (declared only): out of line in the original.
    void sub_7100E179A4(bool a, bool b, bool c, bool d);
    void calc_() override;

    bool _1c = false;
};

}  // namespace uking::action
