#include "KingSystem/Resource/resBfRes.h"
#include <nn/g3d/ResFile.h>
#include "KingSystem/Resource/resResourceFileUtil.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

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
