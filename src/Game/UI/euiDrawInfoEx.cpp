#include "Game/UI/euiScreen.h"

namespace eui {

// 0x7100bf2ab0
void DrawInfoEx::freeDynamicTexture() {
    for (auto it = mDynamicTextures.begin(); it != mDynamicTextures.end();) {
        const auto current = it++;
        current->freeDynamicTexture();
        mDynamicTextures.erase(current);
    }
}

}  // namespace eui
