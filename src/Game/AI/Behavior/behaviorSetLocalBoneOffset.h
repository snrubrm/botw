#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace uking::behavior {

class SetLocalBoneOffset : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetLocalBoneOffset, ksys::act::ai::Behavior)
public:
    explicit SetLocalBoneOffset(const InitArg& arg);
    ~SetLocalBoneOffset() override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x710063c9d8)

    /* 0x28 */ sead::SafeString mBoneName_s{};
    /* 0x38 */ const sead::Vector3f* mTransOffset_s{};
    /* 0x40 */ const sead::Vector3f* mRotOffset_s{};
    /* 0x48 */ ksys::act::BoneHandle _48;
};
KSYS_CHECK_SIZE_NX150(SetLocalBoneOffset, 0xf0);

}  // namespace uking::behavior
