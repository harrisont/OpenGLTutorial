import cmake
import directories
import function_timing
import generate

import logging

import os


def build():
    """
    :return: True on success, False on failure
    """
    if not os.path.isdir(directories.BUILD_INTERMEDIATE_DIR):
        generate_succeeded = generate.generate()
        if not generate_succeeded:
            return False
    return cmake.build(directories.BUILD_INTERMEDIATE_DIR)


def time_build():
    """
    :return: True on success, False on failure
    """
    print('Building')
    print('-' * 100)
    succeeded, duration = function_timing.time_function(build)
    duration_str = function_timing.get_duration_str(duration)
    print('Build duration: {}'.format(duration_str))
    return succeeded


def main():
    logging.basicConfig(level=logging.INFO)
    succeeded = time_build()
    exit(0 if succeeded else 1)


if __name__ == '__main__':
    main()
