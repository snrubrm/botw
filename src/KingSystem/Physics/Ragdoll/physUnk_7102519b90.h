#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/Resource/resResource.h"

namespace ksys::phys {

class Unk_71012a6f50;

// Resource built at 0x71012aa370, with vtable 0x7102519b90 and entries of stride 0xa8.
class Unk_7102519b90 : public res::Resource {
    SEAD_RTTI_OVERRIDE(Unk_7102519b90, res::Resource)
public:
    Unk_7102519b90();
    ~Unk_7102519b90() override;

protected:
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    void finalize_() override;
    bool finishParsing_() override;
    bool m7_() override;

private:
    sead::Buffer<Unk_71012a6f50> mEntries;
};
KSYS_CHECK_SIZE_NX150(Unk_7102519b90, 0x48);

}  // namespace ksys::phys
