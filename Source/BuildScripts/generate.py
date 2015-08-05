import cmake
import directories
import function_timing


def generate():
    """
    :return: 0 on success, non-0 on failure
    """
    return cmake.run(directories.BUILD_INTERMEDIATE_DIR, directories.SOURCE_DIR, generator=None)


def time_generate():
    """
    :return: 0 on success, non-0 on failure
    """
    print('Running CMake')
    print('-' * 100)
    result, duration = function_timing.time_function(generate)
    duration_str = function_timing.get_duration_str(duration)
    print('CMake duration: {}'.format(duration_str))
    return result


def main():
    result = time_generate()
    exit(result)


if __name__ == '__main__':
    main()
