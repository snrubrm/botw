#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace aal {

/// Base of the named aal objects (shapes, listeners, ...): a vtable and the name string.
class NamedObj {
public:
    NamedObj() = default;
    explicit NamedObj(const sead::SafeString& name) : mName("") { mName = name; }
    explicit NamedObj(const char* name) : mName(name) {}
    virtual ~NamedObj() = default;
    virtual void setObjName(const sead::SafeString& name);

    const sead::SafeString& getObjName() const { return mName; }

protected:
    sead::SafeString mName;
};
static_assert(sizeof(NamedObj) == 0x18, "aal::NamedObj size mismatch");

/// A named object that owns the storage of its name (the name of NamedObj points to it).
template <s32 N>
class FixedNamedObj : public NamedObj {
public:
    FixedNamedObj() : NamedObj("") {}
    ~FixedNamedObj() override = default;

    void setObjName(const sead::SafeString& name) override;

protected:
    sead::FixedSafeString<N> mFixedName;
};

}  // namespace aal
