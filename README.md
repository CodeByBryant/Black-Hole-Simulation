# Black Hole Simulation

Watch objects orbit, collide, and get sucked into a black hole—all in real-time 3D with interactive controls.

## What You Get

- **Real-time 3D visualization** of a black hole and orbiting objects
- **Realistic physics** including gravity, orbital mechanics, and an event horizon
- **Interactive controls** to add objects, change the simulation speed, and move the camera around
- **Glowing accretion disk** and starfield background
- **Smooth performance** at 60 FPS

## Quick Start

### On Replit
Simply run:
```bash
./run.sh
```

The script will build everything and launch the simulation automatically.

### On Your Own Computer

**Linux/Mac with Homebrew:**
```bash
brew install cmake glfw glew glm

mkdir build && cd build
cmake ..
make -j$(nproc)
cd ..
./build/blackhole_sim
```

**Linux (apt):**
```bash
sudo apt-get install build-essential cmake libglfw3-dev libglew-dev libglm-dev libx11-dev

mkdir build && cd build
cmake ..
make -j$(nproc)
cd ..
./build/blackhole_sim
```

## How to Use It

**Camera:**
- Click and drag the left mouse button to rotate your view
- Right click and drag to move the camera around
- Scroll to zoom in and out
- Press ESC to quit

**Add Objects:**
- Use the on-screen menu to create objects with custom:
  - Position and velocity (where it starts and how fast it moves)
  - Mass (affects gravity)
  - Size and color
  - Optional glow effect

**Simulation Controls:**
- Pause/resume the simulation
- Speed it up or slow it down (0.1x to 5.0x)
- Clear all objects and start fresh

## What's Inside

```
├── src/           # The actual code
├── shaders/       # Graphics effects
├── imgui/         # User interface library
├── include/       # Header files
└── CMakeLists.txt # Build configuration
```

## How It Works

The simulation uses real Newtonian gravity to calculate how objects move. Objects orbit the black hole, and if they get too close to the event horizon (the point of no return), they disappear. Everything is rendered with OpenGL for smooth, real-time animation.

## What It Doesn't Do (Yet)

- It's using simplified physics, not full Einstein's General Relativity
- Only non-rotating black holes are supported
- Can't save or load simulations
- No collisions between objects (they pass through each other)

## Want to Help?

Found a bug or have an idea? Pull requests and issues are welcome!

## License

MIT License - see [LICENSE](LICENSE) for details.
