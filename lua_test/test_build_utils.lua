local build_utils = require("build_utils")

function test_git_clone(repo_url, target_dir)
    if build_utils.git_clone(repo_url, target_dir) then
        print("clone success")
    else
        print("failed to clone")
    end
end

-- Example usage
local repo_url = "https://github.com/postgres/postgres.git"
local target_dir = "./PostgreSQL/"

test_git_clone(repo_url, target_dir)