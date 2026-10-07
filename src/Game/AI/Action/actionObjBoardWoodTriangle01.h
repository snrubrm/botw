#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "Game/Actor/actObjBoardWoodTriangleUserTag.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include <container/seadObjArray.h>

namespace uking::action {

class ObjBoardWoodTriangle01 : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ObjBoardWoodTriangle01, ksys::act::ai::Action)
public:
    explicit ObjBoardWoodTriangle01(const InitArg& arg);
    ~ObjBoardWoodTriangle01() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;

    sead::FixedObjArray<ksys::act::BaseProcLink, 4> _20;
    // The original has another fixed object array and message senders in this block.
    u8 _a0[0x3f8 - 0xa0];
    f32 _3f8 = 1.0f;
    act::ObjBoardWoodTriangleUserTag _400{mActor};
    bool _460 = false;
};
KSYS_CHECK_SIZE_NX150(ObjBoardWoodTriangle01, 0x468);

}  // namespace uking::action
