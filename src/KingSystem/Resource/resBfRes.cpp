#include "KingSystem/Resource/resBfRes.h"
#include <nn/g3d/ResFile.h>
#include "KingSystem/Resource/resResourceFileUtil.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

// NON_MATCHING: the original stores _41 right after Resource::Resource() and _40 later (ours merges the two bytes into
// one halfword store) and schedules the 0x48 / 0x58 / 0x180 / 0x190 stores differently.
BfRes::BfRes() {
    _138.initOffset(8);
    _150.initOffset(8);
}

BfRes::~BfRes() = default;

s32 BfRes::getLoadDataAlignment() const {
    return 0x1000;
}

bool BfRes::needsParse() const {
    return true;
}

bool BfRes::m2_() {
    return _50 != nullptr;
}

// NON_MATCHING: the alignment warning branch has a different block order.
void BfRes::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {
    u32 alignment = sub_7100FDDB40(buffer)->GetAlignment();
    if ((alignment & 0xfff) && ((alignment + 0x1fff) & 0x1000))
        stubbedLogFunction();
}

void BfRes::onDestroy_() {
    sub_7100FDDB70(sub_7100FDDB40(mRawData));
}

}  // namespace ksys::res
