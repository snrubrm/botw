#pragma once

#include <basis/seadTypes.h>

namespace aal {

// The asset-list interface behind the six virtual defaults at 0x7101059458..0x7101059484.
// The slot order is the native one: destructor, 0x7101059468, 0x710105946c, 0x7101059474,
// isDirty, clearDirty, 0x7101059458. The three unnamed slots stay mNN placeholders; only the
// two named rows' signatures are proved (both take just the receiver).
class IAssetList {
public:
    virtual ~IAssetList();

    // 0x7101059468: does nothing.
    virtual void m2();
    // 0x710105946c / 0x7101059474 / 0x7101059458: the defaults return false.
    virtual bool m3() const;
    virtual bool m4() const;
    virtual bool isDirty() const;
    // 0x7101059484: does nothing.
    virtual void clearDirty();
    virtual bool m5() const;
};

}  // namespace aal
