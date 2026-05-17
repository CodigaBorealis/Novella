#pragma once
#include <raylib.h>
#include <type_traits>

namespace Novella{

    enum class WindowFlags : unsigned int{

        None = 0,
        Fullscreen = FLAG_FULLSCREEN_MODE,
        Resizable = FLAG_WINDOW_RESIZABLE,
        Undecorated = FLAG_WINDOW_UNDECORATED,
        Hidden = FLAG_WINDOW_HIDDEN,
        Minimized = FLAG_WINDOW_MINIMIZED,
        Maximized = FLAG_WINDOW_MAXIMIZED,
        Unfocused = FLAG_WINDOW_UNFOCUSED,
        Topmost = FLAG_WINDOW_TOPMOST,
        AlwaysRun = FLAG_WINDOW_ALWAYS_RUN,
        Transparent = FLAG_WINDOW_TRANSPARENT,
        HighDPI = FLAG_WINDOW_HIGHDPI,
        VSync = FLAG_VSYNC_HINT,
        MSAA4X = FLAG_MSAA_4X_HINT,
        Interlaced = FLAG_INTERLACED_HINT
    };

    inline WindowFlags operator|(WindowFlags lhs, WindowFlags rhs){

        return static_cast<WindowFlags>(

            static_cast<unsigned int>(lhs) |
            static_cast<unsigned int>(rhs)
        );
    }

    inline WindowFlags operator&(WindowFlags lhs, WindowFlags rhs){

        return static_cast<WindowFlags>(

            static_cast<unsigned int>(lhs) &
            static_cast<unsigned int>(rhs)
        );
    }

    inline WindowFlags& operator|=(WindowFlags& lhs, WindowFlags rhs){

        lhs = rhs | rhs;

        return lhs;
    }

}