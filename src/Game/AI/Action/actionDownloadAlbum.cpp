#include "Game/AI/Action/actionDownloadAlbum.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

DownloadAlbum::DownloadAlbum(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DownloadAlbum::~DownloadAlbum() = default;

bool DownloadAlbum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DownloadAlbum::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = 0;
    ui::sub_7100A9ED74();
}

void DownloadAlbum::leave_() {
    ksys::act::ai::Action::leave_();
}

void DownloadAlbum::loadParams_() {}

void DownloadAlbum::calc_() {
    if (ui::sub_7100A9F104())
        setFinished();
    if (_1c == 0) {
        _1c = 1;
    } else if (_1c == 1) {
        ui::sub_7100A9F0CC();
        _1c = _1c + 1;
    }
}

}  // namespace uking::action
