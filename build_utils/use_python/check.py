import os
from typing import NoReturn
from record import log_message


def work_path(project_name: str) -> NoReturn:
    """
    Checks if the current working directory's path ends with the specified project name.

    Parameters:
        project_name (str): The name of the project, typically the name of the project folder.

    Returns:
        NoReturn: This function does not return any value but will raise an exception if the path is incorrect.

    Raises:
        Exception: If the current path does not end with the specified project name, an exception is raised.

    Description:
        The function retrieves the current working directory path and checks whether it ends with the provided
        project name. If the path is correct, it prints a confirmation message; if the path is incorrect,
        it raises an exception, indicating that the path is not as expected.
    """
    current_path: str = os.getcwd()
    suffix: str = current_path[-len(project_name):]
    if suffix == project_name:
        log_message(f"Work path is: {current_path}")
    else:
        raise Exception(f"Path error. Please ensure that the last few strings after using pwd are '{project_name}'")


def directory_exists(directory: str) -> NoReturn:
    """
    Checks if the specified directory exists, and creates it if it does not.

    Parameters:
        directory (str): The name or path of the directory to check. Defaults to "third_party".

    Returns:
        NoReturn: This function does not return any value but prints appropriate messages.

    Description:
        The function first checks if the specified directory exists. If the directory does not exist,
        it automatically creates the directory and prints a creation message; if the directory already exists,
        it prints a confirmation message without making any changes.
    """
    if not os.path.exists(directory):
        log_message(f"Directory '{directory}' does not exist. Creating it.")
        os.makedirs(directory)
    else:
        log_message(f"Directory '{directory}' already exists.")


def change_path(path: str) -> NoReturn:
    """
    Switch to the specified directory. If the directory does not exist, an error message will be displayed
    """
    try:
        os.chdir(path)
        log_message(f"current path: {os.getcwd()}")
    except FileNotFoundError:
        print(f"directory does not exist: {path}")
    except Exception as e:
        log_message(f"error: {e}")