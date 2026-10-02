#pragma once

#include "Game/AI/Behavior/behaviorCreateEaselBase.h"

namespace uking::behavior {

// CSV name: CreateEasel (intermediate base of the CreateEasel behavior; placeholder name from its vtable).
class Unk_7102435118 : public CreateEaselBase {
    SEAD_RTTI_OVERRIDE(Unk_7102435118, CreateEaselBase)
public:
    explicit Unk_7102435118(const InitArg& arg);
    ~Unk_7102435118() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    const char* m14() override;  // not decompiled yet (0x710061ddc8)

};

}  // namespace uking::behavior
