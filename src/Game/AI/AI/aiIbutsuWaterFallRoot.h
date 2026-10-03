#pragma once

#include <aal/aalShape.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class IbutsuWaterFallRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(IbutsuWaterFallRoot, ksys::act::ai::Ai)
public:
    explicit IbutsuWaterFallRoot(const InitArg& arg);
    ~IbutsuWaterFallRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool sub_7100445394(sead::Heap* heap);

    void sub_7100445AA0();

protected:
    bool _38{};
    // created in sub_7100445394
    aal::ShapeCylinder* _40{};
    aal::ShapeCylinder* _48{};
    aal::ShapeSphere* _50{};
    void* _58{};
    u32 _60{};
    void* _68{};
    u32 _70{};
    void* _78{};
    u32 _80{};
};

}  // namespace uking::ai
