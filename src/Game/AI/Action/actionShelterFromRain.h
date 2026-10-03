#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShelterFromRain : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(ShelterFromRain, AreaTagAction)
public:
    explicit ShelterFromRain(const InitArg& arg);
    ~ShelterFromRain() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool handleAck_(const ksys::MessageAck* ack) override;

protected:
    void calc_() override;
    bool m15(const ksys::act::ActorConstDataAccess& accessor) override;
    sead::Buffer<Payload>* m6() override { return &_40; }

    // map_unit_param at offset 0x38
    const int* mShelterFromRainTagType_m{};
    sead::Buffer<Payload> _40;
    bool _50 = false;
    bool _51 = false;
    // Matrix of the owner actor, sent to the sheltering NPC (message 0x8000075).
    sead::Matrix34f _54;
};
KSYS_CHECK_SIZE_NX150(ShelterFromRain, 0x88);

}  // namespace uking::action
