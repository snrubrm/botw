#pragma once

#include <prim/seadSafeString.h>

namespace aal {

/// Base of the named aal objects (shapes, listeners, ...): a vtable and the name string.
class NamedObj {
public:
    NamedObj() = default;
    explicit NamedObj(const sead::SafeString& name) : mName("") { mName = name; }
    virtual ~NamedObj() = default;
    virtual void setObjName(const sead::SafeString& name);

    const sead::SafeString& getObjName() const { return mName; }

protected:
    sead::SafeString mName;
};
static_assert(sizeof(NamedObj) == 0x18, "aal::NamedObj size mismatch");

}  // namespace aal
