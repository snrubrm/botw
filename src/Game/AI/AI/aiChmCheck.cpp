#include "Game/AI/AI/aiChmCheck.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

ChmCheck::ChmCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChmCheck::~ChmCheck() = default;

bool ChmCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChmCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    bool on = false;
    if (auto* chemical = mActor->sub_71011D8A44(0)) {
        switch (*mChmType_s) {
        case 0:
            on = chemical->_1b8 > 0;
            break;
        case 1:
            on = chemical->_90->_7c > 0;
            break;
        case 2:
            on = (chemical->_bc & 8) || (chemical->_90->_12 & 2);
            break;
        }
    }
    if (on)
        changeChild("オン");
    else
        changeChild("オフ");
    mFlags.set(Flag::Changeable);
}

void ChmCheck::calc_() {
    bool on = false;
    if (auto* chemical = mActor->sub_71011D8A44(0)) {
        switch (*mChmType_s) {
        case 0:
            on = chemical->_1b8 > 0;
            break;
        case 1:
            on = chemical->_90->_7c > 0;
            break;
        case 2:
            on = (chemical->_bc & 8) || (chemical->_90->_12 & 2);
            break;
        }
    }
    if (on) {
        if (!isCurrentChild("オン"))
            changeChild("オン");
    } else {
        if (!isCurrentChild("オフ"))
            changeChild("オフ");
    }
}

void ChmCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChmCheck::loadParams_() {
    getStaticParam(&mChmType_s, "ChmType");
}

}  // namespace uking::ai
