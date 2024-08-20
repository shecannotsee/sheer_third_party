local build_utils = {}

-- Lua function to clone a Git repository
function build_utils.git_clone(repo_url, target_dir)
    local clone_command = string.format("git clone %s %s", repo_url, target_dir)
    local success = os.execute(clone_command)
    if success then
        return true
    else
        return false
    end
end

return build_utils
