import os
import subprocess


def _run_process(args):
    """
    :return: 0 on success, non-0 on failure
    """
    return subprocess.call(['cmake'] + args)


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
    args = ['-Wdev']
    if generator:
        args.extend(['-G', generator])
    args.append(source_dir)
    return _run_process(args)


def build(build_intermediate_dir):
    """
    :return: 0 on success, non-0 on failure
    """
    return _run_process(['--build', build_intermediate_dir])
