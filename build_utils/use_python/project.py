class info:
    def __init__(self, name: str, get_path: str, version: str, build_dir: str):
        self.name      = name
        self.get_path  = get_path
        self.version   = version
        self.build_dir = build_dir

    def __repr__(self):
        return f"project(name='{self.name}', get_path='{self.get_path}', version='{self.version}', build_dir='{self.build_dir}')"