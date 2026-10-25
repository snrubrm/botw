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

void Awareness::Unk1::sub_7100D7F004(Node* node) {
    if (_8)
        _10->_8 = node;
    else
        _8 = node;
    _10 = node;
    node->_14 = 1;
}

}  // namespace ksys::act
