#include "Game/AI/Action/actionFromCDungeonToMainField.h"
#include "Game/gameScene.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/StageInfo.h"

namespace uking::action {

FromCDungeonToMainField::FromCDungeonToMainField(const InitArg& arg) : ChangeSceneBase(arg) {}

FromCDungeonToMainField::~FromCDungeonToMainField() = default;

bool FromCDungeonToMainField::init_(sead::Heap* heap) {
    return ChangeSceneBase::init_(heap);
}

void FromCDungeonToMainField::enter_(ksys::act::ai::InlineParamPack* params) {
    ChangeSceneBase::enter_(params);
    if (isFinished() || isFailed())
        return;

    const auto* manager = ksys::evt::Manager::instance();
    if (manager->_1d2f4_bytes[0] & 0x20) {
        setFinished();
        return;
    }

    sead::FixedSafeString<64> map;
    sead::FixedSafeString<64> pos;
    if (ksys::StageInfo::sIsCDungeon)
        ::changeSceneForCDungeonToMainField(_48, &map, &pos);
    else if (ksys::StageInfo::sIsMainFieldDungeon)
        ::changeSceneForDungeonToMainField(_48, &map, &pos);
    else
        ::changeSceneForCDungeonToMainField(_48, &map, &pos);
    initWarpEventFlow(map, pos);
}

void FromCDungeonToMainField::leave_() {
    ChangeSceneBase::leave_();
}

void FromCDungeonToMainField::loadParams_() {
    ChangeSceneBase::loadParams_();
}

void FromCDungeonToMainField::calc_() {
    ChangeSceneBase::calc_();
}

}  // namespace uking::action
