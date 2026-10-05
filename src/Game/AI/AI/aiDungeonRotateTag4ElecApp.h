#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonRotateTag4ElecApp : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonRotateTag4ElecApp, ksys::act::ai::Ai)
public:
    explicit DungeonRotateTag4ElecApp(const InitArg& arg);
    ~DungeonRotateTag4ElecApp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_710037816C();

    // map_unit_param at offset 0x38
    const int* mCtrlDgnRemainsElectricBodyPart_m{};
    // map_unit_param at offset 0x40
    const float* mInitDgnRotRad_m{};
    f32 _48{};
    int _4c{};
    int _50 = -1;
};

}  // namespace uking::ai
