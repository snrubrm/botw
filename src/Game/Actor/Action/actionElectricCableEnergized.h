#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::act {
class Chemical;
}

namespace uking::action {

class ElectricCableEnergized : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ElectricCableEnergized, ksys::act::ai::Action)
public:
    explicit ElectricCableEnergized(const InitArg& arg);
    ~ElectricCableEnergized() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    u8 _1c[0x4];
    ksys::act::Chemical* _20 = nullptr;
    ksys::act::Chemical* _28 = nullptr;

};
KSYS_CHECK_SIZE_NX150(ElectricCableEnergized, 0x30);

}  // namespace uking::action
