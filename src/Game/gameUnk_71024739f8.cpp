#include "Game/gameUnk_71024739f8.h"

namespace uking {

bool Unk_71024739f8::checkDerivedRuntimeTypeInfo(
    const sead::RuntimeTypeInfo::Interface* typeInfo) const {
    return checkDerivedRuntimeTypeInfoStatic(typeInfo);
}

const sead::RuntimeTypeInfo::Interface* Unk_71024739f8::getRuntimeTypeInfo() const {
    return getRuntimeTypeInfoStatic();
}

u32 Unk_71024739f8::getHold() const {
    return mHold;
}

const sead::Vector2f* Unk_71024739f8::getSticks() const {
    return mSticks;
}

const Unk_71024739f8::PointerState& Unk_71024739f8::getPointerState() const {
    return mPointerState;
}

}  // namespace uking
