#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace uking::behavior {

class SetLocalBoneOffsetRandom : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetLocalBoneOffsetRandom, ksys::act::ai::Behavior)
public:
    explicit SetLocalBoneOffsetRandom(const InitArg& arg);
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x710063cda4)
    ~SetLocalBoneOffsetRandom() override;  // not decompiled yet

    /* 0x28 */ sead::SafeString mBoneName_s{};
    /* 0x38 */ const sead::Vector3f* mTransOffsetMax_s{};
    /* 0x40 */ const sead::Vector3f* mTransOffsetMin_s{};
    /* 0x48 */ const sead::Vector3f* mRotOffsetMax_s{};
    /* 0x50 */ const sead::Vector3f* mRotOffsetMin_s{};
    /* 0x58 */ ksys::act::BoneHandle _58;
};
KSYS_CHECK_SIZE_NX150(SetLocalBoneOffsetRandom, 0x100);

}  // namespace uking::behavior
