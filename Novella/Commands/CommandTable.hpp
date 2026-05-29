#pragma once
#include "Alias.hpp"
#include "AudioCommands.hpp"
#include "CommandEntry.hpp"
#include "InputCommands.hpp"
#include "SceneCommands.hpp"
#include "TransformationCommands.hpp"
#include "WindowCommands.hpp"
#include <array>

namespace Novella{

    static const std::array<CommandEntry, 23> commandTable{{

        {Alias::PlaySound, Commands::playSound},
        {Alias::PlayMusic, Commands::playMusic},
        {Alias::StopSound, Commands::stopSound},
        {Alias::StopMusic, Commands::stopMusic},
        {Alias::SetMousePosition, Commands::setMousePosition},
        {Alias::ShowCursor, Commands::showCursor},
        {Alias::HideCursor, Commands::hideCursor},
        {Alias::EnableCursor, Commands::enableCursor},
        {Alias::DisableCursor, Commands::disableCursor},
        {Alias::ChangeScene, Commands::changeScene},
        {Alias::SpawnObject, Commands::spawnObject},
        {Alias::RemoveObject, Commands::RemoveObject},
        {Alias::Resize, Commands::resize},
        {Alias::Move, Commands::move},
        {Alias::SetPosition, Commands::setPosition},
        {Alias::SetColor, Commands::setColor},
        {Alias::SetTransparency, Commands::setTransparency},
        {Alias::SetText, Commands::setText},
        {Alias::SetWindowTitle, Commands::setWindowTitle},
        {Alias::SetWindowIcon, Commands::setWindowIcon},
        {Alias::SetWindowPosition, Commands::setWindowPosition},
        {Alias::SetWindowSize, Commands::setWindowSize},
        {Alias::CloseWindow, Commands::closeWindow}

    }};
}