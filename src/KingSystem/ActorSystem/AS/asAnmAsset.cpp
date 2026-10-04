#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

f32 AnmAsset::m4() {
    return _c;
}

int AnmAsset::m6() {
    return _a;
}

int AnmAsset::m7() {
    return _a >= 0 ? _a : 1;
}

}  // namespace ksys::as
