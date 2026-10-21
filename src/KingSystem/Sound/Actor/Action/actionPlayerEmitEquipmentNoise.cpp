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

bool PlayerEmitEquipmentNoise::oneShot_() {
    Unk_710251b170::Strength type = Unk_710251b170::Strength::Weak;
    f32 volume;
    if (mSpeed_d == "Dash") {
        type = Unk_710251b170::Strength::Strong;
        volume = 0.3;
    } else if (mSpeed_d == "Fast") {
        type = Unk_710251b170::Strength::Middle;
        volume = 0.2;
    } else if (mSpeed_d == "MdlSpd") {
        type = Unk_710251b170::Strength::Middle;
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
