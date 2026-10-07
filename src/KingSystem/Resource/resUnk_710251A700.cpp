#include "KingSystem/Resource/resUnk_710251A700.h"
#include <prim/seadScopedLock.h>

namespace ksys::res {

Unk_710251A700::Unk_710251A700()
    : mCS(nullptr, sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified) {}

Unk_710251A700::~Unk_710251A700() {
    mBuffer.freeBuffer();
}

bool Unk_710251A700::sub_71012B9054(const InitArg& arg) {
    mBuffer.tryAllocBuffer(arg._0, arg._8, 8);
    for (u32 i = 0; i < arg._0; ++i)
        mBuffer.pushBack(new (arg._8, 8) Entry);
    return true;
}

void* Unk_710251A700::sub_71012B913C() {
    auto lock = sead::makeScopedLock(mCS);
    return mBuffer.popFront();
}

void Unk_710251A700::sub_71012B91B4(void* item) {
    auto lock = sead::makeScopedLock(mCS);
    mBuffer.pushBack(item);
}

}  // namespace ksys::res
