import os
import shutil
from typing import Dict
from build_helper import cmake, make, install
from get_source_code import clone_repository, switch_branches
from log import record, LOG_LEVEL
from path_helper import get_current_path, check_workiong_path_in, change_path_to
from path_helper import check_directory_exists, is_directory_empty, delete_directory
from path_helper import check_file_exists, is_file_empty, delete_file
from record_steps import step_file


# 测试代码部分
if __name__ == "__main__":
    # ----- get_source_code -----
    # clone dir
    url: str = "https://github.com/google/googletest.git"
    destination_dir: str = "gtest-src"
    install_dir: str = "gtest"


    # try clone and create dir
    try:
        command: str = clone_repository(url, destination_dir)
        record(LOG_LEVEL.INFO, f"Successfully executed command: {command}")
        commond: str = clone_repository("111", destination_dir) # Trigger exception
        record(LOG_LEVEL.INFO, f"Successfully executed command: {command}")
    except Exception as e:
        record(LOG_LEVEL.WARNING, str(e)) # Will execute

    # try to switch branch
    try:
        os.chdir(destination_dir) # step to dir
        command: str = switch_branches("release-1.12.0")
        record(LOG_LEVEL.INFO, f"Successfully executed command: {command}")
        os.chdir("..") # Exit directory
    except Exception as e:
        record(LOG_LEVEL.WARNING, str(e)) # Never execute
    
    # ----- build_helper -----
    check_directory_exists(install_dir) # create install dir
    install_path = os.path.join(os.getcwd(), install_dir) # {pwd}/{install_dir}
    os.chdir(destination_dir) # step to dir
    check_directory_exists("build") # create build dir
    os.chdir("build") # step to dir
    install_param: str = (f"-DCMAKE_INSTALL_PREFIX={install_path}")
    compile_path: str  = ".."
    command: str = cmake(install_param, compile_path)
    make()
    install()
    os.chdir("..") # Exit directory
    os.chdir("..") # Exit directory
    # remove source dir
    shutil.rmtree(destination_dir)

    # ----- path_helper -----
    # test [get_current_path]
    record(LOG_LEVEL.INFO, "test......get_current_path")
    current_path: str = get_current_path()
    record(LOG_LEVEL.INFO, f"current_path: {current_path}")
    work_path: str = os.path.basename(current_path)
    record(LOG_LEVEL.INFO, f"work_path: {work_path}")

    # test [check_workiong_path_in]
    record(LOG_LEVEL.INFO, "test......check_workiong_path_in")
    try:
        check_workiong_path_in(work_path) # Good 
        check_workiong_path_in(work_path + "hello!") # Trigger exception
    except Exception as e:
        record(LOG_LEVEL.WARNING, str(e)) # Will execute

    # test [check_directory_exists] [delete_directory] [is_directory_empty]
    record(LOG_LEVEL.INFO, "test......check_directory_exists, delete_directory, is_directory_empty")
    try:
        test_dir_name: str = "temp"
        check_directory_exists(test_dir_name) # Create dir named "temp"
        if is_directory_empty(test_dir_name) == True:
            record(LOG_LEVEL.INFO, f"{test_dir_name} is empty") # Trigger
        delete_directory(test_dir_name) # Delete dir named "temp"
        record(LOG_LEVEL.INFO, f"delete dir {test_dir_name} successfully")
    except Exception as e:
        record(LOG_LEVEL.WARNING, str(e)) # Never execute

    # test [check_file_exists] [delete_file] [is_file_empty]
    record(LOG_LEVEL.INFO, "test......check_file_exists, delete_file, is_file_empty")
    try:
        test_file_name: str = "temp"
        check_file_exists(test_file_name) # Create file named "temp"
        if is_file_empty(test_file_name) == True:
            record(LOG_LEVEL.INFO, f"{test_file_name} is empty") # Trigger
        delete_file(test_file_name) # Delete file named "temp"
        record(LOG_LEVEL.INFO, f"delete file {test_file_name} successfully")
    except Exception as e:
        record(LOG_LEVEL.WARNING, str(e)) # Never execute

    # test [change_path_to]
    record(LOG_LEVEL.INFO, "test......change_path_to")
    try:
        current_path: str = change_path_to("temp") # Trigger exception
    except Exception as e:
        record(LOG_LEVEL.WARNING, str(e)) # Will execute

    try:
        test_dir_name: str = "temp"
        check_directory_exists(test_dir_name) # Create dir named "temp"
        current_path: str = change_path_to(test_dir_name) # step to temp path
        check_workiong_path_in(test_dir_name)
        record(LOG_LEVEL.INFO, f"path change:{current_path} -> {test_dir_name}")
        change_path_to(current_path)
        check_workiong_path_in(work_path)
        delete_directory(test_dir_name) # Delete file named "temp"
    except Exception as e:
        record(LOG_LEVEL.WARNING, str(e)) # Never execute
    

    # ----- record_steps -----
    file_name = "build.ini"
    build_log: step_file = step_file(file_name)
    completed_key: str = "completed"
    steps: list[tuple[str, Dict[str, str]]] = [
        ("check_path", {"work_path": "use_python"}),
        ("get_source", {"work_path": "use_python"}),
        ("pre_build", {"work_path": "my_lib"}),
        ("build_install", {"work_path": "my_lib"})
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
                # 执行本步骤
                step1: bool = True
                if step1 == False:
                    raise Exception(f"Step execution interrupt: {step_name}")
                # 执行成功则记录步骤执行结果
                build_log.set_value(step_name, completed_key, "y")
            elif step_id ==2:
                # 为本步骤缓存所必要的值, 以及执行成功的标志
                build_log.set_value(step_name, completed_key, "n")
                # 执行本步骤
                step2: bool = True
                if step2 == False:
                    raise Exception(f"Step execution interrupt: {step_name}")
                # 执行成功则记录步骤执行结果
                build_log.set_value(step_name, completed_key, "y")
            elif step_id == 3:
                # 为本步骤缓存所必要的值, 以及执行成功的标志
                build_log.set_value(step_name, completed_key, "n")
                # 执行本步骤,
                step3: bool = False
                if step3 == False:
                    raise Exception(f"Step execution interrupt: {step_name}")
                # 执行成功则记录步骤执行结果
                build_log.set_value(step_name, completed_key, "y")
            elif step_id == 4:
                # 为本步骤缓存所必要的值, 以及执行成功的标志
                build_log.set_value(step_name, completed_key, "n")
                # 执行本步骤,
                step4: bool = True
                if step4 == False:
                    raise Exception(f"Step execution interrupt: {step_name}")
                # 执行成功则记录步骤执行结果
                build_log.set_value(step_name, completed_key, "y")
            else: 
                raise Exception("Unknow step......{step_name}")

    except Exception as e:
        record(LOG_LEVEL.WARNING, str(e))
