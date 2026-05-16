#pragma once

#ifdef __linux_//For now i leave it like this to shut up clangd

    #error "Windows-specific header cannot be included in linux build."

#endif

namespace Novella::Platform::Windows{

}