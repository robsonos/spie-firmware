Import("env")


def update_version(source, target, env):
    versionFileLine = 2
    
    # Get path for versionFile
    versionFile = 'lib/Context/Context.h'

    # Get current firmware version
    with open("VERSION", 'r') as file:
        firmware_version = file.readline()[:-1]

    # Read versionFile
    with open(versionFile, "r") as file:
        content = file.readlines()

    # Add line with usedConfFile to line 4 of versionFile
    content[versionFileLine] = "#define VERSION \"" + firmware_version + \
        "\" // INFO: line used by builder. Do not change it\n"

    # Write content to versionFile
    with open(versionFile, 'w') as file:
        file.writelines(content)


env.AddPreAction("$BUILD_DIR/${PROGNAME}.hex", update_version)
