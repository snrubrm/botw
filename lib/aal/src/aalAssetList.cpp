#include <aal/aalAssetList.h>

namespace aal {

IAssetList::~IAssetList() = default;

void IAssetList::m2() {}

bool IAssetList::m3() const {
    return false;
}

bool IAssetList::m4() const {
    return false;
}

bool IAssetList::isDirty() const {
    return false;
}

void IAssetList::clearDirty() {}

bool IAssetList::m5() const {
    return false;
}

}  // namespace aal
