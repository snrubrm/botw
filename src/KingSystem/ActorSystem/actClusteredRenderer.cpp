#include "KingSystem/ActorSystem/actClusteredRenderer.h"
#include <gsys/gsysModel.h>

namespace ksys::act {

// NON_MATCHING: the compiler folds the positive countdown test into the decrement.
void ClusteredRenderer::requestDraw() {
    if ((_c9c & 0x22) == 0x22) {
        if (_c44 > 0)
            --_c44;
        else
            _108->requestDraw();
    }
    _c3c = _c38;
}

}  // namespace ksys::act
