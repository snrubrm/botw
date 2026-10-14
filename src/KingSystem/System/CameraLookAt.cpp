#include "KingSystem/System/CameraS1.h"
#include "KingSystem/Camera/CameraMgr.h"
#include <geom/seadFrustum.h>

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

bool Unk_71024dd110::sub_7100D8AFCC(const sead::Vector3f& pos) {
    return sub_7100D8B080(pos, _6c, _70);
}

bool Unk_71024dd110::sub_7100D8B080(const sead::Vector3f& pos, f32 near_clip,
                                  f32 far_clip) const {
    if (_74 >= sead::Mathf::pi())
        return false;
    const f32 aspect = CameraMgr::instance()->sub_7100D8C4E8()->getAspect();
    sead::Frustum frustum;
    frustum.set(getMatrix(), _74, aspect, near_clip, far_clip);
    return frustum.isInside(pos, 0.0f, frustum.getNear(), frustum.getFar());
}

bool Unk_71024dd110::sub_7100D8B138(const sead::Vector3f& pos, f32 radius,
                                  f32 near_clip, f32 far_clip) const {
    if (_74 >= sead::Mathf::pi())
        return false;
    const f32 aspect = CameraMgr::instance()->sub_7100D8C4E8()->getAspect();
    sead::Frustum frustum;
    frustum.set(getMatrix(), _74, aspect, near_clip, far_clip);
    return frustum.isInside(pos, radius, frustum.getNear(), frustum.getFar());
}

bool Unk_71024dd110::sub_7100D8B1F4(const sead::Vector3f& pos, f32 radius) const {
    return sub_7100D8B138(pos, radius, _6c, _70);
}

// NON_MATCHING: the camera clip fields load after the aspect query and frustum construction.
bool Unk_71024dd110::sub_7100D8B2AC(const sead::Vector3f& pos, f32 radius) const {
    if (_74 >= sead::Mathf::pi())
        return false;
    const f32 aspect = CameraMgr::instance()->sub_7100D8C4F0()->getAspect();
    sead::Frustum frustum;
    frustum.set(getMatrix(), _74, aspect, _6c, _70);
    return frustum.isInside(pos, radius, frustum.getNear(), frustum.getFar());
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
