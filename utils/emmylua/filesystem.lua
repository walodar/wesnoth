---@meta

filesystem = {}

---Read a text file into memory, or list files in a directory
---@param path string
---@return string|string[]
function filesystem.read_file(path) end

---Check if a file exists
---@param path string
---@return boolean
function filesystem.have_file(path) end

---Resolve a file path relative to the current script
---@param path string
---@return string
function filesystem.canonical_path(path) end

---Determine the size of an image asset
---@param path string
---@return integer width
---@return integer height
function filesystem.image_size(path) end

---Check if an asset exists in the current binary path
---@param type string
---@param path string
---@return boolean
function filesystem.have_asset(type, path) end

---Resolve an asset path against the current binary path
---@param type string
---@param path string
---@return string
function filesystem.resolve_asset(type, path) end
