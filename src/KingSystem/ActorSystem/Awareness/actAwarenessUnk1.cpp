#include "KingSystem/ActorSystem/Awareness/actAwareness.h"

namespace ksys::act {

void Awareness::Unk1::finalize() {
    while (_8) {
        auto* node = _8;
        _8 = node->_8;
        node->_8 = nullptr;
    }
    _10 = nullptr;
}

}  // namespace ksys::act
