#include "Game/AI/Action/actionDownloadPictureBook.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

DownloadPictureBook::DownloadPictureBook(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DownloadPictureBook::~DownloadPictureBook() = default;

bool DownloadPictureBook::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DownloadPictureBook::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = 0;
    ui::sub_7100A9ED74();
}

void DownloadPictureBook::leave_() {
    ksys::act::ai::Action::leave_();
}

void DownloadPictureBook::loadParams_() {}

void DownloadPictureBook::calc_() {
    if (_1c == 2) {
        if (ui::sub_7100A9F134())
            setFinished();
    }
    if (_1c == 0) {
        _1c = 1;
    } else if (_1c == 1) {
        ui::sub_7100A9F108();
        _1c = _1c + 1;
    }
}

}  // namespace uking::action
