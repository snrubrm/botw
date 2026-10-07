#include "KingSystem/Resource/resResDerived.h"
#include "KingSystem/Resource/resBfRes.h"

namespace ksys::res {

ResDerived::ResDerived() = default;

ResDerived::~ResDerived() = default;

BfRes* ResDerived::getModelRes() {
    return sead::DynamicCast<BfRes>(getResource());
}

void* ResDerived::sub_71011FC6AC() {
    auto* res = sead::DynamicCast<BfRes>(getResource());
    return res ? res->_50 : nullptr;
}

void* ResDerived::sub_71011FC73C() {
    return static_cast<BfRes*>(getResourceUnchecked())->_50;
}

}  // namespace ksys::res
