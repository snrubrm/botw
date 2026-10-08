#include "Game/Damage/dmgClothStiffnessMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/Cloth/physClothParam.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourcePhysics.h"

namespace uking::dmg {

ClothStiffnessMgr::Entry* ClothStiffnessMgr::sub_7100665830(const sead::SafeString& name) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (auto& entry : mEntries) {
        if (entry.mRefCount > 0 && entry.mKey == name)
            return &entry;
    }
    return nullptr;
}

void ClothStiffnessMgr::sub_7100665A84(ksys::act::Actor* actor) {
    const sead::SafeString name =
        actor->getParam()->getRes().mPhysics->getParamSet().cloth_set->cloth_setup_file_path.ref();
    auto* physics = actor->getPhysics();
    if (!physics)
        return;
    auto* cloth_set = physics->getClothSet();
    if (!cloth_set || !cloth_set->_8)
        return;
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (auto* entry = sub_7100665830(name)) {
        if (--entry->mRefCount == 0)
            entry->mHandle.requestUnload();
    }
}

void ClothStiffnessMgr::sub_7100665B20() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mEntries[0]._a8 = nullptr;
    mEntries[0].mRefCount = 0;
    mEntries[1]._a8 = nullptr;
    mEntries[1].mRefCount = 0;
    mEntries[2]._a8 = nullptr;
    mEntries[2].mRefCount = 0;
}

}  // namespace uking::dmg
