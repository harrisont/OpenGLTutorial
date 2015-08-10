import cmake
import directories
import function_timing

import logging


def generate():
    """
    :return: True on success, False on failure
    """
    return cmake.run(directories.BUILD_INTERMEDIATE_DIR, directories.SOURCE_DIR, generator=None)


def time_generate():
    """
    :return: True on success, False on failure
    """
    print('Running CMake')
    print('-' * 100)
    result, duration = function_timing.time_function(generate)
    duration_str = function_timing.get_duration_str(duration)
    print('CMake duration: {}'.format(duration_str))
    return result


def main():
    logging.basicConfig(level=logging.INFO)
    succeeded = time_generate()
    exit(0 if succeeded else 1)


if __name__ == '__main__':
    main()
