#pragma once

#include "KingSystem/Resource/resHandle.h"

namespace ksys::res {

class BfRes;

// CSV ResDerived (ctor 0x71011fc5c0: `res::Handle::Handle()` + its own vtable store; 71 callers): a res::Handle
// subclass that holds a bfres resource (BfRes: placeholder name, the T of the EntryFactory<T> of the texture handle
// manager TU). Placeholder name.
class ResDerived : public Handle {
    SEAD_RTTI_OVERRIDE(ResDerived, Handle)
public:
    ResDerived();
    ~ResDerived() override;

    // 0x71011fc618 (CSV ResDerived::getModelRes): the loaded resource if it is a BfRes.
    BfRes* getModelRes();
    // 0x71011fc6ac / 0x71011fc73c: the pointer at +0x50 of the BfRes (checked / without the type check).
    void* sub_71011FC6AC();
    void* sub_71011FC73C();
};

}  // namespace ksys::res
