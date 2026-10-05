#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <xlink2/xlink2HandleELink.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace ksys::act {
class Unk_71024ef620;
}

namespace uking::ai {

class GerudoQueenBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GerudoQueenBattle, ksys::act::ai::Ai)
public:
    explicit GerudoQueenBattle(const InitArg& arg);
    ~GerudoQueenBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRetireFrame_s{};
    xlink2::HandleELink _40;
    ksys::act::BaseProcLink _50;
    ksys::act::BaseProcLink _60;
    ksys::act::BaseProcLink _70;
    ksys::act::Unk_71024ef620* _80 = nullptr;
    bool _88 = false;
    bool _89 = false;
    sead::Matrix34f _8c = sead::Matrix34f::ident;
    sead::Matrix34f _bc = sead::Matrix34f::ident;
    f32 _ec = 1.0f;
    f32 _f0 = 1.0f;
    f32 _f4 = 0.2f;
    bool _f8 = false;
    sead::Vector3f _fc{0, 0, 0};
    sead::Vector3f _108{0, 0, 0};
    u32 _114 = 0;
    ksys::act::BoneHandle* _118 = nullptr;  // new BoneHandle[3] (the destructor deletes it)
};
KSYS_CHECK_SIZE_NX150(GerudoQueenBattle, 0x120);

}  // namespace uking::ai
