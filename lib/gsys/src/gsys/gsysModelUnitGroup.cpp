#include "gsys/gsysModelUnitGroup.h"

namespace gsys {

// 0x7100c4baac
ModelUnitGroup::CreateArg::CreateArg(const sead::SafeString& first,
                                   const sead::SafeString& second)
    : mCount(1) {
    mNames[0] = first;
    mNames[mCount++] = second;
}

// 0x7100c4bc54, deleting destructor 0x7100c4bc68
ModelUnitGroup::~ModelUnitGroup() {
    mUnits.freeBuffer();
}

}  // namespace gsys
