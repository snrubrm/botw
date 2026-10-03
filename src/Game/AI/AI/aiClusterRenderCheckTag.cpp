#include "Game/AI/AI/aiClusterRenderCheckTag.h"

namespace uking::ai {

ClusterRenderCheckTag::ClusterRenderCheckTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ClusterRenderCheckTag::~ClusterRenderCheckTag() = default;

bool ClusterRenderCheckTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ClusterRenderCheckTag::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("オフ");
    _58 = false;
    _38.bind(this, &ClusterRenderCheckTag::sub_710035404C);
    mFlags.set(Flag::Changeable);
}

bool ClusterRenderCheckTag::sub_710035404C(ClusterInfo* cluster) {
    if (cluster->_80)
        return !_58;
    _58 = true;
    return false;
}

void ClusterRenderCheckTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ClusterRenderCheckTag::loadParams_() {}

}  // namespace uking::ai
