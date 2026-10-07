#include "KingSystem/Resource/resUnk_710251A740.h"

namespace ksys::res {

// 0x7100fddb40: ResCast(data), invokes the embedded resource query, returns the original ResFile.
nn::g3d::ResFile* sub_7100FDDB40(void* data);

Unk_710251A740::Unk_710251A740() = default;
Unk_710251A740::~Unk_710251A740() = default;

bool Unk_710251A740::needsParse() const {
    return true;
}

bool Unk_710251A740::parse_(u8* data, size_t, sead::Heap*) {
    _38 = sub_7100FDDB40(data);
    return true;
}

}  // namespace ksys::res
