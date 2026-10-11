#pragma once

#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace uking {

// Complete five-slot table 0x71024739f8. Both concrete constructors 8BDDD8 / 8BED58
// call this constructor and place their first member at +480.
class Unk_71024739f8 {
public:
    // 90DBCC initializes both flags and the vector; 8BF664 forwards them to setPointerWithBound_.
    struct PointerState {
        bool _0;
        bool _1;
        sead::Vector2f position;
    };

    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {
        static const sead::RuntimeTypeInfo::Root typeInfo;
        return &typeInfo;
    }

    static bool checkDerivedRuntimeTypeInfoStatic(
        const sead::RuntimeTypeInfo::Interface* typeInfo) {
        return typeInfo == getRuntimeTypeInfoStatic();
    }

    virtual bool checkDerivedRuntimeTypeInfo(
        const sead::RuntimeTypeInfo::Interface* typeInfo) const;
    virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const;

    Unk_71024739f8();
    virtual ~Unk_71024739f8();
    virtual void update();

    u32 getHold() const;
    const sead::Vector2f* getSticks() const;
    const PointerState& getPointerState() const;

private:
    u32 mHold;
    u8 _c[4];
    // Full concrete 8BE174 producer / 246D198 table establish the existing delegate interface.
    sead::SafeArray<sead::AnyDelegate1<bool*>, 32> mButtonDelegates;
    sead::Vector2f mSticks[2];
    u8 _420[0x20];
    PointerState mPointerState;
    u8 _44c[4];
    u8 _450[0x20];
    u8 _470[0x10];
};
KSYS_CHECK_SIZE_NX150(Unk_71024739f8::PointerState, 0xc);
KSYS_CHECK_SIZE_NX150(Unk_71024739f8, 0x480);

}  // namespace uking
