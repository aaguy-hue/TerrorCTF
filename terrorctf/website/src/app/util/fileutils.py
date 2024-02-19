import os
from pathlib import Path


def delete_folder_contents(folder: Path):
    """Deletes all the files in a folder.add()

    Args:
        folder (Path): The folder to delete the files of.
    """
    files = folder.glob("*")
    for f in files:
        os.remove(f)


def copy_file(src_file: Path, dest_file:Path):
    """Copy a file to some other path.

    Args:
        src_file (Path): The file to copy.
        dest_file (Path): The final path that the file should be copied to.
    """
    with open(src_file, "rb") as f1:
        with open(dest_file, "wb") as f2:
            for byte in f1.read():
                f2.write(byte)