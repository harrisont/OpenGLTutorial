import cmake
import directories
import function_timing
import generate

import os


def build():
    """
    :return: 0 on success, non-0 on failure
    """
    if not os.path.isdir(directories.BUILD_INTERMEDIATE_DIR):
        generate_result = generate.generate()
        if generate_result:
            return generate_result
    return cmake.build(directories.BUILD_INTERMEDIATE_DIR)


def time_build():
    """
    :return: 0 on success, non-0 on failure
    """
    print('Building')
    print('-' * 100)
    result, duration = function_timing.time_function(build)
    duration_str = function_timing.get_duration_str(duration)
    print('Build duration: {}'.format(duration_str))
    return result


def main():
    result = time_build()
    exit(result)


if __name__ == '__main__':
    main()
