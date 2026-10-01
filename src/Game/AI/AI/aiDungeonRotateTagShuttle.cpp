#include "Game/AI/AI/aiDungeonRotateTagShuttle.h"

namespace uking::ai {

DungeonRotateTagShuttle::DungeonRotateTagShuttle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonRotateTagShuttle::~DungeonRotateTagShuttle() = default;

bool DungeonRotateTagShuttle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRotateTagShuttle::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 rad = *mInitDgnRotRad_m;
    if (rad <= 0.0f) {
        changeChild("時計回り回転後待機");
    } else if (rad > 0.0f) {
        changeChild("反時計回り回転後待機");
    }
    _40 = false;
}

void DungeonRotateTagShuttle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTagShuttle::loadParams_() {
    getMapUnitParam(&mInitDgnRotRad_m, "InitDgnRotRad");
}

}  // namespace uking::ai
