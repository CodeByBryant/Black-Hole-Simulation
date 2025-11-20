# Black Hole Simulation

A real-time 3D black hole simulation written in C++ with OpenGL, featuring gravitational physics, visual effects, and interactive object manipulation.

![Black Hole Simulation](https://img.shields.io/badge/OpenGL-3.3-blue)
![C++](https://img.shields.io/badge/C++-17-green)
![License](https://img.shields.io/badge/license-MIT-brightgreen)

## Features

- **Real-time 3D Rendering**: OpenGL-based graphics with smooth 60 FPS performance
- **Black Hole Physics**: Schwarzschild black hole with event horizon and accretion disk
- **Gravitational Simulation**: Newtonian gravity approximation with N-body interactions
- **Interactive Objects**: Add spherical objects with custom mass, velocity, and color
- **Light Sources**: Objects can emit light for enhanced visual effects
- **Orbital Mechanics**: Watch objects orbit the black hole or fall into the event horizon
- **Trajectory Trails**: Visualize object paths through space
- **Camera Controls**: Free-form camera with rotation, zoom, and pan
- **Accretion Disk**: Animated disk with realistic motion and color gradients
- **Starfield Background**: Procedurally generated stars with gravitational distortion
- **ImGui Interface**: Easy-to-use controls for simulation parameters

## Screenshots

The simulation features:
- A central black hole with visible event horizon
- Glowing accretion disk with orbital motion
- Interactive objects with customizable properties
- Real-time physics simulation
- Starfield background

## Physics

The simulation implements:
- **Schwarzschild Metric**: Simplified gravitational lensing calculations
- **Newtonian Gravity**: Force calculations between objects and black hole
- **Event Horizon**: Objects that cross the Schwarzschild radius are removed
- **N-body Simulation**: All objects interact gravitationally with each other

## Requirements

### System Dependencies
- **C++ Compiler**: Clang 14+ or GCC 9+
- **CMake**: 3.10 or higher
- **OpenGL**: 3.3 or higher
- **X11**: For display (Linux)
- **VNC** (optional): For remote display

### Libraries
- **GLFW**: Window management and input (3.3+)
- **GLEW**: OpenGL extension loading (2.0+)
- **GLM**: Mathematics library (0.9.9+)
- **ImGui**: Immediate mode GUI (1.90+)

## Building and Running

### Quick Start (All Platforms)

The easiest way to build and run:

```bash
# Clone repository
git clone https://github.com/yourusername/blackhole-simulation.git
cd blackhole-simulation

# Run the script (builds if needed, then runs)
./run.sh
```

The `run.sh` script automatically:
- Detects if build is needed
- Runs CMake and make
- Launches the simulation

### Manual Build (Linux/macOS)

```bash
# Install dependencies (Debian/Ubuntu)
sudo apt-get install build-essential cmake pkg-config
sudo apt-get install libglfw3-dev libglew-dev libglm-dev
sudo apt-get install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev

# Or on macOS with Homebrew
brew install cmake glfw glew glm

# Build
mkdir build
cd build
cmake ..
make -j$(nproc)

# Run
cd ..
./build/blackhole_sim
```

### NixOS

```bash
# Enter nix-shell with all dependencies
nix-shell

# Build and run
./run.sh
```

### Windows (MSVC/MinGW)

Install dependencies via vcpkg or manually, then:

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
..\build\Release\blackhole_sim.exe
```

## Controls

### Mouse
- **Left Click + Drag**: Rotate camera around black hole
- **Right Click + Drag**: Pan camera
- **Scroll Wheel**: Zoom in/out

### Interface
- **Add Object**: Create new objects with custom properties
  - Position (X, Y, Z coordinates)
  - Velocity (initial motion vector)
  - Mass (affects gravitational interactions)
  - Radius (visual size)
  - Color (RGB values)
  - Light emission (makes object glow)

- **Simulation Controls**:
  - Pause/Resume button
  - Time scale slider (0.1x to 5.0x speed)
  - Clear all objects button

### Keyboard
- **ESC**: Exit simulation

## Project Structure

```
blackhole-simulation/
├── src/                    # Source files
│   ├── main.cpp           # Application entry point
│   ├── renderer.cpp       # OpenGL rendering engine
│   ├── camera.cpp         # Camera controls
│   ├── physics.cpp        # Physics simulation
│   ├── blackhole.cpp      # Black hole calculations
│   ├── object.cpp         # Simulation objects
│   └── shader.cpp         # Shader management
├── include/               # Header files
│   ├── renderer.h
│   ├── camera.h
│   ├── physics.h
│   ├── blackhole.h
│   ├── object.h
│   └── shader.h
├── shaders/              # GLSL shaders
│   ├── object.vert       # Object vertex shader
│   ├── object.frag       # Object fragment shader
│   ├── skybox.vert       # Skybox vertex shader
│   ├── skybox.frag       # Skybox fragment shader
│   ├── accretion.vert    # Accretion disk vertex shader
│   └── accretion.frag    # Accretion disk fragment shader
├── imgui/                # ImGui library
├── CMakeLists.txt        # Build configuration
├── run.sh                # Launch script
└── README.md             # This file
```

## Technical Details

### Rendering
- **Graphics API**: OpenGL 3.3 Core Profile
- **Shading**: Phong reflection model with specular highlights
- **Geometry**: Procedurally generated sphere meshes
- **Effects**: Transparency blending for accretion disk

### Physics Engine
- **Time Integration**: Explicit Euler method
- **Force Calculation**: O(N²) pairwise interactions
- **Gravitational Constant**: Tunable parameter (default: 0.5)
- **Collision Detection**: Event horizon boundary check

### Shaders
- **Object Shader**: Per-vertex normal calculation, Phong lighting
- **Skybox Shader**: Procedural star generation
- **Accretion Shader**: Animated disk with distance-based coloring

## Customization

### Adding Features
The codebase is modular and easy to extend:

1. **New Object Types**: Extend `SimObject` class in `object.h`
2. **Custom Forces**: Add force calculations in `physics.cpp`
3. **Visual Effects**: Modify shaders in `shaders/` directory
4. **UI Elements**: Add ImGui controls in `main.cpp`

### Performance Tuning
- Adjust sphere resolution in `renderer.cpp` (sectors/stacks)
- Modify trail length in `object.cpp` (maxTrailLength)
- Change physics timestep in `main.cpp` (deltaTime)

## Known Limitations

- Newtonian approximation (not full General Relativity)
- No Kerr metric support (non-rotating black holes only)
- Simplified gravitational lensing (not ray-traced geodesics)
- CPU-bound physics (no GPU acceleration)

## Future Enhancements

- [ ] Full Schwarzschild geodesic integration with RK4
- [ ] Rotating black holes (Kerr metric)
- [ ] Gravitational redshift visualization
- [ ] Photon sphere rendering
- [ ] GPU-accelerated physics (compute shaders)
- [ ] Save/load simulation states
- [ ] Multi-black hole systems
- [ ] Collision detection between objects

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **ImGui**: [Dear ImGui](https://github.com/ocornut/imgui) by Omar Cornut
- **GLM**: [OpenGL Mathematics](https://github.com/g-truc/glm)
- **GLFW**: [GLFW library](https://www.glfw.org/)
- **GLEW**: [OpenGL Extension Wrangler](http://glew.sourceforge.net/)

## References

- Schwarzschild, K. (1916). "On the Gravitational Field of a Mass Point"
- James, O. et al. (2015). "Gravitational Lensing by Spinning Black Holes in Astrophysics"
- Riazuelo, A. (2015). "Seeing Relativity: Ray Tracing in Schwarzschild Metric"

## Author

Created as a demonstration of real-time physics simulation and OpenGL rendering techniques.

## Support

For issues, questions, or suggestions, please open an issue on GitHub.
