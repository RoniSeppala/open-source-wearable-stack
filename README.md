# Smart ring
## current functionality
Read icm20602 with custom firmware and print data to serial monitor using an esp32-c6-devkitc board for testing purposes.
## Design goals
- 6-8 gestures with minimal user friction
- 7+ day battery life
- wireless charging
- bluetooth data transfer
- sub 100e component cost
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