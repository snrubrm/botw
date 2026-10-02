#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace ksys::act {

BoneHandleBase::BoneHandleBase() : _8(false), _9(false), _10(nullptr), _18(nullptr) {}

void BoneHandleBase::sub_7100D3BA6C(BoneHandleBase* head, gsys::Model* model) {
    for (auto* handle = head; handle; handle = handle->_18)
        handle->m2(model);
}

bool BoneHandleBase::sub_7100D3BAAC(BoneHandleBase** head, gsys::Model* model, bool sorted) {
    if (_8)
        return false;

    if (!m3(model, sorted))
        return false;

    _9 = sorted;

    if (*head) {
        if (!sorted) {
            BoneHandleBase* first = *head;
            _18 = first;
            first->_10 = this;
        } else {
            BoneHandleBase* prev = nullptr;
            BoneHandleBase* it = *head;
            while (true) {
                const auto* key = m4();
                const auto* other_key = it->m4();
                if (it->_9 && key && other_key &&
                    u16(key->model_unit_index) == u16(other_key->model_unit_index) &&
                    key->bone_index < other_key->bone_index) {
                    if (prev) {
                        prev->_18 = this;
                        _10 = prev;
                    } else {
                        *head = this;
                    }
                    it->_10 = this;
                    _18 = it;
                    _8 = true;
                    return true;
                }
                if (!it->_18)
                    break;
                prev = it;
                it = it->_18;
            }
            it->_18 = this;
            _10 = it;
            _8 = true;
            return true;
        }
    }
    *head = this;
    _8 = true;
    return true;
}

bool BoneHandleBase::sub_7100D3BBD4(BoneHandleBase** head) {
    if (!_8 && !_18 && !_10 && *head != this)
        return false;

    if (*head == this)
        *head = _18;
    if (_18)
        _18->_10 = _10;
    if (_10)
        _10->_18 = _18;
    _10 = nullptr;
    _18 = nullptr;
    _8 = false;
    return true;
}

}  // namespace ksys::act
