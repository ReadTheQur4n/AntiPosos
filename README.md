# AntiPosos

AntiPosos - A simple open source hacked client for Minecraft: Bedrock Edition (Android)

## Build with CMake

1. Open cmd
2. Make sure you have a keyboard

Use this command first:
```
cmake -G Ninja -S ./src -B ./build -DCMAKE_TOOLCHAIN_FILE=<path_to_ndk>\build\cmake\android.toolchain.cmake -DANDROID_ABI=arm64-v8a
```

You should replace <path_to_ndk> with... The path to NDK! Amazing, isn't it?

Then, if everything goes well, you need to build the project with this command:
```
cmake --build ./build
```

“Indeed, Allah is with those who fear God and do good.” - Surah 16, verse 128
