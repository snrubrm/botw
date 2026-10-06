#pragma once

#include <aal/aalShape.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/AI/aiUnk_71010F122C.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AscendingCurrent : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AscendingCurrent, ksys::act::ai::Action)
public:
    explicit AscendingCurrent(const InitArg& arg);
    ~AscendingCurrent() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool hasUpdateForPreDeleteCb() override;

protected:
    void calc_() override;

    // Activates the wind box (a no-op unless it has a body).
    virtual void m32();
    // The size of the wind box (twice the actor's scale).
    virtual void m33(sead::Vector3f* size);
    // The matrix of the wind box (the actor's home matrix).
    virtual void m34(sead::Matrix34f* mtx);

    // 0x71000a6f24 (declared only): moves the wind box, its element, the effect and the sound shape to
    // the matrix / size given by m34 / m33.
    void sub_71000A6F24();
    // 0x71000a71b0 (declared only): emits the wind sound ("wind" on the actor's SLink, else
    // "windAscending" on the global SLink) and gives it the shape.
    void sub_71000A71B0();
    void sub_71000A7354();

    // static_param at offset 0x20
    const float* mWindSpeed_s{};
    Unk_710250d530 _28;
    xlink2::HandleELink _58;
    xlink2::HandleSLink _68;
    // created in init_ with aal::ShapeCube::create
    aal::Shape* _78 = nullptr;
};
KSYS_CHECK_SIZE_NX150(AscendingCurrent, 0x80);

}  // namespace uking::action
