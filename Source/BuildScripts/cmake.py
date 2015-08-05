import os
import subprocess


def run(build_intermediate_dir, source_dir, generator):
    """
    :param generator: if None use the default generator
    :return: 0 on success, non-0 on failure
    """
    # Out-of-source build
    os.makedirs(build_intermediate_dir, exist_ok=True)
    os.chdir(build_intermediate_dir)

    # CMake args:
    #  -Wdev enable developer warnings
    #  -G specifies the generator
    args = ['cmake', '-Wdev']
    if generator:
        args.extend(['-G', generator])
    args.append(source_dir)
    return subprocess.call(args)
