#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"

// Vtable 0x71023b3310: the weak-point action's damage callback, with no extra data.
class Unk_71023b3310 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_71023b3310, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
              uking::dmg::DamageCallbackInfo* a6) override;
};

namespace uking::action {

class RemainsElectricWeakPointWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainsElectricWeakPointWait, ksys::act::ai::Action)
public:
    explicit RemainsElectricWeakPointWait(const InitArg& arg);
    ~RemainsElectricWeakPointWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    Unk_71023b3310 _20;
    ksys::act::BaseProcLink _48;
    ksys::MessageTransceiverTxOnly _58;
    s32 _a8 = -1;
};
KSYS_CHECK_SIZE_NX150(RemainsElectricWeakPointWait, 0xb0);

}  // namespace uking::action
