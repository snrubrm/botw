#include "Game/AI/Behavior/behaviorShowRandomMessage3D.h"
#include <random/seadGlobalRandom.h>

namespace uking::behavior {

ShowRandomMessage3D::ShowRandomMessage3D(const InitArg& arg) : ShowMessage3D(arg) {}

ShowRandomMessage3D::~ShowRandomMessage3D() = default;

void ShowRandomMessage3D::m7() {
    ShowMessage3D::m7();
}

void ShowRandomMessage3D::m14(sead::BufferedSafeString* out) {
    if (out) {
        out->clear();
        const u32 width = *mRandomWidth_s;
        const u32 random = sead::GlobalRandom::instance()->getU32(width);
        out->format("%s_%02d", mLabelName_s.cstr(), random);
    }
}

void ShowRandomMessage3D::loadParams() {
    ShowMessage3D::loadParams();
    getStaticParam(&mRandomWidth_s, "RandomWidth");
}

}  // namespace uking::behavior
