#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>

namespace sead {
class LookAtCamera;
class Viewport;
}  // namespace sead

namespace ksys {

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
