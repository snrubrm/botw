#include "KingSystem/System/CameraS1.h"
#include "KingSystem/System/CameraMgr.h"

namespace ksys {

// NON_MATCHING: constructor stores are scheduled differently around the vtables and fixed list.
Unk_71024dd110::Unk_71024dd110() {
    sead::LookAtCamera::doUpdateMatrix(&getMatrix());
}

// NON_MATCHING: listener iteration keeps object pointers instead of the original list-node pointers.
Unk_71024dd110::~Unk_71024dd110() {
    if (!_80.isEmpty()) {
        for (auto it = _80.begin(); it != _80.end();) {
            const auto& listener = *it;
            // The selector callback can remove this listener, so advance before calling it.
            ++it;
            switch (listener.id) {
            case 0:
                CameraMgr::instance()->sub_7100D8C498(listener.index);
                break;
            case 1:
                CameraMgr::instance()->sub_7100D8C4A0(listener.index);
                break;
            }
        }
        _80.clear();
    }
}

void Unk_71024dd110::sub_7100D8B364(bool active) {
    _68.changeBit(0, active);
}

void Unk_71024dd110::sub_7100D8B380(s32 id, s32 index) {
    if (!_80.isFull())
        _80.emplaceBack(Listener{id, index});
}

// NON_MATCHING: the iterator advances an object pointer; the original keeps the next list node.
void Unk_71024dd110::sub_7100D8B3E8(s32 id) {
    for (auto it = _80.begin(); it != _80.end();) {
        Listener* listener = &*it;
        ++it;
        if (listener->id == id)
            _80.erase(listener);
    }
}

}  // namespace ksys
