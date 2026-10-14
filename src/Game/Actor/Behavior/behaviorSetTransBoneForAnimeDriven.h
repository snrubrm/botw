#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetTransBoneForAnimeDriven : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetTransBoneForAnimeDriven, ksys::act::ai::Behavior)
public:
    explicit SetTransBoneForAnimeDriven(const InitArg& arg);
    ~SetTransBoneForAnimeDriven() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ sead::SafeString mTransBoneName_s{};
};
KSYS_CHECK_SIZE_NX150(SetTransBoneForAnimeDriven, 0x38);

}  // namespace uking::behavior
