import sys
import os
from typing import Dict
sys.path.append("build_utils/use_python")
from build_helper import cmake, make, install
from get_source_code import clone_repository, switch_branches
from log import record, LOG_LEVEL
from path_helper import get_current_path, check_workiong_path_in, change_path_to
from path_helper import check_directory_exists, is_directory_empty, delete_directory
from path_helper import check_file_exists, is_file_empty, delete_file
from record_steps import step_file


# check path
def get_source_code(work_path: str, url: str, clone_dir: str, version: str) -> bool:
    """
    获取源码步骤
    """
    try:
        check_workiong_path_in(work_path)
        command: str = clone_repository(url, clone_dir)
        record(LOG_LEVEL.INFO, f"Successfully executed command: {command}")
        change_path_to(clone_dir)
        command: str = switch_branches(version)
        record(LOG_LEVEL.INFO, f"Successfully executed command: {command}")
    except Exception as e:
        record(LOG_LEVEL.WARNING,str(e))
        return False
    return True

def pre_build(work_path: str, source_path: str, build_path: str, *args):
    """
    预构建步骤
    """
    try:
        check_workiong_path_in(work_path)
        change_path_to(source_path)
        check_directory_exists(build_path)
        change_path_to(build_path)
        command: str = cmake(*args)
        record(LOG_LEVEL.INFO, f"Successfully executed command: {command}")
    except Exception as e:
        record(LOG_LEVEL.WARNING,str(e))
        return False
    return True

def build_with_install(work_path: str, source_path: str, build_dir: str):
    """
    构建步骤
    """
    try:
        check_workiong_path_in(work_path)
        change_path_to(source_path + "/" + build_dir)
        command: str = make()
        record(LOG_LEVEL.INFO, f"Successfully executed command: {command}")
        command: str = install()
        record(LOG_LEVEL.INFO, f"Successfully executed command: {command}")
    except Exception as e:
        record(LOG_LEVEL.WARNING,str(e))
        return False
    return True


if __name__ == "__main__":
    check_directory_exists("build_log")
    record_step_file_name = "build_log/build_template.ini"
    build_log: step_file = step_file(record_step_file_name)
    completed_key: str = "completed" # step exec success key
    steps: list[tuple[str, Dict[str, str]]] = [
        ("get_source_code", {   "work_path"  : "sheer_third_party",
                                "clone_path" : "libraries/googletest-source",
                                "url"        : "https://github.com/google/googletest.git", 
                                "version"    : "release-1.12.0"}),
        ("pre_build", { "work_path"        : "sheer_third_party", 
                        "source_path"      : "libraries/googletest-source",
                        "build_dir"        : "build",
                        "version"          : "release-1.12.0",
                        "pre_install_path" : "libraries/googletest", 
                        "cmake_options1"   : "-DCMAKE_INSTALL_PREFIX="}),
        ("build_with_install", {"work_path"    : "sheer_third_party",
                                "source_path"  : "libraries/googletest-source",
                                "build_dir"    : "build"})
    ]


    try:
        step_id: int = 0
        for step_name, step_data in steps:
            step_id += 1
            record(LOG_LEVEL.INFO, f"start......{str(step_id)}: {step_name}")
            # 检查当前步骤是否已经完成
            if build_log.get_value(step_name, completed_key) == "y":
                continue
            # 分步骤执行
            if step_id == 1:
                # 为本步骤缓存所必要的值, 以及执行成功的标志
                build_log.set_value(step_name, completed_key, "n")
                current_path: str = get_current_path()
                build_log.set_value(step_name, "work_path",   step_data["work_path"])
                build_log.set_value(step_name, "url",         step_data["url"])
                build_log.set_value(step_name, "clone_path",  step_data["clone_path"])
                build_log.set_value(step_name, "version",     step_data["version"])
                # 执行本步骤
                if get_source_code(step_data["work_path"], step_data["url"], step_data["clone_path"], step_data["version"]) == False:
                    change_path_to(current_path)
                    delete_directory(step_data["clone_path"])
                    raise Exception(f"Step execution interrupt: {step_name}")
                # 执行成功则记录步骤执行结果
                change_path_to(current_path)
                build_log.set_value(step_name, completed_key, "y")

            elif step_id == 2:
                # 为本步骤缓存所必要的值, 以及执行成功的标志
                build_log.set_value(step_name, completed_key, "n")
                current_path: str = get_current_path()
                build_log.set_value(step_name, "work_path",        step_data["work_path"])
                build_log.set_value(step_name, "source_path",      step_data["source_path"])
                build_log.set_value(step_name, "build_dir",        step_data["build_dir"])
                build_log.set_value(step_name, "version",          step_data["version"])
                build_log.set_value(step_name, "pre_install_path", step_data["pre_install_path"])
                build_log.set_value(step_name, "cmake_options1",   step_data["cmake_options1"])
                # 执行本步骤
                install_path: str = current_path + "/" + step_data["pre_install_path"] + "-" +  step_data["version"]
                cmake_param1: str = step_data["cmake_options1"] + install_path
                if pre_build(step_data["work_path"], step_data["source_path"], step_data["build_dir"], cmake_param1, "..") == False:
                    change_path_to(current_path)
                    delete_directory(step_data["source_path"] + "/" + step_data["build_dir"])
                    raise Exception(f"Step execution interrupt: {step_name}")
                # 执行成功则记录步骤执行结果
                change_path_to(current_path)
                build_log.set_value(step_name, completed_key, "y")

            elif step_id == 3:
                # 为本步骤缓存所必要的值, 以及执行成功的标志
                build_log.set_value(step_name, completed_key, "n")
                current_path: str = get_current_path()
                build_log.set_value(step_name, "work_path",   step_data["work_path"])
                build_log.set_value(step_name, "source_path", step_data["source_path"])
                build_log.set_value(step_name, "build_dir",   step_data["build_dir"])
                # 执行本步骤
                if build_with_install(step_data["work_path"], step_data["source_path"], step_data["build_dir"]) == False:
                    raise Exception(f"Step execution interrupt: {step_name}")
                # 执行成功则记录步骤执行结果
                change_path_to(current_path)
                build_log.set_value(step_name, completed_key, "y")

            else: 
                raise Exception("Unknow step......{step_name}")
    except Exception as e:
        record(LOG_LEVEL.WARNING, str(e))

    record(LOG_LEVEL.INFO, "build and install lib: googletest success")

