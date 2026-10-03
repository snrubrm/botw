#include "KingSystem/Physics/System/physHavokAI.h"

namespace ksys::phys {

void HavokAI::destroyQuery(Unk_7102372790* query) {
    _40->sub_71012A9EE8(query);
}

void HavokAI::sub_7100F83A94(Unk_7102372790* query) {
    _40->sub_71012AA000(query);
}

bool HavokAI::submitQuery(Unk_7102372790* query) {
    return _40->sub_71012A9F68(query);
}

}  // namespace ksys::phys
