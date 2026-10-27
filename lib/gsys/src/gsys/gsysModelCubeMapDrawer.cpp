#include "gsys/gsysModelCubeMapDrawer.h"

namespace gsys {

// 0x7100c7d950
void ModelCubeMapDrawer::update() {
    mQueue0.sort();
    mQueue1.sort();
}

// 0x7100c7dcc8
ModelCubeMapDrawer::CreateArg::~CreateArg() {}

}  // namespace gsys
