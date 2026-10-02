#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SandwichDetectionAreaTag : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(SandwichDetectionAreaTag, AreaTagAction)
public:
    explicit SandwichDetectionAreaTag(const InitArg& arg);
    ~SandwichDetectionAreaTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m15(const ksys::act::ActorConstDataAccess& accessor) override;
    void m2() override;
    void m5() override;
    bool m13(const CollisionIterator& it, int area_idx) override;
    bool m14(const ContactIterator& it, int area_idx) override;
    sead::Buffer<Payload>* m6() override { return &_38; }

    sead::Buffer<Payload> _38;
    u8 _48[0x100];
    // An accepted actor is in the area (this frame).
    bool _148;
    // Value of _148 when the basic signal was last emitted.
    bool _149;
};
KSYS_CHECK_SIZE_NX150(SandwichDetectionAreaTag, 0x150);

}  // namespace uking::action
