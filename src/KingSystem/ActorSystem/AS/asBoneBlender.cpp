#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

BoneBlender::BoneBlender() {}

f32 BoneBlender::m39(s32* a1, s32* a2, void* a3, void* a4) {
    *a1 = 0;
    *a2 = mChildren.size() == 2 ? 1 : -1;
    return 0.01f;
}

}  // namespace ksys::as
