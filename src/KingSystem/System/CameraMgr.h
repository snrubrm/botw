#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include "KingSystem/System/CameraS1.h"

namespace sead {
class LookAtCamera;
class Viewport;
}  // namespace sead

namespace ksys {

// 0x7100d8c4f8 (declaration only, free function): forwards `pos` to the look-at camera (0x7100d8afcc);
// false without a camera. Placeholder name (CameraMgr::instance() is used).
bool sub_7100D8C4F8(const sead::Vector3f& pos);
// 0x7100d8c6ac (lane1 s22, placeholder name; CSV cam::getCameraPositionMaybe): writes the look-at
// camera's position to `out` (zero without a camera); false without a camera.
bool sub_7100D8C6AC(sead::Vector3f* out);
// 0x7100d8c71c / 0x7100d8c78c (placeholder names): same for the look-at camera's target / up vector.
bool sub_7100D8C71C(sead::Vector3f* out);
bool sub_7100D8C78C(sead::Vector3f* out);
// 0x7100d8c7fc (free function): writes the negated look vector of the look-at camera
// to `out` (zero without a camera); false when `out` is null or there is no camera. Placeholder name.
bool sub_7100D8C7FC(sead::Vector3f* out);
// 0x7100d8c8fc: aspect ratio of the CameraMgr viewport (1 without one). Placeholder name.
f32 sub_7100D8C8FC();

class CameraMgr : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(CameraMgr)
    CameraMgr() : _28(0), _118(1) {}
    virtual ~CameraMgr();

public:
    struct InitArg {
        s32 _0;
        s32 _4;
    };
    bool init(const InitArg& arg);
    void sub_7100D8C484();
    void sub_7100D8C488(s32 index, Unk_71024dd110* camera);
    void sub_7100D8C490(s32 index, Unk_71024dd110* camera);
    void sub_7100D8C498(s32 index);
    void sub_7100D8C4A0(s32 index);
    void sub_7100D8C4A8(s32 index);
    void sub_7100D8C4B0(s32 index);
    sead::LookAtCamera* getLookAtCamera() const;
    Unk_71024dd110* sub_7100D8C4C0() const;
    // 0x7100d8c4c8 (CSV Camera::__auto7): like getLookAtCamera, forwards to the object at +0x28.
    const sead::Viewport* sub_7100D8C4C8() const;
    s32 sub_7100D8C4D0() const;
    void sub_7100D8C4D8();
    void sub_7100D8C4E0();
    sead::PerspectiveProjection* sub_7100D8C4E8();
    sead::PerspectiveProjection* sub_7100D8C4F0();

private:
    // createInstance constructs these at +0x28/+0x118 with selector ids 0/1.
    CameraS1 _28;
    CameraS1 _118;
};
KSYS_CHECK_SIZE_NX150(CameraMgr, 0x208);

}  // namespace ksys
