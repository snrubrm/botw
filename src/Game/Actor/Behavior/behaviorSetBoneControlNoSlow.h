#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetBoneControlNoSlow : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetBoneControlNoSlow, ksys::act::ai::Behavior)
public:
    explicit SetBoneControlNoSlow(const InitArg& arg);
    ~SetBoneControlNoSlow() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(SetBoneControlNoSlow, 0x28);

}  // namespace uking::behavior
