#pragma once

#include "Game/Actor/Behavior/behaviorCancelMessageSendToPartsBase.h"

namespace uking::behavior {

class CancelMessageSendToParts : public CancelMessageSendToPartsBase {
    SEAD_RTTI_OVERRIDE(CancelMessageSendToParts, CancelMessageSendToPartsBase)
public:
    explicit CancelMessageSendToParts(const InitArg& arg);
    ~CancelMessageSendToParts() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m14() override;
    Unk_7102357d20* m15() override;

    /* 0x50 */ Unk_7102372510 _50{mActor, 0x8000008};
};
KSYS_CHECK_SIZE_NX150(CancelMessageSendToParts, 0x80);

}  // namespace uking::behavior
