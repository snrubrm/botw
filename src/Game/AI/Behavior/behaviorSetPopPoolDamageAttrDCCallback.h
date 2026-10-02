#pragma once

#include "Game/AI/Behavior/behaviorSetDamageCallback.h"
#include "Game/AI/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetPopPoolDamageAttrDCCallback : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetPopPoolDamageAttrDCCallback, SetDamageCallback)
public:
    explicit SetPopPoolDamageAttrDCCallback(const InitArg& arg);
    ~SetPopPoolDamageAttrDCCallback() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    uking::dmg::DamageCallback* m14() override;

    /* 0x30 */ const int* mAttrForSmall_s{};
    /* 0x38 */ const int* mAttrForFinish_s{};
    /* 0x40 */ Unk_7102451d40 _40;
};
KSYS_CHECK_SIZE_NX150(SetPopPoolDamageAttrDCCallback, 0x70);

}  // namespace uking::behavior
