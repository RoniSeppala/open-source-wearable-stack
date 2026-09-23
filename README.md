# Smart ring
## current functionality
Read icm20602 with custom firmware and print data to serial monitor using an esp32-c6-devkitc board for testing purposes.
## Design goals
- 6-8 gestures with minimal user friction
  - gesture execution thrugh a custom vector based gravity and orientation corrected 3d-grid system projected onto the rings plane
- 7+ day battery life
- wireless charging
- bluetooth data transfer
- sub 100e component cost
- determine which way ring is by measuring capacitance on both internal surface edges capasitance??
  - if not possible, then mark ring or use a determining tap gesture( tap surface/other finger, and determine joint location based on accelerometer + gyro, and determine ring orientation based on that)
## how to compile and develop
### requirements
- zephyr
- vscode
### how to build
#### install recommended vscode extensions
VSCode should prompt for install, but they can also be found at [extensions.json](.vscode/extensions.json)
#### clone repository
#### build with zephyr
The currently supported way to compile and flash is using vscodes zephyr-ide extension.
It is recommended to set the .vscode/settings.json file up according to instructions here [VSCode settings instructions](./documentation/vscode_configuration.md#recommended-vscode-settings)
#### Flash with zephyr-ide
### Notes
- The building should be possible using any way zephyr supports, but the project documentation is for VSCode Zephyr-IDE
- The compile_commands.json is genereated on first pristine build, which is required for intelliSense
## AI-notice
The project consists of no AI-genereated code

AI has been used as a learning tool for zephyr(among other resources), parseing documentation and datasheets, as well as analysing build/compile errors, but all code and other files in this repository are otherwise made without the use of AI


# possible gestures
- finger tap/double tap/triple tap
- when finger is horizontal compared to ground (e.g. pointing forwards or other)
  - swipe left
  - swipe right
  - spipe up
  - swipe down
  - rotate counter clockwise
  - rotate clockwise
- when finger is vertical compared to ground
  - rotate counter clockwise
  - rotate clockwise
  - general swipe (direction agnostic)