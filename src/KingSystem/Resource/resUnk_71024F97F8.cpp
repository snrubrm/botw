#include "KingSystem/Resource/resUnk_71024F97F8.h"

namespace ksys::res {

Unk_71024F97F8::Unk_71024F97F8() = default;
Unk_71024F97F8::~Unk_71024F97F8() = default;

bool Unk_71024F97F8::needsParse() const {
    return true;
}

bool Unk_71024F97F8::m2_() {
    return mArchive.isValid();
}

bool Unk_71024F97F8::parse_(u8* data, size_t size, sead::Heap* heap) {
    mArchive = agl::utl::ResParameterArchive(data + mAllocSize);
    return true;
}

}  // namespace ksys::res
