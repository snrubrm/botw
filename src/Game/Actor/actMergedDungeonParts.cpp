#include "Game/Actor/actMergedDungeonParts.h"
#include <basis/seadNew.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
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

// NON_MATCHING: the loop uses a separate matrix pointer and compares the index with 17.
void MergedDungeonParts::updatePositionMaybe() {
    auto* mgr = ksys::phys::System::instance()->getStaticCompoundMgr();
    if (mgr) {
        ksys::phys::StaticCompoundRigidBodyGroup* group = nullptr;
        sead::Matrix34f transform = sead::Matrix34f::ident;
        sead::FixedSafeString<32> name;
        for (int i = 0; i < 17; ++i) {
            group = mgr->getBodyGroup(i - 1);
            if (group)
                transform = mgr->getTransformedMatrix(group, _850[i]);
            if (_b80[i] >= 0) {
                auto* unit = mModel->getUnits().unsafeAt(_b80[i])->mModelUnit;
                if (unit)
                    unit->setBoneLocalMatrix(transform, sead::Vector3f::ones, 0);
            }
        }
    }
    MapConstActiveOrMergedDungeonParts::updatePositionMaybe();
}

}  // namespace uking::act
