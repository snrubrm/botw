#include "KingSystem/Physics/System/physHavokAI.h"

namespace ksys::phys {

void HavokAI::destroyQuery(Unk_7102372790* query) {
    _40->sub_71012A9EE8(query);
}

bool HavokAI::submitQuery(Unk_7102372790* query) {
    return _40->sub_71012A9F68(query);
}

}  // namespace ksys::phys
