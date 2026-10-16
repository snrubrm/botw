#pragma once

#include "Game/Actor/Behavior/behaviorSetDamageCallback.h"
#include "Game/Actor/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetPopPoolDamageAttrDCCallback : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetPopPoolDamageAttrDCCallback, SetDamageCallback)
public:
    explicit SetPopPoolDamageAttrDCCallback(const InitArg& arg);
    ~SetPopPoolDamageAttrDCCallback() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    uking::act::DamageCallback* m14() override;

    struct Params {
        const int* mAttrForSmall_s{};
        const int* mAttrForFinish_s{};
    };
    /* 0x30 */ Params mParams;
    /* 0x40 */ Unk_7102451d40 _40;
};
KSYS_CHECK_SIZE_NX150(SetPopPoolDamageAttrDCCallback, 0x70);

}  // namespace uking::behavior
