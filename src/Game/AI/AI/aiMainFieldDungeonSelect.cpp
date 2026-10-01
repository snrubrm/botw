#include "Game/AI/AI/aiMainFieldDungeonSelect.h"
#include "Game/gameScene.h"

namespace uking::ai {

MainFieldDungeonSelect::MainFieldDungeonSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MainFieldDungeonSelect::~MainFieldDungeonSelect() = default;

bool MainFieldDungeonSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MainFieldDungeonSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::SafeString map_name = GameScene::getCurrentMapName();
    if (map_name.include("RemainsWind"))
        changeChild("風の遺物");
    else if (map_name.include("RemainsElectric"))
        changeChild("電気の遺物");
    else if (map_name.include("RemainsWater"))
        changeChild("水の遺物");
    else if (map_name.include("RemainsFire"))
        changeChild("火の遺物");
    else if (map_name.include("FinalTrial"))
        changeChild("その他");
    else
        changeChild("風の遺物");
}

void MainFieldDungeonSelect::calc_() {}

void MainFieldDungeonSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MainFieldDungeonSelect::loadParams_() {}

}  // namespace uking::ai
