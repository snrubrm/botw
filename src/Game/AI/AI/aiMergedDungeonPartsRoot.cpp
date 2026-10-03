#include "Game/AI/AI/aiMergedDungeonPartsRoot.h"

namespace uking::ai {

MergedDungeonPartsRoot::MergedDungeonPartsRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MergedDungeonPartsRoot::~MergedDungeonPartsRoot() = default;

bool MergedDungeonPartsRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MergedDungeonPartsRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("通常");
}

void MergedDungeonPartsRoot::calc_() {}

void MergedDungeonPartsRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MergedDungeonPartsRoot::loadParams_() {
    getMapUnitParam(&mParams.mTransFieldBodyGroup00_m, "TransFieldBodyGroup00");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup00_m, "RotateFieldBodyGroup00");
    getMapUnitParam(&mParams.mTransFieldBodyGroup01_m, "TransFieldBodyGroup01");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup01_m, "RotateFieldBodyGroup01");
    getMapUnitParam(&mParams.mTransFieldBodyGroup02_m, "TransFieldBodyGroup02");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup02_m, "RotateFieldBodyGroup02");
    getMapUnitParam(&mParams.mTransFieldBodyGroup03_m, "TransFieldBodyGroup03");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup03_m, "RotateFieldBodyGroup03");
    getMapUnitParam(&mParams.mTransFieldBodyGroup04_m, "TransFieldBodyGroup04");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup04_m, "RotateFieldBodyGroup04");
    getMapUnitParam(&mParams.mTransFieldBodyGroup05_m, "TransFieldBodyGroup05");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup05_m, "RotateFieldBodyGroup05");
    getMapUnitParam(&mParams.mTransFieldBodyGroup06_m, "TransFieldBodyGroup06");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup06_m, "RotateFieldBodyGroup06");
    getMapUnitParam(&mParams.mTransFieldBodyGroup07_m, "TransFieldBodyGroup07");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup07_m, "RotateFieldBodyGroup07");
    getMapUnitParam(&mParams.mTransFieldBodyGroup08_m, "TransFieldBodyGroup08");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup08_m, "RotateFieldBodyGroup08");
    getMapUnitParam(&mParams.mTransFieldBodyGroup09_m, "TransFieldBodyGroup09");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup09_m, "RotateFieldBodyGroup09");
    getMapUnitParam(&mParams.mTransFieldBodyGroup10_m, "TransFieldBodyGroup10");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup10_m, "RotateFieldBodyGroup10");
    getMapUnitParam(&mParams.mTransFieldBodyGroup11_m, "TransFieldBodyGroup11");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup11_m, "RotateFieldBodyGroup11");
    getMapUnitParam(&mParams.mTransFieldBodyGroup12_m, "TransFieldBodyGroup12");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup12_m, "RotateFieldBodyGroup12");
    getMapUnitParam(&mParams.mTransFieldBodyGroup13_m, "TransFieldBodyGroup13");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup13_m, "RotateFieldBodyGroup13");
    getMapUnitParam(&mParams.mTransFieldBodyGroup14_m, "TransFieldBodyGroup14");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup14_m, "RotateFieldBodyGroup14");
    getMapUnitParam(&mParams.mTransFieldBodyGroup15_m, "TransFieldBodyGroup15");
    getMapUnitParam(&mParams.mRotateFieldBodyGroup15_m, "RotateFieldBodyGroup15");
}

}  // namespace uking::ai
