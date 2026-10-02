#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OwnedHorseObserveAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(OwnedHorseObserveAction, AreaTagAction)
public:
    explicit OwnedHorseObserveAction(const InitArg& arg);
    ~OwnedHorseObserveAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m15(const ksys::act::ActorConstDataAccess& accessor) override;
    sead::Buffer<Payload>* m6() override { return &_48; }

    // map_unit_param at offset 0x38
    sead::SafeString mSaveFlag_m{};
    sead::Buffer<Payload> _48;
    // The owned horse is in the area (this frame).
    bool _58 = false;
    // Last value written to the SaveFlag game data flag (0xff: none yet).
    u8 _59 = 0xff;
};
KSYS_CHECK_SIZE_NX150(OwnedHorseObserveAction, 0x60);

}  // namespace uking::action
