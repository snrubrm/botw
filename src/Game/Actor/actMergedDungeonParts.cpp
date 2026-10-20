#include "Game/Actor/actMergedDungeonParts.h"
#include <basis/seadNew.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/Physics/System/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace uking::act {

MergedDungeonParts::MergedDungeonParts(const CreateArg& arg)
    : MapConstActiveOrMergedDungeonParts(arg) {
    for (int i = 0; i < 17; ++i)
        _850[i] = sead::Matrix34f::ident;
    for (int i = 0; i < 17; ++i)
        _b80[i] = -1;
}

ksys::act::BaseProc* MergedDungeonParts::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) MergedDungeonParts(arg);
}

MergedDungeonParts::~MergedDungeonParts() = default;

bool MergedDungeonParts::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return MapConstActiveOrMergedDungeonParts::prepareInit_(heap, arg);
}

void MergedDungeonParts::onPreDeleteStart_(PrepareArg& arg) {
    MapConstActiveOrMergedDungeonParts::onPreDeleteStart_(arg);
}

// NON_MATCHING: map-parameter pointer stack slots and one format-argument scheduling difference.
void MergedDungeonParts::m63() {
    MapConstActiveOrMergedDungeonParts::m63();
    sub_71007394E8(this);
    for (s32 i = 0; i < 17; ++i)
        _850[i] = sead::Matrix34f::ident;
    for (auto& index : _b80)
        index = -1;

    sead::FixedSafeString<32> unit_name;
    sead::FixedSafeString<32> position_name;
    sead::FixedSafeString<32> rotation_name;
    for (s32 i = 0; i < 17; ++i) {
        if (i == 0) {
            _b80[i] = mModel->searchUnitIndex("Base");
            continue;
        }
        const s32 group_index = i - 1;
        position_name.format("TransFieldBodyGroup");
        position_name.appendWithFormat("%02d", group_index);
        rotation_name.format("RotateFieldBodyGroup");
        rotation_name.appendWithFormat("%02d", group_index);
        const sead::Vector3f* position;
        const sead::Vector3f* rotation;
        getRootAi()->getMapUnitParam(&position, position_name);
        getRootAi()->getMapUnitParam(&rotation, rotation_name);
        const sead::Vector3f angles = *rotation * sead::Mathf::deg2rad(1.0f);
        unit_name.format("Group");
        unit_name.appendWithFormat("%02d", group_index);
        _b80[i] = mModel->searchUnitIndex(unit_name);
        _850[i].makeRT(angles, *position);
    }
}

void MergedDungeonParts::initMaybe() {
    MapConstActiveOrMergedDungeonParts::initMaybe();
}

void MergedDungeonParts::calcMaybe() {
    MapConstActiveOrMergedDungeonParts::calcMaybe();
}

void MergedDungeonParts::updatePositionMaybe() {
    auto* mgr = ksys::phys::System::instance()->getStaticCompoundMgr();
    if (mgr) {
        ksys::phys::StaticCompoundRigidBodyGroup* group = nullptr;
        sead::Matrix34f transform = sead::Matrix34f::ident;
        sead::FixedSafeString<32> name;
        int i = 0;
        for (const auto& matrix : _850) {
            group = mgr->getBodyGroup(i - 1);
            if (group)
                transform = mgr->getTransformedMatrix(group, matrix);
            if (_b80[i] >= 0) {
                auto* unit = mModel->getUnits().unsafeAt(_b80[i])->mModelUnit;
                if (unit)
                    unit->setBoneLocalMatrix(transform, sead::Vector3f::ones, 0);
            }
            ++i;
        }
    }
    MapConstActiveOrMergedDungeonParts::updatePositionMaybe();
}

}  // namespace uking::act
