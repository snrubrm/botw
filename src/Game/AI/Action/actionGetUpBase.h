#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/aiUnk_7102384718.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class GetUpBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GetUpBase, ksys::act::ai::Action)
public:
    explicit GetUpBase(const InitArg& arg);
    ~GetUpBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    u32 _1c = 0;
    s32 _20 = -1;
    // static_param at offset 0x28
    sead::SafeString mASName_s{};
    // static_param at offset 0x38
    const sead::Vector3f* mRootOffset_s{};
    u32 _40 = 0;
    sead::Matrix33f _44;
    u32 _68 = 0;
    sead::Vector2f _6c{0.0f, 0.0f};
    ksys::VFRValue _74;
    bool _80 = false;
    sead::Vector3f _84 = sead::Vector3f::zero;
    ksys::act::BoneHandle _90;
    Unk_71025afb58Ref<Unk_7102384718> _138;
    // aitree_variable at offset 0x140
    void* mCRBOffsetUnit_a{};
};

}  // namespace uking::action
