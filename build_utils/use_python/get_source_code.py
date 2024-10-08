import subprocess

def clone_repository(url: str, destination: str) -> str:
    """
    通过url克隆仓库到目录
    :param url: 克隆的url
    :param destination: 仓库克隆的目录
    """
    command: list = ["git", "clone", url, destination]
    subprocess.run(command, check=True)
    return " ".join(command) # Format output command


def switch_branches(version: str) -> str:
    """
    切换仓库分支
    :param version: 分支名
    """
    command: list = ["git", "checkout", version]
    subprocess.run(command, check=True)
    return " ".join(command) # Format output command

def pull_submodules() -> str:
    """
    切换仓库分支
    :param version: 分支名
    """
    command: list = ["git", "submodule", "update", "--init", "--recursive"]
    subprocess.run(command, check=True)
    return " ".join(command) # Format output command

