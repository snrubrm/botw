#pragma once

#include "Game/AI/Action/actionEquipedAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::ai {
class Unk_7102407678;
}

namespace uking::action {

class EquipedRod : public EquipedAction {
    SEAD_RTTI_OVERRIDE(EquipedRod, EquipedAction)
public:
    explicit EquipedRod(const InitArg& arg);
    ~EquipedRod() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool sub_7100111C48();
    bool sub_7100111AC4();
    bool sub_7100111D60();
    bool sub_7100111EB8();
    bool sub_7100112850();
    bool sub_7100112C20();

    // static_param at offset 0x40
    const float* mMagicCreateYOffset_s{};
    // static_param at offset 0x48
    const bool* mIsAxisYTop_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mMagicShootVelOffset_s{};
    // static_param at offset 0x58
    const bool* mIsCreateWeaponPosOffset_s{};
    // static_param at offset 0x60
    const sead::Vector3f* mCreatePosOffset_s{};
    // static_param at offset 0x68
    const float* mAxisYAngle_s{};
    // aitree_variable at offset 0x70
    ai::Unk_7102407678** mMagicCreateUnit_a{};
    f32 _78 = 0.0f;
    f32 _7c = 0.0f;
    f32 _80 = 0.0f;
    f32 _84 = -1.0f;
    void* _88{};
    f32 _90 = -1.0f;
    s32 _94 = 0;
    u16 _98 = 0;
    s32 _9c = 0;
    s32 _a0 = 0;
    u32 _a4 = 1;
};
KSYS_CHECK_SIZE_NX150(EquipedRod, 0xa8);

}  // namespace uking::action
