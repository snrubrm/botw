#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SandwichDetectionAreaTagSimple : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(SandwichDetectionAreaTagSimple, AreaTagAction)
public:
    explicit SandwichDetectionAreaTagSimple(const InitArg& arg);
    ~SandwichDetectionAreaTagSimple() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m15(const ksys::act::ActorConstDataAccess& accessor) override;
    void m2() override { _48 = false; }
    void m5() override;
    sead::Buffer<Payload>* m6() override { return &_38; }

    sead::Buffer<Payload> _38;
    // An accepted actor is in the area (this frame).
    bool _48 = false;
    // Value of _48 when the basic signal was last emitted.
    bool _49 = false;
};
KSYS_CHECK_SIZE_NX150(SandwichDetectionAreaTagSimple, 0x50);

}  // namespace uking::action
