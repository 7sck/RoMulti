# Hidden Roblox Multi-Instance

Run multiple Roblox instances simultaneously with no visible windows.

## How It Works
Creates a hidden window that claims the `ROBLOX_singletonMutex`, allowing other Roblox instances to run. Unlike other tools, this operates completely in the background.

## Usage
1. Run the executable before launching Roblox
2. Launch multiple Roblox instances as needed
3. The tool runs invisibly (only visible in Task Manager)

## Building
```bash
# Clang
clang++ -std=c++17 -o RoMulti.exe RoMulti.cc -luser32

# MSVC
cl.exe /std:c++17 /EHsc RoMulti.cc user32.lib
```

Note: Teleports between games may be inconsistent.