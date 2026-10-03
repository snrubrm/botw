#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>

namespace sead {
class LookAtCamera;
class Viewport;
}  // namespace sead

namespace ksys {

// 0x7100d8c4f8 (declaration only, free function): forwards `pos` to the look-at camera (0x7100d8afcc);
// false without a camera. Placeholder name (CameraMgr::instance() is used).
bool sub_7100D8C4F8(const sead::Vector3f& pos);
// 0x7100d8c7fc (declaration only, free function): writes the negated look vector of the look-at camera
// to `out` (zero without a camera); false when `out` is null or there is no camera. Placeholder name.
bool sub_7100D8C7FC(sead::Vector3f* out);

// FIXME: incomplete
class CameraMgr : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(CameraMgr)
    CameraMgr() = default;
    virtual ~CameraMgr() = default;

public:
    sead::LookAtCamera* getLookAtCamera() const;
    // 0x7100d8c4c8 (CSV Camera::__auto7): like getLookAtCamera, forwards to the object at +0x28.
    const sead::Viewport* sub_7100D8C4C8() const;
};

}  // namespace ksys
