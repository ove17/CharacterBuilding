# CharacterBuilding

CharacterBuilding is a lightweight C library for writing characters and strings to text-based displays, intended for embedded systems with LCD displays.

It automatically manages custom character generation in CGRAM, allowing applications to use custom characters without having to manage the character generator memory themselves.

## Features

- Lightweight C library for embedded systems.
- Write characters and strings to a text-based display.
- Automatic management of custom characters in CGRAM.
- Designed for use with LCD displays.
- Separates character handling from display-specific implementation.

## Concept

CharacterBuilding provides a layer for handling characters and strings on displays that support user-defined characters.

The library manages the allocation and use of custom characters in CGRAM. This allows the application to work with its character data without having to manage the underlying character generator memory directly.

The application remains responsible for communicating with the display and implementing the display-specific functionality required by the library.

## Usage

Include the CharacterBuilding header in your application and initialize the library as required.

See the public header files in include for the available functions, data structures and usage details.

The library is intended to be integrated into an existing embedded application that provides the display interface.

## Design and constraints

- CharacterBuilding is designed for resource-constrained embedded systems.
- Custom character generation is managed by the library.
- Display communication remains the responsibility of the application.
- The library focuses on character and string handling rather than providing a complete display driver.

## License

CharacterBuilding is licensed under the MIT License. See LICENCE for details.
