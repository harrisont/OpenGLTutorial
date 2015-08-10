import build
import generate

import logging


def generate_and_build():
    """
    :return: True on success, False on failure
    """
    generate_succeded = generate.time_generate()
    if not generate_succeded:
        return False
    return build.time_build()


def main():
    logging.basicConfig(level=logging.INFO)
    succeeded = generate_and_build()
    exit(0 if succeeded else 1)


if __name__ == '__main__':
    main()
