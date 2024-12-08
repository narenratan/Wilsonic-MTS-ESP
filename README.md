# Wilsonic

Wilsonic is an advanced audio plugin and standalone application for creative sound design and music production. It features a powerful synthesizer engine with MTS-ESP support for microtuning capabilities.

## Features

- Standalone application and plugin formats (VST3, AU)
- MTS-ESP support for microtuning
- Advanced sound design capabilities
- Cross-platform compatibility (macOS, Windows)
- Intuitive user interface

## Installation

### macOS

1. Download the latest Wilsonic installer for macOS from the [releases page](https://github.com/marcus-w-hobbs/Wilsonic-MTS-ESP/releases).
2. Open the downloaded `.pkg` file and follow the installation wizard.
3. The standalone application will be installed in your Applications folder.
4. Audio Unit (AU) and VST3 plugins will be installed in their respective system folders.

### Windows

1. Download the latest Wilsonic installer for Windows from the [releases page](https://github.com/marcus-w-hobbs/Wilsonic-MTS-ESP/releases).
2. Run the downloaded `.exe` file and follow the installation wizard.
3. The standalone application will be installed in the specified location (default: Program Files).
4. VST3 plugins will be installed in the system VST3 folder.

## Building from Source

### Prerequisites

- Projucer (part of the JUCE framework)
- C++17 compatible compiler
- Xcode (for macOS) or Visual Studio (for Windows)

### Build Instructions

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/wilsonic.git
   cd wilsonic
   ```

2. Open the Wilsonic.jucer file in Projucer.

3. In Projucer, select your target IDE (Xcode for macOS or Visual Studio for Windows) and click "Save and Open in IDE".

4. Build the project in your IDE:
   - For Xcode: Select the desired target and click "Build"
   - For Visual Studio: Select the desired configuration and platform, then build the solution

5. The built standalone application and plugins will be in the "Builds" directory.

## Usage

Refer to the [User Manual](docs/user_manual.md) for detailed instructions on how to use Wilsonic.

## Design Philosophy

Wilsonic MTS-ESP is designed to enable professional music production with microtonal scale designs by Erv Wilson in the DAW of your choice, where all the parameters to the scale design are automatable in the DAW.  See "daw_automated_params.txt" for the parameters that can be automated.

The source of truth for all state is therefore JUCE's AudioProcessorValueTreeState.  The Processor owns the APVTS and all Models.  The Model objects own the Tuning objects, and bind them to APVTS, and provide an interface for the UI objects.  The Tuning objects are responsible for generating the MTS-ESP data.  Tuning objects know how to draw themselves.  Components delegate drawing to the Model objects, which pass the drawing on to the Tuning objects.  

The Editor is only responsible for rendering the UI, which is implemented as a LookAndFeel and Component hierarchy.  The Editor is not guaranteed to ever be created. 

## Contributing

We welcome contributions to Wilsonic! Please read our [Contributing Guidelines](CONTRIBUTING.md) for details on how to submit pull requests, report issues, and suggest improvements.

## License

Wilsonic is released under the [MIT License](LICENSE).

## Acknowledgements

- [JUCE](https://juce.com/) - Cross-platform audio application framework
- [MTS-ESP](https://github.com/ODDSound/MTS-ESP) - Microtuning support library

## Contact

For support or inquiries, please [open an issue](https://github.com/yourusername/wilsonic/issues) on this repository or contact us at support@wilsonic.co.
