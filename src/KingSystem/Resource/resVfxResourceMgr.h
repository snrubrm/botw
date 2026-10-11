#pragma once

#include "KingSystem/Resource/resResource.h"

namespace ksys::res {

// Complete table 2518018 and independent factory producers 12726E4 / 1272E54
// establish this 0x38-byte Resource for the esetlist extension.
class Unk_7102518018 : public Resource {
    SEAD_RTTI_OVERRIDE(Unk_7102518018, Resource)
public:
    ~Unk_7102518018() override;
    static constexpr size_t cLoadDataAlignment = 0x4000;
    s32 getLoadDataAlignment() const override;

protected:
    // Native 1271C50, declared only pending the SDK Unrelocate interface audit.
    void onDestroy_() override;
};
KSYS_CHECK_SIZE_NX150(Unk_7102518018, 0x38);

}  // namespace ksys::res
