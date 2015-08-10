import logging
import os
import subprocess


def _run_process(args):
    """
    :return: True on success, False on failure
    """
    logging.info('Running CMake: {}'.format(args))
    exit_code = subprocess.call(['cmake'] + args)
    return True if exit_code == 0 else False


def run(build_intermediate_dir, source_dir, generator):
    """
    :param generator: if None use the default generator
    :return: True on success, False on failure
    """
    # Out-of-source build
    os.makedirs(build_intermediate_dir, exist_ok=True)
    os.chdir(build_intermediate_dir)

    # CMake args:
    #  -Wdev enable developer warnings
    #  -G specifies the generator
    #  -D define
    args = ['-Wdev']
    if generator:
        args.extend(['-G', generator])
    args.append(source_dir)
    return _run_process(args)


def build(build_intermediate_dir):
    """
    :return: True on success, False on failure
    """
    msbuild_flags = ['/nologo', '/verbosity:minimal']
    return _run_process(['--build', build_intermediate_dir, '--'] + msbuild_flags)
