import os
import shutil
from typing import NoReturn

def get_current_path() -> str:
    """
    获取当前工作路径
    :return 当前路径
    """
    current_path: str = os.getcwd()  # Get the new current working directory
    return current_path

def check_workiong_path_in(work_path: str) -> NoReturn:
    """
    检查当前路径是否在work_path下
    :param work_path: 工作路径
    """
    current_path: str = os.getcwd()
    suffix: str = current_path[-len(work_path):]
    if suffix != work_path:
        raise Exception(f"Work path error: please ensure that the last few strings after using pwd are \"{work_path}\"")


def change_path_to(path: str) -> str:
    """
    切换目录到path下, 返回切换之前的路径
    :param path: 要切换的目录
    :return 切换之前的目录
    """
    try:
        current_path: str = os.getcwd()  # Get the new current working directory
        os.chdir(path)
        return current_path
    except FileNotFoundError:
        raise FileNotFoundError(f"Directory does not exist, unable to change directory: {path}")
    except Exception as e:
        raise Exception(f"Error changing directory: {e}")


def check_directory_exists(directory: str) -> NoReturn:
    """
    检查目录是否存在, 若不存在则创建目录
    :param directory: 要检查的目录
    """
    if not os.path.exists(directory):
        os.makedirs(directory)


def is_directory_empty(path: str) -> bool:
    """
    检查指定的目录是否为空
    :param path: 要检查的目录路径
    :return: 如果目录为空, 则为True, 否则为False
    """
    if not os.path.isdir(path):
        raise NotADirectoryError(f"Path is not a directory: {path}")
    # Check if the directory is empty
    return len(os.listdir(path)) == 0


def delete_directory(directory: str) -> NoReturn:
    """
    删除指定目录及其所有内容
    :param directory_path: 要删除的目录路径
    """
    if os.path.exists(directory):
        try:
            shutil.rmtree(directory)
        except Exception as e:
            raise Exception(f"delete directory {directory} failed: {e}")
        

def check_file_exists(file_path: str) -> None:
    """
    检查文件是否存在, 不存在则创建文件
    :param file_path: 文件路径
    """
    if not os.path.isfile(file_path):
        with open(file_path, 'w') as file:
            # Create an empty file
            pass

def is_file_empty(file_path: str) -> bool:
    """
    检查文件是否为空
    :param file_path: 文件路径
    :return: 如果文件为空, 则为True, 否则为False
    """
    if not os.path.isfile(file_path):
        raise FileNotFoundError(f"File does not exist: {file_path}")

    return os.path.getsize(file_path) == 0

def delete_file(file_path: str) -> NoReturn:
    """
    删除指定文件
    :param file_path: 要删除的文件路径
    """
    if os.path.isfile(file_path):
        os.remove(file_path)
