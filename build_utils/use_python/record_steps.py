import configparser
from typing import NoReturn, Tuple, Dict, List
from path_helper import check_file_exists, delete_file
from log import record, LOG_LEVEL

class step_file:
    def __init__(self, file_path: str) -> None:
        """
        初始化 IniFileHandler 类，加载 ini 文件
        :param file_path: ini 文件的路径
        """
        self.file_path: str = file_path
        # 检查文件是否存在, 不存在则创建文件
        check_file_exists(self.file_path)
        self.config: configparser.ConfigParser = configparser.ConfigParser()
        self.config.read(self.file_path)

    def get_value(self, section: str, key: str) -> str:
        """
        获取ini文件中指定节和键的值
        :param section: 节的名称
        :param key: 键的名称
        :return: 键的值, 如果没有找到, 返回空字符串
        """
        if self.config.has_section(section) and self.config.has_option(section, key):
            value: str = self.config.get(section, key)
            return value
        else:
            return {}

    def set_value(self, section: str, key: str, value: str) -> NoReturn:
        """
        设置ini文件中指定节和键的值
        :param section: 节的名称
        :param key: 键的名称
        :param value: 要设置的值
        """
        if not self.config.has_section(section):
            self.config.add_section(section)
        self.config.set(section, key, value)
        # 将更改保存到文件
        with open(self.file_path, 'w') as configfile:
            self.config.write(configfile)



if __name__ == "__main__":
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
