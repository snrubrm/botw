#pragma once

#include <prim/seadSafeString.h>

namespace sead {
class Heap;

namespace hostio {
class Node;
}
}  // namespace sead

namespace gsys::ORUtil {

enum class Icon {
    _b = 0xB,
};

enum class Category {
    _0 = 0,
    _1 = 1,
    _4 = 4,
};

enum class Attribute {
    _2 = 2,
};

void setNodeMeta(sead::hostio::Node* node, Category category, sead::Heap* heap);
// 0x7100c6bbbc (declared only)
void setNodeMeta(sead::hostio::Node* node, Category category, const sead::SafeString& meta,
                 sead::Heap* heap);
void setNodeMeta(sead::hostio::Node* node, Category category, Attribute attr, sead::Heap* heap);
void setNodeMetaIcon(sead::hostio::Node* node, Icon icon, sead::Heap* heap);

}  // namespace gsys::ORUtil
