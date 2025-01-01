<p align="center">
<h3 align="center">SPIE firmware</h3>
</p>
<p align="center">
  <img
      alt="Maintenance status"
      src="https://img.shields.io/maintenance/yes/2025?style=flat-square">
  <a
    href="https://github.com/robsonos/spie-firmware/actions/workflows/ci.yml"
    style="color: inherit; text-decoration: none;">
    <img
      alt="GitHub Workflow Status (with event)"
      src="https://img.shields.io/github/actions/workflow/status/robsonos/spie-firmware/ci.yml">
  </a>
  <a
    href="LICENSE"
    style="color: inherit; text-decoration: none;">
    <img
      alt="GitHub License"
      src="https://img.shields.io/github/license/robsonos/spie-firmware">
  </a>
  <br />
  <a
    href="https://github.com/robsonos/spie-firmware/releases"
    style="color: inherit; text-decoration: none;">
    <img
      alt="GitHub Release version"
      src="https://img.shields.io/github/v/release/robsonos/spie-firmware">
  </a>
  <a
    href="#contributors"
    style="color: inherit; text-decoration: none;">
    <img
        alt="GitHub contributors from allcontributors.org"
        src="https://img.shields.io/github/all-contributors/robsonos/spie-firmware">
  </a>
</p>

This repository was initially created to test the features of [spie](https://github.com/robsonos/spie). However, it can be used to bootstrap your `PlatformIO` project with a modern embedded system workflow.
The firmware itself provides a simple implementation of an AT command interface for configuring a sine wave generator.

## Index

- [Features](#features)
- [Getting started](#getting-started)
- [Platformio tasks](#platformio-tasks)
- [AT commands](#at-commands)
- [CD/CI/Release workflow](#cdcirelease-workflow)
- [Troubleshooting](#troubleshooting)

## Features

<p align="center"><br><img src="./docs/demo-serial-plotter.gif" width="500"></p>
<p align="center"><br><img src="./docs/demo-spie-plotter.gif" width="500"></p>

- Configure sine wave generation in real-time using AT commands.
- Command validation and error handling for invalid inputs.
- Unit-tested with mocks using `ArduinoFake`.
- CI/CD workflows with proper versioning and release routines.

## Getting Started

### Steps

1. Clone the repository

```sh
git clone https://github.com/robsonos/spie-firmware
```

2. Open the repository with VSCode and install the recommended extensions

3. Familiarise yourself with [PlatformIO](https://platformio.org/)

[Back to Index](#index)

## Platformio tasks

- Build the code:

```sh
pio run -e uno
```

- Upload code:

```sh
pio run -e uno -t upload
```

- Run `cppcheck`:

```sh
pio check
```

- Run unit tests:

```sh
pio test
```

[Back to Index](#index)

## AT Commands

### Configuration Commands

Set or query configuration parameters using the following AT commands:

| Command                   | Description                                              | Example                | Response              |
| ------------------------- | -------------------------------------------------------- | ---------------------- | --------------------- |
| `AT+NUMPHASES=<value>`    | Sets the number of phases (positive integer).            | `AT+NUMPHASES=3`       | `OK`                  |
| `AT+NUMPHASES?`           | Queries the current number of phases.                    | `AT+NUMPHASES?`        | `+NUMPHASES: 3`       |
| `AT+SIGNALFREQ=<value>`   | Sets the signal frequency (positive integer).            | `AT+SIGNALFREQ=50`     | `OK`                  |
| `AT+SIGNALFREQ?`          | Queries the current signal frequency.                    | `AT+SIGNALFREQ?`       | `+SIGNALFREQ: 50`     |
| `AT+SAMPLINGFREQ=<value>` | Sets the sampling frequency (positive integer).          | `AT+SAMPLINGFREQ=1000` | `OK`                  |
| `AT+SAMPLINGFREQ?`        | Queries the current sampling frequency.                  | `AT+SAMPLINGFREQ?`     | `+SAMPLINGFREQ: 1000` |
| `AT+AMPLITUDE=<value>`    | Sets the amplitude (zero or positive integer).           | `AT+AMPLITUDE=2000`    | `OK`                  |
| `AT+AMPLITUDE?`           | Queries the current amplitude.                           | `AT+AMPLITUDE?`        | `+AMPLITUDE: 2000`    |
| `AT+OFFSET=<value>`       | Sets the offset (integer between -10000 and 10000).      | `AT+OFFSET=500`        | `OK`                  |
| `AT+OFFSET?`              | Queries the current offset.                              | `AT+OFFSET?`           | `+OFFSET: 500`        |
| `AT+ERRORPERCENT=<value>` | Sets the error percentage (float between 0.0 and 100.0). | `AT+ERRORPERCENT=5.5`  | `OK`                  |
| `AT+ERRORPERCENT?`        | Queries the current error percentage.                    | `AT+ERRORPERCENT?`     | `+ERRORPERCENT: 5.5`  |
| `AT+VERSION?`             | Queries the current firmware version.                    | `AT+VERSION?`          | `+VERSION: 1.0.0`     |
| `AT+ALL?`                 | Queries all current configuration parameters.            |

### Error Responses

If a command is invalid, the interface responds with a descriptive error message:

- `ERROR: Invalid AT command format.`
- `ERROR: Unknown command.`
- `ERROR: <parameter> must be <valid range>.`

[Back to Index](#index)

## CD/CI/Release workflow

There are many ways CD/CI/Release workflow can be implemented. I chose the most convenient one and here is how it is meant to work:

- `dev`: holds the development code. Pushes to this will trigger the `CI workflow`, test your code, and create a PR to merge it into `main`.
- `main`: holds the code for the latest release. Pushes to this will trigger the `CD workflow` and create a new github release and tag. You should never need to push commits to `main`; use `dev` and create a PR instead. The code on this branch should always come from merges from `dev`.
- Once a new release is done, the `Release` workflow will be triggered to build and add the binaries to the release.
- If you need to maintain more release channels, like `main` is at `v3.x.x` but you need to support `v1.x.x`, I would recommend using a similar approach:
  - `main` for `v3.x.x`
  - `main/v1` for `v1.x.x`
  - `dev` for `v3.x.x` development
  - `dev/v1` for `v1.x.x` development
- I may look into exemplifying the above and `pre-releases` in the feature

[Back to Index](#index)

## Troubleshooting

- You may need to update the following for unit testing the code:

```ini
[env:native]
platform = native; or windows_x86, or linux_x86_64 ...
...
```

For more information, check out [PlatformIO's Development Platforms](https://docs.platformio.org/en/latest/platforms/index.html#desktop)

[Back to Index](#index)

## Contributors

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

[Back to Index](#index)
