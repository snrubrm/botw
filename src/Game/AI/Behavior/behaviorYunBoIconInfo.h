#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class YunBoIconInfo : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(YunBoIconInfo, ksys::act::ai::Behavior)
public:
    explicit YunBoIconInfo(const InitArg& arg);
    ~YunBoIconInfo() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mType_s{};
    /* 0x30 */ const bool* mVisible_s{};
};
KSYS_CHECK_SIZE_NX150(YunBoIconInfo, 0x38);

}  // namespace uking::behavior
