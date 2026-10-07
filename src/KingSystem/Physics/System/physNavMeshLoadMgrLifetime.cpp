#include "KingSystem/Physics/System/physHavokAI.h"

namespace ksys::phys {

NavMeshLoadMgr::NavMeshLoadMgr()
    : _8(0), _10(nullptr), _170(sead::Vector2i::zero), _178(sead::Vector2i::zero),
      _180(sead::Vector2i::zero), _188(-1, -1), _190(false) {}

NavMeshLoadMgr::~NavMeshLoadMgr() {
    sub_7100F898E4();
}

}  // namespace ksys::phys
