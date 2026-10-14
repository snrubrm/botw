#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemPartsSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GolemPartsSelect, ksys::act::ai::Ai)
public:
    explicit GolemPartsSelect(const InitArg& arg);
    ~GolemPartsSelect() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool isMaterialVisible(const gsys::MaterialAccessKeyEx& key) const;

    struct Params {
        // static_param at offset 0x38
        sead::SafeString mArmRModelMatrialName_s{};
        // static_param at offset 0x48
        sead::SafeString mArmLModelMatrialName_s{};
    };
    Params mParams;
    gsys::MaterialAccessKeyEx _58;
    gsys::MaterialAccessKeyEx _90;
};

}  // namespace uking::ai
