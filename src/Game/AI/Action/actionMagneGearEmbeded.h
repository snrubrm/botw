#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MagneGearEmbeded : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MagneGearEmbeded, ksys::act::ai::Action)
public:
    explicit MagneGearEmbeded(const InitArg& arg);
    ~MagneGearEmbeded() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void* _20{};
    void* _28{};
    void* _30{};
    void* _38{};
    void* _40{};
    void* _48{};
};

}  // namespace uking::action
