import os
import subprocess
from log import record, LOG_LEVEL

def cmake(*args) -> str:
    for arg in args:
        if not isinstance(arg, str):
            raise ValueError("All arguments must be strings")
    command = ["cmake"] + list(args)
    subprocess.run(command, check=True)
    return " ".join(command) # Format output command


def make(*args) -> str:
    for arg in args:
        if not isinstance(arg, str):
            raise ValueError("All arguments must be strings")
    # Obtain CPU core
    total_cores = os.cpu_count() or 1

    command = ["make", "-j" + str(total_cores)] + list(args)
    subprocess.run(command, check=True)
    return " ".join(command) # Format output command

def install() -> str:
    command = ["make", "install"]
    subprocess.run(command, check=True)
    return " ".join(command) # Format output command