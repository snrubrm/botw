#include "KingSystem/Physics/SupportBone/physSupportBoneResource.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace ksys::phys {

s32 SupportBoneInstanceMaybe::sub_71012273A8(const sead::SafeString& name) const {
    if (!mResource)
        return -1;
    return mResource->getSupportBoneIndexByName(name);
}

}  // namespace ksys::phys
