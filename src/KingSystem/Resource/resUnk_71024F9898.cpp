#include "KingSystem/Resource/resUnk_71024F9898.h"

namespace ksys::res {

Unk_71024F9898::Unk_71024F9898() = default;
Unk_71024F9898::~Unk_71024F9898() = default;

s32 Unk_71024F9898::getLoadDataAlignment() const {
    return cLoadDataAlignment;
}

bool Unk_71024F9898::needsParse() const {
    return true;
}

bool Unk_71024F9898::m2_() {
    return _40 != nullptr;
}

}  // namespace ksys::res
