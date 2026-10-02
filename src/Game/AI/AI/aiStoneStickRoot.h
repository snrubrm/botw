#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StoneStickRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StoneStickRoot, ksys::act::ai::Ai)
public:
    explicit StoneStickRoot(const InitArg& arg);
    ~StoneStickRoot() override;
    bool hasUpdateForPreDeleteCb() override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const sead::Vector3f* mFixPoint_s{};
    bool _40 = false;
    void* _48 = nullptr;
    u32 _50 = 0;
    u32 _54 = 0;
    void* _58 = nullptr;
    u32 _60 = 0;
    u32 _64 = 0;
    void* _68 = nullptr;
    void* _70 = nullptr;
    u32 _78 = 0;
};
KSYS_CHECK_SIZE_NX150(StoneStickRoot, 0x80);

}  // namespace uking::ai
