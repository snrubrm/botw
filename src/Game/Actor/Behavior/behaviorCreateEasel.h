#pragma once

#include "Game/Actor/Behavior/behaviorUnk_7102435118.h"

namespace uking::behavior {

class CreateEasel : public Unk_7102435118 {
    SEAD_RTTI_OVERRIDE(CreateEasel, Unk_7102435118)
public:
    explicit CreateEasel(const InitArg& arg);
    ~CreateEasel() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    bool m15() override;

};
KSYS_CHECK_SIZE_NX150(CreateEasel, 0x58);

}  // namespace uking::behavior
