#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace uking::ai {

// Unnamed bone handle embedded in AssassinMiddleRoot (vtable 0x71023d8e28, only referenced by
// AssassinMiddleRoot's constructor). Sets a local matrix (_24, scale _54) on the bone _20.
// Placeholder name = vtable address.
class Unk_71023d8e28 : public ksys::act::BoneHandleBase {
public:
    // 0x710032173c (declared before m2 so that this TU emits the vtable).
    bool m3(gsys::Model* model, bool sorted) override;
    // 0x7100320da8: not decompiled (reads gsys::Model fields that lib/gsys does not declare).
    void m2(gsys::Model* model) override;
    const gsys::BoneAccessKey* m4() override { return &_20; }

    gsys::BoneAccessKey _20;
    sead::Matrix34f _24 = sead::Matrix34f::ident;
    sead::Vector3f _54 = sead::Vector3f::ones;
};
KSYS_CHECK_SIZE_NX150(Unk_71023d8e28, 0x60);

class AssassinMiddleRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(AssassinMiddleRoot, EnemyRoot)
public:
    explicit AssassinMiddleRoot(const InitArg& arg);
    ~AssassinMiddleRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    bool m35() override;
    void m43() override;

protected:
    // static_param at offset 0x1d8
    const int* mPodModelUnitIdx_s{};
    // static_param at offset 0x1e0
    sead::SafeString mPodNodeName_s{};
    // static_param at offset 0x1f0
    sead::SafeString mMagicUsePartsName_s{};
    // static_param at offset 0x200
    const sead::Vector3f* mSheathOffset_s{};
    Unk_71023d8e28 _208;
    ksys::act::BoneHandle _268;
    Unk_7102372510 _310{mActor, 0x8000008};
};
KSYS_CHECK_SIZE_NX150(AssassinMiddleRoot, 0x340);

}  // namespace uking::ai
