#include "Game/gameUnk_71024739f8.h"

namespace uking {

bool Unk_71024739f8::checkDerivedRuntimeTypeInfo(
    const sead::RuntimeTypeInfo::Interface* typeInfo) const {
    return checkDerivedRuntimeTypeInfoStatic(typeInfo);
}

const sead::RuntimeTypeInfo::Interface* Unk_71024739f8::getRuntimeTypeInfo() const {
    return getRuntimeTypeInfoStatic();
}

Unk_71024739f8::Unk_71024739f8() = default;

// NON_MATCHING: block layout (the original duplicates the loop latch for unbound delegates) and the stack slot of `on`.
void Unk_71024739f8::update() {
    s32 bit = 0;
    for (auto& delegate : mButtonDelegates) {
        if (delegate) {
            bool on = false;
            delegate(&on);
            if (on)
                mHold |= 1 << bit;
            else
                mHold &= ~(1 << bit);
            ++bit;
        }
    }
    if (mSticksDelegate)
        mSticksDelegate(mSticks);
    if (mPointerStateDelegate)
        mPointerStateDelegate(&mPointerState);
}

bool Unk_71024739f8::sub_710090DD88() const {
    return bool(mPointerStateDelegate);
}

bool Unk_71024739f8::sub_710090DD9C() const {
    return bool(mSticksDelegate);
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
