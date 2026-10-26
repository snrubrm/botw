#include <gsys/gsysCameraAnimation.h>
#include <gsys/gsysModelProceduralShape.h>

namespace gsys {

// 0x71014099f8: the two delegate members default-construct to their UnbindDummy tables.
ModelProceduralShape::ModelProceduralShape() = default;

// 0x7101409a28: the members have no destructor; the original body is empty.
ModelProceduralShape::~ModelProceduralShape() {}

void CameraAnimation::sub_71014092F8(CameraAnimation* animation) {
    delete animation;
}
}  // namespace gsys
