#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaActorObserve : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(AreaActorObserve, AreaTagAction)
public:
    explicit AreaActorObserve(const InitArg& arg);
    ~AreaActorObserve() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    virtual void m32();
    void m2() override { _34 = 0; }
    bool m15(const ksys::act::ActorConstDataAccess& accessor) override;
    // 0x7100e23070 (declared only): emits the basic signal; needs the AreaManagement actor class.
    void m5() override;
    sead::Buffer<Payload>* m6() override { return &_50; }
    // Whether `accessor` is one of the observed actors.
    virtual bool m37(const ksys::act::ActorConstDataAccess& accessor);

    // Number of observed actors in the area (in ActorObserver's tail padding).
    int _34 = 0;
    // map_unit_param at offset 0x38
    const int* mCount_m{};
    // map_unit_param at offset 0x40
    const bool* mIsSendMessage_m{};
    // map_unit_param at offset 0x48
    const bool* mDefaultBasicSignal_m{};
    sead::Buffer<Payload> _50;
};
KSYS_CHECK_SIZE_NX150(AreaActorObserve, 0x60);

}  // namespace uking::action
