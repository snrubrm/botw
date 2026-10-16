#pragma once

#include "Game/Actor/Behavior/behaviorCreateEaselBase.h"

namespace uking::behavior {

// CSV name: CreateEasel (intermediate base of the CreateEasel behavior; placeholder name from its vtable).
class Unk_7102435118 : public CreateEaselBase {
    SEAD_RTTI_OVERRIDE(Unk_7102435118, CreateEaselBase)
public:
    explicit Unk_7102435118(const InitArg& arg);
    ~Unk_7102435118() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    const char* m14() override;

};

}  // namespace uking::behavior
