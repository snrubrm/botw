#include "Game/AI/AI/aiDungeonRotateTag4WaterApp.h"
#include "Game/UI/uiUtils.h"

namespace uking::ai {

DungeonRotateTag4WaterApp::DungeonRotateTag4WaterApp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonRotateTag4WaterApp::~DungeonRotateTag4WaterApp() = default;

bool DungeonRotateTag4WaterApp::init_(sead::Heap* heap) {
    *mTargetRad_a = 0.0f;
    *mTargetRadMax_a = 0.0f;
    *mTargetRadMin_a = 0.0f;
    return true;
}

// NON_MATCHING: the original does not keep the address of mLv0_s in a register (the other nine are
// hoisted, ours hoists all ten and spills one).
void DungeonRotateTag4WaterApp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
    const float levels[] = {*mLv0_s, *mLv1_s, *mLv2_s, *mLv3_s, *mLv4_s,
                            *mLv5_s, *mLv6_s, *mLv7_s, *mLv8_s, *mLv9_s};
    *mTargetRadMax_a = *mLv9_s;
    *mTargetRadMin_a = *mLv0_s;
    ui::sub_7100A9D1A0(levels);

    const int level = ui::sub_7100A9D290();
    float rad;
    switch (level) {
    case 0:
        rad = *mLv0_s;
        break;
    case 1:
        rad = *mLv1_s;
        break;
    case 2:
        rad = *mLv2_s;
        break;
    case 3:
        rad = *mLv3_s;
        break;
    case 4:
        rad = *mLv4_s;
        break;
    case 5:
        rad = *mLv5_s;
        break;
    case 6:
        rad = *mLv6_s;
        break;
    case 7:
        rad = *mLv7_s;
        break;
    case 8:
        rad = *mLv8_s;
        break;
    case 9:
        rad = *mLv9_s;
        break;
    default:
        rad = 0;
        break;
    }
    *mTargetRad_a = rad;
    _a0 = level;
    changeChild("待機");
}

void DungeonRotateTag4WaterApp::calc_() {
    auto* child = getCurrentChild();
    if (!ui::sub_7100A9BAEC(23) || _a0 == ui::sub_7100A9D290()) {
        if (child->isFinished() || child->isFailed()) {
            if (isCurrentChild("回転"))
                changeChild("待機");
        }
        return;
    }

    const int level = ui::sub_7100A9D290();
    float rad;
    switch (level) {
    case 0:
        rad = *mLv0_s;
        break;
    case 1:
        rad = *mLv1_s;
        break;
    case 2:
        rad = *mLv2_s;
        break;
    case 3:
        rad = *mLv3_s;
        break;
    case 4:
        rad = *mLv4_s;
        break;
    case 5:
        rad = *mLv5_s;
        break;
    case 6:
        rad = *mLv6_s;
        break;
    case 7:
        rad = *mLv7_s;
        break;
    case 8:
        rad = *mLv8_s;
        break;
    case 9:
        rad = *mLv9_s;
        break;
    default:
        rad = 0;
        break;
    }
    *mTargetRad_a = rad;
    _a0 = level;
    if (!isCurrentChild("回転"))
        changeChild("回転");
}

void DungeonRotateTag4WaterApp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTag4WaterApp::loadParams_() {
    getStaticParam(&mLv0_s, "Lv0");
    getStaticParam(&mLv1_s, "Lv1");
    getStaticParam(&mLv2_s, "Lv2");
    getStaticParam(&mLv3_s, "Lv3");
    getStaticParam(&mLv4_s, "Lv4");
    getStaticParam(&mLv5_s, "Lv5");
    getStaticParam(&mLv6_s, "Lv6");
    getStaticParam(&mLv7_s, "Lv7");
    getStaticParam(&mLv8_s, "Lv8");
    getStaticParam(&mLv9_s, "Lv9");
    getAITreeVariable(&mTargetRad_a, "TargetRad");
    getAITreeVariable(&mTargetRadMax_a, "TargetRadMax");
    getAITreeVariable(&mTargetRadMin_a, "TargetRadMin");
}

}  // namespace uking::ai
