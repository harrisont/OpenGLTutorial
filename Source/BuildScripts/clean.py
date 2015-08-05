import directories

import shutil


def rmtree_if_exists(path):
    shutil.rmtree(path, ignore_errors=True)


def clean():
    rmtree_if_exists(directories.BUILD_INTERMEDIATE_DIR)
    rmtree_if_exists(directories.BUILD_DIR)


if __name__ == "__main__":
    clean()
