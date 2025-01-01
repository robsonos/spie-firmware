import os
from shutil import copy
Import("env")


def generate_dist_files(source, target, env):
    # Get current firmware version
    with open("VERSION", 'r') as file:
        firmware_version = file.readline()[:-1]

    # Get PlatformIO build folder location
    build_dir = env.get("PROJECT_BUILD_DIR")

    # Get device type (the name of current PlatformIO environment)
    device_type = env.get("PIOENV")

    # Source files
    hex_source_path = os.path.join(build_dir, device_type,
                                   "firmware.hex")

    # Get PlatformIO project folder location
    project_dir = env.get("PROJECT_DIR")

    # Create dist folder if it does not exist
    dist_folder = os.path.join(
        project_dir, "dist", device_type, "v" + firmware_version)
    if not os.path.exists(dist_folder):
        os.makedirs(dist_folder)

    # Destination files
    hex_destination_path = os.path.join(dist_folder,
                                        device_type + "-v" + firmware_version + ".hex")

    # Copy files from source to destination
    copy(hex_source_path, hex_destination_path)


env.AddPostAction("$BUILD_DIR/${PROGNAME}.hex", generate_dist_files)
