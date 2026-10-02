#include "Game/AI/AI/aiKorokFlowerColorRoot.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

KorokFlowerColorRoot::KorokFlowerColorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokFlowerColorRoot::~KorokFlowerColorRoot() = default;

bool KorokFlowerColorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokFlowerColorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;

    as_list->startAnimationMaybe(-1.0f, -1.0f, "Wait", 0, 0, true);
    if (mActor->checkBasicSig()) {
        _40 = true;
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, 1.0f);
    } else {
        _40 = false;
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, 0.0f);
    }
}

void KorokFlowerColorRoot::calc_() {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;

    if (mActor->checkBasicSig()) {
        if (!_40) {
            _40 = true;
            xlinkSearchAndEmit(mActor, "Change", 2, &_48);
            switch (*mKorokFlowerColorNum_m) {
            case 1:
                xlinkSearchAndEmit(mActor, "ChangeColor_00", 2, &_48);
                break;
            case 2:
                xlinkSearchAndEmit(mActor, "ChangeColor_01", 2, &_48);
                break;
            case 3:
                xlinkSearchAndEmit(mActor, "ChangeColor_02", 2, &_48);
                break;
            case 4:
                xlinkSearchAndEmit(mActor, "ChangeColor_03", 2, &_48);
                break;
            case 5:
                xlinkSearchAndEmit(mActor, "ChangeColor_04", 2, &_48);
                break;
            default:
                break;
            }
        }
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, 1.0f);
    } else {
        if (_40) {
            _40 = false;
            xlinkSearchAndEmit(mActor, "Change", 2, &_48);
            xlinkSearchAndEmit(mActor, "ChangeColor_Failed", 2, &_48);
        }
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, 0.0f);
    }
}

void KorokFlowerColorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokFlowerColorRoot::loadParams_() {
    getMapUnitParam(&mKorokFlowerColorNum_m, "KorokFlowerColorNum");
}

}  // namespace uking::ai
