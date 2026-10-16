#include "KingSystem/Sound/Actor/Action/actionPlayerEmitEquipmentNoise.h"
#include "KingSystem/Sound/sndUnk_7102502138.h"

namespace ksys::snd {

PlayerEmitEquipmentNoise::PlayerEmitEquipmentNoise(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerEmitEquipmentNoise::~PlayerEmitEquipmentNoise() = default;

bool PlayerEmitEquipmentNoise::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerEmitEquipmentNoise::loadParams_() {
    getDynamicParam(&mSteppingFoot_d, "SteppingFoot");
    getDynamicParam(&mSpeed_d, "Speed");
}

// NON_MATCHING: `type` sits at sp+0x8 in the original (sp+0xc here); the real type of the 0x710103b3cc argument
// is unknown (maybe an 8-byte object).
bool PlayerEmitEquipmentNoise::oneShot_() {
    s32 type = 1;
    f32 volume;
    if (mSpeed_d == "Dash") {
        type = 3;
        volume = 0.3;
    } else if (mSpeed_d == "Fast") {
        type = 2;
        volume = 0.2;
    } else if (mSpeed_d == "MdlSpd") {
        type = 2;
        volume = 0.15;
    } else {
        volume = 0.05;
    }

    if (mSteppingFoot_d == "Right")
        Unk_7102502138::instance()->sub_710103B384(volume);
    else if (mSteppingFoot_d == "Left")
        Unk_7102502138::instance()->sub_710103B33C(volume);
    else
        Unk_7102502138::instance()->sub_710103B3CC(&type);
    return true;
}

}  // namespace ksys::snd
