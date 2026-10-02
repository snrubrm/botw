#include "Game/AI/Behavior/behaviorShowRandomMessage3D.h"

namespace uking::behavior {

ShowRandomMessage3D::ShowRandomMessage3D(const InitArg& arg) : ShowMessage3D(arg) {}

ShowRandomMessage3D::~ShowRandomMessage3D() = default;

void ShowRandomMessage3D::m7() {
    ShowMessage3D::m7();
}

void ShowRandomMessage3D::loadParams() {
    ShowMessage3D::loadParams();
    getStaticParam(&mRandomWidth_s, "RandomWidth");
}

}  // namespace uking::behavior
