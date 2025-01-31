cmake_minimum_required(VERSION 3.22.1)

project("antiposos")

# Do you even understand what's going on in the code?
# A child who grew up copying cheats for Unity-based games, you have no idea how stupid you are compared to us.
# You waste time on the same type of copying without even trying to structure the code properly and are afraid that by strings using SHIFT + F12 your cheat will be reversed and your offsets will be stolen,
# which can be obtained in 1 hour of my work.
# Pathetic skidders, you are trying to hide your strings using the XOR obfuscator, but it is so easy to do with a simple strstr hook that you will cry when you find out about it
# Fall down before my power.
# "Proud" and not stupid (ha-ha) ching chongs, we beat you in 6 days of development practically from scratch.
# No obfuscation will save your lower forms of source code, which for some reason you consider a precious treasure.
# You can not try to use ultimate packer or ollvm, it will not help you against really smart people, which you are not.
# No eres de ninguna utilidad para la sociedad si no sabes usar cmakelists.

if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")


add_library(${CMAKE_PROJECT_NAME} SHARED
        main.cpp

        config/ConfigManager.cpp

        includes/imgui/imgui.cpp
        #includes/imgui/imgui_demo.cpp
        includes/imgui/imgui_draw.cpp
        includes/imgui/imgui_impl_android.cpp
        includes/imgui/imgui_impl_opengl3.cpp
        includes/imgui/imgui_tables.cpp
        includes/imgui/imgui_widgets.cpp

        menu/Menu.cpp
        menu/MainButton.cpp
        menu/NotificationManager.cpp
        menu/elements/FloatingButton.cpp
        menu/elements/ModuleShortcutButton.cpp

        memory/Hooks.cpp
        memory/Game.cpp

        module/Module.cpp
        module/ModuleManager.cpp

        module/combat/AimBot.cpp
        module/combat/KillAura.cpp
        module/combat/TriggerBot.cpp
        module/combat/Velocity.cpp
        module/misc/Blink.cpp
        module/misc/ChestStealer.cpp
        module/misc/Configs.cpp
        module/misc/NoInvisible.cpp
        module/movement/AirJump.cpp
        module/movement/BlockFly.cpp
        module/movement/Jetpack.cpp
        module/movement/Step.cpp
        module/render/NameTags.cpp
        module/render/TraceLines.cpp

        sdk/Actor.cpp
        sdk/AppPlatform.cpp
        sdk/Block.cpp
        sdk/ClientInstance.cpp
        sdk/Dimension.cpp
        sdk/GameMode.cpp
        sdk/InputHandler.cpp
        sdk/Inventory.cpp
        sdk/Level.cpp
        sdk/LocalPlayer.cpp
        sdk/mce.cpp
        sdk/Minecraft.cpp
        sdk/MinecraftGame.cpp
        sdk/Packet.cpp
        sdk/Player.cpp
        sdk/ScreenController.cpp

        utils/Utils.cpp
        utils/RenderUtils.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/glm
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/imgui
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log
        ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libfmod.so
        ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libminecraftpe.so
        ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libdobby.a
        EGL
        GLESv3
)