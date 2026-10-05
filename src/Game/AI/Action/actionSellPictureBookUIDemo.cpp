#include "Game/AI/Action/actionSellPictureBookUIDemo.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

SellPictureBookUIDemo::SellPictureBookUIDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SellPictureBookUIDemo::~SellPictureBookUIDemo() = default;

bool SellPictureBookUIDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SellPictureBookUIDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mSellPicturePack_d) {
        ui::createAndLoadScreenIfNeededImpl(ui::ScreenId::AppPictureBook, nullptr);
        ui::sellPictureBookDemo(*mSellPicturePack_d);
    }
    _28 = 0;
}

void SellPictureBookUIDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void SellPictureBookUIDemo::loadParams_() {
    getDynamicParam(&mSellPicturePack_d, "SellPicturePack");
}

void SellPictureBookUIDemo::calc_() {
    sub_7100738488(mActor, 0.f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.f);
    if (isFinished() || isFailed())
        return;
    if (_28 == 1) {
        ui::sellPictureBookUIEnd();
    } else if (_28 != 0 && ui::sellPictureBookUIEnd2()) {
        setFinished();
        mFlags.set(Flag::Changeable);
    }
    ++_28;
}

}  // namespace uking::action
