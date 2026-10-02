#include "Game/AI/AI/aiNpcTebaTrainingRoot.h"
#include <prim/seadSafeString.h>
#include "Game/gameFlagUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::ai {

NpcTebaTrainingRoot::NpcTebaTrainingRoot(const InitArg& arg) : NPCRoot(arg) {}

NpcTebaTrainingRoot::~NpcTebaTrainingRoot() = default;

bool NpcTebaTrainingRoot::init_(sead::Heap* heap) {
    return NPCRoot::init_(heap);
}

void NpcTebaTrainingRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
    _238.sub_7100721830(mActor, true);
    _238._c8 = false;
    changeAS("Teba_DamageVisibility_On", true, 3, 0);
}

void NpcTebaTrainingRoot::calc_() {
    NPCRoot::calc_();
    s32 value;
    if (!ksys::gdt::getBoolByKey("Wind_Relic_Finished") &&
        getFlagInt(&value, "Wind_Relic_BreakTarget") && value <= 4) {
        sead::FixedSafeString<64> label;
        label.format("%s_%02d", "BreakTarget", value - 1);
        _238.sub_7100721B1C(0.0f, label);
    }
    _238.sub_7100721C48();
}

void NpcTebaTrainingRoot::leave_() {
    NPCRoot::leave_();
}

void NpcTebaTrainingRoot::loadParams_() {
    NPCRoot::loadParams_();
}

}  // namespace uking::ai
