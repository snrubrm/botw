#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

class PlayerStainWait : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerStainWait, PlayerAction)
public:
    explicit PlayerStainWait(const InitArg& arg);
    ~PlayerStainWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    s32 _20 = -1;
    ksys::MessageTransceiverTxOnly _28{mActor};
    sead::Matrix34f _78 = sead::Matrix34f::ident;

};
KSYS_CHECK_SIZE_NX150(PlayerStainWait, 0xa8);

}  // namespace uking::action
