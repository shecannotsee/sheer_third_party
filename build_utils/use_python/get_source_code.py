import subprocess
from typing import NoReturn
from sheer_third_party.build_utils.use_python.build_log import log_message


def clone_repository(url: str, destination: str) -> NoReturn:
    commond: str = ["git", "clone", url, destination]
    log_message(f"{commond}")
    subprocess.run(commond, check=True)
    log_message(f"Successfully cloned repository to {destination}.")


def switch_branches(version: str) -> NoReturn:
    commond: str = ["git", "checkout", version]
    log_message(f"{commond}")
    subprocess.run(commond, check=True)
    log_message(f"Successfully switched branches: {version}.")
