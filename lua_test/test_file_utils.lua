local file_utils = require("file_utils")

-- Test function for checking file existence
function test_file_exists(file_path)
    if file_utils.file_exists(file_path) then
        print(file_path .. " exists.")
    else
        print(file_path .. " does not exist.")
    end
end

-- Test function for checking directory existence
function test_dir_exists(dir_path)
    if file_utils.dir_exists(dir_path) then
        print(dir_path .. " exists.")
    else
        print(dir_path .. " does not exist.")
    end
end

-- Test function for creating a file
function test_create_file(file_path)
    local success, err = file_utils.create_file(file_path)
    if success then
        print(file_path .. " created successfully.")
    else
        print("Failed to create " .. file_path .. ": " .. err)
    end
end

-- Test function for creating a directory
function test_create_dir(dir_path)
    local success, err = file_utils.create_dir(dir_path)
    if success then
        print(dir_path .. " created successfully.")
    else
        print("Failed to create " .. dir_path .. ": " .. err)
    end
end

-- Test function for renaming a file
function test_rename_file(old_path, new_path)
    local success, err = file_utils.rename(old_path, new_path)
    if success then
        print(old_path .. " renamed to " .. new_path .. " successfully.")
    else
        print("Failed to rename " .. old_path .. " to " .. new_path .. ": " .. err)
    end
end

-- Test function for renaming a directory
function test_rename_dir(old_path, new_path)
    local success, err = file_utils.rename(old_path, new_path)
    if success then
        print(old_path .. " renamed to " .. new_path .. " successfully.")
    else
        print("Failed to rename " .. old_path .. " to " .. new_path .. ": " .. err)
    end
end

-- Example usage of test functions
local file_path = "./test_file"
local dir_path = "./test_dir"
local new_file_path = "./new_test_file"
local new_dir_path = "./new_test_dir"

test_file_exists(file_path)
test_dir_exists(dir_path)
test_create_file(file_path)
test_create_dir(dir_path)
test_rename_file(file_path, new_file_path)
test_rename_dir(dir_path, new_dir_path)
