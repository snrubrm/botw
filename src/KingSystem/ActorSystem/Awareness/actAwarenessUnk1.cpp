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

void Awareness::Unk1::sub_7100D7F02C(Node* node) {
    if (!_8)
        return;

    if (_8 == node) {
        _8 = node->_8;
        if (_10 == node)
            _10 = nullptr;
    } else {
        auto* prev = _8;
        for (auto* n = _8->_8; n; prev = n, n = n->_8) {
            if (n != node)
                continue;
            prev->_8 = node->_8;
            if (_10 == node) {
                _10 = prev;
                break;
            }
        }
    }

    node->_8 = nullptr;
    node->_14 = 0;
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
