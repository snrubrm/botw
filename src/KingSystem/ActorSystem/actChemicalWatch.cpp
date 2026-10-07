#include "KingSystem/ActorSystem/actChemical.h"

namespace ksys::act {

// NON_MATCHING: the original counts the remaining pointer bytes in its search loop.
void Unk_ChemicalWatch::sub_7100D99760(Chemical* chemical) {
    const s32 index = mChemicals.indexOf(chemical);
    if (index != -1)
        mChemicals.erase(index);
}

}  // namespace ksys::act
