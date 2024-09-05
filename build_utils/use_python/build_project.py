import os
import subprocess
from typing import NoReturn
from record import log_message


def cmake(*args) -> NoReturn:
    for arg in args:
        if not isinstance(arg, str):
            raise ValueError("All arguments must be strings")
    command = ["cmake"] + list(args)
    log_message(f"{command}")
    subprocess.run(command, check=True)
    log_message(f"Compilation successful.")


def make(*args) -> NoReturn:
    for arg in args:
        if not isinstance(arg, str):
            raise ValueError("All arguments must be strings")
    total_cores = os.cpu_count() or 1

    command = ['make', "-j" + str(total_cores)] + list(args)
    log_message(f"{command}")
    subprocess.run(command, check=True)
    log_message(f"Compilation successful.")

def install():
    log_message(f"make install")
    subprocess.run(["make", "install"], check=True)
    log_message(f"library install success.")