#pragma once

#include "KingSystem/System/VFRValue.h"
#include "Game/AI/Action/actionDungeonRotateBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonRotate : public DungeonRotateBase {
    SEAD_RTTI_OVERRIDE(DungeonRotate, DungeonRotateBase)
public:
    explicit DungeonRotate(const InitArg& arg);
    ~DungeonRotate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71000fd51c (declared only): out of line in the original.
    void sub_71000FD51C();
    void calc_() override;

    // map_unit_param at offset 0xc8
    const int* mDgnRotDir_m{};
    ksys::VFRValue _d0;
    u8 _dc[0x4];
};
KSYS_CHECK_SIZE_NX150(DungeonRotate, 0xe0);

}  // namespace uking::action
