local lfs = require("lfs")

local file_utils = {}

-- Function to check if a file exists
function file_utils.file_exists(file_path)
    local attr = lfs.attributes(file_path)
    return attr ~= nil and attr.mode == "file"
end

-- Function to check if a directory exists
function file_utils.dir_exists(dir_path)
    local attr = lfs.attributes(dir_path)
    return attr ~= nil and attr.mode == "directory"
end

-- Function to create a file
function file_utils.create_file(file_path)
    local file, err = io.open(file_path, "w")
    if not file then
        return false, err
    end
    file:close()
    return true
end

-- Function to create a directory
function file_utils.create_dir(dir_path)
    local success, err = lfs.mkdir(dir_path)
    return success, err
end

-- Function to rename a file or directory
function file_utils.rename(old_path, new_path)
    local success, err = os.rename(old_path, new_path)
    return success, err
end

return file_utils
